/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#include <cstdio>
#include <cstdlib>
#include <image.h>
#include <misc.h>
#include <pnmfile.h>
#include "segment-image.h"
#include "segment-graph.h"

#include "fh_segmentation/fh_segmentation.h"

image<rgb>* cvTOfh(const cv::Mat& cvImage)
{
	image<rgb> *fhImage = new image<rgb>(cvImage.cols, cvImage.rows);
	for (int i = 0; i < cvImage.rows; i++)
	{
		for (int j = 0; j < cvImage.cols; j++)
		{
			rgb temp;
			cv::Vec3b pixel = cvImage.at<cv::Vec3b>(i,j);
			temp.r = pixel[2];
			temp.g = pixel[1];
			temp.b = pixel[0];

			imRef(fhImage, j, i) = temp;
		}
	}
	return fhImage;
}

cv::Mat fhTOcv(const image<rgb>* fhImage)
{
	cv::Mat cvImage = cv::Mat::zeros(fhImage->height(), fhImage->width(), CV_8UC3);
	for (int v = 0; v < cvImage.rows; v++)
	{
		for (int u = 0; u < cvImage.cols; u++)
		{
			rgb temp = imRef(fhImage, u, v);
			cv::Vec3b pixel;
			pixel[2] = temp.r;
			pixel[1] = temp.g;
			pixel[0] = temp.b;
			cvImage.at<cv::Vec3b>(v,u) = pixel;
		}
	}
	return cvImage;
}

void segment(const cv::Mat& input, cv::Mat& colors, cv::Mat& labels, float sigma, float k, int min_size)
{
	image<rgb>* fhImg = cvTOfh(input);

	printf("processing\n");
	int num_ccs;
	image<rgb> *seg = segment_image(fhImg, sigma, k, min_size, &num_ccs);
	printf("got %d components\n", num_ccs);

	colors = fhTOcv(seg);//.copyTo(colors);
}

/*
int main(int argc, char **argv) {
	if (argc != 6) {
		fprintf(stderr, "usage: %s sigma k min input(ppm) output(ppm)\n", argv[0]);
		return 1;
	}

	float sigma = atof(argv[1]);
	float k = atof(argv[2]);
	int min_size = atoi(argv[3]);
	
	printf("loading input image.\n");
	cv::Mat cvImg = cv::imread(argv[4]);
	cv::Mat segmentedImg;
	cv::Mat labeledImg;
	segment(cvImg, segmentedImg, labeledImg, sigma, k, min_size);
	std::cerr << segmentedImg.cols << " " << segmentedImg.rows << std::endl;
	cv::imwrite(std::string(argv[5]), segmentedImg);

	cv::namedWindow("out", cv::WINDOW_NORMAL);
	cv::imshow("out", segmentedImg);
	cv::waitKey(0);

	printf("done! uff...that's hard work.\n");

	return 0;
}
*/
