#include "headfile.h"
#include "Individual.h"
#include "Qpacking.h"
#include "rankSequ.h"
#include "Chromosome.h"
#include "Item.h"
#include <algorithm>
#include <map>
#include <iomanip>
#include <omp.h>

void QPacking::paraller_search(vector <vector<CIndividual>>& v_new_Chromo, vector<CIndividual>& v_new_TotalChromo, vector<Item>& v_product)
{
	////step1: 对DC获得的新种群v_new_TotalChromo/v_new_Chromo中的每个个体独立进行7种Local-Search操作（即7个动作），得到7个LS种群v_ls_Chromo
	#pragma omp parallel for num_threads(7)
	for (int ls_no = 1; ls_no <= 7; ls_no++)
	{
		//cout << "do this part by thread " << omp_get_thread_num() << endl;
		if (ls_no == 1)
		{
			vector <vector<CIndividual>> v_new_Chromo_temp1(v_new_Chromo); //对临时种群v_new_Chromo_temp1进行local_search操作1
			local_search1(v_new_Chromo_temp1, v_product);//获得LS种群v_ls_Chromo1
		}
		else if (ls_no == 2)
		{
			vector <vector<CIndividual>> v_new_Chromo_temp2(v_new_Chromo); //对临时种群v_new_Chromo_temp2进行local_search操作2
			local_search2(v_new_Chromo_temp2, v_product);//获得LS种群v_ls_Chromo2
		}
		else if (ls_no == 3)
		{
			vector <vector<CIndividual>> v_new_Chromo_temp3(v_new_Chromo); //对临时种群v_new_Chromo_temp3进行local_search操作3
			local_search3(v_new_Chromo_temp3, v_product);//获得LS种群v_ls_Chromo3
		}
		else if (ls_no == 4)
		{
			vector <vector<CIndividual>> v_new_Chromo_temp4(v_new_Chromo); //对临时种群v_new_Chromo_temp4进行local_search操作4
			local_search4(v_new_Chromo_temp4, v_product);//获得LS种群v_ls_Chromo4
		}
		else if (ls_no == 5)
		{
			vector <vector<CIndividual>> v_new_Chromo_temp5(v_new_Chromo); //对临时种群v_new_Chromo_temp5进行local_search操作5
			local_search5(v_new_Chromo_temp5, v_product);//获得LS种群v_ls_Chromo5
		}
		else if (ls_no == 6)
		{
			vector <vector<CIndividual>> v_new_Chromo_temp6(v_new_Chromo); //对临时种群v_new_Chromo_temp6进行local_search操作6
			local_search6(v_new_Chromo_temp6, v_product);//获得LS种群v_ls_Chromo6
		}
		else if (ls_no == 7)
		{
			vector <vector<CIndividual>> v_new_Chromo_temp7(v_new_Chromo); //对临时种群v_new_Chromo_temp7进行local_search操作7
			local_search7(v_new_Chromo_temp7, v_product);//获得LS种群v_ls_Chromo7
		}
	}

	////step2: 求7个并行运算获得的LS种群的适值
	vector<CIndividual>().swap(v_ls_TotalChromo1);
	vector<CIndividual>().swap(v_ls_TotalChromo2);
	vector<CIndividual>().swap(v_ls_TotalChromo3);
	vector<CIndividual>().swap(v_ls_TotalChromo4);
	vector<CIndividual>().swap(v_ls_TotalChromo5);
	vector<CIndividual>().swap(v_ls_TotalChromo6);
	vector<CIndividual>().swap(v_ls_TotalChromo7);
	for (int mm = 0; mm < v_ls_Chromo1.size(); mm++)
	{
		for (int nn = 0; nn < v_ls_Chromo1[mm].size(); nn++)
		{
			upper_evaluate(v_ls_Chromo1[mm][nn], board_width, board_height, v_product);
			v_ls_TotalChromo1.push_back(v_ls_Chromo1[mm][nn]);
			upper_evaluate(v_ls_Chromo2[mm][nn], board_width, board_height, v_product);
			v_ls_TotalChromo2.push_back(v_ls_Chromo2[mm][nn]);
			upper_evaluate(v_ls_Chromo3[mm][nn], board_width, board_height, v_product);
			v_ls_TotalChromo3.push_back(v_ls_Chromo3[mm][nn]);
			upper_evaluate(v_ls_Chromo4[mm][nn], board_width, board_height, v_product);
			v_ls_TotalChromo4.push_back(v_ls_Chromo4[mm][nn]);
			upper_evaluate(v_ls_Chromo5[mm][nn], board_width, board_height, v_product);
			v_ls_TotalChromo5.push_back(v_ls_Chromo5[mm][nn]);
			upper_evaluate(v_ls_Chromo6[mm][nn], board_width, board_height, v_product);
			v_ls_TotalChromo6.push_back(v_ls_Chromo6[mm][nn]);
			upper_evaluate(v_ls_Chromo7[mm][nn], board_width, board_height, v_product);
			v_ls_TotalChromo7.push_back(v_ls_Chromo7[mm][nn]);
		}
	}
	//cout << "LS后的新种群LS1：" << endl;
	//out_result(v_ls_Chromo1, v_ls_TotalChromo1);
	//cout << "LS后的新种群LS2：" << endl;
	//out_result(v_ls_Chromo2, v_ls_TotalChromo2);
	//cout << "LS后的新种群LS3：" << endl;
	//out_result(v_ls_Chromo3, v_ls_TotalChromo3);
	//cout << "LS后的新种群LS4：" << endl;
	//out_result(v_ls_Chromo4, v_ls_TotalChromo4);
	//cout << "LS后的新种群LS5：" << endl;
	//out_result(v_ls_Chromo5, v_ls_TotalChromo5);
	//cout << "LS后的新种群LS6：" << endl;
	//out_result(v_ls_Chromo6, v_ls_TotalChromo6);
	//cout << "LS后的新种群LS7：" << endl;
	//out_result(v_ls_Chromo7, v_ls_TotalChromo7);

	////step3: 比较LS种群与未进行LS的种群的支配性，更新奖励、动作、状态和Q表		
	Learning_Rate = 1 - 0.9 * (outer_iteration_count / outer_iteration_count_max);
	#pragma omp parallel for num_threads(7)
	for (int ls_no = 1; ls_no <= 7; ls_no++)
	{
		//cout << "Do this part by thread " << omp_get_thread_num() << endl;
		if (ls_no == 1)
		{
			vector <CIndividual> v_new_TotalChromo_temp1(v_new_TotalChromo);
			C_metric1(v_ls_TotalChromo1, v_new_TotalChromo_temp1, C_value_v1);//新种群支配原种群的比例
			C_metric1(v_new_TotalChromo_temp1, v_ls_TotalChromo1, C_value_t1);//原种群支配新种群的比例
			difference_C1 = C_value_v1 - C_value_t1;
			//cout << "difference_C1 = " << difference_C1 << endl;
			DV_metric1(v_ls_TotalChromo1, DV_value_v1);
			DV_metric1(v_new_TotalChromo_temp1, DV_value_t1);
			difference_DV1 = DV_value_v1 - DV_value_t1;
			//cout << "difference_DV1 = " << difference_DV1 << endl;

			Action_Current1 = ls_no;//获得动作
			//cout << "当前动作Action_Current1 = " << Action_Current1 << endl;
			double REWARD1 = 0;//初始化奖励值
			if (difference_C1 > 0.0 && difference_DV1 > 0.0)//更新状态和奖励值
			{
				State_Next1 = 1;
				REWARD1 = 10;
			}
			else if (difference_C1 > 0.0 && difference_DV1 <= 0)
			{
				State_Next1 = 2;
				REWARD1 = 5;
			}
			else if (difference_C1 <= 0.0 && difference_DV1 > 0)
			{
				State_Next1 = 3;
				REWARD1 = 5;
			}
			else
			{
				State_Next1 = 4;
				REWARD1 = 0;
			}
			//cout << "当前状态State_Current1 = " << State_Current1 << endl;
			//cout << "下一个状态State_Next1 = " << State_Next1 << endl;
			//cout << "获得奖励REWARD1 = " << REWARD1 << endl;

			Q_TABLE[State_Current1 - 1][Action_Current1 - 1] = Q_TABLE[State_Current1 - 1][Action_Current1 - 1] + Learning_Rate * (REWARD1 + Discount_Factor * Q_TABLE[State_Next1 - 1][Action_Current1 - 1] - Q_TABLE[State_Current1 - 1][Action_Current1 - 1]);
			State_Current1 = State_Next1;//更新下一次进化时的状态
		}
		else if (ls_no == 2)
		{
			vector <CIndividual> v_new_TotalChromo_temp2(v_new_TotalChromo);
			C_metric2(v_ls_TotalChromo2, v_new_TotalChromo_temp2, C_value_v2);//新种群支配原种群的比例
			C_metric2(v_new_TotalChromo_temp2, v_ls_TotalChromo2, C_value_t2);//原种群支配新种群的比例
			difference_C2 = C_value_v2 - C_value_t2;
			//cout << "difference_C2 = " << difference_C2 << endl;
			DV_metric2(v_ls_TotalChromo2, DV_value_v2);
			DV_metric2(v_new_TotalChromo_temp2, DV_value_t2);
			difference_DV2 = DV_value_v2 - DV_value_t2;
			//cout << "difference_DV2 = " << difference_DV2 << endl;

			Action_Current2 = ls_no;
			//cout << "当前动作Action_Current2 = " << Action_Current2 << endl;
			double REWARD2 = 0;//奖励值
			if (difference_C2 > 0.0 && difference_DV2 > 0.0)
			{
				State_Next2 = 1;
				REWARD2 = 10;
			}
			else if (difference_C2 > 0.0 && difference_DV2 <= 0)
			{
				State_Next2 = 2;
				REWARD2 = 5;
			}
			else if (difference_C2 <= 0.0 && difference_DV2 > 0)
			{
				State_Next2 = 3;
				REWARD2 = 5;
			}
			else
			{
				State_Next2 = 4;
				REWARD2 = 0;
			}
			//cout << "当前状态State_Current2 = " << State_Current2 << endl;
			//cout << "下一个状态State_Next2 = " << State_Next2 << endl;
			//cout << "获得奖励REWARD2 = " << REWARD2 << endl;

			Q_TABLE[State_Current2 - 1][Action_Current2 - 1] = Q_TABLE[State_Current2 - 1][Action_Current2 - 1] + Learning_Rate * (REWARD2 + Discount_Factor * Q_TABLE[State_Next2 - 1][Action_Current2 - 1] - Q_TABLE[State_Current2 - 1][Action_Current2 - 1]);
			State_Current2 = State_Next2;//更新下一次进化时的状态
		}
		else if (ls_no == 3)
		{
			vector <CIndividual> v_new_TotalChromo_temp3(v_new_TotalChromo);
			C_metric3(v_ls_TotalChromo3, v_new_TotalChromo_temp3, C_value_v3);//新种群支配原种群的比例
			C_metric3(v_new_TotalChromo_temp3, v_ls_TotalChromo3, C_value_t3);//原种群支配新种群的比例
			difference_C3 = C_value_v3 - C_value_t3;
			//cout << "difference_C3 = " << difference_C3 << endl;
			DV_metric3(v_ls_TotalChromo3, DV_value_v3);
			DV_metric3(v_new_TotalChromo_temp3, DV_value_t3);
			difference_DV3 = DV_value_v3 - DV_value_t3;
			//cout << "difference_DV3 = " << difference_DV3 << endl;

			Action_Current3 = ls_no;
			//cout << "当前动作Action_Current3 = " << Action_Current3 << endl;
			double REWARD3 = 0;//奖励值
			if (difference_C3 > 0.0 && difference_DV3 > 0.0)
			{
				State_Next3 = 1;
				REWARD3 = 10;
			}
			else if (difference_C3 > 0.0 && difference_DV3 <= 0)
			{
				State_Next3 = 2;
				REWARD3 = 5;
			}
			else if (difference_C3 <= 0.0 && difference_DV3 > 0)
			{
				State_Next3 = 3;
				REWARD3 = 5;
			}
			else
			{
				State_Next3 = 4;
				REWARD3 = 0;
			}
			//cout << "当前状态State_Current3 = " << State_Current3 << endl;
			//cout << "下一个状态State_Next3 = " << State_Next3 << endl;
			//cout << "获得奖励REWARD3 = " << REWARD3 << endl;

			Q_TABLE[State_Current3 - 1][Action_Current3 - 1] = Q_TABLE[State_Current3 - 1][Action_Current3 - 1] + Learning_Rate * (REWARD3 + Discount_Factor * Q_TABLE[State_Next3 - 1][Action_Current3 - 1] - Q_TABLE[State_Current3 - 1][Action_Current3 - 1]);
			State_Current3 = State_Next3;//更新下一次进化时的状态
		}
		else if (ls_no == 4)
		{
			vector <CIndividual> v_new_TotalChromo_temp4(v_new_TotalChromo);
			C_metric4(v_ls_TotalChromo4, v_new_TotalChromo_temp4, C_value_v4);//新种群支配原种群的比例
			C_metric4(v_new_TotalChromo_temp4, v_ls_TotalChromo4, C_value_t4);//原种群支配新种群的比例
			difference_C4 = C_value_v4 - C_value_t4;
			//cout << "difference_C4 = " << difference_C4 << endl;
			DV_metric4(v_ls_TotalChromo4, DV_value_v4);
			DV_metric4(v_new_TotalChromo_temp4, DV_value_t4);
			difference_DV4 = DV_value_v4 - DV_value_t4;
			//cout << "difference_DV4 = " << difference_DV4 << endl;

			Action_Current4 = ls_no;
			//cout << "当前动作Action_Current4 = " << Action_Current4 << endl;
			double REWARD4 = 0;//奖励值
			if (difference_C4 > 0.0 && difference_DV4 > 0.0)
			{
				State_Next4 = 1;
				REWARD4 = 10;
			}
			else if (difference_C4 > 0.0 && difference_DV4 <= 0)
			{
				State_Next4 = 2;
				REWARD4 = 5;
			}
			else if (difference_C4 <= 0.0 && difference_DV4 > 0)
			{
				State_Next4 = 3;
				REWARD4 = 5;
			}
			else
			{
				State_Next4 = 4;
				REWARD4 = 0;
			}
			//cout << "当前状态State_Current4 = " << State_Current4 << endl;
			//cout << "下一个状态State_Next4 = " << State_Next4 << endl;
			//cout << "获得奖励REWARD4 = " << REWARD4 << endl;

			Q_TABLE[State_Current4 - 1][Action_Current4 - 1] = Q_TABLE[State_Current4 - 1][Action_Current4 - 1] + Learning_Rate * (REWARD4 + Discount_Factor * Q_TABLE[State_Next4 - 1][Action_Current4 - 1] - Q_TABLE[State_Current4 - 1][Action_Current4 - 1]);
			State_Current4 = State_Next4;//更新下一次进化时的状态
		}
		else if (ls_no == 5)
		{
			vector <CIndividual> v_new_TotalChromo_temp5(v_new_TotalChromo);
			C_metric5(v_ls_TotalChromo5, v_new_TotalChromo_temp5, C_value_v5);//新种群支配原种群的比例
			C_metric5(v_new_TotalChromo_temp5, v_ls_TotalChromo5, C_value_t5);//原种群支配新种群的比例
			difference_C5 = C_value_v5 - C_value_t5;
			//cout << "difference_C5 = " << difference_C5 << endl;
			DV_metric5(v_ls_TotalChromo5, DV_value_v5);
			DV_metric5(v_new_TotalChromo_temp5, DV_value_t5);
			difference_DV5 = DV_value_v5 - DV_value_t5;
			//cout << "difference_DV5 = " << difference_DV5 << endl;

			Action_Current5 = ls_no;
			//cout << "当前动作Action_Current5 = " << Action_Current5 << endl;
			double REWARD5 = 0;//奖励值
			if (difference_C5 > 0.0 && difference_DV5 > 0.0)
			{
				State_Next5 = 1;
				REWARD5 = 10;
			}
			else if (difference_C5 > 0.0 && difference_DV5 <= 0)
			{
				State_Next5 = 2;
				REWARD5 = 5;
			}
			else if (difference_C5 <= 0.0 && difference_DV5 > 0)
			{
				State_Next5 = 3;
				REWARD5 = 5;
			}
			else
			{
				State_Next5 = 4;
				REWARD5 = 0;
			}
			//cout << "当前状态State_Current5 = " << State_Current5 << endl;
			//cout << "下一个状态State_Next5 = " << State_Next5 << endl;
			//cout << "获得奖励REWARD5 = " << REWARD5 << endl;

			Q_TABLE[State_Current5 - 1][Action_Current5 - 1] = Q_TABLE[State_Current5 - 1][Action_Current5 - 1] + Learning_Rate * (REWARD5 + Discount_Factor * Q_TABLE[State_Next5 - 1][Action_Current5 - 1] - Q_TABLE[State_Current5 - 1][Action_Current5 - 1]);
			State_Current5 = State_Next5;//更新下一次进化时的状态
		}
		else if (ls_no == 6)
		{
			vector <CIndividual> v_new_TotalChromo_temp6(v_new_TotalChromo);
			C_metric6(v_ls_TotalChromo6, v_new_TotalChromo_temp6, C_value_v6);//新种群支配原种群的比例
			C_metric6(v_new_TotalChromo_temp6, v_ls_TotalChromo6, C_value_t6);//原种群支配新种群的比例
			difference_C6 = C_value_v6 - C_value_t6;
			//cout << "difference_C6 = " << difference_C6 << endl;
			DV_metric6(v_ls_TotalChromo6, DV_value_v6);
			DV_metric6(v_new_TotalChromo_temp6, DV_value_t6);
			difference_DV6 = DV_value_v6 - DV_value_t6;
			//cout << "difference_DV6 = " << difference_DV6 << endl;

			Action_Current6 = ls_no;
			//cout << "当前动作Action_Current6 = " << Action_Current6 << endl;
			double REWARD6 = 0;//奖励值
			if (difference_C6 > 0.0 && difference_DV6 > 0.0)
			{
				State_Next6 = 1;
				REWARD6 = 10;
			}
			else if (difference_C6 > 0.0 && difference_DV6 <= 0)
			{
				State_Next6 = 2;
				REWARD6 = 5;
			}
			else if (difference_C6 <= 0.0 && difference_DV6 > 0)
			{
				State_Next6 = 3;
				REWARD6 = 5;
			}
			else
			{
				State_Next6 = 4;
				REWARD6 = 0;
			}
			//cout << "当前状态State_Current6 = " << State_Current6 << endl;
			//cout << "下一个状态State_Next6 = " << State_Next6 << endl;
			//cout << "获得奖励REWARD6 = " << REWARD6 << endl;

			Q_TABLE[State_Current6 - 1][Action_Current6 - 1] = Q_TABLE[State_Current6 - 1][Action_Current6 - 1] + Learning_Rate * (REWARD6 + Discount_Factor * Q_TABLE[State_Next6 - 1][Action_Current6 - 1] - Q_TABLE[State_Current6 - 1][Action_Current6 - 1]);
			State_Current6 = State_Next6;//更新下一次进化时的状态
		}
		else if (ls_no == 7)
		{
			vector <CIndividual> v_new_TotalChromo_temp7(v_new_TotalChromo);
			C_metric7(v_ls_TotalChromo7, v_new_TotalChromo_temp7, C_value_v7);//新种群支配原种群的比例
			C_metric7(v_new_TotalChromo_temp7, v_ls_TotalChromo7, C_value_t7);//原种群支配新种群的比例
			difference_C7 = C_value_v7 - C_value_t7;
			//cout << "difference_C7 = " << difference_C7 << endl;
			DV_metric6(v_ls_TotalChromo7, DV_value_v7);
			DV_metric6(v_new_TotalChromo_temp7, DV_value_t7);
			difference_DV7 = DV_value_v7 - DV_value_t7;
			//cout << "difference_DV7 = " << difference_DV7 << endl;

			Action_Current7 = ls_no;
			//cout << "当前动作Action_Current7 = " << Action_Current7 << endl;
			double REWARD7 = 0;//奖励值
			if (difference_C7 > 0.0 && difference_DV7 > 0.0)
			{
				State_Next7 = 1;
				REWARD7 = 10;
			}
			else if (difference_C7 > 0.0 && difference_DV7 <= 0)
			{
				State_Next7 = 2;
				REWARD7 = 5;
			}
			else if (difference_C7 <= 0.0 && difference_DV7 > 0)
			{
				State_Next7 = 3;
				REWARD7 = 5;
			}
			else
			{
				State_Next7 = 4;
				REWARD7 = 0;
			}
			//cout << "当前状态State_Current7 = " << State_Current7 << endl;
			//cout << "下一个状态State_Next7 = " << State_Next7 << endl;
			//cout << "获得奖励REWARD7 = " << REWARD7 << endl;

			Q_TABLE[State_Current7 - 1][Action_Current7 - 1] = Q_TABLE[State_Current7 - 1][Action_Current7 - 1] + Learning_Rate * (REWARD7 + Discount_Factor * Q_TABLE[State_Next7 - 1][Action_Current7 - 1] - Q_TABLE[State_Current7 - 1][Action_Current7 - 1]);
			State_Current7 = State_Next7;//更新下一次进化时的状态
		}
	}
	//cout << "QTABLE:" << endl;
	//for (int q = 0; q < State_Number; q++)
	//{
	//	for (int qq = 0; qq < Action_Number; qq++)
	//	{
	//		cout << std::fixed << std::setprecision(4) << Q_TABLE[q][qq] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//system("pause");

	////step4: 基于收敛性和多样性指标选择最终的ls种群
	vector<double> v_CDV_value;
	v_CDV_value.push_back(difference_C1 + difference_DV1);
	v_CDV_value.push_back(difference_C2 + difference_DV2);
	v_CDV_value.push_back(difference_C3 + difference_DV3);
	v_CDV_value.push_back(difference_C4 + difference_DV4);
	v_CDV_value.push_back(difference_C5 + difference_DV5);
	v_CDV_value.push_back(difference_C6 + difference_DV6);
	v_CDV_value.push_back(difference_C7 + difference_DV7);
	//for (int cdv = 0; cdv < v_CDV_value.size(); cdv++)
	//{
	//	cout << std::fixed << std::setprecision(4) << v_CDV_value[cdv] << " ";
	//}
	//cout << endl;
	auto max_iter = max_element(v_CDV_value.begin(), v_CDV_value.end());
	int max_index = distance(v_CDV_value.begin(), max_iter);
	//cout << "max_index = " << max_index << endl;
	if (max_index + 1 == 1)
	{
		vector<vector<CIndividual>>().swap(v_ls_Chromo);
		vector<CIndividual>().swap(v_ls_TotalChromo);
		for (int lsize = 0; lsize < v_ls_Chromo1.size(); lsize++)
		{
			vector <CIndividual> v_ls_subChromo;
			vector <CIndividual>().swap(v_ls_subChromo);
			for (int lssize = 0; lssize < v_ls_Chromo1[lsize].size(); lssize++)
			{
				v_ls_subChromo.push_back(v_ls_Chromo1[lsize][lssize]);
				v_ls_TotalChromo.push_back(v_ls_Chromo1[lsize][lssize]);
			}
			v_ls_Chromo.push_back(v_ls_subChromo);
		}
	}
	else if (max_index + 1 == 2)
	{
		vector<vector<CIndividual>>().swap(v_ls_Chromo);
		vector<CIndividual>().swap(v_ls_TotalChromo);
		for (int lsize = 0; lsize < v_ls_Chromo2.size(); lsize++)
		{
			vector <CIndividual> v_ls_subChromo;
			vector <CIndividual>().swap(v_ls_subChromo);
			for (int lssize = 0; lssize < v_ls_Chromo2[lsize].size(); lssize++)
			{
				v_ls_subChromo.push_back(v_ls_Chromo2[lsize][lssize]);
				v_ls_TotalChromo.push_back(v_ls_Chromo2[lsize][lssize]);
			}
			v_ls_Chromo.push_back(v_ls_subChromo);
		}
	}
	else if (max_index + 1 == 3)
	{
		vector<vector<CIndividual>>().swap(v_ls_Chromo);
		vector<CIndividual>().swap(v_ls_TotalChromo);
		for (int lsize = 0; lsize < v_ls_Chromo3.size(); lsize++)
		{
			vector <CIndividual> v_ls_subChromo;
			vector <CIndividual>().swap(v_ls_subChromo);
			for (int lssize = 0; lssize < v_ls_Chromo3[lsize].size(); lssize++)
			{
				v_ls_subChromo.push_back(v_ls_Chromo3[lsize][lssize]);
				v_ls_TotalChromo.push_back(v_ls_Chromo3[lsize][lssize]);
			}
			v_ls_Chromo.push_back(v_ls_subChromo);
		}
	}
	else if (max_index + 1 == 4)
	{
		vector<vector<CIndividual>>().swap(v_ls_Chromo);
		vector<CIndividual>().swap(v_ls_TotalChromo);
		for (int lsize = 0; lsize < v_ls_Chromo4.size(); lsize++)
		{
			vector <CIndividual> v_ls_subChromo;
			vector <CIndividual>().swap(v_ls_subChromo);
			for (int lssize = 0; lssize < v_ls_Chromo4[lsize].size(); lssize++)
			{
				v_ls_subChromo.push_back(v_ls_Chromo4[lsize][lssize]);
				v_ls_TotalChromo.push_back(v_ls_Chromo4[lsize][lssize]);
			}
			v_ls_Chromo.push_back(v_ls_subChromo);
		}
	}
	else if (max_index + 1 == 5)
	{
		vector<vector<CIndividual>>().swap(v_ls_Chromo);
		vector<CIndividual>().swap(v_ls_TotalChromo);
		for (int lsize = 0; lsize < v_ls_Chromo5.size(); lsize++)
		{
			vector <CIndividual> v_ls_subChromo;
			vector <CIndividual>().swap(v_ls_subChromo);
			for (int lssize = 0; lssize < v_ls_Chromo5[lsize].size(); lssize++)
			{
				v_ls_subChromo.push_back(v_ls_Chromo5[lsize][lssize]);
				v_ls_TotalChromo.push_back(v_ls_Chromo5[lsize][lssize]);
			}
			v_ls_Chromo.push_back(v_ls_subChromo);
		}
	}
	else if (max_index + 1 == 6)
	{
		vector<vector<CIndividual>>().swap(v_ls_Chromo);
		vector<CIndividual>().swap(v_ls_TotalChromo);
		for (int lsize = 0; lsize < v_ls_Chromo6.size(); lsize++)
		{
			vector <CIndividual> v_ls_subChromo;
			vector <CIndividual>().swap(v_ls_subChromo);
			for (int lssize = 0; lssize < v_ls_Chromo6[lsize].size(); lssize++)
			{
				v_ls_subChromo.push_back(v_ls_Chromo6[lsize][lssize]);
				v_ls_TotalChromo.push_back(v_ls_Chromo6[lsize][lssize]);
			}
			v_ls_Chromo.push_back(v_ls_subChromo);
		}
	}
	else if (max_index + 1 == 7)
	{
		vector<vector<CIndividual>>().swap(v_ls_Chromo);
		vector<CIndividual>().swap(v_ls_TotalChromo);
		for (int lsize = 0; lsize < v_ls_Chromo7.size(); lsize++)
		{
			vector <CIndividual> v_ls_subChromo;
			vector <CIndividual>().swap(v_ls_subChromo);
			for (int lssize = 0; lssize < v_ls_Chromo7[lsize].size(); lssize++)
			{
				v_ls_subChromo.push_back(v_ls_Chromo7[lsize][lssize]);
				v_ls_TotalChromo.push_back(v_ls_Chromo7[lsize][lssize]);
			}
			v_ls_Chromo.push_back(v_ls_subChromo);
		}
	}
	
	////step5: 更新ls种群的序值
	rank_up(v_ls_TotalChromo);//获取种群中个体的上层序值和拥挤度距离
	rank_low(v_ls_Chromo);//获取种群中每个子种群中个体的下层序值和拥挤度距离
	update_subpop(v_ls_TotalChromo, v_ls_Chromo);//获得新种群v_new_TotalChromo/v_new_Chromo
	//system("pause");
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}