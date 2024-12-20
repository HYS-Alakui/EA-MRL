#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"
#include "Item.h"
#include <algorithm>
#include <map>

void QPacking::local_search3(vector <vector<CIndividual>>& v_new_Chromo_temp3, vector<Item>& v_product)
{
	vector<vector<CIndividual>>().swap(v_ls_Chromo3);
	for (int i = 0; i < number_of_subpop; i++)
	{
		vector <CIndividual> v_ls_subChromo3;
		vector <CIndividual>().swap(v_ls_subChromo3);
		for (int j = 0; j < lower_number_of_individuals; j++) //对每个个体执行局部搜索操作
		{
			CIndividual ls_indiv3 = v_new_Chromo_temp3[i][j];
			ls_operation3(ls_indiv3, v_product); ////对每个个体执行局部搜索操作3
			v_ls_subChromo3.push_back(ls_indiv3);
		}
		v_ls_Chromo3.push_back(v_ls_subChromo3);
	}
}