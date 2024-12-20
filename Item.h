#pragma once
class Item
{
public:
    int number;//编号
    int width;//宽
    int height;//高
    int handle_time; //切割时间
    int order; //所属订单
    double he_value;//启发知识

    int xuanz;//是否旋转
    int layout;//所属板材
    int origin_x;//左下角横坐标
    int down_y; //左下角纵坐标
    int finish_time; //结束时间  
};