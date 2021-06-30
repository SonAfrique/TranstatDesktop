#ifndef CVUTILITIES_H
#define CVUTILITIES_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <assert.h>
#include <iostream>

namespace cvUtils {

cv::Mat visualizeHistogram(cv::Mat histogram);
cv::Rect nonZeroBoundingBox(cv::Mat input);
cv::Mat overlayColor(cv::Mat input, cv::Mat mask, float r, float g, float b);
float round(float d);
bool inImage(cv::Point point, cv::Size imageSize);
bool inRanges(float value, std::vector<cv::Range> ranges);
void saveOverlay(const char* filename, cv::Mat img1, cv::Mat img2, float blending = 0.5);

void hueAdd(cv::Mat image, int value, cv::Mat mask, int upperBound = 180);
void warpPerspective(const cv::Mat& src, cv::Mat& dst, const cv::Mat& M0, cv::Size dsize, int flags = cv::INTER_LINEAR, int borderType = cv::BORDER_CONSTANT, const cv::Scalar& borderValue = cv::Scalar(), cv::Point origin = cv::Point(0,0));
cv::Mat resizeCanvas(cv::Mat input, cv::Scalar fill, int left = 0, int right = 0, int up = 0, int down = 0);
cv::Mat resizeCanvas(cv::Mat input, cv::Scalar fill, int* parameters);
cv::Mat autoCrop(cv::Mat input, int *parameters = NULL);
cv::Mat blendMask(cv::Mat foreground, cv::Mat background, cv::Mat mask);
cv::Mat blendMask(cv::Scalar foreground, cv::Mat background, cv::Mat mask);
cv::Mat colorOverlay(cv::Scalar color, float alpha, cv::Mat image, cv::Mat mask);
bool pointYCompare(cv::Point& a, cv::Point& b);
bool pointXCompare(cv::Point& a, cv::Point& b);
std::vector<cv::Scalar> distinctColors(int amount, int startHue = 240, float saturation = 1, float luminance = 0.5);
std::string matInfo(cv::Mat mat, int typeTest = -1, int depthTest = -1);
void drawArrow(cv::Mat &img, cv::Point p, cv::Point q, cv::Scalar color, int arrowMag, int thickness = 1, int lineType = 8, int shift = 0);

}

#endif // CVUTILITIES_H

