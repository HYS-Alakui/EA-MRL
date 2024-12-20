#include "Qpacking.h"
#include "Headfile.h"
#include "Item.h"
#include <iostream>
#include <algorithm>
#include <time.h>
#include <iomanip>
#include <set>
#include <vector>

using namespace std;

struct OutLine 
{
	OutLine(int origin, int end, int height)
	{
		this->origin = origin;
		this->end = end;
		this->height = height;
	}

	OutLine() {}

	int origin;
	int end;
	int height;
};

class Product
{
public:
	Product(int w, int h, int num, int handle_time)
	{
		this->w = w;
		this->h = h;
		this->num = num;
		this->handle_time = handle_time;
		this->finish_time = 0;
	}

	int w;
	int h;
	int num;
	int handle_time;
	int finish_time;
	int xzb, yzb; 
	int layout;
	int xuanz;

	void print()
	{
		cout << "Product:" << num <<",xuanz:"<<xuanz << ",width:" << w << ",height:" << h <<  ",layout_number:" << layout << ",pos:(" << xzb << "," << yzb << ")" <<",finish_time:" << finish_time << endl;
	}


	static int search_by_width(int target_width, vector<Product> data)
	{
		int n = data.size();
		for (int ii = 0; ii < n; ii++) 
		{
			if (data[ii].w <= target_width)
			{
				return ii;
			}
		}
		return -1;
	}

	static int search_by_size(int target_width, vector<Product> data)
	{
		int n = data.size();
		for (int ii = 0; ii < n; ii++) 
		{
			if (data[ii].w <= target_width || data[ii].h <= target_width) 
			{
				return ii;
			}
		}
		return -1;
	}

	static int search_by_shape(int target_width, int target_height, vector<Product> data)
	{
		int n = data.size();
		for (int ii = 0; ii < n; ii++) 
		{
			if ((data[ii].w <= target_width && data[ii].h <= target_height) || (data[ii].w <= target_height && data[ii].h <= target_width)) 
			{
				return ii;
			}
		}
		return -1;
	}

	Product rotate_new() const
	{
		return { this->h, this->w, this->num, this->handle_time };
	}
};

class RectLayout
{
public:
	RectLayout(int number,int width, int height)
	{
		//this->number = _layout_number++;
		this->number = number;
		this->width = width;
		this->height = height;
	}

	int number;
	int width;
	int height;
	vector<OutLine> line_list;
	OutLine lowest_line;
	int lowest_line_idx;
	// 最终位置结果[[矩形件编号,左下角横坐标,左下角纵坐标,矩形件宽度,矩形件高度], ...]
	vector<vector<int>> result_pos;
	double ratio;

	// 初始化水平线集合（起始x位置，终止x位置，高度）
	void init_line_list(int origin, int end, int height)
	{
		auto init_line = OutLine(origin, end, height);
		line_list.push_back(init_line);
		lowest_line = init_line;
		lowest_line_idx = 0;
		ratio = 0;
	}

	// 提升最低水平线
	void enhance_line(int index)
	{
		//cout << "提升！" << endl;
		if (line_list.size() > 1) 
		{
			int neighbor_idx = 0;
			if (index == 0) 
			{
				neighbor_idx = 1;
			}
			else if (index == line_list.size() - 1)
			{
				neighbor_idx = index - 1;
			}
			else {
				auto left_neighbor = line_list[index - 1];
				auto right_neighbor = line_list[index + 1];
				if (left_neighbor.height < right_neighbor.height) 
				{
					neighbor_idx = index - 1;
				}
				else if (left_neighbor.height == right_neighbor.height)
				{
					if (left_neighbor.origin < right_neighbor.origin)
					{
						neighbor_idx = index - 1;
					}
					else
					{
						neighbor_idx = index + 1;
					}
				}
				else 
				{
					neighbor_idx = index + 1;
				}
			}

			auto old = line_list[neighbor_idx];
			if (neighbor_idx < index)
				line_list[neighbor_idx] = OutLine(old.origin, old.end + line_width(index), old.height);
			else
				line_list[neighbor_idx] = OutLine(old.origin - line_width(index), old.end, old.height);

			line_list.erase(line_list.begin() + index);
		}
	}

	// 按位置更新水平线
	void update_line_list(int index, OutLine new_line)
	{
		line_list[index] = new_line;
	}

	// 按位置插入水平线
	void insert_line_list(int index, OutLine new_line)
	{
		if (index >= line_list.size())
			line_list.push_back(new_line);
		else if (index < 0)
			line_list.insert(line_list.begin(), new_line);
		else
			line_list.insert(line_list.begin() + index, new_line);
	}

	// 计算水平线宽度
	int line_width(int index)
	{
		return line_list[index].end - line_list[index].origin;
	}

