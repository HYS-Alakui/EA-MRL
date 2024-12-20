#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"

void QPacking::lower_mutate(CIndividual& t, double rate)//对个体进行变异，rate是变异率；t是传进来的child1对象，在evovle中
{
	//cout << "变异前子代的排样序列：" << endl;
	//for (int n = 0; n < number_of_jobs; n++)
	//{
	//	cout << t.v_chromosome2[n].job_number << " ";
	//}
	//cout << endl;

	if (rand() / (RAND_MAX * 1.0) <= rate)   //两点交换
	{
		int cutpoint3, cutpoint4;
		int jobNo1, jobNo2;
		cutpoint3 = rand() % number_of_jobs;
		cutpoint4 = rand() % number_of_jobs;
		while (cutpoint3 == cutpoint4)
		{
			cutpoint4 = rand() % number_of_jobs;
		}
		jobNo1 = t.v_chromosome2[cutpoint3].job_number;
		jobNo2 = t.v_chromosome2[cutpoint4].job_number;
		//cout << "cutpoint3 = " << cutpoint3 << endl;
		//cout << "cutpoint4 = " << cutpoint4 << endl;
		//cout << "jobNo1 = " << jobNo1 << endl;
		//cout << "jobNo2 = " << jobNo2 << endl;
		int temp_job;
		temp_job = t.v_chromosome2[cutpoint3].job_number;
		t.v_chromosome2[cutpoint3].job_number = t.v_chromosome2[cutpoint4].job_number;
		t.v_chromosome2[cutpoint4].job_number = temp_job;
		//cout << "变异后子代的排样序列：" << endl;
		//for (int j = 0; j <number_of_jobs; j++)
		//{
		//	cout << t.v_chromosome2[j].job_number << " ";
		//}
		//cout << endl;
		//system("pause");
	}
	else//不变异
	{
		//cout << "不变异" << endl;
		t = t;
	}

	//cout << "变异后子代个体的下层向量：" << endl;
	//for (int j = 0; j < number_of_jobs; j++)
	//{
	//	cout << t.v_chromosome2[j].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
}