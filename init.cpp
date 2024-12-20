#include "Headfile.h"
#include "Qpacking.h"
#include "Item.h"
#include "Chromosome.h"
#include "Individual.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>

void QPacking::init_parameters()//��ʼ������
{
	number_of_objectives = 2;//Ŀ������
	upper_number_of_individuals = 300;//�ϲ���Ⱥ��ģ300
	number_of_subpop = 10;//����Ⱥ��Ŀ10
	lower_number_of_individuals = upper_number_of_individuals / number_of_subpop;
	//cout << "lower_number_of_individuals = " << lower_number_of_individuals << endl;
	outer_iteration_count_max = 100;//100
	outer_iteration_count;

	Discount_Factor = 0.7;//�ۿ�����0.7
	State_Number = 4;//״̬��
	Action_Number = 7;//�ж���

	State_Current = 1;//��ʼ״̬
	Action_Current = 0;//��ʼ�ж�
	State_Next1 = 0;//��һ��״̬
	State_Current1 = 1;//��ʼ״̬
	Action_Current1 = 0;//��ʼ�ж�
	State_Next1 = 0;//��һ��״̬
	State_Current2 = 1;//��ʼ״̬
	Action_Current2 = 1;//��ʼ�ж�
	State_Next2 = 0;//��һ��״̬
	State_Current3 = 1;//��ʼ״̬
	Action_Current3 = 2;//��ʼ�ж�
	State_Next3 = 0;//��һ��״̬
	State_Current4 = 1;//��ʼ״̬
	Action_Current4 = 3;//��ʼ�ж�
	State_Next4 = 0;//��һ��״̬
	State_Current5 = 1;//��ʼ״̬
	Action_Current5 = 4;//��ʼ�ж�
	State_Next5 = 0;//��һ��״̬
	State_Current6 = 1;//��ʼ״̬
	Action_Current6 = 5;//��ʼ�ж�
	State_Next6 = 0;//��һ��״̬
	State_Current7 = 1;//��ʼ״̬
	Action_Current7 = 6;//��ʼ�ж�
	State_Next7 = 0;//��һ��״̬


	//��ʼ��Q��
	for (int i = 0; i < State_Number; i++)
	{
		for (int j = 0; j < Action_Number; j++)
		{
			Q_TABLE[i][j] = 0;
		}
	}

	pre_input_alpha = 0.00;
	pre_input_gamma = 0.00;
	pre_total_loss = 0.00;
	now_total_loss = 0.00;
}


