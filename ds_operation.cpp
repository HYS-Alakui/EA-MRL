#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"
#include "Item.h"
#include <algorithm>
#include <map>

void QPacking::ds_operation(vector <CIndividual>& v_TotalChromo, vector <vector<CIndividual>>& v_Chromo, vector<Item>& v_product)
{
	//for (int m = 0; m < v_TotalChromo.size(); m++)
	//{
	//	cout << "m = " << m + 1 << endl;
	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
	//	{
	//		cout << v_TotalChromo[m].v_chromosome1[n].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
	//	{
	//		cout << v_TotalChromo[m].v_chromosome1[n].operation_index << " ";
	//	}
	//	cout << endl;
	//	for (int n = number_of_jobs * number_of_operations; n < v_TotalChromo[m].v_chromosome1.size(); n++)
	//	{
	//		cout << v_TotalChromo[m].v_chromosome1[n].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = number_of_jobs * number_of_operations; n < v_TotalChromo[m].v_chromosome1.size(); n++)
	//	{
	//		cout << v_TotalChromo[m].v_chromosome1[n].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < v_TotalChromo[m].v_chromosome2.size(); n++)
	//	{
	//		cout << v_TotalChromo[m].v_chromosome2[n].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < v_TotalChromo[m].v_ul_objectives.size(); n++)
	//	{
	//		for (int v = 0; v < v_TotalChromo[m].v_ul_objectives[n].size(); v++)
	//		{
	//			cout << v_TotalChromo[m].v_ul_objectives[n][v] << " ";
	//		}
	//	}
	//	cout << endl;
	//	cout << v_TotalChromo[m].upper_rank << " " << v_TotalChromo[m].upper_crowdedistance << endl;
	//	cout << v_TotalChromo[m].lower_rank << " " << v_TotalChromo[m].lower_crowdedistance << endl;
	//}
	//system("pause");

	vector <vector<CIndividual>>().swap(v_Chromo_temp);
	vector <vector<CIndividual>> v_Chromo_temp(v_Chromo);
	vector <vector<CIndividual>>().swap(v_new_Chromo);
	vector <CIndividual>().swap(v_new_TotalChromo);
	//cout << "��������ʱ��Ⱥ��" << endl;
	//for (int m = 0; m < v_Chromo_temp.size(); m++)
	//{
	//	cout << "sub_no = " << m + 1 << endl;
	//	for (int n = 0; n < v_Chromo_temp[m].size(); n++)
	//	{
	//		cout << "iner = " << n + 1 << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_Chromo_temp[m][n].v_chromosome1[u].operation_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_Chromo_temp[m][n].v_chromosome1[u].operation_index << " ";
	//		}
	//		cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_Chromo_temp[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_Chromo_temp[m][n].v_chromosome1[u].machine_number << " ";
	//		}
	//		cout << endl;
	//		//for (int u = number_of_jobs * number_of_operations; u < v_Chromo_temp[m][n].v_chromosome1.size(); u++)
	//		//{
	//		//	cout << v_Chromo_temp[m][n].v_chromosome1[u].job_number << " ";
	//		//}
	//		//cout << endl;
	//		for (int u = 0; u < v_Chromo_temp[m][n].v_chromosome2.size(); u++)
	//		{
	//			cout << v_Chromo_temp[m][n].v_chromosome2[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_Chromo_temp[m][n].v_ul_objectives.size(); u++)
	//		{
	//			for (int v = 0; v < v_Chromo_temp[m][n].v_ul_objectives[u].size(); v++)
	//			{
	//				cout << v_Chromo_temp[m][n].v_ul_objectives[u][v] << " ";
	//			}
	//		}
	//		cout << endl;
	//		//system("pause");
	//		cout << v_Chromo_temp[m][n].upper_rank << ",  " << v_Chromo_temp[m][n].upper_crowdedistance << endl;
	//		cout << v_Chromo_temp[m][n].lower_rank << ",  " << v_Chromo_temp[m][n].lower_crowdedistance << endl;
	//		//system("pause");
	//	}
	//	cout << endl<<endl;
	//}
	//system("pause");


	for (int i = 0; i < number_of_subpop; i++)
	{
		//cout << "i = " << i + 1 << endl;
		vector <CIndividual> v_new_subChromo;
		vector <CIndividual>().swap(v_new_subChromo);
		for (int j = 0; j < lower_number_of_individuals; j++)//��ÿ������ִ�����ٺ��ع�����
		{
			//cout << "j = " << j << endl;
			
			////�жϵ�ǰ�����rank_value
			if (v_Chromo_temp[i][j].upper_rank == 1)
			{
				//cout << "ִ��DC������" << endl;
				CIndividual des_indiv = v_Chromo_temp[i][j];
				ds_operation_individual(des_indiv, v_product);//��ÿ������ִ�����ٺ��ع�����

				CIndividual new_sub_indv;
				new_sub_indv.sub_no = i + 1;
				for (int u = 0; u < des_indiv.v_upper_chromosome1.size(); u++)
				{
					CChromosome cc1;
					cc1.operation_number = des_indiv.v_upper_chromosome1[u].operation_number;
					cc1.operation_index = des_indiv.v_upper_chromosome1[u].operation_index;
					cc1.job_number = des_indiv.v_upper_chromosome1[u].operation_number;
					new_sub_indv.v_chromosome1.push_back(cc1);
				}
				int count_operation = 0;
				int count_job_num = 1;
				for (int u = 0; u < des_indiv.v_upper_chromosome2.size(); u++)
				{
					CChromosome cc2;
					cc2.machine_number = des_indiv.v_upper_chromosome2[u].machine_number;
					if (count_operation < number_of_operations)
					{
						cc2.job_number = count_job_num;
					}
					else
					{
						count_operation = 0;
						count_job_num++;
						cc2.job_number = count_job_num;
					}
					new_sub_indv.v_chromosome1.push_back(cc2);
					count_operation++;
				}
				for (int u = 0; u < des_indiv.v_lower_chromosome.size(); u++)
				{
					CChromosome cc3;
					cc3.job_number = des_indiv.v_lower_chromosome[u].job_number;
					new_sub_indv.v_chromosome2.push_back(cc3);
				}
				//cout << "����-�ع����new_sub_indv�⣺" << endl;
				//for (int s = 0; s < new_sub_indv.v_chromosome1.size() / 2; s++)
				//{
				//	cout << new_sub_indv.v_chromosome1[s].operation_number << " ";
				//}
				//cout << endl;
				//for (int s = 0; s < new_sub_indv.v_chromosome1.size() / 2; s++)
				//{
				//	cout << new_sub_indv.v_chromosome1[s].operation_index << " ";
				//}
				//cout << endl;
				//for (int s = new_sub_indv.v_chromosome1.size() / 2; s < new_sub_indv.v_chromosome1.size(); s++)
				//{
				//	cout << new_sub_indv.v_chromosome1[s].machine_number << " ";
				//}
				//cout << endl;
				//for (int s = new_sub_indv.v_chromosome1.size() / 2; s < new_sub_indv.v_chromosome1.size(); s++)
				//{
				//	cout << new_sub_indv.v_chromosome1[s].job_number << " ";
				//}
				//cout << endl;
				//for (int s = 0; s < new_sub_indv.v_chromosome2.size(); s++)
				//{
				//	cout << new_sub_indv.v_chromosome2[s].job_number << " ";
				//}
				//cout << endl;
				//system("pause");
				upper_evaluate(new_sub_indv, board_width, board_height, v_product);//���ϲ���²�Ŀ�꺯��ֵ�������²�Ŀ��ֵ��Ȼ������²�Լ������ϲ�Ŀ��ֵ
				//for (int s = 0; s < new_sub_indv.v_ul_objectives.size(); s++)
				//{
				//	for (int ss = 0; ss < new_sub_indv.v_ul_objectives[s].size(); ss++)
				//	{
				//		cout << new_sub_indv.v_ul_objectives[s][ss] << " ";
				//	}
				//}
				//cout << endl;
				v_new_subChromo.push_back(new_sub_indv);
				v_new_TotalChromo.push_back(new_sub_indv);
				//system("pause");
			}
			else
			{
				//cout << "����ѡ��-����-����õ��Ӵ���" << endl;			
				CIndividual new_sub_indv;
				new_sub_indv.sub_no = i + 1;

				////step1.1: ���ö�Ԫ������ѡ�����ѡ��һ��������Ϊ�ϲ�ĸ��
				CIndividual upper_fathIndiv, upper_mothIndiv, upper_chIndiv1, upper_chIndiv2;
				upper_fathIndiv = v_Chromo_temp[i][j];
				int upper_parent_sub_no_1, upper_parent_sub_no_2;
				upper_parent_sub_no_1 = rand() % number_of_subpop;
				//cout << "upper_parent_sub_no_1 = " << upper_parent_sub_no_1 << endl;
				upper_parent_sub_no_2 = rand() % number_of_subpop;
				while (upper_parent_sub_no_2 == upper_parent_sub_no_1)
				{
					upper_parent_sub_no_2 = rand() % number_of_subpop;
				}
				//cout << "upper_parent_sub_no_2 = " << upper_parent_sub_no_2 << endl;
				int low_index_1 = rand() % lower_number_of_individuals;
				//cout << "low_index_1 = " << low_index_1 << endl;
				int low_index_2 = rand() % lower_number_of_individuals;
				//cout << "low_index_2 = " << low_index_2 << endl;
				int u_rank_1 = v_Chromo_temp[upper_parent_sub_no_1][low_index_1].upper_rank;
				//cout << "u_rank_1 = " << u_rank_1 << endl;
				int u_rank_2 = v_Chromo_temp[upper_parent_sub_no_2][low_index_2].upper_rank;
				//cout << "u_rank_2 = " << u_rank_2 << endl;
				double u_dist_1 = v_Chromo_temp[upper_parent_sub_no_1][low_index_1].upper_crowdedistance;
				//cout << "u_dist_1 = " << u_dist_1 << endl;
				double u_dist_2 = v_Chromo_temp[upper_parent_sub_no_2][low_index_2].upper_crowdedistance;
				//cout << "u_dist_2 = " << u_dist_2 << endl;
				if (u_rank_1 == u_rank_2 && u_dist_1 == u_dist_2)
				{
					int rand_num = rand() % 2;
					if (rand_num == 0)
					{
						upper_mothIndiv = v_Chromo_temp[upper_parent_sub_no_1][low_index_1];
					}
					else
					{
						upper_mothIndiv = v_Chromo_temp[upper_parent_sub_no_2][low_index_2];
					}
				}
				else if ((u_rank_1 == u_rank_2 && u_dist_1 > u_dist_2) || (u_rank_1 < u_rank_2))
				{
					upper_mothIndiv = v_Chromo_temp[upper_parent_sub_no_1][low_index_1];
				}
				else
				{
					upper_mothIndiv = v_Chromo_temp[upper_parent_sub_no_2][low_index_2];
				}

				////Step1.2�����ý��溯�����������������ϲ������v_chromosome1���н��棬�õ������µ��Ӵ��ϲ�����
				upper_crossover(upper_fathIndiv, upper_mothIndiv, upper_chIndiv1, upper_chIndiv2);

				////Step1.3�����ñ��캯�������һ���Ӵ��ϲ��������б���
				int rand_number = rand() % 2;
				if (rand_number == 0)
				{
					upper_mutate(upper_chIndiv1, 0.95);
					new_sub_indv.v_chromosome1 = upper_chIndiv1.v_chromosome1;
				}
				else
				{
					upper_mutate(upper_chIndiv2, 0.95);
					new_sub_indv.v_chromosome1 = upper_chIndiv2.v_chromosome1;
				}

				//////////////////////////////////////���ϻ�ȡ���Ӵ����ϲ�����///////////////////////////////////
				//////////////////////////////////////���»�ȡ���Ӵ����²�����///////////////////////////////////
				CIndividual upper_lower_fathIndiv, upper_lower_mothIndiv, upper_lower_chIndiv1, upper_lower_chIndiv2;
				upper_lower_fathIndiv = upper_fathIndiv;
				upper_lower_mothIndiv = upper_mothIndiv;

				////Step2.1�����ý��溯�����������������²������v_chromosome2���н��棬�õ������µ��Ӵ��²�����
				lower_crossover(upper_lower_fathIndiv, upper_lower_mothIndiv, upper_lower_chIndiv1, upper_lower_chIndiv2);
				
				////Step2.2�����ñ��캯�������һ���Ӵ��²��������б���
				int rand_number2 = rand() % 2;
				if (rand_number2 == 0)
				{
					lower_mutate(upper_lower_chIndiv1, 0.95);
					new_sub_indv.v_chromosome2 = upper_lower_chIndiv1.v_chromosome2;
				}
				else
				{
					lower_mutate(upper_lower_chIndiv2, 0.95);
					new_sub_indv.v_chromosome2 = upper_lower_chIndiv2.v_chromosome2;
				}

				//cout << "ѡ��-����-������new_sub_indv�⣺" << endl;
				//for (int s = 0; s < new_sub_indv.v_chromosome1.size() / 2; s++)
				//{
				//	cout << new_sub_indv.v_chromosome1[s].operation_number << " ";
				//}
				//cout << endl;
				//for (int s = 0; s < new_sub_indv.v_chromosome1.size() / 2; s++)
				//{
				//	cout << new_sub_indv.v_chromosome1[s].operation_index << " ";
				//}
				//cout << endl;
				//for (int s = new_sub_indv.v_chromosome1.size() / 2; s < new_sub_indv.v_chromosome1.size(); s++)
				//{
				//	cout << new_sub_indv.v_chromosome1[s].machine_number << " ";
				//}
				//cout << endl;
				//for (int s = new_sub_indv.v_chromosome1.size() / 2; s < new_sub_indv.v_chromosome1.size(); s++)
				//{
				//	cout << new_sub_indv.v_chromosome1[s].job_number << " ";
				//}
				//cout << endl;
				//for (int s = 0; s < new_sub_indv.v_chromosome2.size(); s++)
				//{
				//	cout << new_sub_indv.v_chromosome2[s].job_number << " ";
				//}
				//cout << endl;
				//system("pause");
				
				////step3����new_sub_indv����ֵ�������䱣��
				upper_evaluate(new_sub_indv, board_width, board_height, v_product);//���ϲ���²�Ŀ�꺯��ֵ�������²�Ŀ��ֵ��Ȼ������²�Լ������ϲ�Ŀ��ֵ
				//for (int s = 0; s < new_sub_indv.v_ul_objectives.size(); s++)
				//{
				//	for (int ss = 0; ss < new_sub_indv.v_ul_objectives[s].size(); ss++)
				//	{
				//		cout << new_sub_indv.v_ul_objectives[s][ss] << " ";
				//	}
				//}
				//cout << endl;
				v_new_subChromo.push_back(new_sub_indv);
				v_new_TotalChromo.push_back(new_sub_indv);
				//system("pause");
			}
		}
		v_new_Chromo.push_back(v_new_subChromo);
	}


	//cout << "D-C�������Ⱥ��" << endl;
	//for (int m = 0; m < v_new_Chromo.size(); m++)
	//{
	//	cout << "sub_no = " << m + 1 << endl;
	//	for (int n = 0; n < v_new_Chromo[m].size(); n++)
	//	{
	//		cout << "iner = " << n + 1 << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_new_Chromo[m][n].v_chromosome1[u].operation_number << " ";
	//		}
	//		cout << endl;
	//		//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		//{
	//		//	cout << v_new_Chromo[m][n].v_chromosome1[u].operation_index << " ";
	//		//}
	//		//cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_new_Chromo[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_new_Chromo[m][n].v_chromosome1[u].machine_number << " ";
	//		}
	//		cout << endl;
	//		//for (int u = number_of_jobs * number_of_operations; u < v_new_Chromo[m][n].v_chromosome1.size(); u++)
	//		//{
	//		//	cout << v_new_Chromo[m][n].v_chromosome1[u].job_number << " ";
	//		//}
	//		//cout << endl;
	//		for (int u = 0; u < v_new_Chromo[m][n].v_chromosome2.size(); u++)
	//		{
	//			cout << v_new_Chromo[m][n].v_chromosome2[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_new_Chromo[m][n].v_ul_objectives.size(); u++)
	//		{
	//			for (int v = 0; v < v_new_Chromo[m][n].v_ul_objectives[u].size(); v++)
	//			{
	//				cout << v_new_Chromo[m][n].v_ul_objectives[u][v] << " ";
	//			}
	//		}
	//		cout << endl;
	//	}
	//	cout << endl << endl;
	//}
	//system("pause");
}

