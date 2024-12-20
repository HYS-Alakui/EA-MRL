#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"

void QPacking::upper_mutate(CIndividual& t, double rate)//�Ը�����б��죬rate�Ǳ����ʣ�t�Ǵ�������child1������evovle��
{
	if (rand() / (RAND_MAX * 1.0) <= rate)   //����һ���������rate�Ƚ��ж��Ƿ���б��죬�������õ��ǰٷְٱ��죬�ʿ϶��Ըø�����б���
	{
		////step1:�Թ������������ѡ��������ͬ�ĵ㣬Ȼ����з�ת
		int cutpoint1, cutpoint2;//���������е㣻			
		cutpoint1 = rand() % (number_of_jobs * number_of_operations);
		cutpoint2 = rand() % (number_of_jobs * number_of_operations);
		while (cutpoint1 == cutpoint2)//�������е���ͬ
		{
			cutpoint2 = rand() % (number_of_jobs * number_of_operations);//�����²���һ���е�2
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
		vector <int>().swap(v_oper_part_list);//��������Ԫ�ط����������ʹ��reverse��ת
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
		reverse(v_oper_part_list.begin(), v_oper_part_list.end()); //��v_operation_part_list�еĴ�v_operation_part_list.begin()������������v_operation_part_list.end()������������Ԫ�ص��ã���v_operation_part_list��Ԫ��Ϊ1,2,3,4,���ú�Ϊ4,3,2,1
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
			t.v_chromosome1[j].job_number = jobNo_j;//job_number��֮����
		}
		//system("pause");

		//operation_index��֮����
		for (int k = 0; k < number_of_jobs; k++)//�ж���ÿ��job�ĵڼ�������
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
		////�������������������Ϣ
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


		////step4:�Ի������������ѡ1������Ȼ�������������
		////���ѡ��һ�������λ��������ȡ�乤���ź͹�����ű��
		int ls = rand() % (number_of_jobs * number_of_operations);
		//cout << "ls = " << ls << endl;
		int ls_operation = t.v_chromosome1[ls].operation_number;
		//cout << "ls_operation =" << ls_operation << endl;
		int ls_operation_xuhao = t.v_chromosome1[ls].operation_index;
		//cout << "ls_operation_xuhao =" << ls_operation_xuhao << endl;
		////��ȡ��job�ĸõ�����Ŀ�ʹ�û�������
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
		////���������������Ϣ
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
		//���� ����������ɱ���
		//system("pause");
	}
	else//������
	{
		//cout << "������" << endl;
		t = t;
	}

	//cout << "������Ӵ�����Ĺ���ͻ���������" << endl;
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