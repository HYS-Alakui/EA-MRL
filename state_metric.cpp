#include "Qpacking.h"
#include "Individual.h"
#include "rankSequ.h"
#include "headfile.h"

void QPacking::C_metric(vector <CIndividual>& r1_Chromo, vector <CIndividual>& r2_Chromo, double& C_value)
{
	int dominant_number = 0;//����Ⱥ֧��ԭ��Ⱥ�еĸ��������
	for (int i = 0; i < r2_Chromo.size(); i++)
	{
		for (int j = 0; j < r1_Chromo.size(); j++)
		{
			int domRel;
			domRelation_up1(r1_Chromo[j], r2_Chromo[i], domRel);
			if (domRel == 1)
			{
				dominant_number++;
				break;
			}
		}
	}
	C_value = (double)dominant_number / r2_Chromo.size();
	//cout << "Cָ�꣺" << C_value << endl;
}

void QPacking::DV_metric(vector <CIndividual>& r_Chromo, double& DV_value)
{
	vector <CIndividual> population_rank;//���еķ�֧�����
	vector <CIndividual>().swap(population_rank);//����swap�����ڴ�
	for (int i = 0; i < r_Chromo.size(); i++)
	{
		if (r_Chromo[i].upper_rank == 1)
		{
			population_rank.push_back(r_Chromo[i]);
		}
	}

	CIndividual t;
	int rank_size = population_rank.size();
	double dtemp = 0;//Ŀ��ֵ������
	for (int objNo = 0; objNo < number_of_objectives; objNo++)//����ÿ��Ŀ��
	{
		for (int i = 0; i <= rank_size - 2; i++)//�������У�������ð������
		{
			for (int j = i + 1; j <= rank_size - 1; j++)
			{
				dtemp = population_rank[i].v_ul_objectives[0][objNo];//��ȡi�����Ŀ��ֵ
				if (dtemp > population_rank[j].v_ul_objectives[0][objNo])//��j�����Ŀ��ֵ�Ƚ�
				{
					t = population_rank[i];//��Ϊ�Ƕ��󻻣��Ҷ��������е����Լ���ǰĿ���µ�Ŀ��ֵҲ���ű䶯��
					population_rank[i] = population_rank[j];//���ö���t���������������ˣ�
					population_rank[j] = t;//����������Ŀ��ֵС�Ķ��󱻻���ǰ�棬Ŀ��ֵ��Ķ��󱻻�������
				}
			}
		}
	}

	vector<double>dist_two_point;//�洢������֮���ŷ�Ͼ���
	double total_distance = 0;//�ܾ���
	for (int k = 0; k < population_rank.size() - 1; k++)
	{
		double object_dis_1 = pow((population_rank[k].v_ul_objectives[0][0] - population_rank[k + 1].v_ul_objectives[0][0]), 2);
		double object_dis_2 = pow((population_rank[k].v_ul_objectives[0][1] - population_rank[k + 1].v_ul_objectives[0][1]), 2);
		double object_dis = object_dis_1 + object_dis_2;// + object_dis_3
		double diatance_two = sqrt(object_dis);
		dist_two_point.push_back(diatance_two);
		total_distance = total_distance + diatance_two;
	}
	double avr_distance = total_distance / dist_two_point.size();//ƽ������
	double total_difference_distance = 0;//DV����
	for (int k = 0; k < dist_two_point.size(); k++)
	{
		total_difference_distance = total_difference_distance + fabs(dist_two_point[k] - avr_distance);
	}
	DV_value = total_difference_distance / (dist_two_point.size() * avr_distance);
	//cout << "DVֵ��" << DV_value << endl;
}

void QPacking::C_metric1(vector <CIndividual>& r1_Chromo1, vector <CIndividual>& r2_Chromo1, double& C_value1)
{
	int dominant_number1 = 0;//����Ⱥ֧��ԭ��Ⱥ�еĸ��������
	for (int i = 0; i < r2_Chromo1.size(); i++)
	{
		for (int j = 0; j < r1_Chromo1.size(); j++)
		{
			int domRel1;
			domRelation_up1(r1_Chromo1[j], r2_Chromo1[i], domRel1);
			if (domRel1 == 1)
			{
				dominant_number1++;
				break;
			}
		}
	}
	C_value1 = (double)dominant_number1 / r2_Chromo1.size();
	//cout << "Cָ�꣺" << C_value1 << endl;
}

