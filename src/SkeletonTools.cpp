#include "SkeletonTools.h"
#include "FileHandle.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "GlobalFunction.h"

SkeletonTools* SkeletonTools::_instance = NULL;


SkeletonTools::SkeletonTools(void)
{
}


SkeletonTools::~SkeletonTools(void)
{
}

SkeletonTools* SkeletonTools::getInstance()
{
	if (_instance == NULL )
	{
		_instance = new SkeletonTools();
	}
	return _instance;
}


map<int, vector<SkeletonPoint> > SkeletonTools::getAllSkeletonPerFps(string filePath)
{
	FileHandle fileHandler;
	map<int, vector<SkeletonPoint> > reMap;
	for (int i = 1; i <=5 ; ++i)
	{
		try{
			stringstream fileName;
			fileName<<filePath<<"/cn"<<i<<".txt";
			fileHandler.setFileName(fileName.str());
			reMap[i] = fileHandler.readSkeletonPointFromFile();
			fileHandler.printInfo();
		}catch(int errorCode){
			if (errorCode==-1)
			{
				cout<<"Catch error when open in file"<<endl;
			}
			if (errorCode==-2)
			{
				cout<<"Catch error when open out file"<<endl;
			}
		}
		
	}
	return reMap;
}

void SkeletonTools::writeAllSkeletonPerFps(string filePath, string fileMark, map<int, vector<SkeletonPoint> > sk_map)
{
	FileHandle fileHandler;
	for (int i = 1; i <=5 ; ++i)
	{
		try{
			stringstream fileName;
			fileName<<filePath<<"/cn"<<i<<fileMark<<".txt";
			fileHandler.writeSkeletonToFile(fileName.str(),sk_map[i]);

		}catch(int errorCode){
			if (errorCode==-1)
			{
				cout<<"Catch error when open in file"<<endl;
			}
			if (errorCode==-2)
			{
				cout<<"Catch error when open out file"<<endl;
			}
		}

	}
}

map<int, vector<SkeletonPoint> > SkeletonTools::getSampleSkeletonPerFps(map<int, vector<SkeletonPoint> > skeleton)
{
	map<int, vector<SkeletonPoint> > sampleSkeleton;

	//左臂，取10点
	int cn1_size = skeleton[1].size();
	for (int i = 1; i<=10; ++i)
	{
		int index = int((double(cn1_size)/10.0)*i);
		sampleSkeleton[1].push_back(skeleton[1].at(indexJudge(index-1)));
	}

	//右臂，取10点
	int cn2_size = skeleton[2].size();
	for (int i = 1; i<=10; ++i)
	{
		int index = int((double(cn2_size)/10.0)*i);
		sampleSkeleton[2].push_back(skeleton[2].at(indexJudge(index-1)));
	}

	//左腿，取10点
	sort(skeleton[3].begin(),skeleton[3].end(),GlobalFunction::compareSkeletonPoint_Y_Less);
	int cn3_size = skeleton[3].size();
	for (int i = 1; i<=10; ++i)
	{
		int index = int((double(cn3_size)/10.0)*i);
		sampleSkeleton[3].push_back(skeleton[3].at(indexJudge(index-1)));
	}

	//右腿，取10点
	sort(skeleton[4].begin(),skeleton[4].end(),GlobalFunction::compareSkeletonPoint_Y_Less);
	int cn4_size = skeleton[4].size();
	for (int i = 1; i<=10; ++i)
	{
		int index = int((double(cn4_size)/10.0)*i);
		sampleSkeleton[4].push_back(skeleton[4].at(indexJudge(index-1)));
	}

	//躯干，取10点
	sort(skeleton[5].begin(),skeleton[5].end(),GlobalFunction::compareSkeletonPoint_Y_Less);
	int cn5_size = skeleton[5].size();
	for (int i = 1; i<=10; ++i)
	{
		int index = int((double(cn5_size)/10.0)*i);
		sampleSkeleton[5].push_back(skeleton[5].at(indexJudge(index-1)));
	}

	//SkeletonPoint center = getMidPoint(sampleSkeleton[1].at(9),sampleSkeleton[2].at(0));
	SkeletonPoint center = getAveragePoint(skeleton[5]);
	return skeletonAlign(sampleSkeleton,center);

}