	// 找出最低水平线
	void find_lowest_line()
	{
		//cout << "line_list.size() = " << line_list.size() << endl;
		auto lowest = line_list[0].height;
		for (int i = 1; i < line_list.size(); i++)
			if (line_list[i].height < lowest)
				lowest = line_list[i].height;
		//cout << "lowest =" << lowest << endl;
		auto min_origin = INT_MAX;
		for (int i = 0; i < line_list.size(); i++)
		{
			if (line_list[i].height == lowest && line_list[i].origin < min_origin) 
			{
				min_origin = line_list[i].origin;
				lowest_line_idx = i;
				lowest_line = line_list[i];
			}
		}
		//cout << "lowest_line_idx = " << lowest_line_idx << endl;
	}

	// 清空水平线集合
	void clear_line_list()
	{
		line_list.clear();
	}

	// 计算最高水平线高度
	int cal_high_line()
	{
		auto highest = line_list[0].height;
		for (int i = 1; i < line_list.size(); i++)
			if (line_list[i].height > highest)
				highest = line_list[i].height;
		return highest;
	}

	// 将矩形物品排样
	void packing(Product _pro)
	{
		// 找出最低水平线宽度
		auto lowest_line_width = line_width(lowest_line_idx);
		// 对矩形件排样
		result_pos.push_back({ _pro.num, lowest_line.origin, lowest_line.height, _pro.w, _pro.h });
		// 更新水平线集
		auto new_line1 = OutLine(lowest_line.origin, lowest_line.origin + _pro.w, lowest_line.height + _pro.h);
		auto new_line2 = OutLine(lowest_line.origin + _pro.w, lowest_line.origin + lowest_line_width, lowest_line.height);
		update_line_list(lowest_line_idx, new_line1);
		if (lowest_line_width - _pro.w > 0)
			insert_line_list(lowest_line_idx + 1, new_line2);
	}

	// 计算板材利用率
	pair<int, double> cal_used_ratio()
	{
		auto used_area = 0;
		for (auto& _p : result_pos)
			used_area += _p[3] * _p[4];
		auto max_high = cal_high_line();
		if (max_high > 0)
		{
			ratio = (double)(used_area * 1) / (width * max_high);
			ratio = (int)(ratio * 1000) / 1000.0;	//保留三位小数
		}
		return { used_area, ratio };
	}
};

