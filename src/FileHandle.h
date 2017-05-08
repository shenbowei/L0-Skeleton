#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "SkeletonPoint.h"
using namespace std;

class FileHandle
{
public:
	FileHandle();
	FileHandle(string fileName);
	~FileHandle(void);

	void setFileName(string fileName);
	string getFileName();

	vector<SkeletonPoint> readSkeletonPointFromFile();
	void writeSkeletonToFile(string filename, vector<SkeletonPoint> skeleton);
	void writeSkeletonMapToFile( map<int,vector<SkeletonPoint> > skeletonMap);
	inline SkeletonPoint getMidPoint(){ return mid_point; }

	void printInfo();

	//bool compareSkeletonPoint(const SkeletonPoint& sp1, const SkeletonPoint& sp2);

private:
	string file_name;
	vector<SkeletonPoint> skeleton_points;
	SkeletonPoint mid_point;
};

