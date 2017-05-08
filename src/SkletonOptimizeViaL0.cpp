#include "SkletonOptimizeViaL0.h"
#include <Eigen/Core>
#include <Eigen/Sparse>

typedef Eigen::MatrixXd Matrix;
typedef Eigen::SparseMatrix<double> SpMat;
typedef Eigen::Triplet<double> Triplet;

SkletonOptimizeViaL0::SkletonOptimizeViaL0(void)
{
}


SkletonOptimizeViaL0::~SkletonOptimizeViaL0(void)
{
}

vector<SkeletonPoint> SkletonOptimizeViaL0::optimizeViaL0(vector<SkeletonPoint> skeleton, int frameInterval)
{
	int nVert = skeleton.size();
	
	//创建系数矩阵D,各点的矩阵pInit、pVec,单位矩阵I
	vector<Triplet> tripD;
	Matrix pInit(nVert, 3);
	Matrix pVec(nVert, 3);
	vector<Triplet> tripI(nVert);
	//增加约束矩阵R
	vector<Triplet> tripR;
	vector<Triplet> tripR_Joint;
	for (int i=0; i<nVert ; ++i)
	{
		//稀疏矩阵D
		int lastIndex = i;
		int nextIndex = i;
		if ((i-frameInterval)>=0)
		{
			lastIndex = i-frameInterval;
		}

		if ((i+frameInterval)<nVert)
		{
			nextIndex = i+frameInterval;
		}

		if (lastIndex==i)
		{
			//第一帧
			tripD.push_back(Triplet(i, i, 1.0));
			tripD.push_back(Triplet(i, nextIndex, -1.0));
			//tripR.push_back(Triplet(i, i, 1.0));
			//tripR.push_back(Triplet(i, nextIndex, -1.0));
		}
		else if(nextIndex==i)
		{
			//最后一帧
			tripD.push_back(Triplet(i, lastIndex, -1.0));
			tripD.push_back(Triplet(i, i, 1.0));
			//tripR.push_back(Triplet(i, lastIndex, -1.0));
			//tripR.push_back(Triplet(i, i, 1.0));
		}
		else
		{
			tripD.push_back(Triplet(i, lastIndex, -1.0));
			tripD.push_back(Triplet(i, i, 2.0));
			tripD.push_back(Triplet(i, nextIndex, -1.0));

			//tripR.push_back(Triplet(i, lastIndex, -1.0));
			//tripR.push_back(Triplet(i, i, 2.0));
			//tripR.push_back(Triplet(i, nextIndex, -1.0));
		}

		//R矩阵改为同一帧相邻点的约束（相邻帧约束已经在l0中体现），所以为了保证同一帧中骨骼相邻点平滑，加上约束R
		if (i%10 == 0)
		{
			//如果是该帧所在块的第一个点
			//tripR.push_back(Triplet(i,i,1.0));
			//tripR.push_back(Triplet(i,i+1,-1.0));
		}
		else if ((i+1)%10 == 0)
		{
			//如果是该帧所在块的最后一个点
			//tripR.push_back(Triplet(i,i-1,-1.0));
			//tripR.push_back(Triplet(i,i,1.0));
		}
		else
		{
			tripR.push_back(Triplet(i,i-1,-1.0));
			tripR.push_back(Triplet(i,i,2.0));
			tripR.push_back(Triplet(i,i+1,-1.0));
		}

		//增加joint点的约束
		//双臂间的joint点
		if(i%50==9)
		{
			/*
			//左臂最右一点
			tripR_Joint.push_back(Triplet(i,i,-1.0));
			//右臂最左一点
			tripR_Joint.push_back(Triplet(i,i+10,-1.0));
			//骨干的第三点
			tripR_Joint.push_back(Triplet(i,i+33,2.0));
			*/
			tripR_Joint.push_back(Triplet(i,i,1.0));
			tripR_Joint.push_back(Triplet(i,i+10,-1.0));
		}
		else if(i%50==19)
		{
			/*
			//左臂最右一点
			tripR_Joint.push_back(Triplet(i,i,-1.0));
			//右臂最左一点
			tripR_Joint.push_back(Triplet(i,i-10,-1.0));
			//骨干的第三点
			tripR_Joint.push_back(Triplet(i,i+23,2.0));
			*/
			tripR_Joint.push_back(Triplet(i,i,1.0));
			tripR_Joint.push_back(Triplet(i,i-10,-1.0));
		}
		else if(i%50==42)
		{
			
			//左臂最右一点
			tripR_Joint.push_back(Triplet(i,i-33,-1.0));
			//右臂最左一点
			tripR_Joint.push_back(Triplet(i,i-23,-1.0));
			//骨干的第三点
			tripR_Joint.push_back(Triplet(i,i,2.0));
			
		}
		//两腿间的joint点
		else if(i%50==29)
		{
			/*
			//左腿最右一点
			tripR_Joint.push_back(Triplet(i,i,-1.0));
			//右腿最左一点
			tripR_Joint.push_back(Triplet(i,i+10,-1.0));
			//骨干的最后一点
			tripR_Joint.push_back(Triplet(i,i+20,2.0));
			*/
			tripR_Joint.push_back(Triplet(i,i,1.0));
			tripR_Joint.push_back(Triplet(i,i+10,-1.0));

			/*
			cout<<i<<endl;
			cout<<skeleton.at(i).getX()<<" "<<skeleton.at(i).getY()<<" "<<skeleton.at(i).getZ()<<endl;
			cout<<skeleton.at(i+10).getX()<<" "<<skeleton.at(i).getY()<<" "<<skeleton.at(i).getZ()<<endl;
			cout<<skeleton.at(i+20).getX()<<" "<<skeleton.at(i).getY()<<" "<<skeleton.at(i).getZ()<<endl;
			*/
			
		}
		else if(i%50==39)
		{
			/*
			//左腿最右一点
			tripR_Joint.push_back(Triplet(i,i-10,-1.0));
			//右腿最左一点
			tripR_Joint.push_back(Triplet(i,i,-1.0));
			//骨干的最后一点
			tripR_Joint.push_back(Triplet(i,i+10,2.0));
			*/
			tripR_Joint.push_back(Triplet(i,i,1.0));
			tripR_Joint.push_back(Triplet(i,i-10,-1.0));

		}
		else if(i%50==49)
		{

			//左腿最右一点
			tripR_Joint.push_back(Triplet(i,i-20,-1.0));
			//右腿最左一点
			tripR_Joint.push_back(Triplet(i,i-10,-1.0));
			//骨干的最后一点
			tripR_Joint.push_back(Triplet(i,i,2.0));

		}


		//各点的矩阵pInit、pVec
		SkeletonPoint sp = skeleton.at(i);
		pInit(i, 0) = sp.getX();
		pInit(i, 1) = sp.getY();
		pInit(i, 2) = sp.getZ();

		pVec(i, 0) = sp.getX();
		pVec(i, 1) = sp.getY();
		pVec(i, 2) = sp.getZ();

		//单位矩阵I
		tripI[i] = Triplet(i, i, 1.0);
	}
	SpMat D(nVert, nVert);
	D.setFromTriplets(tripD.begin(), tripD.end());
	SpMat I(nVert, nVert);
	I.setFromTriplets(tripI.begin(), tripI.end());

	SpMat R(nVert, nVert);
	R.setFromTriplets(tripR.begin(), tripR.end());
	SpMat R_Joint(nVert, nVert);
	R_Joint.setFromTriplets(tripR_Joint.begin(), tripR_Joint.end());

	//求解最优化问题
	double lambda = 0.003*5.0;

	double alpha    = 2.0;
	double beta     = 2.0;
	double gamma    = 0.001;
	double gmax     = 100.0;
	double mu_gamma = 1.414;

	Matrix dlt(nVert, 3);

	while(gamma < gmax) {
		// 阶段一：固定p，求解dlt (shrinkage operator)
		printf("solve sub-problem for delta\n");
		Matrix y = D * pVec;
		for(int i=0; i<nVert; i++) {
			/*
			dlt(i, 0) = 0.0;
			for(int d=0; d<3; d++) {
				dlt(i, 0) += y(i, d) * y(i, d);
			}

			if(dlt(i, 0) < lambda / beta) {
				dlt(i, 0) = 0.0;
			}

			dlt(i, 1) = dlt(i, 0);
			dlt(i, 2) = dlt(i, 0);
			*/
			
			dlt(i, 0) = 0.0;
			for(int d=0; d<3; d++) {
				dlt(i, d) = y(i, d);
			}
			
			if((dlt(i, 0)*dlt(i, 0)+dlt(i, 1)*dlt(i, 1)+dlt(i, 2)*dlt(i, 2)) < lambda / gamma) {
				dlt(i, 0) = 0.0;
				dlt(i, 1) = 0.0;
				dlt(i, 2) = 0.0;
			}
			
		}

		// 阶段二：固定dlt，求解p (linear system)
		printf("solve sub-problem for points\n");
		SpMat  A = I  + alpha * R.transpose() * R + beta* R_Joint.transpose() * R_Joint + gamma * D.transpose() * D;
		Matrix b = pInit + gamma * D.transpose() * dlt;

		Eigen::SparseLU<Eigen::SparseMatrix<double> > solver;
		solver.analyzePattern(A);
		solver.factorize(A);
		cout<<solver.info()<<endl;
		cout<<solver.lastErrorMessage()<<std::endl;
		if(solver.info() != Eigen::Success)
		{
			cout<<"error after factorize"<<endl;
		}
		pVec = solver.solve(b);
		cout<<solver.info()<<endl;
		cout<<solver.lastErrorMessage()<<std::endl;
		if(solver.info() != Eigen::Success)
		{
			cout<<"error after solve"<<endl;
		}
		
		// 更新参数
		gamma  *= mu_gamma;
		//alpha *= 0.707;
	}
	cout<<"optimization finished"<<endl;

	//返回优化后的点
	vector<SkeletonPoint> reSkeleton;
	for (int i=0; i<nVert; ++i)
	{
		reSkeleton.push_back(SkeletonPoint(pVec(i, 0), pVec(i, 1), pVec(i, 2)));
	}

	return reSkeleton;
}


