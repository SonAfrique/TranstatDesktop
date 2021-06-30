#include "drawcounter.h"
#include "ui_drawcounter.h"

DrawCounter::DrawCounter(QWidget *parent, QImage & _current_image, int& _affected_id, std::map<int, dataPoint>& _counter_lines) :
    QDialog(parent),
    ui(new Ui::DrawCounter)
{
    ui->setupUi(this);
    this->setFixedSize(1300, 1000);
    counter_lines= _counter_lines;
    counter_line_id = _affected_id;
    LOGxy("ID:", counter_line_id);
    LOGxy("LINES COCUNT:", counter_lines.size());
    current_image = new QImage;
    *current_image = _current_image;

    mviewer = new OpenCVViewer(ui->imgViewer);
    mviewer->setGeometry(ui->imgViewer->geometry().x(), ui->imgViewer->geometry().y(), ui->imgViewer->width(), ui->imgViewer->height());
    cv::Mat mat_to_set(current_image->height(),current_image->width(),CV_8UC3,current_image->bits(), current_image->bytesPerLine());

    mat_2 = mat_to_set.clone();
    mat_3 = mat_to_set.clone();
    mviewer->setImage(mat_2);


    connect(mviewer, SIGNAL(mouseClicked(QMouseEvent*)), this, SLOT(mouseHandler(QMouseEvent*)));
    connect(mviewer, SIGNAL(mouseDoubleClicked(QMouseEvent*)), this, SLOT(mouseHandler(QMouseEvent*)));
    connect(mviewer, SIGNAL(mouseMoved(QMouseEvent*)), this, SLOT(mouseHandler(QMouseEvent*)));
    connect(mviewer, SIGNAL(mouseReleased(QMouseEvent*)), this, SLOT(mouseHandler(QMouseEvent*)));
}

DrawCounter::~DrawCounter()
{
    delete ui;
}

void DrawCounter::mouseHandler(QMouseEvent *event)
{
    cv::Point pt = mviewer->mapPoint(cv::Point(event->x(), event->y()));

    int sizeMultiplier = mat_2.cols/640;

    if (event->button() == Qt::LeftButton && (event->buttons() & Qt::LeftButton) == Qt::LeftButton){
        //Left button Clicked
        line_point_one = pt;
        line_point_two = pt;
        cv::circle(mat_2,pt,0.5,cv::Scalar(0,255,0),1, cv::LINE_AA);
//        mviewer->setImage(mat_2);
        //        emit sendPoint(rec_point);
    }else if (event->button() == Qt::NoButton && (event->buttons() & Qt::LeftButton) == 1){
        if(event->type() == QEvent::MouseMove){
            line_point_two = pt;
        }
        update();
        cv::line(mat_2, line_point_one, line_point_two, cv::Scalar(0, 255,0), 1, cv::LINE_AA);

        mviewer->setImage(mat_2);

        cv::line(mat_2, line_point_one, line_point_two, cv::Scalar(0, 255,0), 1, cv::LINE_AA);
//        mviewer->setImage(mat_2);
    }else if (event->button() == Qt::LeftButton && (event->buttons() & Qt::LeftButton) == 0){
        line_point_two = pt;
        QMessageBox::StandardButton confirmNewPoints;
        confirmNewPoints = QMessageBox::warning(this, "Confirm Data Point",
                                              "Are you sure about the data point?",
                                              QMessageBox::Yes | QMessageBox::No);
        if (confirmNewPoints == QMessageBox::Yes) {
            cv::line(mat_3, line_point_one, line_point_two, cv::Scalar(0, 255,0), 1, cv::LINE_AA);
              std::map<int, dataPoint>::iterator it;
              it = counter_lines.find(counter_line_id);
              if (it!=counter_lines.end()){
                  it->second.point_one = line_point_one;
                  it->second.point_two = line_point_two;
                  it->second.drawn = true;
              }
//            updateDataCollectionPoint(rec_point_one, rec_point_two);

            mviewer->setImage(mat_3);
        }else{

        }







        //Finished drawing rectangle

//        emit sendPoint(rec_point);
    }else if (event->type()==QEvent::MouseButtonDblClick && (event->button() == Qt::LeftButton)){
        cv::Point rec_point = pt;

//        emit sendPoint(rec_point);
    }
}

void DrawCounter::on_btn_apply_clicked()
{
    emit send_drawing_task_complete(counter_line_id);
}


void DrawCounter::on_btn_cancel_clicked()
{
    emit send_drawing_task_cancelled();
}

