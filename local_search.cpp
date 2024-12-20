#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"
#include "Item.h"
#include <algorithm>
#include <map>

void QPacking::local_search(vector<CIndividual>& v_new_TotalChromo_temp, vector <vector<CIndividual>>& v_new_Chromo_temp, vector<Item>& v_product, int& Action_Current)
{
	//cout << "local_search前！" << endl;
	//out_result(v_new_Chromo_temp, v_new_TotalChromo_temp);

	/////局部搜索
	vector<vector<CIndividual>>().swap(v_ls_Chromo);
	vector<CIndividual>().swap(v_ls_TotalChromo);
	for (int i = 0; i < number_of_subpop; i++)
	{
		vector <CIndividual> v_ls_subChromo;
		vector <CIndividual>().swap(v_ls_subChromo);
		for (int j = 0; j < lower_number_of_individuals; j++) //对每个个体执行局部搜索操作
		{
			CIndividual ls_indiv = v_new_Chromo_temp[i][j];		
			ls_operation_individual(ls_indiv, v_product, Action_Current); ////对每个个体执行局部搜索操作
			upper_evaluate(ls_indiv, board_width, board_height, v_product);
			v_ls_subChromo.push_back(ls_indiv);
			v_ls_TotalChromo.push_back(ls_indiv);
		}
		v_ls_Chromo.push_back(v_ls_subChromo);
	}
	
	rank_up(v_ls_TotalChromo);//获取种群中个体的上层序值和拥挤度距离
	rank_low(v_ls_Chromo);//获取种群中每个子种群中个体的下层序值和拥挤度距离
	update_subpop(v_ls_TotalChromo, v_ls_Chromo);//获得新种群v_new_TotalChromo/v_new_Chromo
	
	//cout << "local_search后！" << endl;
	//out_result(v_ls_Chromo, v_ls_TotalChromo);
}

void QPacking::ls_operation_individual(CIndividual& ls_indiv, vector<Item>& v_product, int & Action_Current)
{
	//cout << "局部搜索前的个体：" << endl;
	//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//{
	//	cout << ls_indiv.v_chromosome1[u].operation_number << " ";
	//}
	//cout << endl;
	//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//{
	//	cout << ls_indiv.v_chromosome1[u].operation_index << " ";
	//}
	//cout << endl;
	//for (int u = number_of_jobs * number_of_operations; u < ls_indiv.v_chromosome1.size(); u++)
	//{
	//	cout << ls_indiv.v_chromosome1[u].machine_number << " ";
	//}
	//cout << endl;
	////for (int u = number_of_jobs * number_of_operations; u < ls_indiv.v_chromosome1.size(); u++)
	////{
	////	cout << ls_indiv.v_chromosome1[u].job_number << " ";
	////}
	////cout << endl;
	////for (int u = 0; u < ls_indiv.v_chromosome2.size(); u++)
	////{
	////	cout << ls_indiv.v_chromosome2[u].job_number << " ";
	////}
	////cout << endl;
	////for (int u = 0; u < ls_indiv.v_ul_objectives.size(); u++)
	////{
	////	for (int v = 0; v < ls_indiv.v_ul_objectives[u].size(); v++)
	////	{
	////		cout << ls_indiv.v_ul_objectives[u][v] << " ";
	////	}
	////}
	////system("pause");

	////执行四种通用邻域结构
	//Case1:改变工序序列的加工顺序，在工序向量上随机选中两个切点，然后对两点之间的工序进行翻转，机器向量不变
	//Case2:改变工序序列的加工顺序，在工序向量上随机选中两个切点，然后对两点上的工序进行交换，机器向量不变
	//Case3:改变工序序列的加工顺序，在工序向量上随机选中两个切点，然后把靠后的切点上的工序插入到靠前的切点上的工序的前面，机器向量不变
	//Case4:改变机器分配，在工序向量上随机选中两个切点，然后对两点之间的工序的机器编号重新生成
	//Case5:随机交换关键路径上在排样阶段或排产阶段的两个job
	//Case6:随机将关键路径上在排样阶段或排产阶段的一个job插入到另一个job前面
	//Case7:随机更换关键路径上在排产阶段的一个job的机器分配
	int rand_select_number = Action_Current;
	//cout << "rand_select_number = " << rand_select_number << endl;
	if (rand_select_number == 1)
	{
		//cout << "执行case1" << endl;
		ls_operation1(ls_indiv, v_product);
	}
	else if (rand_select_number == 2)
	{
		//cout << "执行case2" << endl;
		ls_operation2(ls_indiv, v_product);
	}
	else if (rand_select_number == 3)
	{
		//cout << "执行case3" << endl;
		ls_operation3(ls_indiv, v_product);
	}
	else if (rand_select_number == 4)
	{
		//cout << "执行case4" << endl;
		ls_operation4(ls_indiv, v_product);
	}
	else if (rand_select_number == 5)
	{
		//cout << "执行case5" << endl;
		ls_operation5(ls_indiv, v_product);
	}
	else if (rand_select_number == 6)
	{
		//cout << "执行case6" << endl;
		ls_operation6(ls_indiv, v_product);
	}
	else if (rand_select_number == 7)
	{
		//cout << "执行case6" << endl;
		ls_operation6(ls_indiv, v_product);
	}

	//cout << "局部搜索后的个体：" << endl;
	//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//{
	//	cout << ls_indiv.v_chromosome1[u].operation_number << " ";
	//}
	//cout << endl;
	//for (int u = 0; u < number_of_jobs * number_of_operations; u++)
	//{
	//	cout << ls_indiv.v_chromosome1[u].operation_index << " ";
	//}
	//cout << endl;
	//for (int u = number_of_jobs * number_of_operations; u < ls_indiv.v_chromosome1.size(); u++)
	//{
	//	cout << ls_indiv.v_chromosome1[u].machine_number << " ";
	//}
	//cout << endl;
	////for (int u = number_of_jobs * number_of_operations; u < ls_indiv.v_chromosome1.size(); u++)
	////{
	////	cout << ls_indiv.v_chromosome1[u].job_number << " ";
	////}
	////cout << endl;
	////for (int u = 0; u < ls_indiv.v_chromosome2.size(); u++)
	////{
	////	cout << ls_indiv.v_chromosome2[u].job_number << " ";
	////}
	////cout << endl;
	////for (int u = 0; u < ls_indiv.v_ul_objectives.size(); u++)
	////{
	////	for (int v = 0; v < ls_indiv.v_ul_objectives[u].size(); v++)
	////	{
	////		cout << ls_indiv.v_ul_objectives[u][v] << " ";
	////	}
	////}
	//system("pause");
}

