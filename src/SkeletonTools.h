#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "SkeletonPoint.h"
using namespace std;

class SkeletonTools
{
private:
	SkeletonTools(void);
public:
	static SkeletonTools* getInstance();
	~SkeletonTools(void);

    map<int, vector<SkeletonPoint> > getAllSkeletonPerFps(string filePath);
	void writeAllSkeletonPerFps(string filePath, string fileMark,map<int, vector<SkeletonPoint> > sk_map);

	map<int, vector<SkeletonPoint> > getSampleSkeletonPerFps(map<int, vector<SkeletonPoint> > skeleton);
	map<int, vector<SkeletonPoint> > getSampleSkeletonPerFps(map<int, vector<SkeletonPoint> > skeleton,string sortMethod[]);
	map<int, vector<SkeletonPoint> > getSampleSkeletonPerFps_asKinect(map<int, vector<SkeletonPoint> > skeleton);

	void sortSkMap(map<int, vector<SkeletonPoint> >& skeleton,string sortMethod[]);
	void printSkMap(map<int, vector<SkeletonPoint> > skeleton);

	SkeletonPoint getMidPoint(SkeletonPoint sp1, SkeletonPoint sp2);
	SkeletonPoint getAveragePoint(vector<SkeletonPoint> sk_v);
	int indexJudge(int index);

	vector<SkeletonPoint> getSkeleonVector(map<int, map<int,vector<SkeletonPoint> > > sk_map);

	map<int, vector<SkeletonPoint> > skeletonAlign(map<int, vector<SkeletonPoint> > sk_source, SkeletonPoint sp);

	map<int,map<int,vector<SkeletonPoint> > > segmentSkletonVector(vector<SkeletonPoint> sk);
	map<int,map<int,vector<SkeletonPoint> > > segmentSkletonVector(vector<SkeletonPoint> sk, int fpsNum, int perSegNum);

private:
	static SkeletonTools *_instance;
};

