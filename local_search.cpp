#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"
#include "Item.h"
#include <algorithm>
#include <map>

void QPacking::local_search(vector<CIndividual>& v_new_TotalChromo_temp, vector <vector<CIndividual>>& v_new_Chromo_temp, vector<Item>& v_product, int& Action_Current)
{
	//cout << "local_searchǰ��" << endl;
	//out_result(v_new_Chromo_temp, v_new_TotalChromo_temp);

	/////�ֲ�����
	vector<vector<CIndividual>>().swap(v_ls_Chromo);
	vector<CIndividual>().swap(v_ls_TotalChromo);
	for (int i = 0; i < number_of_subpop; i++)
	{
		vector <CIndividual> v_ls_subChromo;
		vector <CIndividual>().swap(v_ls_subChromo);
		for (int j = 0; j < lower_number_of_individuals; j++) //��ÿ������ִ�оֲ���������
		{
			CIndividual ls_indiv = v_new_Chromo_temp[i][j];		
			ls_operation_individual(ls_indiv, v_product, Action_Current); ////��ÿ������ִ�оֲ���������
			upper_evaluate(ls_indiv, board_width, board_height, v_product);
			v_ls_subChromo.push_back(ls_indiv);
			v_ls_TotalChromo.push_back(ls_indiv);
		}
		v_ls_Chromo.push_back(v_ls_subChromo);
	}
	
	rank_up(v_ls_TotalChromo);//��ȡ��Ⱥ�и�����ϲ���ֵ��ӵ���Ⱦ���
	rank_low(v_ls_Chromo);//��ȡ��Ⱥ��ÿ������Ⱥ�и�����²���ֵ��ӵ���Ⱦ���
	update_subpop(v_ls_TotalChromo, v_ls_Chromo);//�������Ⱥv_new_TotalChromo/v_new_Chromo
	
	//cout << "local_search��" << endl;
	//out_result(v_ls_Chromo, v_ls_TotalChromo);
}

void QPacking::ls_operation_individual(CIndividual& ls_indiv, vector<Item>& v_product, int & Action_Current)
{
	//cout << "�ֲ�����ǰ�ĸ��壺" << endl;
	//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//{
	//	cout << ls_indiv.v_chromosome1[u].operation_number << " ";
	//}
	//cout << endl;
	//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//{
	//	cout << ls_indiv.v_chromosome1[u].operation_index << " ";
	//}
	//cout << endl;
	//for (int u = number_of_jobs * number_of_operations; u < ls_indiv.v_chromosome1.size(); u++)
	//{
	//	cout << ls_indiv.v_chromosome1[u].machine_number << " ";
	//}
	//cout << endl;
	////for (int u = number_of_jobs * number_of_operations; u < ls_indiv.v_chromosome1.size(); u++)
	////{
	////	cout << ls_indiv.v_chromosome1[u].job_number << " ";
	////}
	////cout << endl;
	////for (int u = 0; u < ls_indiv.v_chromosome2.size(); u++)
	////{
	////	cout << ls_indiv.v_chromosome2[u].job_number << " ";
	////}
	////cout << endl;
	////for (int u = 0; u < ls_indiv.v_ul_objectives.size(); u++)
	////{
	////	for (int v = 0; v < ls_indiv.v_ul_objectives[u].size(); v++)
	////	{
	////		cout << ls_indiv.v_ul_objectives[u][v] << " ";
	////	}
	////}
	////system("pause");

	////ִ������ͨ������ṹ
	//Case1:�ı乤�����еļӹ�˳���ڹ������������ѡ�������е㣬Ȼ�������֮��Ĺ�����з�ת��������������
	//Case2:�ı乤�����еļӹ�˳���ڹ������������ѡ�������е㣬Ȼ��������ϵĹ�����н�����������������
	//Case3:�ı乤�����еļӹ�˳���ڹ������������ѡ�������е㣬Ȼ��ѿ�����е��ϵĹ�����뵽��ǰ���е��ϵĹ����ǰ�棬������������
	//Case4:�ı�������䣬�ڹ������������ѡ�������е㣬Ȼ�������֮��Ĺ���Ļ��������������
	//Case5:��������ؼ�·�����������׶λ��Ų��׶ε�����job
	//Case6:������ؼ�·�����������׶λ��Ų��׶ε�һ��job���뵽��һ��jobǰ��
	//Case7:��������ؼ�·�������Ų��׶ε�һ��job�Ļ�������
	int rand_select_number = Action_Current;
	//cout << "rand_select_number = " << rand_select_number << endl;
	if (rand_select_number == 1)
	{
		//cout << "ִ��case1" << endl;
		ls_operation1(ls_indiv, v_product);
	}
	else if (rand_select_number == 2)
	{
		//cout << "ִ��case2" << endl;
		ls_operation2(ls_indiv, v_product);
	}
	else if (rand_select_number == 3)
	{
		//cout << "ִ��case3" << endl;
		ls_operation3(ls_indiv, v_product);
	}
	else if (rand_select_number == 4)
	{
		//cout << "ִ��case4" << endl;
		ls_operation4(ls_indiv, v_product);
	}
	else if (rand_select_number == 5)
	{
		//cout << "ִ��case5" << endl;
		ls_operation5(ls_indiv, v_product);
	}
	else if (rand_select_number == 6)
	{
		//cout << "ִ��case6" << endl;
		ls_operation6(ls_indiv, v_product);
	}
	else if (rand_select_number == 7)
	{
		//cout << "ִ��case6" << endl;
		ls_operation6(ls_indiv, v_product);
	}

	//cout << "�ֲ�������ĸ��壺" << endl;
	//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//{
	//	cout << ls_indiv.v_chromosome1[u].operation_number << " ";
	//}
	//cout << endl;
	//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//{
	//	cout << ls_indiv.v_chromosome1[u].operation_index << " ";
	//}
	//cout << endl;
	//for (int u = number_of_jobs * number_of_operations; u < ls_indiv.v_chromosome1.size(); u++)
	//{
	//	cout << ls_indiv.v_chromosome1[u].machine_number << " ";
	//}
	//cout << endl;
	////for (int u = number_of_jobs * number_of_operations; u < ls_indiv.v_chromosome1.size(); u++)
	////{
	////	cout << ls_indiv.v_chromosome1[u].job_number << " ";
	////}
	////cout << endl;
	////for (int u = 0; u < ls_indiv.v_chromosome2.size(); u++)
	////{
	////	cout << ls_indiv.v_chromosome2[u].job_number << " ";
	////}
	////cout << endl;
	////for (int u = 0; u < ls_indiv.v_ul_objectives.size(); u++)
	////{
	////	for (int v = 0; v < ls_indiv.v_ul_objectives[u].size(); v++)
	////	{
	////		cout << ls_indiv.v_ul_objectives[u][v] << " ";
	////	}
	////}
	//system("pause");
}