void QPacking::generInitPopu(vector<Item>& v_product)//��ʼ����Ⱥ
{
	//cout << "------------1����ʼ����Ⱥ---------" << endl;
	vector <vector<CIndividual>>().swap(v_Chromo);//����swap�����ڴ棬��Ⱥ��ʼ��Ϊ��
	vector <CIndividual>().swap(v_TotalChromo);
	//for (int i = 0; i < 1; i++)//����ϲ㹤���������������ʣ��ӹ�ʱ��Ĺ������ȼӹ�
	//{
	//	//cout << "i = " << i + 1 << endl;
	//	CIndividual T;
	//	Upper_H1(T);
	//	vector <CIndividual> v_subChromo;
	//	vector <CIndividual>().swap(v_subChromo);
	//	////�������Ⱥ�е�ÿ�����壬���ȼ̳еõ��Ĺ����ϲ��������ٵ���randomlower�������õ�һ���²�����
	//	for (int j = 0; j < lower_number_of_individuals; j++)
	//	{
	//		//cout << "j = " << j + 1<< endl;
	//		CIndividual t;
	//		t.sub_no = i + 1;
	//		t.v_chromosome1 = T.v_chromosome1;//����Ⱥ
	//		//cout << "�ϲ�����" << endl;
	//		//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	//		//{
	//		//	cout << t.v_chromosome1[j].operation_number << " ";
	//		//}
	//		//cout << endl;
	//		//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	//		//{
	//		//	cout << t.v_chromosome1[j].operation_index << " ";
	//		//}
	//		//cout << endl;
	//		//for (int j = number_of_jobs * number_of_operations; j < t.v_chromosome1.size(); j++)
	//		//{
	//		//	cout << t.v_chromosome1[j].machine_number << " ";
	//		//}
	//		//cout << endl;
	//		//for (int j = number_of_jobs * number_of_operations; j < t.v_chromosome1.size(); j++)
	//		//{
	//		//	cout << t.v_chromosome1[j].job_number << " ";
	//		//}
	//		//cout << endl;
	//		//system("pause");
	//		randomLower(t);//��������²�����
	//		//cout << "�²�����" << endl;
	//		//for (int k = 0; k < t.v_chromosome2.size(); k++)
	//		//{
	//		//	cout << t.v_chromosome2[k].job_number << " ";
	//		//}
	//		//cout << endl;
	//		//system("pause");
	//		upper_evaluate(t, board_width, board_height, v_product);//���ϲ���²�Ŀ�꺯��ֵ�������²�Ŀ��ֵ��Ȼ������²�Լ������ϲ�Ŀ��ֵ
	//		//system("pause");
	//		v_subChromo.push_back(t);
	//		v_TotalChromo.push_back(t);
	//	}
	//	v_Chromo.push_back(v_subChromo);
	//}
	//for (int i = 1; i < 2; i++)//����ϲ����������������С���ɵĻ������ȱ�ѡ��
	//{
	//	//cout << "i = " << i + 1 << endl;
	//	CIndividual T;
	//	Upper_H2(T);
	//	vector <CIndividual> v_subChromo;
	//	vector <CIndividual>().swap(v_subChromo);
	//	////�������Ⱥ�е�ÿ�����壬���ȼ̳еõ��Ĺ����ϲ��������ٵ���randomlower�������õ�һ���²�����
	//	for (int j = 0; j < lower_number_of_individuals; j++)
	//	{
	//		//cout << "j = " << j + 1<< endl;
	//		CIndividual t;
	//		t.sub_no = i + 1;
	//		t.v_chromosome1 = T.v_chromosome1;//����Ⱥ
	//		//cout << "�ϲ�����" << endl;
	//		//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	//		//{
	//		//	cout << t.v_chromosome1[j].operation_number << " ";
	//		//}
	//		//cout << endl;
	//		//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	//		//{
	//		//	cout << t.v_chromosome1[j].operation_index << " ";
	//		//}
	//		//cout << endl;
	//		//for (int j = number_of_jobs * number_of_operations; j < t.v_chromosome1.size(); j++)
	//		//{
	//		//	cout << t.v_chromosome1[j].machine_number << " ";
	//		//}
	//		//cout << endl;
	//		//for (int j = number_of_jobs * number_of_operations; j < t.v_chromosome1.size(); j++)
	//		//{
	//		//	cout << t.v_chromosome1[j].job_number << " ";
	//		//}
	//		//cout << endl;
	//		//system("pause");
	//		randomLower(t);//��������²�����
	//		//cout << "�²�����" << endl;
	//		//for (int k = 0; k < t.v_chromosome2.size(); k++)
	//		//{
	//		//	cout << t.v_chromosome2[k].job_number << " ";
	//		//}
	//		//cout << endl;
	//		//system("pause");
	//		upper_evaluate(t, board_width, board_height, v_product);//���ϲ���²�Ŀ�꺯��ֵ�������²�Ŀ��ֵ��Ȼ������²�Լ������ϲ�Ŀ��ֵ
	//		//system("pause");
	//		v_subChromo.push_back(t);
	//		v_TotalChromo.push_back(t);
	//	}
	//	v_Chromo.push_back(v_subChromo);
	//}
	for (int i = 0; i < number_of_subpop; i++)
	{
		//cout << "i = " << i + 1 << endl;
		////���ÿ������Ⱥ������randomUpper�������õ�һ�������ϲ�����
		CIndividual T;
		randomUpper(T);//��������ϲ�����
		vector <CIndividual> v_subChromo;
		vector <CIndividual>().swap(v_subChromo);//����swap�����ڴ棬����Ⱥ��ʼ��Ϊ�գ�����Ⱥ�������²���干���ϲ�����	
		////�������Ⱥ�е�ÿ�����壬���ȼ̳еõ��Ĺ����ϲ��������ٵ���randomlower�������õ�һ���²�����
		//for (int j = 0; j < 1; j++)
		//{	
		//	//cout << "j = " << j + 1<< endl;
		//	CIndividual t;
		//	t.sub_no = i + 1;
		//	t.v_chromosome1 = T.v_chromosome1;//����Ⱥ
		//	//cout << "�ϲ�����" << endl;
		//	//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
		//	//{
		//	//	cout << t.v_chromosome1[j].operation_number << " ";
		//	//}
		//	//cout << endl;
		//	//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
		//	//{
		//	//	cout << t.v_chromosome1[j].operation_index << " ";
		//	//}
		//	//cout << endl;
		//	//for (int j = number_of_jobs * number_of_operations; j < t.v_chromosome1.size(); j++)
		//	//{
		//	//	cout << t.v_chromosome1[j].machine_number << " ";
		//	//}
		//	//cout << endl;
		//	//for (int j = number_of_jobs * number_of_operations; j < t.v_chromosome1.size(); j++)
		//	//{
		//	//	cout << t.v_chromosome1[j].job_number << " ";
		//	//}
		//	//cout << endl;
		//	//system("pause");
		//	Lower_H3(t);
		//	//cout << "�²�����" << endl;
		//	//for (int k = 0; k < t.v_chromosome2.size(); k++)
		//	//{
		//	//	cout << t.v_chromosome2[k].job_number << " ";
		//	//}
		//	//cout << endl;
		//	//system("pause");
		//	upper_evaluate(t, board_width, board_height, v_product);//���ϲ���²�Ŀ�꺯��ֵ�������²�Ŀ��ֵ��Ȼ������²�Լ������ϲ�Ŀ��ֵ
		//	//system("pause");
		//	v_subChromo.push_back(t);
		//	v_TotalChromo.push_back(t);
		//}
		for (int j = 0; j < lower_number_of_individuals; j++)
		{
			//cout << "j = " << j+ 1<< endl;
			CIndividual t;
			t.sub_no = i + 1;
			t.v_chromosome1 = T.v_chromosome1;//����Ⱥ
			//cout << "�ϲ�����" << endl;
			//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
			//{
			//	cout << t.v_chromosome1[j].operation_number << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
			//{
			//	cout << t.v_chromosome1[j].operation_index << " ";
			//}
			//cout << endl;
			//for (int j = number_of_jobs * number_of_operations; j < t.v_chromosome1.size(); j++)
			//{
			//	cout << t.v_chromosome1[j].machine_number << " ";
			//}
			//cout << endl;
			//for (int j = number_of_jobs * number_of_operations; j < t.v_chromosome1.size(); j++)
			//{
			//	cout << t.v_chromosome1[j].job_number << " ";
			//}
			//cout << endl;
			//system("pause");
	
			randomLower(t);//��������²�����
			//cout << "�²�����" << endl;
			//for (int k = 0; k < t.v_chromosome2.size(); k++)
			//{
			//	cout << t.v_chromosome2[k].job_number << " ";
			//}
			//cout << endl;
			//system("pause");
	
			upper_evaluate(t, board_width, board_height, v_product);//���ϲ���²�Ŀ�꺯��ֵ�������²�Ŀ��ֵ��Ȼ������²�Լ������ϲ�Ŀ��ֵ
			//system("pause");

			v_subChromo.push_back(t);	
			v_TotalChromo.push_back(t);
		}
		v_Chromo.push_back(v_subChromo);
	}

	//cout << "��ʼ��Ⱥ��" << endl;
	//for (int i = 0; i < v_TotalChromo.size(); i++)
	//{
	//	cout << "i = " << i << endl;
	//	//cout << v_TotalChromo[i].sub_no << endl;
	//	for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	//	{
	//		cout << v_TotalChromo[i].v_chromosome1[j].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs * number_of_operations; j < v_TotalChromo[i].v_chromosome1.size(); j++)
	//	{
	//		cout << v_TotalChromo[i].v_chromosome1[j].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < v_TotalChromo[i].v_chromosome2.size(); j++)
	//	{
	//		cout << v_TotalChromo[i].v_chromosome2[j].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < v_TotalChromo[i].v_ul_objectives.size(); j++)
	//	{
	//		for (int h = 0; h < v_TotalChromo[i].v_ul_objectives[j].size(); h++)
	//		{
	//			cout << v_TotalChromo[i].v_ul_objectives[j][h] << " ";
	//		}
	//	}
	//	cout << endl;
	//}
	//system("pause");

	//cout << "��ʼ��Ⱥ��" << endl;
	//for (int m = 0; m < v_Chromo.size(); m++)
	//{
	//	cout << "sub_no = " << m + 1 << endl;
	//	for (int n = 0; n < v_Chromo[m].size(); n++)
	//	{
	//		cout << "iner = " << n + 1 << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_Chromo[m][n].v_chromosome1[u].operation_number << " ";
	//		}
	//		cout << endl;
	//		//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		//{
	//		//	cout << v_Chromo[m][n].v_chromosome1[u].operation_index << " ";
	//		//}
	//		//cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_Chromo[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_Chromo[m][n].v_chromosome1[u].machine_number << " ";
	//		}
	//		cout << endl;
	//		//for (int u = number_of_jobs * number_of_operations; u < v_Chromo[m][n].v_chromosome1.size(); u++)
	//		//{
	//		//	cout << v_Chromo[m][n].v_chromosome1[u].job_number << " ";
	//		//}
	//		//cout << endl;
	//		for (int u = 0; u < v_Chromo[m][n].v_chromosome2.size(); u++)
	//		{
	//			cout << v_Chromo[m][n].v_chromosome2[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_Chromo[m][n].v_ul_objectives.size(); u++)
	//		{
	//			for (int v = 0; v < v_Chromo[m][n].v_ul_objectives[u].size(); v++)
	//			{
	//				cout << v_Chromo[m][n].v_ul_objectives[u][v] << " ";
	//			}
	//		}
	//		cout << endl;
	//		//system("pause");
	//	}
	//	cout << endl<<endl;
	//}
	//system("pause");
}


