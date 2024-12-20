#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"

void QPacking::upper_mutate(CIndividual& t, double rate)//对个体进行变异，rate是变异率；t是传进来的child1对象，在evovle中
{
	if (rand() / (RAND_MAX * 1.0) <= rate)   //产生一个随机数与rate比较判断是否进行变异，由于设置的是百分百变异，故肯定对该个体进行变异
	{
		////step1:对工序向量，随机选中两个不同的点，然后进行翻转
		int cutpoint1, cutpoint2;//工厂序列切点；			
		cutpoint1 = rand() % (number_of_jobs * number_of_operations);
		cutpoint2 = rand() % (number_of_jobs * number_of_operations);
		while (cutpoint1 == cutpoint2)//若两个切点相同
		{
			cutpoint2 = rand() % (number_of_jobs * number_of_operations);//则重新产生一个切点2
		}
		int temp_cut;
		if (cutpoint1 > cutpoint2)
		{
			temp_cut = cutpoint1;
			cutpoint1 = cutpoint2;
			cutpoint2 = temp_cut;
		}
		//cout << "cutpoint1 = " << cutpoint1 << endl;
		//cout << "cutpoint2 = " << cutpoint2 << endl;

		int operNo;
		vector <int> v_oper_part_list;
		vector <int>().swap(v_oper_part_list);//把两点间的元素放在数组里，好使用reverse翻转
		for (int j = cutpoint1; j <= cutpoint2; j++)
		{
			operNo = t.v_chromosome1[j].operation_number;
			v_oper_part_list.push_back(operNo);
		}
		//for (int j = 0; j < v_oper_part_list.size(); j++)
		//{
		//	cout << v_oper_part_list[j] << " ";
		//}
		//system("pause");
		reverse(v_oper_part_list.begin(), v_oper_part_list.end()); //对v_operation_part_list中的从v_operation_part_list.begin()（包括它）到v_operation_part_list.end()（包括它）的元素倒置，如v_operation_part_list中元素为1,2,3,4,倒置后为4,3,2,1
		//for (int j = 0; j < v_oper_part_list.size(); j++)
		//{
		//	cout << v_oper_part_list[j] << " ";
		//}
		//system("pause");
		int jobNo_j;
		for (int j = cutpoint1; j <= cutpoint2; j++)
		{
			jobNo_j = v_oper_part_list[j - cutpoint1];
			//cout << "jobNo_j = " << jobNo_j << endl;
			t.v_chromosome1[j].operation_number = jobNo_j;
			t.v_chromosome1[j].job_number = jobNo_j;//job_number随之更新
		}
		//system("pause");

		//operation_index随之更新
		for (int k = 0; k < number_of_jobs; k++)//判断是每个job的第几道工序
		{
			int current_job_number = k + 1;
			int count = 0;
			for (int c = 0; c < number_of_jobs * number_of_operations; c++)
			{
				if (current_job_number == t.v_chromosome1[c].job_number)
				{
					count = count + 1;
					t.v_chromosome1[c].operation_index = count;
				}
				continue;
			}
		}
		////输出工序序列向量的信息
		//for (int k = 0; k < number_of_jobs * number_of_operations; k++)
		//{
		//	cout << t.v_chromosome1[k].operation_number << " ";
		//}
		//cout << endl;
		//for (int k = 0; k < number_of_jobs * number_of_operations; k++)
		//{
		//	cout << t.v_chromosome1[k].operation_index << " ";
		//}
		//cout << endl;
		//for (int k = 0; k < number_of_jobs * number_of_operations; k++)
		//{
		//	cout << t.v_chromosome1[k].job_number << " ";
		//}
		//cout << endl;
		//system("pause");


		////step4:对机器向量，随机选1个工序然后更换其机器编号
		////随机选中一个工序的位置索引获取其工序编号和工序序号编号
		int ls = rand() % (number_of_jobs * number_of_operations);
		//cout << "ls = " << ls << endl;
		int ls_operation = t.v_chromosome1[ls].operation_number;
		//cout << "ls_operation =" << ls_operation << endl;
		int ls_operation_xuhao = t.v_chromosome1[ls].operation_index;
		//cout << "ls_operation_xuhao =" << ls_operation_xuhao << endl;
		////获取该job的该道工序的可使用机器数量
		int operation_machine_size = v_available_machines[ls_operation - 1][ls_operation_xuhao - 1].size();
		//cout << "operation_machine_size = " << operation_machine_size << endl;
		if (operation_machine_size >= 2)
		{
			int rand_machine_number_index = rand() % operation_machine_size;
			//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
			int rand_machine_number = v_available_machines[ls_operation - 1][ls_operation_xuhao - 1][rand_machine_number_index];
			//cout << "rand_machine_number = " << rand_machine_number << endl;
			int index = number_of_jobs * number_of_operations + (ls_operation - 1) * number_of_operations + (ls_operation_xuhao - 1);
			//cout << "index = " << index << endl;
			int current_machine_number = t.v_chromosome1[index].machine_number;
			//cout << "current_machine_number =" << current_machine_number << endl;
			while (current_machine_number == rand_machine_number)
			{
				rand_machine_number_index = rand() % operation_machine_size;
				//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
				rand_machine_number = v_available_machines[ls_operation - 1][ls_operation_xuhao - 1][rand_machine_number_index];
				//cout << "rand_machine_number = " << rand_machine_number << endl;
			}
			t.v_chromosome1[index].machine_number = rand_machine_number;
		}
		//system("pause");
		////输出机器向量的信息
		//for (int k = number_of_jobs * number_of_operations; k < t.v_chromosome1.size(); k++)
		//{
		//	cout << t.v_chromosome1[k].machine_number << " ";
		//}
		//cout << endl;
		//for (int k = number_of_jobs * number_of_operations; k < t.v_chromosome1.size(); k++)
		//{
		//	cout << t.v_chromosome1[k].job_number << " ";
		//}
		//cout << endl;
		//以上 各向量均完成变异
		//system("pause");
	}
	else//不变异
	{
		//cout << "不变异" << endl;
		t = t;
	}

	//cout << "变异后子代个体的工序和机器向量：" << endl;
	//for (int j = 0; j < number_of_jobs*number_of_operations; j++)
	//{
	//	cout << t.v_chromosome1[j].operation_number << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < number_of_jobs*number_of_operations; j++)
	//{
	//	cout << t.v_chromosome1[j].operation_index << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs * number_of_operations; j < t.v_chromosome1.size(); j++)
	//{
	//	cout << t.v_chromosome1[j].machine_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs * number_of_operations; j < t.v_chromosome1.size(); j++)
	//{
	//	cout << t.v_chromosome1[j].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
}