void QPacking::DV_metric1(vector <CIndividual>& r_Chromo1, double& DV_value1)
{
	vector <CIndividual> population_rank1;//���еķ�֧�����
	vector <CIndividual>().swap(population_rank1);//����swap�����ڴ�
	for (int i = 0; i < r_Chromo1.size(); i++)
	{
		if (r_Chromo1[i].upper_rank == 1)
		{
			population_rank1.push_back(r_Chromo1[i]);
		}
	}

	CIndividual t1;
	int rank_size1 = population_rank1.size();
	double dtemp1 = 0;//Ŀ��ֵ������
	for (int objNo = 0; objNo < number_of_objectives; objNo++)//����ÿ��Ŀ��
	{
		for (int i = 0; i <= rank_size1 - 2; i++)//�������У�������ð������
		{
			for (int j = i + 1; j <= rank_size1 - 1; j++)
			{
				dtemp1 = population_rank1[i].v_ul_objectives[0][objNo];//��ȡi�����Ŀ��ֵ
				if (dtemp1 > population_rank1[j].v_ul_objectives[0][objNo])//��j�����Ŀ��ֵ�Ƚ�
				{
					t1 = population_rank1[i];//��Ϊ�Ƕ��󻻣��Ҷ��������е����Լ���ǰĿ���µ�Ŀ��ֵҲ���ű䶯��
					population_rank1[i] = population_rank1[j];//���ö���t���������������ˣ�
					population_rank1[j] = t1;//����������Ŀ��ֵС�Ķ��󱻻���ǰ�棬Ŀ��ֵ��Ķ��󱻻�������
				}
			}
		}
	}

	vector<double>dist_two_point1;//�洢������֮���ŷ�Ͼ���
	double total_distance1 = 0;//�ܾ���
	for (int k = 0; k < population_rank1.size() - 1; k++)
	{
		double object_dis_11 = pow((population_rank1[k].v_ul_objectives[0][0] - population_rank1[k + 1].v_ul_objectives[0][0]), 2);
		double object_dis_21 = pow((population_rank1[k].v_ul_objectives[0][1] - population_rank1[k + 1].v_ul_objectives[0][1]), 2);
		double object_dis1 = object_dis_11 + object_dis_21;// + object_dis_3
		double diatance_two1 = sqrt(object_dis1);
		dist_two_point1.push_back(diatance_two1);
		total_distance1 = total_distance1 + diatance_two1;
	}
	double avr_distance1 = total_distance1 / dist_two_point1.size();//ƽ������
	double total_difference_distance1 = 0;//DV����
	for (int k = 0; k < dist_two_point1.size(); k++)
	{
		total_difference_distance1 = total_difference_distance1 + fabs(dist_two_point1[k] - avr_distance1);
	}
	DV_value1 = total_difference_distance1 / (dist_two_point1.size() * avr_distance1);
	//cout << "DVֵ��" << DV_value1 << endl;
}

void QPacking::C_metric2(vector <CIndividual>& r1_Chromo2, vector <CIndividual>& r2_Chromo2, double& C_value2)
{
	int dominant_number2 = 0;//����Ⱥ֧��ԭ��Ⱥ�еĸ��������
	for (int ii = 0; ii < r2_Chromo2.size(); ii++)
	{
		for (int jj = 0; jj < r1_Chromo2.size(); jj++)
		{
			int domRel2;
			domRelation_up2(r1_Chromo2[jj], r2_Chromo2[ii], domRel2);
			if (domRel2 == 1)
			{
				dominant_number2++;
				break;
			}
		}
	}
	C_value2 = (double)dominant_number2 / r2_Chromo2.size();
	//cout << "Cָ�꣺" << C_value2 << endl;
}