void QPacking::ls_operation1(CIndividual& ls_indiv1, vector<Item>& v_product)
{
	//cout << "两点翻转！" << endl;
	int cutpoint1, cutpoint2;//工序序列切点；			
	cutpoint1 = rand() % (number_of_jobs * number_of_operations);
	cutpoint2 = rand() % (number_of_jobs * number_of_operations);
	while (cutpoint1 == cutpoint2)//若两个切点相同
	{
		cutpoint1 = rand() % (number_of_jobs * number_of_operations);//则重新产生一个切点2
	}
	int temp_cut1;
	if (cutpoint1 > cutpoint2)
	{
		temp_cut1 = cutpoint1;
		cutpoint1 = cutpoint2;
		cutpoint2 = temp_cut1;
	}
	//cout << "cutpoint1 = " << cutpoint1 << endl;
	//cout << "cutpoint2 = " << cutpoint2 << endl;
	
	vector <int> v_oper_part_list;
	vector <int>().swap(v_oper_part_list);//把两点间的元素放在数组里，好使用reverse翻转
	for (int u = cutpoint1; u <= cutpoint2; u++)
	{
		int operNo = ls_indiv1.v_chromosome1[u].operation_number;
		v_oper_part_list.push_back(operNo);
	}
	//for (int u = 0; u < v_oper_part_list.size(); u++)
	//{
	//	cout << v_oper_part_list[u] << " ";
	//}
	//system("pause");

	reverse(v_oper_part_list.begin(), v_oper_part_list.end()); //对v_operation_part_list中的从v_operation_part_list.begin()（包括它）到v_operation_part_list.end()（包括它）的元素倒置，如v_operation_part_list中元素为1,2,3,4,倒置后为4,3,2,1
	//for (int u = 0; u < v_oper_part_list.size(); u++)
	//{
	//	cout << v_oper_part_list[u] << " ";
	//}
	//system("pause");

	for (int u = cutpoint1; u <= cutpoint2; u++)
	{
		int jobNo_j = v_oper_part_list[u - cutpoint1];
		//cout << "jobNo_j = " << jobNo_j << endl;
		ls_indiv1.v_chromosome1[u].operation_number = jobNo_j;
		ls_indiv1.v_chromosome1[u].job_number = jobNo_j;//job_number随之更新
	}

	//operation_index随之更新
	for (int u = 0; u < number_of_jobs; u++)//判断是每个job的第几道工序
	{
		int current_job_number = u + 1;
		int count = 0;
		for (int c = 0; c < number_of_jobs * number_of_operations; c++)
		{
			if (current_job_number == ls_indiv1.v_chromosome1[c].job_number)
			{
				count = count + 1;
				ls_indiv1.v_chromosome1[c].operation_index = count;
			}
			continue;
		}
	}
}