void QPacking::ds_operation_individual(CIndividual& des_indiv, vector<Item>& v_product)
{
	//cout << "����-�ع�ǰ��des_indiv�⣺" << endl;
	//for (int s = 0; s < des_indiv.v_chromosome1.size()/2; s++)
	//{
	//	cout << des_indiv.v_chromosome1[s].operation_number << " ";
	//}
	//cout << endl;
	//for (int s = 0; s < des_indiv.v_chromosome1.size()/2; s++)
	//{
	//	cout << des_indiv.v_chromosome1[s].operation_index << " ";
	//}
	//cout << endl;
	//for (int s = des_indiv.v_chromosome1.size() / 2; s < des_indiv.v_chromosome1.size(); s++)
	//{
	//	cout << des_indiv.v_chromosome1[s].machine_number << " ";
	//}
	//cout << endl;
	//for (int s = 0; s < des_indiv.v_chromosome2.size(); s++)
	//{
	//	cout << des_indiv.v_chromosome2[s].job_number << " ";
	//}
	//cout << endl;
	//for (int s = 0; s < des_indiv.v_ul_objectives.size(); s++)
	//{
	//	for (int ss = 0; ss < des_indiv.v_ul_objectives[s].size(); ss++)
	//	{
	//		cout << des_indiv.v_ul_objectives[s][ss] << " ";
	//	}
	//}
	//cout << endl << endl;

	////׼������
	vector<int> v_delete_jobs;
	vector<int> v_delete_machines;
	vector<int> v_intial_machine_assignment;
	for (int u = number_of_jobs * number_of_operations; u < des_indiv.v_chromosome1.size(); u++)
	{
		v_intial_machine_assignment.push_back(des_indiv.v_chromosome1[u].machine_number);
	}

	////���ٲ���
	destruction(des_indiv, v_delete_jobs, v_delete_machines);
	//cout << "job��" << endl;
	//for (int u = 0; u < v_delete_jobs.size(); u++)
	//{
	//	cout << v_delete_jobs[u] << " ";
	//}
	//cout << endl;
	//cout << "machine��" << endl;
	//for (int u = 0; u < v_delete_machines.size(); u++)
	//{
	//	cout << v_delete_machines[u] << " ";
	//}
	//cout << endl;
	//cout << "gene��" << endl;
	for (int u = 0; u < des_indiv.v_chromosome1.size() / 2; u++)
	{
		//cout << des_indiv.v_chromosome1[u].operation_number << " ";
		CChromosome up1;
		up1.operation_number = des_indiv.v_chromosome1[u].operation_number;
		up1.job_number = des_indiv.v_chromosome1[u].operation_number;
		des_indiv.v_upper_chromosome1.push_back(up1);
	}
	for (int u = des_indiv.v_chromosome1.size() / 2; u < des_indiv.v_chromosome1.size(); u++)
	{
		//cout << des_indiv.v_chromosome1[u].machine_number << " ";
		CChromosome up2;
		up2.machine_number = des_indiv.v_chromosome1[u].machine_number;
		des_indiv.v_upper_chromosome2.push_back(up2);
	}
	for (int u = 0; u < des_indiv.v_chromosome2.size(); u++)
	{
		//cout << des_indiv.v_chromosome2[u].job_number << " ";
		CChromosome low;
		low.job_number = des_indiv.v_chromosome2[u].job_number;
		des_indiv.v_lower_chromosome.push_back(low);
	}
	//system("pause");


	////�ع�����
	construction(des_indiv, v_delete_jobs, v_delete_machines, v_intial_machine_assignment, v_product);
	//cout << "����-�ع����des_indiv�⣺" << endl;
	//for (int s = 0; s < des_indiv.v_upper_chromosome1.size(); s++)
	//{
	//	cout << des_indiv.v_upper_chromosome1[s].operation_number << " ";
	//}
	//cout << endl;
	//for (int s = 0; s < des_indiv.v_upper_chromosome1.size(); s++)
	//{
	//	cout << des_indiv.v_upper_chromosome1[s].operation_index << " ";
	//}
	//cout << endl;
	//for (int s = 0; s < des_indiv.v_upper_chromosome2.size(); s++)
	//{
	//	cout << des_indiv.v_upper_chromosome2[s].machine_number << " ";
	//}
	//cout << endl;
	//for (int s = 0; s < des_indiv.v_lower_chromosome.size(); s++)
	//{
	//	cout << des_indiv.v_lower_chromosome[s].job_number << " ";
	//}
	//cout << endl;
	//for (int s = 0; s < des_indiv.v_ul_objectives.size(); s++)
	//{
	//	for (int ss = 0; ss < des_indiv.v_ul_objectives[s].size(); ss++)
	//	{
	//		cout << des_indiv.v_ul_objectives[s][ss] << " ";
	//	}
	//}
	//cout << endl;
}

