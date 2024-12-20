#include<vector>
#include "Headfile.h"
#include "Item.h"
#include "Individual.h"
#include "Chromosome.h"
#include "RankSequ.h"
#include <map>
#include <tuple>
using namespace std;

class QPacking
{
private:

	int number_of_objectives; //目标数目
	int upper_number_of_individuals;//种群规模
	int number_of_subpop;//子种群数目
	int lower_number_of_individuals;//种群规模

	int outer_iteration_count_max;
	int outer_iteration_count;

	int number_of_products;
	int board_width;
	int board_height;
	int number_of_orders;

	int number_of_jobs; //作业数目
	int number_of_machines;//机器数目
	int number_of_operations;//每个作业的工序数目
	int*** p_b_fjsp_processing_time;//每个作业在柔性作业车间每道工序每台机器上的基本加工时间
	int*** p_c_fjsp_processing_time;//每个作业在柔性作业车间每道工序每台机器上的实际加工时间
	double* p_machine_adjust_time;//同质变异质
	double* p_order_due_time;//每个订单的交货期
	double* p_order_completion_time;//记录每个订单的完工时间

	vector <int> product_number;
	vector<pair<int, int>> product_scale;
	vector<double> product_handle_time;
	vector<int> product_order;

	vector<int> actions;
	vector<int> v_path;
	vector<vector<double>> Qtable;
	double input_alpha, input_gamma;

	vector<vector<int>> v_order_product;
	vector <vector<vector <int>>> v_available_machines;//每个job的每个operation的可用机器集

	vector <vector<CIndividual>> v_Chromo;
	vector <CIndividual> v_subChromo;
	vector <CIndividual > v_TotalChromo;

	vector <vector<CIndividual>> v_Chromo_temp;
	vector <vector<CIndividual>> v_new_Chromo;
	vector <CIndividual> v_new_subChromo;
	vector <CIndividual > v_new_TotalChromo;

	vector <vector<CIndividual>> v_new_Chromo_temp;
	vector <CIndividual> v_new_subChromo_temp;
	vector <CIndividual > v_new_TotalChromo_temp;
	vector <vector<CIndividual>> v_new_Chromo_temp1;
	vector <CIndividual > v_new_TotalChromo_temp1;
	vector <vector<CIndividual>> v_new_Chromo_temp2;
	vector <CIndividual > v_new_TotalChromo_temp2;
	vector <vector<CIndividual>> v_new_Chromo_temp3;
	vector <CIndividual > v_new_TotalChromo_temp3;
	vector <vector<CIndividual>> v_new_Chromo_temp4;
	vector <CIndividual > v_new_TotalChromo_temp4;
	vector <vector<CIndividual>> v_new_Chromo_temp5;
	vector <CIndividual > v_new_TotalChromo_temp5;
	vector <vector<CIndividual>> v_new_Chromo_temp6;
	vector <CIndividual > v_new_TotalChromo_temp6;
	vector <vector<CIndividual>> v_new_Chromo_temp7;
	vector <CIndividual > v_new_TotalChromo_temp7;

	vector<vector<CIndividual>> v_ls_Chromo;
	vector <CIndividual> v_ls_subChromo;
	vector<CIndividual> v_ls_TotalChromo;
	vector<vector<CIndividual>> v_ls_Chromo1;
	vector <CIndividual> v_ls_subChromo1;
	vector<CIndividual> v_ls_TotalChromo1;
	vector<vector<CIndividual>> v_ls_Chromo2;
	vector <CIndividual> v_ls_subChromo2;
	vector<CIndividual> v_ls_TotalChromo2;
	vector<vector<CIndividual>> v_ls_Chromo3;
	vector <CIndividual> v_ls_subChromo3;
	vector<CIndividual> v_ls_TotalChromo3;
	vector<vector<CIndividual>> v_ls_Chromo4;
	vector <CIndividual> v_ls_subChromo4;
	vector<CIndividual> v_ls_TotalChromo4;
	vector<vector<CIndividual>> v_ls_Chromo5;
	vector <CIndividual> v_ls_subChromo5;
	vector<CIndividual> v_ls_TotalChromo5;
	vector<vector<CIndividual>> v_ls_Chromo6;
	vector <CIndividual> v_ls_subChromo6;
	vector<CIndividual> v_ls_TotalChromo6;
	vector<vector<CIndividual>> v_ls_Chromo7;
	vector <CIndividual> v_ls_subChromo7;
	vector<CIndividual> v_ls_TotalChromo7;