void QPacking::ls_operation1(CIndividual& ls_indiv1, vector<Item>& v_product)
{
	//cout << "���㷭ת��" << endl;
	int cutpoint1, cutpoint2;//���������е㣻			
	cutpoint1 = rand() % (number_of_jobs * number_of_operations);
	cutpoint2 = rand() % (number_of_jobs * number_of_operations);
	while (cutpoint1 == cutpoint2)//�������е���ͬ
	{
		cutpoint1 = rand() % (number_of_jobs * number_of_operations);//�����²���һ���е�2
	}
	int temp_cut1;
	if (cutpoint1 > cutpoint2)
	{
		temp_cut1 = cutpoint1;
		cutpoint1 = cutpoint2;
		cutpoint2 = temp_cut1;
	}
	//cout << "cutpoint1 = " << cutpoint1 << endl;
	//cout << "cutpoint2 = " << cutpoint2 << endl;
	
	vector <int> v_oper_part_list;
	vector <int>().swap(v_oper_part_list);//��������Ԫ�ط����������ʹ��reverse��ת
	for (int u = cutpoint1; u <= cutpoint2; u++)
	{
		int operNo = ls_indiv1.v_chromosome1[u].operation_number;
		v_oper_part_list.push_back(operNo);
	}
	//for (int u = 0; u < v_oper_part_list.size(); u++)
	//{
	//	cout << v_oper_part_list[u] << " ";
	//}
	//system("pause");

	reverse(v_oper_part_list.begin(), v_oper_part_list.end()); //��v_operation_part_list�еĴ�v_operation_part_list.begin()������������v_operation_part_list.end()������������Ԫ�ص��ã���v_operation_part_list��Ԫ��Ϊ1,2,3,4,���ú�Ϊ4,3,2,1
	//for (int u = 0; u < v_oper_part_list.size(); u++)
	//{
	//	cout << v_oper_part_list[u] << " ";
	//}
	//system("pause");

	for (int u = cutpoint1; u <= cutpoint2; u++)
	{
		int jobNo_j = v_oper_part_list[u - cutpoint1];
		//cout << "jobNo_j = " << jobNo_j << endl;
		ls_indiv1.v_chromosome1[u].operation_number = jobNo_j;
		ls_indiv1.v_chromosome1[u].job_number = jobNo_j;//job_number��֮����
	}

	//operation_index��֮����
	for (int u = 0; u < number_of_jobs; u++)//�ж���ÿ��job�ĵڼ�������
	{
		int current_job_number = u + 1;
		int count = 0;
		for (int c = 0; c < number_of_jobs * number_of_operations; c++)
		{
			if (current_job_number == ls_indiv1.v_chromosome1[c].job_number)
			{
				count = count + 1;
				ls_indiv1.v_chromosome1[c].operation_index = count;
			}
			continue;
		}
	}
}