void QPacking::DV_metric2(vector <CIndividual>& r_Chromo2, double& DV_value2)
{
	vector <CIndividual> population_rank2;//���еķ�֧�����
	vector <CIndividual>().swap(population_rank2);//����swap�����ڴ�
	for (int i = 0; i < r_Chromo2.size(); i++)
	{
		if (r_Chromo2[i].upper_rank == 1)
		{
			population_rank2.push_back(r_Chromo2[i]);
		}
	}

	CIndividual t2;
	int rank_size2 = population_rank2.size();
	double dtemp2 = 0;//Ŀ��ֵ������
	for (int objNo = 0; objNo < number_of_objectives; objNo++)//����ÿ��Ŀ��
	{
		for (int i = 0; i <= rank_size2 - 2; i++)//�������У�������ð������
		{
			for (int j = i + 1; j <= rank_size2 - 1; j++)
			{
				dtemp2 = population_rank2[i].v_ul_objectives[0][objNo];//��ȡi�����Ŀ��ֵ
				if (dtemp2 > population_rank2[j].v_ul_objectives[0][objNo])//��j�����Ŀ��ֵ�Ƚ�
				{
					t2 = population_rank2[i];//��Ϊ�Ƕ��󻻣��Ҷ��������е����Լ���ǰĿ���µ�Ŀ��ֵҲ���ű䶯��
					population_rank2[i] = population_rank2[j];//���ö���t���������������ˣ�
					population_rank2[j] = t2;//����������Ŀ��ֵС�Ķ��󱻻���ǰ�棬Ŀ��ֵ��Ķ��󱻻�������
				}
			}
		}
	}

	vector<double>dist_two_point2;//�洢������֮���ŷ�Ͼ���
	double total_distance2 = 0;//�ܾ���
	for (int k = 0; k < population_rank2.size() - 1; k++)
	{
		double object_dis_12 = pow((population_rank2[k].v_ul_objectives[0][0] - population_rank2[k + 1].v_ul_objectives[0][0]), 2);
		double object_dis_22 = pow((population_rank2[k].v_ul_objectives[0][1] - population_rank2[k + 1].v_ul_objectives[0][1]), 2);
		double object_dis2 = object_dis_12 + object_dis_22;
		double diatance_two2 = sqrt(object_dis2);
		dist_two_point2.push_back(diatance_two2);
		total_distance2 = total_distance2 + diatance_two2;
	}
	double avr_distance2 = total_distance2 / dist_two_point2.size();//ƽ������
	double total_difference_distance2 = 0;//DV����
	for (int k = 0; k < dist_two_point2.size(); k++)
	{
		total_difference_distance2 = total_difference_distance2 + fabs(dist_two_point2[k] - avr_distance2);
	}
	DV_value2 = total_difference_distance2 / (dist_two_point2.size() * avr_distance2);
	//cout << "DVֵ��" << DV_value2 << endl;
}

void QPacking::C_metric3(vector <CIndividual>& r1_Chromo3, vector <CIndividual>& r2_Chromo3, double& C_value3)
{
	int dominant_number3 = 0;//����Ⱥ֧��ԭ��Ⱥ�еĸ��������
	for (int iii = 0; iii < r2_Chromo3.size(); iii++)
	{
		for (int jjj = 0; jjj < r1_Chromo3.size();jjj++)
		{
			int domRel3;
			domRelation_up3(r1_Chromo3[jjj], r2_Chromo3[iii], domRel3);
			if (domRel3 == 1)
			{
				dominant_number3++;
				break;
			}
		}
	}
	C_value3 = (double)dominant_number3 / r2_Chromo3.size();
	//cout << "Cָ�꣺" << C_value3 << endl;
}

