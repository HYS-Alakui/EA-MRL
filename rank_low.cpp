#include "Qpacking.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"
#include <vector>
#include "RankSequ.h"
using namespace std;

void QPacking::rank_low(vector <vector<CIndividual>>& v_Chromo)
{
	for (int ch = 0; ch < v_Chromo.size(); ch++)
	{
		//cout << "------------3、下层非支配分层---------" << endl;
		int i, j;
		int domRel, rankLevel, size, sizeZero, domChromoNo, domedChromoNo;
		double objValue;
		bool bt;
		vector <int> v_low_domZero;//储存被支配次数为0的个体（不是单指第一层，有可能是后面新一批的下一层）
		for (i = 0; i < v_Chromo[ch].size(); i++)//初始化
		{
			v_Chromo[ch][i].lower_domination_count = 0;
			v_Chromo[ch][i].v_lower_dominationSet.resize(0);
			v_Chromo[ch][i].lower_rank = 0;
		}

		for (i = 0; i < v_Chromo[ch].size() - 1; i++)//此过程获取当前子种群中每个 对象的 被支配次数 和 支配其他个体的集合
		{
			for (int j = i + 1; j < v_Chromo[ch].size(); j++)
			{
				domRel = 3;
				domRelation_low(v_Chromo[ch][i], v_Chromo[ch][j], domRel);
				if (domRel == 1)//前者优于后者      函数值=1，表示支配；
				{
					v_Chromo[ch][j].lower_domination_count++;
					v_Chromo[ch][i].v_lower_dominationSet.push_back(j);
				}
				else if (domRel == -1)///前者差于后者    函数值=-1，表示被支配
				{
					v_Chromo[ch][i].lower_domination_count++;
					v_Chromo[ch][j].v_lower_dominationSet.push_back(i);
				}
			}
		}

		vector <CRankSequ>().swap(v_lower_rankSequ); //此过程获取种群中每个 对象的 lower_rank，lower_domination_count，v_lower_dominationSet
		rankLevel = 1;
		while (1)
		{
			bt = false;
			v_low_domZero.resize(0);
			for (i = 0; i < v_Chromo[ch].size(); i++)
			{
				if (v_Chromo[ch][i].lower_domination_count == 0)
				{
					CRankSequ t;
					v_Chromo[ch][i].lower_rank = rankLevel;
					t.chromoNo = i;
					t.rankSequ = rankLevel;
					for (j = 0; j < number_of_objectives; j++)
					{
						objValue = v_Chromo[ch][i].v_ul_objectives[1][j];
						t.v_rObjValue.push_back(objValue);
					}
					v_lower_rankSequ.push_back(t);
					bt = true;
					v_low_domZero.push_back(i);
				}
			}
			if (bt == false)
			{
				break;
			}
			if (bt == true)
			{
				rankLevel++;
				sizeZero = v_low_domZero.size();
				for (int j = 0; j < sizeZero; j++)
				{
					domChromoNo = v_low_domZero[j];
					v_Chromo[ch][domChromoNo].lower_domination_count = -1;
					size = v_Chromo[ch][domChromoNo].v_lower_dominationSet.size();
					for (int k = 0; k < size; k++)
					{
						domedChromoNo = v_Chromo[ch][domChromoNo].v_lower_dominationSet[k];
						v_Chromo[ch][domedChromoNo].lower_domination_count--;
					}
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//cout << "每个个体的lower_rank值（NDl）：" << endl;
		//for (int m = 0; m < v_Chromo[ch].size(); m++)
		//{
		//	cout << "m = "<< m << ", " << v_Chromo[ch][m].lower_rank << endl;
		//}
		//cout << endl;
		//////输出v_rankSequ容器，对象属性包括:chromoNo个体号；rankSequ序值；拥挤度距离和目标值
		//cout << "v_rankSequ容器：" << endl;
		//for (int cn = 0; cn < v_lower_rankSequ.size(); cn++)
		//{
		//	cout << v_lower_rankSequ[cn].chromoNo << " ";
		//	cout << v_lower_rankSequ[cn].rankSequ << endl;
		//}
		//cout << endl;

		//首先需要获取一共有多少个簇，找出最大的rankSequ即可	
		int cluster_number = v_lower_rankSequ[v_Chromo[ch].size() - 1].rankSequ;
		int num_c = 0;
		vector <vector<CRankSequ>>().swap(v_lower_cluster);//清空容器,初始化
		for (int cn = 1; cn <= cluster_number; cn++)
		{
			vector <CRankSequ> v;
			v_lower_cluster.push_back(v);

			for (int i = num_c; i < v_lower_rankSequ.size(); i++)
			{
				if (v_lower_rankSequ[i].rankSequ == cn)
				{
					CRankSequ clu;
					clu.chromoNo = v_lower_rankSequ[i].chromoNo;//获取作业号
					clu.rankSequ = v_lower_rankSequ[i].rankSequ;//获取rank值
					clu.v_rObjValue = v_lower_rankSequ[i].v_rObjValue;//获取上层目标值
					v_lower_cluster[cn - 1].push_back(clu);//将该对象放入当前簇列表
					num_c++;
				}
				else
				{
					break;
				}
			}
		}
		//cout<<"每层包含的个体及其簇号和目标值"<<endl;
		//for (int i = 0; i < v_lower_cluster.size(); i++)
		//{
		//	for (int j = 0; j < v_lower_cluster[i].size(); j++)
		//	{
		//		cout << v_lower_cluster[i][j].chromoNo << " ";
		//	}
		//	cout << endl;
		//	for (int j = 0; j < v_lower_cluster[i].size(); j++)
		//	{
		//		cout << v_lower_cluster[i][j].rankSequ << " ";
		//	}
		//	cout << endl;
		//	for (int j = 0; j < v_lower_cluster[i].size(); j++)
		//	{
		//		for (int k = 0; k < v_lower_cluster[i][j].v_rObjValue.size(); k++)
		//		{
		//			cout << v_lower_cluster[i][j].v_rObjValue[k] << " ";
		//		}
		//		cout << endl;
		//	}
		//	cout << endl;
		//}
		//system("pause");

		for (int m = 0; m < v_lower_cluster.size(); m++)
		{
			int start = 0;
			//cout << "start = " << start << endl;
			int end = v_lower_cluster[m].size() - 1;
			//cout << "end = " <<end << endl;
			crodiversity(v_lower_cluster[m], start, end);//求每层个体的拥挤度距离
			//system("pause");

			int chr_no;
			double cro_dis;
			for (int n = 0; n < v_lower_cluster[m].size(); n++)//获取v_Chromo[ch]中相应个体的拥挤度
			{
				//cout << v_lower_cluster[m][n].croDiversity << " ";
				cro_dis = v_lower_cluster[m][n].croDiversity;
				//cout << v_lower_cluster[m][n].chromoNo << " ";
				chr_no = v_lower_cluster[m][n].chromoNo;
				v_Chromo[ch][chr_no].lower_crowdedistance = cro_dis;
			}
			//cout << endl;

			//for (int n = 0; n < v_lower_cluster[m].size(); n++)
			//{
			//	cout << v_lower_cluster[m][n].rankSequ << " ";
			//}
			//cout << endl;
			//for (int n = 0; n < v_lower_cluster[m].size(); n++)
			//{
			//	for (int k = 0; k < v_lower_cluster[m][n].v_rObjValue.size(); k++)
			//	{
			//		cout << v_lower_cluster[m][n].v_rObjValue[k] << " ";
			//	}
			//	cout << endl;
			//}
			//cout << endl;
			//system("pause");
		}

		//cout << "每个个体的lower_crowdedistance值（CDl）：" << endl;
		//for (int m = 0; m < v_Chromo[ch].size(); m++)
		//{
		//	cout << "m = " << m << ", " << v_Chromo[ch][m].lower_crowdedistance << endl;
		//}
		//system("pause");
	}


}

void QPacking::ranklow(vector<CIndividual>& v_low_subChromo)
{
	//cout << "------------3、下层非支配分层---------" << endl;
	int i, j;
	int domRel, rankLevel, size, sizeZero, domChromoNo, domedChromoNo;
	double objValue;
	bool bt;
	vector <int> v_low_domZero;//储存被支配次数为0的个体（不是单指第一层，有可能是后面新一批的下一层）
	for (i = 0; i < v_low_subChromo.size(); i++)//初始化
	{
		v_low_subChromo[i].lower_domination_count = 0;
		v_low_subChromo[i].v_lower_dominationSet.resize(0);
		v_low_subChromo[i].lower_rank = 0;
	}

	for (i = 0; i < v_low_subChromo.size() - 1; i++)//此过程获取当前子种群中每个 对象的 被支配次数 和 支配其他个体的集合
	{
		for (int j = i + 1; j < v_low_subChromo.size(); j++)
		{
			domRel = 3;
			domRelation_low(v_low_subChromo[i], v_low_subChromo[j], domRel);
			if (domRel == 1)//前者优于后者      函数值=1，表示支配；
			{
				v_low_subChromo[j].lower_domination_count++;
				v_low_subChromo[i].v_lower_dominationSet.push_back(j);
			}
			else if (domRel == -1)///前者差于后者    函数值=-1，表示被支配
			{
				v_low_subChromo[i].lower_domination_count++;
				v_low_subChromo[j].v_lower_dominationSet.push_back(i);
			}
		}
	}

	vector <CRankSequ>().swap(v_lower_rankSequ); //此过程获取种群中每个 对象的 lower_rank，lower_domination_count，v_lower_dominationSet
	rankLevel = 1;
	while (1)
	{
		bt = false;
		v_low_domZero.resize(0);
		for (i = 0; i < v_low_subChromo.size(); i++)
		{
			if (v_low_subChromo[i].lower_domination_count == 0)
			{
				CRankSequ t;
				v_low_subChromo[i].lower_rank = rankLevel;
				t.chromoNo = i;
				t.rankSequ = rankLevel;
				for (j = 0; j < number_of_objectives; j++)
				{
					objValue = v_low_subChromo[i].v_ul_objectives[1][j];
					t.v_rObjValue.push_back(objValue);
				}
				v_lower_rankSequ.push_back(t);
				bt = true;
				v_low_domZero.push_back(i);
			}
		}
		if (bt == false)
		{
			break;
		}
		if (bt == true)
		{
			rankLevel++;
			sizeZero = v_low_domZero.size();
			for (int j = 0; j < sizeZero; j++)
			{
				domChromoNo = v_low_domZero[j];
				v_low_subChromo[domChromoNo].lower_domination_count = -1;
				size = v_low_subChromo[domChromoNo].v_lower_dominationSet.size();
				for (int k = 0; k < size; k++)
				{
					domedChromoNo = v_low_subChromo[domChromoNo].v_lower_dominationSet[k];
					v_low_subChromo[domedChromoNo].lower_domination_count--;
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//cout << "每个个体的lower_rank值（NDl）：" << endl;
	//for (int m = 0; m < v_low_subChromo.size(); m++)
	//{
	//	cout << "m = "<< m << ", " << v_low_subChromo[m].lower_rank << endl;
	//}
	//cout << endl;
	//////输出v_rankSequ容器，对象属性包括:chromoNo个体号；rankSequ序值；拥挤度距离和目标值
	//cout << "v_rankSequ容器：" << endl;
	//for (int cn = 0; cn < v_lower_rankSequ.size(); cn++)
	//{
	//	cout << v_lower_rankSequ[cn].chromoNo << " ";
	//	cout << v_lower_rankSequ[cn].rankSequ << endl;
	//}
	//cout << endl;

	//首先需要获取一共有多少个簇，找出最大的rankSequ即可	
	int cluster_number = v_lower_rankSequ[v_low_subChromo.size() - 1].rankSequ;
	int num_c = 0;
	vector <vector<CRankSequ>>().swap(v_lower_cluster);//清空容器,初始化
	for (int cn = 1; cn <= cluster_number; cn++)
	{
		vector <CRankSequ> v;
		v_lower_cluster.push_back(v);

		for (int i = num_c; i < v_lower_rankSequ.size(); i++)
		{
			if (v_lower_rankSequ[i].rankSequ == cn)
			{
				CRankSequ clu;
				clu.chromoNo = v_lower_rankSequ[i].chromoNo;//获取作业号
				clu.rankSequ = v_lower_rankSequ[i].rankSequ;//获取rank值
				clu.v_rObjValue = v_lower_rankSequ[i].v_rObjValue;//获取上层目标值
				v_lower_cluster[cn - 1].push_back(clu);//将该对象放入当前簇列表
				num_c++;
			}
			else
			{
				break;
			}
		}
	}
	//cout<<"每层包含的个体及其簇号和目标值"<<endl;
	//for (int i = 0; i < v_lower_cluster.size(); i++)
	//{
	//	for (int j = 0; j < v_lower_cluster[i].size(); j++)
	//	{
	//		cout << v_lower_cluster[i][j].chromoNo << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < v_lower_cluster[i].size(); j++)
	//	{
	//		cout << v_lower_cluster[i][j].rankSequ << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < v_lower_cluster[i].size(); j++)
	//	{
	//		for (int k = 0; k < v_lower_cluster[i][j].v_rObjValue.size(); k++)
	//		{
	//			cout << v_lower_cluster[i][j].v_rObjValue[k] << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
	//system("pause");

	for (int m = 0; m < v_lower_cluster.size(); m++)
	{
		int start = 0;
		//cout << "start = " << start << endl;
		int end = v_lower_cluster[m].size() - 1;
		//cout << "end = " <<end << endl;
		crodiversity(v_lower_cluster[m], start, end);//求每层个体的拥挤度距离
		//system("pause");

		int chr_no;
		double cro_dis;
		for (int n = 0; n < v_lower_cluster[m].size(); n++)//获取v_low_subChromo中相应个体的拥挤度
		{
			//cout << v_lower_cluster[m][n].croDiversity << " ";
			cro_dis = v_lower_cluster[m][n].croDiversity;
			//cout << v_lower_cluster[m][n].chromoNo << " ";
			chr_no = v_lower_cluster[m][n].chromoNo;
			v_low_subChromo[chr_no].lower_crowdedistance = cro_dis;
		}
		//cout << endl;

		//for (int n = 0; n < v_lower_cluster[m].size(); n++)
		//{
		//	cout << v_lower_cluster[m][n].rankSequ << " ";
		//}
		//cout << endl;
		//for (int n = 0; n < v_lower_cluster[m].size(); n++)
		//{
		//	for (int k = 0; k < v_lower_cluster[m][n].v_rObjValue.size(); k++)
		//	{
		//		cout << v_lower_cluster[m][n].v_rObjValue[k] << " ";
		//	}
		//	cout << endl;
		//}
		//cout << endl;
		//system("pause");
	}

	//cout << "每个个体的lower_crowdedistance值（CDl）：" << endl;
	//for (int m = 0; m < v_low_subChromo.size(); m++)
	//{
	//	cout << "m = " << m << ", " << v_low_subChromo[m].lower_crowdedistance << endl;
	//}
	//system("pause");

}

void QPacking::domRelation_low(const CIndividual& A, const CIndividual& B, int& domRel)
{
	int i;
	int equalCount, lessCount, greaterCount;
	equalCount = 0;
	lessCount = 0;
	greaterCount = 0;
	for (i = 0; i < number_of_objectives; i++)
	{
		if (A.v_ul_objectives[1][i] == B.v_ul_objectives[1][i])
		{
			equalCount++;//若两个对象的目标值相等，则相等次数++
		}
		if (A.v_ul_objectives[1][i] < B.v_ul_objectives[1][i])
		{
			lessCount++;//若A对象的目标值<B对象的目标值，则less次数++
		}
		if (A.v_ul_objectives[1][i] > B.v_ul_objectives[1][i])
		{
			greaterCount++;//若A对象的目标值>B对象的目标值，则greater次数++
		}
	}
	if (equalCount == number_of_objectives)
	{
		domRel = 0;
	}
	else if ((equalCount + lessCount == number_of_objectives) && lessCount > 0)
	{
		domRel = 1;
	}
	else if ((equalCount + greaterCount == number_of_objectives) && greaterCount > 0)
	{
		domRel = -1;
	}
	else
	{
		domRel = 2;
	}
}

void QPacking::update_subpop(vector <CIndividual>& v_TotalChromo, vector <vector<CIndividual>>& v_Chromo)
{
	for (int m = 0; m < v_TotalChromo.size(); m++)//更新v_Chromo的upper_rank,upper_crowdedistance 
	{
		int sub_num = m / lower_number_of_individuals;
		//cout << "sub_num = " << sub_num << endl;
		int low_indiv_index = fmod(m, lower_number_of_individuals);
		//cout << "low_indiv_index = " << low_indiv_index << endl;
		//system("pause");
		v_Chromo[sub_num][low_indiv_index].sub_no = sub_num + 1;
		v_Chromo[sub_num][low_indiv_index].upper_rank = v_TotalChromo[m].upper_rank;
		v_Chromo[sub_num][low_indiv_index].upper_crowdedistance = v_TotalChromo[m].upper_crowdedistance;
	}
	//cout << "输出每个个体的上下层序值和拥挤度距离值" << endl;
	//for (int m = 0; m < v_Chromo.size(); m++)
	//{
	//	cout << "sub_no = " << m + 1 << endl;
	//	for (int n = 0; n < v_Chromo[m].size(); n++)
	//	{
	//		cout << "iner = " << n + 1 << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_Chromo[m][n].v_chromosome1[u].operation_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//		{
	//			cout << v_Chromo[m][n].v_chromosome1[u].operation_index << " ";
	//		}
	//		cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_Chromo[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_Chromo[m][n].v_chromosome1[u].machine_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = number_of_jobs * number_of_operations; u < v_Chromo[m][n].v_chromosome1.size(); u++)
	//		{
	//			cout << v_Chromo[m][n].v_chromosome1[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_Chromo[m][n].v_chromosome2.size(); u++)
	//		{
	//			cout << v_Chromo[m][n].v_chromosome2[u].job_number << " ";
	//		}
	//		cout << endl;
	//		for (int u = 0; u < v_Chromo[m][n].v_ul_objectives.size(); u++)
	//		{
	//			for (int v = 0; v < v_Chromo[m][n].v_ul_objectives[u].size(); v++)
	//			{
	//				cout << v_Chromo[m][n].v_ul_objectives[u][v] << " ";
	//			}
	//		}
	//		cout << endl;
	//		//system("pause");
	//		cout << v_Chromo[m][n].sub_no << endl;
	//		cout << v_Chromo[m][n].upper_rank << " " << v_Chromo[m][n].upper_crowdedistance << endl;
	//		cout << v_Chromo[m][n].lower_rank << " " << v_Chromo[m][n].lower_crowdedistance << endl;
	//		//system("pause");
	//	}
	//	cout << endl<<endl;
	//}


	int Indiv_no = 0;
	for (int m = 0; m < v_Chromo.size(); m++)//更新v_TotalChromo的lower_rank,lower_crowdedistance 
	{
		for (int n = 0; n < v_Chromo[m].size(); n++)
		{
			v_TotalChromo[Indiv_no].sub_no = v_Chromo[m][n].sub_no;
			v_TotalChromo[Indiv_no].lower_rank = v_Chromo[m][n].lower_rank;
			v_TotalChromo[Indiv_no].lower_crowdedistance = v_Chromo[m][n].lower_crowdedistance;
			Indiv_no++;
		}
	}
	//cout << "输出每个个体的上下层序值和拥挤度距离值" << endl;
	//for (int m = 0; m < v_TotalChromo.size(); m++)
	//{
	//	cout << "m = " << m + 1 << endl;
	//	cout << v_TotalChromo[m].sub_no << " ";
	//	cout << v_TotalChromo[m].upper_rank << " ";
	//	cout << v_TotalChromo[m].upper_crowdedistance << " ";
	//	cout << v_TotalChromo[m].lower_rank << " ";
	//	cout << v_TotalChromo[m].lower_crowdedistance << endl;
	//}
	////system("pause");
}