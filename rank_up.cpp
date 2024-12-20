#include "Qpacking.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"
#include <vector>
#include "RankSequ.h"
using namespace std;

void QPacking::rank_up(vector <CIndividual>& v_TotalChromo)
{
	//cout << "------------2���ϲ��֧��ֲ�---------" << endl;
	int i, j;
	int domRel, rankLevel, size, sizeZero, domChromoNo, domedChromoNo;
	double objValue;
	bool bt;
	vector <int> v_domZero;//�������������汻֧�����Ϊ0�ĸ��壨���ǵ�ָ��һ�㣬�п����Ǻ�����һ������һ�㣩
	for (i = 0; i < v_TotalChromo.size(); i++)//��ʼ��
	{
		v_TotalChromo[i].upper_domination_count = 0;
		v_TotalChromo[i].v_upper_dominationSet.resize(0);
		v_TotalChromo[i].upper_rank = 0;
	}
	   
	for (i = 0; i < v_TotalChromo.size() - 1; i++)//�˹��̻�ȡ��Ⱥ��ÿ�� ����� ��֧����� �� ֧����������ļ���
	{
		for (int j = i + 1; j < v_TotalChromo.size(); j++)
		{               
			domRel = 3; 
			domRelation_up(v_TotalChromo[i], v_TotalChromo[j], domRel);
			if (domRel == 1)//ǰ�����ں���      ����ֵ=1����ʾ֧�䣻
			{
				v_TotalChromo[j].upper_domination_count++;
				v_TotalChromo[i].v_upper_dominationSet.push_back(j);
			}
			else if (domRel == -1)///ǰ�߲��ں���    ����ֵ=-1����ʾ��֧��
			{
				v_TotalChromo[i].upper_domination_count++;
				v_TotalChromo[j].v_upper_dominationSet.push_back(i);
			}
		}
	}

	vector <CRankSequ>().swap(v_upper_rankSequ); //�˹��̻�ȡ��Ⱥ��ÿ�� ����� upper_rank��upper_domination_count��v_upper_dominationSet
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
	//cout << "ÿ�������upper_rankֵ��NDu����" << endl;
	//for (int m = 0; m < v_TotalChromo.size(); m++)
	//{
	//	cout << "m = "<< m << ", " << v_TotalChromo[m].upper_rank << endl;
	//}
	//cout << endl;
	//////���v_rankSequ�������������԰���:chromoNo����ţ�rankSequ��ֵ��ӵ���Ⱦ����Ŀ��ֵ
	//cout << "v_rankSequ������" << endl;
	//for (int cn = 0; cn < v_upper_rankSequ.size(); cn++)
	//{
	//	cout << v_upper_rankSequ[cn].chromoNo << " ";
	//	cout << v_upper_rankSequ[cn].rankSequ << endl;
	//}
	//cout << endl;

	//������Ҫ��ȡһ���ж��ٸ��أ��ҳ�����rankSequ����	
	int cluster_number = v_upper_rankSequ[v_TotalChromo.size() - 1].rankSequ;
	int num_c = 0;
	vector <vector<CRankSequ>>().swap(v_upper_cluster);//�������,��ʼ��
	for (int cn = 1; cn <= cluster_number; cn++)
	{
		vector <CRankSequ> v;
		v_upper_cluster.push_back(v);

		for (int i = num_c; i < v_upper_rankSequ.size(); i++)
		{
			if (v_upper_rankSequ[i].rankSequ == cn)
			{
				CRankSequ clu;
				clu.chromoNo = v_upper_rankSequ[i].chromoNo;//��ȡ��ҵ��
				clu.rankSequ = v_upper_rankSequ[i].rankSequ;//��ȡrankֵ
				clu.v_rObjValue = v_upper_rankSequ[i].v_rObjValue;//��ȡ�ϲ�Ŀ��ֵ
				v_upper_cluster[cn - 1].push_back(clu);//���ö�����뵱ǰ���б�
				num_c++;
			}
			else
			{
				break;
			}
		}
	}
	//cout<<"ÿ������ĸ��弰��غź�Ŀ��ֵ"<<endl;
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
		crodiversity(v_upper_cluster[m], start, end);//��ÿ������ӵ���Ⱦ���
		//system("pause");
		
		int chr_no;
		double cro_dis;
		for (int n = 0; n < v_upper_cluster[m].size(); n++)//��ȡv_TotalChromo����Ӧ�����ӵ����
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

	//cout << "ÿ�������upper_crowdedistanceֵ��CDu����" << endl;
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
			equalCount++;//�����������Ŀ��ֵ��ȣ�����ȴ���++
		}
		if (A.v_ul_objectives[0][i] < B.v_ul_objectives[0][i])
		{
			lessCount++;//��A�����Ŀ��ֵ<B�����Ŀ��ֵ����less����++
		}
		if (A.v_ul_objectives[0][i] > B.v_ul_objectives[0][i])
		{
			greaterCount++;//��A�����Ŀ��ֵ>B�����Ŀ��ֵ����greater����++
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
			equalCount1++;//�����������Ŀ��ֵ��ȣ�����ȴ���++
		}
		if (A1.v_ul_objectives[0][i] < B1.v_ul_objectives[0][i])
		{
			lessCount1++;//��A�����Ŀ��ֵ<B�����Ŀ��ֵ����less����++
		}
		if (A1.v_ul_objectives[0][i] > B1.v_ul_objectives[0][i])
		{
			greaterCount1++;//��A�����Ŀ��ֵ>B�����Ŀ��ֵ����greater����++
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
			equalCount2++;//�����������Ŀ��ֵ��ȣ�����ȴ���++
		}
		if (A2.v_ul_objectives[0][ii] < B2.v_ul_objectives[0][ii])
		{
			lessCount2++;//��A�����Ŀ��ֵ<B�����Ŀ��ֵ����less����++
		}
		if (A2.v_ul_objectives[0][ii] > B2.v_ul_objectives[0][ii])
		{
			greaterCount2++;//��A�����Ŀ��ֵ>B�����Ŀ��ֵ����greater����++
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
			equalCount3++;//�����������Ŀ��ֵ��ȣ�����ȴ���++
		}
		if (A3.v_ul_objectives[0][iii] < B3.v_ul_objectives[0][iii])
		{
			lessCount3++;//��A�����Ŀ��ֵ<B�����Ŀ��ֵ����less����++
		}
		if (A3.v_ul_objectives[0][iii] > B3.v_ul_objectives[0][iii])
		{
			greaterCount3++;//��A�����Ŀ��ֵ>B�����Ŀ��ֵ����greater����++
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
			equalCount4++;//�����������Ŀ��ֵ��ȣ�����ȴ���++
		}
		if (A4.v_ul_objectives[0][iiii] < B4.v_ul_objectives[0][iiii])
		{
			lessCount4++;//��A�����Ŀ��ֵ<B�����Ŀ��ֵ����less����++
		}
		if (A4.v_ul_objectives[0][iiii] > B4.v_ul_objectives[0][iiii])
		{
			greaterCount4++;//��A�����Ŀ��ֵ>B�����Ŀ��ֵ����greater����++
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
			equalCount5++;//�����������Ŀ��ֵ��ȣ�����ȴ���++
		}
		if (A5.v_ul_objectives[0][iiiii] < B5.v_ul_objectives[0][iiiii])
		{
			lessCount5++;//��A�����Ŀ��ֵ<B�����Ŀ��ֵ����less����++
		}
		if (A5.v_ul_objectives[0][iiiii] > B5.v_ul_objectives[0][iiiii])
		{
			greaterCount5++;//��A�����Ŀ��ֵ>B�����Ŀ��ֵ����greater����++
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
			equalCount6++;//�����������Ŀ��ֵ��ȣ�����ȴ���++
		}
		if (A6.v_ul_objectives[0][iiiiii] < B6.v_ul_objectives[0][iiiiii])
		{
			lessCount6++;//��A�����Ŀ��ֵ<B�����Ŀ��ֵ����less����++
		}
		if (A6.v_ul_objectives[0][iiiiii] > B6.v_ul_objectives[0][iiiiii])
		{
			greaterCount6++;//��A�����Ŀ��ֵ>B�����Ŀ��ֵ����greater����++
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
			equalCount7++;//�����������Ŀ��ֵ��ȣ�����ȴ���++
		}
		if (A7.v_ul_objectives[0][iiiiiii] < B7.v_ul_objectives[0][iiiiiii])
		{
			lessCount7++;//��A�����Ŀ��ֵ<B�����Ŀ��ֵ����less����++
		}
		if (A7.v_ul_objectives[0][iiiiiii] > B7.v_ul_objectives[0][iiiiiii])
		{
			greaterCount7++;//��A�����Ŀ��ֵ>B�����Ŀ��ֵ����greater����++
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
	double minObjValue, maxObjValue, preObjValue, nextObjValue;//��Сֵ�����Ŀֵ��ǰֵ������
	double dtemp;
	CRankSequ t;

	for (i = start; i <= end; i++)
	{
		v_rankSequ[i].croDiversity = 0.0;//��ʼ�� ĳһ��ĸ��� �� ӵ�����ܶ�=0��
	}
	
	for (int objNo = 0; objNo < number_of_objectives; objNo++)//����ÿ��Ŀ��
	{
		for (i = start; i <= end - 1; i++)//�������У�������ð������
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

		////�������������start��Ӧ��ǰĿ���µ�Ŀ��ֵС�Ķ���end����Ŀ��ֵ��Ķ��� ĳһ��������ٽ���� �� ӵ���Ⱦ��� =�����
		v_rankSequ[start].croDiversity = 0x3f3f3f3f;
		v_rankSequ[end].croDiversity = 0x3f3f3f3f;

		minObjValue = v_rankSequ[start].v_rObjValue[objNo];//��ȡ��ǰĿ�����СĿ��ֵ��
		maxObjValue = v_rankSequ[end].v_rObjValue[objNo];//��ȡ��ǰĿ������Ŀ��ֵ��

		for (i = start + 1; i <= end - 1; i++)
		{   
			preObjValue = v_rankSequ[i - 1].v_rObjValue[objNo];
			nextObjValue = v_rankSequ[i + 1].v_rObjValue[objNo];
			v_rankSequ[i].croDiversity = v_rankSequ[i].croDiversity + abs((double)(nextObjValue - preObjValue)) / ((maxObjValue - minObjValue) * 1.0);
			//cout << "v_rankSequ[i].croDiversity =" << v_rankSequ[i].croDiversity << endl;
		}
		//system("pause");
	}
	//���� ������ж����ӵ���Ⱦ���

	for (i = start; i <= end - 1; i++) //���ո����ܶȣ���v_rankSequ�����еĸ��彵������
	{
		for (j = i + 1; j <= end; j++)
		{
			dtemp = v_rankSequ[i].croDiversity;
			if (dtemp < v_rankSequ[j].croDiversity)
			{
				t = v_rankSequ[i];//�����������Ƚ�ӵ���Ⱦ��룬����Ӧ���󻥻���
				v_rankSequ[i] = v_rankSequ[j];//��ӵ���Ⱦ���ֵС�Ķ�����ǰ�棬ӵ���Ⱦ���ֵ��Ķ����ں��棻
				v_rankSequ[j] = t;//�������󣬹��ö���t���������������ˣ�
			}
		}
	}
}

