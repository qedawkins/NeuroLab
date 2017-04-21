#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

# define M_PI 3.14159265358979323846

string path, base1, ext, type;
float dimen, color;
int len;
unsigned red, green, blue;

inline string nameFile(int n, int len) {
	string result(len--, '0');
	for (int val=(n<0)?-n:n; len>=0&&val!=0; --len,val/=10)
		result[len]='0'+val%10;
	if (len>=0&&n<0) result[0]='-';
	return result;
}

inline int getdegrees(int p, int res, int dimen) {
	if(p%dimen==dimen/2) {
		if(dimen/2-p/dimen >= 0)
			return int(360/(4*float(res)));
		return int(3*360/(4*float(res)));
	}
	if(p/dimen==dimen/2) {
		if(dimen/2-p%dimen >= 0)
			return 0;
		return int(180/res);
	}
	return int(atan(float(dimen/2-p/dimen)/float(dimen/2-p%dimen))*180/(M_PI*float(res)));
}

int main() {
	path = "./UNCOMPRESSED/";
	base4 = "radii";
	ext = ".ppm";
	type = "P3";
	dimen = 1024;
	len = 4;
	color = 255;
	red = chrono::system_clock::now().time_since_epoch().count();
	for(float res = 1; res <= 360; res = res+1) {
		ofstream output4;
		Mat mat = Mat::zeros(dimen, dimen, CV_8UC3);
		output4.open(path+base4+nameFile(res, len)+ext);
		int pixels = ceil(360/res);
		vector<int> tempRed(pixels);
		vector<int> tempGreen(pixels);
		vector<int> tempBlue(pixels);
		red = chrono::system_clock::now().time_since_epoch().count()+1;
		for(int i = 0; i < pixels; ++i) {
			tempRed[i] = i*color/pixels;
			tempGreen[i] = i*color/pixels;
			tempBlue[i] = i*color/pixels;
		}
		green = chrono::system_clock::now().time_since_epoch().count()-1;
		shuffle(tempRed.begin(), tempRed.end(), default_random_engine(red));
		shuffle(tempGreen.begin(), tempGreen.end(), default_random_engine(green));
		blue = chrono::system_clock::now().time_since_epoch().count();
		shuffle(tempBlue.begin(), tempBlue.end(), default_random_engine(blue));
		int count = 0;
		int reset = 0;
		int resCount = 0;
		output4 << type << endl;
		output4 << dimen << " " << dimen << endl;
		output4 << color << endl;
		for(int p = 0; p < dimen*dimen; ++p) {
			count = getdegrees(p, int(res), int(dimen));
			output4 << tempRed[count] << " " << tempGreen[count] << " " << tempBlue[count] << " ";
		}
		output4.close();
	}
	return 0;
}
