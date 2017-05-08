#pragma once
class SkeletonPoint
{
public:
	SkeletonPoint(void);
	SkeletonPoint(double x,double y,double z);
	~SkeletonPoint(void);

	bool operator<(const SkeletonPoint& sp) const;
	SkeletonPoint operator-(const SkeletonPoint& sp) const;

	void setPoint(double x,double y,double z);

	//加const之后就可以以下述参数形式调用：
	//const SkeletonPoint &sp......sp.get()
	inline double getX() const { return _x; } 
	inline double getY() const { return _y; }
	inline double getZ() const { return _z; }

private:
	double _x;
	double _y;
	double _z;
};