void QPacking::randomUpper(CIndividual& T)//�ú�������������һ��������ϲ�����
{
	vector <CChromosome>().swap(T.v_chromosome1);
	////Step1: initialize operation sequence
	int* p_temp = new int[number_of_jobs * number_of_operations];
	int index = 0;
	for (int j = 0; j < number_of_jobs; j++)
	{
		for (int k = 0; k < number_of_operations; k++)
		{
			p_temp[index] = j + 1;
			index = index + 1;
		}
	}
	int total_operations_number = number_of_jobs * number_of_operations;
	int num = number_of_jobs * number_of_operations;
	int rand_num;
	for (int o = 0; o < total_operations_number; o++)
	{
		CChromosome C1;
		rand_num = rand() % num;
		index = p_temp[rand_num];
		C1.job_number = index;
		C1.operation_number = index;
		T.v_chromosome1.push_back(C1);
		p_temp[rand_num] = p_temp[num - 1];
		num = num - 1;
	}
	delete[] p_temp;

	for (int j = 0; j < number_of_jobs; j++)//�ж���ÿ��job�ĵڼ�������
	{
		int current_job_number = j + 1;
		int count = 0;
		//cout << "current_job_number = " << current_job_number << endl;
		for (int o = 0; o < total_operations_number; o++)
		{
			if (current_job_number == T.v_chromosome1[o].job_number)
			{
				count = count + 1;
				T.v_chromosome1[o].operation_index = count;
				//cout << "count = " << count << endl;
			}
			continue;
		}
	}

	////Step2:initialize machine assignment...
	////Step2.1��Ҫ���ÿ��job��ÿ������Ŀ��û�����
	vector<vector<vector<int>>>().swap(v_available_machines);
	for (int j = 0; j < number_of_jobs; j++)
	{
		vector <vector<int>> v1;
		v_available_machines.push_back(v1);
		for (int o = 0; o < number_of_operations; o++)
		{
			vector <int> v2;
			v_available_machines[j].push_back(v2);
			int machine_number;
			for (int m = 0; m < number_of_machines; m++)
			{
				if (p_b_fjsp_processing_time[o][m][j] != 99)
				{
					machine_number = m + 1;
					//cout << "machine_number = " << machine_number << endl;
					v_available_machines[j][o].push_back(machine_number);
				}
			}
			//cout << endl;
		}
		//cout << endl;
	}
	//cout << "ÿ��job��ÿ������Ŀ��û�������" << endl;
	//for (int j = 0; j < v_available_machines.size(); j++)
	//{
	//	cout << "job " << j + 1 << " �ļ�������Ŀ��û������ֱ��ǣ�" << endl;
	//	for (int o = 0; o < v_available_machines[j].size(); o++)
	//	{
	//		for (int m = 0; m < v_available_machines[j][o].size(); m++)
	//		{
	//			cout << v_available_machines[j][o][m] << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
	//system("pause");

	////Step2.2������������������
	for (int j = 0; j < number_of_jobs; j++)
	{
		//cout << "j " << j << endl;
		CChromosome C2;
		//��ȡ��job��ÿ������Ŀ��û�����
		for (int o = 0; o < number_of_operations; o++)
		{
			int operation_machine_size = v_available_machines[j][o].size();
			//cout << "operation_machine_size = " << operation_machine_size << endl;
			int rand_machine_number_index = rand() % operation_machine_size;
			//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
			int rand_machine_number = v_available_machines[j][o][rand_machine_number_index];
			//cout << "rand_machine_number = " << rand_machine_number << endl;
			C2.job_number = j + 1;
			C2.machine_number = rand_machine_number;
			T.v_chromosome1.push_back(C2);
		}
		//cout << endl;
	}
	//cout << endl;
	//system("pause");


	//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	//{
	//	cout << T.v_chromosome1[j].operation_number << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	//{
	//	cout << T.v_chromosome1[j].operation_index << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs * number_of_operations; j < T.v_chromosome1.size(); j++)
	//{
	//	cout << T.v_chromosome1[j].machine_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs * number_of_operations; j < T.v_chromosome1.size(); j++)
	//{
	//	cout << T.v_chromosome1[j].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
}


