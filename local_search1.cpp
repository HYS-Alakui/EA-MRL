#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"
#include "Item.h"
#include <algorithm>
#include <map>

void QPacking::local_search1(vector <vector<CIndividual>>& v_new_Chromo_temp1, vector<Item>& v_product)
{
	vector<vector<CIndividual>>().swap(v_ls_Chromo1);
	for (int i = 0; i < number_of_subpop; i++)
	{
		vector <CIndividual> v_ls_subChromo1;
		vector <CIndividual>().swap(v_ls_subChromo1);
		for (int j = 0; j < lower_number_of_individuals; j++) //��ÿ������ִ�оֲ���������
		{
			CIndividual ls_indiv1 = v_new_Chromo_temp1[i][j];
			ls_operation1(ls_indiv1, v_product); ////��ÿ������ִ�оֲ���������1�õ�ls_indiv
			v_ls_subChromo1.push_back(ls_indiv1);
		}
		v_ls_Chromo1.push_back(v_ls_subChromo1);
	}
}