#include <iomanip>
#include "Qpacking.h"
#include "Individual.h"
#include <cmath>

void QPacking::upper_evaluate(CIndividual& t, int& board_width, int& board_height, vector<Item>& v_product)//评估适应度
{
	//cout << "board_width = " << board_width << endl;
	//cout << "board_height = " << board_height << endl;

	vector <vector<double>>().swap(t.v_ul_objectives);//清空内存，保证每个 个体 的 目标值容器 为0

	////Step1：根据当前下层向量给出的排入路径，调用最低水平线算法，计算板材利用率和每个矩形件（job）的完工时间
	vector<int> path;
	//cout << "矩形件排入路径（下层向量）：" << endl;
	for (int k = 0; k < t.v_chromosome2.size(); k++)
	{
		//cout << t.v_chromosome2[k].job_number << " ";
		path.push_back(t.v_chromosome2[k].job_number);
	}
	//cout << endl;
	//system("pause");
	
	////Step1.1：获取路径上每个矩形件并储存其尺寸以及处理时间放入ran和v_item_sizes和v_handle_time容器中
	vector<int>ran;
	ran.assign(path.begin(), path.end());//把path复制给ran,此时path未受影响，若用swap，path变空
	//for (int m = 0; m < ran.size(); m++)
	//{
	//	cout << ran[m] << " ";
	//}
	//cout << endl;
	vector<vector<int>> v_item_sizes;
	for (int m = 0; m < path.size(); m++)
	{
		vector<int> v_is;
		int product_index = path[m] - 1;
		v_is.push_back(v_product[product_index].width);
		v_is.push_back(v_product[product_index].height);
		v_item_sizes.push_back(v_is);
	}
	//cout << endl;
	//cout << "依次输出这些矩形件的尺寸" << endl;
	//for (int m = 0; m < v_item_sizes.size(); m++)
	//{
	//	for (int n = 0; n < v_item_sizes[m].size(); n++)
	//	{
	//		cout << v_item_sizes[m][n] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	// system("pause");
	vector<double>v_handle_time;
	for (int m = 0; m < path.size(); m++)
	{
		int product_index = path[m] - 1;
		double p_handle_time = v_product[product_index].handle_time;
		v_handle_time.push_back(p_handle_time);
	}
	//cout << "依次输出这些矩形件的处理时间" << endl;
	//for (int m = 0; m < v_handle_time.size(); m++)
	//{
	//	cout << v_handle_time[m] << " ";
	//}
	//cout << endl;
	//system("pause");

	////Step1.2：调用calculate函数计算下层目标函数：板材利用率和一致性目标
	double use_rate = 0;
	double consistent_value = 0;
	vector<pair<int,int>> v_real_path;
	evaluate_Packing(board_width, board_height, v_item_sizes, v_handle_time, ran, use_rate, consistent_value, v_product, v_order_product, v_real_path);
	for (int m = 0; m < v_real_path.size(); m++)
	{
		t.v_real_packing_route.push_back(v_real_path[m]);//储存实际排样顺序及完工时间
	}
	t.consistant_value = consistent_value;
	//cout << "下层Packing的consistant_value = " << t.consistant_value << endl;
	t.use_rate = (1 - use_rate) * 100;//目标是最小化，故取倒数
	//cout << "下层Packing的use_rate = " << t.use_rate << endl;


	vector <int>().swap(t.v_job_packing_finish_time);//供上层使用
	for (int u = 0; u < number_of_jobs; u++)
	{
		int f_time = v_product[u].finish_time;
		//cout << "f_time = " << f_time << endl;
		t.v_job_packing_finish_time.push_back(f_time);
	}
	//system("pause");

	////Step1.2：调用evaluate_FJSP函数计算上层目标函数：total_tardiness和total_cost
	evaluate_FJSP(t);
	//cout << "上层FJSP的总延迟total_tardiness = " << t.total_tardiness << endl;
	//cout << "上层FJSP的总成本total_cost = " << t.total_cost << endl;
	//system("pause");

	///Step3：储存目标
	vector<double> v1;
	v1.push_back(t.total_tardiness);
	v1.push_back(t.total_cost);
	t.v_ul_objectives.push_back(v1);
	vector<double> v2;
	v2.push_back(t.consistant_value);
	v2.push_back(t.use_rate);
	t.v_ul_objectives.push_back(v2);
	//for (int u = 0; u < t.v_ul_objectives.size(); u++)
	//{
	//	for (int v = 0; v < t.v_ul_objectives[u].size(); v++)
	//	{
	//		cout << t.v_ul_objectives[u][v] << " ";
	//	}
	//}
	//cout << endl;
	//system("pause");
}