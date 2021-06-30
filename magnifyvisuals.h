#ifndef MAGNIFYVISUALS_H
#define MAGNIFYVISUALS_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "debugger.h"

namespace Ui {
class MagnifyVisuals;
}

class MagnifyVisuals : public QDialog
{
    Q_OBJECT

public:
    explicit MagnifyVisuals(QWidget *parent, QString&, int &, int &, int&, int&, int&, int&);
    ~MagnifyVisuals();
private:
    bool graph_drawn = false;
    QtCharts::QPieSeries* _statistics_series;
    QtCharts::QChartView* _statistics_charts;
private:
    QString counterline_name;
    int current_cars_total;
    int current_buses_total;
    int current_trucks_total;
    int current_motorbikes_total;
    int current_pedestrian_total;
    int current_total_total;
private slots:

private:
    Ui::MagnifyVisuals *ui;
};

#endif // MAGNIFYVISUALS_H