void QPacking::randomLower(CIndividual& t)//�ú�������������һ��������²�����
{
	vector <CChromosome>().swap(t.v_chromosome2);
	int min = 1;
	int max = number_of_jobs;
	int num = max - min + 1; 
	int jobNo;
	int* a = new int[num];
	for (int ii = 0; ii < num; ii++)
	{
		a[ii] = ii + min;
	}           
	int index;
	for (int ii = 0; ii < num; ii++)
	{
		CChromosome ccc;
		index = (int)((float)(num - ii) * rand() / ((RAND_MAX + 1) * 1.0));
		jobNo = a[index];
		ccc.job_number = jobNo;
		t.v_chromosome2.push_back(ccc);
		a[index] = a[num - ii - 1];
	}
	delete[] a;

	//for (int k = 0; k < t.v_chromosome2.size(); k++)
	//{
	//	cout << t.v_chromosome2[k].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
}


void QPacking::Upper_H1(CIndividual& T)
{
	////step1: ��ȡÿ��job��ÿ��operation�Ŀ���machine set
	vector<vector<vector<int>>>().swap(v_available_machines);
	for (int j = 0; j < number_of_jobs; j++)
	{
		vector <vector<int>> vv1;
		v_available_machines.push_back(vv1);
		for (int o = 0; o < number_of_operations; o++)
		{
			vector <int> vv2;
			v_available_machines[j].push_back(vv2);
			int machine_num;
			for (int m = 0; m < number_of_machines; m++)
			{
				if (p_b_fjsp_processing_time[o][m][j] != 99)
				{
					machine_num = m + 1;
					v_available_machines[j][o].push_back(machine_num);
				}
			}
		}
	}
	//cout << "ÿ��job��ÿ��operation�Ŀ���machine set��" << endl;
	//for (int j = 0; j < v_available_machines.size(); j++)
	//{
	//	cout << "job " << j + 1 << " �ļ�������Ŀ��û������ֱ��ǣ�" << endl;
	//	for (int o = 0; o < v_available_machines[j].size(); o++)
	//	{
	//		for (int m = 0; m < v_available_machines[j][o].size(); m++)
	//		{
	//			cout << v_available_machines[j][o][m] << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
	//system("pause");
	
	////step2: ��ȡÿ��job�ĳ�ʼʣ��ӹ�ʱ��
	vector<int> v_job_remaining_time;
	for (int m = 0; m < number_of_jobs; m++)
	{
		int job_remaining_time = 0;
		for (int n = 0; n < number_of_operations; n++)
		{
			int machine_index = v_available_machines[m][n][0] - 1;
			//cout << "machine_index = " << machine_index << endl;
			int processing_time = p_b_fjsp_processing_time[n][machine_index][m];
			//cout << "processing_time = " << processing_time << endl;
			job_remaining_time += processing_time;
			//cout << "job_remaining_time = " << job_remaining_time << endl;
		}
		v_job_remaining_time.push_back(job_remaining_time);
	}
	//cout << "ÿ��job�ĳ�ʼʣ��ӹ�ʱ�䣺" << endl;
	//for (int m = 0; m < v_job_remaining_time.size(); m++)
	//{
	//	cout << v_job_remaining_time[m] << " ";
	//}
	//cout << endl;

	////step3: ������������
	vector<int> v_operation_list;
	vector<int> v_job_times(number_of_jobs, 0);
	while (v_operation_list.size() < number_of_jobs * number_of_operations)
	{
		////step3.1���ҳ��������ʣ��ʱ���job����
		auto biggest = max_element(v_job_remaining_time.begin(), v_job_remaining_time.end());
		int max_value = *biggest;
		//cout << "max_value = " << max_value << endl;
		int max_value_index = distance(v_job_remaining_time.begin(), biggest);
		//cout << "max_value_index = " << max_value_index << endl;
		
		////step3.2������job��operation���빤���б�
		int job_number = max_value_index + 1;
		//cout << "job_number = " << job_number << endl;
		v_operation_list.push_back(job_number);
		
		////step3.3����¼����ִ������ڼ�������
		v_job_times[job_number - 1] = v_job_times[job_number - 1] + 1;
		//cout << "operation_th = " << v_job_times[job_number - 1] << endl;
		
		////step3.4���ҵ��ù���ļӹ�ʱ��
		int operation_index = v_job_times[job_number - 1] - 1;
		//cout << "operation_index = " << operation_index << endl;
		int machine_index = v_available_machines[job_number - 1][operation_index][0] - 1;
		//cout << "machine_index = " << machine_index << endl;
		int job_index = job_number - 1;
		//cout << "job_index = " << job_index << endl;
		double operation_time = p_b_fjsp_processing_time[operation_index][machine_index][job_index];
		//cout << "operation_time = " << operation_time << endl;
		
		////step3.5������job��ʣ��ӹ�ʱ��
		v_job_remaining_time[max_value_index] = v_job_remaining_time[max_value_index] - operation_time;
		//cout << "v_job_remaining_time[max_value_index] = " << v_job_remaining_time[max_value_index] << endl;
		//system("pause");
	}
	//cout << "��������" << endl;
	//for (int m = 0; m < v_operation_list.size(); m++)
	//{
	//	cout << v_operation_list[m] << " ";
	//}
	//cout << endl;

	////step4: ������������
	vector <CChromosome>().swap(T.v_chromosome1);
	for (int o = 0; o < v_operation_list.size(); o++)
	{
		CChromosome C1;
		C1.job_number = v_operation_list[o];
		C1.operation_number = v_operation_list[o];
		T.v_chromosome1.push_back(C1);
	}
	for (int j = 0; j < number_of_jobs; j++)//�ж���ÿ��job�ĵڼ�������
	{
		int current_job_number = j + 1;
		int count = 0;
		//cout << "current_job_number = " << current_job_number << endl;
		for (int o = 0; o < v_operation_list.size(); o++)
		{
			if (current_job_number == T.v_chromosome1[o].job_number)
			{
				count = count + 1;
				T.v_chromosome1[o].operation_index = count;
				//cout << "count = " << count << endl;
			}
			continue;
		}
	}

	////step5��������������
	for (int j = 0; j < number_of_jobs; j++)
	{
		//cout << "j = " << j + 1 << endl;
		CChromosome C2;
		//��ȡ��job��ÿ������Ŀ��û�����
		for (int o = 0; o < number_of_operations; o++)
		{
			int operation_machine_size = v_available_machines[j][o].size();
			//cout << "operation_machine_size = " << operation_machine_size << endl;
			int rand_machine_number_index = rand() % operation_machine_size;
			//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
			int rand_machine_number = v_available_machines[j][o][rand_machine_number_index];
			//cout << "rand_machine_number = " << rand_machine_number << endl;
			C2.job_number = j + 1;
			C2.machine_number = rand_machine_number;
			T.v_chromosome1.push_back(C2);
		}
		//cout << endl;
	}
	//cout << endl;
	//system("pause");

	//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	//{
	//	cout << T.v_chromosome1[j].operation_number << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	//{
	//	cout << T.v_chromosome1[j].operation_index << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs * number_of_operations; j < T.v_chromosome1.size(); j++)
	//{
	//	cout << T.v_chromosome1[j].machine_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs * number_of_operations; j < T.v_chromosome1.size(); j++)
	//{
	//	cout << T.v_chromosome1[j].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
}