void QPacking::DV_metric3(vector <CIndividual>& r_Chromo3, double& DV_value3)
{
	vector <CIndividual> population_rank3;//���еķ�֧�����
	vector <CIndividual>().swap(population_rank3);//����swap�����ڴ�
	for (int i = 0; i < r_Chromo3.size(); i++)
	{
		if (r_Chromo3[i].upper_rank == 1)
		{
			population_rank3.push_back(r_Chromo3[i]);
		}
	}

	CIndividual t3;
	int rank_size3 = population_rank3.size();
	double dtemp3 = 0;//Ŀ��ֵ������
	for (int objNo = 0; objNo < number_of_objectives; objNo++)//����ÿ��Ŀ��
	{
		for (int i = 0; i <= rank_size3 - 2; i++)//�������У�������ð������
		{
			for (int j = i + 1; j <= rank_size3 - 1; j++)
			{
				dtemp3 = population_rank3[i].v_ul_objectives[0][objNo];//��ȡi�����Ŀ��ֵ
				if (dtemp3 > population_rank3[j].v_ul_objectives[0][objNo])//��j�����Ŀ��ֵ�Ƚ�
				{
					t3 = population_rank3[i];//��Ϊ�Ƕ��󻻣��Ҷ��������е����Լ���ǰĿ���µ�Ŀ��ֵҲ���ű䶯��
					population_rank3[i] = population_rank3[j];//���ö���t���������������ˣ�
					population_rank3[j] = t3;//����������Ŀ��ֵС�Ķ��󱻻���ǰ�棬Ŀ��ֵ��Ķ��󱻻�������
				}
			}
		}
	}

	vector<double>dist_two_point3;//�洢������֮���ŷ�Ͼ���
	double total_distance3 = 0;//�ܾ���
	for (int k = 0; k < population_rank3.size() - 1; k++)
	{
		double object_dis_13 = pow((population_rank3[k].v_ul_objectives[0][0] - population_rank3[k + 1].v_ul_objectives[0][0]), 2);
		double object_dis_23 = pow((population_rank3[k].v_ul_objectives[0][1] - population_rank3[k + 1].v_ul_objectives[0][1]), 2);
		double object_dis3 = object_dis_13 + object_dis_23;
		double diatance_two3 = sqrt(object_dis3);
		dist_two_point3.push_back(diatance_two3);
		total_distance3 = total_distance3 + diatance_two3;
	}
	double avr_distance3 = total_distance3 / dist_two_point3.size();//ƽ������
	double total_difference_distance3 = 0;//DV����
	for (int k = 0; k < dist_two_point3.size(); k++)
	{
		total_difference_distance3 = total_difference_distance3 + fabs(dist_two_point3[k] - avr_distance3);
	}
	DV_value3 = total_difference_distance3 / (dist_two_point3.size() * avr_distance3);
	//cout << "DVֵ��" << DV_value3 << endl;
}

void QPacking::C_metric4(vector <CIndividual>& r1_Chromo4, vector <CIndividual>& r2_Chromo4, double& C_value4)
{
	int dominant_number4 = 0;//����Ⱥ֧��ԭ��Ⱥ�еĸ��������
	for (int iiii = 0; iiii < r2_Chromo4.size(); iiii++)
	{
		for (int jjjj = 0; jjjj < r1_Chromo4.size(); jjjj++)
		{
			int domRel4;
			domRelation_up4(r1_Chromo4[jjjj], r2_Chromo4[iiii], domRel4);
			if (domRel4 == 1)
			{
				dominant_number4++;
				break;
			}
		}
	}
	C_value4 = (double)dominant_number4 / r2_Chromo4.size();
	//cout << "Cָ�꣺" << C_value4 << endl;
}

