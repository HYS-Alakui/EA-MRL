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
	//cout << "��������ʱ��Ⱥ��" << endl;
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

		////Step1:���ȣ����ÿ������Ⱥ�����ö�Ԫ������ѡ��ѡ����������
		CIndividual upper_fathIndiv, upper_mothIndiv, upper_chIndiv1, upper_chIndiv2;
		upper_select(upper_fathIndiv, upper_mothIndiv, v_Chromo_temp);

		////Step2�����ý��溯�����������������ϲ������v_chromosome1���н��棬�õ������µ��Ӵ��ϲ�����
		upper_crossover(upper_fathIndiv, upper_mothIndiv, upper_chIndiv1, upper_chIndiv2);

		////Step3�����ñ��캯�������һ���Ӵ��ϲ��������б���
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
		////��Ե�ǰ����Ⱥ�е�ÿ�����壬ʹ���Ŵ����ӣ��õ��Ӵ��²�����
		for (int j = 0; j < lower_number_of_individuals; j++)
		{
			CIndividual Inert;
			Inert.sub_no = i + 1;
			Inert.v_chromosome1 = OutT.v_chromosome1;

			////Step1:����,���ö�Ԫ������ѡ��ѡ����������
			//cout << "j = " << j + 1 << endl;
			CIndividual upper_lower_fathIndiv, upper_lower_mothIndiv, upper_lower_chIndiv1, upper_lower_chIndiv2;
			upper_select(upper_lower_fathIndiv, upper_lower_mothIndiv, v_Chromo_temp);
			//system("pause");

			////Step2�����ý��溯�����������������²������v_chromosome2���н��棬�õ������µ��Ӵ��²�����
			lower_crossover(upper_lower_fathIndiv, upper_lower_mothIndiv, upper_lower_chIndiv1, upper_lower_chIndiv2);

			////Step3�����ñ��캯�������һ���Ӵ��²��������б���
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
			//cout << "�¸��壺" << endl;
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
			
			//S4ep4��������õĸ���
			upper_evaluate(Inert, board_width, board_height, v_product);//���ϲ���²�Ŀ�꺯��ֵ�������²�Ŀ��ֵ��Ȼ������²�Լ������ϲ�Ŀ��ֵ
			//system("pause");
			v_new_subChromo.push_back(Inert);
			v_new_TotalChromo.push_back(Inert);
		}
		v_new_Chromo.push_back(v_new_subChromo);
		//system("pause");
	}
	//cout << "�ϲ��Ŵ������������Ⱥ��" << endl;
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
