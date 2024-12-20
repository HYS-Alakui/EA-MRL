#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"

void QPacking::upper_crossover(CIndividual& upper_fathIndiv, CIndividual& upper_mothIndiv, CIndividual& upper_chIndiv1, CIndividual& upper_chIndiv2)//����4�����󣺸��ף�ĸ�ף��Ӵ�1���Ӵ�2
{
	//cout << "���׵Ĺ���ͻ���������Ϣ��" << endl;
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

	//cout << "ĸ�׵Ĺ���ͻ�����Ϣ��" << endl;
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
	vector <CChromosome>().swap(upper_chIndiv1.v_chromosome1);//����Ӵ�����
	vector <CChromosome>().swap(upper_chIndiv2.v_chromosome1);//����Ӵ�����
	////step1�������������֣�����˳�򽻲�
	bool bt;
	int index;
	int cutpoint1, cutpoint2;//���������е㣻
	int temp1, operNo;
	cutpoint1 = rand() % number_of_jobs * number_of_operations;
	cutpoint2 = rand() % number_of_jobs * number_of_operations;
	while (cutpoint1 == cutpoint2)//�������е���ͬ
	{
		cutpoint1 = rand() % number_of_jobs * number_of_operations;//�����²���һ���е�2
	}
	if (cutpoint1 > cutpoint2)//���е�1���е�2����
	{
		temp1 = cutpoint1;
		cutpoint1 = cutpoint2;//����л�������
		cutpoint2 = temp1;
	}
	//cout << "cutpoint1 = " << cutpoint1 << endl;
	//cout << "cutpoint2 = " << cutpoint2 << endl;
	for (int j = 0; j < number_of_jobs * number_of_operations; j++)//�Ӵ������ʼ����һ��ʼ���ȴ��������ٶԶ����factory_numberȫ����ֵΪ0
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
	////���� �ǽ���ĸ �����е� �������ҵ ֱ�ӿ��� ���Ӵ�1���Ӵ�2����ͬλ��
	index = cutpoint1;
	vector<int> v_store_operation;
	vector<int>().swap(v_store_operation);
	v_store_operation.push_back(0);//�ȷ���һ��0���������Ƚϣ�����һ��ʼ�ǿյĲ�����size()ѭ��
	for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	{
		int times = 0;
		operNo = upper_mothIndiv.v_chromosome1[j].operation_number;//��ĸ����ÿ����ҵ���Ӵ�1���е���ҵ�Ƚ�;
		//cout << "operNo = " << operNo << endl;
		bt = false;
		//compare1
		for (int k = 0; k < cutpoint1; k++)//����ǰĸ����ҵ���Ӵ�1����[number_of_jobs,cutpoint3)��ҵ�Ƚ�
		{
			if (operNo == upper_chIndiv1.v_chromosome1[k].operation_number)//������һ����ͬ�ģ��ۼ����������ظ�����
			{
				times = times + 1;//��¼��job�Ĺ�������˵��ظ�����
				//cout << "times1 = " << times << endl;//times1,times2,times3��������һ����ֵ��ظ�
			}
		}
		//compare2
		for (int k = cutpoint2; k < number_of_jobs * number_of_operations; k++)
		{
			if (operNo == upper_chIndiv1.v_chromosome1[k].operation_number)
			{
				times = times + 1;//��¼��job�Ĺ����ڶ˵��ظ�����
				//cout << "times2 = " << times << endl;
			}
		}
		//compare3
		for (int k = 0; k < v_store_operation.size(); k++)//����Ҫ�͹̶������˱Ƚϣ���Ҫ��ղ������Щ����Ƚ�
		{
			if (operNo == v_store_operation[k])
			{
				times = times + 1;
				//cout << "times3 = " << times << endl;
			}
		}
		//�ж�
		if (times == number_of_operations)//���ù����Ѿ�����3��
		{
			bt = true;
			continue;//Ҫcontinue,������һ��job�ıȽ�
		}
		//����
		if (bt == false)//��һֱfalse��δ����true��˵���ù���δ����3��
		{
			upper_chIndiv1.v_chromosome1[index].operation_number = operNo;
			v_store_operation.push_back(operNo);
			//cout << "upper_chIndiv1.v_chromosome[index].operation_number=" << upper_chIndiv1.v_chromosome1[index].operation_number << endl;
			index++;//��ʱԭcutpoint1�Ѿ�������ˣ���++�����������һ��λ��
		}
	}//��������Ӵ�1[cutpoint3,cutpoint4)λ����ҵ����䣬��ĸ�׻�á�
	//system("pause");

	index = cutpoint1;
	vector<int>().swap(v_store_operation);
	v_store_operation.push_back(0);//�ȷ���һ��0���������Ƚϣ�����һ��ʼ�ǿյĲ�����size()ѭ��
	for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	{
		int times = 0;
		operNo = upper_fathIndiv.v_chromosome1[j].operation_number;//��ĸ����ÿ����ҵ���Ӵ�1���е���ҵ�Ƚ�;
		//cout << "operNo = " << operNo << endl;
		bt = false;
		//compare1
		for (int k = 0; k < cutpoint1; k++)//����ǰĸ����ҵ���Ӵ�1����[number_of_jobs,cutpoint3)��ҵ�Ƚ�
		{
			if (operNo == upper_chIndiv2.v_chromosome1[k].operation_number)//������һ����ͬ�ģ��ۼ����������ظ�����
			{
				times = times + 1;//��¼��job�Ĺ�������˵��ظ�����
				//cout << "times1 = " << times << endl;//times1,times2,times3��������һ����ֵ��ظ�
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
		for (int k = 0; k < v_store_operation.size(); k++)//����Ҫ�͹̶������˱Ƚϣ���Ҫ��ղ������Щ����Ƚ�
		{
			if (operNo == v_store_operation[k])
			{
				times = times + 1;
				//cout << "times3 = " << times << endl;
			}
		}
		//�ж�
		if (times == number_of_operations)//���ù����Ѿ�����3��
		{
			bt = true;
			continue;//Ҫcontinue,������һ��job�ıȽ�
		}
		//����
		if (bt == false)//��һֱfalse��δ����true��˵���ù���δ����3��
		{
			upper_chIndiv2.v_chromosome1[index].operation_number = operNo;
			v_store_operation.push_back(operNo);
			//cout << "upper_chIndiv2.v_chromosome1[index].operation_number=" << upper_chIndiv2.v_chromosome1[index].operation_number << endl;
			index++;//��ʱԭcutpoint1�Ѿ�������ˣ���++�����������һ��λ��
		}
	}//��������Ӵ�2[cutpoint3,cutpoint4)λ����ҵ����䣬�Ӹ��׻�á�

	////���乤������������job����Ϣ�͹���˳����Ϣ
	for (int k = 0; k < number_of_jobs * number_of_operations; k++)
	{
		upper_chIndiv1.v_chromosome1[k].job_number = upper_chIndiv1.v_chromosome1[k].operation_number;
		upper_chIndiv2.v_chromosome1[k].job_number = upper_chIndiv2.v_chromosome1[k].operation_number;
	}
	for (int k = 0; k < number_of_jobs; k++)//�ж���ÿ��job�ĵڼ�������
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
	for (int k = 0; k < number_of_jobs; k++)//�ж���ÿ��job�ĵڼ�������
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
	//cout<<"����������Ӵ��Ĺ���������"<<endl;
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


	////step2:�����������֣������ַ���
	for (int j = 0; j < number_of_jobs * number_of_operations; j++)//�Ӵ������ʼ����һ��ʼ���ȴ��������ٶԶ����machine_numberȫ����ֵΪ0
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
		//�������һ��0-1����������=0����ȡ���׻���������=1����ȡĸ�׻���
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
		//�������һ��0-1����������=0����ȡ���׻���������=1����ȡĸ�׻���
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
	////�������������job��Ϣ
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
	//cout << "����������Ӵ��Ļ���������" << endl;
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