void QPacking::ls_operation2(CIndividual& ls_indiv2, vector<Item>& v_product)
{
	//cout << "两点交换！" << endl;
	int cutpoint3, cutpoint4;//工序序列切点；			
	cutpoint3 = rand() % (number_of_jobs * number_of_operations);
	cutpoint4 = rand() % (number_of_jobs * number_of_operations);
	while (cutpoint3 == cutpoint4)//若两个切点相同
	{
		cutpoint3 = rand() % (number_of_jobs * number_of_operations);//则重新产生一个切点2
	}
	int temp_cut2;
	if (cutpoint3 > cutpoint4)
	{
		temp_cut2 = cutpoint3;
		cutpoint3 = cutpoint4;
		cutpoint4 = temp_cut2;
	}
	//cout << "cutpoint3 = " << cutpoint3 << endl;
	//cout << "cutpoint4 = " << cutpoint4 << endl;

	//交换两个切点的工序号
	int operNo = ls_indiv2.v_chromosome1[cutpoint3].operation_number;
	ls_indiv2.v_chromosome1[cutpoint3].operation_number = ls_indiv2.v_chromosome1[cutpoint4].operation_number;;
	ls_indiv2.v_chromosome1[cutpoint4].operation_number = operNo;
	
	//job_number随之更新
	ls_indiv2.v_chromosome1[cutpoint3].job_number = ls_indiv2.v_chromosome1[cutpoint3].operation_number;
	ls_indiv2.v_chromosome1[cutpoint4].job_number = ls_indiv2.v_chromosome1[cutpoint4].operation_number;

	//operation_index随之更新
	for (int u = 0; u < number_of_jobs; u++)//判断是每个job的第几道工序
	{
		int current_job_number = u + 1;
		int count = 0;
		for (int c = 0; c < number_of_jobs * number_of_operations; c++)
		{
			if (current_job_number == ls_indiv2.v_chromosome1[c].job_number)
			{
				count = count + 1;
				ls_indiv2.v_chromosome1[c].operation_index = count;
			}
			continue;
		}
	}
}

void QPacking::ls_operation3(CIndividual& ls_indiv3, vector<Item>& v_product)
{
	//cout << "两点插入！" << endl;
	int cutpoint5, cutpoint6;//工序序列切点；			
	cutpoint5 = rand() % (number_of_jobs * number_of_operations);
	cutpoint6 = rand() % (number_of_jobs * number_of_operations);
	while (cutpoint5 == cutpoint6)//若两个切点相同
	{
		cutpoint5 = rand() % (number_of_jobs * number_of_operations);//则重新产生一个切点2
	}
	int temp_cut3;
	if (cutpoint5 > cutpoint6)
	{
		temp_cut3 = cutpoint5;
		cutpoint5 = cutpoint6;
		cutpoint6 = temp_cut3;
	}
	//cout << "cutpoint5 = " << cutpoint5 << endl;
	//cout << "cutpoint6 = " << cutpoint6 << endl;
	
	//获取后面切点上的工序
	int ls_operation_job = ls_indiv3.v_chromosome1[cutpoint6].operation_number;
	//cout << "ls_operation_job = " << ls_operation_job << endl;
	 
	//先将选中的靠后一点的operation在染色体中删除
	ls_indiv3.v_chromosome1.erase(ls_indiv3.v_chromosome1.begin() + cutpoint6);
	
	//然后再把它插入到靠前一点的operation的前面位置
	CChromosome tttt;
	tttt.operation_number = ls_operation_job;
	ls_indiv3.v_chromosome1.insert(ls_indiv3.v_chromosome1.begin() + cutpoint5, tttt);

	//同时，更新它们的job信息
	for (int k = 0; k < number_of_jobs * number_of_operations; k++)
	{
		ls_indiv3.v_chromosome1[k].job_number = ls_indiv3.v_chromosome1[k].operation_number;
	}

	//根据job信息更新它们的operation_index信息
	for (int k = 0; k < number_of_jobs; k++)//判断是每个job的第几道工序
	{
		int current_job_number = k + 1;
		int count = 0;
		for (int c = 0; c < number_of_jobs * number_of_operations; c++)
		{
			if (current_job_number == ls_indiv3.v_chromosome1[c].job_number)
			{
				count = count + 1;
				ls_indiv3.v_chromosome1[c].operation_index = count;
			}
			continue;
		}
	}
}

