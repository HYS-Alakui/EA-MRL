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
	////�²�����Ż�
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

	//cout << "Before_v_ls_Chromo_temp��" << endl;
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


	////Step1:���ÿ������Ⱥ����Qѧϰ��õ�������Ⱥv_low_subChromo�����v_low_Chromo��Qt
	vector <vector<CIndividual>>().swap(v_low_Chromo);//�����������õ������Ӵ�����Ⱥ��ɵ��Ӵ���ȺQt
	for (int i = 0; i < number_of_subpop; i++)//���v_ls_Chromo_temp��ÿ������Ⱥ��ÿ�������Qѧϰ
	{
		//cout << "number_of_subpop = " << i + 1 << endl;	
		vector <CIndividual>().swap(v_low_subChromo);
		for (int j = 0; j < lower_number_of_individuals; j++)
		{
			//cout << "j = " << j + 1 << endl;
			
			////Step1�������Ӵ�����ÿ���²��Ż�ʱ���ϲ��������
			CIndividual C1;
			C1.v_chromosome1 = v_ls_Chromo_temp[i][j].v_chromosome1;

			////Step2������һ�������,������Train_Qtable����������һ��·�����²��������õ�һ��ѵ���õ�·��
			QPacking QP;
			int iter_number = 10;//΢������Ϊoffline�Ѿ�ѵ������Q��Ͳ���
			vector<int>().swap(v_path);
			for (int m = 0; m < v_ls_Chromo_temp[i][j].v_chromosome2.size(); m++)
			{
				v_path.push_back(v_ls_Chromo_temp[i][j].v_chromosome2[m].job_number);
			}

			//cout << "ѵ��ǰQ��" << endl;
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
			//cout << "ѵ�����·����" << endl;
			//for (int m = 0; m < v_path.size(); m++)
			//{
			//	cout << v_path[m] << " ";
			//}
			//cout << endl;
			//system("pause");
			//cout << "ѵ����Q��" << endl;
			//for (int ii = 0; ii < Qtable.size(); ii++)
			//{
			//	for (int jj = 0; jj < Qtable[ii].size(); jj++)
			//	{
			//		cout << std::fixed << std::setprecision(4) << Qtable[ii][jj] << " ";
			//	}
			//	cout << endl;
			//}
			//cout << endl;

			////Step3������Ӵ����²�������ѵ���õ�·��
			for (int m = 0; m < v_path.size(); m++)
			{
				CChromosome	ttt;
				ttt.job_number = v_path[m];
				C1.v_chromosome2.push_back(ttt);
			}
			//cout << "����¸��壺" << endl;
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

			//Step4�����������õ����Ӵ����壬�������µ�����Ⱥ��
			upper_evaluate(C1, board_width, board_height, v_product);//���ϲ���²�Ŀ�꺯��ֵ�������²�Ŀ��ֵ��Ȼ������²�Լ������ϲ�Ŀ��ֵ		
			v_low_subChromo.push_back(C1);
			//system("pause");
		}
		////���������Ⱥ���²���ֵ��ӵ���Ⱦ���ֵ
		ranklow(v_low_subChromo);
		//cout << "��ǰ����Ⱥ�ĵ���������Ⱥ��" << endl;
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
		v_low_Chromo.push_back(v_low_subChromo);//��������Ⱥ�浽Qt��

		////��ÿ������Ⱥ���²�rank=1�ĸ������replay_buffer������΢������ѧϰ�ʺ��ۿ����ӣ��Լ�Q��
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
				double firstDouble = v_low_subChromo[u].v_ul_objectives[1][0];  // Ŀ��1
				double secondDouble = v_low_subChromo[u].v_ul_objectives[1][1]; // Ŀ��2
				double thirdDouble = 1000 / (firstDouble + secondDouble);  // ����ֵ
				aMap[v_path_sequence] = make_tuple(firstDouble, secondDouble, thirdDouble); // ʹ�� make_tuple ���� tuple ����ֵ
				v_replay_buffer.push_back(aMap);
			}
		}
		///��ʼѭ����һ������Ⱥ
	}


	//////////////////////////////////�������㾭�黺������������ʷ�������Q���²�Q��ѧϰ�ʺ��ۿ�����/////////////////////////////////////////////////////
	//cout << "pre_total_loss = " << pre_total_loss << endl;
	//cout << "pre_input_alpha = " << setprecision(4) << pre_input_alpha << endl;
	//cout << "pre_input_gamma = " << setprecision(4) << pre_input_gamma << endl;
	////����һ���б�洢����Ԫ�غͶ�Ӧ��thirdDouble
	vector<pair<MapType*, double>> sortableList;
	for (auto& map : v_replay_buffer)
	{
		for (auto& entry : map) 
		{
			double thirdDouble_value = std::get<2>(entry.second);
			sortableList.push_back(make_pair(&map, thirdDouble_value));
		}
	}
	////��thirdDoubleֵ��������
	sort(sortableList.begin(), sortableList.end(),
		[](const pair<MapType*, double>& a, const pair<MapType*, double>& b) {
			return a.second > b.second;
		});
	////���v_replay_buffer֮ǰ���Ƚ���Ҫ��Ԫ�ظ��Ƶ�һ����ʱ����
	vector<MapType> tempBuffer;
	int buffer_size = 10;
	for (int bf = 0; bf < buffer_size; bf++)
	{
		tempBuffer.push_back(*sortableList[bf].first);
	}	
	v_replay_buffer.clear();// ���v_replay_buffer������ʱ�����������
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
	
	////����ѧϰ�ʺ��ۿ�����
	if (outer_iteration_count % 2 == 0)
	{
		//cout << "������alpha�����ϵ��ݶȣ�������alpha��gamma���ֲ���" << std::endl;
		double temp_dafai_value1 = input_alpha;
		double Denominator1 = input_alpha - pre_input_alpha + 0.00000001;//�����ĸΪ0
		if (Denominator1 == 0)
		{
			Denominator1 = 0.00000001;
		}
		//cout << "Denominator1 = "<< Denominator1 <<endl;
		double TD1 = (now_total_loss - pre_total_loss) / Denominator1;
		//cout << "TD1 = " << TD1 << endl;
		input_alpha = input_alpha - exp(-8) * TD1;
		//cout << "input_alpha = " << input_alpha << endl;
		input_alpha = 1 / (1 + exp(-input_alpha));//Sigmoid ����������ʵ��ӳ�䵽 (0, 1) �����ڣ�ʹ��������ڲ������и�������������
		//cout << "input_alpha = "<< input_alpha <<endl;
		pre_input_alpha = temp_dafai_value1;
		pre_total_loss = now_total_loss;
	}
	else
	{
		//cout << "������gamma�����ϵ��ݶȣ�������gamma��alpha���ֲ���" << std::endl;
		double temp_dafai_value2 = input_gamma;
		double Denominator2 = input_gamma - pre_input_gamma + 0.00000001;//�����ĸΪ0
		if (Denominator2 == 0)
		{
			Denominator2 = 0.00000001;
		}
		//cout << "Denominator2 = " << Denominator2 << endl;
		double TD2 = (now_total_loss - pre_total_loss) / Denominator2;
		//cout << "TD2 = " << TD2 << endl;
		input_gamma = input_gamma - exp(-8) * TD2;
		//cout << "input_gamma = " << input_gamma << endl;
		input_gamma = 1 / (1 + exp(-input_gamma));//Sigmoid ����������ʵ��ӳ�䵽 (0, 1) �����ڣ�ʹ��������ڲ������и�������������
		//cout << "input_gamma = " << input_gamma << endl;
		pre_input_gamma = temp_dafai_value2;
		pre_total_loss = now_total_loss;
	}
	//system("pause");
	
	//////����Q��
	vector<int> v_numbers(buffer_size);// ����һ����������ʼ��Ϊ0��9
	for (int ii = 0; ii < buffer_size; ii++)
	{
		v_numbers[ii] = ii;
	}	
	unsigned seed = std::time(0);// ��ȡ����ʱ�������	
	shuffle(v_numbers.begin(), v_numbers.end(), default_random_engine(seed));// ʹ�����Ӵ�������	
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
	
		//�������Q��
		//cout << "·����" << endl;
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

		//cout << "Update_after_qvalue��" << endl;
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
	

	////Step2:���Qt��Ⱥ�����²���ֵ��ӵ���Ⱦ���
	vector <CIndividual>().swap(v_low_TotalChromo);//�����������õ������Ӵ���ɵ��Ӵ���Ⱥ
	for (int i = 0; i < v_low_Chromo.size(); i++)//����v_low_TotalChromo
	{
		for (int j = 0; j < v_low_Chromo[i].size(); j++)
		{
			v_low_TotalChromo.push_back(v_low_Chromo[i][j]);
		}
	}
	////system("pause");
	//cout << "���Qt��v_low_Chromo��" << endl;
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

	rank_up(v_low_TotalChromo);//��ȡQt���ϲ���ֵ��ӵ���Ⱦ���
	rank_low(v_low_Chromo);//���Qt��ÿ������Ⱥ���²���������ӵ���Ⱦ���
	update_subpop(v_low_TotalChromo, v_low_Chromo);
	//cout << "��� v_low_TotalChromoÿ����������²���ֵ��ӵ���Ⱦ���ֵ" << endl;
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
	//cout << "���v_low_Chromoÿ����������²���ֵ��ӵ���Ⱦ���ֵ" << endl;
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
	//cout << "��ʼѵ����" << endl;
	double alpha = input_alpha;
	//cout << "alpha = " << alpha << endl;
	double gamma = input_gamma;
	//cout << "gamma = " << gamma << endl;
	double epsilon = 0.5;

	//cout << "number_of_products = " << number_of_products << endl;
	//cout << "board_width = " << board_width << endl;
	//cout << "board_height = " << board_height << endl;
	//cout << "��ȡ���о��μ�����֪��Ϣ��" << endl;
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
	//cout << "���������²�������" << endl;
	//for (int ii = 0; ii < v_path.size(); ii++)
	//{
	//	cout << v_path[ii] << " ";
	//}
	//system("pause");
	//cout << "ÿ��������������ҵ��" << endl;
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

	////��ʼ��������
	for (int ii = 0; ii < number_of_products; ii++)
	{
		actions.push_back(ii + 1);
	}
	//////��ʼ��Q��
	//for (int ii = 0; ii < number_of_products; ii++)
	//{
	//	vector<double> v;
	//	for (int jj = 0; jj < number_of_products; jj++)
	//	{
	//		v.push_back(0);
	//	}
	//	Qtable.push_back(v);
	//}
	//cout << "��������Q��" << endl;
	//for (int ii = 0; ii < Qtable.size(); ii++)
	//{
	//	for (int jj = 0; jj < Qtable[ii].size(); jj++)
	//	{
	//		cout << std::fixed << std::setprecision(4) << Qtable[ii][jj] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	vector<vector<double>> qvalue; //��Qtable��ֵ��qvalue
	qvalue.swap(Qtable);
	////��ʼ�������ֵ�����·��
	vector<int> v_max_path(number_of_products, 0);
	double max_path_ob1 = 0;
	double max_path_ob2 = 0;
	double max_reward_value = 0;

	////��ʼ����
	for (int iter = 0; iter < iter_num; iter++)
	{
		//cout << "��" << iter + 1 << "�ε�����" << endl;
		//cout << "���iter_before_qvalue��" << endl;
		//for (int ii = 0; ii < qvalue.size(); ii++)
		//{
		//	for (int jj = 0; jj < qvalue[ii].size(); jj++)
		//	{
		//		cout << std::fixed << std::setprecision(4) << qvalue[ii][jj] << " ";
		//	}
		//	cout << endl;
		//}
		//system("pause");

		////��ʼ������·������
		vector<int> path;		
		
		////��ʼ��״̬
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
		bool flag_done = false;//�ж��Ƿ����о��μ����Ѿ�������
		int visit_num = 1;//��¼���������μ�����
		//system("pause");

		////��ʼʹ��Q-Learning���б���
		while (flag_done == false)
		{
			//cout << "������" << visit_num + 1 << "�����μ���" << endl;
			//cout << "Qǰ��path:" << endl;
			//for (int p = 0; p < path.size(); p++)
			//{
			//	cout << path[p] << " ";
			//}
			//cout << endl;
			//system("pause");

			//cout << "path.size() = " << path.size() << endl;
			if (path.size() < number_of_products)
			{
				////Step1������ǰ·��path��qvalue���Լ�̰�����ӣ��������ѡ��������������̰����������ȡ��һ������a
				int action_number = 0;//�����ֵ
				Choose_action(action_number, path, epsilon, qvalue, he_value_set, number_of_products);//����ֻѡȡ�˶�������û�а�ѡ��Ķ�������·���У���pathδ����
				//cout << "Step1��ѡȡ����Action = " << action_number << endl;
				//system("pause");

				////Step2������ǰ·��path�ͻ�ȡ����һ������action_number,����transform����,����״̬
				int s_next = 0;//�����ֵ
				double reward = 0;//�����ֵ
				flag_done = false;//�����ֵ
				Transform(action_number, s_next, reward, flag_done);//��Ҫע��������ת�ƺ������ص���һ�����飬�������ֱ���int,double,��bool�͵ģ�����ֻ�����˽�����������״̬����û�а�ѡ��Ķ�������·���У���pathδ����
				//cout << "Step2����һ��״̬S_next = " << s_next << endl;
				//cout << "Step2������Reward = " << reward << endl;
				//cout << "Step2�����ֵFlag_done = " << flag_done << endl;
				//system("pause");

				////Step3������·�� �ѵ�ǰ��������һ��״̬����ӵ�·����
				path.push_back(s_next);
				//cout << "Step3��Q���path:" << endl;
				//for (int m = 0; m < path.size(); m++)
				//{
				//	cout << path[m] << " ";
				//}
				//cout << endl;
				//system("pause");

				////Step4������s
				state = s_next;//�����s����һ��״̬Ŷ����ΪҪ������һ��Q��
				visit_num++;
				//��ʼ��һ�����μ�
			}
			else
			{
				//cout << "��ʱ���о��μ����ѱ����꣬������һ��״̬��ֻ��Ҫ������������ȥ����ֵ����" << endl;
				//cout << "Update_before_qvalue��" << endl;
				//for (int i = 0; i < qvalue.size(); i++)
				//{
				//	for (int j = 0; j < qvalue[i].size(); j++)
				//	{
				//		cout << qvalue[i][j] << " ";
				//	}
				//	cout << endl;
				//}
				//system("pause");

				//cout << "�������ˮƽ���㷨��" << endl;
				//cout << "·����" << endl;
				//for (int m = 0; m < path.size(); m++)
				//{
				//	cout << path[m] << " ";
				//}
				//cout << endl;

				////Step5.1����ȡ·����ÿ�����μ�����������ߴ�ͼӹ�ʱ�䡣�ֱ����ran_��v_item_sizes��v_handle_time������
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
				//system("pause");

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

			
				////Step5.2������evaluate_Packing���������������ʺ�һ����ֵ������
				double use_rate = 0;
				double consistent_value = 0;
				vector<pair <int, int>> v_real_path;//����ʵ������˳��
				evaluate_Packing(board_width, board_height, v_item_sizes, v_handle_time, ran, use_rate, consistent_value, v_product, v_order_product, v_real_path);//����ʵ������˳��);
				//cout << "�²�Packing��consistent_value = " << consistent_value << endl;
				use_rate = (1 - use_rate) * 100;//waste_rate
				//cout << "�²�Packing��waste_rate = " << use_rate << endl;
				double reward = 1000 / (use_rate + consistent_value);
				//cout << "Final_Reward = " << reward << endl;
				//������ѽ���ֵ���������·��
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


				////Step5.3���������Q��
				//cout << "·����" << endl;
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

				//cout << "Update_after_qvalue��" << endl;
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
		
		////�û�õ�path����v_path
		vector<int>().swap(v_path);
		for (int ii = 0; ii < path.size(); ii++)
		{
			v_path.push_back(path[ii]);
		}
		//cout<<"���ε�����õ�·����"<<endl;
		//for (int ii = 0; ii < v_path.size(); ii++)
		//{
		//	cout << v_path[ii] << " ";
		//}
		//cout << endl;
		//cout<<"��ʷ���·����"<<endl;
		//for (int ii = 0; ii < v_max_path.size(); ii++)
		//{
		//	cout << v_max_path[ii] << " ";
		//}
		//cout << endl;
		//cout << "��" << iter + 1 << "��eposiode����������" << endl;
		//system("pause");
	}

	////��v_max_path����v_path(ѵ�������е����·��)
	for (int ii = 0; ii < v_max_path.size(); ii++)
	{
		v_path[ii] = v_max_path[ii];
	}
	Qtable.swap(qvalue);
	//cout << "ѵ��������" << endl;
}


double generate_noise(double mean, double std_dev)// ���ܣ�������̬�ֲ�����
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> d(mean, std_dev);
	return d(gen);
}