void QPacking::Upper_H2(CIndividual& T)
{
	vector <CChromosome>().swap(T.v_chromosome1);
	
	////step1: ��ʼ����������
	int* p_temp = new int[number_of_jobs * number_of_operations];
	int index = 0;
	for (int j = 0; j < number_of_jobs; j++)
	{
		for (int k = 0; k < number_of_operations; k++)
		{
			p_temp[index] = j + 1;
			index = index + 1;
		}
	}
	int total_operations_number = number_of_jobs * number_of_operations;
	int num = number_of_jobs * number_of_operations;
	int rand_num;
	for (int o = 0; o < total_operations_number; o++)
	{
		CChromosome C1;
		rand_num = rand() % num;
		index = p_temp[rand_num];
		C1.job_number = index;
		C1.operation_number = index;
		T.v_chromosome1.push_back(C1);
		p_temp[rand_num] = p_temp[num - 1];
		num = num - 1;
	}
	delete[] p_temp;
	
	////step2: ���¹���˳��
	for (int j = 0; j < number_of_jobs; j++)//�ж���ÿ��job�ĵڼ�������
	{
		int current_job_number = j + 1;
		int count = 0;
		//cout << "current_job_number = " << current_job_number << endl;
		for (int o = 0; o < total_operations_number; o++)
		{
			if (current_job_number == T.v_chromosome1[o].job_number)
			{
				count = count + 1;
				T.v_chromosome1[o].operation_index = count;
				//cout << "count = " << count << endl;
			}
			continue;
		}
	}

	////step3: ���ÿ��job��ÿ������Ŀ��û�����
	vector<vector<vector<int>>>().swap(v_available_machines);
	for (int j = 0; j < number_of_jobs; j++)
	{
		vector <vector<int>> v1;
		v_available_machines.push_back(v1);
		for (int o = 0; o < number_of_operations; o++)
		{
			vector <int> v2;
			v_available_machines[j].push_back(v2);
			int machine_number;
			for (int m = 0; m < number_of_machines; m++)
			{
				if (p_b_fjsp_processing_time[o][m][j] != 99)
				{
					machine_number = m + 1;
					//cout << "machine_number = " << machine_number << endl;
					v_available_machines[j][o].push_back(machine_number);
				}
			}
			//cout << endl;
		}
		//cout << endl;
	}
	//cout << "ÿ��job��ÿ������Ŀ��û�������" << endl;
	//for (int j = 0; j < v_available_machines.size(); j++)
	//{
	//	cout << "job " << j + 1 << " �ļ�������Ŀ��û������ֱ��ǣ�" << endl;
	//	for (int o = 0; o < v_available_machines[j].size(); o++)
	//	{
	//		for (int m = 0; m < v_available_machines[j][o].size(); m++)
	//		{
	//			cout << v_available_machines[j][o][m] << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
	//system("pause");

	////step4: �������ɺͻ�������������ʼ��
	vector<int> v_machine_load(number_of_machines, 0);
	for (int j = 0; j < number_of_jobs; j++)
	{
		for (int o = 0; o < number_of_operations; o++)
		{
			CChromosome C2;
			C2.job_number = j + 1;
			C2.machine_number = 0;
			T.v_chromosome1.push_back(C2);
		}
	}

	////step5������������������
	for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	{
		////step5.1: ��ȡ��ǰ�����job�š��ڼ��������Լ����û�������
		int operation_number = T.v_chromosome1[j].operation_number;
		//cout << "operation_number = " << operation_number << endl;
		int operation_index = T.v_chromosome1[j].operation_index;
		//cout << "operation_index = " << operation_index << endl;
		int size = v_available_machines[operation_number - 1][operation_index - 1].size();
		int min_machine, min_machine_index, b_processing_time;
		
		////step5.2:�����û���������2����ѡȡ������Сload�Ļ�������������ֱ��ѡΨһ�Ļ�������
		if (size >= 2)
		{
			vector<int> v_m_aftload;
			vector<int> v_m_aftindex;
			////step5.2.1:��ȡ��ǰ����Ŀ��û������������ϼӹ�ʱ�俴�����Ϻ���̨����load��С
			for (int m = 0; m < size; m++)
			{
				int machine_index = v_available_machines[operation_number - 1][operation_index - 1][m] - 1;
				//cout << "machine_index = " << machine_index << endl;		
				int current_load = v_machine_load[machine_index];//��ȡ��ǰ������load
				//cout << "current_load = " << current_load << endl;
				b_processing_time = p_b_fjsp_processing_time[operation_index - 1][machine_index][operation_number - 1];
				//cout << "b_processing_time1 = " << b_processing_time << endl;
				int aftload = current_load + b_processing_time;
				v_m_aftload.push_back(aftload);
				v_m_aftindex.push_back(machine_index);
			}
			////step5.2.2:��ȡ������Сload�Ļ�������
			auto smallest = min_element(v_m_aftload.begin(), v_m_aftload.end());
			int min_value = *smallest;
			//cout << "min_value = " << min_value << endl;
			int min_value_index = distance(v_m_aftload.begin(),smallest);
			//cout << "min_value_index = " << min_value_index << endl;
			min_machine_index = v_m_aftindex[min_value_index];
		}
		else
		{
			min_machine_index = v_available_machines[operation_number - 1][operation_index - 1][0] - 1;
			b_processing_time = p_b_fjsp_processing_time[operation_index - 1][min_machine_index][operation_number - 1];
			//cout << "b_processing_time2 = " << b_processing_time << endl;
		}
		//cout << "min_machine_index = " << min_machine_index << endl;
		
		////step5.3:����ѡ�еĻ�����load
		v_machine_load[min_machine_index] = v_machine_load[min_machine_index] + b_processing_time;
		int after_load = v_machine_load[min_machine_index];
		//cout << "after_load = " << after_load << endl;
		
		////step5.4:���µ�ǰ����Ļ�������
		min_machine = min_machine_index + 1;
		//cout << "min_machine = " << min_machine << endl;
		int location_index = number_of_jobs * number_of_operations + (operation_number - 1) * number_of_operations + operation_index - 1;
		//cout << "location_index = " << location_index << endl;
		T.v_chromosome1[location_index].machine_number = min_machine;
		//system("pause");
	}


	//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	//{
	//	cout << T.v_chromosome1[j].operation_number << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	//{
	//	cout << T.v_chromosome1[j].operation_index << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs * number_of_operations; j < T.v_chromosome1.size(); j++)
	//{
	//	cout << T.v_chromosome1[j].machine_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs * number_of_operations; j < T.v_chromosome1.size(); j++)
	//{
	//	cout << T.v_chromosome1[j].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
}


