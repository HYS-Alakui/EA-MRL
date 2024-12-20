#include "Headfile.h"
#include "Qpacking.h"
#include "Item.h"
#include "Chromosome.h"
#include "Individual.h"
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

void QPacking::update_blemo_framework(vector <CIndividual>& v_ls_TotalChromo, vector <vector<CIndividual>>& v_ls_Chromo, vector<Item>& v_product)
{
	//cout << "更新前！" << endl;
	//out_result(v_ls_Chromo, v_ls_TotalChromo);
	//system("pause");

	////step1: 建立一个容器保存每个子种群中upper_rank最小的解
	vector<CIndividual> v_rank_indiv;
	for (int m = 0; m < v_ls_Chromo.size(); m++)
	{
		vector<int> v_rank_value;
		for (int n = 0; n < v_ls_Chromo[m].size(); n++)
		{
			v_rank_value.push_back(v_ls_Chromo[m][n].upper_rank);		
		}	
		auto minIt = min_element(v_rank_value.begin(), v_rank_value.end());// 使用std::max_element找到最大元素的迭代器	
		int minIndex = distance(v_rank_value.begin(), minIt);// 计算最大值的索引
		//cout << "最小值: " << *minIt << std::endl;
		//cout << "对应的索引: " << minIndex << std::endl;

		CIndividual update_indiv = v_ls_Chromo[m][minIndex];
		v_rank_indiv.push_back(update_indiv);
	}

	////step2：用每个子种群中upper_rank最小的解的上层向量来更新当前子种群每个个体的上层向量
	vector<CIndividual>().swap(v_ls_TotalChromo);
	for (int m = 0; m < v_ls_Chromo.size(); m++)
	{
		for (int n = 0; n < v_ls_Chromo[m].size(); n++)
		{
			v_ls_Chromo[m][n].v_chromosome1 = v_rank_indiv[m].v_chromosome1;
			upper_evaluate(v_ls_Chromo[m][n], board_width, board_height, v_product);
			v_ls_TotalChromo.push_back(v_ls_Chromo[m][n]);
		}
	}

	rank_up(v_ls_TotalChromo);//获取种群中个体的上层序值和拥挤度距离
	rank_low(v_ls_Chromo);//获取种群中每个子种群中个体的下层序值和拥挤度距离
	update_subpop(v_ls_TotalChromo, v_ls_Chromo);//获得新种群v_new_TotalChromo/v_new_Chromo

	//cout << "更新后！" << endl;
	//out_result(v_ls_Chromo, v_ls_TotalChromo);
	//system("pause");
}