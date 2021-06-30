#include "detector.h"

Detector::Detector(QObject *parent) : QObject(parent)
                   {
    frame_stopped = false;
}

void Detector::detectionTask()
{
    while(!frame_stopped){
         mutex_.lock();
         Det_Frame=current_frame_.clone();
         mutex_.unlock();
         if(!Det_Frame.empty()){
             if (!new_Detector_->CanGrayProcessing() || new_tracker_ ->CanColorFrameToTrack()) {
                 uframe = Det_Frame.getUMat(cv::ACCESS_READ);
             }else {
                 cv::cvtColor(Det_Frame, uframe, cv::COLOR_BGR2GRAY);
             }
             new_Detector_->Detect(uframe);
              regions = new_Detector_->GetDetects();
         }
        if(frame_stopped){
            break;
        }
    }
}

void Detector::setFrame(const Mat &_new_frame, float m_fps)
{
    current_frame_ = _new_frame.clone();
    Fps=m_fps;
}

vector<CRegion> Detector::Draw_Regions()
{
    vector<CRegion> &regs=regions ;
    return regs;
}

void Detector::Collect_Detector(unique_ptr<BaseDetector> &m_detector, std::unique_ptr<CTracker> &m_tracker)
{
    new_Detector_ = static_cast<unique_ptr<BaseDetector, default_delete<BaseDetector>> &&>(m_detector);
    new_tracker_= static_cast<unique_ptr<CTracker, default_delete<CTracker>> &&>(m_tracker);
}

void Detector::stopDet()
{
    frame_stopped = true;
}

void Detector::startDet()
{
    frame_stopped = false;
}

