#include <iomanip>
#include "Qpacking.h"
#include "Individual.h"
#include <cmath>
#include<algorithm>
#include <cassert>

// 输入: 开始时间，结束时间
// 输出: 加工成本
double calculate_cost(double start_time, double end_time)
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


void QPacking::evaluate_FJSP(CIndividual& t)//评估适应度
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

	////step1：获取每个工厂包含的待加工工序
	vector <vector<CChromosome>> v_factory_operation;
	for (int f = 0; f < 1; f++)
	{
		vector<CChromosome> v;
		v_factory_operation.push_back(v);
	}
	for (int j = 0; j < number_of_jobs * number_of_operations; j++)
	{
		int j_num = t.v_chromosome1[j].job_number;//找出该工序的所属job
		//cout << "j_num = " << j_num << endl;	
		int o_num = t.v_chromosome1[j].operation_index;//找出该工序是第几道工序
		//cout << "o_num = " << o_num << endl;
		int m_num_index = number_of_jobs * number_of_operations + (j_num - 1) * number_of_operations + o_num - 1;
		int m_num = t.v_chromosome1[m_num_index].machine_number;//找到该job该工序的所属机器
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
	double** p_operation_completion_time;
	p_operation_completion_time = new double* [number_of_jobs];
	for (int j = 0; j < number_of_jobs; j++)
	{
		p_operation_completion_time[j] = new double[number_of_operations];
	}
	for (int j = 0; j < number_of_jobs; j++)//对开辟的种群初始化
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
					//cout << "当前机器上已有工序，要检查能否插入空闲时间" << endl;
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
								else if (j_pack_finish_time >= m_f_t[machine_index - 1][k - 1] && j_pack_finish_time + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= m_s_t[machine_index - 1][k] )
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
				int find_index = number_of_jobs * number_of_operations + (Job_index - 1) * number_of_operations + (Operation_index - 1) - 1;
				//cout << "find_index = " << find_index << endl;
				int mach = t.v_chromosome1[find_index].machine_number;//前工序的机器号
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
			int current_job_operation_index = M_O[u][v];
			p_operation_completion_time[current_job_number - 1][current_job_operation_index - 1] = m_f_t[u][v];
		}
		//cout << endl;
	}
	//cout << endl;

	////step5：求每个job的的完工时间
	for (int w = 0; w < number_of_jobs; w++)
	{
		p_completion_time[w] = p_operation_completion_time[w][number_of_operations - 1];
		//cout << p_completion_time[w] << endl;
	}
	//system("pause");

	////step6：求每个订单的完工时间
	//cout << "每个订单包含的作业：" << endl;
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
	//cout << "每个订单包含的作业完工时间：" << endl;
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
	//cout << "上层FJSP的总延迟total_tardiness = " << t.total_tardiness << endl;

	auto total_cost = calculate_cost(m_s_t,m_f_t);
	t.total_cost = total_cost;
	//cout << "上层FJSP的总成本total_cost = " << t.total_cost << endl;
	//system("pause");


	/*********************************获取FJSP关键路径***************************************************/
	vector<int>Job;//关键路径的作业编号（倒）
	vector<int>Operation;//关键路径作业的工序编号（倒）
	vector<int>Machine;//关键路径作业的工序所在的机器索引号（倒）
	vector<double>s_t;//关键路径作业的工序的开始时间（倒）
	vector<double>f_t;//关键路径作业的工序的结束时间（倒）
	vector<int>().swap(t.Product_C);//排样阶段的关键路径初始化（正）
	Job.push_back(M_J[max_machine_index][max_position_index]);
	Operation.push_back(M_O[max_machine_index][max_position_index]);
	Machine.push_back(max_machine_index);
	s_t.push_back(m_s_t[max_machine_index][max_position_index]);
	f_t.push_back(m_f_t[max_machine_index][max_position_index]);
	int max_job_index = M_J[max_machine_index][max_position_index] - 1;
	//cout << "max_job_index = " << max_job_index << endl;//机器的最晚完工时间所属job
	vector<double> v_mach_start_time;//储存每台机器的开始加工时间
	for (int u = 0; u < m_s_t.size(); u++)
	{
		v_mach_start_time.push_back(m_s_t[u][0]);
	}
	double job_first_start_time = *min_element(v_mach_start_time.begin(), v_mach_start_time.end());//机器的开始加工时间
	//cout << "job_first_start_time = " << job_first_start_time << endl;
	while (m_s_t[max_machine_index][max_position_index] > job_first_start_time)
	{
		if (max_position_index == 0)
		{
			//cout << "需要判断当前工序是否是所属job的第一道工序" << endl;
			int count_operation_index = M_O[max_machine_index][max_position_index];
			//cout << "count_operation_index = " << count_operation_index << endl;
			max_job_index = M_J[max_machine_index][max_position_index] - 1;
			//cout << "max_job_index = " << max_job_index << endl;
			if (count_operation_index == 1 && m_s_t[max_machine_index][max_position_index] == t.v_job_packing_finish_time[max_job_index])
			{
				//cout << "当前工序是所属job的第一道工序，且该工序的开始时间=所属job的排样结束时间" << endl;
				//cout << "寻找排样阶段的关键路径：" << endl;
				//cout << "当前个体的实际排样顺序及完工时间：" << endl;
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
				break;////直接跳出
			}
			else
			{
				//cout << "当前工序不是所属job的第一道工序，那么寻找所属job的上一道工序" << endl;
				int break_2 = 0;
				int Sum_number = 0;
				//获取当前作业前面还有多少道工序,若当前作业编号是3 那么该作业前面就有（3-1）*number_of_operations道工序
				for (int r = 0; r < M_J[max_machine_index][max_position_index] - 1; r++)
				{
					Sum_number = Sum_number + number_of_operations;
				}
				//获取当前作业关键工序的前一个工序所属的机器编号
				int MACHINE = t.v_chromosome1[number_of_jobs * number_of_operations + Sum_number + M_O[max_machine_index][max_position_index] - 1 - 1].machine_number;//该job前一道工序的机器编号
				//cout << "MACHINE =" << MACHINE << endl;
				for (int q = 0; q < M_J[MACHINE - 1].size(); q++) //遍历关键机器上的工序
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
			if (m_s_t[max_machine_index][max_position_index] == m_f_t[max_machine_index][max_position_index - 1])//若关键工序的开始时间==该位置前一道工序的完工时间
			{
				//cout << "同一机器前后两道工序首尾链接" << endl;
				max_position_index = max_position_index - 1;//更新关键工序：当前机器的前一道工序
				//cout << "cccM_J[max_machine_index][max_position_index] - 1 =" << M_J[max_machine_index][max_position_index] - 1 << endl;
				//system("pause");
				Job.push_back(M_J[max_machine_index][max_position_index]);
				Operation.push_back(M_O[max_machine_index][max_position_index]);
				Machine.push_back(max_machine_index);
				s_t.push_back(m_s_t[max_machine_index][max_position_index]);
				f_t.push_back(m_f_t[max_machine_index][max_position_index]);
			}
			else if (m_s_t[max_machine_index][max_position_index] != m_f_t[max_machine_index][max_position_index - 1])//若关键工序的开始时间！=该位置前一道工序的完工时间
			{
				//cout << "不连接,需要判断当前工序是否是所属job的第一道工序" << endl;
				int count_operation_index = M_O[max_machine_index][max_position_index];
				//cout << "count_operation_index = " << count_operation_index << endl;
				max_job_index = M_J[max_machine_index][max_position_index] - 1;
				//cout << "max_job_index = " << max_job_index << endl;
				if (count_operation_index == 1 && m_s_t[max_machine_index][max_position_index] == t.v_job_packing_finish_time[max_job_index])
				{
					//cout << "当前工序是所属job的第一道工序，且该工序的开始时间=所属job的排样结束时间" << endl;
					//cout << "寻找排样阶段的关键路径：" << endl;
					//cout << "当前个体的实际排样顺序及完工时间：" << endl;
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
					break;////直接跳出
				}
				else
				{
					//cout << "当前工序不是所属job的第一道工序，那么寻找所属job的上一道工序" << endl;
					int break_1 = 0;
					int Sum_number = 0;
					for (int r = 0; r < M_J[max_machine_index][max_position_index] - 1; r++)
					{
						Sum_number = Sum_number + number_of_operations;
					}
					int MACHINE = t.v_chromosome1[number_of_jobs * number_of_operations + Sum_number + M_O[max_machine_index][max_position_index] - 1 - 1].machine_number;//上一道工序机器号
					//cout << "该job的前一道工序所在机器编号MACHINE =" << MACHINE << endl;
					for (int q = 0; q < M_J[MACHINE - 1].size(); q++) //遍历找位置索引
					{
						if (M_J[max_machine_index][max_position_index] == M_J[MACHINE - 1][q])
						{//作业相同
							if (M_O[max_machine_index][max_position_index] == M_O[MACHINE - 1][q] + 1)
							{//紧前工序
								if (m_s_t[max_machine_index][max_position_index] == m_f_t[MACHINE - 1][q])
								{
									max_position_index = q;//更新关键工序：job的上一道工序所在位置
									//cout << "max_position_index = " << max_position_index << endl;
									max_machine_index = MACHINE - 1;//机器号-1
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

	//cout << "排样阶段关键路径job索引号：" << endl;
	//for (int g = 0; g < t.Product_C.size(); g++)
	//{
	//	cout << t.Product_C[g] << " ";
	//}
	//cout << endl;


	////制造阶段FJSP的关键路径
	vector<int>().swap(t.Job_C);//倒序转正序
	vector<int>().swap(t.Operation_C);//（正）
	vector<int>().swap(t.Machine_C);//(正)
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
	//cout << "制造阶段关键路径涉及的job索引号：" << endl;
	//for (int k = 0; k < t.Job_C.size(); k++)
	//{
	//	int job_index = t.Job_C[k] - 1;
	//	cout << job_index << " ";
	//}
	//cout << endl;
	//cout << "制造阶段关键路径涉及的operation索引号：" << endl;
	//for (int k = 0; k < t.Job_C.size(); k++)
	//{
	//	int operation_index = t.Operation_C[k] - 1;
	//	cout << operation_index << " ";
	//}
	//cout << endl;
	//cout << "制造阶段关键路径涉及的machine索引号：" << endl;
	//for (int k = 0; k < t.Machine_C.size(); k++)
	//{
	//	int machine_index = t.Machine_C[k];
	//	cout << machine_index << " ";
	//}
	//cout << endl;
	//system("pause");

	vector<double> s_t_C;//关键路径作业的工序的开始时间（正）
	for (int g = s_t.size() - 1; g >= 0; g--)
	{
		s_t_C.push_back(s_t[g]);
	}
	vector<double> f_t_C;//关键路径作业的工序的结束时间（正）
	for (int g = f_t.size() - 1; g >= 0; g--)
	{
		f_t_C.push_back(f_t[g]);
	}
	//cout << "制造阶段关键路径涉及的开始时间（正）：" << endl;
	//for (int k = 0; k < s_t_C.size(); k++)
	//{
	//	double start_time = s_t_C[k];
	//	cout << start_time << " ";
	//}
	//cout << endl;
	//cout << "制造阶段关键路径涉及的结束时间（正）：" << endl;
	//for (int k = 0; k < f_t_C.size(); k++)
	//{
	//	double finish_time = f_t_C[k];
	//	cout << finish_time << " ";
	//}
	//cout << endl;
	//system("pause");

	//cout << "制造阶段关键路径（正）涉及的job索引号，operation序号索引号，machine索引号：" << endl;
	//for (int k = 0; k < t.Operation_C.size(); k++)
	//{
	//	int job_index = t.Job_C[k] - 1;
	//	cout << "作业索引：" << job_index << " ";
	//	int operation_index = t.Operation_C[k] - 1;
	//	cout << "工序索引："<< operation_index << " ";
	//	int machine_index = t.Machine_C[k];
	//	cout << "机器索引：" << machine_index << " ";//机器索引号
	//	cout << "start：" << s_t_C[k] << " ";//验证
	//	cout << "finish：" << f_t_C[k] << endl;//验证
	//}
	//cout << endl;
	//system("pause");


	delete[] p_completion_time;
	delete[] p_order_completion_time;
}