	vector<vector<CIndividual>> v_ls_Chromo_temp;
	vector <CIndividual> v_ls_subChromo_temp;
	vector<CIndividual> v_ls_TotalChromo_temp;


	double** Q_TABLE;//Q表
	double** input_Q_table_value;
	int State_Number;//状态数
	int Action_Number;//行动数
	double Learning_Rate;//学习率
	double Discount_Factor;//折扣因子

	int State_Current;//初始状态
	int Action_Current;//初始行动
	int State_Next;//下一个状态
	int State_Current1;//初始状态
	int Action_Current1;//初始行动
	int State_Next1;//下一个状态
	int State_Current2;//初始状态
	int Action_Current2;//初始行动
	int State_Next2;//下一个状态
	int State_Current3;//初始状态
	int Action_Current3;//初始行动
	int State_Next3;//下一个状态
	int State_Current4;//初始状态
	int Action_Current4;//初始行动
	int State_Next4;//下一个状态
	int State_Current5;//初始状态
	int Action_Current5;//初始行动
	int State_Next5;//下一个状态
	int State_Current6;//初始状态
	int Action_Current6;//初始行动
	int State_Next6;//下一个状态
	int State_Current7;//初始状态
	int Action_Current7;//初始行动
	int State_Next7;//下一个状态

	double C_value_t;//原种群对新种群的支配程度
	double C_value_v;//新种群对原种群的支配程度
	double DV_value_t;//原种群DV
	double DV_value_v;//新种群DV
	double C_value_t1;//原种群对新种群的支配程度
	double C_value_v1;//新种群对原种群的支配程度
	double DV_value_t1;//原种群DV
	double DV_value_v1;//新种群DV
	double C_value_t2;//原种群对新种群的支配程度
	double C_value_v2;//新种群对原种群的支配程度
	double DV_value_t2;//原种群DV
	double DV_value_v2;//新种群DV
	double C_value_t3;//原种群对新种群的支配程度
	double C_value_v3;//新种群对原种群的支配程度
	double DV_value_t3;//原种群DV
	double DV_value_v3;//新种群DV
	double C_value_t4;//原种群对新种群的支配程度
	double C_value_v4;//新种群对原种群的支配程度
	double DV_value_t4;//原种群DV
	double DV_value_v4;//新种群DV
	double C_value_t5;//原种群对新种群的支配程度
	double C_value_v5;//新种群对原种群的支配程度
	double DV_value_t5;//原种群DV
	double DV_value_v5;//新种群DV
	double C_value_t6;//原种群对新种群的支配程度
	double C_value_v6;//新种群对原种群的支配程度
	double DV_value_t6;//原种群DV
	double DV_value_v6;//新种群DV
	double C_value_t7;//原种群对新种群的支配程度
	double C_value_v7;//新种群对原种群的支配程度
	double DV_value_t7;//原种群DV
	double DV_value_v7;//新种群DV

	double difference_C;//C差值
	double difference_DV;//DV差值
	double difference_C1;//C差值
	double difference_DV1;//DV差值
	double difference_C2;//C差值
	double difference_DV2;//DV差值
	double difference_C3;//C差值
	double difference_DV3;//DV差值
	double difference_C4;//C差值
	double difference_DV4;//DV差值
	double difference_C5;//C差值
	double difference_DV5;//DV差值
	double difference_C6;//C差值
	double difference_DV6;//DV差值
	double difference_C7;//C差值
	double difference_DV7;//DV差值


	using MapType = map<vector<int>, tuple<double, double, double>>;
	vector<MapType> v_replay_buffer; // 创建一个存储 MapType 的 vector
	double pre_input_alpha, pre_input_gamma,pre_total_loss, now_total_loss;


	vector <CIndividual> v_elite_set;
	
	vector <CRankSequ> v_upper_rankSequ;//排序分层 容器
	vector <CRankSequ> v_lower_rankSequ;//排序分层 容器
	vector <vector<CRankSequ>> v_upper_cluster;//储存每层非支配解的个体
	vector <vector<CRankSequ>> v_lower_cluster;//储存每层非支配解的个体

	vector <CIndividual> v_archive;


	vector <CIndividual> v_low_subChromo;
	vector <vector<CIndividual>> v_low_Chromo;//该容器保存获得的所有子代子种群组成的子代种群Qt
	vector <CIndividual> v_low_TotalChromo;//该容器保存获得的所有子代组成的子代种群


public:

