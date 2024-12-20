#include <iomanip>
#include "Qpacking.h"
#include "Individual.h"
#include <cmath>
#include<algorithm>
#include <cassert>

// ����: ��ʼʱ�䣬����ʱ��
// ���: �ӹ��ɱ�
double calculate_cost(double start_time, double end_time)
{
	//cout << "start_time = " << start_time << endl;
	//cout << "end_time = " << end_time << endl;
	assert(start_time <= end_time && start_time >= 0);
	double energy_consumption_rate = 25 / pow(end_time - start_time, 2);
	//cout << "energy_consumption_rate = "<< energy_consumption_rate << endl;

	// ʱ�η�Ϊ[0, 7), [7, 11), [11, 17), [17, 21), [21, 24)
	// EPIΪ 5�� 8��10�� 8�� 5 
	auto get_interval_length = [](double start_time, double end_time) -> pair<double, double>
		{
			double maxInterval = end_time - start_time;
			//cout << "maxInterval = " << maxInterval << endl;
			double day_time = fmod(start_time, 24);
			//cout << "day_time = " << day_time << endl;
			if (day_time < 7)
				return { min(7 - day_time, maxInterval), 5 };
			else if (day_time < 11)
				return { min(11 - day_time, maxInterval), 8 };
			else if (day_time < 17)
				return { min(17 - day_time, maxInterval), 10 };
			else if (day_time < 21)
				return { min(21 - day_time, maxInterval), 8 };
			else
				return { min(24 - day_time, maxInterval), 5 };
		};

	double total_cost_value = 0;
	while (start_time < end_time)//����ÿһ��������õ�ɱ�
	{
		auto tmp = get_interval_length(start_time, end_time);
		double interval_length = tmp.first, EPI = tmp.second;
		//cout << "interval_length = " << interval_length << endl;
		//cout << "EPI = " << EPI << endl;

		total_cost_value += energy_consumption_rate * EPI * interval_length;
		//cout << "total_cost_value = " << total_cost_value << endl;
		start_time += interval_length;
		//cout << "start_time = " << start_time << endl;
	}
	//cout << "total_cost_value = " << total_cost_value << endl;
	//system("pause");
	return total_cost_value;
}

// ���룺ÿ̨������ÿ������ļӹ���ʼʱ��ͽ���ʱ��
// �����ÿ̨�����ļӹ��ɱ��ܺ�
double calculate_cost(const vector<vector<double>>& m_s_t, const vector<vector<double>>& m_f_t)
{
	assert(m_s_t.size() == m_f_t.size());
	int mechine_num = static_cast<int>(m_s_t.size());
	//cout << "mechine_num =" << mechine_num << endl;
	double total_cost_value = 0;
	for (int i = 0; i < mechine_num; i++)
	{
		assert(m_s_t[i].size() == m_f_t[i].size());
		int operation_num = static_cast<int>(m_s_t[i].size());
		//cout << "operation_num =" << operation_num << endl;
		for (int j = 0; j < operation_num; j++)
		{
			total_cost_value += calculate_cost(m_s_t[i][j], m_f_t[i][j]);
			//cout << "total_cost_value =" << total_cost_value << endl;
			//system("pause");
		}
	}
	return total_cost_value;
}


