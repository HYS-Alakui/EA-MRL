#include <iomanip>
#include "Qpacking.h"
#include "Individual.h"
#include <cmath>
#include <algorithm>
#include <cassert>
#include <map>

// 输入: 开始时间，结束时间
// 输出: 加工成本
double calculate_part_cost(double start_time, double end_time)
{
	//cout << "start_time = " << start_time << endl;
	//cout << "end_time = " << end_time << endl;
	assert(start_time <= end_time && start_time >= 0);
	double energy_consumption_rate = 25 / pow(end_time - start_time, 2);
	//cout << "energy_consumption_rate = "<< energy_consumption_rate << endl;

	// 时段分为[0, 7), [7, 11), [11, 17), [17, 21), [21, 24)
	// EPI为 5， 8，10， 8， 5 
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
	while (start_time < end_time)//计算每一道工序的用电成本
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

// 输入：每台机器的每个工序的加工开始时间和结束时间
// 输出：每台机器的加工成本总和
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

void QPacking::evaluate_part_FJSP(CIndividual& t)//评估适应度
{
	//cout << "计算邻域解的部分上层适值！" << endl;
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


	vector<int> v_o_numbers; //把工序基因（含新插入工序）放入容器中
	for (int s = 0; s < t.v_upper_chromosome1.size(); s++)
	{
		v_o_numbers.push_back(t.v_upper_chromosome1[s].operation_number);
	}
	map<int, int> count_map;// 使用 map 来计算每个数字（job）的出现次数
	for (int num : v_o_numbers)
	{
		count_map[num]++;
	}
	//for (const auto& pair : count_map) // 输出countMap
	//{
	//	cout << "Job " << pair.first << " 出现 " << pair.second << " 次！" << std::endl;
	//}

	vector<pair<int, int>> v_j_counts;// 创建一个 vector 来存储每个数字的出现次数
	for (const auto& vjc : count_map)
	{
		int job_id = vjc.first;  //job号
		int operation_count = vjc.second; //job包含的工序数
		v_j_counts.push_back(make_pair(job_id, operation_count));
	}
	//cout << "每个job出现的次数:" << std::endl;
	//for (const auto& count : v_j_counts)
	//{
	//	cout << "(" << count.first << ", ";
	//	cout << count.second << ")";
	//}
	//cout << endl;
	//system("pause");



	////step1：获取每个工厂包含的待加工工序
	vector <vector<CChromosome>> v_factory_operation;
	for (int f = 0; f < 1; f++)
	{
		vector<CChromosome> v;
		v_factory_operation.push_back(v);
	}
	for (int j = 0; j < t.v_upper_chromosome1.size(); j++)
	{
		int j_num = t.v_upper_chromosome1[j].job_number;//找出该工序的所属job
		//cout << "j_num = " << j_num << endl;			
		int o_num = t.v_upper_chromosome1[j].operation_index;//找出该工序是第几道工序
		//cout << "o_num = " << o_num << endl;
		int m_num_index = 0;//确定插入位置机器索引
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
		int m_num = t.v_upper_chromosome2[m_num_index].machine_number;//找到该job该工序的所属机器
		//cout << "m_num = " << m_num << endl;
		//system("pause");

		CChromosome ttt;
		ttt.job_number = j_num;
		ttt.operation_index = o_num;
		ttt.machine_number = m_num;
		v_factory_operation[0].push_back(ttt);
	}
	//cout << "每个工厂包含的工序的信息(工序序列；工序的序号；工序所属的机器)：" << endl;
	//for (int f = 0; f < v_factory_operation.size(); f++)
	//{
	//	cout << "F" << f+1 << "---opera_seque_job：";
	//	for (int n = 0; n < v_factory_operation[f].size(); n++)
	//	{		
	//		cout << v_factory_operation[f][n].job_number << " ";
	//	}
	//	cout << endl;
	//	cout << "F" << f+1 << "---operation_index：";
	//	for (int n = 0; n < v_factory_operation[f].size(); n++)
	//	{
	//		cout << v_factory_operation[f][n].operation_index << " ";
	//	}
	//	cout << endl;
	//	cout << "F" << f+1 << "----machine_number：";
	//	for (int n = 0; n < v_factory_operation[f].size(); n++)
	//	{
	//		cout << v_factory_operation[f][n].machine_number << " ";
	//	}
	//	cout << endl <<endl;
	//}
	//cout << endl;
	//system("pause");

	////step2：每个job的每道工序的实际加工时间
	p_c_fjsp_processing_time = new int** [number_of_operations];//是一个包含number_of_factories个元素的数组1
	for (int i = 0; i < number_of_operations; i++)
	{
		p_c_fjsp_processing_time[i] = new int* [number_of_machines];//数组1中 每个元素 都指向一个 包含number_of_machines个元素的数组2
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
				p_c_fjsp_processing_time[i][j][k] = round(p_b_fjsp_processing_time[i][j][k] / (p_machine_adjust_time[j] * 10));//round是四舍五入函数
				//cout << p_c_fjsp_processing_time[i][j][k] << " ";
			}
			//cout << endl;
		}
		//cout << endl;
	}
	//cout << endl;
	//system("pause");


	////step3:求每个工厂的机器加工的工序的job号、对应的工序号、工序的开始和完工时间
	vector<vector<pair<int, int>>> v_operation_completion_time;	
	for (const auto& kv : count_map)// 根据count_map的内容填充vector
	{
		int job_id = kv.first;  //job号
		int operation_count = kv.second; //job包含的工序数
		int operation_completion_time = 0;//工序完工时间初始化	
		vector<pair<int, int>> v_row(operation_count, make_pair(job_id, operation_completion_time));// 创建一个vector<pair<int,int>>，包含operation_count个元素，每个元素是{job_id, 0}
		v_operation_completion_time.push_back(v_row);
	}
	//cout << "初始化现存job每道工序的完工时间：" << endl;
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
	for (const auto& kv : count_map)// 根据count_map的内容填充vector
	{
		int job_id = kv.first;  //job号
		int job_completion_time = 0;//job完工时间初始化	
		v_job_completion_time.push_back(make_pair(job_id, job_completion_time));
	}
	//cout << "初始化现存job的完工时间：" << endl;
	//for (const auto& pair : v_job_completion_time)
	//{
	//	cout << "(" << pair.first << ", " << pair.second << ") ";
	//}
	//cout << std::endl;
	//system("pause");

	//cout << "每个job的切割完工时间：" << endl;
	//for (int j = 0; j < t.v_job_packing_finish_time.size(); j++)
	//{
	//	cout << t.v_job_packing_finish_time[j] << " ";
	//}
	//cout << endl;
	//system("pause");

	vector<vector<int> > M_J(number_of_machines); //该机器加工的工序对应的作业编号
	vector<vector<int> > M_O(number_of_machines);//该机器加工的工序对应的第几个工序；
	vector<vector<double> > m_s_t(number_of_machines);//该机器加工的每个工序的开始时间
	vector<vector<double> > m_f_t(number_of_machines);//该机器加工的每个工序的完工时间
	for (int i = 0; i < 1; i++)
	{
		for (int o = 0; o < v_factory_operation[i].size(); o++)
		{
			int Job_index = v_factory_operation[i][o].job_number;//工序作业号
			//cout << "Job_index = " << Job_index << endl;
			int Operation_index = v_factory_operation[i][o].operation_index;//工序在作业中的顺序
			//cout << "Operation_index =" << Operation_index << endl;
			int machine_index = v_factory_operation[i][o].machine_number;//该工序所在机器
			//cout << "machine_index =" << machine_index << endl;
			if (Operation_index == 1)//是作业的第一个工序
			{
				//cout << "该工序是当前作业的第一道工序，其开始时间需要≥该作业的排样结束时间" << endl;
				double j_pack_finish_time = t.v_job_packing_finish_time[Job_index - 1];
				//cout << Job_index<< "的j_pack_finish_time = " << j_pack_finish_time << endl;
				if (M_J[machine_index - 1].empty())//该机器上未有工序
				{
					//cout << "当前机器上未有工序！" << endl;
					M_J[machine_index - 1].push_back(Job_index);
					M_O[machine_index - 1].push_back(Operation_index);
					//cout << "当前机器尚未有工序进行加工，那么当前作业的首道工序开始时间 = 该作业的排样完工时间" << endl;
					m_s_t[machine_index - 1].push_back(j_pack_finish_time);//该作业的排样完工时间
					//cout << "mst_time = " << j_pack_finish_time << endl;
					m_f_t[machine_index - 1].push_back(j_pack_finish_time + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
					//cout << "mft_time = " << j_pack_finish_time + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] << endl;
				}
				else if (!M_J[machine_index - 1].empty())
				{
					//cout << "当前机器上已有工序，要检查能否插入空闲时间！" << endl;
					int successinsert = 0;//是否插入进去了
					for (int k = 0; k < M_J[machine_index - 1].size(); k++)
					{
						if (k == 0)//当前机器的加工的第一个工序
						{
							//cout << "检查是否能插入第一个工序的前面" << endl;
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
						else if (k != 0)//当前机器的加工的后面工序
						{
							//cout << "k = " << " k" << endl;
							//cout << "检查是否能插入后面工序的前面：不仅要考虑是否有空闲时间，还要考虑到作业的排样完工时间" << endl;
							double Itime = m_s_t[machine_index - 1][k] - m_f_t[machine_index - 1][k - 1];
							//cout << "Itime = " << Itime << endl;
							////当前俩工序之间有空闲时间且作业的排样时间≤后一道工序的开始时间，那么能插入但分三种情况					
							//第一种是，当作业的排样完工时间≤前一个工序的完工时间，那么此时作业的首道工序的开始时间=前一个工序的完工时间
							//第二种是，当作业的排样完工时间≥前一个工序的完工时间 且 作业的首道工序加工时间≤后一个工序的完工时间-作业的排样完工时间，那么此时作业的首道工序的开始时间 = 作业的排样完工时间
							if (p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= Itime && j_pack_finish_time <= m_s_t[machine_index - 1][k])
							{
								if (j_pack_finish_time <= m_f_t[machine_index - 1][k - 1])
								{
									//cout << "第一种情况" << endl;
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
									//cout << "第二种情况" << endl;
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
					if (successinsert != 1) //未插入，放在最后
					{
						//cout << "没有空闲时间可以插，直接放在当前机器最后一个工序的后面，且要满足它的排样完工时间约束" << endl;
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
			//不是作业的第一个工序
			else if (Operation_index != 1)
			{
				//找到该工序的前工序的机器号，存储前工序在它所属机器上的结束时间
				int j_num = Job_index;
				//cout << "j_num = " << j_num << endl;			
				int o_num = Operation_index;
				//cout << "o_num = " << o_num << endl;
				int m_num_index = 0;//确定插入位置机器索引
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
				int mach = t.v_upper_chromosome2[m_num_index].machine_number;//前工序的机器号
				//cout << "mach = " << mach << endl;
				//找到该工序的前工序，让其开始时间等于前工序的完工时间
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
				if (M_J[machine_index - 1].empty()) //该机器上未有工序		
				{
					//cout << "该机器无工序" << endl;
					m_s_t[machine_index - 1].push_back(finishtime);
					//cout << "msttime = " << finishtime << endl;
					m_f_t[machine_index - 1].push_back(m_s_t[machine_index - 1][m_s_t[machine_index - 1].size() - 1] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
					//cout << "mfttime = " << m_s_t[machine_index - 1][m_s_t[machine_index - 1].size() - 1] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] << endl;
					M_J[machine_index - 1].push_back(Job_index);
					M_O[machine_index - 1].push_back(Operation_index);
				}
				else if (!M_J[machine_index - 1].empty()) //该机器上已有工序
				{
					int successinsert = 0;//是否插入进去了
					vector<double>Itime;//该机器上每个工序之间的空闲时间
					for (int k = 0; k < M_J[machine_index - 1].size(); k++)
					{
						if (finishtime < m_s_t[machine_index - 1][k])
						{
							if (k == 0)
							{
								//cout << "检查第一个工序：" << endl;
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
								//cout << "检查后面工序：" << endl;
								double Itime = m_s_t[machine_index - 1][k] - m_f_t[machine_index - 1][k - 1];
								//cout << "Itime = " << Itime << endl;
								if (p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= Itime)
								{
									if (finishtime <= m_f_t[machine_index - 1][k - 1])
									{
										//cout << "情况1：" << endl;
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
										//cout << "情况2：" << endl;
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
						//cout << "无空闲，直接插最后，但要考虑开始时间" << endl;
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
	////以上求出了每个job的每道工序在不同机器上的完工时间
	//cout << "每台机器加工的工序对应的作业编号" << endl;
	//for (int mj = 0; mj < M_J.size(); mj++)
	//{
	//	for (int mk = 0; mk < M_J[mj].size(); mk++)
	//	{
	//		cout << M_J[mj][mk] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//cout << "每台机器加工的工序对应的工序序号" << endl;
	//for (int mj = 0; mj < M_O.size(); mj++)
	//{
	//	for (int mk = 0; mk < M_O[mj].size(); mk++)
	//	{
	//		cout << M_O[mj][mk] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//cout << "每台机器加工的工序的开始时间" << endl;
	//for (int mj = 0; mj < m_s_t.size(); mj++)
	//{
	//	for (int mk = 0; mk < m_s_t[mj].size(); mk++)
	//	{
	//		cout << m_s_t[mj][mk] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//cout << "每台机器加工的工序的结束时间" << endl;//根据这个数组可以找到具有最大完工时间的工序所在的机器号以及位置号
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
	
	////step4：求每个job的每道工序的完工时间
	for (int u = 0; u < M_J.size(); u++)
	{
		for (int v = 0; v < M_J[u].size(); v++)
		{
			int current_job_number = M_J[u][v];
			//cout << "current_job_number = " << current_job_number << endl;
			int current_job_operation_index = M_O[u][v];
			//cout << "current_job_operation_index = " << current_job_operation_index << endl;
			bool found = false; // 标志变量，用于跳出外层循环
			for (auto& v_row : v_operation_completion_time)// 遍历 v_operation_completion_time 来更新指定元素
			{
				for (int s = 0; s < v_row.size(); s++)
				{
					auto& pair = v_row[s];
					if (pair.first == current_job_number && s == current_job_operation_index - 1)
					{
						pair.second = m_f_t[u][v]; //更新工序完工时间
						found = true; // 设置标志变量为true
						break; // 跳出内层循环
					}
				}
				if (found) 
				{
					break; // 如果已经找到并更新了元素，也跳出外层循环
				}
			}
		}
		//cout << endl;
	}
	//cout << endl;
	//cout << "输出现存job每道工序的完工时间：" << endl;
	//for (const auto& v_row : v_operation_completion_time) 
	//{
	//	for (const auto& pair : v_row)
	//	{
	//		cout << "(" << pair.first << ", " << pair.second << ") ";
	//	}
	//	cout << std::endl;
	//}
	//system("pause");


	////step5：求每个job的的完工时间
	for (int s = 0; s< v_job_completion_time.size(); s++)
	{
		auto& pair = v_job_completion_time[s];
		auto& row = v_operation_completion_time[s];
		auto last_operation_completion_time = row.back().second;
		pair.second = last_operation_completion_time;
	}
	//cout << "输出现存job的完工时间：" << endl;
	//for (const auto& pair : v_job_completion_time)
	//{
	//	cout << "(" << pair.first << ", " << pair.second << ") ";
	//}
	//cout << std::endl;
	//system("pause");

	////step6：求每个order包含的job的完工时间
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
	//cout << "每个订单包含的作业的完工时间：" << endl;
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
	//cout << "每个订单包含的作业完工时间：" << endl;
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
	//cout << "每个订单的完工时间" << endl;
	//for (int i = 0; i < number_of_orders; i++)
	//{
	//	cout << p_order_completion_time[i] << " ";
	//}
	//cout << endl;
	//system("pause");

	/////step7：求total_tardiness和total_cost
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
	//cout << "每个订单的tardiness：" << endl;
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
	//cout << "上层FJSP的总延迟total_tardiness = " << t.total_tardiness << endl;

	auto total_cost = calculate_part_cost(m_s_t, m_f_t);
	t.total_cost = total_cost;
	//cout << "上层FJSP的总成本total_cost = " << t.total_cost << endl;
	//system("pause");

	delete[] p_order_completion_time;
}