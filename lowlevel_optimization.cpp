//#include "Headfile.h"
//#include "Qpacking.h"
//#include "Item.h"
//#include "Chromosome.h"
//#include "Individual.h"
//#include <set>
//#include <vector>
//#include <iostream>
//#include <algorithm>
//
//void QPacking::lowlevel_optimization(vector<CIndividual>& v_new_TotalChromo_temp, vector <vector<CIndividual>>& v_new_Chromo_temp, vector<Item>& v_product)
//{
//	//�²�����Ż�
//	//cout << "Before_v_new_TotalChromo_temp:" << endl;
//	//for (int m = 0; m < v_new_TotalChromo_temp.size(); m++)
//	//{
//	//	cout << "m = " << m + 1 << endl;
//	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
//	//	{
//	//		cout << v_new_TotalChromo_temp[m].v_chromosome1[n].operation_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
//	//	{
//	//		cout << v_new_TotalChromo_temp[m].v_chromosome1[n].operation_index << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = number_of_jobs * number_of_operations; n < v_new_TotalChromo_temp[m].v_chromosome1.size(); n++)
//	//	{
//	//		cout << v_new_TotalChromo_temp[m].v_chromosome1[n].machine_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = number_of_jobs * number_of_operations; n < v_new_TotalChromo_temp[m].v_chromosome1.size(); n++)
//	//	{
//	//		cout << v_new_TotalChromo_temp[m].v_chromosome1[n].job_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = 0; n < v_new_TotalChromo_temp[m].v_chromosome2.size(); n++)
//	//	{
//	//		cout << v_new_TotalChromo_temp[m].v_chromosome2[n].job_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = 0; n < v_new_TotalChromo_temp[m].v_ul_objectives.size(); n++)
//	//	{
//	//		for (int v = 0; v < v_new_TotalChromo_temp[m].v_ul_objectives[n].size(); v++)
//	//		{
//	//			cout << v_new_TotalChromo_temp[m].v_ul_objectives[n][v] << " ";
//	//		}
//	//	}
//	//	cout << endl;
//	//	cout << v_new_TotalChromo_temp[m].upper_rank << " " << v_new_TotalChromo_temp[m].upper_crowdedistance << endl;
//	//	cout << v_new_TotalChromo_temp[m].lower_rank << " " << v_new_TotalChromo_temp[m].lower_crowdedistance << endl;
//	//}
//	//system("pause");
//
//	//cout << "Before_v_new_Chromo_temp��" << endl;
//	//for (int m = 0; m < v_new_Chromo_temp.size(); m++)
//	//{
//	//	cout << "sub_no = " << m + 1 << endl;
//	//	for (int n = 0; n < v_new_Chromo_temp[m].size(); n++)
//	//	{
//	//		cout << "iner = " << n + 1 << endl;
//	//		cout << v_new_Chromo_temp[m][n].sub_no << endl;
//	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
//	//		{
//	//			cout << v_new_Chromo_temp[m][n].v_chromosome1[u].operation_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
//	//		{
//	//			cout << v_new_Chromo_temp[m][n].v_chromosome1[u].operation_index << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = number_of_jobs * number_of_operations; u < v_new_Chromo_temp[m][n].v_chromosome1.size(); u++)
//	//		{
//	//			cout << v_new_Chromo_temp[m][n].v_chromosome1[u].machine_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = number_of_jobs * number_of_operations; u < v_new_Chromo_temp[m][n].v_chromosome1.size(); u++)
//	//		{
//	//			cout << v_new_Chromo_temp[m][n].v_chromosome1[u].job_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < v_new_Chromo_temp[m][n].v_chromosome2.size(); u++)
//	//		{
//	//			cout << v_new_Chromo_temp[m][n].v_chromosome2[u].job_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < v_new_Chromo_temp[m][n].v_ul_objectives.size(); u++)
//	//		{
//	//			for (int v = 0; v < v_new_Chromo_temp[m][n].v_ul_objectives[u].size(); v++)
//	//			{
//	//				cout << v_new_Chromo_temp[m][n].v_ul_objectives[u][v] << " ";
//	//			}
//	//		}
//	//		cout << endl;
//	//		cout << v_new_Chromo_temp[m][n].upper_rank << ",  " << v_new_Chromo_temp[m][n].upper_crowdedistance << endl;
//	//		cout << v_new_Chromo_temp[m][n].lower_rank << ",  " << v_new_Chromo_temp[m][n].lower_crowdedistance << endl;
//	//	}
//	//	cout << endl << endl;
//	//}
//	//system("pause");
//
//	vector <vector<CIndividual>> v_low_Chromo;//�����������õ������Ӵ�����Ⱥ��ɵ��Ӵ���ȺQt
//	vector <CIndividual> v_low_TotalChromo;//�����������õ������Ӵ���ɵ��Ӵ���Ⱥ
//	
//	////Step1:���ÿ������Ⱥ����Tl�ε�����õ�������Ⱥv_low_subChromo�����v_low_Chromo��Qt
//	for (int i = 0; i < number_of_subpop; i++)
//	{
//		//cout << "number_of_subpop = " << i + 1 << endl;	
//		inter_iteration_count = 1;
//		vector<CIndividual> v_new_subChromo_temp;//��ǰ����Ⱥ���м�������ڵ�����������ÿ�ε�����õ�v_low_subChromo���ϸ���
//		
//		////Step1.1:����NDu = 1�ĸ����Ի�õ�ǰ����Ⱥ�ľ�Ӣ��
//		vector <CIndividual>().swap(v_elite_set);
//		for (int n = 0; n < v_new_Chromo_temp[i].size(); n++)
//		{
//			v_new_subChromo_temp.push_back(v_new_Chromo_temp[i][n]);
//			if (v_new_Chromo_temp[i][n].upper_rank == 1)
//			{
//				CIndividual indiv;
//				indiv = v_new_Chromo_temp[i][n];
//				v_elite_set.push_back(indiv);
//			}
//		}
//		//cout << "��ǰ����Ⱥ�ľ�Ӣ����" << endl;
//		//for (int m = 0; m < v_elite_set.size(); m++)
//		//{
//		//	cout << "m = " << m << endl;
//		//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
//		//	{
//		//		cout << v_elite_set[m].v_chromosome1[n].operation_number << " ";
//		//	}
//		//	cout << endl;
//		//	for (int n = number_of_jobs * number_of_operations; n < v_elite_set[m].v_chromosome1.size(); n++)
//		//	{
//		//		cout << v_elite_set[m].v_chromosome1[n].machine_number << " ";
//		//	}
//		//	cout << endl;
//		//	for (int n = 0; n < number_of_jobs; n++)
//		//	{
//		//		cout << v_elite_set[m].v_chromosome2[n].job_number << " ";
//		//	}
//		//	cout << endl;
//		//	cout << v_elite_set[m].upper_rank << endl;
//		//}
//		//system("pause");
//
//		////Step1.2:�����Ŵ�������ѭ��Tl�Σ���õ�ǰ����Ⱥ��������Ⱥ
//		vector <CIndividual> v_low_subChromo;
//		while (inter_iteration_count <= inter_iteration_count_max)
//		{
//			////�����Ŵ���������õ�������Ⱥ��������Ⱥ
//			vector <CIndividual>().swap(v_low_subChromo);
//			cout << "inter_iteration_count = " << inter_iteration_count << endl;
//			for (int j = 0; j < lower_number_of_individuals; j++)
//			{
//				//cout << "lower_number_of_individuals = " << j + 1 << endl;
//				CIndividual C1;
//				C1.v_chromosome1 = v_new_Chromo_temp[i][j].v_chromosome1;//��ÿ���²��Ż�ʱ���ϲ��������
//				//for (int m = 0; m < number_of_jobs * number_of_operations; m++)
//				//{
//				//	cout << C1.v_chromosome1[m].operation_number << " ";
//				//}
//				//cout << endl;
//				//for (int m = number_of_jobs * number_of_operations; m < C1.v_chromosome1.size(); m++)
//				//{
//				//	cout << C1.v_chromosome1[m].machine_number << " ";
//				//}
//				//cout << endl;
//				//system("pause");
//				
//				//cout << "������ǰ����Ⱥ��" << endl;
//				//for (int u = 0; u < v_new_subChromo_temp.size(); u++)
//				//{
//				//	cout << "u = " << u + 1 << endl;
//				//	for (int m = 0; m < number_of_jobs * number_of_operations; m++)
//				//	{
//				//		cout << v_new_subChromo_temp[u].v_chromosome1[m].operation_number << " ";
//				//	}
//				//	cout << endl;
//				//	for (int m = number_of_jobs * number_of_operations; m < v_new_subChromo_temp[u].v_chromosome1.size(); m++)
//				//	{
//				//		cout << v_new_subChromo_temp[u].v_chromosome1[m].machine_number << " ";
//				//	}
//				//	cout << endl;
//				//	for (int m = 0; m < v_new_subChromo_temp[u].v_chromosome2.size(); m++)
//				//	{
//				//		cout << v_new_subChromo_temp[u].v_chromosome2[m].job_number << " ";
//				//	}
//				//	cout << endl;	
//				//	cout << v_new_subChromo_temp[u].lower_rank << " "<< v_new_subChromo_temp[u].lower_crowdedistance<<endl;
//				//}
//				//system("pause");
//
//				////Step1.2.1������,���ö�Ԫ������ѡ�񷨴ӵ�ǰ����Ⱥ�����ϸ��£���ѡ��һ����������һ����������Ӹ�����Ⱥ�ľ�Ӣ����ѡ��			
//				CIndividual lower_fathIndiv, lower_mothIndiv, lower_chIndiv1, lower_chIndiv2;
//				lower_select(lower_fathIndiv, v_new_subChromo_temp);
//				//cout << "ѡ�еĸ���1��" << endl;
//				//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
//				//{
//				//	cout << lower_fathIndiv.v_chromosome1[u].operation_number << " ";
//				//}
//				//cout << endl;
//				//for (int u = number_of_jobs * number_of_operations; u < lower_fathIndiv.v_chromosome1.size(); u++)
//				//{
//				//	cout << lower_fathIndiv.v_chromosome1[u].machine_number << " ";
//				//}
//				//cout << endl;
//				//for (int u = 0; u < lower_fathIndiv.v_chromosome2.size(); u++)
//				//{
//				//	cout << lower_fathIndiv.v_chromosome2[u].job_number << " ";
//				//}
//				//cout << endl;
//				//system("pause");
//
//				if (v_elite_set.size() >= 1)
//				{
//					int rand_es_no = rand() % v_elite_set.size();
//					lower_mothIndiv = v_elite_set[rand_es_no];
//				}
//				else
//				{
//					lower_select(lower_mothIndiv, v_new_subChromo_temp);
//				}
//				//cout << "ѡ�еĸ���2��" << endl;
//				//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
//				//{
//				//	cout << lower_mothIndiv.v_chromosome1[u].operation_number << " ";
//				//}
//				//cout << endl;
//				//for (int u = number_of_jobs * number_of_operations; u < lower_mothIndiv.v_chromosome1.size(); u++)
//				//{
//				//	cout << lower_mothIndiv.v_chromosome1[u].machine_number << " ";
//				//}
//				//cout << endl;
//				//for (int u = 0; u < lower_mothIndiv.v_chromosome2.size(); u++)
//				//{
//				//	cout << lower_mothIndiv.v_chromosome2[u].job_number << " ";
//				//}
//				//cout << endl;
//				//system("pause");
//
//				////Step1.2.2����Σ����ý��溯�����������������²������v_chromosome2���н��棬�õ������µ��Ӵ��²�����
//				lower_crossover(lower_fathIndiv, lower_mothIndiv, lower_chIndiv1, lower_chIndiv2);
//				//system("pause");
//
//				////Step1.2.3�����ţ����ñ��캯�������һ���Ӵ��²��������б���
//				int rand_number2 = rand() % 2;
//				if (rand_number2 == 0)
//				{
//					lower_mutate(lower_chIndiv1, 0.95);
//					C1.v_chromosome2 = lower_chIndiv1.v_chromosome2;
//				}
//				else
//				{
//					lower_mutate(lower_chIndiv2, 0.95);
//					C1.v_chromosome2 = lower_chIndiv2.v_chromosome2;
//				}
//				//system("pause");
//
//				//cout << "�¸��壺" << endl;
//				//for (int m = 0; m < number_of_jobs * number_of_operations; m++)
//				//{
//				//	cout << C1.v_chromosome1[m].operation_number << " ";
//				//}
//				//cout << endl;
//				//for (int m = 0; m < number_of_jobs * number_of_operations; m++)
//				//{
//				//	cout << C1.v_chromosome1[m].operation_index << " ";
//				//}
//				//cout << endl;
//				//for (int m = number_of_jobs * number_of_operations; m < C1.v_chromosome1.size(); m++)
//				//{
//				//	cout << C1.v_chromosome1[m].machine_number << " ";
//				//}
//				//cout << endl;
//				//for (int m = number_of_jobs * number_of_operations; m < C1.v_chromosome1.size(); m++)
//				//{
//				//	cout << C1.v_chromosome1[m].job_number << " ";
//				//}
//				//cout << endl;
//				//for (int m = 0; m < C1.v_chromosome2.size(); m++)
//				//{
//				//	cout << C1.v_chromosome2[m].job_number << " ";
//				//}
//				//cout << endl;
//				//system("pause");
//
//				//Step1.2.4�����������õ����Ӵ����壬�������µ�����Ⱥ��
//				upper_evaluate(C1, board_width, board_height, v_product);//���ϲ���²�Ŀ�꺯��ֵ�������²�Ŀ��ֵ��Ȼ������²�Լ������ϲ�Ŀ��ֵ		
//				v_low_subChromo.push_back(C1);
//			}
//			
//			//Step1.3�����������Ⱥ���²���ֵ��ӵ���Ⱦ���ֵ
//			ranklow(v_low_subChromo);
//			//cout << "��ǰ����Ⱥ�ĵ���������Ⱥ��" << endl;
//			//for (int u = 0; u < v_low_subChromo.size(); u++)
//			//{
//			//	cout << "u = " << u + 1 << endl;
//			//	for (int m = 0; m < number_of_jobs * number_of_operations; m++)
//			//	{
//			//		cout << v_low_subChromo[u].v_chromosome1[m].operation_number << " ";
//			//	}
//			//	cout << endl;
//			//	for (int m = number_of_jobs * number_of_operations; m < v_low_subChromo[u].v_chromosome1.size(); m++)
//			//	{
//			//		cout << v_low_subChromo[u].v_chromosome1[m].machine_number << " ";
//			//	}
//			//	cout << endl;
//			//	for (int m = 0; m < v_low_subChromo[u].v_chromosome2.size(); m++)
//			//	{
//			//		cout << v_low_subChromo[u].v_chromosome2[m].job_number << " ";
//			//	}
//			//	cout << endl;
//			//	cout << v_low_subChromo[u].lower_rank << " " << v_low_subChromo[u].lower_crowdedistance << endl;
//			//}
//			//system("pause");
//			 
//			//Step1.4����������Ⱥ��ֵ��v_new_subChromo_temp��������һ�ε���
//			swap(v_new_subChromo_temp, v_low_subChromo);//����
//			inter_iteration_count++;
//			//system("pause");
//		}
//		v_low_Chromo.push_back(v_new_subChromo_temp);//��ÿ������Ⱥ����Tl�ε�����õ��µ�����Ⱥ�浽Qt��
//	}
//	for (int i = 0; i < v_low_Chromo.size(); i++)//����v_low_TotalChromo
//	{
//		for (int j = 0; j < v_low_Chromo[i].size(); j++)
//		{
//			v_low_TotalChromo.push_back(v_low_Chromo[i][j]);
//		}
//	}
//	//system("pause");
//	//cout << "���Qt��v_low_Chromo��" << endl;
//	//for (int m = 0; m < v_low_Chromo.size(); m++)
//	//{
//	//	cout << "sub_no = " << m + 1 << endl;
//	//	for (int n = 0; n < v_low_Chromo[m].size(); n++)
//	//	{
//	//		cout << "iner = " << n + 1 << endl;
//	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
//	//		{
//	//			cout << v_low_Chromo[m][n].v_chromosome1[u].operation_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
//	//		{
//	//			cout << v_low_Chromo[m][n].v_chromosome1[u].operation_index << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = number_of_jobs * number_of_operations; u < v_low_Chromo[m][n].v_chromosome1.size(); u++)
//	//		{
//	//			cout << v_low_Chromo[m][n].v_chromosome1[u].machine_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = number_of_jobs * number_of_operations; u < v_low_Chromo[m][n].v_chromosome1.size(); u++)
//	//		{
//	//			cout << v_low_Chromo[m][n].v_chromosome1[u].job_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < v_low_Chromo[m][n].v_chromosome2.size(); u++)
//	//		{
//	//			cout << v_low_Chromo[m][n].v_chromosome2[u].job_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < v_low_Chromo[m][n].v_ul_objectives.size(); u++)
//	//		{
//	//			for (int v = 0; v < v_low_Chromo[m][n].v_ul_objectives[u].size(); v++)
//	//			{
//	//				cout << v_low_Chromo[m][n].v_ul_objectives[u][v] << " ";
//	//			}
//	//		}
//	//		cout << endl;
//	//		//system("pause");
//	//	}
//	//	cout << endl << endl;
//	//}
//	//system("pause");
//	
//	////Step2:���Qt��Ⱥ�����²���ֵ��ӵ���Ⱦ���
//	rank_up(v_low_TotalChromo);//��ȡQt���ϲ���ֵ��ӵ���Ⱦ���
//	rank_low(v_low_Chromo);//���Qt��ÿ������Ⱥ���²���������ӵ���Ⱦ���
//	update_subpop(v_low_TotalChromo, v_low_Chromo);
//	//cout << "��� v_low_TotalChromoÿ����������²���ֵ��ӵ���Ⱦ���ֵ" << endl;
//	//for (int m = 0; m < v_low_TotalChromo.size(); m++)
//	//{
//	//	cout << "m = " << m + 1 << endl;
//	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
//	//	{
//	//		cout << v_low_TotalChromo[m].v_chromosome1[n].operation_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
//	//	{
//	//		cout << v_low_TotalChromo[m].v_chromosome1[n].operation_index << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = number_of_jobs * number_of_operations; n < v_low_TotalChromo[m].v_chromosome1.size(); n++)
//	//	{
//	//		cout << v_low_TotalChromo[m].v_chromosome1[n].machine_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = number_of_jobs * number_of_operations; n < v_low_TotalChromo[m].v_chromosome1.size(); n++)
//	//	{
//	//		cout << v_low_TotalChromo[m].v_chromosome1[n].job_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = 0; n < v_low_TotalChromo[m].v_chromosome2.size(); n++)
//	//	{
//	//		cout << v_low_TotalChromo[m].v_chromosome2[n].job_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = 0; n < v_low_TotalChromo[m].v_ul_objectives.size(); n++)
//	//	{
//	//		for (int v = 0; v < v_low_TotalChromo[m].v_ul_objectives[n].size(); v++)
//	//		{
//	//			cout << v_low_TotalChromo[m].v_ul_objectives[n][v] << " ";
//	//		}
//	//	}
//	//	cout << endl;
//	//	cout << v_low_TotalChromo[m].upper_rank << " "<< v_low_TotalChromo[m].upper_crowdedistance << endl;
//	//	cout << v_low_TotalChromo[m].lower_rank << " "<< v_low_TotalChromo[m].lower_crowdedistance <<endl;
//	//}
//	//system("pause");	
//	//cout << "���v_low_Chromoÿ����������²���ֵ��ӵ���Ⱦ���ֵ" << endl;
//	//for (int m = 0; m < v_low_Chromo.size(); m++)
//	//{
//	//	cout << "sub_no = " << m + 1 << endl;
//	//	for (int n = 0; n < v_low_Chromo[m].size(); n++)
//	//	{
//	//		cout << "iner = " << n + 1 << endl;
//	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
//	//		{
//	//			cout << v_low_Chromo[m][n].v_chromosome1[u].operation_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
//	//		{
//	//			cout << v_low_Chromo[m][n].v_chromosome1[u].operation_index << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = number_of_jobs * number_of_operations; u < v_low_Chromo[m][n].v_chromosome1.size(); u++)
//	//		{
//	//			cout << v_low_Chromo[m][n].v_chromosome1[u].machine_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = number_of_jobs * number_of_operations; u < v_low_Chromo[m][n].v_chromosome1.size(); u++)
//	//		{
//	//			cout << v_low_Chromo[m][n].v_chromosome1[u].job_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < v_low_Chromo[m][n].v_chromosome2.size(); u++)
//	//		{
//	//			cout << v_low_Chromo[m][n].v_chromosome2[u].job_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < v_low_Chromo[m][n].v_ul_objectives.size(); u++)
//	//		{
//	//			for (int v = 0; v < v_low_Chromo[m][n].v_ul_objectives[u].size(); v++)
//	//			{
//	//				cout << v_low_Chromo[m][n].v_ul_objectives[u][v] << " ";
//	//			}
//	//		}
//	//		cout << endl;
//	//		system("pause");
//	//		cout << v_low_Chromo[m][n].upper_rank << " " << v_low_Chromo[m][n].upper_crowdedistance << endl;
//	//		cout << v_low_Chromo[m][n].lower_rank << " " << v_low_Chromo[m][n].lower_crowdedistance << endl;
//	//		//system("pause");
//	//	}
//	//	cout << endl<<endl;
//	//}
//	//system("pause");
//
//	////Step3:�ϲ�Pt(v_new_TotalChromo_temp,v_new_Chromo_temp)��Qt(v_low_TotalChromo,v_low_Chromo)ΪRt
//	vector <CIndividual> v_merge_TotalChromo;
//	vector <CIndividual>().swap(v_merge_TotalChromo);
//	for (int m = 0; m < v_new_TotalChromo_temp.size(); m++)
//	{
//		v_merge_TotalChromo.push_back(v_new_TotalChromo_temp[m]);
//	}
//	for (int m = 0; m < v_low_TotalChromo.size(); m++)
//	{
//		v_merge_TotalChromo.push_back(v_low_TotalChromo[m]);
//	}
//	vector <vector<CIndividual>> v_merge_Chromo;
//	vector <vector<CIndividual>>().swap(v_merge_Chromo);
//	for (int m = 0; m < v_new_Chromo_temp.size(); m++)
//	{
//		v_merge_Chromo.push_back(v_new_Chromo_temp[m]);
//	}
//	for (int m = 0; m < v_low_Chromo.size(); m++)
//	{
//		v_merge_Chromo.push_back(v_low_Chromo[m]);
//	}
//
//	////Step4:���Rt��Ⱥ���ϲ���ֵ��ӵ���Ⱦ���ֵ�������Rt�и�������Ⱥ���²���ֵ��ӵ���Ⱦ���ֵ
//	rank_up(v_merge_TotalChromo);//��ȡ��ʼ��Ⱥ���ϲ���ֵ��ӵ���Ⱦ���
//	rank_low(v_merge_Chromo);//���ÿ������Ⱥ���²���������ӵ���Ⱦ���
//	update_subpop(v_merge_TotalChromo, v_merge_Chromo);
//	//cout << "Rank_After_v_merge_Chromo:" << endl;
//	//for (int m = 0; m < v_merge_Chromo.size(); m++)
//	//{
//	//	cout << "sub_no = " << m + 1 << endl;
//	//	for (int n = 0; n < v_merge_Chromo[m].size(); n++)
//	//	{
//	//		cout << "iner = " << n + 1 << endl;
//	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
//	//		{
//	//			cout << v_merge_Chromo[m][n].v_chromosome1[u].operation_number << " ";
//	//		}
//	//		cout << endl;
//	//		//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
//	//		//{
//	//		//	cout << v_merge_Chromo[m][n].v_chromosome1[u].operation_index << " ";
//	//		//}
//	//		//cout << endl;
//	//		for (int u = number_of_jobs * number_of_operations; u < v_merge_Chromo[m][n].v_chromosome1.size(); u++)
//	//		{
//	//			cout << v_merge_Chromo[m][n].v_chromosome1[u].machine_number << " ";
//	//		}
//	//		cout << endl;
//	//		//for (int u = number_of_jobs * number_of_operations; u < v_merge_Chromo[m][n].v_chromosome1.size(); u++)
//	//		//{
//	//		//	cout << v_merge_Chromo[m][n].v_chromosome1[u].job_number << " ";
//	//		//}
//	//		//cout << endl;
//	//		for (int u = 0; u < v_merge_Chromo[m][n].v_chromosome2.size(); u++)
//	//		{
//	//			cout << v_merge_Chromo[m][n].v_chromosome2[u].job_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < v_merge_Chromo[m][n].v_ul_objectives.size(); u++)
//	//		{
//	//			for (int v = 0; v < v_merge_Chromo[m][n].v_ul_objectives[u].size(); v++)
//	//			{
//	//				cout << v_merge_Chromo[m][n].v_ul_objectives[u][v] << " ";
//	//			}
//	//		}
//	//		cout << endl;
//	//		//system("pause");
//	//		cout << v_merge_Chromo[m][n].upper_rank << " " << v_merge_Chromo[m][n].upper_crowdedistance << endl;
//	//		cout << v_merge_Chromo[m][n].lower_rank << " " << v_merge_Chromo[m][n].lower_crowdedistance << endl;
//	//		//system("pause");
//	//	}
//	//	cout << endl << endl;
//	//}
//	//system("pause");
//
//	////Step5:ѡ����һ���²���Ⱥ
//	vector <vector<CIndividual>> v_next_Chromo;
//	vector <CIndividual> v_next_TotalChromo;
//	vector<int> v_save_subno;//�����ѽ�����һ����Ⱥ������Ⱥ���
//	int rank_value = 1;
//	int max_rank_value = 1;
//	for (int i = 0; i < v_merge_Chromo.size(); i++)
//	{
//		for (int j = 0; j < v_merge_Chromo[i].size(); j++)
//		{
//			if (v_merge_Chromo[i][j].upper_rank > max_rank_value)
//			{
//				max_rank_value = v_merge_Chromo[i][j].upper_rank;
//			}
//		}
//	}
//	//cout << "max_rank_value = " << max_rank_value << endl;
//	while (v_next_Chromo.size() < number_of_subpop || rank_value > max_rank_value)
//	{
//		//cout << "v_next_Chromo.size()  = " << v_next_Chromo.size() << endl;
//
//		////Step6.1: ���� NDu = rank_value ������Ⱥ
//		vector<int> v_subno_set;
//		for (int i = 0; i < v_merge_Chromo.size(); i++)
//		{
//			int sub_number = i + 1;
//			//cout << "sub_number = " << sub_number << endl;
//			for (int j = 0; j < v_merge_Chromo[i].size(); j++)
//			{
//				//cout << "v_merge_Chromo[i][j].upper_rank = " << v_merge_Chromo[i][j].upper_rank << endl;
//				if (v_merge_Chromo[i][j].upper_rank == rank_value)//����ǰ����Ⱥ��NDu = 1�ĸ��壬�Ǿͱ��������Ⱥ�ı��
//				{
//					v_subno_set.push_back(sub_number);
//					break;
//				}
//			}
//		}
//		//cout << "NDu = "<< rank_value <<" ������Ⱥ��ţ�" << endl;
//		//for (int i = 0; i < v_subno_set.size(); i++)
//		//{
//		//	cout << v_subno_set[i] << " ";
//		//}
//		//cout << endl;
//
//		////Step6.2:�ٻ�ȡ��Щ����Ⱥ�� NDu = rank_value �� NDl = 1 �ĸ���
//		vector<CIndividual> v_NDl_Indiv_set;
//		vector<double> v_NDl_updist;
//		vector<int> v_NDl_subno;
//		for (int i = 0; i < v_subno_set.size(); i++)
//		{
//			int sub_index = v_subno_set[i] - 1;
//			for (int j = 0; j < v_merge_Chromo[sub_index].size(); j++)
//			{
//				if (v_merge_Chromo[sub_index][j].upper_rank == rank_value && v_merge_Chromo[sub_index][j].lower_rank == 1)
//				{
//					v_NDl_Indiv_set.push_back(v_merge_Chromo[sub_index][j]);
//					v_NDl_updist.push_back(v_merge_Chromo[sub_index][j].upper_crowdedistance);
//					v_NDl_subno.push_back(sub_index + 1);
//				}
//			}
//		}
//		//cout << "NDu = " << rank_value << " �� NDl = 1�ĸ�����ϲ�ӵ���Ⱦ���CDu��" << endl;
//		//for (int i = 0; i < v_NDl_updist.size(); i++)
//		//{
//		//	cout << v_NDl_updist[i] << " ";
//		//}
//		//cout << endl;
//		//cout << "NDu = " << rank_value << " �� NDl = 1�ĸ��������Ⱥ���subno��" << endl;
//		//for (int i = 0; i < v_NDl_subno.size(); i++)
//		//{
//		//	cout << v_NDl_subno[i] << " ";
//		//}
//		//cout << endl;
//
//		////Step6.3:ɸѡ��ǰ���ܹ�������һ��������Ⱥ
//		if (v_NDl_subno.size() == 0)
//		{
//			//cout << "��ǰ����NDu=1��NDl=1�ĸ��壬�����һ�㣺 " << endl;
//		}
//		else if (v_NDl_subno.size() == 1)
//		{
//			int NDl_sub_no = v_NDl_subno[0];
//			if (v_save_subno.size() < 1)
//			{
//				//cout << "��ǰ����Ⱥ�ǵ�һ����ѡ�������Ⱥ" << endl;
//				v_next_Chromo.push_back(v_merge_Chromo[NDl_sub_no - 1]);
//				v_save_subno.push_back(NDl_sub_no);
//			}
//			else
//			{
//				//cout << "��鵱ǰ����Ⱥ�Ƿ��ѳ�����v_save_subno��" << endl;
//				int count = 0;
//				for (int i = 0; i < v_save_subno.size(); i++)
//				{
//					if (NDl_sub_no == v_save_subno[i])
//					{
//						//cout << NDl_sub_no <<"�ѳ��֣�������" << endl;
//						break;
//					}
//					else
//					{
//						count++;
//						//cout << "count_inner = " << count << endl;
//					}
//					//cout << "count_outer = " << count << endl;
//					if (count == v_save_subno.size())
//					{
//						if (v_save_subno.size() < number_of_subpop)
//						{
//							//cout << NDl_sub_no << "δ���֣����������Ⱥ��" << endl;
//							v_next_Chromo.push_back(v_merge_Chromo[NDl_sub_no - 1]);
//							v_save_subno.push_back(NDl_sub_no);
//						}
//					}
//				}
//			}
//
//		}
//		else if (v_NDl_subno.size() >= 2)
//		{
//			////Step6.3.1:�Ƚ� NDu = rank_value �� NDl = 1 �ĸ����CDuֵ����������Ⱥ��Ž�������
//			//cout << "����CDu����Щ����Ⱥ���н�������" << endl;
//			for (int i = 0; i <= v_NDl_updist.size() - 1 - 1; i++)
//			{
//				for (int j = i + 1; j <= v_NDl_updist.size() - 1; j++)
//				{
//					if (v_NDl_updist[i] < v_NDl_updist[j])
//					{
//						double dtemp1 = v_NDl_updist[i];
//						v_NDl_updist[i] = v_NDl_updist[j];
//						v_NDl_updist[j] = dtemp1;
//
//						double dtemp2 = v_NDl_subno[i];
//						v_NDl_subno[i] = v_NDl_subno[j];
//						v_NDl_subno[j] = dtemp2;
//					}
//				}
//			}
//			//cout << "�����NDu = " << rank_value << " �� NDl = 1�ĸ����ӵ���Ⱦ���CDu��" << endl;
//			//for (int i = 0; i < v_NDl_updist.size(); i++)
//			//{
//			//	cout << v_NDl_updist[i] << " ";
//			//}
//			//cout << endl;
//			//cout << "�����NDu = " << rank_value << " �� NDl = 1�ĸ��������Ⱥ���subno��" << endl;
//			//for (int i = 0; i < v_NDl_subno.size(); i++)
//			//{
//			//	cout << v_NDl_subno[i] << " ";
//			//}
//			//cout << endl;
//
//			////Step6.3.2:�Ƚ���Щ����Ⱥ�Ƿ���ֹ��������֣����ж���һ������Ⱥ����δ��������һ����Ⱥ��û���򱣴档
//			for (int i = 0; i < v_NDl_subno.size(); i++)
//			{
//				int NDl_sub_no = v_NDl_subno[i];
//				//cout << "NDl_sub_no = " << NDl_sub_no << endl;
//				//cout << "v_save_subno.size() = " << v_save_subno.size() << endl;
//				if (v_save_subno.size() < 1)
//				{
//					//cout << "��ǰ����Ⱥ�ǵ�һ����ѡ�������Ⱥ" << endl;
//					v_next_Chromo.push_back(v_merge_Chromo[NDl_sub_no - 1]);
//					v_save_subno.push_back(NDl_sub_no);
//				}
//				else
//				{
//					int count = 0;
//					for (int ii = 0; ii < v_save_subno.size(); ii++)
//					{
//						if (NDl_sub_no == v_save_subno[ii])
//						{
//							//cout << NDl_sub_no<< "�ѳ��֣��ж���һ������Ⱥ��" << endl;
//							break;
//						}
//						else
//						{
//							count++;
//							///cout << "inner_count == " << count << endl;
//						}
//					}
//					//cout << "outer_count == " << count << endl;
//					if (count == v_save_subno.size())//˵����ǰ����Ⱥδ����
//					{
//						if (v_save_subno.size() < number_of_subpop)
//						{
//							//cout << NDl_sub_no << "δ���֣����浱ǰ����Ⱥ��" << endl;
//							v_next_Chromo.push_back(v_merge_Chromo[NDl_sub_no - 1]);
//							v_save_subno.push_back(NDl_sub_no);
//						}
//					}
//				}
//
//
//				if (v_save_subno.size() >= number_of_subpop)
//				{
//					//cout << "��һ����Ⱥ��������������ж���һ������Ⱥ��������" << endl;
//					break;
//				}
//				//system("pause");
//			}
//		}
//
//		////Step6.4:�ж�ѡ����һ����Ⱥ��ֹͣ����
//		if (v_save_subno.size() < number_of_subpop)///ɸѡ��һ�㣡
//		{
//			rank_value++;
//			//cout << "next_rank_value = " << rank_value << endl;
//		}
//		else
//		{
//			//cout << "��ʱ����һ����Ⱥ������������" << endl;
//			break;
//		}
//	}
//	//cout << "���������Ⱥ��ţ�" << endl;
//	//for (int i = 0; i < v_save_subno.size(); i++)
//	//{
//	//	cout << v_save_subno[i] << " ";
//	//}
//	//cout << endl;
//	//system("pause");
//	if (v_next_Chromo.size() < number_of_subpop)
//	{
//		//cout << "ʣ�������Ⱥ���������" << endl;
//		for (int i = v_next_Chromo.size() - 1; i < number_of_subpop; i++)
//		{
//			//cout << "i = " << i + 1 << endl;
//			CIndividual T;
//			randomUpper(T);//��������ϲ�����
//			vector <CIndividual> v_subChromo;
//			vector <CIndividual>().swap(v_subChromo);
//			for (int j = 0; j < lower_number_of_individuals; j++)
//			{
//				//cout << "j = " << j+ 1<< endl;
//				CIndividual t;
//				t.sub_no = i + 1;
//				t.v_chromosome1 = T.v_chromosome1;
//				randomLower(t);//��������²�����
//				upper_evaluate(t, board_width, board_height, v_product);
//				v_subChromo.push_back(t);
//			}
//			v_next_Chromo.push_back(v_subChromo);
//		}
//	}
//	//cout << "�����õ�Next��Ⱥ" << endl;
//	//for (int i = 0; i < v_next_Chromo.size(); i++)
//	//{
//	//	cout << "subno = " << i + 1 << endl;
//	//	for (int j = 0; j < v_next_Chromo[i].size(); j++)
//	//	{
//	//		cout << v_next_Chromo[i][j].sub_no << endl;
//	//		for (int m = 0; m < number_of_jobs * number_of_operations; m++)
//	//		{
//	//			cout << v_next_Chromo[i][j].v_chromosome1[m].operation_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int m = number_of_jobs * number_of_operations; m < v_next_Chromo[i][j].v_chromosome1.size(); m++)
//	//		{
//	//			cout << v_next_Chromo[i][j].v_chromosome1[m].machine_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int m = 0; m < number_of_jobs; m++)
//	//		{
//	//			cout << v_next_Chromo[i][j].v_chromosome2[m].job_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < v_next_Chromo[i][j].v_ul_objectives.size(); u++)
//	//		{
//	//			for (int v = 0; v < v_next_Chromo[i][j].v_ul_objectives[u].size(); v++)
//	//			{
//	//				cout << v_next_Chromo[i][j].v_ul_objectives[u][v] << " ";
//	//			}
//	//		}
//	//		cout << endl;
//	//	}
//	//	cout << endl << endl;
//	//}
//	//system("pause");
//
//	////Step6:v_new_Chromo_temp�̳���һ����Ⱥv_next_Chromo��Ⱦɫ��������±�š���⡢������ֵ��ӵ���Ⱦ��룬ͬʱ����v_new_TotalChromo_temp
//	vector <vector<CIndividual>>().swap(v_new_Chromo_temp);
//	vector <CIndividual>().swap(v_new_TotalChromo_temp);
//	for (int i = 0; i < v_next_Chromo.size(); i++)
//	{
//		vector<CIndividual> v_new_subChromo_temp;
//		for (int j = 0; j < v_next_Chromo[i].size(); j++)
//		{
//			CIndividual next_t;
//			next_t.sub_no = i + 1;
//			next_t.v_chromosome1 = v_next_Chromo[i][j].v_chromosome1;
//			next_t.v_chromosome2 = v_next_Chromo[i][j].v_chromosome2;
//			upper_evaluate(next_t, board_width, board_height, v_product);
//			v_new_subChromo_temp.push_back(next_t);
//			v_new_TotalChromo_temp.push_back(next_t);
//		}
//		v_new_Chromo_temp.push_back(v_new_subChromo_temp);
//	}
//	rank_up(v_new_TotalChromo_temp);//��ȡ�²��Ż�����һ����Ⱥ���ϲ���ֵ��ӵ���Ⱦ���
//	rank_low(v_new_Chromo_temp);//����²��Ż�����һ����Ⱥ��ÿ������Ⱥ���²���������ӵ���Ⱦ���
//	update_subpop(v_new_TotalChromo_temp, v_new_Chromo_temp);//�²��Ż�����һ����Ⱥ��ÿ���ⶼ�����²���ֵ��ӵ���Ⱦ���
//
//	//�������²�����Ż����v_new_TotalChromo_temp, v_new_Chromo_temp���ϲ����һ����Ⱥ
//	//cout << "After_v_new_TotalChromo_temp:" << endl;
//	//for (int m = 0; m < v_new_TotalChromo_temp.size(); m++)
//	//{
//	//	cout << "m = " << m + 1 << endl;
//	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
//	//	{
//	//		cout << v_new_TotalChromo_temp[m].v_chromosome1[n].operation_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
//	//	{
//	//		cout << v_new_TotalChromo_temp[m].v_chromosome1[n].operation_index << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = number_of_jobs * number_of_operations; n < v_new_TotalChromo_temp[m].v_chromosome1.size(); n++)
//	//	{
//	//		cout << v_new_TotalChromo_temp[m].v_chromosome1[n].machine_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = number_of_jobs * number_of_operations; n < v_new_TotalChromo_temp[m].v_chromosome1.size(); n++)
//	//	{
//	//		cout << v_new_TotalChromo_temp[m].v_chromosome1[n].job_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = 0; n < v_new_TotalChromo_temp[m].v_chromosome2.size(); n++)
//	//	{
//	//		cout << v_new_TotalChromo_temp[m].v_chromosome2[n].job_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int n = 0; n < v_new_TotalChromo_temp[m].v_ul_objectives.size(); n++)
//	//	{
//	//		for (int v = 0; v < v_new_TotalChromo_temp[m].v_ul_objectives[n].size(); v++)
//	//		{
//	//			cout << v_new_TotalChromo_temp[m].v_ul_objectives[n][v] << " ";
//	//		}
//	//	}
//	//	cout << endl;
//	//	cout << v_new_TotalChromo_temp[m].upper_rank << " " << v_new_TotalChromo_temp[m].upper_crowdedistance << endl;
//	//	cout << v_new_TotalChromo_temp[m].lower_rank << " " << v_new_TotalChromo_temp[m].lower_crowdedistance << endl;
//	//}
//	//system("pause");
//
//	//cout << "After_v_new_Chromo_temp��" << endl;
//	//for (int m = 0; m < v_new_Chromo_temp.size(); m++)
//	//{
//	//	cout << "sub_no = " << m + 1 << endl;
//	//	for (int n = 0; n < v_new_Chromo_temp[m].size(); n++)
//	//	{
//	//		cout << "iner = " << n + 1 << endl;
//	//		cout << v_new_Chromo_temp[m][n].sub_no << endl;
//	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
//	//		{
//	//			cout << v_new_Chromo_temp[m][n].v_chromosome1[u].operation_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
//	//		{
//	//			cout << v_new_Chromo_temp[m][n].v_chromosome1[u].operation_index << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = number_of_jobs * number_of_operations; u < v_new_Chromo_temp[m][n].v_chromosome1.size(); u++)
//	//		{
//	//			cout << v_new_Chromo_temp[m][n].v_chromosome1[u].machine_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = number_of_jobs * number_of_operations; u < v_new_Chromo_temp[m][n].v_chromosome1.size(); u++)
//	//		{
//	//			cout << v_new_Chromo_temp[m][n].v_chromosome1[u].job_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < v_new_Chromo_temp[m][n].v_chromosome2.size(); u++)
//	//		{
//	//			cout << v_new_Chromo_temp[m][n].v_chromosome2[u].job_number << " ";
//	//		}
//	//		cout << endl;
//	//		for (int u = 0; u < v_new_Chromo_temp[m][n].v_ul_objectives.size(); u++)
//	//		{
//	//			for (int v = 0; v < v_new_Chromo_temp[m][n].v_ul_objectives[u].size(); v++)
//	//			{
//	//				cout << v_new_Chromo_temp[m][n].v_ul_objectives[u][v] << " ";
//	//			}
//	//		}
//	//		cout << endl;
//	//		cout << v_new_Chromo_temp[m][n].upper_rank << ",  " << v_new_Chromo_temp[m][n].upper_crowdedistance << endl;
//	//		cout << v_new_Chromo_temp[m][n].lower_rank << ",  " << v_new_Chromo_temp[m][n].lower_crowdedistance << endl;
//	//	}
//	//	cout << endl << endl;
//	//}
//	//system("pause");
//}