void QPacking::ls_operation4(CIndividual& ls_indiv4, vector<Item>& v_product)
{
	//cout << "两点之间机器重新随机生成！" << endl;
	int cutpoint7, cutpoint8;//工序序列切点；			
	cutpoint7 = rand() % (number_of_jobs * number_of_operations);
	cutpoint8 = rand() % (number_of_jobs * number_of_operations);
	while (cutpoint7 == cutpoint8)//若两个切点相同
	{
		cutpoint7 = rand() % (number_of_jobs * number_of_operations);//则重新产生一个切点2
	}
	int temp_cut4;
	if (cutpoint7 > cutpoint8)
	{
		temp_cut4 = cutpoint7;
		cutpoint7 = cutpoint8;
		cutpoint8 = temp_cut4;
	}
	//cout << "cutpoint7 = " << cutpoint7 << endl;
	//cout << "cutpoint8 = " << cutpoint8 << endl;

	for (int u = cutpoint7; u <= cutpoint8; u++)
	{
		int jobNo = ls_indiv4.v_chromosome1[u].job_number;
		//cout << "jobNo = " << jobNo << endl;
		int operIndex = ls_indiv4.v_chromosome1[u].operation_index;
		//cout << "operIndex = " << operIndex << endl;
		//获取该job的该道工序的可使用机器数量
		int operation_machine_size = v_available_machines[jobNo - 1][operIndex - 1].size();
		//cout << "operation_machine_size = " << operation_machine_size << endl;
		if (operation_machine_size >= 2)
		{
			int rand_machine_number_index = rand() % operation_machine_size;
			//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
			int rand_machine_number = v_available_machines[jobNo - 1][operIndex - 1][rand_machine_number_index];
			//cout << "rand_machine_number = " << rand_machine_number << endl;
			//获取该工序的机器位置索引
			int mach_pos_index = number_of_jobs * number_of_operations + (jobNo - 1) * number_of_operations + operIndex - 1;
			//cout << "mach_pos_index = " << mach_pos_index << endl;
			int current_machine_number = ls_indiv4.v_chromosome1[mach_pos_index].machine_number;
			//cout << "current_machine_number = " << current_machine_number << endl;
			while (current_machine_number == rand_machine_number)
			{
				rand_machine_number_index = rand() % operation_machine_size;
				//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
				rand_machine_number = v_available_machines[jobNo - 1][operIndex - 1][rand_machine_number_index];
				//cout << "rand_machine_number = " << rand_machine_number << endl;
			}
			ls_indiv4.v_chromosome1[mach_pos_index].machine_number = rand_machine_number;
		}
	}
}