map<int, vector<SkeletonPoint> > SkeletonTools::getSampleSkeletonPerFps(map<int, vector<SkeletonPoint> > skeleton,string sortMethod[])
{
	map<int, vector<SkeletonPoint> > sampleSkeleton;

	//排序
	printSkMap(skeleton);
	sortSkMap(skeleton,sortMethod);
	printSkMap(skeleton);

	//左臂，取10点
	int cn1_size = skeleton[1].size();
	for (int i = 1; i<=10; ++i)
	{
		int index = int((double(cn1_size)/10.0)*i);
		sampleSkeleton[1].push_back(skeleton[1].at(indexJudge(index-1)));
	}

	//右臂，取10点
	int cn2_size = skeleton[2].size();
	for (int i = 1; i<=10; ++i)
	{
		int index = int((double(cn2_size)/10.0)*i);
		sampleSkeleton[2].push_back(skeleton[2].at(indexJudge(index-1)));
	}

	//左腿，取10点
	//sort(skeleton[3].begin(),skeleton[3].end(),GlobalFunction::compareSkeletonPoint_Y_Less);
	int cn3_size = skeleton[3].size();
	for (int i = 1; i<=10; ++i)
	{
		int index = int((double(cn3_size)/10.0)*i);
		sampleSkeleton[3].push_back(skeleton[3].at(indexJudge(index-1)));
	}

	//右腿，取10点
	//sort(skeleton[4].begin(),skeleton[4].end(),GlobalFunction::compareSkeletonPoint_Y_Less);
	int cn4_size = skeleton[4].size();
	for (int i = 1; i<=10; ++i)
	{
		int index = int((double(cn4_size)/10.0)*i);
		sampleSkeleton[4].push_back(skeleton[4].at(indexJudge(index-1)));
	}

	//躯干，取10点
	//sort(skeleton[5].begin(),skeleton[5].end(),GlobalFunction::compareSkeletonPoint_Y_Less);
	int cn5_size = skeleton[5].size();
	for (int i = 1; i<=10; ++i)
	{
		int index = int((double(cn5_size)/10.0)*i);
		sampleSkeleton[5].push_back(skeleton[5].at(indexJudge(index-1)));
	}

	//SkeletonPoint center = getMidPoint(sampleSkeleton[1].at(9),sampleSkeleton[2].at(9));
	//SkeletonPoint center = getAveragePoint(skeleton[5]);
	SkeletonPoint center = sampleSkeleton[5].at(9);
	return skeletonAlign(sampleSkeleton,center);

}

