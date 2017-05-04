#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "SkeletonPoint.h"

using namespace std;

class SkletonOptimizeViaL0
{
public:
	SkletonOptimizeViaL0(void);
	~SkletonOptimizeViaL0(void);

	static vector<SkeletonPoint> optimizeViaL0(vector<SkeletonPoint> skeleton, int frameInterval);
	static vector<SkeletonPoint> optimizeViaL0_with_Gaussian(vector<SkeletonPoint> skeleton, int frameInterval);
};