void QPacking::ls_operation5(CIndividual& ls_indiv, vector<Item>& v_product)
{
	//cout << "对关键路径进行swap操作！" << endl;

	//cout << "排样阶段关键路径job索引号：" << endl;
	//for (int g = 0; g < ls_indiv.Product_C.size(); g++)
	//{
	//	cout << ls_indiv.Product_C[g] << " ";
	//}
	//cout << endl;

	//cout << "制造阶段关键路径（正）涉及的job索引号，operation序号索引号，machine索引号：" << endl;
	//for (int k = 0; k < ls_indiv.Operation_C.size(); k++)
	//{
	//	int job_index = ls_indiv.Job_C[k] - 1;
	//	cout << "作业索引：" << job_index << " ";
	//	int operation_index = ls_indiv.Operation_C[k] - 1;
	//	cout << "工序索引：" << operation_index << " ";
	//	int machine_index = ls_indiv.Machine_C[k];
	//	cout << "机器索引：" << machine_index << " ";//机器索引号
	//	cout << endl;
	//}
	//cout << endl;
	//system("pause");

	////判断排样阶段的规模
	if (ls_indiv.Product_C.size() >= 2)
	{
		//cout << "对排样或排产关键路径上的job进行调整！" << endl;
		int random_number = rand() % 2;
		if (random_number == 0)
		{
			//cout << "对排样路径上的job进行调整！" << endl;
			////step1：随机选取关键路径上的两个不重复的job
			int key_size = ls_indiv.Product_C.size();
			int ls1 = rand() % key_size;
			int ls2 = rand() % key_size;
			while (ls1 == ls2)
			{
				ls2 = rand() % key_size;
			}
			if (ls1 > ls2)
			{
				int temp = ls1;
				ls1 = ls2;
				ls2 = temp;
			}
			int ls_job1, ls_job2;
			ls_job1 = ls_indiv.Product_C[ls1] + 1;
			ls_job2 = ls_indiv.Product_C[ls2] + 1;

			////step2：在ls_indiv染色体上寻找这俩job的位置索引
			int ls_pos_index1 = 0;
			int ls_pos_index2 = 0;
			for (int u = 0; u < ls_indiv.v_chromosome2.size(); u++)
			{
				if (ls_indiv.v_chromosome2[u].job_number == ls_job1)
				{
					ls_pos_index1 = u;
					break;
				}
			}
			//cout << endl;
			for (int u = 0; u < ls_indiv.v_chromosome2.size(); u++)
			{
				if (ls_indiv.v_chromosome2[u].job_number == ls_job2)
				{
					ls_pos_index2 = u;
					break;
				}
			}

			////step3：在ls_indiv染色体上交换这俩job
			int ls_job_temp = ls_indiv.v_chromosome2[ls_pos_index1].job_number;
			ls_indiv.v_chromosome2[ls_pos_index1].job_number = ls_indiv.v_chromosome2[ls_pos_index2].job_number;
			ls_indiv.v_chromosome2[ls_pos_index2].job_number = ls_job_temp;
		}
		else
		{
			//cout << "对排产路径上的job进行调整！" << endl;
			////step1：随机选中两个关键job
			int ls_size = ls_indiv.Job_C.size();
			int ls1 = rand() % ls_size;
			int ls2 = rand() % ls_size;
			while (ls1 == ls2)
			{
				ls2 = rand() % ls_size;
			}
			if (ls1 > ls2)
			{
				int temp = ls1;
				ls1 = ls2;
				ls2 = temp;
			}
			//cout << "ls1 = " << ls1 << endl;
			//cout << "ls2= " << ls2 << endl;
			int ls_job1, ls_job2;
			ls_job1 = ls_indiv.Job_C[ls1];
			ls_job2 = ls_indiv.Job_C[ls2];
			//cout << "ls_job1 = " << ls_job1 << endl;
			//cout << "ls_job2 = " << ls_job2 << endl;
			int ls_operation1, ls_operation2;
			ls_operation1 = ls_indiv.Operation_C[ls1];
			ls_operation2 = ls_indiv.Operation_C[ls2];
			//cout << "ls_operation1 = " << ls_operation1 << endl;
			//cout << "ls_operation2 = " << ls_operation2 << endl;

			////step2：找出染色体中这两个作业的位置索引
			////找第ls_operation1次出现的ls_job1
			int ls_index1, ls_index2;
			int ls_count1 = 0;
			for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
			{
				if (ls_indiv.v_chromosome1[jj].operation_number == ls_job1)
				{
					ls_count1++;
				}
				if (ls_count1 == ls_operation1)
				{
					ls_index1 = jj;
					break;
				}
			}
			int ls_count2 = 0;
			for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
			{
				if (ls_indiv.v_chromosome1[jj].operation_number == ls_job2)
				{
					ls_count2++;
				}
				if (ls_count2 == ls_operation2)
				{
					ls_index2 = jj;
					break;
				}
			}
			//cout << "ls_index1 = " << ls_index1 << endl;
			//cout << "ls_index2 = " << ls_index2 << endl;


			////step3：交换两个作业在工序序列中的位置
			int ls_temp = ls_indiv.v_chromosome1[ls_index1].operation_number;
			ls_indiv.v_chromosome1[ls_index1].operation_number = ls_indiv.v_chromosome1[ls_index2].operation_number;
			ls_indiv.v_chromosome1[ls_index2].operation_number = ls_temp;
			//同时，更新它们的job信息
			int temp_job_number = ls_indiv.v_chromosome1[ls_index1].job_number;
			ls_indiv.v_chromosome1[ls_index1].job_number = ls_indiv.v_chromosome1[ls_index2].job_number;
			ls_indiv.v_chromosome1[ls_index2].job_number = temp_job_number;
			//并根据job信息更新它们的operation_index信息
			for (int k = 0; k < number_of_jobs; k++)//判断是每个job的第几道工序
			{
				int current_job_number = k + 1;
				int count = 0;
				for (int c = 0; c < number_of_jobs * number_of_operations; c++)
				{
					if (current_job_number == ls_indiv.v_chromosome1[c].job_number)
					{
						count = count + 1;
						ls_indiv.v_chromosome1[c].operation_index = count;
					}
					continue;
				}
			}

		}
	}
	else
	{
		//cout << "对排产路径上的job进行调整！" << endl;
		////step1：随机选中两个关键job
		int ls_size = ls_indiv.Job_C.size();
		int ls1 = rand() % ls_size;
		int ls2 = rand() % ls_size;
		while (ls1 == ls2)
		{
			ls2 = rand() % ls_size;
		}
		if (ls1 > ls2)
		{
			int temp = ls1;
			ls1 = ls2;
			ls2 = temp;
		}
		//cout << "ls1 = " << ls1 << endl;
		//cout << "ls2= " << ls2 << endl;
		int ls_job1, ls_job2;
		ls_job1 = ls_indiv.Job_C[ls1];
		ls_job2 = ls_indiv.Job_C[ls2];
		//cout << "ls_job1 = " << ls_job1 << endl;
		//cout << "ls_job2 = " << ls_job2 << endl;
		int ls_operation1, ls_operation2;
		ls_operation1 = ls_indiv.Operation_C[ls1];
		ls_operation2 = ls_indiv.Operation_C[ls2];
		//cout << "ls_operation1 = " << ls_operation1 << endl;
		//cout << "ls_operation2 = " << ls_operation2 << endl;

		////step2：找出染色体中这两个作业的位置索引
		////找第ls_operation1次出现的ls_job1
		int ls_index1, ls_index2;
		int ls_count1 = 0;
		for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
		{
			if (ls_indiv.v_chromosome1[jj].operation_number == ls_job1)
			{
				ls_count1++;
			}
			if (ls_count1 == ls_operation1)
			{
				ls_index1 = jj;
				break;
			}
		}
		int ls_count2 = 0;
		for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
		{
			if (ls_indiv.v_chromosome1[jj].operation_number == ls_job2)
			{
				ls_count2++;
			}
			if (ls_count2 == ls_operation2)
			{
				ls_index2 = jj;
				break;
			}
		}
		//cout << "ls_index1 = " << ls_index1 << endl;
		//cout << "ls_index2 = " << ls_index2 << endl;


		////step3：交换两个作业在工序序列中的位置
		int ls_temp = ls_indiv.v_chromosome1[ls_index1].operation_number;
		ls_indiv.v_chromosome1[ls_index1].operation_number = ls_indiv.v_chromosome1[ls_index2].operation_number;
		ls_indiv.v_chromosome1[ls_index2].operation_number = ls_temp;
		//同时，更新它们的job信息
		int temp_job_number = ls_indiv.v_chromosome1[ls_index1].job_number;
		ls_indiv.v_chromosome1[ls_index1].job_number = ls_indiv.v_chromosome1[ls_index2].job_number;
		ls_indiv.v_chromosome1[ls_index2].job_number = temp_job_number;
		//并根据job信息更新它们的operation_index信息
		for (int k = 0; k < number_of_jobs; k++)//判断是每个job的第几道工序
		{
			int current_job_number = k + 1;
			int count = 0;
			for (int c = 0; c < number_of_jobs * number_of_operations; c++)
			{
				if (current_job_number == ls_indiv.v_chromosome1[c].job_number)
				{
					count = count + 1;
					ls_indiv.v_chromosome1[c].operation_index = count;
				}
				continue;
			}
		}
	}
}

