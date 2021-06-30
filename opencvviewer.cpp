#include "opencvviewer.h"

using namespace cv;

OpenCVViewer::OpenCVViewer(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    this->setScene(scene);
//    this->view = view;

    prevSize.height = -1;
    prevSize.width = -1;
}

OpenCVViewer::~OpenCVViewer()
{
    delete scene;
}

QSize OpenCVViewer::sizeHint() const
{
    return QSize(400, 300);
}

Mat OpenCVViewer::getImage()
{
    return displayImage;
}

void OpenCVViewer::clear()
{
    scene->clear();
}

void OpenCVViewer::setImage(Mat newImage)
{
    if(newImage.empty()) {
        return;
    }

    if(newImage.channels() == 3 || newImage.channels() == 4) {        
        cvtColor(newImage, displayImage, COLOR_BGR2RGB); // Copy and convert the new image.
    } else {
        cvtColor(newImage, displayImage, COLOR_GRAY2RGB); // Copy and convert the new image.
    }

    QImage img((uchar*)displayImage.data, displayImage.cols, displayImage.rows, displayImage.step, QImage::Format_RGB888);
    qtImg = img;

    scene->clear();
    scene->addPixmap(QPixmap::fromImage(img));

    Mat cvMat;
    displayImage = qimage2Mat_v2(qtImg, cvMat);

    if (newImage.size().width != prevSize.width || newImage.size().height != prevSize.height)
    {
        updateImageSize();
        prevSize = newImage.size();
    }
}

Mat OpenCVViewer::qimage2Mat_v1(QImage qimage, cv::Mat mat)
{
    mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC3 );
    for (int i = 0; i < qimage.height(); i++)
    {
        // scanLine returns a ptr to the start of the data for that row
        memcpy(mat.ptr(i), qimage.scanLine(i), qimage.bytesPerLine());
    }
    cv::cvtColor(mat, mat, COLOR_RGB2BGR);
    return mat;
}

Mat OpenCVViewer::qimage2Mat_v2(QImage qimage, cv::Mat mat)
{
///< The way with mixChannels does not work >///
//    cv::Mat tmpMat = cv::Mat(qimage.height(), qimage.width(), CV_8UC3, (uchar*)qimage.bits(), qimage.bytesPerLine());
//    mat = cv::Mat(tmpMat.rows, tmpMat.cols, CV_8UC3);
//    Mat alpha(tmpMat.rows, tmpMat.cols, CV_8UC1);
//    Mat out[] = {mat, alpha};
//    int from_to[] = {0,2,  1,1,  2,0, 3,3};
//    cv::mixChannels(&tmpMat, 1, out, 2, from_to, 4);
  //    return out[0];

///< So we use a more simple way finally >///
    cv::Mat tmpMat = cv::Mat(qimage.height(), qimage.width(), CV_8UC3, (uchar*)qimage.bits(), qimage.bytesPerLine());
    cv::cvtColor(tmpMat, mat, COLOR_RGB2BGR);
    return mat;
}

void OpenCVViewer::updateImageSize()
{
    scene->setSceneRect(QRectF(0, 0, displayImage.cols, displayImage.rows));
    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void OpenCVViewer::resizeEvent(QResizeEvent* event)
{
    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void OpenCVViewer::mousePressEvent(QMouseEvent* event)
{
    emit mouseClicked(event);
}

void OpenCVViewer::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit mouseDoubleClicked(event);
}

void OpenCVViewer::mouseMoveEvent(QMouseEvent* event)
{
    emit mouseMoved(event);
}

void OpenCVViewer::mouseReleaseEvent(QMouseEvent* event)
{
    emit mouseReleased(event);
}

void OpenCVViewer::wheelEvent(QWheelEvent* event)
{
    emit wheelScrolled(event);
}

void OpenCVViewer::closeEvent(QCloseEvent *event) 
{ 
//    emit widgetClosing(&view);

    // Ignore further processing of the close event. The processing of the emitted signal should take of the rest
    event->ignore(); 
}

//ViewInfo OpenCVViewer::GetView()
//{
//    return view;
//}
//
//void OpenCVViewer::setView(ViewInfo view)
//{
//    this->view = view;
//}


cv::Point OpenCVViewer::mapPoint(cv::Point widgetCoords)
{
    if(displayImage.empty()) { // Bail out if we have no image to map to.
        return cv::Point(0,0);
    }

    QPointF mapResult = this->mapToScene(widgetCoords.x, widgetCoords.y);
    return cv::Point((int)cvUtils::round(mapResult.x()), (int)cvUtils::round(mapResult.y()));
    /*cv::Point mappedPoint;

    float viewportRatio = (float)this->width()/(float)this->height();
    float imageRatio = (float)displayImage.cols/(float)displayImage.rows;

    mappedPoint.x = (int)((float)widgetCoords.x/(float)this->width()*(float)displayImage.cols);
    mappedPoint.y = (int)((float)widgetCoords.y/(float)this->height()*(float)displayImage.rows);
    if(viewportRatio > imageRatio) { // The viewport has black bars on the sides.
        int imageWidth = displayImage.cols*(float)this->height()/(float)displayImage.rows;
        int offset = (this->width()-imageWidth)/2;
        mappedPoint.x = displayImage.cols*((float)(widgetCoords.x-offset)/(float)imageWidth);
    } else if(viewportRatio < imageRatio) { // The viewport has black bars on top and bottom.
        int imageHeight = displayImage.rows*(float)this->width()/(float)displayImage.cols;
        int offset = (this->height()-imageHeight)/2;
        mappedPoint.y = displayImage.rows*((float)(widgetCoords.y-offset)/(float)imageHeight);
    }

    return mappedPoint;*/
}
