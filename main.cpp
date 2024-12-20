#include <iostream>
#include <vector>
#include "Qpacking.h"
#include "Item.h"
#include <time.h>
#include <map>
#include <string>
#include <tuple>


using namespace std;

char findex0[50];//定义一个字符串findex0
char findex1[50];//定义一个字符串findex1
char findex2[50];//定义一个字符串findex2
char filename[100]; //定义文件字符串
const char* extendname = ".txt";  //文件扩展名为.txt


void main()
{

    srand((unsigned)time(NULL)); //添加当前时间为随机数种子
    int SOLVE_TIMES = 10;      //运行20次
    vector <int> v_number_of_instances; 
    v_number_of_instances.push_back(1);//C1 16 17 16
    v_number_of_instances.push_back(2);//C2 25 25 25
    v_number_of_instances.push_back(3);//C3 28 29 28
    v_number_of_instances.push_back(4);//C4 49 49 49
    v_number_of_instances.push_back(5);//C5 73 73 73
    v_number_of_instances.push_back(6);//C6 97 97 97
    v_number_of_instances.push_back(7);//C7 196 197 196
    int number_of_examples = 3;   //每种规模的算例都有3个不同的例子即场景
    for (int instance_index = 3; instance_index <= v_number_of_instances.size();instance_index++)
    {
        int ins_index = v_number_of_instances[instance_index - 1];
        for (int example_index = 1; example_index <= number_of_examples; example_index++)
        {
            for (int solve_times = 1; solve_times <= SOLVE_TIMES; solve_times++)  //执行20次
            {
                clock_t start, finish;
                start = clock();//开始计时

                _itoa_s(ins_index, findex0, 10);//利用_itoa_s函数将整数number_of_products转化为10进制的字符串，并将转换结果存放在findex0中
                _itoa_s(example_index, findex1, 10);//利用_itoa_s函数将整数example_index转化为10进制的字符串，并将转换结果存放在findex1中
                strcpy_s(filename, ".\\data");  //strcpy_s函数将字符串.\\data复制到filename字符串中
                strcat_s(filename, "\\");   //strcat_s函数连接新的filename字符串和\\字符串
                strcat_s(filename, "C");   //strcat_s函数连接新的filename字符串和\\字符串
                strcat_s(filename, findex0); //strcat_s函数连接新的filename字符串和findex0字符串（即number_of_products转换的2、4、6、8、10、12、14、16、18、20存放在findex0字符串中）
                strcat_s(filename, "P");  //strcat_s函数连接新的filename字符串和\\字符串
                strcat_s(filename, findex1); //strcat_s函数连接新的filename字符串和findex1字符串（即instance_index转换的1、2、3存放在findex1字符串中）
                strcat_s(filename, extendname);//strcat_s函数连接新的filename字符串和extendname文件扩展名.txt
                cout << filename << endl;    //换行输出文件名
                //system("pause");

                QPacking Instance;
                Instance.finData(filename);
                //system("pause");

                Instance.runcode();
                //system("pause");

                finish = clock();//结束计时
                double time1 = (double)(finish - start) / CLOCKS_PER_SEC;

                _itoa_s(ins_index, findex0, 10);  //利用_itoa_s函数将整数nins_index转化为10进制的字符串，并将转换结果存放在findex0中
                _itoa_s(example_index, findex1, 10);  //利用_itoa_s函数将整数example_index转化为10进制的字符串，并将转换结果存放在findex1中
                _itoa_s(solve_times, findex2, 10);//利用_itoa_s函数将整数solve_times转化为10进制的字符串，并将转换结果存放在findex1中
                strcpy_s(filename, ".\\result-QPOFF\\");  //strcpy_s函数将字符串.\\result_GA\\复制到filename字符串中
                strcat_s(filename, "\\result-");//字符串连接函数：连接两个字符串
                strcat_s(filename, "C-");   //strcat_s函数连接新的filename字符串和\\字符串
                strcat_s(filename, findex0);//number_factories
                strcat_s(filename, "-P-");   //strcat_s函数连接新的filename字符串和\\字符串
                strcat_s(filename, findex1);//number_machines
                strcat_s(filename, "\\");
                strcat_s(filename, "\\result-");//连接函数，且结果放在前面字符串
                strcat_s(filename, "C-");   //strcat_s函数连接新的filename字符串和\\字符串
                strcat_s(filename, findex0);  //strcat_s函数连接新的filename字符串和findex0字符串（即number_of_products转换的2、4、6、8、10、12、14、16、18、20存放在findex0字符串中）
                strcat_s(filename, "-P-");  //strcat_s函数连接新的filename字符串和\\字符串
                strcat_s(filename, findex1);  //strcat_s函数连接新的filename字符串和和findex1字符串（即instance_index转换的1、2、3存放在findex1字符串中）
                strcat_s(filename, "-");  //strcat_s函数连接新的filename字符串和\\字符串
                strcat_s(filename, findex2);  //strcat_s函数连接新的filename字符串和和findex1字符串（即solve_times转换的1、2、3、4、5、6、7、8、9、10存放在findex1字符串中）
                strcat_s(filename, extendname);//strcat_s函数连接新的filename字符串和extendname文件扩展名.txt         
                //以上输出结果是：.\\result_QPOFF\\result-C-findex0-P-findex1\\result-C-findex0-P-findex1-findex2.txt
                cout << filename << endl;    //换行输出文件名
                //system("pause");

                Instance.foutData(filename, time1);
                //system("pause");
            }
            //cout << endl;
        }
        //cout << endl;
    }
}