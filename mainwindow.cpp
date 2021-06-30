#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    ui->frame_menu->hide();
    ui->frame_buttons_panel->hide();
    ui->frame_heading->hide();
    ui->le_username->setFocus();
    ui->stackedWidget->setCurrentIndex(0);

    counter_lines = new std::map<int, dataPoint>;
    counter_lines_data = new std::map<int, std::map<QString, int>>;

    player = new Player(this);
    dbConnection = new DbConnection;
    QObject::connect(player, SIGNAL(send_processed_image(QImage)),
                         this, SLOT(update_video_label(QImage)));
    QObject::connect(player, SIGNAL(send_count_data(int,int,QString)),
                     this, SLOT(receive_returned_count_data(int,int,QString)));

    connect(ui->cb_counter_line, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index){ /* ... */
                if (index==0){
                    update_data = false;
                }else{
                    QString current_counter = ui->cb_counter_line->currentText();
                    QString _line_id = current_counter.left(current_counter.indexOf(":"));
                    int _display_id = _line_id.toInt();
                    _current_line_selection_for_update = _display_id;
                    display_and_update_counter_line_data(_current_line_selection_for_update);
                    update_data = true;
                }
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_btn_vehicle_analytics_clicked()
{
    restore_frames();
    ui->stackedWidget->setCurrentIndex(2);
    ui->frame_buttons_panel->hide();

    process_analysis_id();
}


void MainWindow::on_btn_lights_analytics_clicked()
{

}


void MainWindow::on_btn_pedestrian_analytics_clicked()
{

}

void MainWindow::restore_frames()
{
    ui->frame_menu->show();
    ui->frame_buttons_panel->show();
    ui->frame_heading->show();
}

void MainWindow::load_video()
{
    filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Video"), QDir::homePath(),
                                                    tr("Video Files (*.avi *.mpg *.mp4)"), 0, QFileDialog::DontUseNativeDialog);
    QFileInfo name = filename;
    if(!filename.isEmpty()){
        if(!player->load_video(filename.toStdString().data())){
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        } else{
            this->setWindowTitle(name.fileName());
            ui->btn_play_pause->setEnabled(true);
            ui->video_slider->setMaximum(player->get_number_of_frames());
            ui->lbl_remaining_time->setText(getFormattedTime((int)player->get_number_of_frames()/(int)player->get_frame_rate()));

        }
    }
}

QString MainWindow::getFormattedTime(int timeInSeconds)
{
    return QString();
}

void MainWindow::update_video_label(QImage img)
{
        current_image = img;
        int w = ui->lbl_video->width();
        int h = ui->lbl_video->height();
        QPixmap videoPixmap = QPixmap::fromImage(img);
        if(!img.isNull()){
            ui->lbl_video->setPixmap(videoPixmap.scaled(w,h,
                                                   Qt::KeepAspectRatio));
            ui->lbl_video->setScaledContents(true);
            ui->video_slider->setValue(player->get_current_frame());
            ui->lbl_elapsed_time->setText(getFormattedTime((int) player->get_current_frame()/(int) player->get_frame_rate()));
        }
}

void MainWindow::on_btn_play_pause_clicked()
{
    if(!analysis_id_exists){
        QMessageBox::critical(this, "Missing Analysis Id",  "You cannot conduct analysis without an Id. Please add one.");
        return;
    }else{
        if(filename.isEmpty()){
            load_video();
        }else{

            if(player->is_stopped()){
                player->_show_counter_lines = true;
                player->play_video();
            }else{
                player->pause_video();
            }
        }
    }

}


void MainWindow::on_btn_stop_clicked()
{
    player->stop_video();
    QPixmap pixmap;
    pixmap.fill(Qt::black);
    ui->lbl_video->setPixmap(pixmap);
    ui->btn_play_pause->setDisabled(true);
    ui->lbl_elapsed_time->setText("00:00:00");
    ui->lbl_remaining_time->setText("00:00:00");
    ui->video_slider->setValue(0);
}