void QPacking::evaluate_FJSP(CIndividual& t)//������Ӧ��
{
	//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//{
	//	cout <<t.v_chromosome1[u].operation_number << " ";
	//}
	//cout << endl;
	//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//{
	//	cout << t.v_chromosome1[u].operation_index << " ";
	//}
	//cout << endl;
	//for (int u = number_of_jobs * number_of_operations; u < t.v_chromosome1.size(); u++)
	//{
	//	cout << t.v_chromosome1[u].machine_number << " ";
	//}
	//cout << endl;

	////step1����ȡÿ�����������Ĵ��ӹ�����
	vector <vector<CChromosome>> v_factory_operation;
	for (int f = 0; f < 1; f++)
	{
		vector<CChromosome> v;
		v_factory_operation.push_back(v);
	}
	for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	{
		int j_num = t.v_chromosome1[j].job_number;//�ҳ��ù��������job
		//cout << "j_num = " << j_num << endl;	
		int o_num = t.v_chromosome1[j].operation_index;//�ҳ��ù����ǵڼ�������
		//cout << "o_num = " << o_num << endl;
		int m_num_index = number_of_jobs * number_of_operations + (j_num - 1) * number_of_operations + o_num - 1;
		int m_num = t.v_chromosome1[m_num_index].machine_number;//�ҵ���job�ù������������
		//cout << "m_num = " << m_num << endl;
		//system("pause");
		CChromosome ttt;
		ttt.job_number = j_num;
		ttt.operation_index = o_num;
		ttt.machine_number = m_num;
		v_factory_operation[0].push_back(ttt);
	}
	//cout << "ÿ�����������Ĺ������Ϣ(�������У��������ţ����������Ļ���)��" << endl;
	//for (int f = 0; f < v_factory_operation.size(); f++)
	//{
	//	cout << "F" << f+1 << "---opera_seque_job��";
	//	for (int n = 0; n < v_factory_operation[f].size(); n++)
	//	{		
	//		cout << v_factory_operation[f][n].job_number << " ";
	//	}
	//	cout << endl;
	//	cout << "F" << f+1 << "---operation_index��";
	//	for (int n = 0; n < v_factory_operation[f].size(); n++)
	//	{
	//		cout << v_factory_operation[f][n].operation_index << " ";
	//	}
	//	cout << endl;
	//	cout << "F" << f+1 << "----machine_number��";
	//	for (int n = 0; n < v_factory_operation[f].size(); n++)
	//	{
	//		cout << v_factory_operation[f][n].machine_number << " ";
	//	}
	//	cout << endl <<endl;
	//}
	//cout << endl;
	//system("pause");

	////step2��ÿ��job��ÿ�������ʵ�ʼӹ�ʱ��
	p_c_fjsp_processing_time = new int** [number_of_operations];//��һ������number_of_factories��Ԫ�ص�����1
	for (int i = 0; i < number_of_operations; i++)
	{
		p_c_fjsp_processing_time[i] = new int* [number_of_machines];//����1�� ÿ��Ԫ�� ��ָ��һ�� ����number_of_machines��Ԫ�ص�����2
		for (int j = 0; j < number_of_machines; j++)
		{
			p_c_fjsp_processing_time[i][j] = new int[number_of_jobs];
		}
	}
	for (int i = 0; i < number_of_operations; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			for (int k = 0; k < number_of_jobs; k++)
			{
				p_c_fjsp_processing_time[i][j][k] = round(p_b_fjsp_processing_time[i][j][k] / (p_machine_adjust_time[j] * 10));//round���������뺯��
				//cout << p_c_fjsp_processing_time[i][j][k] << " ";
			}
		   //cout << endl;
		}
		//cout << endl;
	}
	//cout << endl;
	//system("pause");


	////step3:��ÿ�������Ļ����ӹ��Ĺ����job�š���Ӧ�Ĺ���š�����Ŀ�ʼ���깤ʱ��
	double** p_operation_completion_time;
	p_operation_completion_time = new double* [number_of_jobs];
	for (int j = 0; j < number_of_jobs; j++)
	{
		p_operation_completion_time[j] = new double[number_of_operations];
	}
	for (int j = 0; j < number_of_jobs; j++)//�Կ��ٵ���Ⱥ��ʼ��
	{
		for (int o = 0; o < number_of_operations; o++)
		{
			p_operation_completion_time[j][o] = 0;
		}
	}
	//cout << endl;
	double* p_completion_time = new double[number_of_jobs];
	for (int j = 0; j < number_of_jobs; j++)
	{
		p_completion_time[j] = 0;
	}
	//system("pause");

	//cout << "ÿ��job���и��깤ʱ�䣺" << endl;
	//for (int j = 0; j < t.v_job_packing_finish_time.size(); j++)
	//{
	//	cout << t.v_job_packing_finish_time[j] << " ";
	//}
	//cout << endl;
	//system("pause");

	vector<vector<int> > M_J(number_of_machines); //�û����ӹ��Ĺ����Ӧ����ҵ���
	vector<vector<int> > M_O(number_of_machines);//�û����ӹ��Ĺ����Ӧ�ĵڼ�������
	vector<vector<double> > m_s_t(number_of_machines);//�û����ӹ���ÿ������Ŀ�ʼʱ��
	vector<vector<double> > m_f_t(number_of_machines);//�û����ӹ���ÿ��������깤ʱ��
	for (int i = 0; i < 1; i++)
	{
		for (int o = 0; o < v_factory_operation[i].size(); o++)
		{		
			int Job_index = v_factory_operation[i][o].job_number;//������ҵ��
			//cout << "Job_index = " << Job_index << endl;
			int Operation_index = v_factory_operation[i][o].operation_index;//��������ҵ�е�˳��
			//cout << "Operation_index =" << Operation_index << endl;
			int machine_index = v_factory_operation[i][o].machine_number;//�ù������ڻ���
			//cout << "machine_index =" << machine_index << endl;
			if (Operation_index == 1)//����ҵ�ĵ�һ������
			{
				//cout << "�ù����ǵ�ǰ��ҵ�ĵ�һ�������俪ʼʱ����Ҫ�ݸ���ҵ����������ʱ��" << endl;
				double j_pack_finish_time = t.v_job_packing_finish_time[Job_index - 1];
				//cout << Job_index<< "��j_pack_finish_time = " << j_pack_finish_time << endl;
				if (M_J[machine_index - 1].empty())//�û�����δ�й���
				{
					M_J[machine_index - 1].push_back(Job_index);
					M_O[machine_index - 1].push_back(Operation_index);	
					//cout << "��ǰ������δ�й�����мӹ�����ô��ǰ��ҵ���׵�����ʼʱ�� = ����ҵ�������깤ʱ��" << endl;
					m_s_t[machine_index - 1].push_back(j_pack_finish_time);//����ҵ�������깤ʱ��
					//cout << "mst_time = " << j_pack_finish_time << endl;
					m_f_t[machine_index - 1].push_back(j_pack_finish_time + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
					//cout << "mft_time = " << j_pack_finish_time + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] << endl;
				}
				else if (!M_J[machine_index - 1].empty())
				{
					//cout << "��ǰ���������й���Ҫ����ܷ�������ʱ��" << endl;
					int successinsert = 0;//�Ƿ�����ȥ��
					for (int k = 0; k < M_J[machine_index - 1].size(); k++)
					{
						if (k == 0)//��ǰ�����ļӹ��ĵ�һ������
						{
							//cout << "����Ƿ��ܲ����һ�������ǰ��" << endl;
							double Itime = m_s_t[machine_index - 1][k] - j_pack_finish_time;
							//cout << "Itime = " << Itime << endl;
							if (p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= Itime)
							{
								M_J[machine_index - 1].insert(M_J[machine_index - 1].begin() + k, Job_index);
								M_O[machine_index - 1].insert(M_O[machine_index - 1].begin() + k, Operation_index);
								m_s_t[machine_index - 1].insert(m_s_t[machine_index - 1].begin() + k, j_pack_finish_time);
								//cout << "mst_time = " << j_pack_finish_time << endl;
								m_f_t[machine_index - 1].insert(m_f_t[machine_index - 1].begin() + k, m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
								//cout << "mft_time = " << m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] << endl;
								successinsert = 1;
								break;
							}
						}
						else if (k != 0)//��ǰ�����ļӹ��ĺ��湤��
						{
							//cout << "k = " << " k" << endl;
							//cout << "����Ƿ��ܲ�����湤���ǰ�棺����Ҫ�����Ƿ��п���ʱ�䣬��Ҫ���ǵ���ҵ�������깤ʱ��" << endl;
							double Itime = m_s_t[machine_index - 1][k] - m_f_t[machine_index - 1][k - 1];
							//cout << "Itime = " << Itime << endl;
							////��ǰ������֮���п���ʱ������ҵ������ʱ��ܺ�һ������Ŀ�ʼʱ�䣬��ô�ܲ��뵫���������					
							//��һ���ǣ�����ҵ�������깤ʱ���ǰһ��������깤ʱ�䣬��ô��ʱ��ҵ���׵�����Ŀ�ʼʱ��=ǰһ��������깤ʱ��
							//�ڶ����ǣ�����ҵ�������깤ʱ���ǰһ��������깤ʱ�� �� ��ҵ���׵�����ӹ�ʱ��ܺ�һ��������깤ʱ��-��ҵ�������깤ʱ�䣬��ô��ʱ��ҵ���׵�����Ŀ�ʼʱ�� = ��ҵ�������깤ʱ��
							if (p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= Itime && j_pack_finish_time <= m_s_t[machine_index - 1][k])
							{
								if (j_pack_finish_time <= m_f_t[machine_index - 1][k - 1])
								{
									//cout << "��һ�����" << endl;
									M_J[machine_index - 1].insert(M_J[machine_index - 1].begin() + k, Job_index);
									M_O[machine_index - 1].insert(M_O[machine_index - 1].begin() + k, Operation_index);
									m_s_t[machine_index - 1].insert(m_s_t[machine_index - 1].begin() + k, m_f_t[machine_index - 1][k - 1]);
									//cout << "mst_time = " << m_f_t[machine_index - 1][k - 1] << endl;
									m_f_t[machine_index - 1].insert(m_f_t[machine_index - 1].begin() + k, m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
									//cout << "mft_time = " << m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] << endl;
									successinsert = 1;
									break;
								}
								else if (j_pack_finish_time >= m_f_t[machine_index - 1][k - 1] && j_pack_finish_time + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= m_s_t[machine_index - 1][k] )
								{
									//cout << "�ڶ������" << endl;
									M_J[machine_index - 1].insert(M_J[machine_index - 1].begin() + k, Job_index);
									M_O[machine_index - 1].insert(M_O[machine_index - 1].begin() + k, Operation_index);
									m_s_t[machine_index - 1].insert(m_s_t[machine_index - 1].begin() + k, j_pack_finish_time);
									//cout << "mst_time = " << j_pack_finish_time << endl;
									m_f_t[machine_index - 1].insert(m_f_t[machine_index - 1].begin() + k, m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
									//cout << "mft_time = " << m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] << endl;
									successinsert = 1;
									break;
								}
							}


						}
					}
					if (successinsert != 1) //δ���룬�������
					{
						//cout << "û�п���ʱ����Բ壬ֱ�ӷ��ڵ�ǰ�������һ������ĺ��棬��Ҫ�������������깤ʱ��Լ��" << endl;
						M_J[machine_index - 1].push_back(Job_index);
						M_O[machine_index - 1].push_back(Operation_index);
						double max_value = max(m_f_t[machine_index - 1][m_f_t[machine_index - 1].size() - 1], j_pack_finish_time);
						//cout << "max_value = " << max_value << endl;
						m_s_t[machine_index - 1].push_back(max_value);
						//cout << "mst_time = " << max_value << endl;
						m_f_t[machine_index - 1].push_back(max_value + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
						//cout << "mft_time = " << max_value + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] << endl;
					}
				}
			}
			//������ҵ�ĵ�һ������
			else if (Operation_index != 1)
			{
				//�ҵ��ù����ǰ����Ļ����ţ��洢ǰ�����������������ϵĽ���ʱ��
				int find_index = number_of_jobs * number_of_operations + (Job_index - 1) * number_of_operations + (Operation_index - 1) - 1;
				//cout << "find_index = " << find_index << endl;
				int mach = t.v_chromosome1[find_index].machine_number;//ǰ����Ļ�����
				//cout << "mach = " << mach << endl;
				//�ҵ��ù����ǰ�������俪ʼʱ�����ǰ������깤ʱ��
				double finishtime = 0;
				for (int s = 0; s < M_J[mach - 1].size(); s++)
				{
					if (M_J[mach - 1][s] == Job_index)
					{
						if (M_O[mach - 1][s] == Operation_index - 1)
						{
							finishtime = m_f_t[mach - 1][s];
						}
					}
				}
				//cout << "finishtime = " << finishtime << endl;
				if (M_J[machine_index - 1].empty()) //�û�����δ�й���		
				{
					//cout << "�û����޹���" << endl;
					m_s_t[machine_index - 1].push_back(finishtime);
					//cout << "msttime = " << finishtime << endl;
					m_f_t[machine_index - 1].push_back(m_s_t[machine_index - 1][m_s_t[machine_index - 1].size() - 1] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
					//cout << "mfttime = " << m_s_t[machine_index - 1][m_s_t[machine_index - 1].size() - 1] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] << endl;
					M_J[machine_index - 1].push_back(Job_index);
					M_O[machine_index - 1].push_back(Operation_index);
				}
				else if (!M_J[machine_index - 1].empty()) //�û��������й���
				{
					int successinsert = 0;//�Ƿ�����ȥ��
					vector<double>Itime;//�û�����ÿ������֮��Ŀ���ʱ��
					for (int k = 0; k < M_J[machine_index - 1].size(); k++)
					{
						if (finishtime < m_s_t[machine_index - 1][k])
						{
							if (k == 0)
							{
								//cout << "����һ������" << endl;
								//double Itime = m_s_t[machine_index - 1][k] - 0;
								if (finishtime + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= m_s_t[machine_index - 1][k])
								{
									m_s_t[machine_index - 1].insert(m_s_t[machine_index - 1].begin() + k, finishtime);
									//cout << "msttime = " << finishtime << endl;
									m_f_t[machine_index - 1].insert(m_f_t[machine_index - 1].begin() + k, m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
									//cout << "mfttime = " << m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] << endl;
									M_J[machine_index - 1].insert(M_J[machine_index - 1].begin() + k, Job_index);
									M_O[machine_index - 1].insert(M_O[machine_index - 1].begin() + k, Operation_index);
									successinsert = 1;
									break;
								}
							}
							else if (k != 0)
							{
								//cout << "�����湤��" << endl;
								double Itime = m_s_t[machine_index - 1][k] - m_f_t[machine_index - 1][k - 1];
								//cout << "Itime = " << Itime << endl;
								if (p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= Itime)
								{
									if (finishtime <= m_f_t[machine_index - 1][k - 1])
									{
										//cout << "���1��" << endl;
										m_s_t[machine_index - 1].insert(m_s_t[machine_index - 1].begin() + k, m_f_t[machine_index - 1][k - 1]);
										//cout << "msttime = " << m_f_t[machine_index - 1][k - 1] << endl;
										m_f_t[machine_index - 1].insert(m_f_t[machine_index - 1].begin() + k, m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
										//cout << "mfttime = " << m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] << endl;
										M_J[machine_index - 1].insert(M_J[machine_index - 1].begin() + k, Job_index);
										M_O[machine_index - 1].insert(M_O[machine_index - 1].begin() + k, Operation_index);
										successinsert = 1;
										break;
									}
									else if (finishtime > m_f_t[machine_index - 1][k - 1] && finishtime + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= m_s_t[machine_index - 1][k])
									{
										//cout << "���2��" << endl;
										m_s_t[machine_index - 1].insert(m_s_t[machine_index - 1].begin() + k, finishtime);
										//cout << "msttime = " << finishtime << endl;
										m_f_t[machine_index - 1].insert(m_f_t[machine_index - 1].begin() + k, m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
										//cout << "mfttime = " << m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] << endl;
										M_J[machine_index - 1].insert(M_J[machine_index - 1].begin() + k, Job_index);
										M_O[machine_index - 1].insert(M_O[machine_index - 1].begin() + k, Operation_index);
										successinsert = 1;
										break;
									}
								}
							}
						}
					}
					if (successinsert != 1)
					{
						//cout << "�޿��У�ֱ�Ӳ���󣬵�Ҫ���ǿ�ʼʱ��" << endl;
						//cout << "m_f_t[machine_index - 1][m_f_t[machine_index - 1].size() - 1] = " << m_f_t[machine_index - 1][m_f_t[machine_index - 1].size() - 1] << endl;
						//cout << "finishtime = " << finishtime << endl;
						double max_value = max(m_f_t[machine_index - 1][m_f_t[machine_index - 1].size() - 1], finishtime);
						//cout << "max_value = " << max_value << endl;
						m_s_t[machine_index - 1].push_back(max_value);
						//cout << "msttime = " << max_value << endl;
						m_f_t[machine_index - 1].push_back(m_s_t[machine_index - 1][m_s_t[machine_index - 1].size() - 1] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
						//cout << "mfttime = " << m_s_t[machine_index - 1][m_s_t[machine_index - 1].size() - 1] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] << endl;
						M_J[machine_index - 1].push_back(Job_index);
						M_O[machine_index - 1].push_back(Operation_index);
					}
				}
			}
			//system("pause");
		}
	}
	////���������ÿ��job��ÿ�������ڲ�ͬ�����ϵ��깤ʱ��
	//cout << "ÿ̨�����ӹ��Ĺ����Ӧ����ҵ���" << endl;
	//for (int mj = 0; mj < M_J.size(); mj++)
	//{
	//	for (int mk = 0; mk < M_J[mj].size(); mk++)
	//	{
	//		cout << M_J[mj][mk] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//cout << "ÿ̨�����ӹ��Ĺ����Ӧ�Ĺ������" << endl;
	//for (int mj = 0; mj < M_O.size(); mj++)
	//{
	//	for (int mk = 0; mk < M_O[mj].size(); mk++)
	//	{
	//		cout << M_O[mj][mk] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//cout << "ÿ̨�����ӹ��Ĺ���Ŀ�ʼʱ��" << endl;
	//for (int mj = 0; mj < m_s_t.size(); mj++)
	//{
	//	for (int mk = 0; mk < m_s_t[mj].size(); mk++)
	//	{
	//		cout << m_s_t[mj][mk] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//cout << "ÿ̨�����ӹ��Ĺ���Ľ���ʱ��" << endl;//���������������ҵ���������깤ʱ��Ĺ������ڵĻ������Լ�λ�ú�
	int max_operation_index = 0;
	int max_machine_index = 0;
	int max_position_index = 0;
	int max_operation_value = 0;
	for (int mj = 0; mj < m_f_t.size(); mj++)
	{
		for (int mk = 0; mk < m_f_t[mj].size(); mk++)
		{
			//cout << m_f_t[mj][mk] << " ";
			if (m_f_t[mj][mk] > max_operation_value)
			{
				max_operation_value = m_f_t[mj][mk];
				max_operation_index = M_J[mj][mk] - 1;
				max_machine_index = mj;
				max_position_index = mk;
			}
		}
		//cout << endl;
	}
	//cout << endl;
	//cout << "max_operation_index = " << max_operation_index << endl;
	//cout << "max_machine_index = " << max_machine_index << endl;
	//cout << "max_position_index = " << max_position_index << endl;
	//cout << "max_operation_value = " << max_operation_value << endl;
	//system("pause");
	////step4����ÿ��job��ÿ��������깤ʱ��
	for (int u = 0; u < M_J.size(); u++)
	{
		for (int v = 0; v < M_J[u].size(); v++)
		{
			int current_job_number = M_J[u][v];
			int current_job_operation_index = M_O[u][v];
			p_operation_completion_time[current_job_number - 1][current_job_operation_index - 1] = m_f_t[u][v];
		}
		//cout << endl;
	}
	//cout << endl;

	////step5����ÿ��job�ĵ��깤ʱ��
	for (int w = 0; w < number_of_jobs; w++)
	{
		p_completion_time[w] = p_operation_completion_time[w][number_of_operations - 1];
		//cout << p_completion_time[w] << endl;
	}
	//system("pause");

	////step6����ÿ���������깤ʱ��
	//cout << "ÿ��������������ҵ��" << endl;
	vector<vector<double>> v_order_product_time;
	for (int i = 0; i < v_order_product.size(); i++)
	{
		vector<double> v;
		for (int j = 0; j < v_order_product[i].size(); j++)
		{
			//cout << v_order_product[i][j] << " ";
			int product_index = v_order_product[i][j] - 1;
			//cout << "product_index = " << product_index << endl;
			double finish_time = p_completion_time[product_index];
			//cout << "finish_time = " << finish_time << endl;
			v.push_back(finish_time);
		}
		//cout << endl;
		v_order_product_time.push_back(v);
	}
	//cout << endl;
	//system("pause");
	
	p_order_completion_time = new double[number_of_orders];
	for (int j = 0; j < number_of_orders; j++)
	{
		p_order_completion_time[j] = 0;
	}
	//cout << "ÿ��������������ҵ�깤ʱ�䣺" << endl;
	for (int i = 0; i < number_of_orders; i++)
	{
		double max_order_value = 0;
		for (int j = 0; j < v_order_product_time[i].size(); j++)
		{
			//cout << v_order_product_time[i][j] << " ";
			if (v_order_product_time[i][j] > max_order_value)
			{
				max_order_value = v_order_product_time[i][j];
			}
		}
		p_order_completion_time[i] = max_order_value;
		//cout << endl;
	}
	//cout << endl;
	//cout << "ÿ���������깤ʱ��" << endl;
	//for (int i = 0; i < number_of_orders; i++)
	//{
	//	cout << p_order_completion_time[i] << " ";
	//}
	//cout << endl;
	//system("pause");

	/////step7����total_tardiness��total_cost
	double total_tardiness = 0;
	vector<int> v_order_tardiness;
	for (int i = 0; i < number_of_orders; i++)
	{
		//cout << "i = " << i << endl;
		int order_tardiness = 0;
		if (p_order_completion_time[i] > p_order_due_time[i])
		{
			order_tardiness = p_order_completion_time[i] - p_order_due_time[i];
			total_tardiness += order_tardiness;
			//cout << "order_tardiness = " << order_tardiness << endl;
			//cout << "total_tardiness = " << total_tardiness << endl;
		}
		v_order_tardiness.push_back(order_tardiness);
	}
	//cout << "total_tardiness = " << total_tardiness << endl;
	//system("pause");
	int max_tardiness = v_order_tardiness[0];
	int max_order_index = 0;
	//cout << "ÿ��������tardiness��" << endl;
	for (int i = 0; i < v_order_tardiness.size(); i++)
	{
		//cout << v_order_tardiness[i] << " ";
		if (max_tardiness < v_order_tardiness[i])
		{
			max_tardiness = v_order_tardiness[i];
			max_order_index = i;
		}
	}
	//cout << "max_tardiness = " << max_tardiness << endl;
	//cout << "max_order_index = " << max_order_index << endl;
	//cout << endl;

	int max_product_time = v_order_product_time[max_order_index][0];
	int max_product_index = 0;
	for (int i = 0; i < v_order_product_time[max_order_index].size(); i++)
	{
		//cout << v_order_product_time[max_order_index][i] << " ";
		if (max_product_time < v_order_product_time[max_order_index][i])
		{
			max_product_time = v_order_product_time[max_order_index][i];
			max_product_index = v_order_product[max_order_index][i] - 1;
		}
	}
	//cout << "max_product_time = " << max_product_time << endl;
	//cout << "max_product_index = " << max_product_index << endl;
	//cout << endl;
	//system("pause");
	t.max_tardiness_job_index = max_product_index;
	t.total_tardiness = total_tardiness;
	//cout << "�ϲ�FJSP�����ӳ�total_tardiness = " << t.total_tardiness << endl;

	auto total_cost = calculate_cost(m_s_t,m_f_t);
	t.total_cost = total_cost;
	//cout << "�ϲ�FJSP���ܳɱ�total_cost = " << t.total_cost << endl;
	//system("pause");


	/*********************************��ȡFJSP�ؼ�·��***************************************************/
	vector<int>Job;//�ؼ�·������ҵ��ţ�����
	vector<int>Operation;//�ؼ�·����ҵ�Ĺ����ţ�����
	vector<int>Machine;//�ؼ�·����ҵ�Ĺ������ڵĻ��������ţ�����
	vector<double>s_t;//�ؼ�·����ҵ�Ĺ���Ŀ�ʼʱ�䣨����
	vector<double>f_t;//�ؼ�·����ҵ�Ĺ���Ľ���ʱ�䣨����
	vector<int>().swap(t.Product_C);//�����׶εĹؼ�·����ʼ��������
	Job.push_back(M_J[max_machine_index][max_position_index]);
	Operation.push_back(M_O[max_machine_index][max_position_index]);
	Machine.push_back(max_machine_index);
	s_t.push_back(m_s_t[max_machine_index][max_position_index]);
	f_t.push_back(m_f_t[max_machine_index][max_position_index]);
	int max_job_index = M_J[max_machine_index][max_position_index] - 1;
	//cout << "max_job_index = " << max_job_index << endl;//�����������깤ʱ������job
	vector<double> v_mach_start_time;//����ÿ̨�����Ŀ�ʼ�ӹ�ʱ��
	for (int u = 0; u < m_s_t.size(); u++)
	{
		v_mach_start_time.push_back(m_s_t[u][0]);
	}
	double job_first_start_time = *min_element(v_mach_start_time.begin(), v_mach_start_time.end());//�����Ŀ�ʼ�ӹ�ʱ��
	//cout << "job_first_start_time = " << job_first_start_time << endl;
	while (m_s_t[max_machine_index][max_position_index] > job_first_start_time)
	{
		if (max_position_index == 0)
		{
			//cout << "��Ҫ�жϵ�ǰ�����Ƿ�������job�ĵ�һ������" << endl;
			int count_operation_index = M_O[max_machine_index][max_position_index];
			//cout << "count_operation_index = " << count_operation_index << endl;
			max_job_index = M_J[max_machine_index][max_position_index] - 1;
			//cout << "max_job_index = " << max_job_index << endl;
			if (count_operation_index == 1 && m_s_t[max_machine_index][max_position_index] == t.v_job_packing_finish_time[max_job_index])
			{
				//cout << "��ǰ����������job�ĵ�һ�������Ҹù���Ŀ�ʼʱ��=����job����������ʱ��" << endl;
				//cout << "Ѱ�������׶εĹؼ�·����" << endl;
				//cout << "��ǰ�����ʵ������˳���깤ʱ�䣺" << endl;
				for (int pp = 0; pp < t.v_real_packing_route.size(); pp++)
				{
					//cout << "(" << t.v_real_packing_route[pp].first << ", " << t.v_real_packing_route[pp].second << ") ";
					if (t.v_real_packing_route[pp].first - 1 != max_job_index)
					{
						t.Product_C.push_back(t.v_real_packing_route[pp].first - 1);
					}
					else
					{
						t.Product_C.push_back(max_job_index);
						break;
					}
				}
				//cout << endl;
				break;////ֱ������
			}
			else
			{
				//cout << "��ǰ����������job�ĵ�һ��������ôѰ������job����һ������" << endl;
				int break_2 = 0;
				int Sum_number = 0;
				//��ȡ��ǰ��ҵǰ�滹�ж��ٵ�����,����ǰ��ҵ�����3 ��ô����ҵǰ����У�3-1��*number_of_operations������
				for (int r = 0; r < M_J[max_machine_index][max_position_index] - 1; r++)
				{
					Sum_number = Sum_number + number_of_operations;
				}
				//��ȡ��ǰ��ҵ�ؼ������ǰһ�����������Ļ������
				int MACHINE = t.v_chromosome1[number_of_jobs * number_of_operations + Sum_number + M_O[max_machine_index][max_position_index] - 1 - 1].machine_number;//��jobǰһ������Ļ������
				//cout << "MACHINE =" << MACHINE << endl;
				for (int q = 0; q < M_J[MACHINE - 1].size(); q++) //�����ؼ������ϵĹ���
				{
					if (M_J[max_machine_index][max_position_index] == M_J[MACHINE - 1][q])
					{
						if (M_O[max_machine_index][max_position_index] == M_O[MACHINE - 1][q] + 1)
						{
							if (m_s_t[max_machine_index][max_position_index] == m_f_t[MACHINE - 1][q])
							{
								max_position_index = q;
								max_machine_index = MACHINE - 1;
								//cout << "bbbM_J[max_machine_index][max_position_index] - 1 =" << M_J[max_machine_index][max_position_index] - 1 << endl;
								Job.push_back(M_J[max_machine_index][max_position_index]);
								Operation.push_back(M_O[max_machine_index][max_position_index]);
								Machine.push_back(max_machine_index);
								s_t.push_back(m_s_t[max_machine_index][max_position_index]);
								f_t.push_back(m_f_t[max_machine_index][max_position_index]);
								break_2 = 1;
								break;
							}
						}
					}
				}
				if (break_2 == 1)
				{
					continue;
				}
			}
		}
		else if (max_position_index >= 1)
		{
			if (m_s_t[max_machine_index][max_position_index] == m_f_t[max_machine_index][max_position_index - 1])//���ؼ�����Ŀ�ʼʱ��==��λ��ǰһ��������깤ʱ��
			{
				//cout << "ͬһ����ǰ������������β����" << endl;
				max_position_index = max_position_index - 1;//���¹ؼ����򣺵�ǰ������ǰһ������
				//cout << "cccM_J[max_machine_index][max_position_index] - 1 =" << M_J[max_machine_index][max_position_index] - 1 << endl;
				//system("pause");
				Job.push_back(M_J[max_machine_index][max_position_index]);
				Operation.push_back(M_O[max_machine_index][max_position_index]);
				Machine.push_back(max_machine_index);
				s_t.push_back(m_s_t[max_machine_index][max_position_index]);
				f_t.push_back(m_f_t[max_machine_index][max_position_index]);
			}
			else if (m_s_t[max_machine_index][max_position_index] != m_f_t[max_machine_index][max_position_index - 1])//���ؼ�����Ŀ�ʼʱ�䣡=��λ��ǰһ��������깤ʱ��
			{
				//cout << "������,��Ҫ�жϵ�ǰ�����Ƿ�������job�ĵ�һ������" << endl;
				int count_operation_index = M_O[max_machine_index][max_position_index];
				//cout << "count_operation_index = " << count_operation_index << endl;
				max_job_index = M_J[max_machine_index][max_position_index] - 1;
				//cout << "max_job_index = " << max_job_index << endl;
				if (count_operation_index == 1 && m_s_t[max_machine_index][max_position_index] == t.v_job_packing_finish_time[max_job_index])
				{
					//cout << "��ǰ����������job�ĵ�һ�������Ҹù���Ŀ�ʼʱ��=����job����������ʱ��" << endl;
					//cout << "Ѱ�������׶εĹؼ�·����" << endl;
					//cout << "��ǰ�����ʵ������˳���깤ʱ�䣺" << endl;
					for (int pp = 0; pp < t.v_real_packing_route.size(); pp++)
					{
						//cout << "("<< t.v_real_packing_route[pp].first << ", " << t.v_real_packing_route[pp].second << ") ";
						if (t.v_real_packing_route[pp].first - 1 != max_job_index)
						{
							t.Product_C.push_back(t.v_real_packing_route[pp].first - 1);
						}
						else
						{
							t.Product_C.push_back(max_job_index);
							break;
						}
					}
					//cout << endl;
					break;////ֱ������
				}
				else
				{
					//cout << "��ǰ����������job�ĵ�һ��������ôѰ������job����һ������" << endl;
					int break_1 = 0;
					int Sum_number = 0;
					for (int r = 0; r < M_J[max_machine_index][max_position_index] - 1; r++)
					{
						Sum_number = Sum_number + number_of_operations;
					}
					int MACHINE = t.v_chromosome1[number_of_jobs * number_of_operations + Sum_number + M_O[max_machine_index][max_position_index] - 1 - 1].machine_number;//��һ�����������
					//cout << "��job��ǰһ���������ڻ������MACHINE =" << MACHINE << endl;
					for (int q = 0; q < M_J[MACHINE - 1].size(); q++) //������λ������
					{
						if (M_J[max_machine_index][max_position_index] == M_J[MACHINE - 1][q])
						{//��ҵ��ͬ
							if (M_O[max_machine_index][max_position_index] == M_O[MACHINE - 1][q] + 1)
							{//��ǰ����
								if (m_s_t[max_machine_index][max_position_index] == m_f_t[MACHINE - 1][q])
								{
									max_position_index = q;//���¹ؼ�����job����һ����������λ��
									//cout << "max_position_index = " << max_position_index << endl;
									max_machine_index = MACHINE - 1;//������-1
									//cout << "max_machine_index = " << max_machine_index << endl;
									//cout << "dddM_J[max_machine_index][max_position_index] - 1 =" << M_J[max_machine_index][max_position_index] - 1 << endl;
									//system("pause");
									Job.push_back(M_J[max_machine_index][max_position_index]);
									Operation.push_back(M_O[max_machine_index][max_position_index]);
									Machine.push_back(max_machine_index);
									s_t.push_back(m_s_t[max_machine_index][max_position_index]);
									f_t.push_back(m_f_t[max_machine_index][max_position_index]);
									break_1 = 1;
									break;
								}
							}
						}
					}
					if (break_1 == 1)
					{
						continue;
					}
				}

			}
		}
	}

	//cout << "�����׶ιؼ�·��job�����ţ�" << endl;
	//for (int g = 0; g < t.Product_C.size(); g++)
	//{
	//	cout << t.Product_C[g] << " ";
	//}
	//cout << endl;


	////����׶�FJSP�Ĺؼ�·��
	vector<int>().swap(t.Job_C);//����ת����
	vector<int>().swap(t.Operation_C);//������
	vector<int>().swap(t.Machine_C);//(��)
	for (int g = Job.size() - 1; g >= 0; g--)
	{
		t.Job_C.push_back(Job[g]);
	}
	for (int g = Operation.size() - 1; g >= 0; g--)
	{
		t.Operation_C.push_back(Operation[g]);
	}
	for (int g = Machine.size() - 1; g >= 0; g--)
	{
		t.Machine_C.push_back(Machine[g]);
	}
	//cout << "����׶ιؼ�·���漰��job�����ţ�" << endl;
	//for (int k = 0; k < t.Job_C.size(); k++)
	//{
	//	int job_index = t.Job_C[k] - 1;
	//	cout << job_index << " ";
	//}
	//cout << endl;
	//cout << "����׶ιؼ�·���漰��operation�����ţ�" << endl;
	//for (int k = 0; k < t.Job_C.size(); k++)
	//{
	//	int operation_index = t.Operation_C[k] - 1;
	//	cout << operation_index << " ";
	//}
	//cout << endl;
	//cout << "����׶ιؼ�·���漰��machine�����ţ�" << endl;
	//for (int k = 0; k < t.Machine_C.size(); k++)
	//{
	//	int machine_index = t.Machine_C[k];
	//	cout << machine_index << " ";
	//}
	//cout << endl;
	//system("pause");

	vector<double> s_t_C;//�ؼ�·����ҵ�Ĺ���Ŀ�ʼʱ�䣨����
	for (int g = s_t.size() - 1; g >= 0; g--)
	{
		s_t_C.push_back(s_t[g]);
	}
	vector<double> f_t_C;//�ؼ�·����ҵ�Ĺ���Ľ���ʱ�䣨����
	for (int g = f_t.size() - 1; g >= 0; g--)
	{
		f_t_C.push_back(f_t[g]);
	}
	//cout << "����׶ιؼ�·���漰�Ŀ�ʼʱ�䣨������" << endl;
	//for (int k = 0; k < s_t_C.size(); k++)
	//{
	//	double start_time = s_t_C[k];
	//	cout << start_time << " ";
	//}
	//cout << endl;
	//cout << "����׶ιؼ�·���漰�Ľ���ʱ�䣨������" << endl;
	//for (int k = 0; k < f_t_C.size(); k++)
	//{
	//	double finish_time = f_t_C[k];
	//	cout << finish_time << " ";
	//}
	//cout << endl;
	//system("pause");

	//cout << "����׶ιؼ�·���������漰��job�����ţ�operation��������ţ�machine�����ţ�" << endl;
	//for (int k = 0; k < t.Operation_C.size(); k++)
	//{
	//	int job_index = t.Job_C[k] - 1;
	//	cout << "��ҵ������" << job_index << " ";
	//	int operation_index = t.Operation_C[k] - 1;
	//	cout << "����������"<< operation_index << " ";
	//	int machine_index = t.Machine_C[k];
	//	cout << "����������" << machine_index << " ";//����������
	//	cout << "start��" << s_t_C[k] << " ";//��֤
	//	cout << "finish��" << f_t_C[k] << endl;//��֤
	//}
	//cout << endl;
	//system("pause");


	delete[] p_completion_time;
	delete[] p_order_completion_time;
}