void QPacking::destruction(CIndividual& INDIV, vector<int>& v_delete_jobs, vector<int>& v_delete_machines)
{
	//cout << "��ǰ����Ļ���" << endl;
	//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//{
	//	cout << INDIV.v_chromosome1[u].operation_number << " ";
	//}
	//cout << endl;
	//for (int u = number_of_jobs * number_of_operations; u < INDIV.v_chromosome1.size(); u++)
	//{
	//	cout << INDIV.v_chromosome1[u].machine_number << " ";
	//}
	//cout << endl;

	//���ÿ���ϲ�������������
	//step1���������ٳ���
	int destruction_length = round(0.1 * number_of_jobs);//ɾ����������
	//cout << "destruction_length = " << destruction_length << endl;
	int* p_destruction = new int[destruction_length];//����һ�����鴢��ɾ���Ĺ���

	//step2���ҳ��������tardiness��job
	int max_tardi_jobindex = INDIV.max_tardiness_job_index;
	//cout << "max_tardi_jobindex = " << max_tardi_jobindex << endl;

	//step3������d1 = min(d/2,dj)��dj����ҵj�Ĺ�����Ŀ��d��destruction_length�� d2 = d-d1
	int d1 = min(destruction_length / 2, number_of_operations);
	//cout << "d1 = " << d1 << endl;
	int d2 = destruction_length - d1;
	//cout << "d2 = " << d2 << endl;

	//step4��ȷ�����ٵĹ���λ�úͶ�Ӧ�Ļ���λ��
	vector<int> v_delete_job_pos_index;
	vector<int> v_delete_machine_pos_index;
	vector<int> v_now_jobs_index;
	v_now_jobs_index.push_back(max_tardi_jobindex);
	int count1 = 0;
	while (count1 < d1)
	{
		int right_index = number_of_operations - count1 % number_of_operations;
		//cout << "right_index = " << right_index << endl;			
		int right_job_pos_index;
		for (int mm = 0; mm < INDIV.v_chromosome1.size(); mm++)//�ҳ�job�ĵ�right_index�������λ��
		{
			if (INDIV.v_chromosome1[mm].job_number == max_tardi_jobindex + 1 && INDIV.v_chromosome1[mm].operation_index == right_index)
			{
				right_job_pos_index = mm;
				break;
			}
		}
		//cout << "right_job_pos_index = " << right_job_pos_index << endl;
		v_delete_job_pos_index.push_back(right_job_pos_index);
		v_delete_jobs.push_back(INDIV.v_chromosome1[right_job_pos_index].job_number);
		int right_machine_pos_index = number_of_jobs * number_of_operations + max_tardi_jobindex * number_of_operations + right_index - 1;
		//cout << "right_machi_pos_index = " << right_machine_pos_index << endl;
		v_delete_machine_pos_index.push_back(right_machine_pos_index);
		v_delete_machines.push_back(INDIV.v_chromosome1[right_machine_pos_index].machine_number);
		count1++;
		//cout << "count1 = " << count1 << endl;
	}
	int count2 = 0;
	int rand_jobindex;
	while (count2 < d2)
	{
		int right_index = number_of_operations - count2 % number_of_operations;
		//cout << "right_index = " << right_index << endl;

		if (right_index == number_of_operations)
		{
			//cout << "ѡ����һ��job" << endl;
			bool isPresent;
			do
			{
				rand_jobindex = rand() % number_of_jobs;
				//cout << "rand_jobindex = " << rand_jobindex << endl;
				isPresent = false;
				for (int index : v_now_jobs_index)// ������ɵ������Ƿ������ v_now_jobs_index ��
				{
					if (rand_jobindex == index)
					{
						isPresent = true;
						break;
					}
				}
			} while (isPresent); // ������ڣ���������			
			v_now_jobs_index.push_back(rand_jobindex);
		}
		//cout << "rand_jobindex = " << rand_jobindex << endl;

		int right_job_pos_index;
		for (int mm = 0; mm < INDIV.v_chromosome1.size(); mm++)//�ҳ�job�ĵ�right_index�������λ��
		{
			if (INDIV.v_chromosome1[mm].job_number == rand_jobindex + 1 && INDIV.v_chromosome1[mm].operation_index == right_index)
			{
				right_job_pos_index = mm;
				break;
			}
		}
		//cout << "right_job_pos_index = " << right_job_pos_index << endl;
		v_delete_job_pos_index.push_back(right_job_pos_index);
		v_delete_jobs.push_back(INDIV.v_chromosome1[right_job_pos_index].job_number);
		int right_machine_pos_index = number_of_jobs * number_of_operations + rand_jobindex * number_of_operations + right_index - 1;
		//cout << "right_machi_pos_index = " << right_machine_pos_index << endl;
		v_delete_machine_pos_index.push_back(right_machine_pos_index);
		v_delete_machines.push_back(INDIV.v_chromosome1[right_machine_pos_index].machine_number);
		count2++;
		//cout << "count2 = " << count2 << endl;
		//system("pause");
	}
	//cout << "job_pos_index��" << endl;
	//for (int u = 0; u < v_delete_job_pos_index.size(); u++)
	//{
	//	cout << v_delete_job_pos_index[u] << " ";
	//}
	//cout << endl;
	//cout << "machine_pos_index��" << endl;
	//for (int u = 0; u < v_delete_machine_pos_index.size(); u++)
	//{
	//	cout << v_delete_machine_pos_index[u] << " ";
	//}
	//cout << endl;
	//cout << "job��" << endl;
	//for (int u = 0; u < v_delete_jobs.size(); u++)
	//{
	//	cout << v_delete_jobs[u] << " ";
	//}
	//cout << endl;
	//cout << "machine��" << endl;
	//for (int u = 0; u < v_delete_machines.size(); u++)
	//{
	//	cout << v_delete_machines[u] << " ";
	//}
	//system("pause");

	//step5��ɾ����Ӧ�Ĺ��򼰻���
	sort(v_delete_machine_pos_index.begin(), v_delete_machine_pos_index.end(), greater<int>());
	sort(v_delete_job_pos_index.begin(), v_delete_job_pos_index.end(), greater<int>());
	for (int u = 0; u < v_delete_machine_pos_index.size(); u++)
	{
		INDIV.v_chromosome1.erase(INDIV.v_chromosome1.begin() + v_delete_machine_pos_index[u]);
	}
	for (int u = 0; u < v_delete_job_pos_index.size(); u++)
	{
		INDIV.v_chromosome1.erase(INDIV.v_chromosome1.begin() + v_delete_job_pos_index[u]);
	}
	//cout << "ɾ������Ļ���" << endl;
	//for (int u = 0; u < INDIV.v_chromosome1.size() / 2; u++)
	//{
	//	cout << INDIV.v_chromosome1[u].operation_number << " ";
	//}
	//cout << endl;
	//for (int u = INDIV.v_chromosome1.size() / 2; u < INDIV.v_chromosome1.size(); u++)
	//{
	//	cout << INDIV.v_chromosome1[u].machine_number << " ";
	//}
	//cout << endl;
	//system("pause");
}

