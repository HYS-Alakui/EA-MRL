#include <iomanip>
#include <vector>
#include <iostream>
#include "Headfile.h"
#include "Qpacking.h"
#include "Item.h"

void QPacking::finData(char* filename)
{
	ifstream fin;
	fin.open(filename);
	if (!fin)
	{
		cout << "open the file failure when read in data from instance information.txt" << endl;
		system("pause");
	}

	fin >> number_of_products;
	//cout << "numbre_of_products = " << number_of_products << endl;
	fin >> board_width >> board_height;
	//cout << "board_width = " << board_width << endl;
	//cout << "board_height = " << board_height << endl;
	fin >> number_of_orders;
	//system("pause");


	vector <int>().swap(product_number);
	vector<pair<int, int>>().swap(product_scale) ;
	vector<double>().swap(product_handle_time);
	vector <int>().swap(product_order);
	int pro_num, pro_sca_f, pro_sca_s,pro_order;
	double pro_had_t;
	for (int i = 0; i < number_of_products; i++)
	{
		fin >> pro_num;
		//cout << "pro_num = " << pro_num << endl;
		product_number.push_back(pro_num);

		fin >> pro_sca_f;
		//cout << "pro_sca_f = " << pro_sca_f << endl;
		fin >> pro_sca_s;
		//cout << "pro_sca_s = " << pro_sca_s << endl;
		pair<int, int> pro_pair(pro_sca_f,pro_sca_s);
		product_scale.push_back(pro_pair);

		fin >> pro_had_t;
		//cout << "pro_had_t = " << pro_had_t << endl;
		product_handle_time.push_back(pro_had_t);

		fin >> pro_order;
		//cout << "pro_order = " << pro_order << endl;
		product_order.push_back(pro_order);
	}

	//cout << "所有矩形件的编号：" << endl;
	//for (int i = 0; i < product_number.size(); i++)
	//{
	//	cout << product_number[i] << " ";
	//}
	//cout << endl;
	//cout << "所有矩形件的尺寸：" << endl;
	//for (int i = 0; i < product_scale.size(); i++)
	//{
	//    cout << "矩形件" << i + 1 << "的宽是" << product_scale[i].first <<" ";
	//    cout << "矩形件" << i + 1 << "的高是" << product_scale[i].second << endl;
	//}
	//cout << "所有矩形件的切割时间：" << endl;
	//for (int i = 0; i < product_handle_time.size(); i++)
	//{
	//    cout << product_handle_time[i] << " ";
	//}
	//cout << endl;
	//cout << "所有矩形件的订单号：" << endl;
	//for (int i = 0; i < product_order.size(); i++)
	//{
	//	cout << product_order[i] << " ";
	//}
	//cout << endl;



	fin >> number_of_jobs >> number_of_operations >> number_of_machines;
	//cout << "number_of_jobs = " << number_of_jobs << endl;
	//cout << "number_of_operations = " << number_of_operations << endl;
	//cout << "number_of_machines = " << number_of_machines << endl;

	//FJSP加工时间
	p_b_fjsp_processing_time = new int** [number_of_operations];//是一个包含number_of_factories个元素的数组1
	for (int i = 0; i < number_of_operations; i++)
	{
		p_b_fjsp_processing_time[i] = new int* [number_of_machines];//数组1中 每个元素 都指向一个 包含number_of_machines个元素的数组2
		for (int j = 0; j < number_of_machines; j++)
		{
			p_b_fjsp_processing_time[i][j] = new int[number_of_jobs];
		}
	}
	for (int i = 0; i < number_of_operations; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			for (int k = 0; k < number_of_jobs; k++)
			{
				fin >> p_b_fjsp_processing_time[i][j][k];
			}
		}
	}

	//FJSP
	p_machine_adjust_time = new double[number_of_machines];
	for (int i = 0; i < number_of_machines; i++)
	{
		fin >> p_machine_adjust_time[i];
		//cout << p_machine_adjust_time[i] << " ";
	}
	//cout << endl;

	//FJSP
	p_order_due_time = new double[number_of_orders];
	for (int i = 0; i < number_of_orders; i++)
	{
		fin >> p_order_due_time[i];
		//cout << p_order_due_time[i] << " ";
	}
	//cout << endl << endl << endl;

	fin >> input_alpha >> input_gamma;
	//cout << "input_afa = " << input_alpha << endl;
	//cout << "input_gamma = " << input_gamma << endl;

	input_Q_table_value = new double* [number_of_products];
	for (int i = 0; i < number_of_products; i++)
	{
		input_Q_table_value[i] = new double[number_of_products];
	}
	for (int i = 0; i < number_of_products; i++)
	{
		for (int j = 0; j < number_of_products; j++)
		{
			fin >> input_Q_table_value[i][j];
		}
	}

	State_Number = 4;//状态数
	Action_Number = 7;//行动数
	Q_TABLE = new double* [State_Number];
	for (int i = 0; i < State_Number; i++)
	{
		Q_TABLE[i] = new double[Action_Number];
	}

	fin.close();
	//system("pause");
}