	void finData(char* filename);
	void foutData(char* filename, double& time);
	void runcode();
	void init_parameters();//初始化参数函数
	void generInitPopu(vector<Item>& v_product);//初始化种群函数,在init.cpp中
	void randomUpper(CIndividual& T);
	void Upper_H1(CIndividual& T);
	void Upper_H2(CIndividual& T);
	void randomLower(CIndividual& t);
	void Lower_H3(CIndividual& t);
	void upper_evaluate(CIndividual& t, int& board_width, int& board_height, vector<Item>& v_product);//评估适应度函数
	void evaluate_Packing(int& board_width, int& board_height, vector<vector<int>>& v_item_sizes, vector<double>& v_handle_time, vector<int>& ran, double& use_rate, double& consistent_value, vector<Item>& v_product, vector<vector<int>>& v_order_product, vector<pair<int, int>>& v_real_path);
	void evaluate_FJSP(CIndividual& t);//评估适应度函数
	void rank_up(vector <CIndividual>& v_TotalChromo);
	void domRelation_up(const CIndividual& A, const CIndividual& B, int& domRel);
	void domRelation_up1(CIndividual& A1, CIndividual& B1, int& domRel1);
	void domRelation_up2(const CIndividual& A2, const CIndividual& B2, int& domRel2);
	void domRelation_up3(const CIndividual& A3, const CIndividual& B3, int& domRel3);
	void domRelation_up4(const CIndividual& A4, const CIndividual& B4, int& domRel4);
	void domRelation_up5(const CIndividual& A5, const CIndividual& B5, int& domRel5);
	void domRelation_up6(const CIndividual& A6, const CIndividual& B6, int& domRel6);
	void domRelation_up7(const CIndividual& A7, const CIndividual& B7, int& domRel7);

	void crodiversity(vector <CRankSequ>& v_rankSequ, int& start, int& end);
	void rank_low(vector <vector<CIndividual>>& v_Chromo);
	void ranklow(vector<CIndividual>& v_low_subChromo);
	void domRelation_low(const CIndividual& A, const CIndividual& B, int& domRel);
	void update_subpop(vector <CIndividual>& v_TotalChromo, vector <vector<CIndividual>>& v_Chromo);
	
	void ds_operation(vector <CIndividual>& v_TotalChromo, vector <vector<CIndividual>>& v_Chromo, vector<Item>& v_product);
	void ds_operation_individual(CIndividual& des_indiv, vector<Item>& v_product);
	void destruction(CIndividual& INDIV, vector<int>& v_delete_jobs, vector<int>& v_delete_machines);
	void construction(CIndividual& INDIV, vector<int>& v_delete_jobs, vector<int>& v_delete_machines, vector<int>& v_intial_machine_assignment, vector<Item>& v_product);
	void evaluate_construction(CIndividual& nebo, vector<Item>& v_product);
	void evaluate_part_FJSP(CIndividual& nebo);

	void paraller_search(vector <vector<CIndividual>>& v_new_Chromo, vector<CIndividual>& v_new_TotalChromo, vector<Item>& v_product);
	void adaptive_search(vector <vector<CIndividual>>& v_new_Chromo, vector<CIndividual>& v_new_TotalChromo, vector<Item>& v_product);

	void local_search(vector<CIndividual>& v_new_TotalChromo_temp, vector <vector<CIndividual>>& v_new_Chromo_temp, vector<Item>& v_product, int & Action_Current);
	void local_search_IFCA(vector<CIndividual>& v_new_TotalChromo_temp, vector <vector<CIndividual>>& v_new_Chromo_temp, vector<Item>& v_product);
	void local_search1(vector <vector<CIndividual>>& v_new_Chromo_temp1, vector<Item>& v_product);
	void local_search2(vector <vector<CIndividual>>& v_new_Chromo_temp2, vector<Item>& v_product);
	void local_search3(vector <vector<CIndividual>>& v_new_Chromo_temp3, vector<Item>& v_product);
	void local_search4(vector <vector<CIndividual>>& v_new_Chromo_temp4, vector<Item>& v_product);
	void local_search5(vector <vector<CIndividual>>& v_new_Chromo_temp5, vector<Item>& v_product);
	void local_search6(vector <vector<CIndividual>>& v_new_Chromo_temp6, vector<Item>& v_product);
	void local_search7(vector <vector<CIndividual>>& v_new_Chromo_temp7, vector<Item>& v_product);


	void ls_operation_individual(CIndividual& ls_indiv, vector<Item>& v_product, int& Action_Current);
	void ls_operation1(CIndividual& ls_indiv, vector<Item>& v_product);
	void ls_operation2(CIndividual& ls_indiv, vector<Item>& v_product);
	void ls_operation3(CIndividual& ls_indiv, vector<Item>& v_product);
	void ls_operation4(CIndividual& ls_indiv, vector<Item>& v_product);
	void ls_operation5(CIndividual& ls_indiv, vector<Item>& v_product);
	void ls_operation6(CIndividual& ls_indiv, vector<Item>& v_product);
	void ls_operation7(CIndividual& ls_indiv, vector<Item>& v_product);