void QPacking::DV_metric4(vector <CIndividual>& r_Chromo4, double& DV_value4)
{
	vector <CIndividual> population_rank4;//���еķ�֧�����
	vector <CIndividual>().swap(population_rank4);//����swap�����ڴ�
	for (int i = 0; i < r_Chromo4.size(); i++)
	{
		if (r_Chromo4[i].upper_rank == 1)
		{
			population_rank4.push_back(r_Chromo4[i]);
		}
	}

	CIndividual t4;
	int rank_size4 = population_rank4.size();
	double dtemp4 = 0;//Ŀ��ֵ������
	for (int objNo = 0; objNo < number_of_objectives; objNo++)//����ÿ��Ŀ��
	{
		for (int i = 0; i <= rank_size4 - 2; i++)//�������У�������ð������
		{
			for (int j = i + 1; j <= rank_size4 - 1; j++)
			{
				dtemp4 = population_rank4[i].v_ul_objectives[0][objNo];//��ȡi�����Ŀ��ֵ
				if (dtemp4 > population_rank4[j].v_ul_objectives[0][objNo])//��j�����Ŀ��ֵ�Ƚ�
				{
					t4 = population_rank4[i];//��Ϊ�Ƕ��󻻣��Ҷ��������е����Լ���ǰĿ���µ�Ŀ��ֵҲ���ű䶯��
					population_rank4[i] = population_rank4[j];//���ö���t���������������ˣ�
					population_rank4[j] = t4;//����������Ŀ��ֵС�Ķ��󱻻���ǰ�棬Ŀ��ֵ��Ķ��󱻻�������
				}
			}
		}
	}

	vector<double>dist_two_point4;//�洢������֮���ŷ�Ͼ���
	double total_distance4 = 0;//�ܾ���
	for (int k = 0; k < population_rank4.size() - 1; k++)
	{
		double object_dis_14 = pow((population_rank4[k].v_ul_objectives[0][0] - population_rank4[k + 1].v_ul_objectives[0][0]), 2);
		double object_dis_24 = pow((population_rank4[k].v_ul_objectives[0][1] - population_rank4[k + 1].v_ul_objectives[0][1]), 2);
		double object_dis4 = object_dis_14 + object_dis_24;// + object_dis_3
		double diatance_two4 = sqrt(object_dis4);
		dist_two_point4.push_back(diatance_two4);
		total_distance4 = total_distance4 + diatance_two4;
	}
	double avr_distance4 = total_distance4 / dist_two_point4.size();//ƽ������
	double total_difference_distance4 = 0;//DV����
	for (int k = 0; k < dist_two_point4.size(); k++)
	{
		total_difference_distance4 = total_difference_distance4 + fabs(dist_two_point4[k] - avr_distance4);
	}
	DV_value4 = total_difference_distance4 / (dist_two_point4.size() * avr_distance4);
	//cout << "DVֵ��" << DV_value4 << endl;
}

void QPacking::C_metric5(vector <CIndividual>& r1_Chromo5, vector <CIndividual>& r2_Chromo5, double& C_value5)
{
	int dominant_number5 = 0;//����Ⱥ֧��ԭ��Ⱥ�еĸ��������
	for (int i = 0; i < r2_Chromo5.size(); i++)
	{
		for (int j = 0; j < r1_Chromo5.size(); j++)
		{
			int domRel5;
			domRelation_up5(r1_Chromo5[j], r2_Chromo5[i], domRel5);
			if (domRel5 == 1)
			{
				dominant_number5++;
				break;
			}
		}
	}
	C_value5 = (double)dominant_number5 / r2_Chromo5.size();
	//cout << "Cָ�꣺" << C_value1 << endl;
}

void QPacking::DV_metric5(vector <CIndividual>& r_Chromo5, double& DV_value5)
{
	vector <CIndividual> population_rank5;//���еķ�֧�����
	vector <CIndividual>().swap(population_rank5);//����swap�����ڴ�
	for (int i = 0; i < r_Chromo5.size(); i++)
	{
		if (r_Chromo5[i].upper_rank == 1)
		{
			population_rank5.push_back(r_Chromo5[i]);
		}
	}

	CIndividual t5;
	int rank_size5 = population_rank5.size();
	double dtemp5 = 0;//Ŀ��ֵ������
	for (int objNo = 0; objNo < number_of_objectives; objNo++)//����ÿ��Ŀ��
	{
		for (int i = 0; i <= rank_size5 - 2; i++)//�������У�������ð������
		{
			for (int j = i + 1; j <= rank_size5 - 1; j++)
			{
				dtemp5 = population_rank5[i].v_ul_objectives[0][objNo];//��ȡi�����Ŀ��ֵ
				if (dtemp5 > population_rank5[j].v_ul_objectives[0][objNo])//��j�����Ŀ��ֵ�Ƚ�
				{
					t5 = population_rank5[i];//��Ϊ�Ƕ��󻻣��Ҷ��������е����Լ���ǰĿ���µ�Ŀ��ֵҲ���ű䶯��
					population_rank5[i] = population_rank5[j];//���ö���t���������������ˣ�
					population_rank5[j] = t5;//����������Ŀ��ֵС�Ķ��󱻻���ǰ�棬Ŀ��ֵ��Ķ��󱻻�������
				}
			}
		}
	}

	vector<double>dist_two_point5;//�洢������֮���ŷ�Ͼ���
	double total_distance5 = 0;//�ܾ���
	for (int k = 0; k < population_rank5.size() - 1; k++)
	{
		double object_dis_15 = pow((population_rank5[k].v_ul_objectives[0][0] - population_rank5[k + 1].v_ul_objectives[0][0]), 2);
		double object_dis_25 = pow((population_rank5[k].v_ul_objectives[0][1] - population_rank5[k + 1].v_ul_objectives[0][1]), 2);
		double object_dis5 = object_dis_15 + object_dis_25;// + object_dis_3
		double diatance_two5 = sqrt(object_dis5);
		dist_two_point5.push_back(diatance_two5);
		total_distance5 = total_distance5 + diatance_two5;
	}
	double avr_distance5 = total_distance5 / dist_two_point5.size();//ƽ������
	double total_difference_distance5 = 0;//DV����
	for (int k = 0; k < dist_two_point5.size(); k++)
	{
		total_difference_distance5 = total_difference_distance5 + fabs(dist_two_point5[k] - avr_distance5);
	}
	DV_value5 = total_difference_distance5 / (dist_two_point5.size() * avr_distance5);
	//cout << "DVֵ��" << DV_value5 << endl;
}

