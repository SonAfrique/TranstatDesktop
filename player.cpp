#include "player.h"

Player::Player(QObject* parent): QThread(parent),
    m_showLogs(true),
    m_fps(25),
    m_isTrackerInitialized(false),
    m_startFrame(0),
    m_endFrame(0),
    m_finishDelay(0)
{

    //    redis.set("key", "val");
    #ifdef _WIN32
        std::string pathToModel = "../../data/";
    #else
        std::string pathToModel = "../data/";
    #endif
        stop = true;
    //    m_inFile = video_to_play;
    //    m_inFile = "/home/vt/pangani.mp4";
    //    m_inFile = filename;
    //    m_outFile = "../data/pangani.avi";
        m_showLogs = 1;
        m_startFrame = 0;
        m_endFrame = 0;
        m_finishDelay = 0;

        m_weightsFile = "/home/vt/weights_cfg/yolov4.weights";
        m_configFile = "/home/vt/weights_cfg/yolov4.cfg";
        m_namesFile = "/home/vt/weights_cfg/coco.names";
        if (m_weightsFile.empty() && m_configFile.empty())
        {
            m_weightsFile = pathToModel + "yolov3.weights";
            m_configFile = pathToModel + "yolov3.cfg";
        }
        if (m_namesFile.empty())
            m_namesFile = pathToModel + "coco.names";

        std::map<std::string, tracking::Detectors> infMap;
        infMap.emplace("darknet", tracking::Detectors::Yolo_Darknet);
        infMap.emplace("ocvdnn", tracking::Detectors::DNN_OCV);
    //	std::string inference = parser.get<std::string>("inference");
        std::string inference = "darknet";
        auto infType = infMap.find(inference);
        if (infType != std::end(infMap))
            m_detectorType = infType->second;
        else
            m_detectorType = tracking::Detectors::Yolo_Darknet;

        std::cout << "Inference framework set " << inference << " used " << m_detectorType << ", weights: " << m_weightsFile << ", config: " << m_configFile << ", names: " << m_namesFile << std::endl;

        m_colors.push_back(cv::Scalar(255, 0, 0));
        m_colors.push_back(cv::Scalar(0, 255, 0));
        m_colors.push_back(cv::Scalar(0, 0, 255));
        m_colors.push_back(cv::Scalar(255, 255, 0));
        m_colors.push_back(cv::Scalar(0, 255, 255));
        m_colors.push_back(cv::Scalar(255, 0, 255));
        m_colors.push_back(cv::Scalar(255, 127, 255));
        m_colors.push_back(cv::Scalar(127, 0, 255));
        m_colors.push_back(cv::Scalar(127, 0, 127));


        connect(this,&Player::send_on_video_stop,&CarDetect,&Detector::stopDet);
        connect(this,&Player::send_on_video_start,&CarDetect,&Detector::startDet);
        capture = new VideoCapture();

        stop = true;
        //    CarDetect.frame_stopped = true;
}

