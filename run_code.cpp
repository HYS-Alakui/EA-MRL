#include "Headfile.h"
#include "Qpacking.h"
#include "Item.h"
#include "Chromosome.h"
#include "Individual.h"
#include <iomanip>
#include <algorithm>
#include <vector>
#include <map>
#include <tuple>

void QPacking::runcode()
{
	//cout << "当前算例的信息！" << endl;
	//cout << "所有矩形件的编号：" << endl;
	//for (int i = 0; i < product_number.size(); i++)
	//{
	//	cout << product_number[i] << " ";
	//}
	//cout << endl;
	//cout << "所有矩形件的尺寸：" << endl;
	//for (int i = 0; i < product_scale.size(); i++)
	//{
	//	cout << "矩形件" << i + 1 << "的宽是" << product_scale[i].first << " ";
	//	cout << "矩形件" << i + 1 << "的高是" << product_scale[i].second << endl;
	//}
	//cout << "所有矩形件的切割时间：" << endl;
	//for (int i = 0; i < product_handle_time.size(); i++)
	//{
	//	cout << product_handle_time[i] << " ";
	//}
	//cout << endl;
	//cout << "所有矩形件的订单号：" << endl;
	//for (int i = 0; i < product_order.size(); i++)
	//{
	//	cout << product_order[i] << " ";
	//}
	//cout << endl;
	//system("pause");

	////定义一个容器储存所有矩形件的已知属性
	vector<Item> v_product;
	for (int i = 0; i < number_of_products; i++)
	{
		Item p1;
		p1.number = product_number[i];
		p1.width = product_scale[i].first;
		p1.height = product_scale[i].second;
		p1.handle_time = product_handle_time[i];
		p1.order = product_order[i];
		double long_value = p1.height;
		double short_value = p1.width;
		if (p1.width > p1.height)
		{
			long_value = p1.width;
			short_value = p1.height;
		}
		p1.he_value = 0.5 * (long_value * short_value) + 0.5 * (long_value / short_value);
		v_product.push_back(p1);
	}
	//cout << "所有矩形件的已知信息：" << endl;
	//for (int i = 0; i < v_product.size(); i++)
	//{
	//    cout << v_product[i].number << " ";
	//    cout << v_product[i].width << " ";
	//    cout << v_product[i].height << " ";
	//    cout << v_product[i].handle_time << " ";
	//    cout << v_product[i].order << " ";
	//    cout << v_product[i].he_value << endl;
	//}
	//system("pause");

	for (int i = 0; i < number_of_orders; i++)
	{
		vector<int> v;
		for (int j = 0; j < v_product.size(); j++)
		{
			if (v_product[j].order == i + 1)
			{
				v.push_back(v_product[j].number);
			}
		}
		v_order_product.push_back(v);
	}
	//cout << "每个订单包含的作业：" << endl;
	//for (int i = 0; i < v_order_product.size(); i++)
	//{
	//    for (int j = 0; j < v_order_product[i].size(); j++)
	//    {
	//        cout << v_order_product[i][j] << " ";
	//    }
	//    cout << endl;
	//}
	//cout << endl;
	//system("pause");

	////继承训练好的Q表
	for (int ii = 0; ii < number_of_products; ii++)
	{
		vector<double> v;
		for (int jj = 0; jj < number_of_products; jj++)
		{
			v.push_back(input_Q_table_value[ii][jj]);
		}
		Qtable.push_back(v);
	}
	//cout << "当前算例训练好的Q表：" << endl;
	//for (int ii = 0; ii < Qtable.size(); ii++)
	//{
	//	for (int jj = 0; jj < Qtable[ii].size(); jj++)
	//	{
	//		cout << std::fixed << std::setprecision(4) << Qtable[ii][jj] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	init_parameters();//初始化参数 
	generInitPopu(v_product);//初始化种群(包含评估适应度函数：evaluate)   
	rank_up(v_TotalChromo);//获取初始种群的上层序值和拥挤度距离  
	rank_low(v_Chromo);//获取每个子种群的下层进行排序和拥挤度距离
	update_subpop(v_TotalChromo, v_Chromo);
	outer_iteration_count = 0;
	double run_time = (double)(4000 * number_of_jobs * number_of_machines) / CLOCKS_PER_SEC;
	cout << "run_time = " << run_time << endl;
	double start_time = time(NULL);

	while (1)//outer_iteration_count < outer_iteration_count_max
	{
		//cout << "当代初始Pt种群：" << endl;
		//system("pause");
		//out_result(v_Chromo, v_TotalChromo);
		//system("pause");

		////Step1: 对当代初始种群v_TotalChromo/v_Chromo中每个子种群的每个个体的上下层向量进行遗传操作，得到新种群v_new_TotalChromo/v_new_Chromo
		genetic_operation(v_TotalChromo, v_Chromo, v_product);
		rank_up(v_new_TotalChromo);//获取种群中个体的上层序值和拥挤度距离
		rank_low(v_new_Chromo);//获取种群中每个子种群中个体的下层序值和拥挤度距离
		update_subpop(v_new_TotalChromo, v_new_Chromo);//获得新种群v_new_TotalChromo/v_new_Chromo
		//cout << "上层优化后的new种群：" << endl;
		//system("pause");
		//out_result(v_new_Chromo, v_new_TotalChromo);
		//system("pause");
	
		//////Step2: 基于Q学习的LS
		//if (outer_iteration_count < 1)
		//{
		//	paraller_search(v_new_Chromo, v_new_TotalChromo, v_product);//得到LS种群v_ls_TotalChromo, v_ls_Chromo
		//}
		//else
		//{
		//	adaptive_search(v_new_Chromo, v_new_TotalChromo, v_product);
		//}
		
		//////Step2:对下层优化后的新种群执行7种局部搜索，得到LS种群v_ls_TotalChromo, v_ls_Chromo
		vector <CIndividual> v_new_TotalChromo_temp(v_new_TotalChromo);//这里把新种群v_new_TotalChromo/v_new_Chromo赋值给临时种群v_new_TotalChromo_temp/v_new_Chromo_temp
		vector <vector<CIndividual>> v_new_Chromo_temp(v_new_Chromo);
		local_search_IFCA(v_new_TotalChromo_temp, v_new_Chromo_temp, v_product);
		//cout << "局部搜索后的ls种群：" << endl;
		//system("pause");
		//out_result(v_ls_Chromo, v_ls_TotalChromo);
		//system("pause");


		////Step3: 对LS种群v_ls_Chromo, v_ls_TotalChromo进行更新，保持BLEMO框架
		update_blemo_framework(v_ls_TotalChromo, v_ls_Chromo, v_product);
		//cout << "更新后的ls种群：" << endl;
		//system("pause");
		//out_result(v_ls_Chromo, v_ls_TotalChromo);
		//system("pause");
		
		////Step4: 对LS种群中每个子种群展开下层优化，得到经过下层优化的种群v_low_Chromo, v_low_TotalChromo
		vector <CIndividual> v_ls_TotalChromo_temp(v_ls_TotalChromo);//这里把LS种群v_ls_TotalChromo/v_ls_Chromo赋值给临时种群v_ls_TotalChromo_temp/v_ls_Chromo_temp
		vector <vector<CIndividual>> v_ls_Chromo_temp(v_ls_Chromo);
		lowleveloptimization(v_ls_TotalChromo_temp, v_ls_Chromo_temp, v_product);
		//cout << "下层优化后的Qt种群：" << endl;
		//system("pause");
		//out_result(v_low_Chromo, v_low_TotalChromo);
		//system("pause");

		////Step5: 合并Pt和Qt，选择下一代种群v_new_TotalChromo_temp, v_new_Chromo_temp，并赋值给下一代种群v_TotalChromo/v_Chromo
		selection_next_pop(v_TotalChromo, v_Chromo, v_low_TotalChromo, v_low_Chromo, v_product);
		swap(v_TotalChromo, v_new_TotalChromo_temp);
		swap(v_Chromo, v_new_Chromo_temp);
		//cout << "下一代种群:" << endl;
		//out_result(v_Chromo, v_TotalChromo);
		//system("pause");

		////Step6: 保存每次迭代获得的NDu = 1且NDl = 1的个体，然后每次迭代都更新这个数组
		vector<CIndividual> v_archive_set;
		for (int m = 0; m < v_Chromo.size(); m++)
		{
			for (int n = 0; n < v_Chromo[m].size(); n++)
			{
				if (v_Chromo[m][n].upper_rank == 1 && v_Chromo[m][n].lower_rank == 1)
				{
					CIndividual indiv;
					indiv = v_Chromo[m][n];
					v_archive_set.push_back(indiv);
				}
			}
		}
		update_archive(v_archive_set);
		//cout << "更新后外部存档：" << endl;
		//for (int m = 0; m < v_archive.size(); m++)
		//{
		//	cout << "m = " << m << endl;
		//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
		//	{
		//		cout << v_archive[m].v_chromosome1[n].operation_number << " ";
		//	}
		//	cout << endl;
		//	for (int n = number_of_jobs * number_of_operations; n < v_archive[m].v_chromosome1.size(); n++)
		//	{
		//		cout << v_archive[m].v_chromosome1[n].machine_number << " ";
		//	}
		//	cout << endl;
		//	for (int n = 0; n < number_of_jobs; n++)
		//	{
		//		cout << v_archive[m].v_chromosome2[n].job_number << " ";
		//	}
		//	cout << endl;
		//	for (int n = 0; n < v_archive[m].v_ul_objectives.size(); n++)
		//	{
		//		for (int h = 0; h < v_archive[m].v_ul_objectives[n].size(); h++)
		//		{
		//			cout << v_archive[m].v_ul_objectives[n][h] << " ";
		//		}
		//	}
		//	cout << endl;
		//	cout << v_archive[m].upper_rank << endl;
		//	cout << v_archive[m].lower_rank << endl;
		// }
		//system("pause");


		outer_iteration_count++;
		cout << "outer_iteration_count =  " << outer_iteration_count << endl;
		//system("pause");
		if (time(NULL) - start_time > run_time)
			break;
	}
}