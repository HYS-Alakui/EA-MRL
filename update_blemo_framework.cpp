#include "Headfile.h"
#include "Qpacking.h"
#include "Item.h"
#include "Chromosome.h"
#include "Individual.h"
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

void QPacking::update_blemo_framework(vector <CIndividual>& v_ls_TotalChromo, vector <vector<CIndividual>>& v_ls_Chromo, vector<Item>& v_product)
{
	//cout << "����ǰ��" << endl;
	//out_result(v_ls_Chromo, v_ls_TotalChromo);
	//system("pause");

	////step1: ����һ����������ÿ������Ⱥ��upper_rank��С�Ľ�
	vector<CIndividual> v_rank_indiv;
	for (int m = 0; m < v_ls_Chromo.size(); m++)
	{
		vector<int> v_rank_value;
		for (int n = 0; n < v_ls_Chromo[m].size(); n++)
		{
			v_rank_value.push_back(v_ls_Chromo[m][n].upper_rank);		
		}	
		auto minIt = min_element(v_rank_value.begin(), v_rank_value.end());// ʹ��std::max_element�ҵ����Ԫ�صĵ�����	
		int minIndex = distance(v_rank_value.begin(), minIt);// �������ֵ������
		//cout << "��Сֵ: " << *minIt << std::endl;
		//cout << "��Ӧ������: " << minIndex << std::endl;

		CIndividual update_indiv = v_ls_Chromo[m][minIndex];
		v_rank_indiv.push_back(update_indiv);
	}

	////step2����ÿ������Ⱥ��upper_rank��С�Ľ���ϲ����������µ�ǰ����Ⱥÿ��������ϲ�����
	vector<CIndividual>().swap(v_ls_TotalChromo);
	for (int m = 0; m < v_ls_Chromo.size(); m++)
	{
		for (int n = 0; n < v_ls_Chromo[m].size(); n++)
		{
			v_ls_Chromo[m][n].v_chromosome1 = v_rank_indiv[m].v_chromosome1;
			upper_evaluate(v_ls_Chromo[m][n], board_width, board_height, v_product);
			v_ls_TotalChromo.push_back(v_ls_Chromo[m][n]);
		}
	}

	rank_up(v_ls_TotalChromo);//��ȡ��Ⱥ�и�����ϲ���ֵ��ӵ���Ⱦ���
	rank_low(v_ls_Chromo);//��ȡ��Ⱥ��ÿ������Ⱥ�и�����²���ֵ��ӵ���Ⱦ���
	update_subpop(v_ls_TotalChromo, v_ls_Chromo);//�������Ⱥv_new_TotalChromo/v_new_Chromo

	//cout << "���º�" << endl;
	//out_result(v_ls_Chromo, v_ls_TotalChromo);
	//system("pause");
}