#include "Headfile.h"
#include "Qpacking.h"
#include "Item.h"
#include "Chromosome.h"
#include "Individual.h"
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>
#include <tuple>
#include <random>
#include <ctime>

void QPacking::lowleveloptimization(vector<CIndividual>& v_ls_TotalChromo_temp, vector <vector<CIndividual>>& v_ls_Chromo_temp, vector<Item>& v_product)
{
	////下层迭代优化
	//cout << "Before_v_ls_TotalChromo_temp:" << endl;
	//for (int m = 0; m < v_ls_TotalChromo_temp.size(); m++)
	//{
	//	cout << "m = " << m + 1 << endl;
	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
	//	{
	//		cout << v_ls_TotalChromo_temp[m].v_chromosome1[n].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
	//	{
	//		cout << v_ls_TotalChromo_temp[m].v_chromosome1[n].operation_index << " ";
	//	}
	//	cout << endl;
	//	for (int n = number_of_jobs * number_of_operations; n < v_ls_TotalChromo_temp[m].v_chromosome1.size(); n++)
	//	{
	//		cout << v_ls_TotalChromo_temp[m].v_chromosome1[n].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = number_of_jobs * number_of_operations; n < v_ls_TotalChromo_temp[m].v_chromosome1.size(); n++)
	//	{
	//		cout << v_ls_TotalChromo_temp[m].v_chromosome1[n].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < v_ls_TotalChromo_temp[m].v_chromosome2.size(); n++)
	//	{
	//		cout << v_ls_TotalChromo_temp[m].v_chromosome2[n].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < v_ls_TotalChromo_temp[m].v_ul_objectives.size(); n++)
	//	{
	//		for (int v = 0; v < v_ls_TotalChromo_temp[m].v_ul_objectives[n].size(); v++)
	//		{
	//			cout << v_ls_TotalChromo_temp[m].v_ul_objectives[n][v] << " ";
	//		}
	//	}
	//	cout << endl;
	//	cout << v_ls_TotalChromo_temp[m].upper_rank << " " << v_ls_TotalChromo_temp[m].upper_crowdedistance << endl;
	//	cout << v_ls_TotalChromo_temp[m].lower_rank << " " << v_ls_TotalChromo_temp[m].lower_crowdedistance << endl;
	//}
	//system("pause");

	//cout << "Before_v_ls_Chromo_temp：" << endl;
	//for (int m = 0; m < v_ls_Chromo_temp.size(); m++)
	//{
	//	cout << "sub_no = " << m + 1 << endl;
	//	for (int n = 0; n < v_ls_Chromo_temp[m].size(); n++)
	//	{
	//		cout << "iner = " << n + 1 << endl;
	//		cout << v_ls_Chromo_temp[m][n].sub_no << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_ls_Chromo_temp[m][n].v_chromosome1[u].operation_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_ls_Chromo_temp[m][n].v_chromosome1[u].operation_index << " ";
	//		}
	//		cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_ls_Chromo_temp[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_ls_Chromo_temp[m][n].v_chromosome1[u].machine_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_ls_Chromo_temp[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_ls_Chromo_temp[m][n].v_chromosome1[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_ls_Chromo_temp[m][n].v_chromosome2.size(); u++)
	//		{
	//			cout << v_ls_Chromo_temp[m][n].v_chromosome2[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_ls_Chromo_temp[m][n].v_ul_objectives.size(); u++)
	//		{
	//			for (int v = 0; v < v_ls_Chromo_temp[m][n].v_ul_objectives[u].size(); v++)
	//			{
	//				cout << v_ls_Chromo_temp[m][n].v_ul_objectives[u][v] << " ";
	//			}
	//		}
	//		cout << endl;
	//		cout << v_ls_Chromo_temp[m][n].upper_rank << ",  " << v_ls_Chromo_temp[m][n].upper_crowdedistance << endl;
	//		cout << v_ls_Chromo_temp[m][n].lower_rank << ",  " << v_ls_Chromo_temp[m][n].lower_crowdedistance << endl;
	//	}
	//	cout << endl << endl;
	//}
	//system("pause");


	////Step1:获得每个子种群经过Q学习获得的新子种群v_low_subChromo，组成v_low_Chromo即Qt
	vector <vector<CIndividual>>().swap(v_low_Chromo);//该容器保存获得的所有子代子种群组成的子代种群Qt
	for (int i = 0; i < number_of_subpop; i++)//针对v_ls_Chromo_temp中每个子种群的每个解进行Q学习
	{
		//cout << "number_of_subpop = " << i + 1 << endl;	
		vector <CIndividual>().swap(v_low_subChromo);
		for (int j = 0; j < lower_number_of_individuals; j++)
		{
			//cout << "j = " << j + 1 << endl;
			
			////Step1：创建子代，在每次下层优化时，上层变量不变
			CIndividual C1;
			C1.v_chromosome1 = v_ls_Chromo_temp[i][j].v_chromosome1;

			////Step2：创建一个类对象,调用其Train_Qtable函数，输入一个路径（下层向量）得到一个训练好的路径
			QPacking QP;
			int iter_number = 10;//微调，因为offline已经训练好了Q表和参数
			vector<int>().swap(v_path);
			for (int m = 0; m < v_ls_Chromo_temp[i][j].v_chromosome2.size(); m++)
			{
				v_path.push_back(v_ls_Chromo_temp[i][j].v_chromosome2[m].job_number);
			}

			//cout << "训练前Q表：" << endl;
			//for (int ii = 0; ii < Qtable.size(); ii++)
			//{
			//	for (int jj = 0; jj < Qtable[ii].size(); jj++)
			//	{
			//		cout << std::fixed << std::setprecision(4) << Qtable[ii][jj] << " ";
			//	}
			//	cout << endl;
			//}
			//cout << endl;
			QP.Train_Qtable(iter_number, number_of_products, board_width, board_height, v_product, v_path, v_order_product, Qtable, input_alpha, input_gamma);
			//cout << "训练后的路径：" << endl;
			//for (int m = 0; m < v_path.size(); m++)
			//{
			//	cout << v_path[m] << " ";
			//}
			//cout << endl;
			//system("pause");
			//cout << "训练后Q表：" << endl;
			//for (int ii = 0; ii < Qtable.size(); ii++)
			//{
			//	for (int jj = 0; jj < Qtable[ii].size(); jj++)
			//	{
			//		cout << std::fixed << std::setprecision(4) << Qtable[ii][jj] << " ";
			//	}
			//	cout << endl;
			//}
			//cout << endl;

			////Step3：获得子代的下层向量即训练好的路径
			for (int m = 0; m < v_path.size(); m++)
			{
				CChromosome	ttt;
				ttt.job_number = v_path[m];
				C1.v_chromosome2.push_back(ttt);
			}
			//cout << "输出新个体：" << endl;
			//for (int m = 0; m < number_of_jobs * number_of_operations; m++)
			//{
			//	cout << C1.v_chromosome1[m].operation_number << " ";
			//}
			//cout << endl;
			//for (int m = 0; m < number_of_jobs * number_of_operations; m++)
			//{
			//	cout << C1.v_chromosome1[m].operation_index << " ";
			//}
			//cout << endl;
			//for (int m = number_of_jobs * number_of_operations; m < C1.v_chromosome1.size(); m++)
			//{
			//	cout << C1.v_chromosome1[m].machine_number << " ";
			//}
			//cout << endl;
			//for (int m = number_of_jobs * number_of_operations; m < C1.v_chromosome1.size(); m++)
			//{
			//	cout << C1.v_chromosome1[m].job_number << " ";
			//}
			//cout << endl;
			//for (int m = 0; m < C1.v_chromosome2.size(); m++)
			//{
			//	cout << C1.v_chromosome2[m].job_number << " ";
			//}
			//cout << endl;			
			//system("pause");

			//Step4：最后，评估获得的新子代个体，并存入新的子种群中
			upper_evaluate(C1, board_width, board_height, v_product);//求上层和下层目标函数值：先求下层目标值，然后基于下层约束求解上层目标值		
			v_low_subChromo.push_back(C1);
			//system("pause");
		}
		////获得新子种群的下层序值和拥挤度距离值
		ranklow(v_low_subChromo);
		//cout << "当前子种群的当代新子种群：" << endl;
		//for (int u = 0; u < v_low_subChromo.size(); u++)
		//{
		//	cout << "u = " << u + 1 << endl;
		//	for (int m = 0; m < number_of_jobs * number_of_operations; m++)
		//	{
		//		cout << v_low_subChromo[u].v_chromosome1[m].operation_number << " ";
		//	}
		//	cout << endl;
		//	for (int m = number_of_jobs * number_of_operations; m < v_low_subChromo[u].v_chromosome1.size(); m++)
		//	{
		//		cout << v_low_subChromo[u].v_chromosome1[m].machine_number << " ";
		//	}
		//	cout << endl;
		//	for (int m = 0; m < v_low_subChromo[u].v_chromosome2.size(); m++)
		//	{
		//		cout << v_low_subChromo[u].v_chromosome2[m].job_number << " ";
		//	}
		//	cout << endl;
		//	cout << v_low_subChromo[u].lower_rank << " " << v_low_subChromo[u].lower_crowdedistance << endl;
		//}
		//system("pause");
		v_low_Chromo.push_back(v_low_subChromo);//把新子种群存到Qt中

		////把每个子种群中下层rank=1的个体存入replay_buffer中用于微调更新学习率和折扣因子，以及Q表
		for (int u = 0; u < v_low_subChromo.size(); u++)
		{
			if (v_low_subChromo[u].lower_rank == 1)
			{
				MapType aMap;
				vector<int> v_path_sequence;
				for (int uu = 0; uu < v_low_subChromo[u].v_chromosome2.size(); uu++)
				{
					v_path_sequence.push_back(v_low_subChromo[u].v_chromosome2[uu].job_number);
				}		
				double firstDouble = v_low_subChromo[u].v_ul_objectives[1][0];  // 目标1
				double secondDouble = v_low_subChromo[u].v_ul_objectives[1][1]; // 目标2
				double thirdDouble = 1000 / (firstDouble + secondDouble);  // 奖励值
				aMap[v_path_sequence] = make_tuple(firstDouble, secondDouble, thirdDouble); // 使用 make_tuple 创建 tuple 并赋值
				v_replay_buffer.push_back(aMap);
			}
		}
		///开始循环下一个子种群
	}


	//////////////////////////////////创建优秀经验缓冲区，利用历史经验更新Q表、下层Q的学习率和折扣因子/////////////////////////////////////////////////////
	//cout << "pre_total_loss = " << pre_total_loss << endl;
	//cout << "pre_input_alpha = " << setprecision(4) << pre_input_alpha << endl;
	//cout << "pre_input_gamma = " << setprecision(4) << pre_input_gamma << endl;
	////创建一个列表存储所有元素和对应的thirdDouble
	vector<pair<MapType*, double>> sortableList;
	for (auto& map : v_replay_buffer)
	{
		for (auto& entry : map) 
		{
			double thirdDouble_value = std::get<2>(entry.second);
			sortableList.push_back(make_pair(&map, thirdDouble_value));
		}
	}
	////按thirdDouble值降序排序
	sort(sortableList.begin(), sortableList.end(),
		[](const pair<MapType*, double>& a, const pair<MapType*, double>& b) {
			return a.second > b.second;
		});
	////清空v_replay_buffer之前，先将需要的元素复制到一个临时容器
	vector<MapType> tempBuffer;
	int buffer_size = 10;
	for (int bf = 0; bf < buffer_size; bf++)
	{
		tempBuffer.push_back(*sortableList[bf].first);
	}	
	v_replay_buffer.clear();// 清空v_replay_buffer并从临时容器重新填充
	for (auto& map : tempBuffer) 
	{
		v_replay_buffer.push_back(map);
	}
	//cout << "input_replay_buffer!" << endl;
	for (const auto& map : v_replay_buffer)
	{
		for (const auto& pair : map)
		{
			//cout << "Path: ";
			//for (int num : pair.first)
			//{
			//	cout << num << " ";
			//}
			//cout << "Values: (" << get<0>(pair.second) << ", " << get<1>(pair.second) << ", " << get<2>(pair.second) << ")\n";
			now_total_loss += get<0>(pair.second) + get<1>(pair.second);
		}
	}	
	
	////更新学习率和折扣因子
	if (outer_iteration_count % 2 == 0)
	{
		//cout << "计算在alpha分量上的梯度，并更新alpha，gamma保持不变" << std::endl;
		double temp_dafai_value1 = input_alpha;
		double Denominator1 = input_alpha - pre_input_alpha + 0.00000001;//避免分母为0
		if (Denominator1 == 0)
		{
			Denominator1 = 0.00000001;
		}
		//cout << "Denominator1 = "<< Denominator1 <<endl;
		double TD1 = (now_total_loss - pre_total_loss) / Denominator1;
		//cout << "TD1 = " << TD1 << endl;
		input_alpha = input_alpha - exp(-8) * TD1;
		//cout << "input_alpha = " << input_alpha << endl;
		input_alpha = 1 / (1 + exp(-input_alpha));//Sigmoid 函数将任意实数映射到 (0, 1) 区间内，使其可以用于产生具有概率意义的输出。
		//cout << "input_alpha = "<< input_alpha <<endl;
		pre_input_alpha = temp_dafai_value1;
		pre_total_loss = now_total_loss;
	}
	else
	{
		//cout << "计算在gamma分量上的梯度，并更新gamma，alpha保持不变" << std::endl;
		double temp_dafai_value2 = input_gamma;
		double Denominator2 = input_gamma - pre_input_gamma + 0.00000001;//避免分母为0
		if (Denominator2 == 0)
		{
			Denominator2 = 0.00000001;
		}
		//cout << "Denominator2 = " << Denominator2 << endl;
		double TD2 = (now_total_loss - pre_total_loss) / Denominator2;
		//cout << "TD2 = " << TD2 << endl;
		input_gamma = input_gamma - exp(-8) * TD2;
		//cout << "input_gamma = " << input_gamma << endl;
		input_gamma = 1 / (1 + exp(-input_gamma));//Sigmoid 函数将任意实数映射到 (0, 1) 区间内，使其可以用于产生具有概率意义的输出。
		//cout << "input_gamma = " << input_gamma << endl;
		pre_input_gamma = temp_dafai_value2;
		pre_total_loss = now_total_loss;
	}
	//system("pause");
	
	//////更新Q表
	vector<int> v_numbers(buffer_size);// 创建一个向量并初始化为0至9
	for (int ii = 0; ii < buffer_size; ii++)
	{
		v_numbers[ii] = ii;
	}	
	unsigned seed = std::time(0);// 获取基于时间的种子	
	shuffle(v_numbers.begin(), v_numbers.end(), default_random_engine(seed));// 使用种子打乱数字	
	int mini_batch_size = 5;
	vector<MapType> v_mini_batch;
	for (int ii = 0; ii < mini_batch_size; ii++)
	{
		int bf_index = v_numbers[ii];
		v_mini_batch.push_back(v_replay_buffer[bf_index]);
	}
	//cout << "Mini_batch:" << endl;
	for (const auto& map : v_mini_batch)
	{
		vector<int> Path;
		double reward_value;
		for (const auto& pair : map)
		{
			//cout << "Path: ";
			for (int num : pair.first)
			{
				//cout << num << " ";
				Path.push_back(num);
			}
			//cout << "Values: (" << get<0>(pair.second) << ", " << get<1>(pair.second) << ", " << get<2>(pair.second) << ")\n";
			reward_value = get<2>(pair.second);
		}
	
		//反向更新Q表
		//cout << "路径：" << endl;
		//for (int m = 0; m < Path.size(); m++)
		//{
		//	cout << Path[m] << " ";
		//}
		//cout << endl;
		//cout << "reward_value = " << reward_value << endl;
		//cout << "alpha = " << input_alpha << endl;
		//cout << "gamma = " << input_gamma << endl;	
		for (int m = Path.size() - 1; m > Path.size() - 2; m--)
		{
			//cout << Path[m] << endl;
			int S_index = Path[m - 1] - 1;
			//cout << "S_index = " << S_index << endl;
			int A_index = Path[m] - 1;
			//cout << "A_index = " << A_index << endl;
			Qtable[S_index][A_index] = Qtable[S_index][A_index] + input_alpha * (reward_value + input_gamma * 0 - Qtable[S_index][A_index]);
		}
		//cout << endl;
		//system("pause");
		for (int m = Path.size() - 2; m >= 1; m--)
		{
			//cout << Path[m] << endl;
			int S_index = Path[m - 1] - 1;
			//cout << "S_index = " << S_index << endl;
			int A_index = Path[m] - 1;
			//cout << "A_index = " << A_index << endl;
			int S_next_index = Path[m + 1] - 1;
			//cout << "S_next_index = " << S_next_index << endl;
			Qtable[S_index][A_index] = Qtable[S_index][A_index] + input_alpha * (0 + input_gamma * Qtable[A_index][S_next_index] - Qtable[S_index][A_index]);
		}
		//cout << endl;
		//system("pause");

		//cout << "Update_after_qvalue：" << endl;
		//for (int i = 0; i < Qtable.size(); i++)
		//{
		//	for (int j = 0; j < Qtable[i].size(); j++)
		//	{
		//		cout << std::fixed << std::setprecision(4) << Qtable[i][j] << " ";
		//	}
		//	cout << endl;
		//}
		//system("pause");
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	////Step2:获得Qt种群的上下层序值和拥挤度距离
	vector <CIndividual>().swap(v_low_TotalChromo);//该容器保存获得的所有子代组成的子代种群
	for (int i = 0; i < v_low_Chromo.size(); i++)//更新v_low_TotalChromo
	{
		for (int j = 0; j < v_low_Chromo[i].size(); j++)
		{
			v_low_TotalChromo.push_back(v_low_Chromo[i][j]);
		}
	}
	////system("pause");
	//cout << "输出Qt（v_low_Chromo）" << endl;
	//for (int m = 0; m < v_low_Chromo.size(); m++)
	//{
	//	cout << "sub_no = " << m + 1 << endl;
	//	for (int n = 0; n < v_low_Chromo[m].size(); n++)
	//	{
	//		cout << "iner = " << n + 1 << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_low_Chromo[m][n].v_chromosome1[u].operation_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_low_Chromo[m][n].v_chromosome1[u].operation_index << " ";
	//		}
	//		cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_low_Chromo[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_low_Chromo[m][n].v_chromosome1[u].machine_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_low_Chromo[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_low_Chromo[m][n].v_chromosome1[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_low_Chromo[m][n].v_chromosome2.size(); u++)
	//		{
	//			cout << v_low_Chromo[m][n].v_chromosome2[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_low_Chromo[m][n].v_ul_objectives.size(); u++)
	//		{
	//			for (int v = 0; v < v_low_Chromo[m][n].v_ul_objectives[u].size(); v++)
	//			{
	//				cout << v_low_Chromo[m][n].v_ul_objectives[u][v] << " ";
	//			}
	//		}
	//		cout << endl;
	//		//system("pause");
	//	}
	//	cout << endl << endl;
	//}
	//system("pause");

	rank_up(v_low_TotalChromo);//获取Qt的上层序值和拥挤度距离
	rank_low(v_low_Chromo);//针对Qt中每个子种群的下层进行排序和拥挤度距离
	update_subpop(v_low_TotalChromo, v_low_Chromo);
	//cout << "输出 v_low_TotalChromo每个个体的上下层序值和拥挤度距离值" << endl;
	//for (int m = 0; m < v_low_TotalChromo.size(); m++)
	//{
	//	cout << "m = " << m + 1 << endl;
	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
	//	{
	//		cout << v_low_TotalChromo[m].v_chromosome1[n].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
	//	{
	//		cout << v_low_TotalChromo[m].v_chromosome1[n].operation_index << " ";
	//	}
	//	cout << endl;
	//	for (int n = number_of_jobs * number_of_operations; n < v_low_TotalChromo[m].v_chromosome1.size(); n++)
	//	{
	//		cout << v_low_TotalChromo[m].v_chromosome1[n].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = number_of_jobs * number_of_operations; n < v_low_TotalChromo[m].v_chromosome1.size(); n++)
	//	{
	//		cout << v_low_TotalChromo[m].v_chromosome1[n].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < v_low_TotalChromo[m].v_chromosome2.size(); n++)
	//	{
	//		cout << v_low_TotalChromo[m].v_chromosome2[n].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < v_low_TotalChromo[m].v_ul_objectives.size(); n++)
	//	{
	//		for (int v = 0; v < v_low_TotalChromo[m].v_ul_objectives[n].size(); v++)
	//		{
	//			cout << v_low_TotalChromo[m].v_ul_objectives[n][v] << " ";
	//		}
	//	}
	//	cout << endl;
	//	cout << v_low_TotalChromo[m].upper_rank << " "<< v_low_TotalChromo[m].upper_crowdedistance << endl;
	//	cout << v_low_TotalChromo[m].lower_rank << " "<< v_low_TotalChromo[m].lower_crowdedistance <<endl;
	//}
	//system("pause");	
	//cout << "输出v_low_Chromo每个个体的上下层序值和拥挤度距离值" << endl;
	//for (int m = 0; m < v_low_Chromo.size(); m++)
	//{
	//	cout << "sub_no = " << m + 1 << endl;
	//	for (int n = 0; n < v_low_Chromo[m].size(); n++)
	//	{
	//		cout << "iner = " << n + 1 << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_low_Chromo[m][n].v_chromosome1[u].operation_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_low_Chromo[m][n].v_chromosome1[u].operation_index << " ";
	//		}
	//		cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_low_Chromo[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_low_Chromo[m][n].v_chromosome1[u].machine_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_low_Chromo[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_low_Chromo[m][n].v_chromosome1[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_low_Chromo[m][n].v_chromosome2.size(); u++)
	//		{
	//			cout << v_low_Chromo[m][n].v_chromosome2[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_low_Chromo[m][n].v_ul_objectives.size(); u++)
	//		{
	//			for (int v = 0; v < v_low_Chromo[m][n].v_ul_objectives[u].size(); v++)
	//			{
	//				cout << v_low_Chromo[m][n].v_ul_objectives[u][v] << " ";
	//			}
	//		}
	//		cout << endl;
	//		system("pause");
	//		cout << v_low_Chromo[m][n].upper_rank << " " << v_low_Chromo[m][n].upper_crowdedistance << endl;
	//		cout << v_low_Chromo[m][n].lower_rank << " " << v_low_Chromo[m][n].lower_crowdedistance << endl;
	//		//system("pause");
	//	}
	//	cout << endl<<endl;
	//}
	//system("pause");
}


void QPacking::Train_Qtable(int& iter_num, int& number_of_products, int& board_width, int& board_height, vector<Item>& v_product, vector<int>& v_path, vector<vector<int>>& v_order_product, vector<vector<double>>& Qtable, double & input_alpha, double& input_gamma)
{
	//cout << "开始训练：" << endl;
	double alpha = input_alpha;
	//cout << "alpha = " << alpha << endl;
	double gamma = input_gamma;
	//cout << "gamma = " << gamma << endl;
	double epsilon = 0.5;

	//cout << "number_of_products = " << number_of_products << endl;
	//cout << "board_width = " << board_width << endl;
	//cout << "board_height = " << board_height << endl;
	//cout << "获取所有矩形件的已知信息：" << endl;
	//for (int ii = 0; ii < v_product.size(); ii++)
	//{
	//	cout << v_product[ii].number << " ";
	//	cout << v_product[ii].width << " ";
	//	cout << v_product[ii].height << " ";
	//	cout << v_product[ii].handle_time << " ";
	//	cout << v_product[ii].order << " ";
	//	cout << v_product[ii].he_value << endl;
	//}
	//system("pause");
	//cout << "传进来的下层向量：" << endl;
	//for (int ii = 0; ii < v_path.size(); ii++)
	//{
	//	cout << v_path[ii] << " ";
	//}
	//system("pause");
	//cout << "每个订单包含的作业：" << endl;
	//for (int i = 0; i < v_order_product.size(); i++)
	//{
	//	for (int j = 0; j < v_order_product[i].size(); j++)
	//	{
	//		cout << v_order_product[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//system("pause");

	////初始化动作集
	for (int ii = 0; ii < number_of_products; ii++)
	{
		actions.push_back(ii + 1);
	}
	//////初始化Q表
	//for (int ii = 0; ii < number_of_products; ii++)
	//{
	//	vector<double> v;
	//	for (int jj = 0; jj < number_of_products; jj++)
	//	{
	//		v.push_back(0);
	//	}
	//	Qtable.push_back(v);
	//}
	//cout << "传进来的Q表：" << endl;
	//for (int ii = 0; ii < Qtable.size(); ii++)
	//{
	//	for (int jj = 0; jj < Qtable[ii].size(); jj++)
	//	{
	//		cout << std::fixed << std::setprecision(4) << Qtable[ii][jj] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	vector<vector<double>> qvalue; //将Qtable赋值给qvalue
	qvalue.swap(Qtable);
	////初始化最大奖励值和最佳路径
	vector<int> v_max_path(number_of_products, 0);
	double max_path_ob1 = 0;
	double max_path_ob2 = 0;
	double max_reward_value = 0;

	////开始迭代
	for (int iter = 0; iter < iter_num; iter++)
	{
		//cout << "第" << iter + 1 << "次迭代！" << endl;
		//cout << "输出iter_before_qvalue：" << endl;
		//for (int ii = 0; ii < qvalue.size(); ii++)
		//{
		//	for (int jj = 0; jj < qvalue[ii].size(); jj++)
		//	{
		//		cout << std::fixed << std::setprecision(4) << qvalue[ii][jj] << " ";
		//	}
		//	cout << endl;
		//}
		//system("pause");

		////初始化排入路径容器
		vector<int> path;		
		
		////初始化状态
		int rand_job_location_index = rand() % v_path.size();
		//cout << "rand_job_location_index = " << rand_job_location_index << endl;
		int product_number = v_path[rand_job_location_index];
		int state = product_number;
		//cout << "state = " << state << endl;
		path.push_back(state);
		vector<double> he_value_set;
		for (int ii = 0; ii < number_of_products; ii++)
		{
			he_value_set.push_back(v_product[ii].he_value);
		}
		bool flag_done = false;//判断是否所有矩形件都已经遍历完
		int visit_num = 1;//记录已排样矩形件数量
		//system("pause");

		////开始使用Q-Learning进行遍历
		while (flag_done == false)
		{
			//cout << "遍历第" << visit_num + 1 << "个矩形件！" << endl;
			//cout << "Q前的path:" << endl;
			//for (int p = 0; p < path.size(); p++)
			//{
			//	cout << path[p] << " ";
			//}
			//cout << endl;
			//system("pause");

			//cout << "path.size() = " << path.size() << endl;
			if (path.size() < number_of_products)
			{
				////Step1：将当前路径path和qvalue表以及贪婪因子，传入调用选择动作函数，基于贪婪规则来获取下一个动作a
				int action_number = 0;//随机赋值
				Choose_action(action_number, path, epsilon, qvalue, he_value_set, number_of_products);//这里只选取了动作，并没有把选择的动作加入路径中，故path未更新
				//cout << "Step1：选取动作Action = " << action_number << endl;
				//system("pause");

				////Step2：将当前路径path和获取的下一个动作action_number,传入transform函数,更新状态
				int s_next = 0;//随机赋值
				double reward = 0;//随机赋值
				flag_done = false;//随机赋值
				Transform(action_number, s_next, reward, flag_done);//需要注意的是这个转移函数返回的是一个数组，这个数组分别是int,double,和bool型的；这里只计算了奖励并更新了状态，并没有把选择的动作加入路径中，故path未更新
				//cout << "Step2：下一个状态S_next = " << s_next << endl;
				//cout << "Step2：奖励Reward = " << reward << endl;
				//cout << "Step2：真假值Flag_done = " << flag_done << endl;
				//system("pause");

				////Step3：更新路径 把当前动作（下一个状态）添加到路径中
				path.push_back(s_next);
				//cout << "Step3：Q后的path:" << endl;
				//for (int m = 0; m < path.size(); m++)
				//{
				//	cout << path[m] << " ";
				//}
				//cout << endl;
				//system("pause");

				////Step4：更新s
				state = s_next;//这里的s是下一个状态哦，因为要进行下一次Q了
				visit_num++;
				//开始下一个矩形件
			}
			else
			{
				//cout << "此时所有矩形件都已遍历完，故无下一个状态，只需要调用排样函数去求奖励值即可" << endl;
				//cout << "Update_before_qvalue：" << endl;
				//for (int i = 0; i < qvalue.size(); i++)
				//{
				//	for (int j = 0; j < qvalue[i].size(); j++)
				//	{
				//		cout << qvalue[i][j] << " ";
				//	}
				//	cout << endl;
				//}
				//system("pause");

				//cout << "调用最低水平线算法：" << endl;
				//cout << "路径：" << endl;
				//for (int m = 0; m < path.size(); m++)
				//{
				//	cout << path[m] << " ";
				//}
				//cout << endl;

				////Step5.1：获取路径上每个矩形件，并储存其尺寸和加工时间。分别放入ran_和v_item_sizes和v_handle_time容器中
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
				//system("pause");

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

			
				////Step5.2：调用evaluate_Packing函数计算板材利用率和一致性值即奖励
				double use_rate = 0;
				double consistent_value = 0;
				vector<pair <int, int>> v_real_path;//储存实际排样顺序
				evaluate_Packing(board_width, board_height, v_item_sizes, v_handle_time, ran, use_rate, consistent_value, v_product, v_order_product, v_real_path);//储存实际排样顺序);
				//cout << "下层Packing的consistent_value = " << consistent_value << endl;
				use_rate = (1 - use_rate) * 100;//waste_rate
				//cout << "下层Packing的waste_rate = " << use_rate << endl;
				double reward = 1000 / (use_rate + consistent_value);
				//cout << "Final_Reward = " << reward << endl;
				//更新最佳奖励值和最佳排样路线
				if (reward >= max_reward_value)
				{
					max_path_ob1 = consistent_value;
					max_path_ob2 = use_rate;
					max_reward_value = reward;
					for (int mm = 0; mm < path.size(); mm++)
					{
						v_max_path[mm] = path[mm];
					}
				}
				//cout << "max_reward_value = " << max_reward_value << endl;
				//system("pause");


				////Step5.3：反向更新Q表
				//cout << "路径：" << endl;
				//for (int m = 0; m < path.size(); m++)
				//{
				//	cout << path[m] << " ";
				//}
				//cout << endl;
				//cout << "alpha = " << alpha << endl;
				//cout << "gamma = " << gamma << endl;
				for (int m = path.size() - 1; m > path.size() - 2; m--)
				{
					//cout << path[m] << endl;
					int s_index = path[m - 1] - 1;
					//cout << "s_index = " << s_index << endl;
					int a_index = path[m] - 1;
					//cout << "a_index = " << a_index << endl;
					qvalue[s_index][a_index] = qvalue[s_index][a_index] + alpha * (reward + gamma * 0 - qvalue[s_index][a_index]);
				}
				//cout << endl;
				//system("pause");
				for (int m = path.size() - 2; m >= 1; m--)
				{
					//cout << path[m] << endl;
					int s_index = path[m - 1] - 1;
					//cout << "s_index = " << s_index << endl;
					int a_index = path[m] - 1;
					//cout << "a_index = " << a_index << endl;
					int s_next_index = path[m + 1] - 1;
					//cout << "s_next_index = " << s_next_index << endl;
					qvalue[s_index][a_index] = qvalue[s_index][a_index] + alpha * (0 + gamma * qvalue[a_index][s_next_index] - qvalue[s_index][a_index]);
				}
				//cout << endl;
				//system("pause");

				//cout << "Update_after_qvalue：" << endl;
				//for (int i = 0; i < qvalue.size(); i++)
				//{
				//	for (int j = 0; j < qvalue[i].size(); j++)
				//	{
				//		cout << std::fixed << std::setprecision(4) << qvalue[i][j] << " ";
				//	}
				//	cout << endl;
				//}
				//system("pause");

				flag_done = true;
				//cout << "Flag_done = " << flag_done << endl;
			}
		}
		
		////用获得的path更新v_path
		vector<int>().swap(v_path);
		for (int ii = 0; ii < path.size(); ii++)
		{
			v_path.push_back(path[ii]);
		}
		//cout<<"本次迭代获得的路径："<<endl;
		//for (int ii = 0; ii < v_path.size(); ii++)
		//{
		//	cout << v_path[ii] << " ";
		//}
		//cout << endl;
		//cout<<"历史最佳路径："<<endl;
		//for (int ii = 0; ii < v_max_path.size(); ii++)
		//{
		//	cout << v_max_path[ii] << " ";
		//}
		//cout << endl;
		//cout << "第" << iter + 1 << "次eposiode迭代结束！" << endl;
		//system("pause");
	}

	////用v_max_path更新v_path(训练过程中的最佳路径)
	for (int ii = 0; ii < v_max_path.size(); ii++)
	{
		v_path[ii] = v_max_path[ii];
	}
	Qtable.swap(qvalue);
	//cout << "训练结束！" << endl;
}


double generate_noise(double mean, double std_dev)// 功能：生成正态分布噪声
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> d(mean, std_dev);
	return d(gen);
}


