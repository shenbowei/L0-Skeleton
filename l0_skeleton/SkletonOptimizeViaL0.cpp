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
	
	//����ϵ������D,����ľ���pInit��pVec,��λ����I
	vector<Triplet> tripD;
	Matrix pInit(nVert, 3);
	Matrix pVec(nVert, 3);
	vector<Triplet> tripI(nVert);
	//����Լ������R
	vector<Triplet> tripR;
	vector<Triplet> tripR_Joint;
	for (int i=0; i<nVert ; ++i)
	{
		//ϡ�����D
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
			//��һ֡
			tripD.push_back(Triplet(i, i, 1.0));
			tripD.push_back(Triplet(i, nextIndex, -1.0));
			//tripR.push_back(Triplet(i, i, 1.0));
			//tripR.push_back(Triplet(i, nextIndex, -1.0));
		}
		else if(nextIndex==i)
		{
			//���һ֡
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

		//R�����Ϊͬһ֡���ڵ��Լ��������֡Լ���Ѿ���l0�����֣�������Ϊ�˱�֤ͬһ֡�й������ڵ�ƽ��������Լ��R
		if (i%10 == 0)
		{
			//����Ǹ�֡���ڿ�ĵ�һ����
			//tripR.push_back(Triplet(i,i,1.0));
			//tripR.push_back(Triplet(i,i+1,-1.0));
		}
		else if ((i+1)%10 == 0)
		{
			//����Ǹ�֡���ڿ�����һ����
			//tripR.push_back(Triplet(i,i-1,-1.0));
			//tripR.push_back(Triplet(i,i,1.0));
		}
		else
		{
			tripR.push_back(Triplet(i,i-1,-1.0));
			tripR.push_back(Triplet(i,i,2.0));
			tripR.push_back(Triplet(i,i+1,-1.0));
		}

		//����joint���Լ��
		//˫�ۼ��joint��
		if(i%50==9)
		{
			/*
			//�������һ��
			tripR_Joint.push_back(Triplet(i,i,-1.0));
			//�ұ�����һ��
			tripR_Joint.push_back(Triplet(i,i+10,-1.0));
			//�Ǹɵĵ�����
			tripR_Joint.push_back(Triplet(i,i+33,2.0));
			*/
			tripR_Joint.push_back(Triplet(i,i,1.0));
			tripR_Joint.push_back(Triplet(i,i+10,-1.0));
		}
		else if(i%50==19)
		{
			/*
			//�������һ��
			tripR_Joint.push_back(Triplet(i,i,-1.0));
			//�ұ�����һ��
			tripR_Joint.push_back(Triplet(i,i-10,-1.0));
			//�Ǹɵĵ�����
			tripR_Joint.push_back(Triplet(i,i+23,2.0));
			*/
			tripR_Joint.push_back(Triplet(i,i,1.0));
			tripR_Joint.push_back(Triplet(i,i-10,-1.0));
		}
		else if(i%50==42)
		{
			
			//�������һ��
			tripR_Joint.push_back(Triplet(i,i-33,-1.0));
			//�ұ�����һ��
			tripR_Joint.push_back(Triplet(i,i-23,-1.0));
			//�Ǹɵĵ�����
			tripR_Joint.push_back(Triplet(i,i,2.0));
			
		}
		//���ȼ��joint��
		else if(i%50==29)
		{
			/*
			//��������һ��
			tripR_Joint.push_back(Triplet(i,i,-1.0));
			//��������һ��
			tripR_Joint.push_back(Triplet(i,i+10,-1.0));
			//�Ǹɵ����һ��
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
			//��������һ��
			tripR_Joint.push_back(Triplet(i,i-10,-1.0));
			//��������һ��
			tripR_Joint.push_back(Triplet(i,i,-1.0));
			//�Ǹɵ����һ��
			tripR_Joint.push_back(Triplet(i,i+10,2.0));
			*/
			tripR_Joint.push_back(Triplet(i,i,1.0));
			tripR_Joint.push_back(Triplet(i,i-10,-1.0));

		}
		else if(i%50==49)
		{

			//��������һ��
			tripR_Joint.push_back(Triplet(i,i-20,-1.0));
			//��������һ��
			tripR_Joint.push_back(Triplet(i,i-10,-1.0));
			//�Ǹɵ����һ��
			tripR_Joint.push_back(Triplet(i,i,2.0));

		}


		//����ľ���pInit��pVec
		SkeletonPoint sp = skeleton.at(i);
		pInit(i, 0) = sp.getX();
		pInit(i, 1) = sp.getY();
		pInit(i, 2) = sp.getZ();

		pVec(i, 0) = sp.getX();
		pVec(i, 1) = sp.getY();
		pVec(i, 2) = sp.getZ();

		//��λ����I
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

	//������Ż�����
	double lambda = 0.003*5.0;

	double alpha    = 2.0;
	double beta     = 2.0;
	double gamma    = 0.001;
	double gmax     = 100.0;
	double mu_gamma = 1.414;

	Matrix dlt(nVert, 3);

	while(gamma < gmax) {
		// �׶�һ���̶�p�����dlt (shrinkage operator)
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

		// �׶ζ����̶�dlt�����p (linear system)
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
		
		// ���²���
		gamma  *= mu_gamma;
		//alpha *= 0.707;
	}
	cout<<"optimization finished"<<endl;

	//�����Ż���ĵ�
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
	
	//����ϵ������D,����ľ���pInit��pVec,��λ����I
	vector<Triplet> tripD;
	Matrix pInit(nVert, 3);
	Matrix pVec(nVert, 3);
	vector<Triplet> tripI(nVert);
	//����Լ������R
	vector<Triplet> tripR;
	for (int i=0; i<nVert ; ++i)
	{
		//����ϡ�����D
		double theta_weight = 0.0;
		//����֮ǰ�ĸ�֡
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

		//����֮��ĸ�֡
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

		//��ǰ֡
		cout<<"theta_weight:"<<-theta_weight<<endl;
		tripD.push_back(Triplet(i, i, -theta_weight));
		//tripR.push_back(Triplet(i, i, 1.0));

		//R�����Ϊͬһ֡���ڵ��Լ��������֡Լ���Ѿ���l0�����֣�������Ϊ�˱�֤ͬһ֡�й������ڵ�ƽ��������Լ��R
		if (i%10== 0)
		{
			//����Ǹ�֡���ڿ�ĵ�һ����
			//tripR.push_back(Triplet(i,i,1.0));
			//tripR.push_back(Triplet(i,i+1,-1.0));
		}
		else if ((i+1)%10 == 0)
		{
			//����Ǹ�֡���ڿ�����һ����
			//tripR.push_back(Triplet(i,i-1,-1.0));
			//tripR.push_back(Triplet(i,i,1.0));
		}
		else
		{
			tripR.push_back(Triplet(i,i-1,-1.0));
			tripR.push_back(Triplet(i,i,2.0));
			tripR.push_back(Triplet(i,i+1,-1.0));
		}



		//����ľ���pInit��pVec
		SkeletonPoint sp = skeleton.at(i);
		pInit(i, 0) = sp.getX();
		pInit(i, 1) = sp.getY();
		pInit(i, 2) = sp.getZ();

		pVec(i, 0) = sp.getX();
		pVec(i, 1) = sp.getY();
		pVec(i, 2) = sp.getZ();

		//��λ����I
		tripI[i] = Triplet(i, i, 1.0);
	}
	SpMat D(nVert, nVert);
	D.setFromTriplets(tripD.begin(), tripD.end());
	SpMat I(nVert, nVert);
	I.setFromTriplets(tripI.begin(), tripI.end());

	SpMat R(nVert, nVert);
	R.setFromTriplets(tripR.begin(), tripR.end());

	//������Ż�����
	double lambda = 0.5;
	double alpha  = 2.0;
	double beta   = 0.0001;
	double bmax   = 0.1;
	double mu     = 1.414;

	Matrix dlt(nVert, 3);

	while(beta < bmax) {
		// �׶�һ���̶�p�����dlt (shrinkage operator)
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

		// �׶ζ����̶�dlt�����p (linear system)
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
		
		// ���²���
		beta  *= mu;
		//alpha *= 0.707;
	}
	cout<<"optimization finished"<<endl;

	//�����Ż���ĵ�
	vector<SkeletonPoint> reSkeleton;
	for (int i=0; i<nVert; ++i)
	{
		reSkeleton.push_back(SkeletonPoint(pVec(i, 0), pVec(i, 1), pVec(i, 2)));
	}

	return reSkeleton;
}