map<int, vector<SkeletonPoint> > SkeletonTools::getSampleSkeletonPerFps_asKinect(map<int, vector<SkeletonPoint> > skeleton)
{
	map<int, vector<SkeletonPoint> > sampleSkeleton;

	//cn1 左臂
	int cn1_size = skeleton[1].size();
	SkeletonPoint hand_left = skeleton[1].at(0);
	SkeletonPoint wrist_left = skeleton[1].at(indexJudge(cn1_size/6));
	SkeletonPoint elbow_left = skeleton[1].at(indexJudge(cn1_size/2-1));
	SkeletonPoint shoulder_left = skeleton[1].at(indexJudge(cn1_size*3/4-1));
	SkeletonPoint shoulder_lcenter = skeleton[1].at(indexJudge(cn1_size-1));
	sampleSkeleton[1].push_back(hand_left);
	sampleSkeleton[1].push_back(wrist_left);
	sampleSkeleton[1].push_back(elbow_left);
	sampleSkeleton[1].push_back(shoulder_left);

	//cn2 右臂
	int cn2_size = skeleton[2].size();
	SkeletonPoint hand_right = skeleton[2].at(indexJudge(cn2_size-1));
	SkeletonPoint wrist_right = skeleton[2].at(indexJudge(cn2_size*5/6-1));
	SkeletonPoint elbow_right = skeleton[2].at(indexJudge(cn2_size/2-1));
	SkeletonPoint shoulder_right = skeleton[2].at(indexJudge(cn2_size/4-1));
	SkeletonPoint shoulder_rcenter = skeleton[2].at(0);
	sampleSkeleton[2].push_back(hand_right);
	sampleSkeleton[2].push_back(wrist_right);
	sampleSkeleton[2].push_back(elbow_right);
	sampleSkeleton[2].push_back(shoulder_right);

	//cn3 左腿
	int cn3_size = skeleton[3].size();
	SkeletonPoint foot_left = skeleton[3].at(0);
	SkeletonPoint ankle_left = skeleton[3].at(indexJudge(cn3_size/8));
	SkeletonPoint knee_left = skeleton[3].at(indexJudge(cn3_size/2-1));
	SkeletonPoint hip_left = skeleton[3].at(indexJudge(cn3_size*7/8-1));
	SkeletonPoint hip_lcenter = skeleton[3].at(indexJudge(cn3_size-1));
	sampleSkeleton[3].push_back(foot_left);
	sampleSkeleton[3].push_back(ankle_left);
	sampleSkeleton[3].push_back(knee_left);
	sampleSkeleton[3].push_back(hip_left);

	//cn4 右腿
	int cn4_size = skeleton[4].size();
	SkeletonPoint foot_right = skeleton[4].at(indexJudge(cn4_size-1));
	SkeletonPoint ankle_right = skeleton[4].at(indexJudge(cn4_size*7/8-1));
	SkeletonPoint knee_right = skeleton[4].at(indexJudge(cn4_size/2-1));
	SkeletonPoint hip_right = skeleton[4].at(indexJudge(cn4_size/8));
	SkeletonPoint hip_rcenter = skeleton[4].at(0);
	sampleSkeleton[4].push_back(foot_right);
	sampleSkeleton[4].push_back(ankle_right);
	sampleSkeleton[4].push_back(knee_right);
	sampleSkeleton[4].push_back(hip_right);

	//cn5 躯干
	//增加躯干处点按垂直方向排列
	cout<<"before sort:"<<endl;
	vector<SkeletonPoint>::iterator iter;
	for (iter = skeleton[5].begin(); iter!=skeleton[5].end() ; ++iter)
	{
		cout<<(*iter).getX()<<" "<<(*iter).getY()<<" "<<(*iter).getZ()<<endl;
	} 
	sort(skeleton[5].begin(),skeleton[5].end(),GlobalFunction::compareSkeletonPoint_Y_Less);
	cout<<"after sort:"<<endl;
	for (iter = skeleton[5].begin(); iter!=skeleton[5].end() ; ++iter)
	{
		cout<<(*iter).getX()<<" "<<(*iter).getY()<<" "<<(*iter).getZ()<<endl;
	}
	int cn5_size = skeleton[5].size();
	SkeletonPoint _head = skeleton[5].at(0);
	SkeletonPoint spine = skeleton[5].at(indexJudge(cn5_size*3/4-1));
	SkeletonPoint shoulder_center = getMidPoint(shoulder_lcenter,shoulder_rcenter);
	SkeletonPoint hip_center = getMidPoint(hip_lcenter,hip_rcenter);
	sampleSkeleton[5].push_back(_head);
	sampleSkeleton[5].push_back(spine);
	sampleSkeleton[5].push_back(shoulder_center);
	sampleSkeleton[5].push_back(hip_center);
	
	//对各帧骨骼点进行校准，将shoulder_center点对齐
	//return sampleSkeleton;
	return skeletonAlign(sampleSkeleton,shoulder_center);
}

SkeletonPoint SkeletonTools::getMidPoint(SkeletonPoint sp1, SkeletonPoint sp2)
{
	double mx = ( sp1.getX()+sp2.getX() )/2.0;
	double my = ( sp1.getY()+sp2.getY() )/2.0;
	double mz = ( sp1.getZ()+sp2.getZ() )/2.0;

	return SkeletonPoint(mx,my,mz);
}

