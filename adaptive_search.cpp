#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"
#include "Item.h"
#include <algorithm>
#include <map>
#include <iomanip>

void QPacking::adaptive_search(vector <vector<CIndividual>>& v_new_Chromo, vector<CIndividual>& v_new_TotalChromo, vector<Item>& v_product)
{
	////step1: 动作选择，选择Q值最大的行动或者贪心策略
	double rand_probability = rand() / (RAND_MAX * 1.0);//随机概率
	double greedy_value = 0.5 / (1 + exp(10 * (outer_iteration_count - 0.6 * outer_iteration_count_max) / outer_iteration_count_max));
	if (rand_probability > 1 - greedy_value) //贪心策略
	{
		Action_Current = rand() % (7) + 1;//随机选择一个行动
	}
	else //最大Q值对应的行动
	{
		int Action_Position = max_element(Q_TABLE[State_Current - 1], Q_TABLE[State_Current - 1] + Action_Number) - Q_TABLE[State_Current - 1];
		Action_Current = Action_Position + 1;
	}

	////step2: 执行动作，获得ls种群v_ls_Chromo和v_ls_TotalChromo
	vector <vector<CIndividual>> v_new_Chromo_temp(v_new_Chromo);
	vector <CIndividual> v_new_TotalChromo_temp(v_new_TotalChromo);
	local_search(v_new_TotalChromo_temp, v_new_Chromo_temp, v_product, Action_Current);

	////step3: 比较LS种群与未进行LS的种群的支配性	
	C_metric(v_ls_TotalChromo, v_new_TotalChromo_temp, C_value_v);//新种群支配原种群的比例
	C_metric(v_new_TotalChromo_temp, v_ls_TotalChromo, C_value_t);//原种群支配新种群的比例
	difference_C = C_value_v - C_value_t;
	DV_metric(v_ls_TotalChromo, DV_value_v);
	DV_metric(v_new_TotalChromo_temp, DV_value_t);
	difference_DV = DV_value_v - DV_value_t;

	////step4: 更新奖励、动作、状态和Q表
	double REWARD = 0;//初始化奖励值
	if (difference_C > 0.0 && difference_DV > 0.0)//更新状态和奖励值
	{
		State_Next = 1;
		REWARD = 10;
	}
	else if (difference_C > 0.0 && difference_DV <= 0)
	{
		State_Next = 2;
		REWARD = 5;
	}
	else if (difference_C <= 0.0 && difference_DV > 0)
	{
		State_Next = 3;
		REWARD = 5;
	}
	else
	{
		State_Next = 4;
		REWARD = 0;
	}
	//cout << "当前状态State_Current = " << State_Current << endl;
	//cout << "下一个状态State_Next = " << State_Next << endl;
	//cout << "获得奖励REWARD = " << REWARD << endl;
	double maxQ_next = *max_element(Q_TABLE[State_Next - 1], Q_TABLE[State_Next - 1] + Action_Number);//*max_element()函数的用法：返回相应状态下的最大Q值
	//更新Q表，Q(s,a) ← Q(s,a) + 学习率×[奖励 + 折扣因子×下一个状态最大估计max - Q(s,a)]
	Q_TABLE[State_Current - 1][Action_Current - 1] = Q_TABLE[State_Current - 1][Action_Current - 1] +
		Learning_Rate * (REWARD + Discount_Factor * maxQ_next - Q_TABLE[State_Current - 1][Action_Current - 1]);

	State_Current = State_Next;//更新下一次进化时的状态
}