vector<SkeletonPoint> SkletonOptimizeViaL0::optimizeViaL0_with_Gaussian(vector<SkeletonPoint> skeleton, int frameInterval)
{
	int nVert = skeleton.size();
	
	//创建系数矩阵D,各点的矩阵pInit、pVec,单位矩阵I
	vector<Triplet> tripD;
	Matrix pInit(nVert, 3);
	Matrix pVec(nVert, 3);
	vector<Triplet> tripI(nVert);
	//增加约束矩阵R
	vector<Triplet> tripR;
	for (int i=0; i<nVert ; ++i)
	{
		//计算稀疏矩阵D
		double theta_weight = 0.0;
		//遍历之前的各帧
		for (int n=1; i-n*frameInterval>=0; ++n)
		{
			
			double r = n*frameInterval;
			//double h = max(i,nVert-i);
			double h = nVert;
			tripD.push_back(Triplet(i, i-n*frameInterval, -exp(-(r*r)/(h*h/4.0))));
			theta_weight += -exp(-(r*r)/(h*h/4.0));
			//tripD.push_back(Triplet(i, i-n*frameInterval, -1.0/((double)n*(double)n+1.0)));
			//theta_weight += -1.0/((double)n*(double)n+2.0);
			//tripR.push_back(Triplet(i, i-n*frameInterval, -exp(-(r*r)/(h*h/4.0))));
		}

		//遍历之后的各帧
		for (int n=1; i+n*frameInterval<nVert; ++n)
		{
			double r = n*frameInterval;
			//double h = max(i,nVert-i);
			double h = nVert;
			tripD.push_back(Triplet(i, i+n*frameInterval, -exp(-(r*r)/(h*h/4.0))));
			theta_weight += -exp(-(r*r)/(h*h/4.0));
			//tripD.push_back(Triplet(i, i-n*frameInterval, -1.0/((double)n*(double)n+2.0)));
			//theta_weight += -1.0/((double)n*(double)n+2.0);
			//tripR.push_back(Triplet(i, i+n*frameInterval, -exp(-(r*r)/(h*h/4.0))));
		}

		//当前帧
		cout<<"theta_weight:"<<-theta_weight<<endl;
		tripD.push_back(Triplet(i, i, -theta_weight));
		//tripR.push_back(Triplet(i, i, 1.0));

		//R矩阵改为同一帧相邻点的约束（相邻帧约束已经在l0中体现），所以为了保证同一帧中骨骼相邻点平滑，加上约束R
		if (i%10== 0)
		{
			//如果是该帧所在块的第一个点
			//tripR.push_back(Triplet(i,i,1.0));
			//tripR.push_back(Triplet(i,i+1,-1.0));
		}
		else if ((i+1)%10 == 0)
		{
			//如果是该帧所在块的最后一个点
			//tripR.push_back(Triplet(i,i-1,-1.0));
			//tripR.push_back(Triplet(i,i,1.0));
		}
		else
		{
			tripR.push_back(Triplet(i,i-1,-1.0));
			tripR.push_back(Triplet(i,i,2.0));
			tripR.push_back(Triplet(i,i+1,-1.0));
		}



		//各点的矩阵pInit、pVec
		SkeletonPoint sp = skeleton.at(i);
		pInit(i, 0) = sp.getX();
		pInit(i, 1) = sp.getY();
		pInit(i, 2) = sp.getZ();

		pVec(i, 0) = sp.getX();
		pVec(i, 1) = sp.getY();
		pVec(i, 2) = sp.getZ();

		//单位矩阵I
		tripI[i] = Triplet(i, i, 1.0);
	}
	SpMat D(nVert, nVert);
	D.setFromTriplets(tripD.begin(), tripD.end());
	SpMat I(nVert, nVert);
	I.setFromTriplets(tripI.begin(), tripI.end());

	SpMat R(nVert, nVert);
	R.setFromTriplets(tripR.begin(), tripR.end());

	//求解最优化问题
	double lambda = 0.5;
	double alpha  = 2.0;
	double beta   = 0.0001;
	double bmax   = 0.1;
	double mu     = 1.414;

	Matrix dlt(nVert, 3);

	while(beta < bmax) {
		// 阶段一：固定p，求解dlt (shrinkage operator)
		printf("solve sub-problem for delta\n");
		Matrix y = D * pVec;
		for(int i=0; i<nVert; i++) {
			
			dlt(i, 0) = 0.0;
			for(int d=0; d<3; d++) {
				dlt(i, 0) += y(i, d) * y(i, d);
			}

			if(dlt(i, 0) < lambda / beta) {
				dlt(i, 0) = 0.0;
			}

			dlt(i, 1) = dlt(i, 0);
			dlt(i, 2) = dlt(i, 0);
			
			
			/*
			dlt(i, 0) = 0.0;
			for(int d=0; d<3; d++) {
				dlt(i, d) = y(i, d);
			}
			
			if((dlt(i, 0)*dlt(i, 0)+dlt(i, 1)*dlt(i, 1)+dlt(i, 2)*dlt(i, 2)) < lambda / beta) {
				dlt(i, 0) = 0.0;
				dlt(i, 1) = 0.0;
				dlt(i, 2) = 0.0;
			}
			*/
			
		}

		// 阶段二：固定dlt，求解p (linear system)
		printf("solve sub-problem for points\n");
		SpMat  A = I  /*+ alpha * R.transpose() * R*/+beta * D.transpose() * D;
		Matrix b = pInit + beta * D.transpose() * dlt;

		Eigen::SparseLU<Eigen::SparseMatrix<double> > solver;
		solver.analyzePattern(A);
		solver.factorize(A);
		cout<<solver.info()<<endl;
		cout<<solver.lastErrorMessage()<<std::endl;
		if(solver.info() != Eigen::Success)
		{
			cout<<"error after factorize"<<endl;
		}
		pVec = solver.solve(b);
		cout<<solver.info()<<endl;
		cout<<solver.lastErrorMessage()<<std::endl;
		if(solver.info() != Eigen::Success)
		{
			cout<<"error after solve"<<endl;
		}
		
		// 更新参数
		beta  *= mu;
		//alpha *= 0.707;
	}
	cout<<"optimization finished"<<endl;

	//返回优化后的点
	vector<SkeletonPoint> reSkeleton;
	for (int i=0; i<nVert; ++i)
	{
		reSkeleton.push_back(SkeletonPoint(pVec(i, 0), pVec(i, 1), pVec(i, 2)));
	}

	return reSkeleton;
}