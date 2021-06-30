#ifndef DRAWCOUNTER_H
#define DRAWCOUNTER_H

#include <QDialog>
#include "debugger.h"
#include "opencvviewer.h"
namespace Ui {
class DrawCounter;
}

class DrawCounter : public QDialog
{
    Q_OBJECT

public:
    explicit DrawCounter(QWidget *parent, QImage &, int&, std::map<int, dataPoint>&);
    ~DrawCounter();
public:
    int counter_line_id;
    std::map<int, dataPoint> counter_lines;

private:
    OpenCVViewer* mviewer;
    QImage* current_image;
    cv::Mat mat_2;
    cv::Mat mat_3;
    cv::Point line_point_one;
    cv::Point line_point_two;
private slots:
    void mouseHandler(QMouseEvent* event);
    void on_btn_apply_clicked();
    void on_btn_cancel_clicked();

signals:
    void send_drawing_task_complete(int &);
    void send_drawing_task_cancelled();
private:
    Ui::DrawCounter *ui;
};

#endif // DRAWCOUNTER_H
