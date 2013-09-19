#include <cstdio>
#include <cstdlib>
#include <image.h>
#include <misc.h>
#include <pnmfile.h>
#include "segment-image.h"
#include "segment-graph.h"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

image<rgb>* cvTOfh(const cv::Mat& cvImage);
cv::Mat fhTOcv(const image<rgb>* fhImage);
void segment(const cv::Mat& input, cv::Mat& colors, cv::Mat& labels, float sigma, float k, int min_size = 100);
