#include "Qpacking.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"
#include <vector>
#include "RankSequ.h"
using namespace std;

void QPacking::rank_up(vector <CIndividual>& v_TotalChromo)
{
	//cout << "------------2、上层非支配分层---------" << endl;
	int i, j;
	int domRel, rankLevel, size, sizeZero, domChromoNo, domedChromoNo;
	double objValue;
	bool bt;
	vector <int> v_domZero;//创建容器，储存被支配次数为0的个体（不是单指第一层，有可能是后面新一批的下一层）
	for (i = 0; i < v_TotalChromo.size(); i++)//初始化
	{
		v_TotalChromo[i].upper_domination_count = 0;
		v_TotalChromo[i].v_upper_dominationSet.resize(0);
		v_TotalChromo[i].upper_rank = 0;
	}
	   
	for (i = 0; i < v_TotalChromo.size() - 1; i++)//此过程获取种群中每个 对象的 被支配次数 和 支配其他个体的集合
	{
		for (int j = i + 1; j < v_TotalChromo.size(); j++)
		{               
			domRel = 3; 
			domRelation_up(v_TotalChromo[i], v_TotalChromo[j], domRel);
			if (domRel == 1)//前者优于后者      函数值=1，表示支配；
			{
				v_TotalChromo[j].upper_domination_count++;
				v_TotalChromo[i].v_upper_dominationSet.push_back(j);
			}
			else if (domRel == -1)///前者差于后者    函数值=-1，表示被支配
			{
				v_TotalChromo[i].upper_domination_count++;
				v_TotalChromo[j].v_upper_dominationSet.push_back(i);
			}
		}
	}

	vector <CRankSequ>().swap(v_upper_rankSequ); //此过程获取种群中每个 对象的 upper_rank，upper_domination_count，v_upper_dominationSet
	rankLevel = 1;	
	while (1)
	{                
		bt = false;   
		v_domZero.resize(0);
		for (i = 0; i < v_TotalChromo.size(); i++)
		{    
			if (v_TotalChromo[i].upper_domination_count == 0)
			{				
				CRankSequ t;                
				v_TotalChromo[i].upper_rank = rankLevel;
				t.chromoNo = i;
				t.rankSequ = rankLevel;
				for (j = 0; j < number_of_objectives; j++)
				{
					objValue = v_TotalChromo[i].v_ul_objectives[0][j];
					t.v_rObjValue.push_back(objValue);
				}
				v_upper_rankSequ.push_back(t);
				bt = true;
				v_domZero.push_back(i);
			}		
		}
		if (bt == false)
		{
			break;
		}
		if (bt == true)
		{
			rankLevel++;
			sizeZero = v_domZero.size();
			for (int j = 0; j < sizeZero; j++)
			{
				domChromoNo = v_domZero[j];
				v_TotalChromo[domChromoNo].upper_domination_count = -1;
				size = v_TotalChromo[domChromoNo].v_upper_dominationSet.size();
				for (int k = 0; k < size; k++)
				{
					domedChromoNo = v_TotalChromo[domChromoNo].v_upper_dominationSet[k];
					v_TotalChromo[domedChromoNo].upper_domination_count--;
				}
			}
		}
	}                                                                                          

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//cout << "每个个体的upper_rank值（NDu）：" << endl;
	//for (int m = 0; m < v_TotalChromo.size(); m++)
	//{
	//	cout << "m = "<< m << ", " << v_TotalChromo[m].upper_rank << endl;
	//}
	//cout << endl;
	//////输出v_rankSequ容器，对象属性包括:chromoNo个体号；rankSequ序值；拥挤度距离和目标值
	//cout << "v_rankSequ容器：" << endl;
	//for (int cn = 0; cn < v_upper_rankSequ.size(); cn++)
	//{
	//	cout << v_upper_rankSequ[cn].chromoNo << " ";
	//	cout << v_upper_rankSequ[cn].rankSequ << endl;
	//}
	//cout << endl;

	//首先需要获取一共有多少个簇，找出最大的rankSequ即可	
	int cluster_number = v_upper_rankSequ[v_TotalChromo.size() - 1].rankSequ;
	int num_c = 0;
	vector <vector<CRankSequ>>().swap(v_upper_cluster);//清空容器,初始化
	for (int cn = 1; cn <= cluster_number; cn++)
	{
		vector <CRankSequ> v;
		v_upper_cluster.push_back(v);

		for (int i = num_c; i < v_upper_rankSequ.size(); i++)
		{
			if (v_upper_rankSequ[i].rankSequ == cn)
			{
				CRankSequ clu;
				clu.chromoNo = v_upper_rankSequ[i].chromoNo;//获取作业号
				clu.rankSequ = v_upper_rankSequ[i].rankSequ;//获取rank值
				clu.v_rObjValue = v_upper_rankSequ[i].v_rObjValue;//获取上层目标值
				v_upper_cluster[cn - 1].push_back(clu);//将该对象放入当前簇列表
				num_c++;
			}
			else
			{
				break;
			}
		}
	}
	//cout<<"每层包含的个体及其簇号和目标值"<<endl;
	//for (int i = 0; i < v_upper_cluster.size(); i++)
	//{
	//	for (int j = 0; j < v_upper_cluster[i].size(); j++)
	//	{
	//		cout << v_upper_cluster[i][j].chromoNo << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < v_upper_cluster[i].size(); j++)
	//	{
	//		cout << v_upper_cluster[i][j].rankSequ << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < v_upper_cluster[i].size(); j++)
	//	{
	//		for (int k = 0; k < v_upper_cluster[i][j].v_rObjValue.size(); k++)
	//		{
	//			cout << v_upper_cluster[i][j].v_rObjValue[k] << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
	//system("pause");

	for (int m = 0; m < v_upper_cluster.size(); m++)
	{
		int start = 0;
		//cout << "start = " << start << endl;
		int end = v_upper_cluster[m].size() - 1;
		//cout << "end = " <<end << endl;
		crodiversity(v_upper_cluster[m], start, end);//求每层个体的拥挤度距离
		//system("pause");
		
		int chr_no;
		double cro_dis;
		for (int n = 0; n < v_upper_cluster[m].size(); n++)//获取v_TotalChromo中相应个体的拥挤度
		{
			//cout << v_upper_cluster[m][n].croDiversity << " ";
			cro_dis = v_upper_cluster[m][n].croDiversity;
			//cout << v_upper_cluster[m][n].chromoNo << " ";
			chr_no = v_upper_cluster[m][n].chromoNo;
			v_TotalChromo[chr_no].upper_crowdedistance = cro_dis;
		}
		//cout << endl;

		//for (int n = 0; n < v_upper_cluster[m].size(); n++)
		//{
		//	cout << v_upper_cluster[m][n].rankSequ << " ";
		//}
		//cout << endl;
		//for (int n = 0; n < v_upper_cluster[m].size(); n++)
		//{
		//	for (int k = 0; k < v_upper_cluster[m][n].v_rObjValue.size(); k++)
		//	{
		//		cout << v_upper_cluster[m][n].v_rObjValue[k] << " ";
		//	}
		//	cout << endl;
		//}
		//cout << endl;
		//system("pause");
	}

	//cout << "每个个体的upper_crowdedistance值（CDu）：" << endl;
	//for (int m = 0; m < v_TotalChromo.size(); m++)
	//{
	//	cout << "m = " << m << ", " << v_TotalChromo[m].upper_crowdedistance << endl;
	//}
	//system("pause");
}

