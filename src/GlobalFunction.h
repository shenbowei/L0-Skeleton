#pragma once

#include "SkeletonPoint.h"
#include <iostream>
#include <map>
#include <vector>

#include <osg/Node>
#include <osgViewer/Viewer>
#include <osg/StateSet>
#include <osg/TextureRectangle>
#include <osg/Geode>
#include <osgGA/TrackballManipulator>
#include <osg/Point>
#include <osg/ShapeDrawable>

using namespace std;

class GlobalFunction
{
public:
	GlobalFunction(void);
	~GlobalFunction(void);

	static osg::ref_ptr<osg::Node> geode_skleton;
	static osg::ref_ptr<osg::Node> geode_skletonPoint;

	static bool compareSkeletonPoint_X_Less(const SkeletonPoint& sp1, const SkeletonPoint& sp2);
	static bool compareSkeletonPoint_X_Greater(const SkeletonPoint& sp1, const SkeletonPoint& sp2);

	static bool compareSkeletonPoint_Y_Less(const SkeletonPoint& sp1, const SkeletonPoint& sp2);
	static bool compareSkeletonPoint_Y_Greater(const SkeletonPoint& sp1, const SkeletonPoint& sp2);

	static bool compareSkeletonPoint_Z_Less(const SkeletonPoint& sp1, const SkeletonPoint& sp2);
	static bool compareSkeletonPoint_Z_Greater(const SkeletonPoint& sp1, const SkeletonPoint& sp2);

	map<int,vector<SkeletonPoint> > SkeletonRegistor(map<int,vector<SkeletonPoint> > skeletonMap,map<int,SkeletonPoint> midPointMap);

	static osg::Node* createSkeletonNode(vector<SkeletonPoint> sk_v, osg::Vec3 pointSift);
	static osg::Node* createSkeletonPointSphereNode(vector<SkeletonPoint> sk_v, osg::Vec3 pointSift);
};