void QPacking::C_metric6(vector <CIndividual>& r1_Chromo6, vector <CIndividual>& r2_Chromo6, double& C_value6)
{
	int dominant_number6 = 0;//����Ⱥ֧��ԭ��Ⱥ�еĸ��������
	for (int i = 0; i < r2_Chromo6.size(); i++)
	{
		for (int j = 0; j < r1_Chromo6.size(); j++)
		{
			int domRel6;
			domRelation_up6(r1_Chromo6[j], r2_Chromo6[i], domRel6);
			if (domRel6 == 1)
			{
				dominant_number6++;
				break;
			}
		}
	}
	C_value6 = (double)dominant_number6 / r2_Chromo6.size();
	//cout << "Cָ�꣺" << C_value1 << endl;
}

void QPacking::DV_metric6(vector <CIndividual>& r_Chromo6, double& DV_value6)
{
	vector <CIndividual> population_rank6;//���еķ�֧�����
	vector <CIndividual>().swap(population_rank6);//����swap�����ڴ�
	for (int i = 0; i < r_Chromo6.size(); i++)
	{
		if (r_Chromo6[i].upper_rank == 1)
		{
			population_rank6.push_back(r_Chromo6[i]);
		}
	}

	CIndividual t6;
	int rank_size6 = population_rank6.size();
	double dtemp6 = 0;//Ŀ��ֵ������
	for (int objNo = 0; objNo < number_of_objectives; objNo++)//����ÿ��Ŀ��
	{
		for (int i = 0; i <= rank_size6 - 2; i++)//�������У�������ð������
		{
			for (int j = i + 1; j <= rank_size6 - 1; j++)
			{
				dtemp6 = population_rank6[i].v_ul_objectives[0][objNo];//��ȡi�����Ŀ��ֵ
				if (dtemp6 > population_rank6[j].v_ul_objectives[0][objNo])//��j�����Ŀ��ֵ�Ƚ�
				{
					t6 = population_rank6[i];//��Ϊ�Ƕ��󻻣��Ҷ��������е����Լ���ǰĿ���µ�Ŀ��ֵҲ���ű䶯��
					population_rank6[i] = population_rank6[j];//���ö���t���������������ˣ�
					population_rank6[j] = t6;//����������Ŀ��ֵС�Ķ��󱻻���ǰ�棬Ŀ��ֵ��Ķ��󱻻�������
				}
			}
		}
	}

	vector<double>dist_two_point6;//�洢������֮���ŷ�Ͼ���
	double total_distance6 = 0;//�ܾ���
	for (int k = 0; k < population_rank6.size() - 1; k++)
	{
		double object_dis_16 = pow((population_rank6[k].v_ul_objectives[0][0] - population_rank6[k + 1].v_ul_objectives[0][0]), 2);
		double object_dis_26 = pow((population_rank6[k].v_ul_objectives[0][1] - population_rank6[k + 1].v_ul_objectives[0][1]), 2);
		double object_dis6 = object_dis_16 + object_dis_26;// + object_dis_3
		double diatance_two6 = sqrt(object_dis6);
		dist_two_point6.push_back(diatance_two6);
		total_distance6 = total_distance6 + diatance_two6;
	}
	double avr_distance6 = total_distance6 / dist_two_point6.size();//ƽ������
	double total_difference_distance6 = 0;//DV����
	for (int k = 0; k < dist_two_point6.size(); k++)
	{
		total_difference_distance6 = total_difference_distance6 + fabs(dist_two_point6[k] - avr_distance6);
	}
	DV_value6 = total_difference_distance6 / (dist_two_point6.size() * avr_distance6);
	//cout << "DVֵ��" << DV_value6 << endl;
}

