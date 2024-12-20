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
	//cout << "拷贝后临时种群：" << endl;
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
		for (int j = 0; j < lower_number_of_individuals; j++)//对每个个体执行销毁和重构操作
		{
			//cout << "j = " << j << endl;
			
			////判断当前个体的rank_value
			if (v_Chromo_temp[i][j].upper_rank == 1)
			{
				//cout << "执行DC操作！" << endl;
				CIndividual des_indiv = v_Chromo_temp[i][j];
				ds_operation_individual(des_indiv, v_product);//对每个个体执行销毁和重构操作

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
				//cout << "销毁-重构后的new_sub_indv解：" << endl;
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
				upper_evaluate(new_sub_indv, board_width, board_height, v_product);//求上层和下层目标函数值：先求下层目标值，然后基于下层约束求解上层目标值
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
				//cout << "利用选择-交叉-变异得到子代！" << endl;			
				CIndividual new_sub_indv;
				new_sub_indv.sub_no = i + 1;

				////step1.1: 利用二元锦标赛选择法随机选择一个个体作为上层母亲
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

				////Step1.2：调用交叉函数对这两个父代的上层变量即v_chromosome1进行交叉，得到两个新的子代上层向量
				upper_crossover(upper_fathIndiv, upper_mothIndiv, upper_chIndiv1, upper_chIndiv2);

				////Step1.3：调用变异函数对随机一个子代上层向量进行变异
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

				//////////////////////////////////////以上获取了子代的上层向量///////////////////////////////////
				//////////////////////////////////////以下获取了子代的下层向量///////////////////////////////////
				CIndividual upper_lower_fathIndiv, upper_lower_mothIndiv, upper_lower_chIndiv1, upper_lower_chIndiv2;
				upper_lower_fathIndiv = upper_fathIndiv;
				upper_lower_mothIndiv = upper_mothIndiv;

				////Step2.1：调用交叉函数对这两个父代的下层变量即v_chromosome2进行交叉，得到两个新的子代下层向量
				lower_crossover(upper_lower_fathIndiv, upper_lower_mothIndiv, upper_lower_chIndiv1, upper_lower_chIndiv2);
				
				////Step2.2：调用变异函数对随机一个子代下层向量进行变异
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

				//cout << "选择-交叉-变异后的new_sub_indv解：" << endl;
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
				
				////step3：求new_sub_indv的适值，并将其保存
				upper_evaluate(new_sub_indv, board_width, board_height, v_product);//求上层和下层目标函数值：先求下层目标值，然后基于下层约束求解上层目标值
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


	//cout << "D-C后的新种群：" << endl;
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
	//cout << "销毁-重构前的des_indiv解：" << endl;
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

	////准备工作
	vector<int> v_delete_jobs;
	vector<int> v_delete_machines;
	vector<int> v_intial_machine_assignment;
	for (int u = number_of_jobs * number_of_operations; u < des_indiv.v_chromosome1.size(); u++)
	{
		v_intial_machine_assignment.push_back(des_indiv.v_chromosome1[u].machine_number);
	}

	////销毁操作
	destruction(des_indiv, v_delete_jobs, v_delete_machines);
	//cout << "job：" << endl;
	//for (int u = 0; u < v_delete_jobs.size(); u++)
	//{
	//	cout << v_delete_jobs[u] << " ";
	//}
	//cout << endl;
	//cout << "machine：" << endl;
	//for (int u = 0; u < v_delete_machines.size(); u++)
	//{
	//	cout << v_delete_machines[u] << " ";
	//}
	//cout << endl;
	//cout << "gene：" << endl;
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


	////重构操作
	construction(des_indiv, v_delete_jobs, v_delete_machines, v_intial_machine_assignment, v_product);
	//cout << "销毁-重构后的des_indiv解：" << endl;
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
	//cout << "当前个体的基因：" << endl;
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

	//针对每个上层向量进行销毁
	//step1：设置销毁长度
	int destruction_length = round(0.1 * number_of_jobs);//删除几道工序
	//cout << "destruction_length = " << destruction_length << endl;
	int* p_destruction = new int[destruction_length];//开辟一个数组储存删掉的工序

	//step2：找出具有最大tardiness的job
	int max_tardi_jobindex = INDIV.max_tardiness_job_index;
	//cout << "max_tardi_jobindex = " << max_tardi_jobindex << endl;

	//step3：计算d1 = min(d/2,dj)，dj是作业j的工序数目，d是destruction_length， d2 = d-d1
	int d1 = min(destruction_length / 2, number_of_operations);
	//cout << "d1 = " << d1 << endl;
	int d2 = destruction_length - d1;
	//cout << "d2 = " << d2 << endl;

	//step4：确定销毁的工序位置和对应的机器位置
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
		for (int mm = 0; mm < INDIV.v_chromosome1.size(); mm++)//找出job的第right_index道工序的位置
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
			//cout << "选择下一个job" << endl;
			bool isPresent;
			do
			{
				rand_jobindex = rand() % number_of_jobs;
				//cout << "rand_jobindex = " << rand_jobindex << endl;
				isPresent = false;
				for (int index : v_now_jobs_index)// 检查生成的索引是否存在于 v_now_jobs_index 中
				{
					if (rand_jobindex == index)
					{
						isPresent = true;
						break;
					}
				}
			} while (isPresent); // 如果存在，重新生成			
			v_now_jobs_index.push_back(rand_jobindex);
		}
		//cout << "rand_jobindex = " << rand_jobindex << endl;

		int right_job_pos_index;
		for (int mm = 0; mm < INDIV.v_chromosome1.size(); mm++)//找出job的第right_index道工序的位置
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
	//cout << "job_pos_index：" << endl;
	//for (int u = 0; u < v_delete_job_pos_index.size(); u++)
	//{
	//	cout << v_delete_job_pos_index[u] << " ";
	//}
	//cout << endl;
	//cout << "machine_pos_index：" << endl;
	//for (int u = 0; u < v_delete_machine_pos_index.size(); u++)
	//{
	//	cout << v_delete_machine_pos_index[u] << " ";
	//}
	//cout << endl;
	//cout << "job：" << endl;
	//for (int u = 0; u < v_delete_jobs.size(); u++)
	//{
	//	cout << v_delete_jobs[u] << " ";
	//}
	//cout << endl;
	//cout << "machine：" << endl;
	//for (int u = 0; u < v_delete_machines.size(); u++)
	//{
	//	cout << v_delete_machines[u] << " ";
	//}
	//system("pause");

	//step5：删掉相应的工序及机器
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
	//cout << "删除个体的基因：" << endl;
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
	//cout << "INPUT_initial_machine_assignment：" << endl;
	//for (int u = 0; u < v_intial_machine_assignment.size(); u++)
	//{
	//	cout << v_intial_machine_assignment[u] << " ";
	//}
	//cout << endl;

	//cout << "INPUT_delete_jobs：" << endl;
	//for (int u = 0; u < v_delete_jobs.size(); u++)
	//{
	//	cout << v_delete_jobs[u] << " ";
	//}
	//cout << endl;

	//cout << "INPUT_new_genes：" << endl;
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
		//cout << "插入前INDIV：" << endl;
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


		////STEP1: 获得要插入的job即delete_job_number
		int delete_job_number = v_delete_jobs[u];
		//cout << "STEP1: delete_job_number = " << delete_job_number << endl;
		CChromosome newccc1;
		newccc1.job_number = delete_job_number;
		newccc1.operation_number = delete_job_number;
		newccc1.operation_index = 0;


		////STEP2: 将delete_job_number插入到当前解的所有位置获得一个邻域解集
		//cout << "STEP2: 将delete_job_number插入到当前解的所有位置获得一个邻域解集！" << endl;
		vector <CIndividual> v_nebo_individuals;//储存每个邻域解
		for (int v = 0; v < INDIV.v_upper_chromosome1.size(); v++)
		{
			////step1：创建一个新的个体，复制现有的染色体
			CIndividual newIndiv = INDIV; 
			//cout << "插入前newIndiv：" << endl;
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

			////step2：插入工序操作	
			newIndiv.v_upper_chromosome1.insert(newIndiv.v_upper_chromosome1.begin() + v, newccc1);	
			//cout << "插入后的newIndiv的v_upper_chromosome1：" << endl;
			//for (int s = 0; s < newIndiv.v_upper_chromosome1.size(); s++)
			//{
			//	cout << newIndiv.v_upper_chromosome1[s].operation_number << " ";
			//}
			//cout << endl;
			//system("pause");


			////step3：插入机器的准备	
			vector<int> v_operation_numbers; //把工序基因（含新插入工序）放入容器中
			for (int s = 0; s < newIndiv.v_upper_chromosome1.size(); s++)
			{
				v_operation_numbers.push_back(newIndiv.v_upper_chromosome1[s].operation_number);
			}
			map<int, int> countMap;// 使用 map 来计算每个数字（job）的出现次数 countMap的键是job号，键值是job号相关联的出现次数
			for (int num : v_operation_numbers) 
			{
				countMap[num]++;
			}
			//for (const auto& pair : countMap) // 输出countMap
			//{
			//	cout << "Job " << pair.first << " 出现 " << pair.second << " 次！" << std::endl;
			//}

			vector<pair<int, int>> v_job_counts;// 创建一个 vector 来存储每个数字的出现次数
			for (const auto& vjc : countMap) 
			{
				int job_id = vjc.first;  //job号
				int operation_count = vjc.second; //job包含的工序数
				v_job_counts.push_back(make_pair(job_id, operation_count));
			}
			//cout << "每个job出现的次数:" << std::endl;
			//for (const auto& count : v_job_counts)
			//{
			//	cout << "(" << count.first << ", ";
			//	cout << count.second << ")";
			//}
			//cout << endl;
			//system("pause");

			for (const auto& pair : countMap) //更新插入后每道工序的序号
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

			//cout << "获取要插入的job相应工序的机器号：" << endl;
			int insert_job_oper_count = countMap[delete_job_number];//键存在，可以使用下标操作符 [] 来获取与该键关联的值
			//cout << "insert_job_oper_count = " << insert_job_oper_count << endl;
			int insert_job_mach_index = (delete_job_number - 1) * number_of_operations + insert_job_oper_count - 1;//获取哪个job的哪道工序就能获取其该位置在初始染色体上的索引
			//cout << "insert_job_mach_index = " << insert_job_mach_index << endl;
			int insert_job_mach_number = v_intial_machine_assignment[insert_job_mach_index];//获取机器位置索引就能找到所插入的job需要的machine
			//cout << "insert_job_mach_number = " << insert_job_mach_number << endl;
			//system("pause");

			CChromosome newccc2;
			newccc2.machine_number = insert_job_mach_number;
			int pos_machine_index = 0;
			//cout << "确定插入位置机器索引！" << endl;
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

			////step4：插入机器操作
			newIndiv.v_upper_chromosome2.insert(newIndiv.v_upper_chromosome2.begin() + pos_machine_index, newccc2);	
			//cout << "插入后的newIndiv的v_upper_chromosome2：" << endl;
			//for (int s = 0; s < newIndiv.v_upper_chromosome2.size(); s++)
			//{
			//	cout << newIndiv.v_upper_chromosome2[s].machine_number << " ";
			//}
			//cout << endl;
			//system("pause");


			////step5：保存每个delete_job的邻域解
			v_nebo_individuals.push_back(newIndiv); 
		}
		

		////STEP3: 评估邻域解集
		//cout << "STEP3: 输出并计算当前delete_job的输出邻域解集：" << endl;
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


		////STEP4: 找到最佳的nebo个体，用它来更新INDIV，然后在它基础上开始下一个delete_job_number的插入
		//cout << "STEP4: 找到最佳nebo个体用以更新INDIV" << endl;
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
		INDIV = best_nebo_indiv;//更新INDIV
		//cout << "插入后：" << endl;
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
		//system("pause");//开始下一个delete_job_number
	}
}