SkeletonPoint SkeletonTools::getAveragePoint(vector<SkeletonPoint> sk_v)
{
	vector<SkeletonPoint>::iterator iter;
	int sk_size = sk_v.size();
	double x_total = 0.0;
	double y_total = 0.0;
	double z_total = 0.0;
	for (iter = sk_v.begin();iter!=sk_v.end();++iter)
	{
		x_total += (*iter).getX();
		y_total += (*iter).getY();
		z_total += (*iter).getZ();
	}

	return SkeletonPoint(x_total/(double)sk_size,y_total/(double)sk_size,z_total/(double)sk_size);
}

int SkeletonTools::indexJudge(int index)
{
	if(index<0)
	{
		return 0;
	}
	return index;
}

vector<SkeletonPoint> SkeletonTools::getSkeleonVector(map<int, map<int,vector<SkeletonPoint> > > sk_map)
{
	vector<SkeletonPoint> reVector;
	map<int, map<int,vector<SkeletonPoint> > >::iterator iter_map;
	for (iter_map=sk_map.begin(); iter_map!=sk_map.end(); ++iter_map)
	{
		map<int,vector<SkeletonPoint> > sk_map_per_fps = iter_map->second;
		for (int i=1; i<=5; ++i)
		{
			vector<SkeletonPoint>::iterator iter_vec;
			for (iter_vec=sk_map_per_fps[i].begin(); iter_vec!=sk_map_per_fps[i].end(); ++iter_vec)
			{
				reVector.push_back(*iter_vec);
			}
		}
	}

	return reVector;
}

map<int, vector<SkeletonPoint> > SkeletonTools::skeletonAlign(map<int, vector<SkeletonPoint> > sk_source, SkeletonPoint sp)
{
	map<int, vector<SkeletonPoint> > reSkeletonAlign;
	map<int, vector<SkeletonPoint> >::iterator iter;
	for (iter=sk_source.begin(); iter!=sk_source.end(); ++iter)
	{
		int key = iter->first;
		vector<SkeletonPoint> skeleton = iter->second;

		vector<SkeletonPoint>::iterator iter_v;
		for (iter_v = skeleton.begin(); iter_v != skeleton.end(); ++iter_v)
		{
			SkeletonPoint sp_align = *iter_v - sp;
			reSkeletonAlign[key].push_back(sp_align);
		}
	}

	return reSkeletonAlign;
}

map<int,map<int,vector<SkeletonPoint> > > SkeletonTools::segmentSkletonVector(vector<SkeletonPoint> sk)
{
	int sk_size = sk.size();
	int fps_number = sk_size/20;

	map<int,map<int,vector<SkeletonPoint> > > remap;

	int num = 0;
	for (int i=0; i<fps_number; ++i)
	{
		map<int,vector<SkeletonPoint> > sk_fps;
		for(int n=1; n<=5; ++n)
		{
			for (int counter=0; counter<4; ++counter)
			{
				sk_fps[n].push_back(sk.at(num));
				++num;
			}
		}
		remap[i] = sk_fps;
	}

	return remap;
}

map<int,map<int,vector<SkeletonPoint> > > SkeletonTools::segmentSkletonVector(vector<SkeletonPoint> sk, int fpsNum, int perSegNum)
{
	int sk_size = sk.size();

	map<int,map<int,vector<SkeletonPoint> > > remap;

	int num = 0;
	for (int i=0; i<fpsNum; ++i)
	{
		map<int,vector<SkeletonPoint> > sk_fps;
		for(int n=1; n<=5; ++n)
		{
			for (int counter=0; counter<perSegNum; ++counter)
			{
				sk_fps[n].push_back(sk.at(num));
				++num;
			}
		}
		remap[i] = sk_fps;
	}

	return remap;
}