void QPacking::Lower_H3(CIndividual& t)
{
	vector <CChromosome>().swap(t.v_chromosome2);
	
	////step1: ��ȡÿ������������job
	vector<vector<int>> v_order_jobs;
	for (int m = 0; m < v_order_product.size(); m++)
	{
		vector<int> v_jobs;
		for (int n = 0; n < v_order_product[m].size(); n++)
		{
			v_jobs.push_back(v_order_product[m][n]);
		}
		v_order_jobs.push_back(v_jobs);
	}
	//cout << "ÿ��������������ҵ��" << endl;
	//for (int m = 0; m < v_order_jobs.size(); m++)
	//{
	//	for (int n = 0; n < v_order_jobs[m].size(); n++)
	//	{
	//		cout << v_order_jobs[m][n] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	////step2: ��ȡÿ��������duedate������
	vector<int> v_order_duedate;
	vector<int> v_order_index;
	for (int m = 0; m < number_of_orders; m++)
	{
		v_order_duedate.push_back(p_order_due_time[m]);
		v_order_index.push_back(m);
	}
	//for (int m = 0; m < v_order_duedate.size(); m++)
	//{
	//	cout << v_order_duedate[m] << " ";
	//}
	//cout << endl;
	//for (int m = 0; m < v_order_index.size(); m++)
	//{
	//	cout << v_order_index[m] << " ";
	//}
	//cout << endl;
	//system("pause");

	////step3: �Զ�����duedate��index����ð������
	int temp_value = 0;
	int temp_index = 0;
	for (int m = 0; m < v_order_duedate.size() - 1; m++)
	{
		for (int n = 0; n < v_order_duedate.size() - m - 1; n++)
		{
			if (v_order_duedate[n] > v_order_duedate[n + 1])
			{
				temp_value = v_order_duedate[n];
				v_order_duedate[n] = v_order_duedate[n + 1];
				v_order_duedate[n + 1] = temp_value;

				temp_index = v_order_index[n];
				v_order_index[n] = v_order_index[n + 1];
				v_order_index[n + 1] = temp_index;
			}
		}
	}
	//for (int m = 0; m < v_order_duedate.size(); m++)
	//{
	//	cout << v_order_duedate[m] << " ";
	//}
	//cout << endl;
	//for (int m = 0; m < v_order_index.size(); m++)
	//{
	//	cout << v_order_index[m] << " ";
	//}
	//cout << endl;
	//system("pause");

	////step4: ��v_order_jobs���д���
	//cout << "���Һ�ÿ��������job" << endl;
	for (int m = 0; m < v_order_jobs.size(); m++)
	{
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(v_order_jobs[m].begin(), v_order_jobs[m].end(), g);
		//for (int n = 0; n < v_order_jobs[m].size(); n++)
		//{
		//	cout << v_order_jobs[m][n] << " ";
		//}
		//cout << endl;
	}
	//system("pause");

	///step5: �����²�����
	for (int m = 0; m < v_order_index.size(); m++)
	{	
		int order_index = v_order_index[m];
		//cout << "order_index = " << order_index << endl;
		for (int n = 0; n < v_order_jobs[order_index].size(); n++)
		{
			CChromosome ccc;
			int jobNo = v_order_jobs[order_index][n];
			//cout << "jobNo = " << jobNo << endl;
			ccc.job_number = jobNo;
			t.v_chromosome2.push_back(ccc);
		}
	}


	//for (int k = 0; k < t.v_chromosome2.size(); k++)
	//{
	//	cout << t.v_chromosome2[k].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
}