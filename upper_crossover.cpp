#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"

void QPacking::upper_crossover(CIndividual& upper_fathIndiv, CIndividual& upper_mothIndiv, CIndividual& upper_chIndiv1, CIndividual& upper_chIndiv2)//传入4个对象：父亲，母亲，子代1，子代2
{
	//cout << "父亲的工序和机器序列信息：" << endl;
	//for (int n = 0; n < number_of_jobs * number_of_operations; n++)
	//{
	//	cout << upper_fathIndiv.v_chromosome1[n].operation_number << " ";
	//}
	//cout << endl;
	//for (int n = number_of_jobs * number_of_operations; n < upper_fathIndiv.v_chromosome1.size(); n++)
	//{
	//	cout << upper_fathIndiv.v_chromosome1[n].machine_number << " ";
	//}
	//cout << endl;

	//cout << "母亲的工序和机器信息：" << endl;
	//for (int n = 0; n < number_of_jobs * number_of_operations; n++)
	//{
	//	cout << upper_mothIndiv.v_chromosome1[n].operation_number << " ";
	//}
	//cout << endl;
	//for (int n = number_of_jobs * number_of_operations; n < upper_mothIndiv.v_chromosome1.size(); n++)
	//{
	//	cout << upper_mothIndiv.v_chromosome1[n].machine_number << " ";
	//}
	//cout << endl;
	//system("pause");

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	vector <CChromosome>().swap(upper_chIndiv1.v_chromosome1);//清空子代容器
	vector <CChromosome>().swap(upper_chIndiv2.v_chromosome1);//清空子代容器
	////step1：工序向量部分，采用顺序交叉
	bool bt;
	int index;
	int cutpoint1, cutpoint2;//工序序列切点；
	int temp1, operNo;
	cutpoint1 = rand() % number_of_jobs * number_of_operations;
	cutpoint2 = rand() % number_of_jobs * number_of_operations;
	while (cutpoint1 == cutpoint2)//若两个切点相同
	{
		cutpoint1 = rand() % number_of_jobs * number_of_operations;//则重新产生一个切点2
	}
	if (cutpoint1 > cutpoint2)//若切点1在切点2后面
	{
		temp1 = cutpoint1;
		cutpoint1 = cutpoint2;//则进行互换操作
		cutpoint2 = temp1;
	}
	//cout << "cutpoint1 = " << cutpoint1 << endl;
	//cout << "cutpoint2 = " << cutpoint2 << endl;
	for (int j = 0; j < number_of_jobs * number_of_operations; j++)//子代个体初始化，一开始得先创建对象，再对对象的factory_number全部赋值为0
	{
		CChromosome	tt1;
		tt1.operation_number = 0;
		upper_chIndiv1.v_chromosome1.push_back(tt1);
		CChromosome	tt2;
		tt2.operation_number = 0;
		upper_chIndiv2.v_chromosome1.push_back(tt2);
	}
	for (int j = 0; j < cutpoint1; j++)
	{
		operNo = upper_fathIndiv.v_chromosome1[j].operation_number;
		//cout << "operNo = " << operNo << endl;
		upper_chIndiv1.v_chromosome1[j].operation_number = operNo;
		//cout << "upper_chIndiv1.v_chromosome[j].operation_number = " << upper_chIndiv1.v_chromosome1[j].operation_number << endl;
		operNo = upper_mothIndiv.v_chromosome1[j].operation_number;
		//cout << "operNo = " << operNo << endl;
		upper_chIndiv2.v_chromosome1[j].operation_number = operNo;
		//cout << "upper_chIndiv2.v_chromosome[j].operation_number = " << upper_chIndiv2.v_chromosome1[j].operation_number << endl;
	}
	for (int j = cutpoint2; j < number_of_jobs * number_of_operations; j++)
	{
		operNo = upper_fathIndiv.v_chromosome1[j].operation_number;
		//cout << "operNo = " << operNo << endl;
		upper_chIndiv1.v_chromosome1[j].operation_number = operNo;
		//cout << "upper_chIndiv1.v_chromosome1[j].operation_number = " << upper_chIndiv1.v_chromosome1[j].operation_number << endl;
		operNo = upper_mothIndiv.v_chromosome1[j].operation_number;
		//cout << "operNo = " << operNo << endl;
		upper_chIndiv2.v_chromosome1[j].operation_number = operNo;
		//cout << "upper_chIndiv2.v_chromosome[j].operation_number = " << upper_chIndiv2.v_chromosome1[j].operation_number << endl;
	}
	////以上 是将父母 两个切点 两侧的作业 直接拷贝 给子代1，子代2的相同位置
	index = cutpoint1;
	vector<int> v_store_operation;
	vector<int>().swap(v_store_operation);
	v_store_operation.push_back(0);//先放入一个0，方便后面比较，否则一开始是空的不能用size()循环
	for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	{
		int times = 0;
		operNo = upper_mothIndiv.v_chromosome1[j].operation_number;//将母亲中每个作业与子代1现有的作业比较;
		//cout << "operNo = " << operNo << endl;
		bt = false;
		//compare1
		for (int k = 0; k < cutpoint1; k++)//将当前母亲作业与子代1现有[number_of_jobs,cutpoint3)作业比较
		{
			if (operNo == upper_chIndiv1.v_chromosome1[k].operation_number)//若存在一个相同的，累加这个工序的重复次数
			{
				times = times + 1;//记录该job的工序在左端的重复次数
				//cout << "times1 = " << times << endl;//times1,times2,times3区分在哪一块出现的重复
			}
		}
		//compare2
		for (int k = cutpoint2; k < number_of_jobs * number_of_operations; k++)
		{
			if (operNo == upper_chIndiv1.v_chromosome1[k].operation_number)
			{
				times = times + 1;//记录该job的工序在端的重复次数
				//cout << "times2 = " << times << endl;
			}
		}
		//compare3
		for (int k = 0; k < v_store_operation.size(); k++)//不仅要和固定的两端比较，还要与刚插入的那些工序比较
		{
			if (operNo == v_store_operation[k])
			{
				times = times + 1;
				//cout << "times3 = " << times << endl;
			}
		}
		//判断
		if (times == number_of_operations)//若该工序已经出现3次
		{
			bt = true;
			continue;//要continue,进行下一个job的比较
		}
		//抉择
		if (bt == false)//若一直false，未出现true，说明该工序还未出现3次
		{
			upper_chIndiv1.v_chromosome1[index].operation_number = operNo;
			v_store_operation.push_back(operNo);
			//cout << "upper_chIndiv1.v_chromosome[index].operation_number=" << upper_chIndiv1.v_chromosome1[index].operation_number << endl;
			index++;//此时原cutpoint1已经被填充了，故++，继续填充下一个位置
		}
	}//以上完成子代1[cutpoint3,cutpoint4)位置作业的填充，从母亲获得。
	//system("pause");

	index = cutpoint1;
	vector<int>().swap(v_store_operation);
	v_store_operation.push_back(0);//先放入一个0，方便后面比较，否则一开始是空的不能用size()循环
	for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	{
		int times = 0;
		operNo = upper_fathIndiv.v_chromosome1[j].operation_number;//将母亲中每个作业与子代1现有的作业比较;
		//cout << "operNo = " << operNo << endl;
		bt = false;
		//compare1
		for (int k = 0; k < cutpoint1; k++)//将当前母亲作业与子代1现有[number_of_jobs,cutpoint3)作业比较
		{
			if (operNo == upper_chIndiv2.v_chromosome1[k].operation_number)//若存在一个相同的，累加这个工序的重复次数
			{
				times = times + 1;//记录该job的工序在左端的重复次数
				//cout << "times1 = " << times << endl;//times1,times2,times3区分在哪一块出现的重复
			}
		}
		//compare2
		for (int k = cutpoint2; k < number_of_jobs * number_of_operations; k++)
		{
			if (operNo == upper_chIndiv2.v_chromosome1[k].operation_number)
			{
				times = times + 1;
				//cout << "times2 = " << times << endl;
			}
		}
		//compare3
		for (int k = 0; k < v_store_operation.size(); k++)//不仅要和固定的两端比较，还要与刚插入的那些工序比较
		{
			if (operNo == v_store_operation[k])
			{
				times = times + 1;
				//cout << "times3 = " << times << endl;
			}
		}
		//判断
		if (times == number_of_operations)//若该工序已经出现3次
		{
			bt = true;
			continue;//要continue,进行下一个job的比较
		}
		//抉择
		if (bt == false)//若一直false，未出现true，说明该工序还未出现3次
		{
			upper_chIndiv2.v_chromosome1[index].operation_number = operNo;
			v_store_operation.push_back(operNo);
			//cout << "upper_chIndiv2.v_chromosome1[index].operation_number=" << upper_chIndiv2.v_chromosome1[index].operation_number << endl;
			index++;//此时原cutpoint1已经被填充了，故++，继续填充下一个位置
		}
	}//以上完成子代2[cutpoint3,cutpoint4)位置作业的填充，从父亲获得。

	////补充工序序列向量的job号信息和工序顺序信息
	for (int k = 0; k < number_of_jobs * number_of_operations; k++)
	{
		upper_chIndiv1.v_chromosome1[k].job_number = upper_chIndiv1.v_chromosome1[k].operation_number;
		upper_chIndiv2.v_chromosome1[k].job_number = upper_chIndiv2.v_chromosome1[k].operation_number;
	}
	for (int k = 0; k < number_of_jobs; k++)//判断是每个job的第几道工序
	{
		int current_job_number = k + 1;
		int count = 0;
		for (int c = 0; c < number_of_jobs * number_of_operations; c++)
		{
			if (current_job_number == upper_chIndiv1.v_chromosome1[c].job_number)
			{
				count = count + 1;
				upper_chIndiv1.v_chromosome1[c].operation_index = count;
			}
			continue;
		}
	}
	for (int k = 0; k < number_of_jobs; k++)//判断是每个job的第几道工序
	{
		int current_job_number = k + 1;
		int count = 0;
		for (int c = 0; c < number_of_jobs * number_of_operations; c++)
		{
			if (current_job_number == upper_chIndiv2.v_chromosome1[c].job_number)
			{
				count = count + 1;
				upper_chIndiv2.v_chromosome1[c].operation_index = count;
			}
			continue;
		}
	}
	//cout<<"交叉后两个子代的工序向量："<<endl;
	//for (int k = 0; k < number_of_jobs * number_of_operations; k++)
	//{
	//	cout << upper_chIndiv1.v_chromosome1[k].operation_number << " ";
	//}
	//cout << endl;
	//for (int k = 0; k < number_of_jobs * number_of_operations; k++)
	//{
	//	cout << upper_chIndiv1.v_chromosome1[k].job_number << " ";
	//}
	//cout << endl;
	//for (int k = 0; k < number_of_jobs * number_of_operations; k++)
	//{
	//	cout << upper_chIndiv1.v_chromosome1[k].operation_index << " ";
	//}
	//cout << endl << endl;
	//for (int k = 0; k < number_of_jobs * number_of_operations; k++)
	//{
	//	cout << upper_chIndiv2.v_chromosome1[k].operation_number << " ";
	//}
	//cout << endl;
	//for (int k = 0; k < number_of_jobs * number_of_operations; k++)
	//{
	//	cout << upper_chIndiv2.v_chromosome1[k].job_number << " ";
	//}
	//cout << endl;
	//for (int k = 0; k < number_of_jobs * number_of_operations; k++)
	//{
	//	cout << upper_chIndiv2.v_chromosome1[k].operation_index << " ";
	//}
	//cout << endl;
	//system("pause");


	////step2:机器向量部分，采用字符串
	for (int j = 0; j < number_of_jobs * number_of_operations; j++)//子代个体初始化，一开始得先创建对象，再对对象的machine_number全部赋值为0
	{
		CChromosome	tt3;
		tt3.machine_number = 0;
		upper_chIndiv1.v_chromosome1.push_back(tt3);
		CChromosome	tt4;
		tt4.machine_number = 0;
		upper_chIndiv2.v_chromosome1.push_back(tt4);
	}
	for (int k = number_of_jobs * number_of_operations; k < upper_chIndiv1.v_chromosome1.size(); k++)
	{
		//随机产生一个0-1数，若该数=0，则取父亲基因，若该数=1，则取母亲基因。
		int rand_m_number1 = rand() % 2;
		//cout << "rand_number1 = " << rand_m_number1 << endl;
		if (rand_m_number1 == 0)
		{
			upper_chIndiv1.v_chromosome1[k].machine_number = upper_fathIndiv.v_chromosome1[k].machine_number;
		}
		else if (rand_m_number1 == 1)
		{
			upper_chIndiv1.v_chromosome1[k].machine_number = upper_mothIndiv.v_chromosome1[k].machine_number;
		}
	}
	for (int k = number_of_jobs * number_of_operations; k < upper_chIndiv2.v_chromosome1.size(); k++)
	{
		//随机产生一个0-1数，若该数=0，则取父亲基因，若该数=1，则取母亲基因。
		int rand_m_number2 = rand() % 2;
		//cout << "rand_number2 = " << rand_m_number2 << endl;
		if (rand_m_number2 == 0)
		{
			upper_chIndiv2.v_chromosome1[k].machine_number = upper_fathIndiv.v_chromosome1[k].machine_number;
		}
		else if (rand_m_number2 == 1)
		{
			upper_chIndiv2.v_chromosome1[k].machine_number = upper_mothIndiv.v_chromosome1[k].machine_number;
		}
	}
	//cout << endl << endl;
	////补充机器向量的job信息
	int dis = 0;
	for (int j = 0; j < number_of_jobs; j++)
	{
		for (int o = 0; o < number_of_operations; o++)
		{
			upper_chIndiv1.v_chromosome1[o + dis + number_of_jobs * number_of_operations].job_number = j + 1;
			upper_chIndiv2.v_chromosome1[o + dis + number_of_jobs * number_of_operations].job_number = j + 1;
		}
		dis = dis + number_of_operations;
	}
	//cout << "交叉后两个子代的机器向量：" << endl;
	//for (int k = number_of_jobs * number_of_operations; k < upper_chIndiv1.v_chromosome1.size(); k++)
	//{
	//	cout << upper_chIndiv1.v_chromosome1[k].machine_number << " ";
	//}
	//cout << endl;
	//for (int k = number_of_jobs * number_of_operations; k < upper_chIndiv1.v_chromosome1.size(); k++)
	//{
	//	cout << upper_chIndiv1.v_chromosome1[k].job_number << " ";
	//}
	//cout << endl;
	//for (int k = number_of_jobs * number_of_operations; k < upper_chIndiv2.v_chromosome1.size(); k++)
	//{
	//	cout << upper_chIndiv2.v_chromosome1[k].machine_number << " ";
	//}
	//cout << endl;
	//for (int k = number_of_jobs * number_of_operations; k < upper_chIndiv2.v_chromosome1.size(); k++)
	//{
	//	cout << upper_chIndiv2.v_chromosome1[k].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
}