Player::~Player()
{
    mutex.lock();
    stop = true;
    emit send_on_video_stop();
    capture->release();
    delete capture;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void Player::run()
{
    std::thread det_Thread(&Detector::detectionTask, &CarDetect);

       #ifndef SILENT_WORK
           cv::namedWindow("Video", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
       #endif

           int k = 0;

           double freq = cv::getTickFrequency();

           int64 allTime = 0;

           bool manualMode = false;
           int framesCounter = m_startFrame + 1;


           if (!capture->isOpened())
           {
               std::cerr << "Can't open " << m_inFile << std::endl;
               return;
           }

           cv::Mat colorFrame;
           capture->read( colorFrame);
           if (colorFrame.empty())
           {
               std::cerr << "Frame is empty!" << std::endl;
               return;
           }
           if (!m_isTrackerInitialized)
           {
               cv::UMat uframe = colorFrame.getUMat(cv::ACCESS_READ);
               m_isTrackerInitialized = InitTracker(uframe);
               if (!m_isTrackerInitialized)
               {
                   std::cerr << "Tracker initialize error!!!" << std::endl;
                   return;
               }
           }



        int delay = (800/frameRate);
        while (!stop){
            if(!capture->read(colorFrame)){
                stop = true;
            }
            if (colorFrame.empty())
            {
                std::cerr << "Frame is empty!" << std::endl;
                break;
            }
            int64 t1 = cv::getTickCount();
            CarDetect.mutex_.lock();


            if (colorFrame.data) {

                CarDetect.setFrame(colorFrame,m_fps);
                regon=CarDetect.Draw_Regions();
            }
            CarDetect.mutex_.unlock();

            CarDetect.new_tracker_->Update(regon, CarDetect.uframe, m_fps);

            int64 t2 = cv::getTickCount();

            allTime += t2 - t1;
            int currTime = cvRound(1000 * (t2 - t1) / freq);

            DrawData(colorFrame, framesCounter, currTime);

            if(colorFrame.channels()==3){
                cv::cvtColor(colorFrame, RGBFrame, cv::COLOR_BGR2RGB);
                img = QImage((const unsigned char*)(RGBFrame.data),
                             RGBFrame.cols,RGBFrame.rows,QImage::Format_RGB888);

            } else{
                img = QImage((const unsigned char*)(colorFrame.data),
                             colorFrame.cols,colorFrame.rows,QImage::Format_Indexed8);
            }
            emit send_processed_image(img);

            this->msleep(delay);

        }
        det_Thread.join();
}

void Player::msleep(int ms)
{
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

bool Player::load_video(string filename)
{
    capture = new cv::VideoCapture(filename);
    if(capture->isOpened()){
        frameRate = (int)capture->get(cv::CAP_PROP_FPS);
        LOGxy("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ :", frameRate);

        return true;
    }else{
        return false;
    }
}

void Player::play_video()
{
    if(!isRunning()){
        if(is_stopped() ){
            stop = false;
            emit send_on_video_start();
        }
        start(LowPriority);
    }
}

void Player::pause_video()
{
    emit send_on_video_stop();
    stop = true;
}

void Player::stop_video()
{
    try{
        emit send_on_video_stop();
        stop = true;
        capture->release();
    }catch(const std::exception &ex){
    }
}

bool Player::is_stopped() const
{
    return this->stop;
}

void Player::set_current_frame(int frameNumber)
{

}

double Player::get_frame_rate()
{
    return frameRate;
}

double Player::get_current_frame()
{
    return capture->get(cv::CAP_PROP_POS_FRAMES);
}

double Player::get_number_of_frames()
{
    return capture->get(cv::CAP_PROP_FRAME_COUNT);
}

void Player::add_counter_line(const RoadLine &newLine)
{
    m_lines.push_back(newLine);
}

bool Player::get_counter_line(unsigned int lineUid, RoadLine &line)
{
    for (const auto& rl : m_lines)
    {
        if (rl.m_uid == lineUid)
        {
            line = rl;
            return true;
        }
    }
    return false;
}

bool Player::remove_counter_line(unsigned int lineUid)
{
    for (auto it = std::begin(m_lines); it != std::end(m_lines);)
    {
        if (it->m_uid == lineUid)
            it = m_lines.erase(it);
        else
            ++it;
    }
    return false;
}

bool Player::InitTracker(UMat frame)
{
    bool res = true;

    m_minObjWidth = frame.cols / 50;

    const int minStaticTime = 5;

    config_t config;

#if 1
    switch (m_detectorType)
    {
        case tracking::Detectors::Yolo_Darknet:
            break;

        case tracking::Detectors::DNN_OCV:
#if 1
            config.emplace("dnnTarget", "DNN_TARGET_CPU");
            config.emplace("dnnBackend", "DNN_BACKEND_OPENCV");
#else
            config.emplace("dnnTarget", "DNN_TARGET_CUDA");
        config.emplace("dnnBackend", "DNN_BACKEND_CUDA");
#endif
            break;

        default:
            break;
    }

    config.emplace("modelConfiguration", m_configFile);
    config.emplace("modelBinary", m_weightsFile);
    config.emplace("classNames", m_namesFile);
    config.emplace("confidenceThreshold", "0.5");
    config.emplace("nmsThreshold", "0.4");
    config.emplace("swapRB", "0");
    config.emplace("maxCropRatio", "-1");

    config.emplace("white_list", "person");
    config.emplace("white_list", "car");
    config.emplace("white_list", "bicycle");
    config.emplace("white_list", "motorbike");
    config.emplace("white_list", "bus");
    config.emplace("white_list", "truck");
    //config.emplace("white_list", "traffic light");
    //config.emplace("white_list", "stop sign");

    m_detector = std::unique_ptr<BaseDetector>(CreateDetector(m_detectorType, config, frame));

#else // Background subtraction

    #if 1
    config.emplace("history", std::to_string(cvRound(10 * minStaticTime * m_fps)));
    config.emplace("varThreshold", "16");
    config.emplace("detectShadows", "1");
    m_detector = std::unique_ptr<BaseDetector>(CreateDetector(tracking::Detectors::Motion_MOG2, config, frame));
#else
    config.emplace("minPixelStability", "15");
    config.emplace("maxPixelStability", "900");
    config.emplace("useHistory", "1");
    config.emplace("isParallel", "1");
    m_detector = std::unique_ptr<BaseDetector>(CreateDetector(tracking::Detectors::Motion_CNT, config, m_useLocalTracking, frame));
#endif

#endif

    if (m_detector.get())
        m_detector->SetMinObjectSize(cv::Size(m_minObjWidth, m_minObjWidth));
    else
        res = false;

    if (res)
    {
        TrackerSettings settings;
        settings.SetDistance(tracking::DistJaccard);
        settings.m_kalmanType = tracking::KalmanLinear;
        settings.m_filterGoal = tracking::FilterCenter;
        settings.m_lostTrackType = tracking::TrackCSRT; // Use KCF tracker for collisions resolving
        settings.m_matchType = tracking::MatchHungrian;
        settings.m_dt = 0.3f;                           // Delta time for Kalman filter
        settings.m_accelNoiseMag = 0.2f;                // Accel noise magnitude for Kalman filter
        settings.m_distThres = 0.7f;                    // Distance threshold between region and object on two frames
        settings.m_minAreaRadiusPix = frame.rows / 20.f;
        settings.m_maximumAllowedSkippedFrames = cvRound(2 * m_fps); // Maximum allowed skipped frames

        settings.AddNearTypes("car", "bus", false);
        settings.AddNearTypes("car", "truck", false);
        settings.AddNearTypes("person", "bicycle", true);
        settings.AddNearTypes("person", "motorbike", true);

        settings.m_useAbandonedDetection = false;
        if (settings.m_useAbandonedDetection)
        {
            settings.m_minStaticTime = minStaticTime;
            settings.m_maxStaticTime = 60;
            settings.m_maximumAllowedSkippedFrames = cvRound(settings.m_minStaticTime * m_fps); // Maximum allowed skipped frames
            settings.m_maxTraceLength = 2 * settings.m_maximumAllowedSkippedFrames;        // Maximum trace length
        }
        else
        {
            settings.m_maximumAllowedSkippedFrames = cvRound(10 * m_fps); // Maximum allowed skipped frames
            settings.m_maxTraceLength = cvRound(4 * m_fps);              // Maximum trace length
        }

        m_tracker = std::make_unique<CTracker>(settings);


        std::unique_ptr<CTracker> mtrack= static_cast<unique_ptr<CTracker>>(m_tracker.get());
        CarDetect.Collect_Detector(m_detector, mtrack);

    }

#if 0
    std::vector<cv::Point> framePoints{ cv::Point(420, 348), cv::Point(509, 283), cv::Point(731, 281), cv::Point(840, 343) };
    std::vector<cv::Point2f> geoPoints{ cv::Point2f(45.526646, 5.974535), cv::Point2f(45.527566, 5.973849), cv::Point2f(45.527904, 5.974135), cv::Point2f(45.526867, 5.974826) };
    m_geoParams.SetKeyPoints(framePoints, geoPoints);
#endif

    return res;
}

void Player::DrawData(Mat frame, int framesCounter, int currTime)
{
    //    auto tracks = m_tracker->GetTracks();
            auto tracks = CarDetect.new_tracker_->GetTracks();


            if (m_showLogs)
            {
        //        std::cout << "Frame " << framesCounter << ": tracks = " << tracks.size() << ", time = " << currTime << std::endl;
            }

            if (!m_geoParams.Empty())
            {
                std::vector<cv::Point> points = m_geoParams.GetFramePoints();
                for (size_t i = 0; i < points.size(); ++i)
                {
                    cv::line(frame, points[i % points.size()], points[(i + 1) % points.size()], cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
                }
            }

            for (const auto& track : tracks)
            {
                if (track.m_isStatic)
                {
                    DrawTrack(frame, 1, track, true);
                }
                else
                {
                    if (track.IsRobust(cvRound(m_fps / 4),          // Minimal trajectory size
                                       0.8f,                        // Minimal ratio raw_trajectory_points / trajectory_lenght
                                       cv::Size2f(0.1f, 8.0f))      // Min and max ratio: width / height
                            )
                    {
                        DrawTrack(frame, 1, track, true);
                        std::stringstream label_1;
    //                    label << track.m_type << " " << std::setprecision(2) << track.m_velocity << ": " << track.m_confidence;
                        label_1 << track.m_type<<" Id:"<<track.m_ID;

                        int baseLine = 0;
                        cv::Size labelSize = cv::getTextSize(label_1.str(), cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
                        cv::Rect brect = track.m_rrect.boundingRect();
                        if (brect.x < 0)
                        {
                            brect.width = std::min(brect.width, frame.cols - 1);
                            brect.x = 0;
                        }
                        else if (brect.x + brect.width >= frame.cols)
                        {
                            brect.x = std::max(0, frame.cols - brect.width - 1);
                            brect.width = std::min(brect.width, frame.cols - 1);
                        }
                        if (brect.y - labelSize.height < 0)
                        {
                            brect.height = std::min(brect.height, frame.rows - 1);
                            brect.y = labelSize.height;
                        }
                        else if (brect.y + brect.height >= frame.rows)
                        {
                            brect.y = std::max(0, frame.rows - brect.height - 1);
                            brect.height = std::min(brect.height, frame.rows - 1);
                        }
                        DrawFilledRect(frame, cv::Rect(cv::Point(brect.x, brect.y - labelSize.height), cv::Size(labelSize.width, labelSize.height + baseLine)), cv::Scalar(0, 0, 255), 150);
                        cv::putText(frame, label_1.str(), brect.tl(), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2);

                        CheckLinesIntersection(track, static_cast<float>(frame.cols), static_cast<float>(frame.rows));
                    }
                }
            }
            //m_detector->CalcMotionMap(frame);

            for (const auto& rl : m_lines)
            {
                if(_show_counter_lines){
                    rl.Draw(frame);
                }

            }
}

void Player::DrawTrack(Mat frame, int resizeCoeff, const TrackingObject &track, bool drawTrajectory)
{
    auto ResizeRect = [&](const cv::Rect& r) -> cv::Rect
        {
            return cv::Rect(resizeCoeff * r.x, resizeCoeff * r.y, resizeCoeff * r.width, resizeCoeff * r.height);
        };

        auto ResizePoint = [&](const cv::Point& pt) -> cv::Point
        {
            return cv::Point(resizeCoeff * pt.x, resizeCoeff * pt.y);
        };

        if (track.m_isStatic)
        {
    #if (CV_VERSION_MAJOR >= 4)
            cv::rectangle(frame, ResizeRect(track.m_rrect.boundingRect()), cv::Scalar(255, 0, 255), 2, cv::LINE_AA);
    #else
            cv::rectangle(frame, ResizeRect(track.m_rrect.boundingRect()), cv::Scalar(255, 0, 255), 2, CV_AA);
    #endif
        }
        else
        {
    #if (CV_VERSION_MAJOR >= 4)
            cv::rectangle(frame, ResizeRect(track.m_rrect.boundingRect()), cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
    #else
            cv::rectangle(frame, ResizeRect(track.m_rrect.boundingRect()), cv::Scalar(0, 255, 0), 1, CV_AA);
    #endif

            if (!m_geoParams.Empty())
            {
                int traceSize = static_cast<int>(track.m_trace.size());
                int period = std::min(2 * cvRound(m_fps), traceSize);
                const auto& from = m_geoParams.Pix2Geo(track.m_trace[traceSize - period]);
                const auto& to = m_geoParams.Pix2Geo(track.m_trace[traceSize - 1]);
                auto dist = DistanceInMeters(from, to);

                std::stringstream label;
                if (period >= cvRound(m_fps) / 4)
                {
                    auto velocity = (3.6f * dist * m_fps) / period;
                    //std::cout << track.m_type << ": distance " << std::fixed << std::setw(2) << std::setprecision(2) << dist << " on time " << (period / m_fps) << " with velocity " << velocity << " km/h: " << track.m_confidence << std::endl;
                    if (velocity < 1.f || std::isnan(velocity))
                        velocity = 0;
                    label << track.m_type << " " << std::fixed << std::setw(2) << std::setprecision(2) << velocity << " km/h";

                    int baseLine = 0;
                    double fontScale = 0.5;
                    cv::Size labelSize = cv::getTextSize(label.str(), cv::FONT_HERSHEY_SIMPLEX, fontScale, 1, &baseLine);

                    cv::Rect brect = track.m_rrect.boundingRect();
                    if (brect.x < 0)
                    {
                        brect.width = std::min(brect.width, frame.cols - 1);
                        brect.x = 0;
                    }
                    else if (brect.x + brect.width >= frame.cols)
                    {
                        brect.x = std::max(0, frame.cols - brect.width - 1);
                        brect.width = std::min(brect.width, frame.cols - 1);
                    }
                    if (brect.y - labelSize.height < 0)
                    {
                        brect.height = std::min(brect.height, frame.rows - 1);
                        brect.y = labelSize.height;
                    }
                    else if (brect.y + brect.height >= frame.rows)
                    {
                        brect.y = std::max(0, frame.rows - brect.height - 1);
                        brect.height = std::min(brect.height, frame.rows - 1);
                    }
                    cv::rectangle(frame, cv::Rect(cv::Point(brect.x, brect.y - labelSize.height), cv::Size(labelSize.width, labelSize.height + baseLine)), cv::Scalar(200, 200, 200), cv::FILLED);
                    cv::putText(frame, label.str(), brect.tl(), cv::FONT_HERSHEY_SIMPLEX, fontScale, cv::Scalar(0, 0, 0));

    //				std::cout<<"kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"<<brect<<std::endl;
                }
            }
        }

        if (drawTrajectory)
        {
            cv::Scalar cl = m_colors[track.m_ID % m_colors.size()];

            for (size_t j = 0; j < track.m_trace.size() - 1; ++j)
            {
                const TrajectoryPoint& pt1 = track.m_trace.at(j);
                const TrajectoryPoint& pt2 = track.m_trace.at(j + 1);
    #if (CV_VERSION_MAJOR >= 4)
                cv::line(frame, ResizePoint(pt1.m_prediction), ResizePoint(pt2.m_prediction), cl, 1, cv::LINE_AA);
    #else
                cv::line(frame, ResizePoint(pt1.m_prediction), ResizePoint(pt2.m_prediction), cl, 1, CV_AA);
    #endif
                if (!pt2.m_hasRaw)
                {
    #if (CV_VERSION_MAJOR >= 4)
                    cv::circle(frame, ResizePoint(pt2.m_prediction), 4, cl, 1, cv::LINE_AA);
    #else
                    cv::circle(frame, ResizePoint(pt2.m_prediction), 4, cl, 1, CV_AA);
    #endif
                }
            }
        }
}

void Player::CheckLinesIntersection(const TrackingObject &track, float xMax, float yMax)
{
    auto Pti2f = [&](cv::Point pt) -> cv::Point2f
    {
//        std::cout<<track.m_type<<std::endl;
        return cv::Point2f(pt.x / xMax, pt.y / yMax);
    };

    constexpr size_t minTrack = 5;
    if (track.m_trace.size() >= minTrack)
    {
        for (auto& rl : m_lines)
        {
            if (m_lastIntersections.find(track.m_ID) == m_lastIntersections.end())
            {
                if (rl.IsIntersect(Pti2f(track.m_trace[track.m_trace.size() - minTrack]), Pti2f(track.m_trace[track.m_trace.size() - 1]))){
                    m_lastIntersections.emplace(track.m_ID);
//                    std::cout<<"LINE ID :"<< rl.m_uid<<"CLASS :"<< track.m_type<<"TRACK ID :"<< track.m_ID<<std::endl;
//                    emit send_line_data(rl.m_uid, track.m_type, track.m_ID);
                    int line_id = (int)rl.m_uid;
                    QString classified = QString::fromStdString(track.m_type);
                    emit send_count_data(line_id, track.m_ID, classified);
//                    std::cout<<"COUNTED ON:"<<rl.m_uid<<"OUTPUT: "<<track.m_type<<track.m_ID<<std::endl;
                    //MODIFY ME

                }
            }
        }
    }
}

void Player::DrawFilledRect(Mat &frame, const Rect &rect, Scalar cl, int alpha)
{
    if (alpha)
    {
        const int alpha_1 = 255 - alpha;
        const int nchans = frame.channels();
        int color[3] = { cv::saturate_cast<int>(cl[0]), cv::saturate_cast<int>(cl[1]), cv::saturate_cast<int>(cl[2]) };
        for (int y = rect.y; y < rect.y + rect.height; ++y)
        {
            uchar* ptr = frame.ptr(y) + nchans * rect.x;
            for (int x = rect.x; x < rect.x + rect.width; ++x)
            {
                for (int i = 0; i < nchans; ++i)
                {
                    ptr[i] = cv::saturate_cast<uchar>((alpha_1 * ptr[i] + alpha * color[i]) / 255);
                }
                ptr += nchans;
            }
        }
    }
    else
    {
        cv::rectangle(frame, rect, cl, cv::FILLED);
    }
}

void Player::update_data() {
    LOGx("data updated");
// update count_data
}
