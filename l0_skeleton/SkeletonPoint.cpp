#include "SkeletonPoint.h"


SkeletonPoint::SkeletonPoint(void)
{
}

SkeletonPoint::SkeletonPoint(double x,double y,double z)
	:_x(x),_y(y),_z(z)
{
}

SkeletonPoint::~SkeletonPoint(void)
{
}

void SkeletonPoint::setPoint(double x,double y,double z)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
}


bool SkeletonPoint::operator < ( const SkeletonPoint& sp) const
{
	if (this->_x == sp._x )
	{
		if (this->_y == sp._y)
		{
			return this->_z < sp._z;
		}
		return this->_y < sp._y;
	}
	return this->_x < sp._x;
}

SkeletonPoint SkeletonPoint::operator - (const SkeletonPoint& sp) const
{
	double xx = this->_x - sp._x;
	double yy = this->_y - sp._y;
	double zz = this->_z - sp._z;
	return SkeletonPoint(xx,yy,zz);
}