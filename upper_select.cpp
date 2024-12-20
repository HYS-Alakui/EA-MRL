#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"


void QPacking::upper_select(CIndividual& upper_fathIndiv, CIndividual& upper_mothIndiv, vector <vector<CIndividual>>& v_Chromo_temp)
{
	int upper_parent_sub_no1, upper_parent_sub_no2;
	upper_parent_sub_no1 = rand() % number_of_subpop;
	//cout << "upper_parent_sub_no1 = " << upper_parent_sub_no1 << endl;
	upper_parent_sub_no2 = rand() % number_of_subpop;
	while (upper_parent_sub_no2 == upper_parent_sub_no1)
	{
		upper_parent_sub_no2 = rand() % number_of_subpop;
	}
	//cout << "upper_parent_sub_no2 = " << upper_parent_sub_no2 << endl;
	int low_index1 = rand() % lower_number_of_individuals;
	//cout << "low_index1 = " << low_index1 << endl;
	int low_index2 = rand() % lower_number_of_individuals;
	//cout << "low_index2 = " << low_index2 << endl;

	int u_rank1 = v_Chromo_temp[upper_parent_sub_no1][low_index1].upper_rank;
	//cout << "u_rank1 = " << u_rank1 << endl;
	int u_rank2 = v_Chromo_temp[upper_parent_sub_no2][low_index2].upper_rank;
	//cout << "u_rank2 = " << u_rank2 << endl;
	double u_dist1 = v_Chromo_temp[upper_parent_sub_no1][low_index1].upper_crowdedistance;
	//cout << "u_dist1 = " << u_dist1 << endl;
	double u_dist2 = v_Chromo_temp[upper_parent_sub_no2][low_index2].upper_crowdedistance;
	//cout << "u_dist2 = " << u_dist2 << endl;

	if (u_rank1 == u_rank2 && u_dist1 == u_dist2)
	{
		int rand_num = rand() % 2;
		if (rand_num == 0)
		{
			upper_fathIndiv = v_Chromo_temp[upper_parent_sub_no1][low_index1];
		}
		else
		{
			upper_fathIndiv = v_Chromo_temp[upper_parent_sub_no2][low_index2];
		}
	}
	else if ((u_rank1 == u_rank2 && u_dist1 > u_dist2) || (u_rank1 < u_rank2))
	{
		upper_fathIndiv = v_Chromo_temp[upper_parent_sub_no1][low_index1];
	}
	else
	{
		upper_fathIndiv = v_Chromo_temp[upper_parent_sub_no2][low_index2];
	}

	//cout << "选中的父代1：" << endl;
	//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//{
	//	cout << upper_fathIndiv.v_chromosome1[u].operation_number << " ";
	//}
	//cout << endl;
	//for (int u = number_of_jobs * number_of_operations; u < upper_fathIndiv.v_chromosome1.size(); u++)
	//{
	//	cout << upper_fathIndiv.v_chromosome1[u].machine_number << " ";
	//}
	//cout << endl;
	//for (int u = 0; u < upper_fathIndiv.v_chromosome2.size(); u++)
	//{
	//	cout << upper_fathIndiv.v_chromosome2[u].job_number << " ";
	//}
	//cout << endl;
	//system("pause");


	int upper_parent_sub_no3, upper_parent_sub_no4;
	upper_parent_sub_no3 = rand() % number_of_subpop;
	//cout << "upper_parent_sub_no3 = " << upper_parent_sub_no3 << endl;
	upper_parent_sub_no4 = rand() % number_of_subpop;
	while (upper_parent_sub_no4 == upper_parent_sub_no3)
	{
		upper_parent_sub_no4 = rand() % number_of_subpop;
	}
	//cout << "upper_parent_sub_no4 = " << upper_parent_sub_no4 << endl;
	int low_index3 = rand() % lower_number_of_individuals;
	//cout << "low_index3 = " << low_index3 << endl;
	int low_index4 = rand() % lower_number_of_individuals;
	//cout << "low_index4 = " << low_index4 << endl;

	int u_rank3 = v_Chromo_temp[upper_parent_sub_no3][low_index3].upper_rank;
	//cout << "u_rank3 = " << u_rank3 << endl;
	int u_rank4 = v_Chromo_temp[upper_parent_sub_no4][low_index4].upper_rank;
	//cout << "u_rank4 = " << u_rank4 << endl;
	double u_dist3 = v_Chromo_temp[upper_parent_sub_no3][low_index3].upper_crowdedistance;
	//cout << "u_dist3 = " << u_dist3 << endl;
	double u_dist4 = v_Chromo_temp[upper_parent_sub_no4][low_index4].upper_crowdedistance;
	//cout << "u_dist4 = " << u_dist4 << endl;
	if (u_rank3 == u_rank4 && u_dist3 == u_dist4)
	{
		int rand_num = rand() % 2;
		if (rand_num == 0)
		{
			upper_mothIndiv = v_Chromo_temp[upper_parent_sub_no3][low_index3];
		}
		else
		{
			upper_mothIndiv = v_Chromo_temp[upper_parent_sub_no4][low_index4];
		}
	}
	else if ((u_rank3 == u_rank4 && u_dist3 > u_dist4) || (u_rank3 < u_rank4))
	{
		upper_mothIndiv = v_Chromo_temp[upper_parent_sub_no3][low_index3];
	}
	else
	{
		upper_mothIndiv = v_Chromo_temp[upper_parent_sub_no4][low_index4];
	}

	//cout << "选中的父代2：" << endl;
	//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//{
	//	cout << upper_mothIndiv.v_chromosome1[u].operation_number << " ";
	//}
	//cout << endl;
	//for (int u = number_of_jobs * number_of_operations; u < upper_mothIndiv.v_chromosome1.size(); u++)
	//{
	//	cout << upper_mothIndiv.v_chromosome1[u].machine_number << " ";
	//}
	//cout << endl;
	//for (int u = 0; u < upper_mothIndiv.v_chromosome2.size(); u++)
	//{
	//	cout << upper_mothIndiv.v_chromosome2[u].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
}