void QPacking::construction(CIndividual& INDIV, vector<int>& v_delete_jobs, vector<int>& v_delete_machines, vector<int>& v_intial_machine_assignment, vector<Item>& v_product)
{
	//cout << "INPUT_initial_machine_assignment��" << endl;
	//for (int u = 0; u < v_intial_machine_assignment.size(); u++)
	//{
	//	cout << v_intial_machine_assignment[u] << " ";
	//}
	//cout << endl;

	//cout << "INPUT_delete_jobs��" << endl;
	//for (int u = 0; u < v_delete_jobs.size(); u++)
	//{
	//	cout << v_delete_jobs[u] << " ";
	//}
	//cout << endl;

	//cout << "INPUT_new_genes��" << endl;
	//for (int u = 0; u < INDIV.v_upper_chromosome1.size(); u++)
	//{
	//	cout << INDIV.v_upper_chromosome1[u].operation_number << " ";
	//}
	//cout << endl;
	//for (int u = 0; u < INDIV.v_upper_chromosome2.size(); u++)
	//{
	//	cout << INDIV.v_upper_chromosome2[u].machine_number << " ";
	//}
	//cout << endl;
	//for (int u = 0; u < INDIV.v_lower_chromosome.size(); u++)
	//{
	//	cout << INDIV.v_lower_chromosome[u].job_number << " ";
	//}
	//cout << endl;
	//system("pause");

	for (int u = 0; u < v_delete_jobs.size(); u++)
	{
		//cout << "����ǰINDIV��" << endl;
		//for (int s = 0; s < INDIV.v_upper_chromosome1.size(); s++)
		//{
		//	cout << INDIV.v_upper_chromosome1[s].operation_number << " ";
		//}
		//cout << endl;
		//for (int s = 0; s < INDIV.v_upper_chromosome1.size(); s++)
		//{
		//	cout << INDIV.v_upper_chromosome1[s].operation_index << " ";
		//}
		//cout << endl;
		//for (int s = 0; s < INDIV.v_upper_chromosome2.size(); s++)
		//{
		//	cout << INDIV.v_upper_chromosome2[s].machine_number << " ";
		//}
		//cout << endl;
		//system("pause");


		////STEP1: ���Ҫ�����job��delete_job_number
		int delete_job_number = v_delete_jobs[u];
		//cout << "STEP1: delete_job_number = " << delete_job_number << endl;
		CChromosome newccc1;
		newccc1.job_number = delete_job_number;
		newccc1.operation_number = delete_job_number;
		newccc1.operation_index = 0;


		////STEP2: ��delete_job_number���뵽��ǰ�������λ�û��һ������⼯
		//cout << "STEP2: ��delete_job_number���뵽��ǰ�������λ�û��һ������⼯��" << endl;
		vector <CIndividual> v_nebo_individuals;//����ÿ�������
		for (int v = 0; v < INDIV.v_upper_chromosome1.size(); v++)
		{
			////step1������һ���µĸ��壬�������е�Ⱦɫ��
			CIndividual newIndiv = INDIV; 
			//cout << "����ǰnewIndiv��" << endl;
			//for (int s = 0; s < newIndiv.v_upper_chromosome1.size(); s++)
			//{
			//	cout << newIndiv.v_upper_chromosome1[s].operation_number << " ";
			//}
			//cout << endl;
			//for (int s = 0; s < newIndiv.v_upper_chromosome1.size(); s++)
			//{
			//	cout << newIndiv.v_upper_chromosome1[s].operation_index << " ";
			//}
			//cout << endl;
			//for (int s = 0; s < newIndiv.v_upper_chromosome2.size(); s++)
			//{
			//	cout << newIndiv.v_upper_chromosome2[s].machine_number << " ";
			//}
			//cout << endl;
			//system("pause");

			////step2�����빤�����	
			newIndiv.v_upper_chromosome1.insert(newIndiv.v_upper_chromosome1.begin() + v, newccc1);	
			//cout << "������newIndiv��v_upper_chromosome1��" << endl;
			//for (int s = 0; s < newIndiv.v_upper_chromosome1.size(); s++)
			//{
			//	cout << newIndiv.v_upper_chromosome1[s].operation_number << " ";
			//}
			//cout << endl;
			//system("pause");


			////step3�����������׼��	
			vector<int> v_operation_numbers; //�ѹ�����򣨺��²��빤�򣩷���������
			for (int s = 0; s < newIndiv.v_upper_chromosome1.size(); s++)
			{
				v_operation_numbers.push_back(newIndiv.v_upper_chromosome1[s].operation_number);
			}
			map<int, int> countMap;// ʹ�� map ������ÿ�����֣�job���ĳ��ִ��� countMap�ļ���job�ţ���ֵ��job��������ĳ��ִ���
			for (int num : v_operation_numbers) 
			{
				countMap[num]++;
			}
			//for (const auto& pair : countMap) // ���countMap
			//{
			//	cout << "Job " << pair.first << " ���� " << pair.second << " �Σ�" << std::endl;
			//}

			vector<pair<int, int>> v_job_counts;// ����һ�� vector ���洢ÿ�����ֵĳ��ִ���
			for (const auto& vjc : countMap) 
			{
				int job_id = vjc.first;  //job��
				int operation_count = vjc.second; //job�����Ĺ�����
				v_job_counts.push_back(make_pair(job_id, operation_count));
			}
			//cout << "ÿ��job���ֵĴ���:" << std::endl;
			//for (const auto& count : v_job_counts)
			//{
			//	cout << "(" << count.first << ", ";
			//	cout << count.second << ")";
			//}
			//cout << endl;
			//system("pause");

			for (const auto& pair : countMap) //���²����ÿ����������
			{
				int current_job_number = pair.first;
				//cout << "current_job_number = " << current_job_number << endl;			
				int count = 0;		
				for (int o = 0; o < newIndiv.v_upper_chromosome1.size(); o++)
				{
					//cout << "o = " << o << endl;
					if (current_job_number == newIndiv.v_upper_chromosome1[o].job_number)
					{
						count = count + 1;
						newIndiv.v_upper_chromosome1[o].operation_index = count;
						//cout << "count = " << count << endl;
					}
					continue;
				}
			}
			//for (int s = 0; s < newIndiv.v_upper_chromosome1.size(); s++)
			//{
			//	cout << newIndiv.v_upper_chromosome1[s].operation_index << " ";
			//}
			//cout << endl;
			//system("pause");

			//cout << "��ȡҪ�����job��Ӧ����Ļ����ţ�" << endl;
			int insert_job_oper_count = countMap[delete_job_number];//�����ڣ�����ʹ���±������ [] ����ȡ��ü�������ֵ
			//cout << "insert_job_oper_count = " << insert_job_oper_count << endl;
			int insert_job_mach_index = (delete_job_number - 1) * number_of_operations + insert_job_oper_count - 1;//��ȡ�ĸ�job���ĵ�������ܻ�ȡ���λ���ڳ�ʼȾɫ���ϵ�����
			//cout << "insert_job_mach_index = " << insert_job_mach_index << endl;
			int insert_job_mach_number = v_intial_machine_assignment[insert_job_mach_index];//��ȡ����λ�����������ҵ��������job��Ҫ��machine
			//cout << "insert_job_mach_number = " << insert_job_mach_number << endl;
			//system("pause");

			CChromosome newccc2;
			newccc2.machine_number = insert_job_mach_number;
			int pos_machine_index = 0;
			//cout << "ȷ������λ�û���������" << endl;
			for (const auto& count : v_job_counts)
			{
				if (count.first <= delete_job_number)
				{
					pos_machine_index += count.second;
				}
				else
				{
					break;
				}		
			}
			pos_machine_index = pos_machine_index - 1;
			//cout << "pos_machine_index = " << pos_machine_index << endl;

			////step4�������������
			newIndiv.v_upper_chromosome2.insert(newIndiv.v_upper_chromosome2.begin() + pos_machine_index, newccc2);	
			//cout << "������newIndiv��v_upper_chromosome2��" << endl;
			//for (int s = 0; s < newIndiv.v_upper_chromosome2.size(); s++)
			//{
			//	cout << newIndiv.v_upper_chromosome2[s].machine_number << " ";
			//}
			//cout << endl;
			//system("pause");


			////step5������ÿ��delete_job�������
			v_nebo_individuals.push_back(newIndiv); 
		}
		

		////STEP3: ��������⼯
		//cout << "STEP3: ��������㵱ǰdelete_job���������⼯��" << endl;
		for (int v = 0; v < v_nebo_individuals.size(); v++)
		{
			//cout << "nebo_no = " << v + 1 << endl;
			//for (int s = 0; s < v_nebo_individuals[v].v_upper_chromosome1.size(); s++)
			//{
			//	cout << v_nebo_individuals[v].v_upper_chromosome1[s].operation_number << " ";
			//}
			//cout << endl;
			//for (int s = 0; s < v_nebo_individuals[v].v_upper_chromosome1.size(); s++)
			//{
			//	cout << v_nebo_individuals[v].v_upper_chromosome1[s].operation_index << " ";
			//}
			//cout << endl;
			//for (int s = 0; s < v_nebo_individuals[v].v_upper_chromosome2.size(); s++)
			//{
			//	cout << v_nebo_individuals[v].v_upper_chromosome2[s].machine_number << " ";
			//}
			//cout << endl;
			//for (int s = 0; s < v_nebo_individuals[v].v_lower_chromosome.size(); s++)
			//{
			//	cout << v_nebo_individuals[v].v_lower_chromosome[s].job_number << " ";
			//}
			//cout << endl << endl;
			
			evaluate_construction(v_nebo_individuals[v], v_product);
			//for (int s = 0; s < v_nebo_individuals[v].v_ul_objectives.size(); s++)
			//{
			//	for (int ss = 0; ss < v_nebo_individuals[v].v_ul_objectives[s].size(); ss++)
			//	{
			//		cout << v_nebo_individuals[v].v_ul_objectives[s][ss] << " ";
			//	}
			//}
			//cout << endl << endl;
		}


		////STEP4: �ҵ���ѵ�nebo���壬����������INDIV��Ȼ�����������Ͽ�ʼ��һ��delete_job_number�Ĳ���
		//cout << "STEP4: �ҵ����nebo�������Ը���INDIV" << endl;
		CIndividual best_nebo_indiv = v_nebo_individuals[0];
		int best_nebo_no = 0;
		int domRel = 3;
		for (int v = 0; v < v_nebo_individuals.size(); v++)
		{
			CIndividual current_nebo_indiv = v_nebo_individuals[v];
			domRelation_up(best_nebo_indiv, current_nebo_indiv, domRel);
			if (domRel == 1)
			{
				best_nebo_indiv = best_nebo_indiv;
				best_nebo_no = best_nebo_no;
			}
			else
			{
				best_nebo_indiv = current_nebo_indiv;
				best_nebo_no = v;
			}
		}
		INDIV = best_nebo_indiv;//����INDIV
		//cout << "�����" << endl;
		//for (int s = 0; s < INDIV.v_upper_chromosome1.size(); s++)
		//{
		//	cout << INDIV.v_upper_chromosome1[s].operation_number << " ";
		//}
		//cout << endl;
		//for (int s = 0; s < INDIV.v_upper_chromosome1.size(); s++)
		//{
		//	cout << INDIV.v_upper_chromosome1[s].operation_index << " ";
		//}
		//cout << endl;
		//for (int s = 0; s < INDIV.v_upper_chromosome2.size(); s++)
		//{
		//	cout << INDIV.v_upper_chromosome2[s].machine_number << " ";
		//}
		//cout << endl;
		//for (int s = 0; s < INDIV.v_lower_chromosome.size(); s++)
		//{
		//	cout << INDIV.v_lower_chromosome[s].job_number << " ";
		//}
		//cout << endl;
		//for (int s = 0; s < INDIV.v_ul_objectives.size(); s++)
		//{
		//	for (int ss = 0; ss < INDIV.v_ul_objectives[s].size(); ss++)
		//	{
		//		cout << INDIV.v_ul_objectives[s][ss] << " ";
		//	}
		//}
		//cout << endl;
		//system("pause");//��ʼ��һ��delete_job_number
	}
}