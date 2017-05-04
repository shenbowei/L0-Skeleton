#include "FileHandle.h"
#include "SkeletonTools.h"
#include "SkletonOptimizeViaL0.h"
#include "KeyboardEventHandle.h"
#include <map>

#include "GlobalFunction.h"

osg::ref_ptr<osg::Node> GlobalFunction::geode_skleton;
osg::ref_ptr<osg::Node> GlobalFunction::geode_skletonPoint;

int main()
{
	map<int, map<int,vector<SkeletonPoint> > > skeleton_all;
	try
	{
		//第一组实验
		/*
		skeleton_all[1] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00001");
		skeleton_all[25] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00025");
		skeleton_all[35] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00035");
		skeleton_all[45] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00045");
		skeleton_all[50] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00050");
		skeleton_all[55] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00055");
		skeleton_all[60] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00060");
		*/
		
		//第二组实验
		skeleton_all[63] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00063");
		skeleton_all[65] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00065");
		skeleton_all[66] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00066");
		skeleton_all[68] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00068");

		skeleton_all[70] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00070");
		skeleton_all[72] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00072");
		skeleton_all[74] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00074");
		skeleton_all[76] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00076");
		skeleton_all[78] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00078");

		skeleton_all[80] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00080");
		skeleton_all[82] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00082");
		skeleton_all[84] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00084");
		skeleton_all[86] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00086");
		skeleton_all[88] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00088");

		skeleton_all[90] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00090");
		skeleton_all[92] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00092");
		skeleton_all[94] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00094");
		skeleton_all[96] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00096");
		skeleton_all[98] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00098");

		/*
		//第三组实验
		skeleton_all[643] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00643");
		skeleton_all[644] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00644");
		skeleton_all[645] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00645");
		skeleton_all[646] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00646");
		skeleton_all[647] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00647");
		skeleton_all[648] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00648");
		skeleton_all[649] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00649");
		skeleton_all[650] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00650");
		skeleton_all[651] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_00651");
		*/
		//实验sbw
		/*
		skeleton_all[36] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00036");
		skeleton_all[41] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00041");
		skeleton_all[46] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00046");
		skeleton_all[51] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00051");
		skeleton_all[56] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00056");
		skeleton_all[61] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00061");
		skeleton_all[66] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00066");
		skeleton_all[71] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00071");
		skeleton_all[76] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00076");
		skeleton_all[81] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00081");
		skeleton_all[86] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00086");
		skeleton_all[91] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00091");
		skeleton_all[96] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00096");
		*/
		//实验an
		/*
		skeleton_all[296] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_an/skeleton_00296");
		skeleton_all[301] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_an/skeleton_00301");
		skeleton_all[306] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_an/skeleton_00306");
		skeleton_all[311] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_an/skeleton_00311");
		skeleton_all[316] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_an/skeleton_00316");
		skeleton_all[321] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_an/skeleton_00321");
		skeleton_all[326] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_an/skeleton_00326");
		skeleton_all[331] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_an/skeleton_00331");
		skeleton_all[336] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_an/skeleton_00336");
		skeleton_all[341] = SkeletonTools::getInstance()->getAllSkeletonPerFps("../files/skeleton_an/skeleton_00341");
		*/
	}
	catch(int errorCode)
	{
		if (errorCode==-1)
		{
			cout<<"Catch error when open in file"<<endl;
		}
		if (errorCode==-2)
		{
			cout<<"Catch error when open out file"<<endl;
		}
	} 
	catch(exception &e)
	{
		cout<<e.what()<<endl;
		//throw new exception("exception throw in main.cpp");
	}
	

	//提取每帧20个点的类似kinect的骨骼点
	map<int, map<int,vector<SkeletonPoint> > > skeleton_Extract_all;
	string p[5] = {"XL","XG","YG","YG","YL"};

	//第一组实验
	/*
	skeleton_Extract_all[1]= SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[1],p);
	skeleton_Extract_all[25]= SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[25],p);
	skeleton_Extract_all[35]= SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[35],p);
	skeleton_Extract_all[45] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[45],p);
	skeleton_Extract_all[50] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[50],p);
	p[0] = "ZL";
	p[1] = "ZL";
	skeleton_Extract_all[55] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[55],p);
	skeleton_Extract_all[60] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[60],p);
	*/

	//实验sbw
	/*
	p[0] = "ZL";
	p[1] = "ZG";
	skeleton_Extract_all[36] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[36],p);
	skeleton_Extract_all[41] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[41],p);
	skeleton_Extract_all[46] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[46],p);
	skeleton_Extract_all[51] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[51],p);
	p[0] = "ZL";
	p[1] = "YG";
	skeleton_Extract_all[56] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[56],p);
	p[0] = "YG";
	p[1] = "YG";
	skeleton_Extract_all[61] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[61],p);
	skeleton_Extract_all[66] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[66],p);
	p[0] = "YG";
	p[1] = "ZL";
	skeleton_Extract_all[71] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[71],p);
	skeleton_Extract_all[76] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[76],p);
	skeleton_Extract_all[81] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[81],p);
	skeleton_Extract_all[86] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[86],p);
	skeleton_Extract_all[91] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[91],p);
	skeleton_Extract_all[96] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[96],p);
	*/

	//实验an
	/*
	p[0] = "ZL";
	p[1] = "ZL";
	skeleton_Extract_all[296] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[296],p);
	skeleton_Extract_all[301] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[301],p);
	skeleton_Extract_all[306] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[306],p);
	skeleton_Extract_all[311] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[311],p);
	skeleton_Extract_all[316] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[316],p);
	skeleton_Extract_all[321] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[321],p);
	skeleton_Extract_all[326] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[326],p);
	p[1] = "ZL5XG";
	skeleton_Extract_all[331] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[331],p);
	p[1] = "XG";
	skeleton_Extract_all[336] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[336],p);
	p[1] = "ZL5XG";
	skeleton_Extract_all[341] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[341],p);
	*/
	
	//第二组实验
	
	p[0] = "ZL";
	p[1] = "ZL";
	skeleton_Extract_all[63] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[63],p);
	skeleton_Extract_all[65] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[65],p);
	skeleton_Extract_all[66] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[66],p);
	skeleton_Extract_all[68] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[68],p);

	skeleton_Extract_all[70] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[70],p);
	skeleton_Extract_all[72] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[72],p);
	skeleton_Extract_all[74] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[74],p);
	skeleton_Extract_all[76] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[76],p);
	skeleton_Extract_all[78] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[78],p);

	skeleton_Extract_all[80] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[80],p);
	
	p[1] = "ZL3XG";
	skeleton_Extract_all[82] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[82],p);
	p[1] = "ZL1XG";
	skeleton_Extract_all[84] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[84],p);
	p[1] = "ZL3XG";
	skeleton_Extract_all[86] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[86],p);
	p[1] = "XG";
	skeleton_Extract_all[88] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[88],p);

	//p[0] = "XL";
	//p[1] = "XG";
	skeleton_Extract_all[90] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[90],p);
	skeleton_Extract_all[92] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[92],p);
	skeleton_Extract_all[94] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[94],p);
	skeleton_Extract_all[96] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[96],p);
	skeleton_Extract_all[98] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[98],p);
	

	//第三组实验
	/*
	p[0] = "XL";
	p[1] = "XG";
	skeleton_Extract_all[643] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[643],p);
	skeleton_Extract_all[644] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[644],p);
	skeleton_Extract_all[645] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[645],p);
	skeleton_Extract_all[646] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[646],p);
	skeleton_Extract_all[647] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[647],p);
	skeleton_Extract_all[648] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[648],p);
	skeleton_Extract_all[649] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[649],p);
	skeleton_Extract_all[650] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[650],p);
	//skeleton_Extract_all[651] = SkeletonTools::getInstance()->getSampleSkeletonPerFps(skeleton_all[651],p);
	*/
	

	//对各帧骨骼点进行校准，将shoulder_center点对齐
	//在getSampleSkeletonPerFps中进行
	

	//将提取的骨骼点写入文件
	/*
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00001","_extract_10",sk1_extract_kinect);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00045","_extract_10",sk45_extract_kinect);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00050","_extract_10",sk50_extract_kinect);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00055","_extract_10",sk55_extract_kinect);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00060","_extract_10",sk60_extract_kinect);
	*/

	//生成所有点的vector，优化用
	vector<SkeletonPoint> sk_vec = SkeletonTools::getInstance()->getSkeleonVector(skeleton_Extract_all);
	FileHandle fh;
	//fh.writeSkeletonToFile("../files/skeleton_an/skleton_extract_all_vector_an.txt",sk_vec);

	//l0优化
	//vector<SkeletonPoint> sk_vec_opt = SkletonOptimizeViaL0::optimizeViaL0(sk_vec,50);
	vector<SkeletonPoint> sk_vec_opt = SkletonOptimizeViaL0::optimizeViaL0(sk_vec,50);
	//fh.writeSkeletonToFile("../files/skeleton_an/skleton_extract_all_vector_an_opt.txt",sk_vec_opt);

	//分割为各帧，写入文件
	
	//map<int, map<int,vector<SkeletonPoint> > > skl_map_opt = SkeletonTools::getInstance()->segmentSkletonVector(sk_vec_opt,19,10);
	//cout<<"segment num:"<<skl_map_opt.size()<<endl;
	/*
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00036","_opt",skl_map_opt[0]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00041","_opt",skl_map_opt[1]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00046","_opt",skl_map_opt[2]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00051","_opt",skl_map_opt[3]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00056","_opt",skl_map_opt[4]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00061","_opt",skl_map_opt[5]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00066","_opt",skl_map_opt[6]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00071","_opt",skl_map_opt[7]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00076","_opt",skl_map_opt[8]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00081","_opt",skl_map_opt[9]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00086","_opt",skl_map_opt[10]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00091","_opt",skl_map_opt[11]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_sbw/skeleton_00096","_opt",skl_map_opt[12]);
	*/

	/*
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_an/skeleton_00296","_opt",skl_map_opt[0]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_an/skeleton_00301","_opt",skl_map_opt[1]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_an/skeleton_00306","_opt",skl_map_opt[2]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_an/skeleton_00311","_opt",skl_map_opt[3]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_an/skeleton_00316","_opt",skl_map_opt[4]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_an/skeleton_00321","_opt",skl_map_opt[5]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_an/skeleton_00326","_opt",skl_map_opt[6]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_an/skeleton_00331","_opt",skl_map_opt[7]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_an/skeleton_00336","_opt",skl_map_opt[8]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_an/skeleton_00341","_opt",skl_map_opt[9]);
	*/
	/*
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00063","_opt",skl_map_opt[0]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00065","_opt",skl_map_opt[1]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00066","_opt",skl_map_opt[2]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00068","_opt",skl_map_opt[3]);

	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00070","_opt",skl_map_opt[4]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00072","_opt",skl_map_opt[5]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00074","_opt",skl_map_opt[6]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00076","_opt",skl_map_opt[7]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00078","_opt",skl_map_opt[8]);

	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00080","_opt",skl_map_opt[9]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00082","_opt",skl_map_opt[10]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00084","_opt",skl_map_opt[11]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00086","_opt",skl_map_opt[12]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00088","_opt",skl_map_opt[13]);

	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00090","_opt",skl_map_opt[14]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00092","_opt",skl_map_opt[15]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00094","_opt",skl_map_opt[16]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00096","_opt",skl_map_opt[17]);
	SkeletonTools::getInstance()->writeAllSkeletonPerFps("../files/skeleton_00098","_opt",skl_map_opt[18]);
	*/

	osg::ref_ptr<osg::Group> group;
	group = new osg::Group;

	//vector<SkeletonPoint> sk_45(sk_vec_opt.begin()+4*50,sk_vec_opt.begin()+5*50);
	//vector<SkeletonPoint> sk_65(sk_vec_opt.begin()+1*50,sk_vec_opt.begin()+2*50);
	//std::copy(sk_vec_opt.begin()+40,sk_vec_opt.begin()+50,sk_45.begin());
	GlobalFunction::geode_skleton = GlobalFunction::createSkeletonNode(sk_vec_opt,osg::Vec3(0.0,0.0,0.0));
	GlobalFunction::geode_skletonPoint = GlobalFunction::createSkeletonPointSphereNode(sk_vec_opt,osg::Vec3(0.0,0.0,0.0));
	group->addChild(GlobalFunction::geode_skleton.get());
	group->addChild(GlobalFunction::geode_skletonPoint.get());

	//group->addChild(createSkeletonNode(sk_vec_opt,osg::Vec3(0.0,0.0,0.0)));
	//group->addChild(createSkeletonPointSphereNode(sk_vec_opt,osg::Vec3(0.0,0.0,0.0)));

	//group->addChild(createSkeletonNode(sk_vec,osg::Vec3(0.0,0.0,0.0)));
	//group->addChild(createSkeletonPointSphereNode(sk_vec,osg::Vec3(0.0,0.0,0.0)));
	//添加光照
	osg::ref_ptr<osg::Light> light = new osg::Light();
	light->setLightNum(0);
	//light->setDirection(osg::Vec3(0.0f, 0.0f, -1.0f));
	light->setPosition(osg::Vec4(0.0, 0.0, 0.0, 0.0f));
	light->setAmbient(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setDiffuse(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setConstantAttenuation(0.1f);
	light->setLinearAttenuation(0.1f);
	light->setQuadraticAttenuation(0.1f);
	osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource();
	lightSource->setLight(light.get());
	//group->addChild(lightSource);

	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	viewer->getCamera()->setClearColor(osg::Vec4(1.0,1.0,1.0,1.0));
	viewer->setSceneData(group.get());
	viewer->addEventHandler(new KeyboardEventHandle());
	viewer->setCameraManipulator(new osgGA::TrackballManipulator);
	return viewer->run();

	system("pause");
}