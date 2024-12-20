#include <iomanip>
#include "Qpacking.h"
#include "Individual.h"
#include <cmath>
#include <algorithm>
#include <cassert>
#include <map>

// ����: ��ʼʱ�䣬����ʱ��
// ���: �ӹ��ɱ�
double calculate_part_cost(double start_time, double end_time)
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
double calculate_part_cost(const vector<vector<double>>& m_s_t, const vector<vector<double>>& m_f_t)
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
			total_cost_value += calculate_part_cost(m_s_t[i][j], m_f_t[i][j]);
			//cout << "total_cost_value =" << total_cost_value << endl;
			//system("pause");
		}
	}
	return total_cost_value;
}

void QPacking::evaluate_part_FJSP(CIndividual& t)//������Ӧ��
{
	//cout << "���������Ĳ����ϲ���ֵ��" << endl;
	//for (int s = 0; s < t.v_upper_chromosome1.size(); s++)
	//{
	//	cout << t.v_upper_chromosome1[s].operation_number << " ";
	//}
	//cout << endl;
	//for (int s = 0; s < t.v_upper_chromosome1.size(); s++)
	//{
	//	cout << t.v_upper_chromosome1[s].operation_index << " ";
	//}
	//cout << endl;
	//for (int s = 0; s < t.v_upper_chromosome2.size(); s++)
	//{
	//	cout << t.v_upper_chromosome2[s].machine_number << " ";
	//}
	//cout << endl;
	//for (int s = 0; s < t.v_lower_chromosome.size(); s++)
	//{
	//	cout << t.v_lower_chromosome[s].job_number << " ";
	//}
	//cout << endl << endl;
	//system("pause");


	vector<int> v_o_numbers; //�ѹ�����򣨺��²��빤�򣩷���������
	for (int s = 0; s < t.v_upper_chromosome1.size(); s++)
	{
		v_o_numbers.push_back(t.v_upper_chromosome1[s].operation_number);
	}
	map<int, int> count_map;// ʹ�� map ������ÿ�����֣�job���ĳ��ִ���
	for (int num : v_o_numbers)
	{
		count_map[num]++;
	}
	//for (const auto& pair : count_map) // ���countMap
	//{
	//	cout << "Job " << pair.first << " ���� " << pair.second << " �Σ�" << std::endl;
	//}

	vector<pair<int, int>> v_j_counts;// ����һ�� vector ���洢ÿ�����ֵĳ��ִ���
	for (const auto& vjc : count_map)
	{
		int job_id = vjc.first;  //job��
		int operation_count = vjc.second; //job�����Ĺ�����
		v_j_counts.push_back(make_pair(job_id, operation_count));
	}
	//cout << "ÿ��job���ֵĴ���:" << std::endl;
	//for (const auto& count : v_j_counts)
	//{
	//	cout << "(" << count.first << ", ";
	//	cout << count.second << ")";
	//}
	//cout << endl;
	//system("pause");



	////step1����ȡÿ�����������Ĵ��ӹ�����
	vector <vector<CChromosome>> v_factory_operation;
	for (int f = 0; f < 1; f++)
	{
		vector<CChromosome> v;
		v_factory_operation.push_back(v);
	}
	for (int j = 0; j < t.v_upper_chromosome1.size(); j++)
	{
		int j_num = t.v_upper_chromosome1[j].job_number;//�ҳ��ù��������job
		//cout << "j_num = " << j_num << endl;			
		int o_num = t.v_upper_chromosome1[j].operation_index;//�ҳ��ù����ǵڼ�������
		//cout << "o_num = " << o_num << endl;
		int m_num_index = 0;//ȷ������λ�û�������
		for (const auto& count : v_j_counts)
		{
			if (count.first < j_num)
			{
				m_num_index += count.second;
			}
			else
			{
				break;
			}
		}
		m_num_index = m_num_index + o_num - 1;
		//cout << "m_num_index = " << m_num_index << endl;
		int m_num = t.v_upper_chromosome2[m_num_index].machine_number;//�ҵ���job�ù������������
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
	vector<vector<pair<int, int>>> v_operation_completion_time;	
	for (const auto& kv : count_map)// ����count_map���������vector
	{
		int job_id = kv.first;  //job��
		int operation_count = kv.second; //job�����Ĺ�����
		int operation_completion_time = 0;//�����깤ʱ���ʼ��	
		vector<pair<int, int>> v_row(operation_count, make_pair(job_id, operation_completion_time));// ����һ��vector<pair<int,int>>������operation_count��Ԫ�أ�ÿ��Ԫ����{job_id, 0}
		v_operation_completion_time.push_back(v_row);
	}
	//cout << "��ʼ���ִ�jobÿ��������깤ʱ�䣺" << endl;
	//for (const auto& v_row : v_operation_completion_time) 
	//{
	//	for (const auto& pair : v_row)
	//	{
	//		cout << "(" << pair.first << ", " << pair.second << ") ";
	//	}
	//	cout << std::endl;
	//}
	//system("pause");


	vector<pair<int, int>> v_job_completion_time;
	for (const auto& kv : count_map)// ����count_map���������vector
	{
		int job_id = kv.first;  //job��
		int job_completion_time = 0;//job�깤ʱ���ʼ��	
		v_job_completion_time.push_back(make_pair(job_id, job_completion_time));
	}
	//cout << "��ʼ���ִ�job���깤ʱ�䣺" << endl;
	//for (const auto& pair : v_job_completion_time)
	//{
	//	cout << "(" << pair.first << ", " << pair.second << ") ";
	//}
	//cout << std::endl;
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
					//cout << "��ǰ������δ�й���" << endl;
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
					//cout << "��ǰ���������й���Ҫ����ܷ�������ʱ�䣡" << endl;
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
								else if (j_pack_finish_time >= m_f_t[machine_index - 1][k - 1] && j_pack_finish_time + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= m_s_t[machine_index - 1][k])
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
				int j_num = Job_index;
				//cout << "j_num = " << j_num << endl;			
				int o_num = Operation_index;
				//cout << "o_num = " << o_num << endl;
				int m_num_index = 0;//ȷ������λ�û�������
				for (const auto& count : v_j_counts)
				{
					if (count.first < j_num)
					{
						m_num_index += count.second;
					}
					else
					{
						break;
					}
				}
				m_num_index = m_num_index + o_num - 1 - 1;
				//cout << "m_num_index = " << m_num_index << endl;
				int mach = t.v_upper_chromosome2[m_num_index].machine_number;//ǰ����Ļ�����
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
			//cout << "current_job_number = " << current_job_number << endl;
			int current_job_operation_index = M_O[u][v];
			//cout << "current_job_operation_index = " << current_job_operation_index << endl;
			bool found = false; // ��־�����������������ѭ��
			for (auto& v_row : v_operation_completion_time)// ���� v_operation_completion_time ������ָ��Ԫ��
			{
				for (int s = 0; s < v_row.size(); s++)
				{
					auto& pair = v_row[s];
					if (pair.first == current_job_number && s == current_job_operation_index - 1)
					{
						pair.second = m_f_t[u][v]; //���¹����깤ʱ��
						found = true; // ���ñ�־����Ϊtrue
						break; // �����ڲ�ѭ��
					}
				}
				if (found) 
				{
					break; // ����Ѿ��ҵ���������Ԫ�أ�Ҳ�������ѭ��
				}
			}
		}
		//cout << endl;
	}
	//cout << endl;
	//cout << "����ִ�jobÿ��������깤ʱ�䣺" << endl;
	//for (const auto& v_row : v_operation_completion_time) 
	//{
	//	for (const auto& pair : v_row)
	//	{
	//		cout << "(" << pair.first << ", " << pair.second << ") ";
	//	}
	//	cout << std::endl;
	//}
	//system("pause");


	////step5����ÿ��job�ĵ��깤ʱ��
	for (int s = 0; s< v_job_completion_time.size(); s++)
	{
		auto& pair = v_job_completion_time[s];
		auto& row = v_operation_completion_time[s];
		auto last_operation_completion_time = row.back().second;
		pair.second = last_operation_completion_time;
	}
	//cout << "����ִ�job���깤ʱ�䣺" << endl;
	//for (const auto& pair : v_job_completion_time)
	//{
	//	cout << "(" << pair.first << ", " << pair.second << ") ";
	//}
	//cout << std::endl;
	//system("pause");

	////step6����ÿ��order������job���깤ʱ��
	vector<vector<pair<int,int>>> v_order_product_time;
	for (int i = 0; i < v_order_product.size(); i++)
	{
		vector<pair<int,int>> v;
		for (int j = 0; j < v_order_product[i].size(); j++)
		{
			int product_number = v_order_product[i][j];
			//cout << "product_number = " << product_number << endl;
			for (const auto& pair : v_job_completion_time)
			{
				if (pair.first == product_number)
				{
					double finish_time = pair.second;
					//cout << "finish_time = " << finish_time << endl;
					v.push_back(make_pair(product_number,finish_time));
					break;
				}
			}
		}
		//cout << endl;
		v_order_product_time.push_back(v);
	}
	//cout << "ÿ��������������ҵ���깤ʱ�䣺" << endl;
	//for (int i = 0; i < v_order_product_time.size(); i++) 
	//{
	//	for (int j = 0; j < v_order_product_time[i].size(); j++) 
	//	{
	//		auto& p = v_order_product_time[i][j];
	//		cout << "(" << p.first << ", " << p.second << ")";
	//	}
	//	cout << endl;
	//}
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
			auto& p = v_order_product_time[i][j];
			if (p.second > max_order_value)
			{
				max_order_value = p.second;
			}
		}
		p_order_completion_time[i] = max_order_value;
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
	//system("pause");
	
	int max_product_index = 0;
	int max_product_time = v_order_product_time[max_order_index][0].second;
	for (int i = 0; i < v_order_product_time[max_order_index].size(); i++)
	{
		auto& p = v_order_product_time[max_order_index][i];
		if (p.second > max_product_time)
		{
			max_product_time = p.second;
			max_product_index = p.first - 1;
		}
	}
	//cout << "max_product_time = " << max_product_time << endl;
	//cout << "max_product_index = " << max_product_index << endl;
	//system("pause");
	t.max_tardiness_job_index = max_product_index;
	t.total_tardiness = total_tardiness;
	//cout << "�ϲ�FJSP�����ӳ�total_tardiness = " << t.total_tardiness << endl;

	auto total_cost = calculate_part_cost(m_s_t, m_f_t);
	t.total_cost = total_cost;
	//cout << "�ϲ�FJSP���ܳɱ�total_cost = " << t.total_cost << endl;
	//system("pause");

	delete[] p_order_completion_time;
}