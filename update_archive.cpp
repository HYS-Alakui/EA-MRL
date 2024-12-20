#include "Qpacking.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"
#include <vector>
#include "RankSequ.h"
using namespace std;

void QPacking::update_archive(vector <CIndividual>& v_archive_set)
{
	//cout << "每次上层迭代获得的NDu = 1 且 NDl = 1的个体" << endl;
	//for (int m = 0; m < v_archive_set.size(); m++)
	//{
	//	cout << "m = " << m << endl;
	//	for (int n = 0; n < number_of_jobs * number_of_operations; n++)
	//	{
	//		cout << v_archive_set[m].v_chromosome1[n].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = number_of_jobs * number_of_operations; n < v_archive_set[m].v_chromosome1.size(); n++)
	//	{
	//		cout << v_archive_set[m].v_chromosome1[n].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < number_of_jobs; n++)
	//	{
	//		cout << v_archive_set[m].v_chromosome2[n].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int n = 0; n < v_archive_set[m].v_ul_objectives.size(); n++)
	//	{
	//		for (int h = 0; h < v_archive_set[m].v_ul_objectives[n].size(); h++)
	//		{
	//			cout << v_archive_set[m].v_ul_objectives[n][h] << " ";
	//		}
	//	}
	//	cout << endl;
	//	cout << v_archive_set[m].upper_rank << endl;
	//	cout << v_archive_set[m].lower_rank << endl;
	//}

	int domRel;
	bool bt;
	for (int i = 0; i < v_archive_set.size(); i++)
	{
		int archive_size = v_archive.size();//非支配种群的大小
		if (archive_size == 0)//若非支配集合=空
		{
			v_archive.push_back(v_archive_set[i]);//把当前NDu=1 && NDl = 1种群中第i个个对象 尾插 到非支配集合
			continue;
		}
		bt = false;
		for (int j = archive_size - 1; j >= 0; j--)
		{
			domRelation_up(v_archive_set[i], v_archive[j], domRel); 
			if (domRel == 1)
			{
				v_archive.erase(v_archive.begin() + j);
			}
			else if (domRel == -1 || domRel == 0)
			{
				bt = true;
				break;  
			}
		}
		//上面这个for循环，排除了存在支配关系的个体，也跳过了存在 被支配和相同 关系的个体
		if (bt == false)//存在非支配关系，
		{
			v_archive.push_back(v_archive_set[i]);
		}
	}
}