void QPacking::evaluate_Packing(int& board_width, int& board_height, vector<vector<int>>& v_item_sizes, vector<double>& v_handle_time, vector<int>& ran, double& use_rate, double& consistent_value, vector<Item>& v_product, vector<vector<int>>& v_order_product, vector<pair<int, int>>& v_real_path)
{
	//cout << "Before_v_product信息(用于更新)：" << endl;
	//for (int ii = 0; ii < v_product.size(); ii++)
	//{
	//	cout << v_product[ii].order << " ";
	//    cout << v_product[ii].number << " ";
	//    cout << v_product[ii].width << " ";
	//    cout << v_product[ii].height << " ";
	//    cout << v_product[ii].handle_time << " ";   
	//    cout << v_product[ii].he_value << endl;
	//}
	//system("pause");


	////ran,v_item_sizes,v_handle_time这三个容器与路径一一对应
	//for (int ii = 0; ii < ran.size(); ii++)
	//{
	//	cout << ran[ii] << ' ';
	//}
	//cout << endl;
	//for (int ii = 0; ii < v_item_sizes.size(); ii++)
	//{
	//	cout << '[' << v_item_sizes[ii][0] << "," << v_item_sizes[ii][1] << ']' << ' ';
	//}
	//cout << endl;
	//for (int ii = 0; ii < v_handle_time.size(); ii++)
	//{
	//	cout << v_handle_time[ii] << " ";
	//}
	//cout << endl;

	vector<Product> products;//用于保存传进来的path中的矩形件的信息
	for (int ii = 0; ii < v_item_sizes.size(); ii++)
	{
		products.emplace_back(v_item_sizes[ii][0], v_item_sizes[ii][1], ran[ii], v_handle_time[ii]);//Product类的构造函数
	}
	//for (int ii = 0; ii < v_item_sizes.size(); ii++)
	//{
	//	cout << products[ii].w << " " << products[ii].h << " " << products[ii].num <<" "<<products[ii].handle_time<< endl;
	//}
	//system("pause");
	vector<Product> packing_products; //记录排样信息	
	int board_num = 0;
	int end_time = 0;
	double sum_ratio = 0;

PUT:
	board_num++;
	auto layout = RectLayout(board_num,board_width, board_height);
	layout.init_line_list(0, board_width, 0);
	tuple<int, int, int> pre_lowest_line{ -1, -1, -1 };
	while (!products.empty())
	{	
		layout.find_lowest_line();//找出最低水平线
		auto available_width = layout.line_width(layout.lowest_line_idx);
		//cout << "available_width =" << available_width << endl;
		auto available_height = layout.height - layout.lowest_line.height;
		//cout << "available_height =" << available_height << endl;
		auto candidate_idx = Product::search_by_shape(available_width, available_height, products);
		//cout << "candidate_idx = " << candidate_idx << endl;
		if (candidate_idx != -1) 
		{
			auto pro = products[candidate_idx];
			//cout << "pro.num = " << pro.num << endl;
			//cout << "pro.w = " << pro.w << endl;
			//cout << "pro.h = " << pro.h << endl;
			//cout << "pro.handle_time = " << pro.handle_time << endl;	
			pro.xuanz = 0;//默认为0
			if (pro.w > available_width && pro.h <= available_width)
			{
				//cout << "旋转1" << endl;
				pro = pro.rotate_new();
				pro.xuanz = 1;
			}			
			if (pro.h > available_height && pro.w <= available_height)
			{
				//cout << "旋转2" << endl;
				pro = pro.rotate_new();
				pro.xuanz = 1;
			}
			//cout << "pro.xuanz = " << pro.xuanz << endl;
			layout.packing(pro);
			end_time += pro.handle_time;//矩形件的完工时间
			pro.finish_time = end_time;
			//cout << "pro.finish_time = " << pro.finish_time << endl;
			pro.layout = layout.number;
			//cout << "pro.layout = " << pro.layout << endl;
			pro.xzb = layout.result_pos.back()[1];
			//cout << "pro.xzb = " << pro.xzb << endl;
			pro.yzb = layout.result_pos.back()[2];
			//cout << "pro.yzb = " << pro.yzb << endl;
			packing_products.push_back(pro);//保存排样信息
			products.erase(products.begin() + candidate_idx);
			//system("pause");
		}
		else
		{
			layout.enhance_line(layout.lowest_line_idx);
			layout.find_lowest_line();
			if (pre_lowest_line == tuple<int, int, int>{layout.lowest_line.origin, layout.lowest_line.end, layout.lowest_line.height})
				break;
			pre_lowest_line = { layout.lowest_line.origin, layout.lowest_line.end, layout.lowest_line.height };
		}
	}
;
	
	//// 计算板材利用率
	auto [_area, _ratio] = layout.cal_used_ratio();
	//cout << "used area:" << _area << ",ratio:" << _ratio << endl;	
	sum_ratio = sum_ratio + _ratio;
	//cout << "sum_ratio = " << sum_ratio << endl;

	if (!products.empty())
	{
		goto PUT;
	}
		
	//cout << "排样信息" << endl;
	for (int m = 0; m < packing_products.size(); m++)
	{
		////调用print函数输出整体排样信息
		//packing_products[m].print();

		////此时，每个矩形件的信息都已获取，更新传进来的v_product信息
		int item_number = packing_products[m].num;
		//cout << "item_number = " << item_number << endl;
		int item_xuanz = packing_products[m].xuanz;
		v_product[item_number - 1].xuanz = item_xuanz;
		//cout << "item_xuanz = " << item_xuanz << endl;
		int item_layout = packing_products[m].layout;
		v_product[item_number - 1].layout = item_layout;
		//cout << "item_layout = " << item_layout << endl;
		int item_orign_x = packing_products[m].xzb;
		v_product[item_number - 1].origin_x = item_orign_x;
		//cout << "item_orign_x = " << item_orign_x << endl;
		int item_down_y = packing_products[m].yzb;
		v_product[item_number - 1].down_y = item_down_y;
		//cout << "item_down_y = " << item_down_y << endl;
		int item_finish_time = packing_products[m].finish_time;
		v_product[item_number - 1].finish_time = item_finish_time;
		//cout << "item_finish_time = " << item_finish_time << endl;
	}
	//system("pause");

	/////////////////////////求目标值：一致性目标和板材利用率目标////////////////////////////////////////////////
	//cout << "每个订单包含的作业：" << endl;
	//for (int m = 0; m < v_order_product.size(); m++)
	//{
	//	for (int n = 0; n < v_order_product[m].size(); n++)
	//	{
	//		cout << v_order_product[m][n] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//system("pause");

	for (int m = 0; m < packing_products.size(); m++)
	{
		v_real_path.push_back(make_pair(packing_products[m].num,packing_products[m].finish_time));
	}
	//cout << "实际矩形件（JOB）排样顺序及排样完工时间：" << endl;
	//for (int m = 0; m < v_real_path.size(); m++)
	//{
	//	auto pa = v_real_path[m];
	//	cout << "("<< pa.first << ",  " << pa.second <<")" ;
	//}
	//cout << endl;

	vector<vector<int>> v_order_product_location;//找到每个订单包含的作业在实际排样顺序中的调度顺序索引
	for (int ii = 0; ii < v_order_product.size(); ii++)
	{
		vector<int> v;
		for (int jj = 0; jj < v_order_product[ii].size(); jj++)
		{
			for (int m = 0; m < v_real_path.size(); m++)
			{
				int location_index;
				if (v_order_product[ii][jj] == v_real_path[m].first)
				{
					location_index = m;
					v.push_back(location_index);
					break;
				}
			}
		}
		v_order_product_location.push_back(v);
	}
	//cout << "每个订单包含的作业在实际排样顺序中的调度顺序索引：" << endl;
	//for (int m = 0; m < v_order_product_location.size(); m++)
	//{
	//	for (int n = 0; n < v_order_product_location[m].size(); n++)
	//	{
	//		cout << v_order_product_location[m][n] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	vector<int>v_order_distance;//储存每个订单的距离
	for (int ii = 0; ii < v_order_product_location.size(); ii++)
	{
		auto maxPosition = max_element(v_order_product_location[ii].begin(), v_order_product_location[ii].end());
		auto minPosition = min_element(v_order_product_location[ii].begin(), v_order_product_location[ii].end());
		int order_distance = *maxPosition - *minPosition;
		v_order_distance.push_back(order_distance);
	}
	//cout << "每个订单的距离：" << endl;
	//for (int m = 0; m < v_order_distance.size(); m++)
	//{
	//	cout << v_order_distance[m] << " ";
	//}
	//cout << endl;

	vector<vector<int>> v_order_product_board;//获取每个订单所含矩形件的板件分配信息
	for (int ii = 0; ii < v_order_product.size(); ii++)
	{
		vector<int> v;
		for (int jj = 0; jj < v_order_product[ii].size(); jj++)
		{
			int pro_index = v_order_product[ii][jj] - 1;
			int pro_board_num = v_product[pro_index].layout;
			v.push_back(pro_board_num);
		}
		v_order_product_board.push_back(v);
	}
	//cout << "每个订单所含矩形件的板件分配信息：" << endl;
	//for (int m = 0; m < v_order_product_board.size(); m++)
	//{
	//	for (int n = 0; n < v_order_product_board[m].size(); n++)
	//	{
	//		cout << v_order_product_board[m][n] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	for (int ii = 0; ii < v_order_product_board.size(); ii++)//每个订单包含的作业所在板件(不重复版)
	{
		sort(v_order_product_board[ii].begin(), v_order_product_board[ii].end());
		v_order_product_board[ii].erase(unique(v_order_product_board[ii].begin(), v_order_product_board[ii].end()), v_order_product_board[ii].end());
	}

	vector<int> v_order_board_number;//记录每个订单所需的板子数量
	for (int ii = 0; ii < v_order_product_board.size(); ii++)
	{
		int b_num = v_order_product_board[ii].size();
		v_order_board_number.push_back(b_num);
	}
	//cout << "每个订单所需的板子数量：" << endl;
	//for (int m = 0; m < v_order_board_number.size(); m++)
	//{
	//	cout << v_order_board_number[m] << " ";
	//}
	//cout << endl;

	////计算一致性目标值 = 每个订单所需的板子数量×订单内矩形件之间的最大调度间隔距离
	for (int ii = 0; ii < v_order_board_number.size(); ii++)
	{
		consistent_value += v_order_board_number[ii] * v_order_distance[ii];
	}
	//cout << "consistent_value = " << consistent_value << endl;
	
	//cout << "board num:" << board_num << endl;
	use_rate = sum_ratio / board_num;
	//cout << "use_rate = " << use_rate << endl;
	
	//cout << "After_v_product信息：" << endl;
	//for (int ii = 0; ii < v_product.size(); ii++)
	//{
	//	cout << "item_order = " << v_product[ii].order << " ";
	//	cout << "item_number = " << v_product[ii].number << " ";
	//	cout << "item_xuanz = " << v_product[ii].xuanz << " ";
	//	cout << "item_width = " << v_product[ii].width << " ";
	//	cout << "item_height = " << v_product[ii].height << " ";
	//	cout << "item_handle_time = " << v_product[ii].handle_time << " ";
	//	cout << "item_finish_time = " << v_product[ii].finish_time << " ";
	//	cout << "item_layout = " << v_product[ii].layout << " ";
	//	cout << "item_origin_x = " << v_product[ii].origin_x << " ";
	//	cout << "item_down_y = " << v_product[ii].down_y << " ";
	//	cout << "item_he_value = " << v_product[ii].he_value << endl;
	//}
	//system("pause");
}
