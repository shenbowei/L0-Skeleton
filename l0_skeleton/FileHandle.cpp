#include "FileHandle.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

FileHandle::FileHandle()
{
	skeleton_points.clear();
	mid_point = SkeletonPoint(0,0,0);
}

FileHandle::FileHandle(string fileName)
	:file_name(fileName)
{
	skeleton_points.clear();
	mid_point = SkeletonPoint(0,0,0);
}


FileHandle::~FileHandle(void)
{
}

void FileHandle::setFileName(string fileName)
{
	this->file_name = fileName;
}

string FileHandle::getFileName()
{
	return this->file_name;
}

bool compareSkeletonPoint(const SkeletonPoint& sp1, const SkeletonPoint& sp2)
{
	return sp1 < sp2;
}

vector<SkeletonPoint> FileHandle::readSkeletonPointFromFile()
{
	skeleton_points.clear();
	ifstream infile(file_name, fstream::in);
	if (!infile.is_open())  
	{ 
		cout<<"Error opening file: infile"<<endl; 
		throw(-1);
		//return skeleton_points; 
	}  

	double x_total=0.0;
	double y_total=0.0;
	double z_total=0.0;
	while (!infile.eof() )  
	{  
		string oneLine; 
		getline(infile,oneLine);

		if(oneLine.empty())
		{
			cout<<"empty line！！！"<<endl;
			continue;
		}

		string xaxis = "";
		string yaxis = "";
		string zaxis = "";
		double x=0.0, y=0.0, z=0.0;

		istringstream inStrStream (oneLine);
		inStrStream>>xaxis;
		inStrStream>>yaxis;
		inStrStream>>zaxis;

		x = atof(xaxis.c_str());
		y = atof(yaxis.c_str());
		z = atof(zaxis.c_str());

		x_total+=x;
		y_total+=y;
		z_total+=z;

		skeleton_points.push_back(SkeletonPoint(x,y,z));
	} 
	infile.close();

	int total_num = skeleton_points.size();
	mid_point.setPoint(x_total/(double)total_num,y_total/(double)total_num,z_total/(double)total_num);

	//对skeleton_points排序,下边两行等效
	//sort(skeleton_points.begin(),skeleton_points.end(),compareSkeletonPoint);
	//sort(skeleton_points.begin(),skeleton_points.end());
	return skeleton_points;
}

void FileHandle::writeSkeletonToFile(string filename, vector<SkeletonPoint> skeleton)
{
	ofstream outFile(filename,fstream::out);
	if (!outFile.is_open())
	{
		cout<<"Error opening file: outfile"<<endl; 
		throw(-2);
	}

	vector<SkeletonPoint>::iterator iter;
	for (iter = skeleton.begin(); iter != skeleton.end(); ++iter)
	{
		outFile<<(*iter).getX()<<" "<<(*iter).getY()<<" "<<(*iter).getZ()<<endl;
	}

	outFile.close();
}

void FileHandle::writeSkeletonMapToFile(map<int,vector<SkeletonPoint> > skeletonMap)
{
	map<int,vector<SkeletonPoint> >::iterator iter;
	for (iter = skeletonMap.begin(); iter != skeletonMap.end(); ++iter)
	{
		int key = iter->first;
		vector<SkeletonPoint> skeleton = iter->second;
		/*
		char* skey="";
		sprintf(skey,"%05d",key);
		string fileName = "../files/skeleton_point_"+string(skey)+"_regist.txt";
		*/

		stringstream fileName;
		fileName<<"../files/skeleton_point_"<<setfill('0') <<setw(5)<<key<<"_regist.txt";

		cout<<fileName.str()<<endl;
		writeSkeletonToFile(fileName.str(),skeleton);
	}
}

void FileHandle::printInfo()
{
	cout<<"----------------file:"<<file_name<<"  info---------------------";
	cout<<"mid_point:"<<endl;
	cout<<"x="<<mid_point.getX()<<endl;
	cout<<"y="<<mid_point.getY()<<endl;
	cout<<"z="<<mid_point.getZ()<<endl<<endl;

	cout<<"all skeleton points:"<<skeleton_points.size()<<endl;
	vector<SkeletonPoint>::iterator iter;
	for (iter = skeleton_points.begin(); iter != skeleton_points.end(); ++iter)
	{
		cout<<(*iter).getX()<<" "<<(*iter).getY()<<" "<<(*iter).getZ()<<endl;
	}
}
