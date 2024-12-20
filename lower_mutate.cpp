#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"

void QPacking::lower_mutate(CIndividual& t, double rate)//�Ը�����б��죬rate�Ǳ����ʣ�t�Ǵ�������child1������evovle��
{
	//cout << "����ǰ�Ӵ����������У�" << endl;
	//for (int n = 0; n < number_of_jobs; n++)
	//{
	//	cout << t.v_chromosome2[n].job_number << " ";
	//}
	//cout << endl;

	if (rand() / (RAND_MAX * 1.0) <= rate)   //���㽻��
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
		//cout << "������Ӵ����������У�" << endl;
		//for (int j = 0; j <number_of_jobs; j++)
		//{
		//	cout << t.v_chromosome2[j].job_number << " ";
		//}
		//cout << endl;
		//system("pause");
	}
	else//������
	{
		//cout << "������" << endl;
		t = t;
	}

	//cout << "������Ӵ�������²�������" << endl;
	//for (int j = 0; j < number_of_jobs; j++)
	//{
	//	cout << t.v_chromosome2[j].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
}