void SkeletonTools::sortSkMap(map<int, vector<SkeletonPoint> >& skeleton,string sortMethod[])
{
	for (int i=1; i<=5; ++i)
	{
		if (sortMethod[i-1] == "XL")
		{
			sort(skeleton[i].begin(),skeleton[i].end(),GlobalFunction::compareSkeletonPoint_X_Less);
		}
		else if (sortMethod[i-1] == "XG")
		{
			sort(skeleton[i].begin(),skeleton[i].end(),GlobalFunction::compareSkeletonPoint_X_Greater);
		}
		else if (sortMethod[i-1] == "YL")
		{
			sort(skeleton[i].begin(),skeleton[i].end(),GlobalFunction::compareSkeletonPoint_Y_Less);
		}
		else if (sortMethod[i-1] == "YG")
		{
			sort(skeleton[i].begin(),skeleton[i].end(),GlobalFunction::compareSkeletonPoint_Y_Greater);
		}
		else if (sortMethod[i-1] == "ZL")
		{
			sort(skeleton[i].begin(),skeleton[i].end(),GlobalFunction::compareSkeletonPoint_Z_Less);
		}
		else if (sortMethod[i-1] == "ZG")
		{
			sort(skeleton[i].begin(),skeleton[i].end(),GlobalFunction::compareSkeletonPoint_Z_Greater);
		}
		else
		{
			if (sortMethod[i-1].size()==5)
			{
				string sm_before = sortMethod[i-1].substr(0,2);
				string sm_after = sortMethod[i-1].substr(3,2);
				int num_before = atoi(sortMethod[i-1].substr(2,1).c_str());
				cout<<"sm_before:"<<sm_before<<"    sm_after:"<<sm_after<<"    num_before:"<<num_before<<endl;
				if (sm_before == "XL")
				{
					sort(skeleton[i].begin(),skeleton[i].end(),GlobalFunction::compareSkeletonPoint_X_Less);
				}
				else if(sm_before == "XG")
				{
					sort(skeleton[i].begin(),skeleton[i].end(),GlobalFunction::compareSkeletonPoint_X_Greater);
				}
				else if(sm_before == "YL")
				{
					sort(skeleton[i].begin(),skeleton[i].end(),GlobalFunction::compareSkeletonPoint_Y_Less);
				}
				else if(sm_before == "YG")
				{
					sort(skeleton[i].begin(),skeleton[i].end(),GlobalFunction::compareSkeletonPoint_Y_Greater);
				}
				else if(sm_before == "ZL")
				{
					sort(skeleton[i].begin(),skeleton[i].end(),GlobalFunction::compareSkeletonPoint_Z_Less);
				}
				else if(sm_before == "ZG")
				{
					sort(skeleton[i].begin(),skeleton[i].end(),GlobalFunction::compareSkeletonPoint_Z_Greater);
				}

				vector<SkeletonPoint>::iterator iter;
		
				if (sm_after == "XL")
				{
					sort(skeleton[i].begin()+num_before,skeleton[i].end(),GlobalFunction::compareSkeletonPoint_X_Less);
				}
				else if(sm_after == "XG")
				{
					sort(skeleton[i].begin()+num_before,skeleton[i].end(),GlobalFunction::compareSkeletonPoint_X_Greater);
				}
				else if(sm_after == "YL")
				{
					sort(skeleton[i].begin()+num_before,skeleton[i].end(),GlobalFunction::compareSkeletonPoint_Y_Less);
				}
				else if(sm_after == "YG")
				{
					sort(skeleton[i].begin()+num_before,skeleton[i].end(),GlobalFunction::compareSkeletonPoint_Y_Greater);
				}
				else if(sm_after == "ZL")
				{
					sort(skeleton[i].begin()+num_before,skeleton[i].end(),GlobalFunction::compareSkeletonPoint_Z_Less);
				}
				else if(sm_after == "ZG")
				{
					sort(skeleton[i].begin()+num_before,skeleton[i].end(),GlobalFunction::compareSkeletonPoint_Z_Greater);
				}
			}
		}

	}
}

void SkeletonTools::printSkMap(map<int, vector<SkeletonPoint> > skeleton)
{
	cout<<"print Skeleton Map 5 cn in 1 fps"<<endl;
	map<int, vector<SkeletonPoint> >::iterator iter_m;
	for (iter_m = skeleton.begin();iter_m != skeleton.end(); ++iter_m)
	{
		cout<<"cn:"<<iter_m->first<<endl;
		vector<SkeletonPoint>::iterator iter_v;
		for (iter_v = iter_m->second.begin(); iter_v != iter_m->second.end(); ++iter_v)
		{
			SkeletonPoint sk = *iter_v;
			cout<<sk.getX()<<" "<<sk.getY()<<" "<<sk.getZ()<<endl;
		}
	}
}