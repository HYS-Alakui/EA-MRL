#include "Headfile.h"
#include "Qpacking.h"
#include "Item.h"
#include "Chromosome.h"
#include "Individual.h"
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

void QPacking::selection_next_pop(vector <CIndividual>& v_TotalChromo, vector <vector<CIndividual>>& v_Chromo, vector <CIndividual>& v_low_TotalChromo, vector <vector<CIndividual>>& v_low_Chromo, vector<Item>& v_product)
{
	////Step1:合并Pt(v_Chromo, v_TotalChromo);和Qt(v_low_TotalChromo,v_low_Chromo)为Rt
	vector <CIndividual> v_merge_TotalChromo;
	vector <CIndividual>().swap(v_merge_TotalChromo);
	for (int m = 0; m < v_TotalChromo.size(); m++)
	{
		v_merge_TotalChromo.push_back(v_TotalChromo[m]);
	}
	for (int m = 0; m < v_low_TotalChromo.size(); m++)
	{
		v_merge_TotalChromo.push_back(v_low_TotalChromo[m]);
	}
	vector <vector<CIndividual>> v_merge_Chromo;
	vector <vector<CIndividual>>().swap(v_merge_Chromo);
	for (int m = 0; m < v_Chromo.size(); m++)
	{
		v_merge_Chromo.push_back(v_Chromo[m]);
	}
	for (int m = 0; m < v_low_Chromo.size(); m++)
	{
		v_merge_Chromo.push_back(v_low_Chromo[m]);
	}
	//cout << "合并种群：" << endl;
	//out_result(v_merge_Chromo, v_merge_TotalChromo);
	//system("pause");

	////Step2:获得Rt种群的上层序值和拥挤度距离值，并获得Rt中各个子种群的下层序值和拥挤度距离值
	rank_up(v_merge_TotalChromo);//获取初始种群的上层序值和拥挤度距离
	rank_low(v_merge_Chromo);//针对每个子种群的下层进行排序和拥挤度距离
	update_subpop(v_merge_TotalChromo, v_merge_Chromo);
	//cout << "Rank_After_v_merge_Chromo:" << endl;
	//for (int m = 0; m < v_merge_Chromo.size(); m++)
	//{
	//	cout << "sub_no = " << m + 1 << endl;
	//	for (int n = 0; n < v_merge_Chromo[m].size(); n++)
	//	{
	//		cout << "iner = " << n + 1 << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_merge_Chromo[m][n].v_chromosome1[u].operation_number << " ";
	//		}
	//		cout << endl;
	//		//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		//{
	//		//	cout << v_merge_Chromo[m][n].v_chromosome1[u].operation_index << " ";
	//		//}
	//		//cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_merge_Chromo[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_merge_Chromo[m][n].v_chromosome1[u].machine_number << " ";
	//		}
	//		cout << endl;
	//		//for (int u = number_of_jobs * number_of_operations; u < v_merge_Chromo[m][n].v_chromosome1.size(); u++)
	//		//{
	//		//	cout << v_merge_Chromo[m][n].v_chromosome1[u].job_number << " ";
	//		//}
	//		//cout << endl;
	//		for (int u = 0; u < v_merge_Chromo[m][n].v_chromosome2.size(); u++)
	//		{
	//			cout << v_merge_Chromo[m][n].v_chromosome2[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_merge_Chromo[m][n].v_ul_objectives.size(); u++)
	//		{
	//			for (int v = 0; v < v_merge_Chromo[m][n].v_ul_objectives[u].size(); v++)
	//			{
	//				cout << v_merge_Chromo[m][n].v_ul_objectives[u][v] << " ";
	//			}
	//		}
	//		cout << endl;
	//		//system("pause");
	//		cout << v_merge_Chromo[m][n].upper_rank << " " << v_merge_Chromo[m][n].upper_crowdedistance << endl;
	//		cout << v_merge_Chromo[m][n].lower_rank << " " << v_merge_Chromo[m][n].lower_crowdedistance << endl;
	//		//system("pause");
	//	}
	//	cout << endl << endl;
	//}
	//system("pause");

	////Step3:选择下一代下层种群
	vector <vector<CIndividual>> v_next_Chromo;
	vector <CIndividual> v_next_TotalChromo;
	vector<int> v_save_subno;//储存已进入下一代种群的子种群编号
	int rank_value = 1;
	int max_rank_value = 1;
	for (int i = 0; i < v_merge_Chromo.size(); i++)
	{
		for (int j = 0; j < v_merge_Chromo[i].size(); j++)
		{
			if (v_merge_Chromo[i][j].upper_rank > max_rank_value)
			{
				max_rank_value = v_merge_Chromo[i][j].upper_rank;
			}
		}
	}
	//cout << "max_rank_value = " << max_rank_value << endl;
	while (v_next_Chromo.size() < number_of_subpop || rank_value > max_rank_value)
	{
		//cout << "v_next_Chromo.size()  = " << v_next_Chromo.size() << endl;

		////Step3.1: 先找 NDu = rank_value 的子种群
		vector<int> v_subno_set;
		for (int i = 0; i < v_merge_Chromo.size(); i++)
		{
			int sub_number = i + 1;
			//cout << "sub_number = " << sub_number << endl;
			for (int j = 0; j < v_merge_Chromo[i].size(); j++)
			{
				//cout << "v_merge_Chromo[i][j].upper_rank = " << v_merge_Chromo[i][j].upper_rank << endl;
				if (v_merge_Chromo[i][j].upper_rank == rank_value)//若当前子种群有NDu = 1的个体，那就保存该子种群的编号
				{
					v_subno_set.push_back(sub_number);
					break;
				}
			}
		}
		//cout << "NDu = "<< rank_value <<" 的子种群编号：" << endl;
		//for (int i = 0; i < v_subno_set.size(); i++)
		//{
		//	cout << v_subno_set[i] << " ";
		//}
		//cout << endl;

		////Step3.2:再获取这些子种群中 NDu = rank_value 且 NDl = 1 的个体
		vector<CIndividual> v_NDl_Indiv_set;
		vector<double> v_NDl_updist;
		vector<int> v_NDl_subno;
		for (int i = 0; i < v_subno_set.size(); i++)
		{
			int sub_index = v_subno_set[i] - 1;
			for (int j = 0; j < v_merge_Chromo[sub_index].size(); j++)
			{
				if (v_merge_Chromo[sub_index][j].upper_rank == rank_value && v_merge_Chromo[sub_index][j].lower_rank == 1)
				{
					v_NDl_Indiv_set.push_back(v_merge_Chromo[sub_index][j]);
					v_NDl_updist.push_back(v_merge_Chromo[sub_index][j].upper_crowdedistance);
					v_NDl_subno.push_back(sub_index + 1);
				}
			}
		}
		//cout << "NDu = " << rank_value << " 且 NDl = 1的个体的上层拥挤度距离CDu：" << endl;
		//for (int i = 0; i < v_NDl_updist.size(); i++)
		//{
		//	cout << v_NDl_updist[i] << " ";
		//}
		//cout << endl;
		//cout << "NDu = " << rank_value << " 且 NDl = 1的个体的子种群编号subno：" << endl;
		//for (int i = 0; i < v_NDl_subno.size(); i++)
		//{
		//	cout << v_NDl_subno[i] << " ";
		//}
		//cout << endl;

		////Step3.3:筛选当前层能够进入下一代的子种群
		if (v_NDl_subno.size() == 0)
		{
			//cout << "当前层无NDu=1且NDl=1的个体，检查下一层： " << endl;
		}
		else if (v_NDl_subno.size() == 1)
		{
			int NDl_sub_no = v_NDl_subno[0];
			if (v_save_subno.size() < 1)
			{
				//cout << "当前子种群是第一个被选择的子种群" << endl;
				v_next_Chromo.push_back(v_merge_Chromo[NDl_sub_no - 1]);
				v_save_subno.push_back(NDl_sub_no);
			}
			else
			{
				//cout << "检查当前子种群是否已出现与v_save_subno中" << endl;
				int count = 0;
				for (int i = 0; i < v_save_subno.size(); i++)
				{
					if (NDl_sub_no == v_save_subno[i])
					{
						//cout << NDl_sub_no <<"已出现，跳出！" << endl;
						break;
					}
					else
					{
						count++;
						//cout << "count_inner = " << count << endl;
					}
					//cout << "count_outer = " << count << endl;
					if (count == v_save_subno.size())
					{
						if (v_save_subno.size() < number_of_subpop)
						{
							//cout << NDl_sub_no << "未出现，保存该子种群：" << endl;
							v_next_Chromo.push_back(v_merge_Chromo[NDl_sub_no - 1]);
							v_save_subno.push_back(NDl_sub_no);
						}
					}
				}
			}

		}
		else if (v_NDl_subno.size() >= 2)
		{
			////Step3.3.1:比较 NDu = rank_value 且 NDl = 1 的个体的CDu值，并对子种群编号降序排序
			//cout << "按照CDu对这些子种群进行降序排序" << endl;
			for (int i = 0; i <= v_NDl_updist.size() - 1 - 1; i++)
			{
				for (int j = i + 1; j <= v_NDl_updist.size() - 1; j++)
				{
					if (v_NDl_updist[i] < v_NDl_updist[j])
					{
						double dtemp1 = v_NDl_updist[i];
						v_NDl_updist[i] = v_NDl_updist[j];
						v_NDl_updist[j] = dtemp1;

						double dtemp2 = v_NDl_subno[i];
						v_NDl_subno[i] = v_NDl_subno[j];
						v_NDl_subno[j] = dtemp2;
					}
				}
			}
			//cout << "排序后，NDu = " << rank_value << " 且 NDl = 1的个体的拥挤度距离CDu：" << endl;
			//for (int i = 0; i < v_NDl_updist.size(); i++)
			//{
			//	cout << v_NDl_updist[i] << " ";
			//}
			//cout << endl;
			//cout << "排序后，NDu = " << rank_value << " 且 NDl = 1的个体的子种群编号subno：" << endl;
			//for (int i = 0; i < v_NDl_subno.size(); i++)
			//{
			//	cout << v_NDl_subno[i] << " ";
			//}
			//cout << endl;

			////Step3.3.2:比较这些子种群是否出现过，若出现，则判断下一个子种群，若未出现且下一代种群还没买，则保存。
			for (int i = 0; i < v_NDl_subno.size(); i++)
			{
				int NDl_sub_no = v_NDl_subno[i];
				//cout << "NDl_sub_no = " << NDl_sub_no << endl;
				//cout << "v_save_subno.size() = " << v_save_subno.size() << endl;
				if (v_save_subno.size() < 1)
				{
					//cout << "当前子种群是第一个被选择的子种群" << endl;
					v_next_Chromo.push_back(v_merge_Chromo[NDl_sub_no - 1]);
					v_save_subno.push_back(NDl_sub_no);
				}
				else
				{
					int count = 0;
					for (int ii = 0; ii < v_save_subno.size(); ii++)
					{
						if (NDl_sub_no == v_save_subno[ii])
						{
							//cout << NDl_sub_no<< "已出现，判断下一个子种群！" << endl;
							break;
						}
						else
						{
							count++;
							///cout << "inner_count == " << count << endl;
						}
					}
					//cout << "outer_count == " << count << endl;
					if (count == v_save_subno.size())//说明当前子种群未保存
					{
						if (v_save_subno.size() < number_of_subpop)
						{
							//cout << NDl_sub_no << "未出现，保存当前子种群！" << endl;
							v_next_Chromo.push_back(v_merge_Chromo[NDl_sub_no - 1]);
							v_save_subno.push_back(NDl_sub_no);
						}
					}
				}


				if (v_save_subno.size() >= number_of_subpop)
				{
					//cout << "下一代种群已满，无须继续判断下一个子种群，跳出！" << endl;
					break;
				}
				//system("pause");
			}
		}

		////Step3.4:判断选择下一代种群的停止条件
		if (v_save_subno.size() < number_of_subpop)///筛选下一层！
		{
			rank_value++;
			//cout << "next_rank_value = " << rank_value << endl;
		}
		else
		{
			//cout << "此时，下一代种群已满，跳出！" << endl;
			break;
		}
	}
	//cout << "保存的子种群编号：" << endl;
	//for (int i = 0; i < v_save_subno.size(); i++)
	//{
	//	cout << v_save_subno[i] << " ";
	//}
	//cout << endl;
	//system("pause");
	if (v_next_Chromo.size() < number_of_subpop)
	{
		//cout << "剩余的子种群随机产生！" << endl;
		for (int i = v_next_Chromo.size() - 1; i < number_of_subpop; i++)
		{
			//cout << "i = " << i + 1 << endl;
			CIndividual T;
			randomUpper(T);//随机生成上层向量
			vector <CIndividual> v_subChromo;
			vector <CIndividual>().swap(v_subChromo);
			for (int j = 0; j < lower_number_of_individuals; j++)
			{
				//cout << "j = " << j+ 1<< endl;
				CIndividual t;
				t.sub_no = i + 1;
				t.v_chromosome1 = T.v_chromosome1;
				randomLower(t);//随机生成下层向量
				upper_evaluate(t, board_width, board_height, v_product);
				v_subChromo.push_back(t);
			}
			v_next_Chromo.push_back(v_subChromo);
		}
	}
	//cout << "输出获得的Next种群" << endl;
	//for (int i = 0; i < v_next_Chromo.size(); i++)
	//{
	//	cout << "subno = " << i + 1 << endl;
	//	for (int j = 0; j < v_next_Chromo[i].size(); j++)
	//	{
	//		cout << v_next_Chromo[i][j].sub_no << endl;
	//		for (int m = 0; m < number_of_jobs * number_of_operations; m++)
	//		{
	//			cout << v_next_Chromo[i][j].v_chromosome1[m].operation_number << " ";
	//		}
	//		cout << endl;
	//		for (int m = number_of_jobs * number_of_operations; m < v_next_Chromo[i][j].v_chromosome1.size(); m++)
	//		{
	//			cout << v_next_Chromo[i][j].v_chromosome1[m].machine_number << " ";
	//		}
	//		cout << endl;
	//		for (int m = 0; m < number_of_jobs; m++)
	//		{
	//			cout << v_next_Chromo[i][j].v_chromosome2[m].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_next_Chromo[i][j].v_ul_objectives.size(); u++)
	//		{
	//			for (int v = 0; v < v_next_Chromo[i][j].v_ul_objectives[u].size(); v++)
	//			{
	//				cout << v_next_Chromo[i][j].v_ul_objectives[u][v] << " ";
	//			}
	//		}
	//		cout << endl;
	//	}
	//	cout << endl << endl;
	//}
	//system("pause");

	////Step4:v_new_Chromo_temp继承下一代种群v_next_Chromo的染色体基因，重新编号、求解、计算序值和拥挤度距离，同时更新v_new_TotalChromo_temp
	vector <vector<CIndividual>>().swap(v_new_Chromo_temp);
	vector <CIndividual>().swap(v_new_TotalChromo_temp);
	for (int i = 0; i < v_next_Chromo.size(); i++)
	{
		vector<CIndividual> v_new_subChromo_temp;
		for (int j = 0; j < v_next_Chromo[i].size(); j++)
		{
			CIndividual next_t;
			next_t.sub_no = i + 1;
			next_t.v_chromosome1 = v_next_Chromo[i][j].v_chromosome1;
			next_t.v_chromosome2 = v_next_Chromo[i][j].v_chromosome2;
			upper_evaluate(next_t, board_width, board_height, v_product);
			v_new_subChromo_temp.push_back(next_t);
			v_new_TotalChromo_temp.push_back(next_t);
		}
		v_new_Chromo_temp.push_back(v_new_subChromo_temp);
	}
	rank_up(v_new_TotalChromo_temp);//获取下层优化的下一代种群的上层序值和拥挤度距离
	rank_low(v_new_Chromo_temp);//针对下层优化的下一代种群中每个子种群的下层进行排序和拥挤度距离
	update_subpop(v_new_TotalChromo_temp, v_new_Chromo_temp);//下层优化的下一代种群中每个解都有上下层序值和拥挤度距离

	////经历过下层迭代优化后的v_new_TotalChromo_temp, v_new_Chromo_temp是上层的下一代种群
	//cout << "After_v_new_TotalChromo_temp:" << endl;
	//for (int m = 0; m < v_new_TotalChromo_temp.size(); m++)
	//{
	//	cout << "m = " << m + 1 << endl;
	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
	//	{
	//		cout << v_new_TotalChromo_temp[m].v_chromosome1[n].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
	//	{
	//		cout << v_new_TotalChromo_temp[m].v_chromosome1[n].operation_index << " ";
	//	}
	//	cout << endl;
	//	for (int n = number_of_jobs * number_of_operations; n < v_new_TotalChromo_temp[m].v_chromosome1.size(); n++)
	//	{
	//		cout << v_new_TotalChromo_temp[m].v_chromosome1[n].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = number_of_jobs * number_of_operations; n < v_new_TotalChromo_temp[m].v_chromosome1.size(); n++)
	//	{
	//		cout << v_new_TotalChromo_temp[m].v_chromosome1[n].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < v_new_TotalChromo_temp[m].v_chromosome2.size(); n++)
	//	{
	//		cout << v_new_TotalChromo_temp[m].v_chromosome2[n].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < v_new_TotalChromo_temp[m].v_ul_objectives.size(); n++)
	//	{
	//		for (int v = 0; v < v_new_TotalChromo_temp[m].v_ul_objectives[n].size(); v++)
	//		{
	//			cout << v_new_TotalChromo_temp[m].v_ul_objectives[n][v] << " ";
	//		}
	//	}
	//	cout << endl;
	//	cout << v_new_TotalChromo_temp[m].upper_rank << " " << v_new_TotalChromo_temp[m].upper_crowdedistance << endl;
	//	cout << v_new_TotalChromo_temp[m].lower_rank << " " << v_new_TotalChromo_temp[m].lower_crowdedistance << endl;
	//}
	//system("pause");

	//cout << "After_v_new_Chromo_temp：" << endl;
	//for (int m = 0; m < v_new_Chromo_temp.size(); m++)
	//{
	//	cout << "sub_no = " << m + 1 << endl;
	//	for (int n = 0; n < v_new_Chromo_temp[m].size(); n++)
	//	{
	//		cout << "iner = " << n + 1 << endl;
	//		cout << v_new_Chromo_temp[m][n].sub_no << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_new_Chromo_temp[m][n].v_chromosome1[u].operation_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_new_Chromo_temp[m][n].v_chromosome1[u].operation_index << " ";
	//		}
	//		cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_new_Chromo_temp[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_new_Chromo_temp[m][n].v_chromosome1[u].machine_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_new_Chromo_temp[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_new_Chromo_temp[m][n].v_chromosome1[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_new_Chromo_temp[m][n].v_chromosome2.size(); u++)
	//		{
	//			cout << v_new_Chromo_temp[m][n].v_chromosome2[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_new_Chromo_temp[m][n].v_ul_objectives.size(); u++)
	//		{
	//			for (int v = 0; v < v_new_Chromo_temp[m][n].v_ul_objectives[u].size(); v++)
	//			{
	//				cout << v_new_Chromo_temp[m][n].v_ul_objectives[u][v] << " ";
	//			}
	//		}
	//		cout << endl;
	//		cout << v_new_Chromo_temp[m][n].upper_rank << ",  " << v_new_Chromo_temp[m][n].upper_crowdedistance << endl;
	//		cout << v_new_Chromo_temp[m][n].lower_rank << ",  " << v_new_Chromo_temp[m][n].lower_crowdedistance << endl;
	//	}
	//	cout << endl << endl;
	//}
	//system("pause");
}