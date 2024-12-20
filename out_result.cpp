#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"
#include "Item.h"
#include <algorithm>
#include <map>

void QPacking::out_result(vector <vector<CIndividual>>& V_Chromo, vector<CIndividual>& V_TotalChromo)
{
	for (int m = 0; m < V_Chromo.size(); m++)
	{
		cout << "sub_no = " << m + 1 << endl;
		for (int n = 0; n < V_Chromo[m].size(); n++)
		{
			cout << "iner = " << n + 1 << endl;
			for (int u = 0; u < number_of_jobs * number_of_operations; u++)
			{
				cout << V_Chromo[m][n].v_chromosome1[u].operation_number << " ";
			}
			cout << endl;
			for (int u = 0; u < number_of_jobs * number_of_operations; u++)
			{
				cout << V_Chromo[m][n].v_chromosome1[u].operation_index << " ";
			}
			cout << endl;
			for (int u = number_of_jobs * number_of_operations; u < V_Chromo[m][n].v_chromosome1.size(); u++)
			{
				cout << V_Chromo[m][n].v_chromosome1[u].machine_number << " ";
			}
			cout << endl;
			for (int u = number_of_jobs * number_of_operations; u < V_Chromo[m][n].v_chromosome1.size(); u++)
			{
				cout << V_Chromo[m][n].v_chromosome1[u].job_number << " ";
			}
			cout << endl;
			for (int u = 0; u < V_Chromo[m][n].v_chromosome2.size(); u++)
			{
				cout << V_Chromo[m][n].v_chromosome2[u].job_number << " ";
			}
			cout << endl;
			for (int u = 0; u < V_Chromo[m][n].v_ul_objectives.size(); u++)
			{
				for (int v = 0; v < V_Chromo[m][n].v_ul_objectives[u].size(); v++)
				{
					cout << V_Chromo[m][n].v_ul_objectives[u][v] << " ";
				}
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	system("pause");

	//for (int i = 0; i < V_TotalChromo.size(); i++)
	//{
	//	cout << "i = " << i << endl;
	//	for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	//	{
	//		cout << V_TotalChromo[i].v_chromosome1[j].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs * number_of_operations; j < V_TotalChromo[i].v_chromosome1.size(); j++)
	//	{
	//		cout << V_TotalChromo[i].v_chromosome1[j].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < V_TotalChromo[i].v_chromosome2.size(); j++)
	//	{
	//		cout << V_TotalChromo[i].v_chromosome2[j].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < V_TotalChromo[i].v_ul_objectives.size(); j++)
	//	{
	//		for (int h = 0; h < V_TotalChromo[i].v_ul_objectives[j].size(); h++)
	//		{
	//			cout << V_TotalChromo[i].v_ul_objectives[j][h] << " ";
	//		}
	//	}
	//	cout << endl;
	//}
}
