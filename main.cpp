#include <iostream>
#include <vector>
#include "Qpacking.h"
#include "Item.h"
#include <time.h>
#include <map>
#include <string>
#include <tuple>


using namespace std;

char findex0[50];//����һ���ַ���findex0
char findex1[50];//����һ���ַ���findex1
char findex2[50];//����һ���ַ���findex2
char filename[100]; //�����ļ��ַ���
const char* extendname = ".txt";  //�ļ���չ��Ϊ.txt


void main()
{

    srand((unsigned)time(NULL)); //��ӵ�ǰʱ��Ϊ���������
    int SOLVE_TIMES = 10;      //����20��
    vector <int> v_number_of_instances; 
    v_number_of_instances.push_back(1);//C1 16 17 16
    v_number_of_instances.push_back(2);//C2 25 25 25
    v_number_of_instances.push_back(3);//C3 28 29 28
    v_number_of_instances.push_back(4);//C4 49 49 49
    v_number_of_instances.push_back(5);//C5 73 73 73
    v_number_of_instances.push_back(6);//C6 97 97 97
    v_number_of_instances.push_back(7);//C7 196 197 196
    int number_of_examples = 3;   //ÿ�ֹ�ģ����������3����ͬ�����Ӽ�����
    for (int instance_index = 3; instance_index <= v_number_of_instances.size();instance_index++)
    {
        int ins_index = v_number_of_instances[instance_index - 1];
        for (int example_index = 1; example_index <= number_of_examples; example_index++)
        {
            for (int solve_times = 1; solve_times <= SOLVE_TIMES; solve_times++)  //ִ��20��
            {
                clock_t start, finish;
                start = clock();//��ʼ��ʱ

                _itoa_s(ins_index, findex0, 10);//����_itoa_s����������number_of_productsת��Ϊ10���Ƶ��ַ���������ת����������findex0��
                _itoa_s(example_index, findex1, 10);//����_itoa_s����������example_indexת��Ϊ10���Ƶ��ַ���������ת����������findex1��
                strcpy_s(filename, ".\\data");  //strcpy_s�������ַ���.\\data���Ƶ�filename�ַ�����
                strcat_s(filename, "\\");   //strcat_s���������µ�filename�ַ�����\\�ַ���
                strcat_s(filename, "C");   //strcat_s���������µ�filename�ַ�����\\�ַ���
                strcat_s(filename, findex0); //strcat_s���������µ�filename�ַ�����findex0�ַ�������number_of_productsת����2��4��6��8��10��12��14��16��18��20�����findex0�ַ����У�
                strcat_s(filename, "P");  //strcat_s���������µ�filename�ַ�����\\�ַ���
                strcat_s(filename, findex1); //strcat_s���������µ�filename�ַ�����findex1�ַ�������instance_indexת����1��2��3�����findex1�ַ����У�
                strcat_s(filename, extendname);//strcat_s���������µ�filename�ַ�����extendname�ļ���չ��.txt
                cout << filename << endl;    //��������ļ���
                //system("pause");

                QPacking Instance;
                Instance.finData(filename);
                //system("pause");

                Instance.runcode();
                //system("pause");

                finish = clock();//������ʱ
                double time1 = (double)(finish - start) / CLOCKS_PER_SEC;

                _itoa_s(ins_index, findex0, 10);  //����_itoa_s����������nins_indexת��Ϊ10���Ƶ��ַ���������ת����������findex0��
                _itoa_s(example_index, findex1, 10);  //����_itoa_s����������example_indexת��Ϊ10���Ƶ��ַ���������ת����������findex1��
                _itoa_s(solve_times, findex2, 10);//����_itoa_s����������solve_timesת��Ϊ10���Ƶ��ַ���������ת����������findex1��
                strcpy_s(filename, ".\\result-QPOFF\\");  //strcpy_s�������ַ���.\\result_GA\\���Ƶ�filename�ַ�����
                strcat_s(filename, "\\result-");//�ַ������Ӻ��������������ַ���
                strcat_s(filename, "C-");   //strcat_s���������µ�filename�ַ�����\\�ַ���
                strcat_s(filename, findex0);//number_factories
                strcat_s(filename, "-P-");   //strcat_s���������µ�filename�ַ�����\\�ַ���
                strcat_s(filename, findex1);//number_machines
                strcat_s(filename, "\\");
                strcat_s(filename, "\\result-");//���Ӻ������ҽ������ǰ���ַ���
                strcat_s(filename, "C-");   //strcat_s���������µ�filename�ַ�����\\�ַ���
                strcat_s(filename, findex0);  //strcat_s���������µ�filename�ַ�����findex0�ַ�������number_of_productsת����2��4��6��8��10��12��14��16��18��20�����findex0�ַ����У�
                strcat_s(filename, "-P-");  //strcat_s���������µ�filename�ַ�����\\�ַ���
                strcat_s(filename, findex1);  //strcat_s���������µ�filename�ַ����ͺ�findex1�ַ�������instance_indexת����1��2��3�����findex1�ַ����У�
                strcat_s(filename, "-");  //strcat_s���������µ�filename�ַ�����\\�ַ���
                strcat_s(filename, findex2);  //strcat_s���������µ�filename�ַ����ͺ�findex1�ַ�������solve_timesת����1��2��3��4��5��6��7��8��9��10�����findex1�ַ����У�
                strcat_s(filename, extendname);//strcat_s���������µ�filename�ַ�����extendname�ļ���չ��.txt         
                //�����������ǣ�.\\result_QPOFF\\result-C-findex0-P-findex1\\result-C-findex0-P-findex1-findex2.txt
                cout << filename << endl;    //��������ļ���
                //system("pause");

                Instance.foutData(filename, time1);
                //system("pause");
            }
            //cout << endl;
        }
        //cout << endl;
    }
}