void QPacking::ls_operation2(CIndividual& ls_indiv2, vector<Item>& v_product)
{
	//cout << "���㽻����" << endl;
	int cutpoint3, cutpoint4;//���������е㣻			
	cutpoint3 = rand() % (number_of_jobs * number_of_operations);
	cutpoint4 = rand() % (number_of_jobs * number_of_operations);
	while (cutpoint3 == cutpoint4)//�������е���ͬ
	{
		cutpoint3 = rand() % (number_of_jobs * number_of_operations);//�����²���һ���е�2
	}
	int temp_cut2;
	if (cutpoint3 > cutpoint4)
	{
		temp_cut2 = cutpoint3;
		cutpoint3 = cutpoint4;
		cutpoint4 = temp_cut2;
	}
	//cout << "cutpoint3 = " << cutpoint3 << endl;
	//cout << "cutpoint4 = " << cutpoint4 << endl;

	//���������е�Ĺ����
	int operNo = ls_indiv2.v_chromosome1[cutpoint3].operation_number;
	ls_indiv2.v_chromosome1[cutpoint3].operation_number = ls_indiv2.v_chromosome1[cutpoint4].operation_number;;
	ls_indiv2.v_chromosome1[cutpoint4].operation_number = operNo;
	
	//job_number��֮����
	ls_indiv2.v_chromosome1[cutpoint3].job_number = ls_indiv2.v_chromosome1[cutpoint3].operation_number;
	ls_indiv2.v_chromosome1[cutpoint4].job_number = ls_indiv2.v_chromosome1[cutpoint4].operation_number;

	//operation_index��֮����
	for (int u = 0; u < number_of_jobs; u++)//�ж���ÿ��job�ĵڼ�������
	{
		int current_job_number = u + 1;
		int count = 0;
		for (int c = 0; c < number_of_jobs * number_of_operations; c++)
		{
			if (current_job_number == ls_indiv2.v_chromosome1[c].job_number)
			{
				count = count + 1;
				ls_indiv2.v_chromosome1[c].operation_index = count;
			}
			continue;
		}
	}
}

void QPacking::ls_operation3(CIndividual& ls_indiv3, vector<Item>& v_product)
{
	//cout << "������룡" << endl;
	int cutpoint5, cutpoint6;//���������е㣻			
	cutpoint5 = rand() % (number_of_jobs * number_of_operations);
	cutpoint6 = rand() % (number_of_jobs * number_of_operations);
	while (cutpoint5 == cutpoint6)//�������е���ͬ
	{
		cutpoint5 = rand() % (number_of_jobs * number_of_operations);//�����²���һ���е�2
	}
	int temp_cut3;
	if (cutpoint5 > cutpoint6)
	{
		temp_cut3 = cutpoint5;
		cutpoint5 = cutpoint6;
		cutpoint6 = temp_cut3;
	}
	//cout << "cutpoint5 = " << cutpoint5 << endl;
	//cout << "cutpoint6 = " << cutpoint6 << endl;
	
	//��ȡ�����е��ϵĹ���
	int ls_operation_job = ls_indiv3.v_chromosome1[cutpoint6].operation_number;
	//cout << "ls_operation_job = " << ls_operation_job << endl;
	 
	//�Ƚ�ѡ�еĿ���һ���operation��Ⱦɫ����ɾ��
	ls_indiv3.v_chromosome1.erase(ls_indiv3.v_chromosome1.begin() + cutpoint6);
	
	//Ȼ���ٰ������뵽��ǰһ���operation��ǰ��λ��
	CChromosome tttt;
	tttt.operation_number = ls_operation_job;
	ls_indiv3.v_chromosome1.insert(ls_indiv3.v_chromosome1.begin() + cutpoint5, tttt);

	//ͬʱ���������ǵ�job��Ϣ
	for (int k = 0; k < number_of_jobs * number_of_operations; k++)
	{
		ls_indiv3.v_chromosome1[k].job_number = ls_indiv3.v_chromosome1[k].operation_number;
	}

	//����job��Ϣ�������ǵ�operation_index��Ϣ
	for (int k = 0; k < number_of_jobs; k++)//�ж���ÿ��job�ĵڼ�������
	{
		int current_job_number = k + 1;
		int count = 0;
		for (int c = 0; c < number_of_jobs * number_of_operations; c++)
		{
			if (current_job_number == ls_indiv3.v_chromosome1[c].job_number)
			{
				count = count + 1;
				ls_indiv3.v_chromosome1[c].operation_index = count;
			}
			continue;
		}
	}
}

