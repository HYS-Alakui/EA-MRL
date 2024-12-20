#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"
#include "Item.h"
#include <algorithm>
#include <map>

void QPacking::local_search7(vector <vector<CIndividual>>& v_new_Chromo_temp7, vector<Item>& v_product)
{
	vector<vector<CIndividual>>().swap(v_ls_Chromo7);
	vector<CIndividual>().swap(v_ls_TotalChromo7);
	for (int i = 0; i < number_of_subpop; i++)
	{
		vector <CIndividual> v_ls_subChromo7;
		vector <CIndividual>().swap(v_ls_subChromo7);
		for (int j = 0; j < lower_number_of_individuals; j++) //对每个个体执行局部搜索操作
		{
			CIndividual ls_indiv7 = v_new_Chromo_temp7[i][j];
			ls_operation7(ls_indiv7, v_product); ////对每个个体执行局部搜索操作4
			v_ls_subChromo7.push_back(ls_indiv7);
		}
		v_ls_Chromo7.push_back(v_ls_subChromo7);
	}
}