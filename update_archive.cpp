#include "Qpacking.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"
#include <vector>
#include "RankSequ.h"
using namespace std;

void QPacking::update_archive(vector <CIndividual>& v_archive_set)
{
	//cout << "ÿ���ϲ������õ�NDu = 1 �� NDl = 1�ĸ���" << endl;
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
		int archive_size = v_archive.size();//��֧����Ⱥ�Ĵ�С
		if (archive_size == 0)//����֧�伯��=��
		{
			v_archive.push_back(v_archive_set[i]);//�ѵ�ǰNDu=1 && NDl = 1��Ⱥ�е�i�������� β�� ����֧�伯��
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
		//�������forѭ�����ų��˴���֧���ϵ�ĸ��壬Ҳ�����˴��� ��֧�����ͬ ��ϵ�ĸ���
		if (bt == false)//���ڷ�֧���ϵ��
		{
			v_archive.push_back(v_archive_set[i]);
		}
	}
}