void QPacking::ls_operation4(CIndividual& ls_indiv4, vector<Item>& v_product)
{
	//cout << "����֮���������������ɣ�" << endl;
	int cutpoint7, cutpoint8;//���������е㣻			
	cutpoint7 = rand() % (number_of_jobs * number_of_operations);
	cutpoint8 = rand() % (number_of_jobs * number_of_operations);
	while (cutpoint7 == cutpoint8)//�������е���ͬ
	{
		cutpoint7 = rand() % (number_of_jobs * number_of_operations);//�����²���һ���е�2
	}
	int temp_cut4;
	if (cutpoint7 > cutpoint8)
	{
		temp_cut4 = cutpoint7;
		cutpoint7 = cutpoint8;
		cutpoint8 = temp_cut4;
	}
	//cout << "cutpoint7 = " << cutpoint7 << endl;
	//cout << "cutpoint8 = " << cutpoint8 << endl;

	for (int u = cutpoint7; u <= cutpoint8; u++)
	{
		int jobNo = ls_indiv4.v_chromosome1[u].job_number;
		//cout << "jobNo = " << jobNo << endl;
		int operIndex = ls_indiv4.v_chromosome1[u].operation_index;
		//cout << "operIndex = " << operIndex << endl;
		//��ȡ��job�ĸõ�����Ŀ�ʹ�û�������
		int operation_machine_size = v_available_machines[jobNo - 1][operIndex - 1].size();
		//cout << "operation_machine_size = " << operation_machine_size << endl;
		if (operation_machine_size >= 2)
		{
			int rand_machine_number_index = rand() % operation_machine_size;
			//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
			int rand_machine_number = v_available_machines[jobNo - 1][operIndex - 1][rand_machine_number_index];
			//cout << "rand_machine_number = " << rand_machine_number << endl;
			//��ȡ�ù���Ļ���λ������
			int mach_pos_index = number_of_jobs * number_of_operations + (jobNo - 1) * number_of_operations + operIndex - 1;
			//cout << "mach_pos_index = " << mach_pos_index << endl;
			int current_machine_number = ls_indiv4.v_chromosome1[mach_pos_index].machine_number;
			//cout << "current_machine_number = " << current_machine_number << endl;
			while (current_machine_number == rand_machine_number)
			{
				rand_machine_number_index = rand() % operation_machine_size;
				//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
				rand_machine_number = v_available_machines[jobNo - 1][operIndex - 1][rand_machine_number_index];
				//cout << "rand_machine_number = " << rand_machine_number << endl;
			}
			ls_indiv4.v_chromosome1[mach_pos_index].machine_number = rand_machine_number;
		}
	}
}

