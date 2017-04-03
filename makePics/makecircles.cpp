#include <iostream>https://github.com/qedawkins/NeuroLab.git
#include <fstream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

string path, base2, ext, type;
float dimen, color;
int len;https://github.com/qedawkins/NeuroLab.git

inline string nameFile(int n, int len)
{
	string result(len--, '0');
	for (int val=(n<0)?-n:n; len>=0&&val!=0; --len,val/=10)
		result[len]='0'+val%10;
	if (len>=0&&n<0) result[0]='-';
	return result;
}

int main() {
	path = "./UNCOMPRESSED/";
	base2 = "circle";
	ext = ".ppm";
	type = "P3";
	dimen = 1024;
	len = 4;
	color = 255;
	red = chrono::system_clock::now().time_since_epoch().count();
	for(float res = 1; res <= dimen/4; res = res+1) {
		ofstream output2;
		Mat mat = Mat::zeros(dimen, dimen, CV_8UC3);
		output2.open(path+base2+nameFile(res, len)+ext);
		int pixels = ceil(dimen/res)*ceil(dimen/res);
		vector<int> tempRed(pixels);
		vector<int> tempGreen(pixels);
		vector<int> tempBlue(pixels);
		for(int i = 0; i < pixels; ++i) {
			tempRed[i] = i*color/pixels;
			tempGreen[i] = i*color/pixels;
			tempBlue[i] = i*color/pixels;
			circle(mat, Point(int(double(rand())/(RAND_MAX)*dimen), int(dimen*double(rand())/(RAND_MAX))), int(res), Scalar(int(color*double(rand())/(RAND_MAX)), int(double(rand())/(RAND_MAX)*color), int(color*double(rand())/(RAND_MAX))), -1, 8, 0);
		}
		output2 << type << endl;
		output2 << dimen << " " << dimen << endl;
		output2 << color << endl;
		for(int p = 0; p < dimen*dimen; ++p) {
			output2 << int(mat.at<Vec3b>(p/int(dimen), p%int(dimen))[0]) << " " << int(mat.at<Vec3b>(p/int(dimen), p%int(dimen))[1]) << " " << int(mat.at<Vec3b>(p/int(dimen), p%int(dimen))[2]) << " ";
		}
		output2.close();
	}
	return 0;
}
