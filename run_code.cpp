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
	//cout << "��ǰ��������Ϣ��" << endl;
	//cout << "���о��μ��ı�ţ�" << endl;
	//for (int i = 0; i < product_number.size(); i++)
	//{
	//	cout << product_number[i] << " ";
	//}
	//cout << endl;
	//cout << "���о��μ��ĳߴ磺" << endl;
	//for (int i = 0; i < product_scale.size(); i++)
	//{
	//	cout << "���μ�" << i + 1 << "�Ŀ���" << product_scale[i].first << " ";
	//	cout << "���μ�" << i + 1 << "�ĸ���" << product_scale[i].second << endl;
	//}
	//cout << "���о��μ����и�ʱ�䣺" << endl;
	//for (int i = 0; i < product_handle_time.size(); i++)
	//{
	//	cout << product_handle_time[i] << " ";
	//}
	//cout << endl;
	//cout << "���о��μ��Ķ����ţ�" << endl;
	//for (int i = 0; i < product_order.size(); i++)
	//{
	//	cout << product_order[i] << " ";
	//}
	//cout << endl;
	//system("pause");

	////����һ�������������о��μ�����֪����
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
	//cout << "���о��μ�����֪��Ϣ��" << endl;
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
	//cout << "ÿ��������������ҵ��" << endl;
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

	////�̳�ѵ���õ�Q��
	for (int ii = 0; ii < number_of_products; ii++)
	{
		vector<double> v;
		for (int jj = 0; jj < number_of_products; jj++)
		{
			v.push_back(input_Q_table_value[ii][jj]);
		}
		Qtable.push_back(v);
	}
	//cout << "��ǰ����ѵ���õ�Q��" << endl;
	//for (int ii = 0; ii < Qtable.size(); ii++)
	//{
	//	for (int jj = 0; jj < Qtable[ii].size(); jj++)
	//	{
	//		cout << std::fixed << std::setprecision(4) << Qtable[ii][jj] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	init_parameters();//��ʼ������ 
	generInitPopu(v_product);//��ʼ����Ⱥ(����������Ӧ�Ⱥ�����evaluate)   
	rank_up(v_TotalChromo);//��ȡ��ʼ��Ⱥ���ϲ���ֵ��ӵ���Ⱦ���  
	rank_low(v_Chromo);//��ȡÿ������Ⱥ���²���������ӵ���Ⱦ���
	update_subpop(v_TotalChromo, v_Chromo);
	outer_iteration_count = 0;
	double run_time = (double)(4000 * number_of_jobs * number_of_machines) / CLOCKS_PER_SEC;
	cout << "run_time = " << run_time << endl;
	double start_time = time(NULL);

	while (1)//outer_iteration_count < outer_iteration_count_max
	{
		//cout << "������ʼPt��Ⱥ��" << endl;
		//system("pause");
		//out_result(v_Chromo, v_TotalChromo);
		//system("pause");

		////Step1: �Ե�����ʼ��Ⱥv_TotalChromo/v_Chromo��ÿ������Ⱥ��ÿ����������²����������Ŵ��������õ�����Ⱥv_new_TotalChromo/v_new_Chromo
		genetic_operation(v_TotalChromo, v_Chromo, v_product);
		rank_up(v_new_TotalChromo);//��ȡ��Ⱥ�и�����ϲ���ֵ��ӵ���Ⱦ���
		rank_low(v_new_Chromo);//��ȡ��Ⱥ��ÿ������Ⱥ�и�����²���ֵ��ӵ���Ⱦ���
		update_subpop(v_new_TotalChromo, v_new_Chromo);//�������Ⱥv_new_TotalChromo/v_new_Chromo
		//cout << "�ϲ��Ż����new��Ⱥ��" << endl;
		//system("pause");
		//out_result(v_new_Chromo, v_new_TotalChromo);
		//system("pause");
	
		//////Step2: ����Qѧϰ��LS
		//if (outer_iteration_count < 1)
		//{
		//	paraller_search(v_new_Chromo, v_new_TotalChromo, v_product);//�õ�LS��Ⱥv_ls_TotalChromo, v_ls_Chromo
		//}
		//else
		//{
		//	adaptive_search(v_new_Chromo, v_new_TotalChromo, v_product);
		//}
		
		//////Step2:���²��Ż��������Ⱥִ��7�־ֲ��������õ�LS��Ⱥv_ls_TotalChromo, v_ls_Chromo
		vector <CIndividual> v_new_TotalChromo_temp(v_new_TotalChromo);//���������Ⱥv_new_TotalChromo/v_new_Chromo��ֵ����ʱ��Ⱥv_new_TotalChromo_temp/v_new_Chromo_temp
		vector <vector<CIndividual>> v_new_Chromo_temp(v_new_Chromo);
		local_search_IFCA(v_new_TotalChromo_temp, v_new_Chromo_temp, v_product);
		//cout << "�ֲ��������ls��Ⱥ��" << endl;
		//system("pause");
		//out_result(v_ls_Chromo, v_ls_TotalChromo);
		//system("pause");


		////Step3: ��LS��Ⱥv_ls_Chromo, v_ls_TotalChromo���и��£�����BLEMO���
		update_blemo_framework(v_ls_TotalChromo, v_ls_Chromo, v_product);
		//cout << "���º��ls��Ⱥ��" << endl;
		//system("pause");
		//out_result(v_ls_Chromo, v_ls_TotalChromo);
		//system("pause");
		
		////Step4: ��LS��Ⱥ��ÿ������Ⱥչ���²��Ż����õ������²��Ż�����Ⱥv_low_Chromo, v_low_TotalChromo
		vector <CIndividual> v_ls_TotalChromo_temp(v_ls_TotalChromo);//�����LS��Ⱥv_ls_TotalChromo/v_ls_Chromo��ֵ����ʱ��Ⱥv_ls_TotalChromo_temp/v_ls_Chromo_temp
		vector <vector<CIndividual>> v_ls_Chromo_temp(v_ls_Chromo);
		lowleveloptimization(v_ls_TotalChromo_temp, v_ls_Chromo_temp, v_product);
		//cout << "�²��Ż����Qt��Ⱥ��" << endl;
		//system("pause");
		//out_result(v_low_Chromo, v_low_TotalChromo);
		//system("pause");

		////Step5: �ϲ�Pt��Qt��ѡ����һ����Ⱥv_new_TotalChromo_temp, v_new_Chromo_temp������ֵ����һ����Ⱥv_TotalChromo/v_Chromo
		selection_next_pop(v_TotalChromo, v_Chromo, v_low_TotalChromo, v_low_Chromo, v_product);
		swap(v_TotalChromo, v_new_TotalChromo_temp);
		swap(v_Chromo, v_new_Chromo_temp);
		//cout << "��һ����Ⱥ:" << endl;
		//out_result(v_Chromo, v_TotalChromo);
		//system("pause");

		////Step6: ����ÿ�ε�����õ�NDu = 1��NDl = 1�ĸ��壬Ȼ��ÿ�ε����������������
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
		//cout << "���º��ⲿ�浵��" << endl;
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