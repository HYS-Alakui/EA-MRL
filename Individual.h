#include "headfile.h"
#include "Chromosome.h"

#ifndef _INFORMATIONCOLLEAGE_
#define _INFORMATIONCOLLEAGE_

class CIndividual//定义一个类 类名为CIndividual
{
private:
public:
	vector <CChromosome> v_chromosome1; //上层变量：FJSP的工序加工序列和机器选择序列        
	vector <CChromosome> v_chromosome2; //下层变量：矩形件的排入顺序


	vector <CChromosome> v_upper_chromosome1;
	vector <CChromosome> v_upper_chromosome2;
	vector <CChromosome> v_lower_chromosome;

	int sub_no;//该个体所属的子种群编号

	vector<vector<double>> v_ul_objectives;
	double use_rate;
	double consistant_value;
	double total_tardiness;	
	double total_cost;

	vector <int> v_job_packing_finish_time;//记录每个矩形件（job）的切割完工时间

	int upper_rank;
	int upper_domination_count;
	vector <int> v_upper_dominationSet;
	double upper_crowdedistance;

	int lower_rank;
	int lower_domination_count;
	vector <int> v_lower_dominationSet;
	double lower_crowdedistance;

	int max_tardiness_job_index;

	vector<pair<int, int>> v_real_packing_route;

	vector<int>Job_C;//关键路径的作业（正）
	vector<int>Operation_C;//关键路径作业的工序号（正）
	vector<int>Machine_C;//关键路径作业的工序所在的机器（正）,机器号-1；
	vector<int>Product_C;//排样阶段关键路径的job号（正）

	//vector<int>Keymachine_Operation;//关键机器上的工序
	//vector<int>Keymachine_Operation_Xuhao;//关键机器上的工序序号

	//vector <int> v_job_list;//创建一个保存 每个对象 的 作业序列 的 容器
	//vector <int> v_factory_list;//创建一个保存 每个对象 的 作业序列 的 容器	

	//int key_cell;
	//int key_factory_index;//最佳工厂
	//int key_machine_index;//最佳机器

};
#endif
