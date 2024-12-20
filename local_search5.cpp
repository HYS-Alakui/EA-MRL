#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"
#include "Item.h"
#include <algorithm>
#include <map>

void QPacking::local_search5(vector <vector<CIndividual>>& v_new_Chromo_temp5, vector<Item>& v_product)
{
	vector<vector<CIndividual>>().swap(v_ls_Chromo5);
	for (int i = 0; i < number_of_subpop; i++)
	{
		vector <CIndividual> v_ls_subChromo5;
		vector <CIndividual>().swap(v_ls_subChromo5);
		for (int j = 0; j < lower_number_of_individuals; j++) //对每个个体执行局部搜索操作
		{
			CIndividual ls_indiv5 = v_new_Chromo_temp5[i][j];
			ls_operation5(ls_indiv5, v_product); ////对每个个体执行局部搜索操作4
			v_ls_subChromo5.push_back(ls_indiv5);
		}
		v_ls_Chromo5.push_back(v_ls_subChromo5);
	}
}