void QPacking::domRelation_up(const CIndividual& A, const CIndividual& B, int& domRel)
{                 
	int i; 
	int equalCount, lessCount, greaterCount;
	equalCount = 0;
	lessCount = 0;
	greaterCount = 0;
	for (i = 0; i < number_of_objectives; i++)
	{
		if (A.v_ul_objectives[0][i] == B.v_ul_objectives[0][i])
		{
			equalCount++;//若两个对象的目标值相等，则相等次数++
		}
		if (A.v_ul_objectives[0][i] < B.v_ul_objectives[0][i])
		{
			lessCount++;//若A对象的目标值<B对象的目标值，则less次数++
		}
		if (A.v_ul_objectives[0][i] > B.v_ul_objectives[0][i])
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

void QPacking::domRelation_up1(CIndividual& A1, CIndividual& B1, int& domRel1)
{
	int i;
	int equalCount1, lessCount1, greaterCount1;
	equalCount1 = 0;
	lessCount1 = 0;
	greaterCount1 = 0;

	for (i = 0; i < number_of_objectives; i++)
	{
		//cout << "A1.v_ul_objectives[0][i] == " << A1.v_ul_objectives[0][i] << endl;
		if (A1.v_ul_objectives[0][i] == B1.v_ul_objectives[0][i])
		{
			equalCount1++;//若两个对象的目标值相等，则相等次数++
		}
		if (A1.v_ul_objectives[0][i] < B1.v_ul_objectives[0][i])
		{
			lessCount1++;//若A对象的目标值<B对象的目标值，则less次数++
		}
		if (A1.v_ul_objectives[0][i] > B1.v_ul_objectives[0][i])
		{
			greaterCount1++;//若A对象的目标值>B对象的目标值，则greater次数++
		}
	}
	//cout << "equalCount1 = " << equalCount1 << endl;
	if (equalCount1 == number_of_objectives)
	{
		domRel1 = 0;
	}
	else if ((equalCount1 + lessCount1 == number_of_objectives) && lessCount1 > 0)
	{
		domRel1 = 1;
	}
	else if ((equalCount1 + greaterCount1 == number_of_objectives) && greaterCount1 > 0)
	{
		domRel1 = -1;
	}
	else
	{
		domRel1 = 2;
	}
}

void QPacking::domRelation_up2(const CIndividual& A2, const CIndividual& B2, int& domRel2)
{
	int ii;
	int equalCount2, lessCount2, greaterCount2;
	equalCount2 = 0;
	lessCount2 = 0;
	greaterCount2 = 0;
	for (ii = 0; ii < number_of_objectives; ii++)
	{
		if (A2.v_ul_objectives[0][ii] == B2.v_ul_objectives[0][ii])
		{
			equalCount2++;//若两个对象的目标值相等，则相等次数++
		}
		if (A2.v_ul_objectives[0][ii] < B2.v_ul_objectives[0][ii])
		{
			lessCount2++;//若A对象的目标值<B对象的目标值，则less次数++
		}
		if (A2.v_ul_objectives[0][ii] > B2.v_ul_objectives[0][ii])
		{
			greaterCount2++;//若A对象的目标值>B对象的目标值，则greater次数++
		}
	}
	if (equalCount2 == number_of_objectives)
	{
		domRel2 = 0;
	}
	else if ((equalCount2 + lessCount2 == number_of_objectives) && lessCount2 > 0)
	{
		domRel2 = 1;
	}
	else if ((equalCount2 + greaterCount2 == number_of_objectives) && greaterCount2 > 0)
	{
		domRel2 = -1;
	}
	else
	{
		domRel2 = 2;
	}
}

void QPacking::domRelation_up3(const CIndividual& A3, const CIndividual& B3, int& domRel3)
{
	int iii;
	int equalCount3, lessCount3, greaterCount3;
	equalCount3 = 0;
	lessCount3 = 0;
	greaterCount3 = 0;
	for (iii = 0; iii < number_of_objectives; iii++)
	{
		if (A3.v_ul_objectives[0][iii] == B3.v_ul_objectives[0][iii])
		{
			equalCount3++;//若两个对象的目标值相等，则相等次数++
		}
		if (A3.v_ul_objectives[0][iii] < B3.v_ul_objectives[0][iii])
		{
			lessCount3++;//若A对象的目标值<B对象的目标值，则less次数++
		}
		if (A3.v_ul_objectives[0][iii] > B3.v_ul_objectives[0][iii])
		{
			greaterCount3++;//若A对象的目标值>B对象的目标值，则greater次数++
		}
	}
	if (equalCount3 == number_of_objectives)
	{
		domRel3 = 0;
	}
	else if ((equalCount3 + lessCount3 == number_of_objectives) && lessCount3 > 0)
	{
		domRel3 = 1;
	}
	else if ((equalCount3 + greaterCount3 == number_of_objectives) && greaterCount3 > 0)
	{
		domRel3 = -1;
	}
	else
	{
		domRel3 = 2;
	}
}

void QPacking::domRelation_up4(const CIndividual& A4, const CIndividual& B4, int& domRel4)
{
	int iiii;
	int equalCount4, lessCount4, greaterCount4;
	equalCount4 = 0;
	lessCount4 = 0;
	greaterCount4 = 0;
	for (iiii = 0; iiii < number_of_objectives; iiii++)
	{
		if (A4.v_ul_objectives[0][iiii] == B4.v_ul_objectives[0][iiii])
		{
			equalCount4++;//若两个对象的目标值相等，则相等次数++
		}
		if (A4.v_ul_objectives[0][iiii] < B4.v_ul_objectives[0][iiii])
		{
			lessCount4++;//若A对象的目标值<B对象的目标值，则less次数++
		}
		if (A4.v_ul_objectives[0][iiii] > B4.v_ul_objectives[0][iiii])
		{
			greaterCount4++;//若A对象的目标值>B对象的目标值，则greater次数++
		}
	}
	if (equalCount4 == number_of_objectives)
	{
		domRel4 = 0;
	}
	else if ((equalCount4 + lessCount4 == number_of_objectives) && lessCount4 > 0)
	{
		domRel4 = 1;
	}
	else if ((equalCount4 + greaterCount4 == number_of_objectives) && greaterCount4 > 0)
	{
		domRel4 = -1;
	}
	else
	{
		domRel4 = 2;
	}
}

void QPacking::domRelation_up5(const CIndividual& A5, const CIndividual& B5, int& domRel5)
{
	int iiiii;
	int equalCount5, lessCount5, greaterCount5;
	equalCount5 = 0;
	lessCount5 = 0;
	greaterCount5 = 0;
	for (iiiii = 0; iiiii < number_of_objectives; iiiii++)
	{
		if (A5.v_ul_objectives[0][iiiii] == B5.v_ul_objectives[0][iiiii])
		{
			equalCount5++;//若两个对象的目标值相等，则相等次数++
		}
		if (A5.v_ul_objectives[0][iiiii] < B5.v_ul_objectives[0][iiiii])
		{
			lessCount5++;//若A对象的目标值<B对象的目标值，则less次数++
		}
		if (A5.v_ul_objectives[0][iiiii] > B5.v_ul_objectives[0][iiiii])
		{
			greaterCount5++;//若A对象的目标值>B对象的目标值，则greater次数++
		}
	}
	if (equalCount5 == number_of_objectives)
	{
		domRel5 = 0;
	}
	else if ((equalCount5 + lessCount5 == number_of_objectives) && lessCount5 > 0)
	{
		domRel5 = 1;
	}
	else if ((equalCount5 + greaterCount5 == number_of_objectives) && greaterCount5 > 0)
	{
		domRel5 = -1;
	}
	else
	{
		domRel5 = 2;
	}
}

void QPacking::domRelation_up6(const CIndividual& A6, const CIndividual& B6, int& domRel6)
{
	int iiiiii;
	int equalCount6, lessCount6, greaterCount6;
	equalCount6 = 0;
	lessCount6 = 0;
	greaterCount6 = 0;
	for (iiiiii = 0; iiiiii < number_of_objectives; iiiiii++)
	{
		if (A6.v_ul_objectives[0][iiiiii] == B6.v_ul_objectives[0][iiiiii])
		{
			equalCount6++;//若两个对象的目标值相等，则相等次数++
		}
		if (A6.v_ul_objectives[0][iiiiii] < B6.v_ul_objectives[0][iiiiii])
		{
			lessCount6++;//若A对象的目标值<B对象的目标值，则less次数++
		}
		if (A6.v_ul_objectives[0][iiiiii] > B6.v_ul_objectives[0][iiiiii])
		{
			greaterCount6++;//若A对象的目标值>B对象的目标值，则greater次数++
		}
	}
	if (equalCount6 == number_of_objectives)
	{
		domRel6 = 0;
	}
	else if ((equalCount6 + lessCount6 == number_of_objectives) && lessCount6 > 0)
	{
		domRel6 = 1;
	}
	else if ((equalCount6 + greaterCount6 == number_of_objectives) && greaterCount6 > 0)
	{
		domRel6 = -1;
	}
	else
	{
		domRel6 = 2;
	}
}

void QPacking::domRelation_up7(const CIndividual& A7, const CIndividual& B7, int& domRel7)
{
	int iiiiiii;
	int equalCount7, lessCount7, greaterCount7;
	equalCount7 = 0;
	lessCount7 = 0;
	greaterCount7 = 0;
	for (iiiiiii = 0; iiiiiii < number_of_objectives; iiiiiii++)
	{
		if (A7.v_ul_objectives[0][iiiiiii] == B7.v_ul_objectives[0][iiiiiii])
		{
			equalCount7++;//若两个对象的目标值相等，则相等次数++
		}
		if (A7.v_ul_objectives[0][iiiiiii] < B7.v_ul_objectives[0][iiiiiii])
		{
			lessCount7++;//若A对象的目标值<B对象的目标值，则less次数++
		}
		if (A7.v_ul_objectives[0][iiiiiii] > B7.v_ul_objectives[0][iiiiiii])
		{
			greaterCount7++;//若A对象的目标值>B对象的目标值，则greater次数++
		}
	}
	if (equalCount7 == number_of_objectives)
	{
		domRel7 = 0;
	}
	else if ((equalCount7 + lessCount7 == number_of_objectives) && lessCount7 > 0)
	{
		domRel7 = 1;
	}
	else if ((equalCount7 + greaterCount7 == number_of_objectives) && greaterCount7 > 0)
	{
		domRel7 = -1;
	}
	else
	{
		domRel7 = 2;
	}
}

void QPacking::crodiversity(vector <CRankSequ>& v_rankSequ, int& start, int& end)
{                         
	int i, j;
	double minObjValue, maxObjValue, preObjValue, nextObjValue;//最小值，最大目值，前值，后置
	double dtemp;
	CRankSequ t;

	for (i = start; i <= end; i++)
	{
		v_rankSequ[i].croDiversity = 0.0;//初始化 某一层的个体 的 拥挤度密度=0；
	}
	
	for (int objNo = 0; objNo < number_of_objectives; objNo++)//遍历每个目标
	{
		for (i = start; i <= end - 1; i++)//升序排列；类似于冒泡排序
		{
			for (int j = i + 1; j <= end; j++)
			{
				dtemp = v_rankSequ[i].v_rObjValue[objNo];
				if (dtemp > v_rankSequ[j].v_rObjValue[objNo])
				{
					t = v_rankSequ[i];
					v_rankSequ[i] = v_rankSequ[j];
					v_rankSequ[j] = t;
				}
			}
		}

		////经历上面排序后，start对应当前目标下的目标值小的对象，end对象目标值大的对象 某一层的两端临界对象 的 拥挤度距离 =无穷大
		v_rankSequ[start].croDiversity = 0x3f3f3f3f;
		v_rankSequ[end].croDiversity = 0x3f3f3f3f;

		minObjValue = v_rankSequ[start].v_rObjValue[objNo];//获取当前目标的最小目标值；
		maxObjValue = v_rankSequ[end].v_rObjValue[objNo];//获取当前目标的最大目标值；

		for (i = start + 1; i <= end - 1; i++)
		{   
			preObjValue = v_rankSequ[i - 1].v_rObjValue[objNo];
			nextObjValue = v_rankSequ[i + 1].v_rObjValue[objNo];
			v_rankSequ[i].croDiversity = v_rankSequ[i].croDiversity + abs((double)(nextObjValue - preObjValue)) / ((maxObjValue - minObjValue) * 1.0);
			//cout << "v_rankSequ[i].croDiversity =" << v_rankSequ[i].croDiversity << endl;
		}
		//system("pause");
	}
	//以上 求出所有对象的拥挤度距离

	for (i = start; i <= end - 1; i++) //按照个体密度，对v_rankSequ容器中的个体降序排列
	{
		for (j = i + 1; j <= end; j++)
		{
			dtemp = v_rankSequ[i].croDiversity;
			if (dtemp < v_rankSequ[j].croDiversity)
			{
				t = v_rankSequ[i];//互换操作，比较拥挤度距离，将对应对象互换；
				v_rankSequ[i] = v_rankSequ[j];//即拥挤度距离值小的对象在前面，拥挤度距离值大的对象在后面；
				v_rankSequ[j] = t;//互换对象，故用对象t来当第三方工具人；
			}
		}
	}
}

