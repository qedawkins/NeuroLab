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

string path, base1, ext, type;
float dimen, color;
int len;https://github.com/qedawkins/NeuroLab.git
unsigned red, green, blue;

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
	base1 = "square";
	ext = ".ppm";
	type = "P3";
	dimen = 1024;
	len = 4;
	color = 255;
	red = chrono::system_clock::now().time_since_epoch().count();
	for(float res = 1; res <= dimen/4; res = res+1) {
		ofstream output1;
		Mat mat = Mat::zeros(dimen, dimen, CV_8UC3);
		output1.open(path+base1+nameFile(res, len)+ext);
		int pixels = ceil(dimen/res)*ceil(dimen/res);
		vector<int> tempRed(pixels);
		vector<int> tempGreen(pixels);
		vector<int> tempBlue(pixels);
		vector<int> adjacencies(dimen*dimen);
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
		output1 << type << endl;
		output1 << dimen << " " << dimen << endl;
		output1 << color << endl;
		for(int p = 0; p < dimen*dimen; ++p) {
			output1 << tempRed[count] << " " << tempGreen[count] << " " << tempBlue[count] << " ";
			if((p-resCount*diff)%int(res) == int(res)-1 || p%int(dimen) == int(dimen)-1) {
				++count;
				if((p/int(dimen))%int(res)==int(res)-1) {
					reset = count;
				}
			}
			if((p+1)%int(dimen)==0) {
				count = reset;
				++resCount;
			}
		}
		output1.close();
	}
	return 0;
}
