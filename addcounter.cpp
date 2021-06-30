#include "addcounter.h"
#include "ui_addcounter.h"

AddCounter::AddCounter(QWidget *parent, std::map<int, dataPoint>& _data_points, std::map<int, std::map<QString, int>>& _counter_data) :
    QDialog(parent),
    ui(new Ui::AddCounter)
{
    ui->setupUi(this);
    this->setFixedSize(490, 340);
    counter_lines = _data_points;
    counter_lines_data = _counter_data;
    counter_line_id = counter_lines.size();
}

AddCounter::~AddCounter()
{
    delete ui;
}

void AddCounter::add_counter_line()
{
    _new_data_point.name = ui->le_counter->text();
    _new_data_point.drawn = false;
    _new_data_point.direction = QString();
    _new_data_point.point_one =cv::Point(0,0);
    _new_data_point.point_two =cv::Point(0,0);

    counter_lines.insert(std::pair<int, dataPoint>(new_counter_line_id, _new_data_point));
}

void AddCounter::add_counter_line_initial_data()
{
    std::map<QString, int> _temp_data_map;
    int initial_vehicle_count = 0;
    QString car_data = "car";
    QString bus_data = "bus";
    QString truck_data = "truck";
    QString motorbike_data = "motorbike";
    QString person_data = "person";
    QString total_data = "total";
    _temp_data_map.insert(std::pair<QString, int>(car_data, initial_vehicle_count));
    _temp_data_map.insert(std::pair<QString, int>(bus_data, initial_vehicle_count));
    _temp_data_map.insert(std::pair<QString, int>(truck_data, initial_vehicle_count));
    _temp_data_map.insert(std::pair<QString, int>(motorbike_data, initial_vehicle_count));
    _temp_data_map.insert(std::pair<QString, int>(person_data, initial_vehicle_count));
    _temp_data_map.insert(std::pair<QString, int>(total_data, initial_vehicle_count));
    counter_lines_data.insert(std::pair<int, std::map<QString, int>>(new_counter_line_id, _temp_data_map));


}

void AddCounter::on_btn_save_clicked()
{
    if(ui->le_counter->text().isEmpty()){
        QMessageBox::critical(this, "Missing Counter Name",  "Your counter cannot have an empty name. Please add one.");
        return;
    }else if(ui->cb_direction->currentIndex()==0){
        QMessageBox::critical(this, "Invalid Counter Direction",  "Your counter must have a valid direction. Please provide one.");
        return;
    }else{
        new_counter_line_id = counter_line_id+1;
        add_counter_line();
        add_counter_line_initial_data();
        emit send_counter_addition_successful(new_counter_line_id);
    }

}


void AddCounter::on_btn_cancel_clicked()
{
    emit send_counter_addition_cancelled();
}