void QPacking::foutData(char* filename, double & time)
{
	ofstream fout;
	fout.open(filename);//创建 .\\result_NSGAII\\result - findex0 - findex1\\findex2.txt
	if (!fout)
	{
		cout << "open the file failure when output the data" << endl;
		cout << filename << endl;
		system("pause");
	}

	//fout << best_rate << endl;//非支配解数量
	//fout << endl;

	//for (int i = 0; i < v_best_path.size(); i++)
	//{
	//	fout << v_best_path[i] << " ";
	//}
	//fout << endl;
	//fout << endl;

	//for (int i = 0; i < v_best_product.size(); i++)
	//{
	//	fout << v_best_product[i].order << " ";
	//	fout << v_best_product[i].number << " ";
	//	fout << v_best_product[i].xuanz << " ";
	//	fout << v_best_product[i].width << " ";
	//	fout << v_best_product[i].height << " ";
	//	fout << v_best_product[i].handle_time << " ";
	//	fout << v_best_product[i].finish_time << " ";
	//	fout << v_best_product[i].layout << " ";
	//	fout << v_best_product[i].origin_x << " ";
	//	fout << v_best_product[i].down_y << " ";
	//	fout << v_best_product[i].he_value << endl;
	//}
	//fout << endl;


	//for (int i = 0; i < v_best_q_table.size(); i++)
	//{
	//	for (int j = 0; j < v_best_q_table[i].size(); j++)
	//	{
	//		fout << std::left << std::setw(10) << fixed << setprecision(2) << v_best_q_table[i][j] << " ";
	//	}
	//	fout << endl;
	//}
	//fout << endl;

	for (int m = 0; m < v_archive.size(); m++)
	{
		//cout << "m = " << m << endl;
		//for (int n = 0; n < number_of_jobs * number_of_operations; n++)
		//{
		//	cout << v_archive[m].v_chromosome1[n].operation_number << " ";
		//}
		//cout << endl;
		//for (int n = number_of_jobs * number_of_operations; n < v_archive[m].v_chromosome1.size(); n++)
		//{
		//	cout << v_archive[m].v_chromosome1[n].machine_number << " ";
		//}
		//cout << endl;
		//for (int n = 0; n < number_of_jobs; n++)
		//{
		//	cout << v_archive[m].v_chromosome2[n].job_number << " ";
		//}
		//cout << endl;
		for (int n = 0; n < v_archive[m].v_ul_objectives.size(); n++)
		{
			for (int h = 0; h < v_archive[m].v_ul_objectives[n].size(); h++)
			{
				fout << v_archive[m].v_ul_objectives[n][h] << " ";
			}
		}
		fout << endl;
		//cout << v_archive[m].upper_rank << endl;
		//cout << v_archive[m].lower_rank << endl;
		//system("pause");
	}

	fout << time << endl;

	fout.close();	//结束输出
	//system("pause");

	for (int i = 0; i < number_of_operations; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			delete[] p_b_fjsp_processing_time[i][j];
		}
		delete[] p_b_fjsp_processing_time[i];
	}
	delete[] p_b_fjsp_processing_time;

	delete[] p_machine_adjust_time;

	for (int i = 0; i < number_of_operations; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			delete[] p_c_fjsp_processing_time[i][j];
		}
		delete[] p_c_fjsp_processing_time[i];
	}
	delete[] p_c_fjsp_processing_time;

	delete[] p_order_due_time;
}