void MainWindow::on_btn_add_counter_clicked()
{
    if(current_image.isNull()){
        QMessageBox::critical(this, "Null Image ",  "You cannot draw counters on an empty image. Load video to proceed.");
        return;
    }else{
        if(player->isRunning()){
            player->_show_counter_lines = false;
            player->pause_video();
        }
        addCounterLine = new AddCounter(this, *counter_lines, *counter_lines_data);
        addCounterLine->setModal(true);
        addCounterLine->show();
    }


    QObject::connect(addCounterLine, SIGNAL(send_counter_addition_successful(int &)),
                     this, SLOT(receive_counter_added_successfully(int &)));

    QObject::connect(addCounterLine, SIGNAL(receive_counter_addition_cancelled()),
                     this, SLOT(receive_counter_addition_cancelled()));

}


void MainWindow::on_btn_draw_counter_clicked()
{

}


void MainWindow::on_btn_edit_counter_clicked()
{

}


void MainWindow::on_btn_show_hide_counter_clicked()
{

}


void MainWindow::on_btn_show_hide_class_data_clicked()
{

}


void MainWindow::on_btn_analysis_id_clicked()
{
    process_analysis_id();
}

void MainWindow::process_analysis_id()
{
    analysisId = new AnalysisId;
    analysisId->setModal(true);
    analysisId->show();

    QObject::connect(analysisId, SIGNAL(send_analysis_id_added_successfully(QString&)),
                     this, SLOT(receive_analysis_id_added_successfully(QString&)));

    QObject::connect(analysisId, SIGNAL(send_analysis_id_addition_cancelled()),
                     this, SLOT(receive_analysis_id_addition_cancelled()));

}

void MainWindow::receive_analysis_id_added_successfully(QString &_returned_analysis_id)
{
    analysisId->close();
    analysis_id = _returned_analysis_id;
    analysis_id_exists = true;
    QMessageBox::information(this, "Analysis Id Addition Success ", _returned_analysis_id+ "has been successfully added.");
}

void MainWindow::receive_analysis_id_addition_cancelled()
{
    analysisId->close();
    QMessageBox::information(this, "Analysis Id Addition Cancelled ",  "Analysis Id addition cancelled.");
    return;
}

void MainWindow::receive_counter_added_successfully(int& _returned_line)
{
    *counter_lines = addCounterLine->counter_lines;
    *counter_lines_data = addCounterLine->counter_lines_data;
    addCounterLine->close();
    QMessageBox::information(this, "Counter Line Additon Success ","Please draw the line for analysis.");
    draw_counter_line_on_frame(_returned_line, *counter_lines);
}

void MainWindow::receive_counter_addition_cancelled()
{
    addCounterLine->close();
    QMessageBox::information(this, "Counter Line Addition Cancelled ",  "Counter Line addition cancelled.");
    return;
}

void MainWindow::draw_counter_line_on_frame(int & _id_to_draw, std::map<int, dataPoint> &_counter_lines)
{


//    if(player->is_stopped())

        drawCounter = new DrawCounter(this, current_image, _id_to_draw, _counter_lines);
        drawCounter->setModal(true);
        drawCounter->show();


        //    bring slots
        QObject::connect(drawCounter, SIGNAL(send_drawing_task_complete(int&)),
                         this, SLOT(receive_drawing_counter_complete(int&)));

        QObject::connect(drawCounter, SIGNAL(send_drawing_task_cancelled()),
                         this, SLOT(receive_drawing_counter_lines_cancelled()));
}

void MainWindow::receive_drawing_counter_complete(int&_drawn_id)
{
    drawCounter->close();
    *counter_lines = drawCounter->counter_lines;
    cv::Mat current_frame(current_image.height(),current_image.width(),CV_8UC3,current_image.bits(), current_image.bytesPerLine());
    float xMax = current_frame.cols;
    float yMax = current_frame.rows;
    auto Pti2f = [&](cv::Point pt) -> cv::Point2f
 {
     return cv::Point2f(pt.x / xMax, pt.y / yMax);
 };
    std::map<int, dataPoint>::iterator it;
    it = counter_lines->find(_drawn_id);
    if (it!=counter_lines->end()){
        player->add_counter_line(RoadLine(Pti2f(it->second.point_one), Pti2f(it->second.point_two), it->first));
        QString counter_line_item = QString::number(_drawn_id)+": "+it->second.name;
        ui->cb_counter_line->addItem(counter_line_item);
    }





    //remove counter lines

    //add counter lines

}