void QPacking::Choose_action(int& action_number, vector<int>& path, double& epsilon, vector<vector<double>>& qvalue, vector<double>& he_value_set, int& number_of_products)
{
	const int inf = 0x3f3f3f3f;
	//cout << "ѡ������������Ҫ��������path:" << endl;
	//for (int p = 0; p < path.size(); p++)
	//{
	//	cout << path[p] << " ";
	//}
	//cout << endl;

	double rand_num = ((double)rand()) / RAND_MAX;
	//cout << "rand_num = " << rand_num << endl;
	//cout << "epsilon = " << epsilon << endl;//epsilon��ʼֵ��0.5�� �����½�����ʼ�գ�0.05�����Ž�����Խ��Խ����̰��
	//system("pause");
	if (rand_num < epsilon)
	{
		//cout << "̰����ѡ��ǰ״̬(last city)�¾������qheֵ�Ķ���" << endl;
		////step1.1����ȡ��ǰ״̬
		int last_product = path.back();//path.back()����path���������һ��Ԫ��
		//cout << "��ǰ״̬last_product = " << last_product << endl;

		////step1.2����ȡqvalue���е�ǰ״̬�����һ��Ԫ�����ڵ���һ��Ԫ��
		auto q_list = qvalue[last_product - 1];
		//cout << "Before��ǰ״̬(last product)������Ԫ�أ�" << endl;
		//for (int m = 0; m < q_list.size(); m++)
		//{
		//	cout << q_list[m] << " ";
		//}
		//cout << endl;
		//system("pause");

		////step1.3����qvalue���е�ǰ״̬�����һ��Ԫ�����ڵ���һ��Ԫ�����Ѿ����ֹ���Ԫ�ؽ��и������ֵ
		for (int m = 0; m < path.size(); m++)//����ȡpath�е�Ԫ��
		{
			int path_element = path[m];
			//cout << "path_element = " << path_element << endl;
			int path_element_index = path_element - 1;
			q_list[path_element_index] = -inf;//��·�����Ѿ����ֹ���Ԫ�ؼ����е�qֵ ��ֵΪ ������󣬱����ٴ�ѡ��
		}
		//cout << "After��ǰ״̬(last product)������Ԫ�أ�" << endl;
		//for (int m = 0; m < q_list.size(); m++)
		//{
		//	cout << q_list[m] << " ";
		//}
		//cout << endl;

		////step1.4������һ����������ÿ��������ѡ��ĸ���ֵ
		vector <double> v_qhe_value;
		vector<double>().swap(v_qhe_value);
		//cout << "ÿ�����μ�������֪ʶֵ��" << endl;
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
		//cout << "ÿ�������ĸ���ֵ��" << endl;
		//for (int m = 0; m < v_qhe_value.size(); m++)
		//{
		//	cout << v_qhe_value[m] << " ";
		//}
		//cout << endl;
		//system("pause");

		////step1.5����ȡ�����ص�ǰ״̬��������ֵ��Ӧ�Ķ�������
		int max_qhe_action_index = 0;//��ʼ��
		int max_qhe_value = *max_element(v_qhe_value.begin(), v_qhe_value.end());//��ȡ���ֵ
		//cout << "max_qhe_value = " << max_qhe_value << endl;
		vector<int> v_max_indexs;//���������ͬ���ֵ��λ������
		for (int m = 0; m < v_qhe_value.size(); m++)
		{
			if (v_qhe_value[m] == max_qhe_value)
			{
				v_max_indexs.push_back(m);
			}
		}
		if (v_max_indexs.size() >= 2)
		{
			//cout << "���ѡ��һ��λ��������" << endl;
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
			max_qhe_action_index = max_element(v_qhe_value.begin(), v_qhe_value.end()) - v_qhe_value.begin();//��ȡ���ֵ�����������������Qֵ��Ӧ�Ķ�������		
		}
		//cout << "max_qhe_action_index = " << max_qhe_action_index << endl;
		action_number = max_qhe_action_index + 1;
		//cout << "action_number = " << action_number << endl;
		//system("pause");
	}
	else
	{
		//cout << "���ѡȡһ������" << endl;
		while (1)
		{
			////step1.1�����ѡ��һ������
			//cout << "actions.size()=" << actions.size() << endl;
			int index = rand() % actions.size();
			//cout << "index = " << index << endl;
			int choose_action_number = actions[index];//����ڶ����б���ѡ��һ��������ֻҪ�ö���û�г��ֹ������ɱ�ѡȡ
			//cout << "choose_action_number = " << choose_action_number << endl;

			////step1.2���жϸö����Ƿ��ѱ�ѡ��δѡ����Ϊ��һ���������ѳ����������������
			if (find(path.begin(), path.end(), choose_action_number) == path.end()) //find����������path�����д�ͷ��β��������ָ��Ԫ��action_number��if (find() != path.end())��һ��������䣬�����ж�find()�����Ƿ��ҵ���Ŀ��Ԫ�ء�
			{
				//cout << "û��path�������ҵ�Ԫ��action_number" << endl;
				action_number = choose_action_number;
				break;
			}
			else
			{
				//cout << "���ָ�Ԫ���Ѵ���path������,����ѭ�����������" << endl;
				continue;
			}
		}
		//cout << "action_number = " << action_number << endl;
		//system("pause");
	}
	//cout << "ѡ��������ִ�н���������һ��������" << endl;
}


void QPacking::Transform(int& action_number, int& s_next, double& reward, bool& bool_value)
{
	s_next = action_number;
	reward = 0;
	bool_value = false;
}