#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLayout>
#include <QSpacerItem>
#include <QCompleter>
#include <QTableWidget>
#include <QMessageBox>
#include <QKeyEvent>
#include <QFileDialog>
#include <QTimer>
#include <QDateTime>
#include <fstream>
#include <string>
#include <iostream>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts>
#include "player.h"
#include "analysisid.h"
#include "dbconnection.h"
#include "addcounter.h"
#include "drawcounter.h"
#include "magnifyvisuals.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_login_clicked();
    void on_btn_vehicle_analytics_clicked();
    void on_btn_lights_analytics_clicked();
    void on_btn_pedestrian_analytics_clicked();
    void on_btn_play_pause_clicked();

    void on_btn_stop_clicked();
    void on_btn_add_counter_clicked();
    void on_btn_draw_counter_clicked();
    void on_btn_edit_counter_clicked();
    void on_btn_show_hide_counter_clicked();
    void on_btn_show_hide_class_data_clicked();

private:
    void restore_frames();
    void load_video();
    DbConnection* dbConnection;
private:
    QString getFormattedTime(int timeInSeconds);
    QImage current_image;
    QString filename;
private:
    Player *player;
private slots:
    void update_video_label(QImage img);
    void on_btn_analysis_id_clicked();

private:
    QString analysis_id;
    bool analysis_id_exists = false;
    void process_analysis_id();
    AnalysisId* analysisId;
private slots:
    void receive_analysis_id_added_successfully(QString&);
    void receive_analysis_id_addition_cancelled();

    void receive_counter_added_successfully(int &);
    void receive_counter_addition_cancelled();

    void draw_counter_line_on_frame(int&, std::map<int, dataPoint>&);
public:
    std::map<int, dataPoint> *counter_lines;
    std::map<int, std::map<QString, int>>* counter_lines_data;
private:
    AddCounter* addCounterLine;
    DrawCounter* drawCounter;
//    QImage current_image;
private slots:
    void receive_drawing_counter_complete(int&);
    void receive_drawing_counter_lines_cancelled();
    void receive_returned_count_data(int, int, QString);
    void on_btn_magnify_visuals_clicked();

private:
    void push_single_count_data_to_db(QString&, QString&, int&, int&, int&);

private:
    void _add_counter_lines_to_video();
    bool counter_lines_added = false;
    bool update_data;
    int _current_line_selection_for_update;
    void display_and_update_counter_line_data(int&);
private:
    bool graph_drawn = false;
    QtCharts::QPieSeries* _statistics_series;
    QtCharts::QChartView* _statistics_charts;
private:
    int _current_count_cars;
    int _current_count_buses;
    int _current_count_trucks;
    int _current_count_motorbikes;
    int _current_count_pedestrians;
    int _current_count_totals;
    QString _magnifier_counter;

    int _extended_current_count_cars;
    int _extended_current_count_buses;
    int _extended_current_count_trucks;
    int _extended_current_count_motorbikes;
    int _extended_current_count_pedestrians;
    int _extended_current_count_totals;
    QString _extended_magnifier_counter;



private:
    MagnifyVisuals* magnifyVisuals;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