	void C_metric(vector <CIndividual>& r1_Chromo, vector <CIndividual>& r2_Chromo, double& C_value);
	void DV_metric(vector <CIndividual>& r_Chromo, double& DV_value);
	void C_metric1(vector <CIndividual>& r1_Chromo1, vector <CIndividual>& r2_Chromo1, double& C_value1);
	void DV_metric1(vector <CIndividual>& r_Chromo1, double& DV_value1);
	void C_metric2(vector <CIndividual>& r1_Chromo2, vector <CIndividual>& r2_Chromo2, double& C_value2);
	void DV_metric2(vector <CIndividual>& r_Chromo2, double& DV_value2);
	void C_metric3(vector <CIndividual>& r1_Chromo3, vector <CIndividual>& r2_Chromo3, double& C_value3);
	void DV_metric3(vector <CIndividual>& r_Chromo3, double& DV_value3);
	void C_metric4(vector <CIndividual>& r1_Chromo4, vector <CIndividual>& r2_Chromo4, double& C_value4);
	void DV_metric4(vector <CIndividual>& r_Chromo4, double& DV_value4);
	void C_metric5(vector <CIndividual>& r1_Chromo5, vector <CIndividual>& r2_Chromo5, double& C_value5);
	void DV_metric5(vector <CIndividual>& r_Chromo5, double& DV_value5);
	void C_metric6(vector <CIndividual>& r1_Chromo6, vector <CIndividual>& r2_Chromo6, double& C_value6);
	void DV_metric6(vector <CIndividual>& r_Chromo6, double& DV_value6);
	void C_metric7(vector <CIndividual>& r1_Chromo7, vector <CIndividual>& r2_Chromo7, double& C_value7);
	void DV_metric7(vector <CIndividual>& r_Chromo7, double& DV_value7);

	void out_result(vector <vector<CIndividual>>& V_Chromo,vector<CIndividual>& V_TotalChromo);

	void genetic_operation(vector <CIndividual>& v_TotalChromo, vector <vector<CIndividual>>& v_Chromo, vector<Item>& v_product);
	void upper_select(CIndividual& upper_fathIndiv, CIndividual& upper_mothIndiv, vector <vector<CIndividual>>& v_Chromo_temp);
	void upper_crossover(CIndividual& upper_fathIndiv, CIndividual& upper_mothIndiv, CIndividual& upper_chIndiv1, CIndividual& upper_chIndiv2);
	void upper_mutate(CIndividual& t, double rate);
	void lowleveloptimization(vector<CIndividual>& v_ls_TotalChromo_temp, vector <vector<CIndividual>>& v_ls_Chromo_temp, vector<Item>& v_product);
	void selection_next_pop(vector <CIndividual>& v_TotalChromo, vector <vector<CIndividual>>& v_Chromo, vector <CIndividual>& v_low_TotalChromo, vector <vector<CIndividual>>& v_low_Chromo, vector<Item>& v_product);
	void Train_Qtable(int& iter_num, int& number_of_products, int& board_width, int& board_height, vector<Item>& v_product, vector<int>& v_path, vector<vector<int>>& v_order_product, vector<vector<double>> & Qtable, double& input_alpha, double& input_gamma);
	void Choose_action(int& action_number, vector<int>& path, double& epsilon, vector<vector<double>>& qvalue, vector<double>& he_value_set, int& number_of_products);
	void Transform(int& action_number, int& s_next, double& reward, bool& bool_value);

	void lower_crossover(CIndividual& lower_fathIndiv, CIndividual& lower_mothIndiv, CIndividual& lower_chIndiv1, CIndividual& lower_chIndiv2);
	void lower_mutate(CIndividual& t, double rate);
	void lowlevel_optimization(vector<CIndividual>& v_new_TotalChromo_temp, vector <vector<CIndividual>>& v_new_Chromo_temp, vector<Item>& v_product);
	void lower_select(CIndividual& lower_fathIndiv, vector<CIndividual>& v_new_subChromo_temp);
	void update_archive(vector <CIndividual>& v_archive_set);

	void update_blemo_framework(vector <CIndividual>& v_ls_TotalChromo, vector <vector<CIndividual>>& v_ls_Chromo, vector<Item>& v_product);
};