void QPacking::ls_operation6(CIndividual& ls_indiv, vector<Item>& v_product)
{
	//cout << "对关键路径进行insert操作！" << endl;

	//cout << "排样阶段关键路径job索引号：" << endl;
	//for (int g = 0; g < ls_indiv.Product_C.size(); g++)
	//{
	//	cout << ls_indiv.Product_C[g] << " ";
	//}
	//cout << endl;

	//cout << "制造阶段关键路径（正）涉及的job索引号，operation序号索引号，machine索引号：" << endl;
	//for (int k = 0; k < ls_indiv.Operation_C.size(); k++)
	//{
	//	int job_index = ls_indiv.Job_C[k] - 1;
	//	cout << "作业索引：" << job_index << " ";
	//	int operation_index = ls_indiv.Operation_C[k] - 1;
	//	cout << "工序索引：" << operation_index << " ";
	//	int machine_index = ls_indiv.Machine_C[k];
	//	cout << "机器索引：" << machine_index << " ";//机器索引号
	//	cout << endl;
	//}
	//cout << endl;
	//system("pause");

	////判断排样阶段的规模
	if (ls_indiv.Product_C.size() >= 2)
	{
		//cout << "对排样或排产关键路径上的job进行调整！" << endl;
		int random_number = rand() % 2;
		if (random_number == 0)
		{
			//cout << "对排样路径上的job进行调整！" << endl;
			////step1：随机选取关键路径上的两个不重复的job
			int key_size = ls_indiv.Product_C.size();
			int ls1 = rand() % key_size;
			int ls2 = rand() % key_size;
			while (ls1 == ls2)
			{
				ls2 = rand() % key_size;
			}
			if (ls1 > ls2)
			{
				int temp = ls1;
				ls1 = ls2;
				ls2 = temp;
			}
			int ls_job1, ls_job2;
			ls_job1 = ls_indiv.Product_C[ls1] + 1;
			ls_job2 = ls_indiv.Product_C[ls2] + 1;
			//cout << "ls_job1 = " << ls_job1 << endl;
			//cout << "ls_job2 = " << ls_job2 << endl;

			////step2：在ls_indiv染色体上寻找这俩job的位置索引
			int ls_pos_index1 = 0;
			int ls_pos_index2 = 0;
			for (int u = 0; u < ls_indiv.v_chromosome2.size(); u++)
			{
				if (ls_indiv.v_chromosome2[u].job_number == ls_job1)
				{
					ls_pos_index1 = u;
					break;
				}
			}
			//cout << endl;
			for (int u = 0; u < ls_indiv.v_chromosome2.size(); u++)
			{
				if (ls_indiv.v_chromosome2[u].job_number == ls_job2)
				{
					ls_pos_index2 = u;
					break;
				}
			}
			//cout << "ls_pos_index1 = " << ls_pos_index1 << endl;
			//cout << "ls_pos_index2 = " << ls_pos_index2 << endl;

			////step3：在ls_indiv染色体上删掉靠后的job
			ls_indiv.v_chromosome2.erase(ls_indiv.v_chromosome2.begin() + ls_pos_index2);
			int current_size = ls_indiv.v_chromosome2.size();
			//cout << "current_size = " << current_size << endl;
			//然后再把它插入到靠前一点的operation的前面位置
			CChromosome tttt;
			tttt.job_number = ls_job2;
			ls_indiv.v_chromosome2.insert(ls_indiv.v_chromosome2.begin() + ls_pos_index1, tttt);
			current_size = ls_indiv.v_chromosome2.size();
			//cout << "current_size = " << current_size << endl;
		}
		else
		{
			//cout << "对排产路径上的job进行调整！" << endl;
			////step1：随机选中两个关键job
			int ls_size = ls_indiv.Job_C.size();
			int ls1 = rand() % ls_size;
			int ls2 = rand() % ls_size;
			while (ls1 == ls2)
			{
				ls2 = rand() % ls_size;
			}
			if (ls1 > ls2)
			{
				int temp = ls1;
				ls1 = ls2;
				ls2 = temp;
			}
			//cout << "ls1 = " << ls1 << endl;
			//cout << "ls2 = " << ls2 << endl;
			int ls_job1, ls_job2;
			ls_job1 = ls_indiv.Job_C[ls1];
			ls_job2 = ls_indiv.Job_C[ls2];
			//cout << "ls_job1 = " << ls_job1 << endl;
			//cout << "ls_job2 = " << ls_job2 << endl;
			int ls_operation1, ls_operation2;
			ls_operation1 = ls_indiv.Operation_C[ls1];
			ls_operation2 = ls_indiv.Operation_C[ls2];
			//cout << "ls_operation1 = " << ls_operation1 << endl;
			//cout << "ls_operation2 = " << ls_operation2 << endl;

			////step2：找出染色体中这两个作业的位置索引
			////找第ls_operation1次出现的ls_job1
			int ls_index1, ls_index2;
			int ls_count1 = 0;
			for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
			{
				if (ls_indiv.v_chromosome1[jj].operation_number == ls_job1)
				{
					ls_count1++;
				}
				if (ls_count1 == ls_operation1)
				{
					ls_index1 = jj;
					break;
				}
			}
			int ls_count2 = 0;
			for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
			{
				if (ls_indiv.v_chromosome1[jj].operation_number == ls_job2)
				{
					ls_count2++;
				}
				if (ls_count2 == ls_operation2)
				{
					ls_index2 = jj;
					break;
				}
			}
			//cout << "ls_index1 = " << ls_index1 << endl;
			//cout << "ls_index2 = " << ls_index2 << endl;


			////step3：将靠后的operation插入靠前的operation的前面，机器向量不变
			//先将选中的靠后一点的operation在染色体中删除
			ls_indiv.v_chromosome1.erase(ls_indiv.v_chromosome1.begin() + ls_index2);
			int current_size = ls_indiv.v_chromosome1.size();
			//cout << "current_size = " << current_size << endl;
			//然后再把它插入到靠前一点的operation的前面位置
			CChromosome tttt;
			tttt.operation_number = ls_job2;
			ls_indiv.v_chromosome1.insert(ls_indiv.v_chromosome1.begin() + ls_index1, tttt);
			current_size = ls_indiv.v_chromosome1.size();
			//cout << "current_size = " << current_size << endl;
			//同时，更新它们的job信息
			for (int k = 0; k < number_of_jobs * number_of_operations; k++)
			{
				ls_indiv.v_chromosome1[k].job_number = ls_indiv.v_chromosome1[k].operation_number;
			}
			//并根据job信息更新它们的operation_index信息
			for (int k = 0; k < number_of_jobs; k++)//判断是每个job的第几道工序
			{
				int current_job_number = k + 1;
				int count = 0;
				for (int c = 0; c < number_of_jobs * number_of_operations; c++)
				{
					if (current_job_number == ls_indiv.v_chromosome1[c].job_number)
					{
						count = count + 1;
						ls_indiv.v_chromosome1[c].operation_index = count;
					}
					continue;
				}
			}
		}
	}
	else
	{
		//cout << "对排产路径上的job进行调整！" << endl;
		////step1：随机选中两个关键job
		int ls_size = ls_indiv.Job_C.size();
		int ls1 = rand() % ls_size;
		int ls2 = rand() % ls_size;
		while (ls1 == ls2)
		{
			ls2 = rand() % ls_size;
		}
		if (ls1 > ls2)
		{
			int temp = ls1;
			ls1 = ls2;
			ls2 = temp;
		}
		//cout << "ls1 = " << ls1 << endl;
		//cout << "ls2 = " << ls2 << endl;
		int ls_job1, ls_job2;
		ls_job1 = ls_indiv.Job_C[ls1];
		ls_job2 = ls_indiv.Job_C[ls2];
		//cout << "ls_job1 = " << ls_job1 << endl;
		//cout << "ls_job2 = " << ls_job2 << endl;
		int ls_operation1, ls_operation2;
		ls_operation1 = ls_indiv.Operation_C[ls1];
		ls_operation2 = ls_indiv.Operation_C[ls2];
		//cout << "ls_operation1 = " << ls_operation1 << endl;
		//cout << "ls_operation2 = " << ls_operation2 << endl;

		////step2：找出染色体中这两个作业的位置索引
		////找第ls_operation1次出现的ls_job1
		int ls_index1, ls_index2;
		int ls_count1 = 0;
		for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
		{
			if (ls_indiv.v_chromosome1[jj].operation_number == ls_job1)
			{
				ls_count1++;
			}
			if (ls_count1 == ls_operation1)
			{
				ls_index1 = jj;
				break;
			}
		}
		int ls_count2 = 0;
		for (int jj = 0; jj < number_of_jobs * number_of_operations; jj++)
		{
			if (ls_indiv.v_chromosome1[jj].operation_number == ls_job2)
			{
				ls_count2++;
			}
			if (ls_count2 == ls_operation2)
			{
				ls_index2 = jj;
				break;
			}
		}
		//cout << "ls_index1 = " << ls_index1 << endl;
		//cout << "ls_index2 = " << ls_index2 << endl;


		////step3：将靠后的operation插入靠前的operation的前面，机器向量不变
		//先将选中的靠后一点的operation在染色体中删除
		ls_indiv.v_chromosome1.erase(ls_indiv.v_chromosome1.begin() + ls_index2);
		int current_size = ls_indiv.v_chromosome1.size();
		//cout << "current_size = " << current_size << endl;
		//然后再把它插入到靠前一点的operation的前面位置
		CChromosome tttt;
		tttt.operation_number = ls_job2;
		ls_indiv.v_chromosome1.insert(ls_indiv.v_chromosome1.begin() + ls_index1, tttt);
		current_size = ls_indiv.v_chromosome1.size();
		//cout << "current_size = " << current_size << endl;
		//同时，更新它们的job信息
		for (int k = 0; k < number_of_jobs * number_of_operations; k++)
		{
			ls_indiv.v_chromosome1[k].job_number = ls_indiv.v_chromosome1[k].operation_number;
		}
		//并根据job信息更新它们的operation_index信息
		for (int k = 0; k < number_of_jobs; k++)//判断是每个job的第几道工序
		{
			int current_job_number = k + 1;
			int count = 0;
			for (int c = 0; c < number_of_jobs * number_of_operations; c++)
			{
				if (current_job_number == ls_indiv.v_chromosome1[c].job_number)
				{
					count = count + 1;
					ls_indiv.v_chromosome1[c].operation_index = count;
				}
				continue;
			}
		}
	}
}

