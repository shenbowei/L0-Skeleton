#include "GlobalFunction.h"


GlobalFunction::GlobalFunction(void)
{
}


GlobalFunction::~GlobalFunction(void)
{
}

bool GlobalFunction::compareSkeletonPoint_X_Less(const SkeletonPoint& sp1, const SkeletonPoint& sp2)
{
	if (sp1.getX() == sp2.getX())
	{
		if (sp1.getY() == sp2.getY() )
		{
			return sp1.getZ() < sp2.getZ();
		}
		return sp1.getY() < sp2.getY();
	}
	return sp1.getX() < sp2.getX();
}

bool GlobalFunction::compareSkeletonPoint_X_Greater(const SkeletonPoint& sp1, const SkeletonPoint& sp2)
{
	if (sp1.getX() == sp2.getX())
	{
		if (sp1.getY() == sp2.getY() )
		{
			return sp1.getZ() > sp2.getZ();
		}
		return sp1.getY() > sp2.getY();
	}
	return sp1.getX() > sp2.getX();
}

bool GlobalFunction::compareSkeletonPoint_Y_Less(const SkeletonPoint& sp1, const SkeletonPoint& sp2)
{
	if (sp1.getY() == sp2.getY())
	{
		if (sp1.getX() == sp2.getX() )
		{
			return sp1.getZ() < sp2.getZ();
		}
		return sp1.getX() < sp2.getX();
	}
	return sp1.getY() < sp2.getY();
}

bool GlobalFunction::compareSkeletonPoint_Y_Greater(const SkeletonPoint& sp1, const SkeletonPoint& sp2)
{
	if (sp1.getY() == sp2.getY())
	{
		if (sp1.getX() == sp2.getX() )
		{
			return sp1.getZ() > sp2.getZ();
		}
		return sp1.getX() > sp2.getX();
	}
	return sp1.getY() > sp2.getY();
}

bool GlobalFunction::compareSkeletonPoint_Z_Less(const SkeletonPoint& sp1, const SkeletonPoint& sp2)
{
	if (sp1.getZ() == sp2.getZ())
	{
		if (sp1.getX() == sp2.getX() )
		{
			return sp1.getY() < sp2.getY();
		}
		return sp1.getX() < sp2.getX();
	}
	return sp1.getZ() < sp2.getZ();
}

bool GlobalFunction::compareSkeletonPoint_Z_Greater(const SkeletonPoint& sp1, const SkeletonPoint& sp2)
{
	if (sp1.getZ() == sp2.getZ())
	{
		if (sp1.getX() == sp2.getX() )
		{
			return sp1.getY() > sp2.getY();
		}
		return sp1.getX() > sp2.getX();
	}
	return sp1.getZ() > sp2.getZ();
}

map<int,vector<SkeletonPoint> > GlobalFunction::SkeletonRegistor(map<int,vector<SkeletonPoint> > skeletonMap,map<int,SkeletonPoint> midPointMap)
{

	map<int,vector<SkeletonPoint> > skeleton_registor;

	map<int,vector<SkeletonPoint> >::iterator iter;

	for (iter = skeletonMap.begin(); iter != skeletonMap.end(); ++iter)
	{
		int key = iter->first;
		SkeletonPoint midPoint = midPointMap[key];
		vector<SkeletonPoint> skeleton = iter->second;

		vector<SkeletonPoint>::iterator iter_v;
		for (iter_v = skeleton.begin(); iter_v != skeleton.end(); ++iter_v)
		{
			SkeletonPoint sp_reg = *iter_v - midPoint;
			skeleton_registor[key].push_back(sp_reg);
		}
	}

	return skeleton_registor;
}

osg::Node* GlobalFunction::createSkeletonNode(vector<SkeletonPoint> sk_v, osg::Vec3 pointSift)
{
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	n->push_back(osg::Vec3(0.0f,0.0f,-1.0f));

	vector<SkeletonPoint>::iterator iter;
	int fpsNum=0;
	int pointNum = 0;

	int totalPointNum = sk_v.size();
	int totalFpsNum = totalPointNum/50+1;
	double rgbInterval = 255.0/totalFpsNum;

	osg::ref_ptr<osg::Group> group = new osg::Group;

	for( iter = sk_v.begin(); iter != sk_v.end(); ++iter )
	{

		v->push_back( osg::Vec3((*iter).getX(),
			(*iter).getY(),
			(*iter).getZ()
			) - pointSift);
		//c->push_back(osg::Vec4(50.0*(double)fpsNum/255.0,1-50.0*(double)fpsNum/255.0,50.0*(double)fpsNum/255.0,1.0f));
		c->push_back(osg::Vec4(rgbInterval*(double)fpsNum/255.0,1.0-rgbInterval*(double)fpsNum/255.0,1.0-rgbInterval*(double)fpsNum/255.0,1.0f));

		if (pointNum%10==9)
		{
			osg::ref_ptr<osg::Geode>	geode = new osg::Geode;
			osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

			geom->setVertexArray( v.get() );
			geom->setColorArray( c.get() );
			geom->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
			geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINE_STRIP, v->size()-10, 10) );
			cout<<"v_size:"<<v->size()<<endl;
			geom->setNormalArray(n.get());
			geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
			/*
			osg::StateSet* set = geom->getOrCreateStateSet();
			osg::Point* p = new osg::Point;
			p->setSize(3.0);
			osg::Sphere* s = new osg::Sphere;
			s->setRadius(20.0);
			set->setAttribute(p);
			//geom->setShape(s);
			*/

			geode->addDrawable(geom.get());
			group->addChild(geode.get());
			

			//v->clear();
			//c->clear();
		}
		
		if (pointNum%50==49)
		{
			fpsNum++;
		}

		++pointNum;

	}

	return  group.release();
}

osg::Node* GlobalFunction::createSkeletonPointSphereNode(vector<SkeletonPoint> sk_v, osg::Vec3 pointSift)
{
	vector<SkeletonPoint>::iterator iter;
	int fpsNum=0;
	int pointNum = 0;

	int totalPointNum = sk_v.size();
	int totalFpsNum = totalPointNum/50+1;
	double rgbInterval = 255.0/totalFpsNum;

	osg::ref_ptr<osg::Group> group = new osg::Group;

	for( iter = sk_v.begin(); iter != sk_v.end(); ++iter )
	{

		osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere(osg::Vec3((*iter).getX(),(*iter).getY(),(*iter).getZ()) - pointSift, 0.008f);
		osg::ref_ptr<osg::ShapeDrawable> shapeDrawable = new osg::ShapeDrawable(sphere.get());
		shapeDrawable->setColor(osg::Vec4(rgbInterval*(double)fpsNum/255.0,1.0-rgbInterval*(double)fpsNum/255.0,1.0-rgbInterval*(double)fpsNum/255.0,1.0f));
		//shapeDrawable->setColor(osg::Vec4(0.0,13.0*(double)fpsNum/255.0,0.0,1.0f));
		
		osg::ref_ptr<osg::Geode>	geode = new osg::Geode;
		geode->addDrawable(shapeDrawable.get());
		group->addChild(geode.get());
			
		if (pointNum%50==49)
		{
			fpsNum++;
		}

		++pointNum;

	}

	return  group.release();
}
