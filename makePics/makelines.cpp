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
	base3 = "lines";
	ext = ".ppm";
	type = "P3";
	dimen = 1024;
	len = 4;
	color = 255;
	for(float res = 1; res <= dimen/4; res = res+1) {
		ofstream output3;
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
		output3 << type << endl;
		output3 << dimen << " " << dimen << endl;
		output3 << color << endl;
		for(int p = 0; p < dimen*dimen; ++p) {
			countLines = getColor(p, adjacencies, dimen, pixels);
			adjacencies[p] = countLines;
			output3 << tempRed[countLines] << " " << tempGreen[countLines] << " " << tempBlue[countLines] << " ";
		}
		output3.close();
	}
	return 0;
}
