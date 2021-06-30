#ifndef OPENCVVIEWER_H
#define OPENCVVIEWER_H

#include <QtGui>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "cvutilities.h"
//#include "ruba.h"
//#include "viewinfo.h"


/**
 * Widget to display frames or single images from OpenCV using a QGraphicsView.
 *
 * This class integrates OpenCV and Qt. It is a widget that can be added to
 * your GUI and handle display of video and single images.
 *
 * To show an image, simply set it with setImage() and the display will
 * automatically be updated.
 */
class OpenCVViewer : public QGraphicsView
{
    Q_OBJECT

public:
    /**
     * Constructor.
     *
     * Creates a new OpenCVViewer. Be aware that the capture source must be
     * set before any capture can commence. See setSource().
     */
    OpenCVViewer(QWidget *parent);
    ~OpenCVViewer();

    /**
     * Sets a default widget size of 400x300 px.
     *
     * @return the preferred size of the widget.
     */
    QSize sizeHint() const;


    /**
     * Return the current image.
     *
     * This function returns the current image. Note that this is a shallow copy
     * (as per OpenCV's memory management), so any alterations of the returned
     * Mat will reflect in the original Mat being displayed in the OpenGL object.
     *
     * @return a shallow copy of the most recently shown image.
     */
    cv::Mat getImage();


    /**
     * Return the bgr opencv image.
     *
     * This functions return the transformed qt image to opencv image matrix.
     *
     * @return a shallow copy of the transformed qimage.
     */
    cv::Mat qimage2Mat_v1(QImage qimage, cv::Mat mat);
    cv::Mat qimage2Mat_v2(QImage qimage, cv::Mat mat);


    /**
     * Map a point in the widget to the image coordinates.
     *
     * @param the point in the widget coordinate system.
     * @return the point in the image coordinate system.
     */
    cv::Point mapPoint(cv::Point widgetCoords);


//    ViewInfo GetView();
//    void setView(ViewInfo view);


    /** Clears the current image
    *
    */
    void clear();

public slots:
    /**
     * Set image
     *
     * Overwrites the previous display image and updates the display.
     *
     * @param the image to display.
     */
    void setImage(cv::Mat newImage);

protected:
    void resizeEvent(QResizeEvent* event); ///< Used when the widget is resized.
    void mousePressEvent(QMouseEvent* event); ///< Called each time a mouse button is clicked.
    void mouseMoveEvent(QMouseEvent* event); ///< Called when the mouse is moved and mouse tracking is on or a mouse button is down.
    void mouseReleaseEvent(QMouseEvent* event); ///< Called when a mouse button is released.
    void mouseDoubleClickEvent(QMouseEvent* event); ///< Called when the mouse button is double clicked
    void wheelEvent(QWheelEvent* event); ///< Called when the mouse wheel is scrolled.
    void closeEvent(QCloseEvent *event); ///< Called when the widget is closed

    void updateImageSize(); ///<  Updates the scene size and view based on the size of the current image
    

    QGraphicsScene *scene; ///< The scene which shows the picture.
    cv::Mat displayImage; ///< Holds the image to be displayed in the OpenGL-widget.
    QImage qtImg; ///< Holds the transformed opencv mat to qt image.

    cv::Size prevSize; //< The size of the previous frame
//    ViewInfo view; ///< Holds the current modality of the view

signals:
    void mouseClicked(QMouseEvent* event); ///< Emitted each time a mouse button is clicked.
    void mouseDoubleClicked(QMouseEvent* event); ///< Emitted each time a mouse button is double clicked
    void mouseMoved(QMouseEvent* event); ///< Emitted when the mouse is moved and mouse tracking is on or a mouse button is down.
    void mouseReleased(QMouseEvent* event); ///< Emitted when a mouse button is released.
    void wheelScrolled(QWheelEvent* event); ///< Emitted when the mouse wheel is scrolled.
//    void widgetClosing(ViewInfo* view); ///< Emitted when the widget is closing

};

#endif // OPENCVVIEWER_H
