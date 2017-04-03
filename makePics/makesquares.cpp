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

string path, base1, base2, base3, ext, type;
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

inline int getColor(int pos, vector<int> adj, int dim, int pixels) {
	int random = double(rand())/(RAND_MAX);
	if(!(pos%dim == 0)) {
		if(!(pos < dim)) {
			if(random < 0.3)
				return adj[pos-1];
			if(random < 0.6)
				return adj[pos-dimen];
			if(random < 0.9)
				return adj[pos-1-dimen];
			return int(pixels*double(rand())/(RAND_MAX));
		}
		if(random < 0.9)
			return adj[pos-1];
		return int(pixels*double(rand())/(RAND_MAX));
	}
	if(!(pos == 0)) {
		if(random < 0.9)
			return adj[pos-dimen];
		return int(pixels*double(rand())/(RAND_MAX));
	}
	return 0;
}

int main() {
	path = "./UNCOMPRESSED/";
	base1 = "test";
	base2 = "circle";
	base3 = "lines";
	ext = ".ppm";
	type = "P3";
	dimen = 1024;
	len = 4;
	color = 255;
	red = chrono::system_clock::now().time_since_epoch().count();
	for(float res = 1; res <= dimen/4; res = res+1) {
		ofstream output1, output2, output3;
		Mat mat = Mat::zeros(dimen, dimen, CV_8UC3);
		output1.open(path+base1+nameFile(res, len)+ext);
		output2.open(path+base2+nameFile(res, len)+ext);
		output3.open(path+base3+nameFile(res, len)+ext);
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
			circle(mat, Point(int(double(rand())/(RAND_MAX)*dimen), int(dimen*double(rand())/(RAND_MAX))), int(res), Scalar(int(color*double(rand())/(RAND_MAX)), int(double(rand())/(RAND_MAX)*color), int(color*double(rand())/(RAND_MAX))), -1, 8, 0);
		}
		green = chrono::system_clock::now().time_since_epoch().count()-1;
		shuffle(tempRed.begin(), tempRed.end(), default_random_engine(red));
		shuffle(tempGreen.begin(), tempGreen.end(), default_random_engine(green));
		blue = chrono::system_clock::now().time_since_epoch().count();
		shuffle(tempBlue.begin(), tempBlue.end(), default_random_engine(blue));
		int count = 0;
		int countLines = 0;
		int reset = 0;
		int resCount = 0;
		int diff = int(dimen)%int(res);
		output1 << type << endl;
		output1 << dimen << " " << dimen << endl;
		output1 << color << endl;
		output2 << type << endl;
		output2 << dimen << " " << dimen << endl;
		output2 << color << endl;
		output3 << type << endl;
		output3 << dimen << " " << dimen << endl;
		output3 << color << endl;
		for(int p = 0; p < dimen*dimen; ++p) {
			output1 << tempRed[count] << " " << tempGreen[count] << " " << tempBlue[count] << " ";
			output2 << int(mat.at<Vec3b>(p/int(dimen), p%int(dimen))[0]) << " " << int(mat.at<Vec3b>(p/int(dimen), p%int(dimen))[1]) << " " << int(mat.at<Vec3b>(p/int(dimen), p%int(dimen))[2]) << " ";
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
			countLines = getColor(p, adjacencies, dimen, pixels);
			adjacencies[p] = countLines;
			output3 << tempRed[countLines] << " " << tempGreen[countLines] << " " << tempBlue[countLines] << " ";
		}
		output1.close();
		output2.close();
	}
	return 0;
}