void QPacking::ls_operation5(CIndividual& ls_indiv, vector<Item>& v_product)
{
	//cout << "�Թؼ�·������swap������" << endl;

	//cout << "�����׶ιؼ�·��job�����ţ�" << endl;
	//for (int g = 0; g < ls_indiv.Product_C.size(); g++)
	//{
	//	cout << ls_indiv.Product_C[g] << " ";
	//}
	//cout << endl;

	//cout << "����׶ιؼ�·���������漰��job�����ţ�operation��������ţ�machine�����ţ�" << endl;
	//for (int k = 0; k < ls_indiv.Operation_C.size(); k++)
	//{
	//	int job_index = ls_indiv.Job_C[k] - 1;
	//	cout << "��ҵ������" << job_index << " ";
	//	int operation_index = ls_indiv.Operation_C[k] - 1;
	//	cout << "����������" << operation_index << " ";
	//	int machine_index = ls_indiv.Machine_C[k];
	//	cout << "����������" << machine_index << " ";//����������
	//	cout << endl;
	//}
	//cout << endl;
	//system("pause");

	////�ж������׶εĹ�ģ
	if (ls_indiv.Product_C.size() >= 2)
	{
		//cout << "���������Ų��ؼ�·���ϵ�job���е�����" << endl;
		int random_number = rand() % 2;
		if (random_number == 0)
		{
			//cout << "������·���ϵ�job���е�����" << endl;
			////step1�����ѡȡ�ؼ�·���ϵ��������ظ���job
			int key_size = ls_indiv.Product_C.size();
			int ls1 = rand() % key_size;
			int ls2 = rand() % key_size;
			while (ls1 == ls2)
			{
				ls2 = rand() % key_size;
			}
			if (ls1 > ls2)
			{
				int temp = ls1;
				ls1 = ls2;
				ls2 = temp;
			}
			int ls_job1, ls_job2;
			ls_job1 = ls_indiv.Product_C[ls1] + 1;
			ls_job2 = ls_indiv.Product_C[ls2] + 1;

			////step2����ls_indivȾɫ����Ѱ������job��λ������
			int ls_pos_index1 = 0;
			int ls_pos_index2 = 0;
			for (int u = 0; u < ls_indiv.v_chromosome2.size(); u++)
			{
				if (ls_indiv.v_chromosome2[u].job_number == ls_job1)
				{
					ls_pos_index1 = u;
					break;
				}
			}
			//cout << endl;
			for (int u = 0; u < ls_indiv.v_chromosome2.size(); u++)
			{
				if (ls_indiv.v_chromosome2[u].job_number == ls_job2)
				{
					ls_pos_index2 = u;
					break;
				}
			}

			////step3����ls_indivȾɫ���Ͻ�������job
			int ls_job_temp = ls_indiv.v_chromosome2[ls_pos_index1].job_number;
			ls_indiv.v_chromosome2[ls_pos_index1].job_number = ls_indiv.v_chromosome2[ls_pos_index2].job_number;
			ls_indiv.v_chromosome2[ls_pos_index2].job_number = ls_job_temp;
		}
		else
		{
			//cout << "���Ų�·���ϵ�job���е�����" << endl;
			////step1�����ѡ�������ؼ�job
			int ls_size = ls_indiv.Job_C.size();
			int ls1 = rand() % ls_size;
			int ls2 = rand() % ls_size;
			while (ls1 == ls2)
			{
				ls2 = rand() % ls_size;
			}
			if (ls1 > ls2)
			{
				int temp = ls1;
				ls1 = ls2;
				ls2 = temp;
			}
			//cout << "ls1 = " << ls1 << endl;
			//cout << "ls2= " << ls2 << endl;
			int ls_job1, ls_job2;
			ls_job1 = ls_indiv.Job_C[ls1];
			ls_job2 = ls_indiv.Job_C[ls2];
			//cout << "ls_job1 = " << ls_job1 << endl;
			//cout << "ls_job2 = " << ls_job2 << endl;
			int ls_operation1, ls_operation2;
			ls_operation1 = ls_indiv.Operation_C[ls1];
			ls_operation2 = ls_indiv.Operation_C[ls2];
			//cout << "ls_operation1 = " << ls_operation1 << endl;
			//cout << "ls_operation2 = " << ls_operation2 << endl;

			////step2���ҳ�Ⱦɫ������������ҵ��λ������
			////�ҵ�ls_operation1�γ��ֵ�ls_job1
			int ls_index1, ls_index2;
			int ls_count1 = 0;
			for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
			{
				if (ls_indiv.v_chromosome1[jj].operation_number == ls_job1)
				{
					ls_count1++;
				}
				if (ls_count1 == ls_operation1)
				{
					ls_index1 = jj;
					break;
				}
			}
			int ls_count2 = 0;
			for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
			{
				if (ls_indiv.v_chromosome1[jj].operation_number == ls_job2)
				{
					ls_count2++;
				}
				if (ls_count2 == ls_operation2)
				{
					ls_index2 = jj;
					break;
				}
			}
			//cout << "ls_index1 = " << ls_index1 << endl;
			//cout << "ls_index2 = " << ls_index2 << endl;


			////step3������������ҵ�ڹ��������е�λ��
			int ls_temp = ls_indiv.v_chromosome1[ls_index1].operation_number;
			ls_indiv.v_chromosome1[ls_index1].operation_number = ls_indiv.v_chromosome1[ls_index2].operation_number;
			ls_indiv.v_chromosome1[ls_index2].operation_number = ls_temp;
			//ͬʱ���������ǵ�job��Ϣ
			int temp_job_number = ls_indiv.v_chromosome1[ls_index1].job_number;
			ls_indiv.v_chromosome1[ls_index1].job_number = ls_indiv.v_chromosome1[ls_index2].job_number;
			ls_indiv.v_chromosome1[ls_index2].job_number = temp_job_number;
			//������job��Ϣ�������ǵ�operation_index��Ϣ
			for (int k = 0; k < number_of_jobs; k++)//�ж���ÿ��job�ĵڼ�������
			{
				int current_job_number = k + 1;
				int count = 0;
				for (int c = 0; c < number_of_jobs * number_of_operations; c++)
				{
					if (current_job_number == ls_indiv.v_chromosome1[c].job_number)
					{
						count = count + 1;
						ls_indiv.v_chromosome1[c].operation_index = count;
					}
					continue;
				}
			}

		}
	}
	else
	{
		//cout << "���Ų�·���ϵ�job���е�����" << endl;
		////step1�����ѡ�������ؼ�job
		int ls_size = ls_indiv.Job_C.size();
		int ls1 = rand() % ls_size;
		int ls2 = rand() % ls_size;
		while (ls1 == ls2)
		{
			ls2 = rand() % ls_size;
		}
		if (ls1 > ls2)
		{
			int temp = ls1;
			ls1 = ls2;
			ls2 = temp;
		}
		//cout << "ls1 = " << ls1 << endl;
		//cout << "ls2= " << ls2 << endl;
		int ls_job1, ls_job2;
		ls_job1 = ls_indiv.Job_C[ls1];
		ls_job2 = ls_indiv.Job_C[ls2];
		//cout << "ls_job1 = " << ls_job1 << endl;
		//cout << "ls_job2 = " << ls_job2 << endl;
		int ls_operation1, ls_operation2;
		ls_operation1 = ls_indiv.Operation_C[ls1];
		ls_operation2 = ls_indiv.Operation_C[ls2];
		//cout << "ls_operation1 = " << ls_operation1 << endl;
		//cout << "ls_operation2 = " << ls_operation2 << endl;

		////step2���ҳ�Ⱦɫ������������ҵ��λ������
		////�ҵ�ls_operation1�γ��ֵ�ls_job1
		int ls_index1, ls_index2;
		int ls_count1 = 0;
		for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
		{
			if (ls_indiv.v_chromosome1[jj].operation_number == ls_job1)
			{
				ls_count1++;
			}
			if (ls_count1 == ls_operation1)
			{
				ls_index1 = jj;
				break;
			}
		}
		int ls_count2 = 0;
		for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
		{
			if (ls_indiv.v_chromosome1[jj].operation_number == ls_job2)
			{
				ls_count2++;
			}
			if (ls_count2 == ls_operation2)
			{
				ls_index2 = jj;
				break;
			}
		}
		//cout << "ls_index1 = " << ls_index1 << endl;
		//cout << "ls_index2 = " << ls_index2 << endl;


		////step3������������ҵ�ڹ��������е�λ��
		int ls_temp = ls_indiv.v_chromosome1[ls_index1].operation_number;
		ls_indiv.v_chromosome1[ls_index1].operation_number = ls_indiv.v_chromosome1[ls_index2].operation_number;
		ls_indiv.v_chromosome1[ls_index2].operation_number = ls_temp;
		//ͬʱ���������ǵ�job��Ϣ
		int temp_job_number = ls_indiv.v_chromosome1[ls_index1].job_number;
		ls_indiv.v_chromosome1[ls_index1].job_number = ls_indiv.v_chromosome1[ls_index2].job_number;
		ls_indiv.v_chromosome1[ls_index2].job_number = temp_job_number;
		//������job��Ϣ�������ǵ�operation_index��Ϣ
		for (int k = 0; k < number_of_jobs; k++)//�ж���ÿ��job�ĵڼ�������
		{
			int current_job_number = k + 1;
			int count = 0;
			for (int c = 0; c < number_of_jobs * number_of_operations; c++)
			{
				if (current_job_number == ls_indiv.v_chromosome1[c].job_number)
				{
					count = count + 1;
					ls_indiv.v_chromosome1[c].operation_index = count;
				}
				continue;
			}
		}
	}
}

