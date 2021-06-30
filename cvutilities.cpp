#include "cvutilities.h"

using namespace cv;
using namespace std;

namespace cvUtils {

Mat visualizeHistogram(Mat histogram) {
    Mat histImg = Mat::zeros(histogram.rows*10, 10, CV_8UC3);
    double maxVal=0;
    minMaxLoc(histogram, 0, &maxVal, 0, 0);
    for( int h = 0; h < 120; h++ ) {
        float binVal = histogram.at<float>(h, 1);
        int intensity = cvRound(binVal*255/maxVal);
        rectangle(histImg, cv::Point(0, h*10), cv::Point(10, h*10+10), cv::Scalar::all(intensity), LINE_8);
    }
    return histImg;
}

cv::Rect nonZeroBoundingBox(Mat input)
{
    cv::Rect box;
    Mat column, row;

    // Project the image to a single row and a single column.
    cv::reduce(input, column, 1, 2); // Using CV_REDUCE_MAX
    cv::reduce(input, row, 0, 2); // Using CV_REDUCE_MAX

    // Find the first used row:
    for(int i = 0; i < column.rows; i++) {
        if(column.at<uchar>(i, 0) != 0) {
            box.y = i;
            break;
        }
    }

    // Find the last used row and calculate the height:
    for(int i = column.rows-1; i >= 0; i--) {
        if(column.at<uchar>(i, 0) != 0) {
            box.height = i-box.y;
            break;
        }
    }

    // Find the first used column:
    for(int i = 0; i < row.cols; i++) {
        if(row.at<uchar>(0, i) != 0) {
            box.x = i;
            break;
        }
    }

    // Find the last used column and calculate width:
    for(int i = row.cols-1; i >= 0; i--) {
        if(row.at<uchar>(0, i) != 0) {
            box.width = i-box.x;
            break;
        }
    }

    return box;
}

float round(float d)
{
    return d < 0.0 ? ceil(d - 0.5) : floor(d + 0.5); // Handles both positive and negative numbers correctly.
}

bool inImage(cv::Point point, cv::Size imageSize)
{
	return point.x >= 0 && point.x < imageSize.width && point.y >=0 && point.y < imageSize.height;
}

bool inRanges(float value, std::vector<cv::Range> ranges)
{
	for(unsigned int i = 0; i < ranges.size(); i++) {
		if((ranges[i].start <= ranges[i].end && (value >= ranges[i].start && value < ranges[i].end)) || (ranges[i].start > ranges[i].end && (value >= ranges[i].start || value < ranges[i].end)) ) {
			//printf("%f in range.\n", value);
			return true;
		}
	}
	//printf("%f not in any accepted range.\n", value);
	return false;
}

void saveOverlay(const char* filename, Mat img1, Mat img2, float blending)
{
	Mat temp(img1.size(), CV_8UC1);

	cv::MatIterator_<uchar>tempIt = temp.begin<uchar>();
	cv::MatIterator_<uchar>img1It = img1.begin<uchar>();
	cv::MatIterator_<uchar>img2It = img2.begin<uchar>();
	for(; tempIt != temp.end<uchar>(); ++tempIt, ++img1It, ++img2It) {
		*tempIt = *img1It*(1-blending)+*img2It*blending;
	}
	cv::imwrite(filename, temp);
}


/**
 * Add a number to all matrix elements, with wrap-around.
 *
 * Negative numbers can be added. Works only with CV_8UC1 matrices.
 */
void hueAdd(Mat image, int value, Mat mask, int upperBound) {
	assert(image.type() == CV_8UC1);
	assert(mask.type() == CV_8UC1);

	for(int i = 0; i < image.rows; i++) {
		for(int j = 0; j < image.cols; j++) {
			if(mask.at<uchar>(i,j) == 0) {
				continue;
			}

			int result = (int)image.at<uchar>(i, j) + value; // Typecasting to make sure negative results can be saved.

			if(result > upperBound) {
				image.at<uchar>(i, j) = result-upperBound;
			} else if(result < 0) {
				image.at<uchar>(i, j) = upperBound+result;
			} else {
				image.at<uchar>(i, j) = result;
			}

		}
	}
}

void warpPerspective( const Mat& src, Mat& dst, const Mat& M0, cv::Size dsize, int flags, int borderType, const cv::Scalar& borderValue, cv::Point origin)
{
	dst.create(dsize, src.type());

	const int BLOCK_SZ = 32; // Block-size.
	short XY[BLOCK_SZ*BLOCK_SZ*2], A[BLOCK_SZ*BLOCK_SZ];
	double M[9];
	Mat _M(3, 3, CV_64F, M);
	int interpolation = flags & cv::INTER_MAX;
	if(interpolation == cv::INTER_AREA) {
		interpolation = cv::INTER_LINEAR;
	}

	CV_Assert((M0.type() == CV_32F || M0.type() == CV_64F) && M0.rows == 3 && M0.cols == 3);
	M0.convertTo(_M, _M.type());

	if(!(flags & cv::WARP_INVERSE_MAP)) {
		invert(_M, _M);
	}

	int x, xDest, y, yDest, x1, y1, width = dst.cols, height = dst.rows;

	// Calculate the sizes of the blocks the image will be split into (bh is block height, bw is block width):
	int bh0 = std::min(BLOCK_SZ/2, height);
	int bw0 = std::min(BLOCK_SZ*BLOCK_SZ/bh0, width);
	bh0 = std::min(BLOCK_SZ*BLOCK_SZ/bw0, height);

	// Loop through the blocks:
	for(y = -origin.y, yDest = 0; y < height; y += bh0, yDest += bh0) {
		for(x = -origin.x, xDest = 0; x < width; x += bw0, xDest += bw0) {

			// Find the size of the current block - either the normal size, or smaller, if the block lies near the edge of the image:
			int bw = std::min(bw0, width - xDest);
			int bh = std::min(bh0, height - yDest);

			// Avoid dimension errors:
			if (bw <= 0 || bh <= 0) {
				break;
			}

			Mat _XY(bh, bw, CV_16SC2, XY); // The map for use in remap.
			Mat dpart(dst, cv::Rect(xDest, yDest, bw, bh)); // The destination ROI for this block.

			// Loop through each row of the current block (and subsequently each pixel to calculate the map):
			for(y1 = 0; y1 < bh; y1++) {
				short* xy = XY + y1*bw*2; // Pointer to the first slot in the current row of the map.

				// Calculate the transformation (a simple matrix-vector product):
				double X0 = M[0]*x + M[1]*(y + y1) + M[2];
				double Y0 = M[3]*x + M[4]*(y + y1) + M[5];
				double W0 = M[6]*x + M[7]*(y + y1) + M[8];

				if(interpolation == cv::INTER_NEAREST) {
					// Loop through each column in the current block-row:
					for(x1 = 0; x1 < bw; x1++)
					{
						double W = W0 + M[6]*x1;
						W = W ? 1./W : 0;
						int X = cv::saturate_cast<int>((X0 + M[0]*x1)*W);
						int Y = cv::saturate_cast<int>((Y0 + M[3]*x1)*W);
						xy[x1*2] = (short)X;
						xy[x1*2+1] = (short)Y;
					}
				} else {
					short* alpha = A + y1*bw;
					// Loop through each column in the current block-row:
					for(x1 = 0; x1 < bw; x1++) {
						double W = W0 + M[6]*x1;
						W = W ? cv::INTER_TAB_SIZE/W : 0;
						int X = cv::saturate_cast<int>((X0 + M[0]*x1)*W);
						int Y = cv::saturate_cast<int>((Y0 + M[3]*x1)*W);
						xy[x1*2] = (short)(X >> cv::INTER_BITS) + origin.x;
						xy[x1*2+1] = (short)(Y >> cv::INTER_BITS) + origin.y;
						alpha[x1] = (short)((Y & (cv::INTER_TAB_SIZE-1))*cv::INTER_TAB_SIZE + (X & (cv::INTER_TAB_SIZE-1)));
					}
				}
			}

			// Remap using the calculated maps:
			if(interpolation == cv::INTER_NEAREST) {
				remap(src, dpart, _XY, Mat(), interpolation, borderType, borderValue);
			} else {
				Mat _A(bh, bw, CV_16U, A);
				remap(src, dpart, _XY, _A, interpolation, borderType, borderValue);
			}
		}
	}
}

Mat resizeCanvas(Mat input, cv::Scalar fill, int left, int right, int up, int down)
{
	assert(input.rows+up+down > 0 && input.cols+right+left > 0);

	Mat newCanvas(input.rows+up+down, input.cols+left+right, input.type(), fill);

	int leftOffset = std::max(0, left);
	int rightOffset = std::min(0, right);
	int upOffset = std::max(0, up);
	int downOffset = std::min(0, down);
	int inputLeftOffset = (int)std::abs(std::min(0, left));
	int inputUpOffset = (int)std::abs(std::min(0, up));

	int roiWidth = std::min(newCanvas.cols, input.cols+rightOffset);
	int roiHeight = std::min(newCanvas.rows, input.rows+downOffset);

	//std::cout << "canvasROI: " << leftOffset << " " << upOffset << " " << roiWidth << " " << roiHeight << " (img size: " << newCanvas.cols << "x" << newCanvas.rows << ")" << std::endl;
	Mat canvasROI = newCanvas(cv::Rect(leftOffset, upOffset, roiWidth, roiHeight));

	//std::cout << "inputROI: " << inputLeftOffset << " " << inputUpOffset << " " << roiWidth << " " << roiHeight << " (img size: " << newCanvas.cols << "x" << newCanvas.rows << ")" << std::endl;
	Mat inputROI = input(cv::Rect(inputLeftOffset, inputUpOffset, roiWidth, roiHeight));

	inputROI.copyTo(canvasROI);
	return newCanvas;
}

Mat resizeCanvas(Mat input, cv::Scalar fill, int* parameters)
{
	return resizeCanvas(input, fill, parameters[0], parameters[1], parameters[2], parameters[3]);
}

Mat autoCrop(Mat input, int* parameters)
{
	assert(input.depth() == CV_8U);
	assert(input.channels() == 3 || input.channels() == 1);

	int minX = input.cols, minY = input.rows, maxX = 0, maxY = 0;

	if(input.channels() == 3) {
		cv::Vec3b baseColor = input.at<cv::Vec3b>(0,0);
		for(int y = 0; y < input.rows; y++) {
			for(int x = 0; x < input.cols; x++) {
				if(input.at<cv::Vec3b>(y,x)[0] != baseColor[0] || input.at<cv::Vec3b>(y,x)[1] != baseColor[1] || input.at<cv::Vec3b>(y,x)[2] != baseColor[2]) {
					minX = x < minX ? x : minX;
					minY = y < minY ? y : minY;
					maxX = x > maxX ? x : maxX;
					maxY = y > maxY ? y : maxY;
				}
			}
		}
	} else {
		uchar baseColor = input.at<uchar>(0,0);
		for(int y = 0; y < input.rows; y++) {
			for(int x = 0; x < input.cols; x++) {
				if(input.at<uchar>(y,x) != baseColor) {
					minX = x < minX ? x : minX;
					minY = y < minY ? y : minY;
					maxX = x > maxX ? x : maxX;
					maxY = y > maxY ? y : maxY;
				}
			}
		}
	}

	if(parameters != NULL) {
		parameters[0] = -minX;
		parameters[1] = maxX-input.cols;
		parameters[2] = -minY;
		parameters[3] = maxY-input.rows;
	}

	return resizeCanvas(input, cv::Scalar(0), -minX, maxX-input.cols, -minY, maxY-input.rows);
}

Mat blendMask(Mat foreground, Mat background, Mat inputMask)
{
	assert(foreground.type() == CV_8UC3 && background.type() == CV_8UC3);
	assert(inputMask.type() == CV_8UC1);
	assert(foreground.cols == background.cols && foreground.rows == background.rows && foreground.rows == inputMask.rows && foreground.cols == inputMask.cols);

	std::vector<Mat> fgChannels, bgChannels;
	Mat mask(foreground.rows, foreground.cols, CV_32F);
	Mat inverseMask(foreground.rows, foreground.cols, CV_32F);
	Mat tempForeground, tempBackground;

    inputMask.convertTo(mask, CV_32F);
    mask = mask/255.0;
    inverseMask = 1-mask;

	foreground.convertTo(tempForeground, CV_32FC3);
	background.convertTo(tempBackground, CV_32FC3);

	split(tempForeground, fgChannels);
	split(tempBackground, bgChannels);
	for(unsigned int i = 0; i < fgChannels.size(); i++) {
		fgChannels[i] = fgChannels[i].mul(mask);
		bgChannels[i] = bgChannels[i].mul(inverseMask);
	}
	merge(fgChannels, tempForeground);
	merge(bgChannels, tempBackground);

	tempForeground.convertTo(tempForeground, CV_8UC3);
	tempBackground.convertTo(tempBackground, CV_8UC3);

    return tempForeground+tempBackground;
}

Mat blendMask(cv::Scalar foreground, Mat background, Mat mask)
{
    Mat fg = Mat(background.size(), CV_8UC3, foreground);
    return blendMask(fg, background, mask);
}

Mat colorOverlay(cv::Scalar color, float alpha, Mat image, Mat mask)
{
    Mat blended, output, overlay;
    Mat colorImg = Mat(image.size(), CV_8UC3, color);
    colorImg.copyTo(overlay, mask);
    addWeighted(overlay, alpha, image, 1-alpha, 0, blended);
    output = image.clone();
    blended.copyTo(output, mask);
    return output;
}

Mat overlayColor(Mat input, Mat mask, float r, float g, float b)
{
    std::vector<Mat> channels;
    Mat output;
    float blending[3] = {b, g, r};

    split(input, channels);
    for(size_t i = 0; i < channels.size(); i++) {
        Mat work;
        addWeighted(channels[i], 1-blending[i], mask, blending[i], 0, work);
        work.copyTo(channels[i], mask); // Copy only the values inside the coutour mask
    }
    merge(channels, output);

    return output;
}

bool pointYCompare(cv::Point& a, cv::Point& b)
{
    return a.y < b.y;
}

bool pointXCompare(cv::Point& a, cv::Point& b)
{
    return a.x < b.x;
}

std::vector<cv::Scalar> distinctColors(int amount, int startHue, float saturation, float luminance)
{
    if(amount == 0) {
        return std::vector<cv::Scalar>();
    }

    assert(startHue >= 0 && startHue < 360 && saturation >= 0 && saturation <= 1 && luminance >= 0 && luminance <= 1);

    int step = 360/amount;
    int h = startHue;
    float s = saturation;
    float l = luminance;
    float c = (1-fabs(2*l-1))*s;
    float m = l-0.5*c;

    std::vector<cv::Scalar> colors;
    for(int i = 0; i < amount; i++) {
        float hMark = h/60.0;
        float x = c*(1-fabs(fmod(hMark,2) - 1));
        float r1, g1, b1;
        if(hMark >= 0 && hMark < 1) {
            r1 = c;
            g1 = x;
            b1 = 0;
        } else if(hMark >= 1 && hMark < 2) {
            r1 = x;
            g1 = c;
            b1 = 0;
        } else if(hMark >= 2 && hMark < 3) {
            r1 = 0;
            g1 = c;
            b1 = x;
        } else if(hMark >= 3 && hMark < 4) {
            r1 = 0;
            g1 = x;
            b1 = c;
        } else if(hMark >= 4 && hMark < 5) {
            r1 = x;
            g1 = 0;
            b1 = c;
        } else {// if(hMark >= 5 && hMark < 6) { // Be sure to catch the rest.
            r1 = c;
            g1 = 0;
            b1 = x;
        }

        colors.push_back(cv::Scalar((int)cvUtils::round((b1+m)*255), (int)cvUtils::round((g1+m)*255), (int)cvUtils::round((r1+m)*255)));
        h += step;
        if(h > 359) {
            h = h-360;
        }
    }
    return colors;
}

std::string matInfo(cv::Mat mat, int typeTest, int depthTest)
{
    std::stringstream info;
    info << "Cols: " << mat.cols << " | Rows: " << mat.rows << " | Type: " << mat.type();
    if(typeTest != -1) {
        if(mat.type() == typeTest) {
            info << " (same as test)";
        } else {
            info << " (different from test)";
        }
    }
    info << " | Depth: " << mat.depth();
    if(depthTest != -1) {
        if(mat.depth() == depthTest) {
            info << " (same as test)";
        } else {
            info << " (different from test)";
        }
    }
    info << " | Channels: " << mat.channels();

    return info.str().c_str();
}

void drawArrow(Mat &img, Point p, Point q, Scalar color, int arrowMag, int thickness, int lineType, int shift)
{
    // Draw the main line
    line(img, p, q, color, thickness, lineType, shift);

    // Compute the angle alpha
    double angle = atan2(double(p.y-q.y),double(p.x-q.x));

    // Compute the coordinates of the first segment
    p.x = int(q.x + arrowMag * cos(angle+M_PI/4));
    p.y = int(q.y + arrowMag * sin(angle+M_PI/4));

    // Draw the first segment
    line(img, p, q, color, thickness, lineType, shift);

    // Compute the coordinates of the second segment
    p.x = int(q.x + arrowMag * cos(angle-M_PI/4));
    p.y = int(q.y + arrowMag * sin(angle-M_PI/4));

    // Draw the second element
    line(img, p, q, color, thickness, lineType, shift);
}

}