void QPacking::Choose_action(int& action_number, vector<int>& path, double& epsilon, vector<vector<double>>& qvalue, vector<double>& he_value_set, int& number_of_products)
{
	const int inf = 0x3f3f3f3f;
	//cout << "选择动作过程中需要传进来的path:" << endl;
	//for (int p = 0; p < path.size(); p++)
	//{
	//	cout << path[p] << " ";
	//}
	//cout << endl;

	double rand_num = ((double)rand()) / RAND_MAX;
	//cout << "rand_num = " << rand_num << endl;
	//cout << "epsilon = " << epsilon << endl;//epsilon初始值是0.5， 不断下降，但始终＞0.05；随着进化，越来越侧重贪婪
	//system("pause");
	if (rand_num < epsilon)
	{
		//cout << "贪婪：选择当前状态(last city)下具有最大qhe值的动作" << endl;
		////step1.1：获取当前状态
		int last_product = path.back();//path.back()返回path容器中最后一个元素
		//cout << "当前状态last_product = " << last_product << endl;

		////step1.2：获取qvalue表中当前状态即最后一个元素所在的那一行元素
		auto q_list = qvalue[last_product - 1];
		//cout << "Before当前状态(last product)所在行元素：" << endl;
		//for (int m = 0; m < q_list.size(); m++)
		//{
		//	cout << q_list[m] << " ";
		//}
		//cout << endl;
		//system("pause");

		////step1.3：对qvalue表中当前状态即最后一个元素所在的那一行元素中已经出现过的元素进行负无穷大赋值
		for (int m = 0; m < path.size(); m++)//依次取path中的元素
		{
			int path_element = path[m];
			//cout << "path_element = " << path_element << endl;
			int path_element_index = path_element - 1;
			q_list[path_element_index] = -inf;//对路径中已经出现过的元素即城市的q值 赋值为 负无穷大，避免再次选中
		}
		//cout << "After当前状态(last product)所在行元素：" << endl;
		//for (int m = 0; m < q_list.size(); m++)
		//{
		//	cout << q_list[m] << " ";
		//}
		//cout << endl;

		////step1.4：建立一个容器储存每个动作被选择的概率值
		vector <double> v_qhe_value;
		vector<double>().swap(v_qhe_value);
		//cout << "每个矩形件的启发知识值：" << endl;
		//for (int m = 0; m < he_value_set.size(); m++)
		//{
		//	cout << he_value_set[m] << " ";
		//}
		//cout << endl;
		double noise_std_dev = 0.1;
		for (int m = 0; m < q_list.size(); m++)
		{		
			double noise = generate_noise(0.0, noise_std_dev);
			//cout << "noise = " << noise << endl;
			v_qhe_value.push_back(q_list[m] * he_value_set[m] + noise);
		}
		//cout << "每个动作的概率值：" << endl;
		//for (int m = 0; m < v_qhe_value.size(); m++)
		//{
		//	cout << v_qhe_value[m] << " ";
		//}
		//cout << endl;
		//system("pause");

		////step1.5：获取并返回当前状态下最大概率值对应的动作索引
		int max_qhe_action_index = 0;//初始化
		int max_qhe_value = *max_element(v_qhe_value.begin(), v_qhe_value.end());//获取最大值
		//cout << "max_qhe_value = " << max_qhe_value << endl;
		vector<int> v_max_indexs;//储存具有相同最大值的位置索引
		for (int m = 0; m < v_qhe_value.size(); m++)
		{
			if (v_qhe_value[m] == max_qhe_value)
			{
				v_max_indexs.push_back(m);
			}
		}
		if (v_max_indexs.size() >= 2)
		{
			//cout << "随机选中一个位置索引！" << endl;
			//for (int m = 0; m < v_max_indexs.size(); m++)
			//{
			//	cout << v_max_indexs[m] << " ";
			//}
			//cout << endl;
			int rand_position_number = rand() % v_max_indexs.size();
			//cout << "rand_position_number = " << rand_position_number << endl;
			max_qhe_action_index = v_max_indexs[rand_position_number];
		}
		else
		{
			max_qhe_action_index = max_element(v_qhe_value.begin(), v_qhe_value.end()) - v_qhe_value.begin();//获取最大值的索引，即具有最大Q值对应的动作索引		
		}
		//cout << "max_qhe_action_index = " << max_qhe_action_index << endl;
		action_number = max_qhe_action_index + 1;
		//cout << "action_number = " << action_number << endl;
		//system("pause");
	}
	else
	{
		//cout << "随机选取一个动作" << endl;
		while (1)
		{
			////step1.1：随机选择一个动作
			//cout << "actions.size()=" << actions.size() << endl;
			int index = rand() % actions.size();
			//cout << "index = " << index << endl;
			int choose_action_number = actions[index];//随机在动作列表中选择一个动作，只要该动作没有出现过，即可被选取
			//cout << "choose_action_number = " << choose_action_number << endl;

			////step1.2：判断该动作是否已被选择，未选择即作为下一个动作，已出现则重新随机生成
			if (find(path.begin(), path.end(), choose_action_number) == path.end()) //find函数用于在path容器中从头到尾遍历查找指定元素action_number。if (find() != path.end())是一个条件语句，用于判断find()函数是否找到了目标元素。
			{
				//cout << "没在path容器中找到元素action_number" << endl;
				action_number = choose_action_number;
				break;
			}
			else
			{
				//cout << "发现该元素已存在path容器中,继续循环，继续随机" << endl;
				continue;
			}
		}
		//cout << "action_number = " << action_number << endl;
		//system("pause");
	}
	//cout << "选择动作函数执行结束，返回一个动作：" << endl;
}


void QPacking::Transform(int& action_number, int& s_next, double& reward, bool& bool_value)
{
	s_next = action_number;
	reward = 0;
	bool_value = false;
}