#include "magnifyvisuals.h"
#include "ui_magnifyvisuals.h"

MagnifyVisuals::MagnifyVisuals(QWidget *parent, QString& _counterline, int & cars, int & buses, int& trucks, int& motorbikes, int& pedestrians, int& total) :
    QDialog(parent),
    ui(new Ui::MagnifyVisuals)
{
    ui->setupUi(this);
    this->setFixedSize(1100, 1000);
    counterline_name = _counterline;
    current_cars_total = cars;
    current_buses_total = buses;
    current_trucks_total = trucks;
    current_motorbikes_total = motorbikes;
    current_pedestrian_total = pedestrians;
    current_total_total = total;
    if(current_total_total>0){
//                if(graph_drawn){
//                    ui->data_visual->removeWidget(_statistics_charts);
//                }
                _statistics_series = new QtCharts::QPieSeries();
                _statistics_series->setHoleSize(0.35);


                float _car_percentage = float(current_cars_total)/float(current_total_total)*100;
                QString _car_caption = "Cars % "+QString::number(_car_percentage, 'f', 2)+"%";
                QtCharts::QPieSlice* car_slice =_statistics_series->append(_car_caption, _car_percentage);
                car_slice->setExploded();
                car_slice->setLabelVisible();



                float _bus_percentage = float(current_buses_total)/float(current_total_total)*100;
                QString _bus_caption = "Buses % "+QString::number(_bus_percentage, 'f', 2)+"%";
                _statistics_series->append(_bus_caption, _bus_percentage);
                _statistics_series->setLabelsVisible();

                float _truck_percentage = float(current_trucks_total)/float(current_total_total)*100;
                QString _truck_caption = "Trucks % "+QString::number(_truck_percentage, 'f', 2)+"%";
                _statistics_series->append(_truck_caption, _truck_percentage);
                _statistics_series->setLabelsVisible();

                float _bike_percentage = float(current_motorbikes_total)/float(current_total_total)*100;
                QString _bike_caption = "Motorbike % "+QString::number(_bike_percentage, 'f', 2)+"%";
                _statistics_series->append(_bike_caption, _bike_percentage);
                _statistics_series->setLabelsVisible();

                float _pedestrian_percentage = float(current_pedestrian_total)/float(current_total_total)*100;
                QString _pedestrian_caption = "Pedestrian % "+QString::number(_pedestrian_percentage, 'f', 2)+"%";
                _statistics_series->append(_pedestrian_caption, _pedestrian_percentage);
                _statistics_series->setLabelsVisible();

                _statistics_charts = new QtCharts::QChartView();
                _statistics_charts->setRenderHint(QPainter::Antialiasing);
                _statistics_charts->chart()->setTitle("Classifications by Percentage");
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

MagnifyVisuals::~MagnifyVisuals()
{
    delete ui;
}