void QPacking::C_metric7(vector <CIndividual>& r1_Chromo7, vector <CIndividual>& r2_Chromo7, double& C_value7)
{
	int dominant_number7 = 0;//����Ⱥ֧��ԭ��Ⱥ�еĸ��������
	for (int i = 0; i < r2_Chromo7.size(); i++)
	{
		for (int j = 0; j < r1_Chromo7.size(); j++)
		{
			int domRel7;
			domRelation_up7(r1_Chromo7[j], r2_Chromo7[i], domRel7);
			if (domRel7 == 1)
			{
				dominant_number7++;
				break;
			}
		}
	}
	C_value7 = (double)dominant_number7 / r2_Chromo7.size();
	//cout << "Cָ�꣺" << C_value1 << endl;
}

void QPacking::DV_metric7(vector <CIndividual>& r_Chromo7, double& DV_value7)
{
	vector <CIndividual> population_rank7;//���еķ�֧�����
	vector <CIndividual>().swap(population_rank7);
	for (int i = 0; i < r_Chromo7.size(); i++)
	{
		if (r_Chromo7[i].upper_rank == 1)
		{
			population_rank7.push_back(r_Chromo7[i]);
		}
	}

	CIndividual t7;
	int rank_size7 = population_rank7.size();
	double dtemp7 = 0;//Ŀ��ֵ������
	for (int objNo = 0; objNo < number_of_objectives; objNo++)//����ÿ��Ŀ��
	{
		for (int i = 0; i <= rank_size7 - 2; i++)//�������У�������ð������
		{
			for (int j = i + 1; j <= rank_size7 - 1; j++)
			{
				dtemp7 = population_rank7[i].v_ul_objectives[0][objNo];//��ȡi�����Ŀ��ֵ
				if (dtemp7 > population_rank7[j].v_ul_objectives[0][objNo])//��j�����Ŀ��ֵ�Ƚ�
				{
					t7 = population_rank7[i];//��Ϊ�Ƕ��󻻣��Ҷ��������е����Լ���ǰĿ���µ�Ŀ��ֵҲ���ű䶯��
					population_rank7[i] = population_rank7[j];//���ö���t���������������ˣ�
					population_rank7[j] = t7;//����������Ŀ��ֵС�Ķ��󱻻���ǰ�棬Ŀ��ֵ��Ķ��󱻻�������
				}
			}
		}
	}

	vector<double>dist_two_point7;//�洢������֮���ŷ�Ͼ���
	double total_distance7 = 0;//�ܾ���
	for (int k = 0; k < population_rank7.size() - 1; k++)
	{
		double object_dis_17 = pow((population_rank7[k].v_ul_objectives[0][0] - population_rank7[k + 1].v_ul_objectives[0][0]), 2);
		double object_dis_27 = pow((population_rank7[k].v_ul_objectives[0][1] - population_rank7[k + 1].v_ul_objectives[0][1]), 2);
		double object_dis7 = object_dis_17 + object_dis_27;
		double diatance_two7 = sqrt(object_dis7);
		dist_two_point7.push_back(diatance_two7);
		total_distance7 = total_distance7 + diatance_two7;
	}
	double avr_distance7 = total_distance7 / dist_two_point7.size();//ƽ������
	double total_difference_distance7 = 0;
	for (int k = 0; k < dist_two_point7.size(); k++)
	{
		total_difference_distance7 = total_difference_distance7 + fabs(dist_two_point7[k] - avr_distance7);
	}
	DV_value7 = total_difference_distance7 / (dist_two_point7.size() * avr_distance7);
	//cout << "DVֵ��" << DV_value7 << endl;
}