void QPacking::ls_operation6(CIndividual& ls_indiv, vector<Item>& v_product)
{
	//cout << "�Թؼ�·������insert������" << endl;

	//cout << "�����׶ιؼ�·��job�����ţ�" << endl;
	//for (int g = 0; g < ls_indiv.Product_C.size(); g++)
	//{
	//	cout << ls_indiv.Product_C[g] << " ";
	//}
	//cout << endl;

	//cout << "����׶ιؼ�·���������漰��job�����ţ�operation��������ţ�machine�����ţ�" << endl;
	//for (int k = 0; k < ls_indiv.Operation_C.size(); k++)
	//{
	//	int job_index = ls_indiv.Job_C[k] - 1;
	//	cout << "��ҵ������" << job_index << " ";
	//	int operation_index = ls_indiv.Operation_C[k] - 1;
	//	cout << "����������" << operation_index << " ";
	//	int machine_index = ls_indiv.Machine_C[k];
	//	cout << "����������" << machine_index << " ";//����������
	//	cout << endl;
	//}
	//cout << endl;
	//system("pause");

	////�ж������׶εĹ�ģ
	if (ls_indiv.Product_C.size() >= 2)
	{
		//cout << "���������Ų��ؼ�·���ϵ�job���е�����" << endl;
		int random_number = rand() % 2;
		if (random_number == 0)
		{
			//cout << "������·���ϵ�job���е�����" << endl;
			////step1�����ѡȡ�ؼ�·���ϵ��������ظ���job
			int key_size = ls_indiv.Product_C.size();
			int ls1 = rand() % key_size;
			int ls2 = rand() % key_size;
			while (ls1 == ls2)
			{
				ls2 = rand() % key_size;
			}
			if (ls1 > ls2)
			{
				int temp = ls1;
				ls1 = ls2;
				ls2 = temp;
			}
			int ls_job1, ls_job2;
			ls_job1 = ls_indiv.Product_C[ls1] + 1;
			ls_job2 = ls_indiv.Product_C[ls2] + 1;
			//cout << "ls_job1 = " << ls_job1 << endl;
			//cout << "ls_job2 = " << ls_job2 << endl;

			////step2����ls_indivȾɫ����Ѱ������job��λ������
			int ls_pos_index1 = 0;
			int ls_pos_index2 = 0;
			for (int u = 0; u < ls_indiv.v_chromosome2.size(); u++)
			{
				if (ls_indiv.v_chromosome2[u].job_number == ls_job1)
				{
					ls_pos_index1 = u;
					break;
				}
			}
			//cout << endl;
			for (int u = 0; u < ls_indiv.v_chromosome2.size(); u++)
			{
				if (ls_indiv.v_chromosome2[u].job_number == ls_job2)
				{
					ls_pos_index2 = u;
					break;
				}
			}
			//cout << "ls_pos_index1 = " << ls_pos_index1 << endl;
			//cout << "ls_pos_index2 = " << ls_pos_index2 << endl;

			////step3����ls_indivȾɫ����ɾ�������job
			ls_indiv.v_chromosome2.erase(ls_indiv.v_chromosome2.begin() + ls_pos_index2);
			int current_size = ls_indiv.v_chromosome2.size();
			//cout << "current_size = " << current_size << endl;
			//Ȼ���ٰ������뵽��ǰһ���operation��ǰ��λ��
			CChromosome tttt;
			tttt.job_number = ls_job2;
			ls_indiv.v_chromosome2.insert(ls_indiv.v_chromosome2.begin() + ls_pos_index1, tttt);
			current_size = ls_indiv.v_chromosome2.size();
			//cout << "current_size = " << current_size << endl;
		}
		else
		{
			//cout << "���Ų�·���ϵ�job���е�����" << endl;
			////step1�����ѡ�������ؼ�job
			int ls_size = ls_indiv.Job_C.size();
			int ls1 = rand() % ls_size;
			int ls2 = rand() % ls_size;
			while (ls1 == ls2)
			{
				ls2 = rand() % ls_size;
			}
			if (ls1 > ls2)
			{
				int temp = ls1;
				ls1 = ls2;
				ls2 = temp;
			}
			//cout << "ls1 = " << ls1 << endl;
			//cout << "ls2 = " << ls2 << endl;
			int ls_job1, ls_job2;
			ls_job1 = ls_indiv.Job_C[ls1];
			ls_job2 = ls_indiv.Job_C[ls2];
			//cout << "ls_job1 = " << ls_job1 << endl;
			//cout << "ls_job2 = " << ls_job2 << endl;
			int ls_operation1, ls_operation2;
			ls_operation1 = ls_indiv.Operation_C[ls1];
			ls_operation2 = ls_indiv.Operation_C[ls2];
			//cout << "ls_operation1 = " << ls_operation1 << endl;
			//cout << "ls_operation2 = " << ls_operation2 << endl;

			////step2���ҳ�Ⱦɫ������������ҵ��λ������
			////�ҵ�ls_operation1�γ��ֵ�ls_job1
			int ls_index1, ls_index2;
			int ls_count1 = 0;
			for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
			{
				if (ls_indiv.v_chromosome1[jj].operation_number == ls_job1)
				{
					ls_count1++;
				}
				if (ls_count1 == ls_operation1)
				{
					ls_index1 = jj;
					break;
				}
			}
			int ls_count2 = 0;
			for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
			{
				if (ls_indiv.v_chromosome1[jj].operation_number == ls_job2)
				{
					ls_count2++;
				}
				if (ls_count2 == ls_operation2)
				{
					ls_index2 = jj;
					break;
				}
			}
			//cout << "ls_index1 = " << ls_index1 << endl;
			//cout << "ls_index2 = " << ls_index2 << endl;


			////step3���������operation���뿿ǰ��operation��ǰ�棬������������
			//�Ƚ�ѡ�еĿ���һ���operation��Ⱦɫ����ɾ��
			ls_indiv.v_chromosome1.erase(ls_indiv.v_chromosome1.begin() + ls_index2);
			int current_size = ls_indiv.v_chromosome1.size();
			//cout << "current_size = " << current_size << endl;
			//Ȼ���ٰ������뵽��ǰһ���operation��ǰ��λ��
			CChromosome tttt;
			tttt.operation_number = ls_job2;
			ls_indiv.v_chromosome1.insert(ls_indiv.v_chromosome1.begin() + ls_index1, tttt);
			current_size = ls_indiv.v_chromosome1.size();
			//cout << "current_size = " << current_size << endl;
			//ͬʱ���������ǵ�job��Ϣ
			for (int k = 0; k < number_of_jobs * number_of_operations; k++)
			{
				ls_indiv.v_chromosome1[k].job_number = ls_indiv.v_chromosome1[k].operation_number;
			}
			//������job��Ϣ�������ǵ�operation_index��Ϣ
			for (int k = 0; k < number_of_jobs; k++)//�ж���ÿ��job�ĵڼ�������
			{
				int current_job_number = k + 1;
				int count = 0;
				for (int c = 0; c < number_of_jobs * number_of_operations; c++)
				{
					if (current_job_number == ls_indiv.v_chromosome1[c].job_number)
					{
						count = count + 1;
						ls_indiv.v_chromosome1[c].operation_index = count;
					}
					continue;
				}
			}
		}
	}
	else
	{
		//cout << "���Ų�·���ϵ�job���е�����" << endl;
		////step1�����ѡ�������ؼ�job
		int ls_size = ls_indiv.Job_C.size();
		int ls1 = rand() % ls_size;
		int ls2 = rand() % ls_size;
		while (ls1 == ls2)
		{
			ls2 = rand() % ls_size;
		}
		if (ls1 > ls2)
		{
			int temp = ls1;
			ls1 = ls2;
			ls2 = temp;
		}
		//cout << "ls1 = " << ls1 << endl;
		//cout << "ls2 = " << ls2 << endl;
		int ls_job1, ls_job2;
		ls_job1 = ls_indiv.Job_C[ls1];
		ls_job2 = ls_indiv.Job_C[ls2];
		//cout << "ls_job1 = " << ls_job1 << endl;
		//cout << "ls_job2 = " << ls_job2 << endl;
		int ls_operation1, ls_operation2;
		ls_operation1 = ls_indiv.Operation_C[ls1];
		ls_operation2 = ls_indiv.Operation_C[ls2];
		//cout << "ls_operation1 = " << ls_operation1 << endl;
		//cout << "ls_operation2 = " << ls_operation2 << endl;

		////step2���ҳ�Ⱦɫ������������ҵ��λ������
		////�ҵ�ls_operation1�γ��ֵ�ls_job1
		int ls_index1, ls_index2;
		int ls_count1 = 0;
		for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
		{
			if (ls_indiv.v_chromosome1[jj].operation_number == ls_job1)
			{
				ls_count1++;
			}
			if (ls_count1 == ls_operation1)
			{
				ls_index1 = jj;
				break;
			}
		}
		int ls_count2 = 0;
		for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
		{
			if (ls_indiv.v_chromosome1[jj].operation_number == ls_job2)
			{
				ls_count2++;
			}
			if (ls_count2 == ls_operation2)
			{
				ls_index2 = jj;
				break;
			}
		}
		//cout << "ls_index1 = " << ls_index1 << endl;
		//cout << "ls_index2 = " << ls_index2 << endl;


		////step3���������operation���뿿ǰ��operation��ǰ�棬������������
		//�Ƚ�ѡ�еĿ���һ���operation��Ⱦɫ����ɾ��
		ls_indiv.v_chromosome1.erase(ls_indiv.v_chromosome1.begin() + ls_index2);
		int current_size = ls_indiv.v_chromosome1.size();
		//cout << "current_size = " << current_size << endl;
		//Ȼ���ٰ������뵽��ǰһ���operation��ǰ��λ��
		CChromosome tttt;
		tttt.operation_number = ls_job2;
		ls_indiv.v_chromosome1.insert(ls_indiv.v_chromosome1.begin() + ls_index1, tttt);
		current_size = ls_indiv.v_chromosome1.size();
		//cout << "current_size = " << current_size << endl;
		//ͬʱ���������ǵ�job��Ϣ
		for (int k = 0; k < number_of_jobs * number_of_operations; k++)
		{
			ls_indiv.v_chromosome1[k].job_number = ls_indiv.v_chromosome1[k].operation_number;
		}
		//������job��Ϣ�������ǵ�operation_index��Ϣ
		for (int k = 0; k < number_of_jobs; k++)//�ж���ÿ��job�ĵڼ�������
		{
			int current_job_number = k + 1;
			int count = 0;
			for (int c = 0; c < number_of_jobs * number_of_operations; c++)
			{
				if (current_job_number == ls_indiv.v_chromosome1[c].job_number)
				{
					count = count + 1;
					ls_indiv.v_chromosome1[c].operation_index = count;
				}
				continue;
			}
		}
	}
}

