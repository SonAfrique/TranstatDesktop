#ifndef DEBUGGER_H
#define DEBUGGER_H
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <iostream>
#include <QMessageBox>
#include<QFileDialog>
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <QMessageBox>
#include<QFileDialog>
#include <QDateTime>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/freetype.hpp>



#define LOGx(x) std::cout<< x << std::endl
#define LOGxy(x,y) std::cout<< x << y << std::endl
#define Debug(x) qDebug()<<(x)

struct loggedUser{
    QString username;
    QString name;
    QString email;
    QString user_id;
    QString password;
    QString user_role;
    QString user_avatar;
    QString user_status;
    QDateTime timestamp;
};

struct dataPoint{
    QString name;
    QString direction;
    bool drawn;
    cv::Point point_one;
    cv::Point point_two;
};


struct plateData{
    QImage plate_image;
    int id;
    QString plate;
    QDateTime time;
};
struct lineManager{
    QString name;
    bool enabled;
    bool drawn;
};
class Debugger
{
public:
    Debugger();
};

#endif // DEBUGGER_H
