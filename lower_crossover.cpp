#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"

void QPacking::lower_crossover(CIndividual& lower_fathIndiv, CIndividual& lower_mothIndiv, CIndividual& lower_chIndiv1, CIndividual& lower_chIndiv2)//����4�����󣺸��ף�ĸ�ף��Ӵ�1���Ӵ�2
{
	//cout << "���׵�����������Ϣ��" << endl;
	//for (int n = 0; n < number_of_jobs; n++)
	//{
	//	cout << lower_fathIndiv.v_chromosome2[n].job_number << " ";
	//}
	//cout << endl;

	//cout << "ĸ�׵�����������Ϣ��" << endl;
	//for (int n = 0; n < number_of_jobs; n++)
	//{
	//	cout << lower_mothIndiv.v_chromosome2[n].job_number << " ";
	//}
	//cout << endl;
	//system("pause");

	//////////////////////////////����ҵ����ִ��ѭ������///////////////////////////////////////////////////////////////////////
	vector <CChromosome>().swap(lower_chIndiv1.v_chromosome2);//����Ӵ�����
	vector <CChromosome>().swap(lower_chIndiv2.v_chromosome2);//����Ӵ�����
	for (int j = 0; j < number_of_jobs; j++)//�Ӵ������ʼ����һ��ʼ���ȴ��������ٶԶ����factory_numberȫ����ֵΪ0
	{
		CChromosome	tt5;
		tt5.job_number = 0;
		lower_chIndiv1.v_chromosome2.push_back(tt5);
		CChromosome	tt6;
		tt6.job_number = 0;
		lower_chIndiv2.v_chromosome2.push_back(tt6);
	}
	int position_number = rand() % number_of_jobs;
	//cout << "position_number = " << position_number << endl;
	int start_job = lower_fathIndiv.v_chromosome2[position_number].job_number;
	//cout << "start_job = " << start_job << endl;
	int fa_p_index = position_number;
	vector<int>v_fa_p_index;//���游��Ⱦɫ���� �� �ϵĻ���λ��
	v_fa_p_index.push_back(fa_p_index);
	int next_job = lower_mothIndiv.v_chromosome2[fa_p_index].job_number;
	//cout << "next_job = " << next_job << endl;
	while (next_job != start_job)//Ѱ�� ���ϵ�job��λ������
	{
		for (int j = 0; j < number_of_jobs; j++)
		{
			if (lower_fathIndiv.v_chromosome2[j].job_number == next_job)
			{
				fa_p_index = j;
				v_fa_p_index.push_back(fa_p_index);
				//cout << "fa_p_index = " << fa_p_index << endl;
			}
		}
		next_job = lower_mothIndiv.v_chromosome2[fa_p_index].job_number;
		//cout << "next_job = " << next_job << endl;
	}

	for (int j = 0; j < v_fa_p_index.size(); j++)//�Ӵ�1�������׻��ϵĻ���
	{
		int fa_index = v_fa_p_index[j];
		//cout << "fa_index = " << fa_index << endl;
		lower_chIndiv1.v_chromosome2[fa_index].job_number = lower_fathIndiv.v_chromosome2[fa_index].job_number;
	}
	//system("pause");
	vector<int>v_fa_jobs;//��ȡ����Ⱦɫ���Ϸǻ��Ļ���
	bool pd_value;
	for (int j = 0; j <  number_of_jobs; j++)
	{
		for (int k = 0; k < v_fa_p_index.size(); k++)
		{
			int fa_p_index = v_fa_p_index[k];
			if (j != fa_p_index)
			{
				pd_value = true;
			}
			else
			{
				pd_value = false;
				break;
			}
		}
		if (pd_value == true)
		{
			v_fa_jobs.push_back(lower_fathIndiv.v_chromosome2[j].job_number);
		}
	}
	//cout << "���ǻ�����" << endl;
	//for (int j = 0; j < v_fa_jobs.size(); j++)
	//{
	//	cout << v_fa_jobs[j] << " ";
	//}
	//cout << endl;


	vector<int>v_mo_jobs;//��ȡĸ��Ⱦɫ���Ϸǻ��ϵĻ���
	bool panduan;
	panduan = false;
	for (int j = 0; j < number_of_jobs; j++)
	{
		for (int k = 0; k < v_fa_p_index.size(); k++)
		{
			if (lower_mothIndiv.v_chromosome2[j].job_number != lower_fathIndiv.v_chromosome2[v_fa_p_index[k]].job_number)
			{
				panduan = true;
			}
			else
			{
				panduan = false;
				break;
			}
		}
		if (panduan == true)
		{
			v_mo_jobs.push_back(lower_mothIndiv.v_chromosome2[j].job_number);
		}
	}
	//cout << "ĸ�ǻ�����" << endl;
	//for (int j = 0; j < v_mo_jobs.size(); j++)
	//{
	//	cout << v_mo_jobs[j] << " ";
	//}
	//cout << endl;

	int p_index = 0;
	for (int j = 0; j < number_of_jobs; j++)//���Ӵ�1��ȱ�ٵķǻ�������и�ֵ������ĸ�׵ķǻ�����
	{
		if (lower_chIndiv1.v_chromosome2[j].job_number == 0)
		{
			lower_chIndiv1.v_chromosome2[j].job_number = v_mo_jobs[p_index];
			p_index++;
			//cout << "p_index = " << p_index << endl;
		}
	}

	for (int j = 0; j < v_fa_p_index.size(); j++)//�Ӵ�2����ĸ�׻��ϵĻ���
	{
		int fa_index = v_fa_p_index[j];
		lower_chIndiv2.v_chromosome2[fa_index].job_number = lower_mothIndiv.v_chromosome2[fa_index].job_number;
	}
	p_index = 0;
	for (int j = 0; j <  number_of_jobs; j++)//���Ӵ�2��ȱ�ٵķǻ�������и�ֵ�����Ը��׵ķǻ�����
	{
		if (lower_chIndiv2.v_chromosome2[j].job_number == 0)
		{
			lower_chIndiv2.v_chromosome2[j].job_number = v_fa_jobs[p_index];
			p_index++;
			//cout << "p_index = " << p_index << endl;
		}
	}
	//cout << "CX����������Ӵ����������У�" << endl;
	//for (int n = 0; n < number_of_jobs; n++)
	//{
	//	cout << lower_chIndiv1.v_chromosome2[n].job_number << " ";
	//}
	//cout << endl;
	//for (int n = 0; n < number_of_jobs; n++)
	//{
	//	cout << lower_chIndiv2.v_chromosome2[n].job_number << " ";
	//}
	//cout << endl;

	vector<int>().swap(v_fa_p_index);
	vector<int>().swap(v_mo_jobs);
	vector<int>().swap(v_fa_jobs);
	//system("pause");
}