void QPacking::ls_operation7(CIndividual& ls_indiv, vector<Item>& v_product)
{
	//cout << "�Թؼ�·������exchange������" << endl;

	//cout << "�����׶ιؼ�·��job�����ţ�" << endl;
	//for (int g = 0; g < ls_indiv.Product_C.size(); g++)
	//{
	//	cout << ls_indiv.Product_C[g] << " ";
	//}
	//cout << endl;

	//cout << "����׶ιؼ�·���������漰��job�����ţ�operation��������ţ�machine�����ţ�" << endl;
	//for (int k = 0; k < ls_indiv.Operation_C.size(); k++)
	//{
	//	int job_index = ls_indiv.Job_C[k] - 1;
	//	cout << "��ҵ������" << job_index << " ";
	//	int operation_index = ls_indiv.Operation_C[k] - 1;
	//	cout << "����������" << operation_index << " ";
	//	int machine_index = ls_indiv.Machine_C[k];
	//	cout << "����������" << machine_index << " ";//����������
	//	cout << endl;
	//}
	//cout << endl;
	//system("pause");

	int ls_size = ls_indiv.Job_C.size();
	//cout << "ls_size = " << ls_size << endl;
	//���ѡ��1���ؼ�job
	int ls = rand() % ls_size;
	//cout << "ls = " << ls << endl;
	int ls_job;
	ls_job = ls_indiv.Job_C[ls];
	//cout << "ls_job = " << ls_job << endl;
	int ls_operation;
	ls_operation = ls_indiv.Operation_C[ls];
	//cout << "ls_operation = " << ls_operation << endl;
	//��ȡ��job�ĸõ�����Ŀ�ʹ�û�������
	int operation_machine_size = v_available_machines[ls_job - 1][ls_operation - 1].size();
	//cout << "operation_machine_size = " << operation_machine_size << endl;
	if (operation_machine_size >= 2)
	{
		int rand_machine_number_index = rand() % operation_machine_size;
		//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
		int rand_machine_number = v_available_machines[ls_job - 1][ls_operation - 1][rand_machine_number_index];
		//cout << "rand_machine_number = " << rand_machine_number << endl;
		int index = (ls_job - 1) * number_of_operations + number_of_jobs * number_of_operations + (ls_operation - 1);
		//cout << "index = " << index << endl;
		int current_machine_number = ls_indiv.v_chromosome1[index].machine_number;
		while (current_machine_number == rand_machine_number)
		{
			rand_machine_number_index = rand() % operation_machine_size;
			//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
			rand_machine_number = v_available_machines[ls_job - 1][ls_operation - 1][rand_machine_number_index];
			//cout << "rand_machine_number = " << rand_machine_number << endl;
		}
		ls_indiv.v_chromosome1[index].machine_number = rand_machine_number;
	}
	//system("pause");
}
