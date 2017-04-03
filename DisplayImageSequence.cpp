#include <fstream>
#include <iostream>
#include <chrono>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

vector<string> get_all_files_names_within_folder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.ppm";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if(hFind != INVALID_HANDLE_VALUE) {
		do {
			if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
				names.push_back(fd.cFileName);
			}
		}while(::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

int main(int argc, char** argv )
{
	ofstream output;
	output.open("./LOGS/timerec.csv");
	auto inittime = chrono::high_resolution_clock::now();
	if ( argc != 2 )
	{
		printf("usage: DisplayImageSequence.out <Directory_Path>\n");
		return -1;
	}

	vector<string> files = get_all_files_names_within_folder(string(argv[1]));
	vector<float> times(files.size(), 0);
	output << "file" << ",";
	for( int i = 0 ; i < files.size(); ++i) {
		output << files[i] << ",";
		Mat input;
		input = imread(string(argv[1]) + "/" + files[i]);
		Size size(1024, 1024);
		Mat image;
		resize(input, image, size);
		
		if ( !image.data )
		{
			printf("No image data \n");
			return -1;
		}
		namedWindow("Display Image", WINDOW_AUTOSIZE );
		imshow("Display Image", image);
		times[i] = float(chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - inittime).count())/float(pow(10, 6));
		waitKey(25);
	}
	output << "\n" << "time" << ",";
	for( int i = 0; i < files.size(); ++i) {
		output << times[i] << ",";
	}
	return 0;
}