void MainWindow::receive_drawing_counter_lines_cancelled()
{
    drawCounter->close();
    QMessageBox::information(this, "Counter Line Drawing Cancelled ",  "Counter Line Dtawing cancelled.");
    return;
}

void MainWindow::receive_returned_count_data(int _line_id, int _class_id, QString _returned_class)
{
    QString counter = analysis_id+":"+QString::number(_line_id);
    int class_up;
    int total_up;
    std::map<int, std::map<QString, int> >::iterator itr;
    std::map<QString, int>::iterator it;
    for(itr = counter_lines_data->begin(); itr != counter_lines_data->end(); itr++){
        if(itr->first == _line_id){
            for(it = itr->second.begin(); it !=itr->second.end();it++){
                if(it->first == _returned_class){
                    it->second++;
                    class_up = it->second;

                }else if(it->first=="total"){
                    it->second++;
                    total_up = it->second;
                }

            }
            push_single_count_data_to_db(counter,_returned_class, _class_id, class_up, total_up);
            if(update_data){
                display_and_update_counter_line_data(_current_line_selection_for_update);
            }
        }

    }

}

void MainWindow::push_single_count_data_to_db(QString & _unique_id, QString & _classification, int &_track_id, int & _class_up, int &_total_up)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString dateString = currentTime.toString("yyyy-MM-dd T hh:mm:ss");
    if(dbConnection->conn_open()){
         QSqlQuery query(QSqlDatabase::database("MyConnect"));
         query.prepare(QString("INSERT INTO counts (analysis_id, counter, date_time, class, class_id, class_count, total_count) "
                               "VALUES (:analysis_id, :counter, :date_time, :class, :class_id, :class_count, :total_count)"));
         query.bindValue(":analysis_id", analysis_id);
         query.bindValue(":counter", _unique_id);
         query.bindValue(":date_time", dateString);
         query.bindValue(":class", _classification);
         query.bindValue(":class_id", _track_id);
         query.bindValue(":class_count", _class_up);
         query.bindValue(":total_count", _total_up);

        if(!query.exec()){
            Debug(query.lastError());
            QMessageBox::critical(this, "Vehicle Data Insertion Error", query.lastError().text());
            return;
        }else{
            LOGx("successfully updated vehicle data ...");
                }
    }
}

void MainWindow::_add_counter_lines_to_video()
{

//     std::map<int, dataPoint>::iterator it;
//    for ( it = counter_lines->begin(); it != counter_lines->end(); ++it ){
//      player->add_counter_line(RoadLine(Pti2f(it->second.point_one), Pti2f(it->second.point_two), it->first));
    //    }
}

