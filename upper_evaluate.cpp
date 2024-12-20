#include <iomanip>
#include "Qpacking.h"
#include "Individual.h"
#include <cmath>

void QPacking::upper_evaluate(CIndividual& t, int& board_width, int& board_height, vector<Item>& v_product)//������Ӧ��
{
	//cout << "board_width = " << board_width << endl;
	//cout << "board_height = " << board_height << endl;

	vector <vector<double>>().swap(t.v_ul_objectives);//����ڴ棬��֤ÿ�� ���� �� Ŀ��ֵ���� Ϊ0

	////Step1�����ݵ�ǰ�²���������������·�����������ˮƽ���㷨�������������ʺ�ÿ�����μ���job�����깤ʱ��
	vector<int> path;
	//cout << "���μ�����·�����²���������" << endl;
	for (int k = 0; k < t.v_chromosome2.size(); k++)
	{
		//cout << t.v_chromosome2[k].job_number << " ";
		path.push_back(t.v_chromosome2[k].job_number);
	}
	//cout << endl;
	//system("pause");
	
	////Step1.1����ȡ·����ÿ�����μ���������ߴ��Լ�����ʱ�����ran��v_item_sizes��v_handle_time������
	vector<int>ran;
	ran.assign(path.begin(), path.end());//��path���Ƹ�ran,��ʱpathδ��Ӱ�죬����swap��path���
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
	//cout << "���������Щ���μ��ĳߴ�" << endl;
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
	//cout << "���������Щ���μ��Ĵ���ʱ��" << endl;
	//for (int m = 0; m < v_handle_time.size(); m++)
	//{
	//	cout << v_handle_time[m] << " ";
	//}
	//cout << endl;
	//system("pause");

	////Step1.2������calculate���������²�Ŀ�꺯������������ʺ�һ����Ŀ��
	double use_rate = 0;
	double consistent_value = 0;
	vector<pair<int,int>> v_real_path;
	evaluate_Packing(board_width, board_height, v_item_sizes, v_handle_time, ran, use_rate, consistent_value, v_product, v_order_product, v_real_path);
	for (int m = 0; m < v_real_path.size(); m++)
	{
		t.v_real_packing_route.push_back(v_real_path[m]);//����ʵ������˳���깤ʱ��
	}
	t.consistant_value = consistent_value;
	//cout << "�²�Packing��consistant_value = " << t.consistant_value << endl;
	t.use_rate = (1 - use_rate) * 100;//Ŀ������С������ȡ����
	//cout << "�²�Packing��use_rate = " << t.use_rate << endl;


	vector <int>().swap(t.v_job_packing_finish_time);//���ϲ�ʹ��
	for (int u = 0; u < number_of_jobs; u++)
	{
		int f_time = v_product[u].finish_time;
		//cout << "f_time = " << f_time << endl;
		t.v_job_packing_finish_time.push_back(f_time);
	}
	//system("pause");

	////Step1.2������evaluate_FJSP���������ϲ�Ŀ�꺯����total_tardiness��total_cost
	evaluate_FJSP(t);
	//cout << "�ϲ�FJSP�����ӳ�total_tardiness = " << t.total_tardiness << endl;
	//cout << "�ϲ�FJSP���ܳɱ�total_cost = " << t.total_cost << endl;
	//system("pause");

	///Step3������Ŀ��
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