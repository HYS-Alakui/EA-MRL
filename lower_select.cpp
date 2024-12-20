#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"


void QPacking::lower_select(CIndividual& lower_fathIndiv, vector<CIndividual> & v_new_subChromo_temp)
{
	int low_index1 = rand() % lower_number_of_individuals;
	//cout << "low_index1 = " << low_index1 << endl;
	int low_index2 = rand() % lower_number_of_individuals;	
	while (low_index1 == low_index2)
	{
		low_index2 = rand() % lower_number_of_individuals;
	}
	//cout << "low_index2 = " << low_index2 << endl;

	int l_rank1 = v_new_subChromo_temp[low_index1].lower_rank;
	//cout << "l_rank1 = " << l_rank1 << endl;
	int l_rank2 = v_new_subChromo_temp[low_index2].lower_rank;
	//cout << "l_rank2 = " << l_rank2 << endl;
	double l_dist1 = v_new_subChromo_temp[low_index1].lower_crowdedistance;
	//cout << "l_dist1 = " << l_dist1 << endl;
	double l_dist2 = v_new_subChromo_temp[low_index2].lower_crowdedistance;
	//cout << "l_dist2 = " << l_dist2 << endl;

	if (l_rank1 == l_rank2 && l_dist1 == l_dist2)
	{
		int rand_num = rand() % 2;
		if (rand_num == 0)
		{
			lower_fathIndiv = v_new_subChromo_temp[low_index1];
		}
		else
		{
			lower_fathIndiv = v_new_subChromo_temp[low_index2];
		}
	}
	else if ((l_rank1 == l_rank2 && l_dist1 > l_dist2) || (l_rank1 < l_rank2))
	{
		lower_fathIndiv = v_new_subChromo_temp[low_index1];
	}
	else
	{
		lower_fathIndiv = v_new_subChromo_temp[low_index2];
	}
}