void QPacking::ls_operation7(CIndividual& ls_indiv, vector<Item>& v_product)
{
	//cout << "对关键路径进行exchange操作！" << endl;

	//cout << "排样阶段关键路径job索引号：" << endl;
	//for (int g = 0; g < ls_indiv.Product_C.size(); g++)
	//{
	//	cout << ls_indiv.Product_C[g] << " ";
	//}
	//cout << endl;

	//cout << "制造阶段关键路径（正）涉及的job索引号，operation序号索引号，machine索引号：" << endl;
	//for (int k = 0; k < ls_indiv.Operation_C.size(); k++)
	//{
	//	int job_index = ls_indiv.Job_C[k] - 1;
	//	cout << "作业索引：" << job_index << " ";
	//	int operation_index = ls_indiv.Operation_C[k] - 1;
	//	cout << "工序索引：" << operation_index << " ";
	//	int machine_index = ls_indiv.Machine_C[k];
	//	cout << "机器索引：" << machine_index << " ";//机器索引号
	//	cout << endl;
	//}
	//cout << endl;
	//system("pause");

	int ls_size = ls_indiv.Job_C.size();
	//cout << "ls_size = " << ls_size << endl;
	//随机选中1个关键job
	int ls = rand() % ls_size;
	//cout << "ls = " << ls << endl;
	int ls_job;
	ls_job = ls_indiv.Job_C[ls];
	//cout << "ls_job = " << ls_job << endl;
	int ls_operation;
	ls_operation = ls_indiv.Operation_C[ls];
	//cout << "ls_operation = " << ls_operation << endl;
	//获取该job的该道工序的可使用机器数量
	int operation_machine_size = v_available_machines[ls_job - 1][ls_operation - 1].size();
	//cout << "operation_machine_size = " << operation_machine_size << endl;
	if (operation_machine_size >= 2)
	{
		int rand_machine_number_index = rand() % operation_machine_size;
		//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
		int rand_machine_number = v_available_machines[ls_job - 1][ls_operation - 1][rand_machine_number_index];
		//cout << "rand_machine_number = " << rand_machine_number << endl;
		int index = (ls_job - 1) * number_of_operations + number_of_jobs * number_of_operations + (ls_operation - 1);
		//cout << "index = " << index << endl;
		int current_machine_number = ls_indiv.v_chromosome1[index].machine_number;
		while (current_machine_number == rand_machine_number)
		{
			rand_machine_number_index = rand() % operation_machine_size;
			//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
			rand_machine_number = v_available_machines[ls_job - 1][ls_operation - 1][rand_machine_number_index];
			//cout << "rand_machine_number = " << rand_machine_number << endl;
		}
		ls_indiv.v_chromosome1[index].machine_number = rand_machine_number;
	}
	//system("pause");
}
