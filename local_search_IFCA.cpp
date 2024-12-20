#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"
#include "Item.h"
#include <algorithm>
#include <map>

void QPacking::local_search_IFCA(vector<CIndividual>& v_new_TotalChromo_temp, vector <vector<CIndividual>>& v_new_Chromo_temp, vector<Item>& v_product)
{
	//cout << "local_searchǰ��" << endl;
	//out_result(v_new_Chromo_temp, v_new_TotalChromo_temp);

	/////�ֲ�����
	vector<vector<CIndividual>>().swap(v_ls_Chromo);
	vector<CIndividual>().swap(v_ls_TotalChromo);
	for (int i = 0; i < number_of_subpop; i++)
	{
		vector <CIndividual>().swap(v_ls_subChromo);
		for (int j = 0; j < lower_number_of_individuals; j++) //��ÿ������ִ�оֲ���������
		{
			CIndividual ls_indiv = v_new_Chromo_temp[i][j];
			int rand_action_num = rand()%7 + 1;
			//cout << "rand_action_num = " << rand_action_num << endl;
			ls_operation_individual(ls_indiv, v_product, rand_action_num); ////��ÿ������ִ�����ѡ��ľֲ���������
			upper_evaluate(ls_indiv, board_width, board_height, v_product);
			v_ls_subChromo.push_back(ls_indiv);
			v_ls_TotalChromo.push_back(ls_indiv);
		}
		v_ls_Chromo.push_back(v_ls_subChromo);
	}

	rank_up(v_ls_TotalChromo);//��ȡ��Ⱥ�и�����ϲ���ֵ��ӵ���Ⱦ���
	rank_low(v_ls_Chromo);//��ȡ��Ⱥ��ÿ������Ⱥ�и�����²���ֵ��ӵ���Ⱦ���
	update_subpop(v_ls_TotalChromo, v_ls_Chromo);//�������Ⱥv_new_TotalChromo/v_new_Chromo
	//system("pause");
	//cout << "local_search��" << endl;
	//out_result(v_ls_Chromo, v_ls_TotalChromo);
}