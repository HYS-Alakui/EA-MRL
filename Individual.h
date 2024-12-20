#include "headfile.h"
#include "Chromosome.h"

#ifndef _INFORMATIONCOLLEAGE_
#define _INFORMATIONCOLLEAGE_

class CIndividual//����һ���� ����ΪCIndividual
{
private:
public:
	vector <CChromosome> v_chromosome1; //�ϲ������FJSP�Ĺ���ӹ����кͻ���ѡ������        
	vector <CChromosome> v_chromosome2; //�²���������μ�������˳��


	vector <CChromosome> v_upper_chromosome1;
	vector <CChromosome> v_upper_chromosome2;
	vector <CChromosome> v_lower_chromosome;

	int sub_no;//�ø�������������Ⱥ���

	vector<vector<double>> v_ul_objectives;
	double use_rate;
	double consistant_value;
	double total_tardiness;	
	double total_cost;

	vector <int> v_job_packing_finish_time;//��¼ÿ�����μ���job�����и��깤ʱ��

	int upper_rank;
	int upper_domination_count;
	vector <int> v_upper_dominationSet;
	double upper_crowdedistance;

	int lower_rank;
	int lower_domination_count;
	vector <int> v_lower_dominationSet;
	double lower_crowdedistance;

	int max_tardiness_job_index;

	vector<pair<int, int>> v_real_packing_route;

	vector<int>Job_C;//�ؼ�·������ҵ������
	vector<int>Operation_C;//�ؼ�·����ҵ�Ĺ���ţ�����
	vector<int>Machine_C;//�ؼ�·����ҵ�Ĺ������ڵĻ���������,������-1��
	vector<int>Product_C;//�����׶ιؼ�·����job�ţ�����

	//vector<int>Keymachine_Operation;//�ؼ������ϵĹ���
	//vector<int>Keymachine_Operation_Xuhao;//�ؼ������ϵĹ������

	//vector <int> v_job_list;//����һ������ ÿ������ �� ��ҵ���� �� ����
	//vector <int> v_factory_list;//����һ������ ÿ������ �� ��ҵ���� �� ����	

	//int key_cell;
	//int key_factory_index;//��ѹ���
	//int key_machine_index;//��ѻ���

};
#endif
