#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"
#include "Item.h"
#include <algorithm>
#include <map>
#include <iomanip>

void QPacking::adaptive_search(vector <vector<CIndividual>>& v_new_Chromo, vector<CIndividual>& v_new_TotalChromo, vector<Item>& v_product)
{
	////step1: ����ѡ��ѡ��Qֵ�����ж�����̰�Ĳ���
	double rand_probability = rand() / (RAND_MAX * 1.0);//�������
	double greedy_value = 0.5 / (1 + exp(10 * (outer_iteration_count - 0.6 * outer_iteration_count_max) / outer_iteration_count_max));
	if (rand_probability > 1 - greedy_value) //̰�Ĳ���
	{
		Action_Current = rand() % (7) + 1;//���ѡ��һ���ж�
	}
	else //���Qֵ��Ӧ���ж�
	{
		int Action_Position = max_element(Q_TABLE[State_Current - 1], Q_TABLE[State_Current - 1] + Action_Number) - Q_TABLE[State_Current - 1];
		Action_Current = Action_Position + 1;
	}

	////step2: ִ�ж��������ls��Ⱥv_ls_Chromo��v_ls_TotalChromo
	vector <vector<CIndividual>> v_new_Chromo_temp(v_new_Chromo);
	vector <CIndividual> v_new_TotalChromo_temp(v_new_TotalChromo);
	local_search(v_new_TotalChromo_temp, v_new_Chromo_temp, v_product, Action_Current);

	////step3: �Ƚ�LS��Ⱥ��δ����LS����Ⱥ��֧����	
	C_metric(v_ls_TotalChromo, v_new_TotalChromo_temp, C_value_v);//����Ⱥ֧��ԭ��Ⱥ�ı���
	C_metric(v_new_TotalChromo_temp, v_ls_TotalChromo, C_value_t);//ԭ��Ⱥ֧������Ⱥ�ı���
	difference_C = C_value_v - C_value_t;
	DV_metric(v_ls_TotalChromo, DV_value_v);
	DV_metric(v_new_TotalChromo_temp, DV_value_t);
	difference_DV = DV_value_v - DV_value_t;

	////step4: ���½�����������״̬��Q��
	double REWARD = 0;//��ʼ������ֵ
	if (difference_C > 0.0 && difference_DV > 0.0)//����״̬�ͽ���ֵ
	{
		State_Next = 1;
		REWARD = 10;
	}
	else if (difference_C > 0.0 && difference_DV <= 0)
	{
		State_Next = 2;
		REWARD = 5;
	}
	else if (difference_C <= 0.0 && difference_DV > 0)
	{
		State_Next = 3;
		REWARD = 5;
	}
	else
	{
		State_Next = 4;
		REWARD = 0;
	}
	//cout << "��ǰ״̬State_Current = " << State_Current << endl;
	//cout << "��һ��״̬State_Next = " << State_Next << endl;
	//cout << "��ý���REWARD = " << REWARD << endl;
	double maxQ_next = *max_element(Q_TABLE[State_Next - 1], Q_TABLE[State_Next - 1] + Action_Number);//*max_element()�������÷���������Ӧ״̬�µ����Qֵ
	//����Q��Q(s,a) �� Q(s,a) + ѧϰ�ʡ�[���� + �ۿ����ӡ���һ��״̬������max - Q(s,a)]
	Q_TABLE[State_Current - 1][Action_Current - 1] = Q_TABLE[State_Current - 1][Action_Current - 1] +
		Learning_Rate * (REWARD + Discount_Factor * maxQ_next - Q_TABLE[State_Current - 1][Action_Current - 1]);

	State_Current = State_Next;//������һ�ν���ʱ��״̬
}