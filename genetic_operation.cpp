#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"
#include "Item.h"

void QPacking::genetic_operation(vector <CIndividual>& v_TotalChromo, vector <vector<CIndividual>>& v_Chromo, vector<Item>& v_product)
{
	//for (int m = 0; m < v_TotalChromo.size(); m++)
	//{
	//	cout << "m = " << m + 1 << endl;
	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
	//	{
	//		cout << v_TotalChromo[m].v_chromosome1[n].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
	//	{
	//		cout << v_TotalChromo[m].v_chromosome1[n].operation_index << " ";
	//	}
	//	cout << endl;
	//	for (int n = number_of_jobs * number_of_operations; n < v_TotalChromo[m].v_chromosome1.size(); n++)
	//	{
	//		cout << v_TotalChromo[m].v_chromosome1[n].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = number_of_jobs * number_of_operations; n < v_TotalChromo[m].v_chromosome1.size(); n++)
	//	{
	//		cout << v_TotalChromo[m].v_chromosome1[n].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < v_TotalChromo[m].v_chromosome2.size(); n++)
	//	{
	//		cout << v_TotalChromo[m].v_chromosome2[n].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < v_TotalChromo[m].v_ul_objectives.size(); n++)
	//	{
	//		for (int v = 0; v < v_TotalChromo[m].v_ul_objectives[n].size(); v++)
	//		{
	//			cout << v_TotalChromo[m].v_ul_objectives[n][v] << " ";
	//		}
	//	}
	//	cout << endl;
	//	cout << v_TotalChromo[m].upper_rank << " " << v_TotalChromo[m].upper_crowdedistance << endl;
	//	cout << v_TotalChromo[m].lower_rank << " " << v_TotalChromo[m].lower_crowdedistance << endl;
	//}
	//system("pause");


	vector <vector<CIndividual>>().swap(v_Chromo_temp);
	vector <vector<CIndividual>> v_Chromo_temp(v_Chromo);
	vector <vector<CIndividual>>().swap(v_new_Chromo);
	vector <CIndividual>().swap(v_new_TotalChromo);
	//cout << "拷贝后临时种群：" << endl;
	//for (int m = 0; m < v_Chromo_temp.size(); m++)
	//{
	//	cout << "sub_no = " << m + 1 << endl;
	//	for (int n = 0; n < v_Chromo_temp[m].size(); n++)
	//	{
	//		cout << "iner = " << n + 1 << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_Chromo_temp[m][n].v_chromosome1[u].operation_number << " ";
	//		}
	//		cout << endl;
	//		//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		//{
	//		//	cout << v_Chromo_temp[m][n].v_chromosome1[u].operation_index << " ";
	//		//}
	//		//cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_Chromo_temp[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_Chromo_temp[m][n].v_chromosome1[u].machine_number << " ";
	//		}
	//		cout << endl;
	//		//for (int u = number_of_jobs * number_of_operations; u < v_Chromo_temp[m][n].v_chromosome1.size(); u++)
	//		//{
	//		//	cout << v_Chromo_temp[m][n].v_chromosome1[u].job_number << " ";
	//		//}
	//		//cout << endl;

	//		for (int u = 0; u < v_Chromo_temp[m][n].v_chromosome2.size(); u++)
	//		{
	//			cout << v_Chromo_temp[m][n].v_chromosome2[u].job_number << " ";
	//		}
	//		cout << endl;

	//		for (int u = 0; u < v_Chromo_temp[m][n].v_ul_objectives.size(); u++)
	//		{
	//			for (int v = 0; v < v_Chromo_temp[m][n].v_ul_objectives[u].size(); v++)
	//			{
	//				cout << v_Chromo_temp[m][n].v_ul_objectives[u][v] << " ";
	//			}
	//		}
	//		cout << endl;
	//		//system("pause");

	//		cout << v_Chromo_temp[m][n].upper_rank << ",  " << v_Chromo_temp[m][n].upper_crowdedistance << endl;
	//		cout << v_Chromo_temp[m][n].lower_rank << ",  " << v_Chromo_temp[m][n].lower_crowdedistance << endl;
	//		//system("pause");
	//	}
	//	cout << endl<<endl;
	//}
	//system("pause");


	for (int i = 0; i < number_of_subpop; i++)
	{
		//cout << "i = " << i + 1 << endl;
		CIndividual OutT;

		////Step1:首先，针对每个子种群，利用二元锦标赛选择法选择两个父代
		CIndividual upper_fathIndiv, upper_mothIndiv, upper_chIndiv1, upper_chIndiv2;
		upper_select(upper_fathIndiv, upper_mothIndiv, v_Chromo_temp);

		////Step2：调用交叉函数对这两个父代的上层变量即v_chromosome1进行交叉，得到两个新的子代上层向量
		upper_crossover(upper_fathIndiv, upper_mothIndiv, upper_chIndiv1, upper_chIndiv2);

		////Step3：调用变异函数对随机一个子代上层向量进行变异
		int rand_number = rand() % 2;
		if (rand_number == 0)
		{
			upper_mutate(upper_chIndiv1, 0.95);
			OutT.v_chromosome1 = upper_chIndiv1.v_chromosome1;
		}
		else
		{
			upper_mutate(upper_chIndiv2, 0.95);
			OutT.v_chromosome1 = upper_chIndiv2.v_chromosome1;
		}

		vector <CIndividual> v_new_subChromo;
		vector <CIndividual>().swap(v_new_subChromo);
		////针对当前子种群中的每个个体，使用遗传算子，得到子代下层向量
		for (int j = 0; j < lower_number_of_individuals; j++)
		{
			CIndividual Inert;
			Inert.sub_no = i + 1;
			Inert.v_chromosome1 = OutT.v_chromosome1;

			////Step1:首先,利用二元锦标赛选择法选择两个父代
			//cout << "j = " << j + 1 << endl;
			CIndividual upper_lower_fathIndiv, upper_lower_mothIndiv, upper_lower_chIndiv1, upper_lower_chIndiv2;
			upper_select(upper_lower_fathIndiv, upper_lower_mothIndiv, v_Chromo_temp);
			//system("pause");

			////Step2：调用交叉函数对这两个父代的下层变量即v_chromosome2进行交叉，得到两个新的子代下层向量
			lower_crossover(upper_lower_fathIndiv, upper_lower_mothIndiv, upper_lower_chIndiv1, upper_lower_chIndiv2);

			////Step3：调用变异函数对随机一个子代下层向量进行变异
			int rand_number2 = rand() % 2;
			if (rand_number2 == 0)
			{
				lower_mutate(upper_lower_chIndiv1, 0.95);
				Inert.v_chromosome2 = upper_lower_chIndiv1.v_chromosome2;
			}
			else
			{
				lower_mutate(upper_lower_chIndiv2, 0.95);
				Inert.v_chromosome2 = upper_lower_chIndiv2.v_chromosome2;
			}
			//cout << "新个体：" << endl;
			//for (int m = 0; m < number_of_jobs * number_of_operations; m++)
			//{
			//	cout << Inert.v_chromosome1[m].operation_number << " ";
			//}
			//cout << endl;
			//for (int m = 0; m < number_of_jobs * number_of_operations; m++)
			//{
			//	cout << Inert.v_chromosome1[m].operation_index << " ";
			//}
			//cout << endl;
			//for (int m = number_of_jobs * number_of_operations; m < Inert.v_chromosome1.size(); m++)
			//{
			//	cout << Inert.v_chromosome1[m].machine_number << " ";
			//}
			//cout << endl;
			//for (int m = number_of_jobs * number_of_operations; m < Inert.v_chromosome1.size(); m++)
			//{
			//	cout << Inert.v_chromosome1[m].job_number << " ";
			//}
			//cout << endl;
			//for (int m = 0; m < Inert.v_chromosome2.size(); m++)
			//{
			//	cout << Inert.v_chromosome2[m].job_number << " ";
			//}
			//cout << endl;
			
			//S4ep4：评估获得的个体
			upper_evaluate(Inert, board_width, board_height, v_product);//求上层和下层目标函数值：先求下层目标值，然后基于下层约束求解上层目标值
			//system("pause");
			v_new_subChromo.push_back(Inert);
			v_new_TotalChromo.push_back(Inert);
		}
		v_new_Chromo.push_back(v_new_subChromo);
		//system("pause");
	}
	//cout << "上层遗传操作后的新种群：" << endl;
	//for (int m = 0; m < v_new_Chromo.size(); m++)
	//{
	//	cout << "sub_no = " << m + 1 << endl;
	//	for (int n = 0; n < v_new_Chromo[m].size(); n++)
	//	{
	//		cout << "iner = " << n + 1 << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_new_Chromo[m][n].v_chromosome1[u].operation_number << " ";
	//		}
	//		cout << endl;
	//		//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		//{
	//		//	cout << v_new_Chromo[m][n].v_chromosome1[u].operation_index << " ";
	//		//}
	//		//cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_new_Chromo[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_new_Chromo[m][n].v_chromosome1[u].machine_number << " ";
	//		}
	//		cout << endl;
	//		//for (int u = number_of_jobs * number_of_operations; u < v_new_Chromo[m][n].v_chromosome1.size(); u++)
	//		//{
	//		//	cout << v_new_Chromo[m][n].v_chromosome1[u].job_number << " ";
	//		//}
	//		//cout << endl;
	//		for (int u = 0; u < v_new_Chromo[m][n].v_chromosome2.size(); u++)
	//		{
	//			cout << v_new_Chromo[m][n].v_chromosome2[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_new_Chromo[m][n].v_ul_objectives.size(); u++)
	//		{
	//			for (int v = 0; v < v_new_Chromo[m][n].v_ul_objectives[u].size(); v++)
	//			{
	//				cout << v_new_Chromo[m][n].v_ul_objectives[u][v] << " ";
	//			}
	//		}
	//		cout << endl;
	//	}
	//	cout << endl << endl;
	//}
	//system("pause");
}
