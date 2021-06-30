#ifndef DETECTOR_H
#define DETECTOR_H

#include <QObject>
#include <QWidget>
#include <opencv2/core/utility.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "debugger.h"
#include "src/Detector/BaseDetector.h"
#include "src/Tracker/Ctracker.h"

using namespace cv;
using namespace std;

class Detector:public QObject
{
    Q_OBJECT
public:
    explicit Detector(QObject *parent = nullptr);
public:
    bool frame_stopped;
    cv::Mat current_frame_;
    mutex mutex_;
    Mat  Det_Frame;
    cv::UMat uframe;
    void detectionTask();
    void setFrame(const cv::Mat& _new_frame,float m_fps);
    vector<CRegion> Draw_Regions();
    vector<CRegion> regions;
    std::unique_ptr<CTracker>   new_tracker_;
    void Collect_Detector(unique_ptr<BaseDetector> &m_detector, std::unique_ptr<CTracker> &m_tracker);
    void Collect_Tracker(std::unique_ptr<CTracker> &m_tracker);
private:
    std::vector<cv::Scalar> m_colors;
    std::unique_ptr<BaseDetector>  new_Detector_;
    float Fps;
protected:
    std::string m_weightsFile;
    std::string m_configFile;
    std::string m_namesFile;
    tracking::Detectors m_detectorType = tracking::Detectors::Yolo_Darknet;
    std::unique_ptr<BaseDetector> m_detector;
public slots:
    void stopDet();
    void startDet();
};

#endif // DETECTOR_H