void MainWindow::display_and_update_counter_line_data(int &_line_to_update)
{
    int _total_count =0;
    int _car_count = 0;
    int _bus_count = 0;
    int _motorbike_count = 0;
    int _truck_count = 0;
    int _pedestrian_count = 0;
    _magnifier_counter = analysis_id+":"+QString::number(_line_to_update);
    std::map<int, std::map<QString, int> >::iterator itr;
    std::map<QString, int>::iterator it;
    for(itr = counter_lines_data->begin(); itr != counter_lines_data->end(); itr++){
        if(itr->first == _line_to_update){
            for(it = itr->second.begin(); it !=itr->second.end();it++){
                if(it->first == "car"){
                    _car_count= it->second;
                    _current_count_cars = _car_count;
                    ui->lbl_car_count->setText(QString::number(it->second));
                }else if(it->first=="bus"){
                    _bus_count= it->second;
                    _current_count_buses = _bus_count;
                    ui->lbl_bus_count->setText(QString::number(it->second));
                }else if(it->first=="truck"){
                    _truck_count= it->second;
                    _current_count_trucks = _truck_count;
                    ui->lbl_truck_count->setText(QString::number(it->second));
                }else if(it->first=="motorbike"){
                    _motorbike_count= it->second;
                    _current_count_motorbikes = _motorbike_count;
                    ui->lbl_motor_cycle_count->setText(QString::number(it->second));
                }else if(it->first=="person"){
                    _pedestrian_count = it->second;
                    _current_count_pedestrians = _pedestrian_count;
                    ui->lbl_pedestrian_count->setText(QString::number(it->second));
                }else if(it->first=="total"){
                    _total_count = it->second;
                    _current_count_totals = _total_count;
                    ui->lbl_sum->setText(QString::number(it->second));
                }

            }
        }
        if(_total_count>0){
            if(graph_drawn){
                ui->data_visual->removeWidget(_statistics_charts);
            }
            _statistics_series = new QtCharts::QPieSeries();
            _statistics_series->setHoleSize(0.35);


            float _car_percentage = float(_car_count)/float(_total_count)*100;
            QString _car_caption = "Cars % "+QString::number(_car_percentage, 'f', 2)+"%";
            QtCharts::QPieSlice* car_slice =_statistics_series->append(_car_caption, _car_percentage);
            car_slice->setExploded();
            car_slice->setLabelVisible();



            float _bus_percentage = float(_bus_count)/float(_total_count)*100;
            QString _bus_caption = "Buses % "+QString::number(_bus_percentage, 'f', 2)+"%";
            _statistics_series->append(_bus_caption, _bus_percentage);
            _statistics_series->setLabelsVisible();

            float _truck_percentage = float(_truck_count)/float(_total_count)*100;
            QString _truck_caption = "Trucks % "+QString::number(_truck_percentage, 'f', 2)+"%";
            _statistics_series->append(_truck_caption, _truck_percentage);
            _statistics_series->setLabelsVisible();

            float _bike_percentage = float(_motorbike_count)/float(_total_count)*100;
            QString _bike_caption = "Motorbike % "+QString::number(_bike_percentage, 'f', 2)+"%";
            _statistics_series->append(_bike_caption, _bike_percentage);
            _statistics_series->setLabelsVisible();

            float _pedestrian_percentage = float(_pedestrian_count)/float(_total_count)*100;
            QString _pedestrian_caption = "Pedestrian % "+QString::number(_pedestrian_percentage, 'f', 2)+"%";
            _statistics_series->append(_pedestrian_caption, _pedestrian_percentage);
            _statistics_series->setLabelsVisible();

            _statistics_charts = new QtCharts::QChartView();
            _statistics_charts->setRenderHint(QPainter::Antialiasing);
            _statistics_charts->chart()->setTitle("Credit and Cash Sales Analysis");
            _statistics_charts->chart()->setDropShadowEnabled(true);
            _statistics_charts->chart()->addSeries(_statistics_series);
            _statistics_charts->chart()->legend()->setAlignment(Qt::AlignBottom);
            _statistics_charts->chart()->setTheme(QtCharts::QChart::ChartThemeQt);
            _statistics_charts->chart()->legend()->setFont(QFont("Arial", 8));
            _statistics_charts->setRenderHint(QPainter::Antialiasing);
            _statistics_charts->chart()->setAnimationOptions(QtCharts::QChart::AllAnimations);
            ui->data_visual->addWidget(_statistics_charts);
            graph_drawn = true;
        }


    }
}


void MainWindow::on_btn_magnify_visuals_clicked()
{
    if(!graph_drawn){
        QMessageBox::critical(this, "No Line Data Selected", "Select Line Data First.");
        return;
    }else{
        _extended_current_count_cars = _current_count_cars;
        _extended_current_count_buses = _current_count_buses;
        _extended_current_count_trucks =_current_count_trucks;
        _extended_current_count_motorbikes =_current_count_motorbikes;
        _extended_current_count_pedestrians =_current_count_pedestrians;
        _extended_current_count_totals =_current_count_totals;
        _extended_magnifier_counter = _magnifier_counter;
        magnifyVisuals = new MagnifyVisuals(this, _extended_magnifier_counter, _extended_current_count_cars,
                                            _extended_current_count_buses, _extended_current_count_trucks,
                                            _extended_current_count_motorbikes, _extended_current_count_pedestrians, _extended_current_count_totals);
        magnifyVisuals->setModal(true);
        magnifyVisuals->show();
    }
}

