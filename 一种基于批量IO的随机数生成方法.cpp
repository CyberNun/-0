/*
注意，本算法采用了过时的方法“strcpy”在新版的visual studio中会无法正常编译，错误代码为c4996.
微软对该错误的描述如下:
	你的代码使用标记为“已弃用”的函数、类成员、变量或 typedef。 符号是使用 __declspec(deprecated) 修饰符或 C++14 [[deprecated]] 属性弃用的。 实际的 C4996 警告消息由声明的 deprecated 修饰符或属性指定。
	Visual Studio 库中的许多函数、成员函数、函数模板和全局变量已弃用。 某些函数/变量（例如 POSIX 和 Microsoft 特定的函数）被弃用的原因是它们现在使用不同的偏好名称。 某些 C 运行时库函数被弃用的原因是它们不安全，而现在具有更安全的变体。 其他函数/变量被弃用的原因是它们已过时。 弃用消息通常包括已弃用函数或全局变量的建议替换项。

解决方法为，项目->属性->c/c++->常规->SDL检查设置为“否(/SDL-)”

*/


#include "iostream"
#include "cstdlib"
#include "cstdio"
#include "ctime"
#include "cmath"
#include "string"
#include "cstring"
using namespace std;

long long get_list(long long , long long);//输出数字表格

int main()
{
	long long n = 0, x = 0, sum = 0;//初始化变量，n代表生成n个随机数，x代表随机数的取值范围（1-x），sum代表所有随机数求和
	bool mark = 0, mark2 = 1;//两个标识位置，用于记录输入数据状态
	char s[100];//输入内容字符串
	while (1)
	{
		printf("-------------------------------------------\n");
		mark = 0;
		mark2 = 1;
		sum = 0;
		n = 0;
		x = 0;//初始化变量，避免后续出现错误
		cin.sync();
		cin.clear();
		cin.getline(s, 99);
		if (strcmp(s, "exit") == 0)
		{
			break;
		}
		int k = strlen(s);
		for (int i = 0; i<k; i++)
		{
			if ((s[i] >= 'a' && s[i] <= 'z' && s[i] != 'd') || (s[i] >= 'A' && s[i] <= 'Z' && s[i] != 'D'))
			{
				mark2 = 0;
			}
			else if (s[i] == 'd')
			{
				s[i] = 'D';
			}
		}//遍历输入字符串，将大小写d统一为大写D，mark2记录了是否在文段种出现了非d以外的其它字母
		for (int i = 0; i < k; i++)
		{
			if (s[i] == '-')//便利字符串是否有负，有符号是非法输入，有非法输入直接跳出循环，mark2==0代表字符串非法。
			{
				mark2 = 0;
				break;
			}
			if (s[i] != 'D' && mark == 0)//在本循环中，mark代表正在解析的数字范围，mark==0则代表解析部分为n（随机数个数），mark==1则代表解析部分为x（随机数范围）
			{
				n = n * 10 + (s[i] - 48);
			}
			else if (s[i] == 'D')//当检测到D存在，mark置为1，代表开始解析随机数范围x，mark2置于1代表输入字符串无非法符号。
			{
				mark = 1;
				mark2 = 1;
			}
			else//解析内容
			{
				x = x * 10 + (s[i] - 48);
			}
		}//从字符串s解析数字n和x
		if (n * x == 0 || mark2 == 0)//当n或x其中一个为零时，或者mark2为零时，判定为非法输入，
		{
			printf("Error: Illegal entry\n");
			system("pause");
			system("cls");
			continue;
		}
		get_list(n, x);//调用函数get_list输出随机数内容
	}
	printf("bye~\n");
	system("pause");
	return 0;
}

// 定义一个名为get_list的函数，接受两个长整型参数number和sq_number，并返回一个长整型值
long long get_list(long long number, long long sq_number)
{
    // 定义一个长整型变量Output_num，用于记录生成的随机数列表中的元素数量
    long long Output_num = 0;
    // 定义一个长整型变量add_sum，用于累加所有随机数的和
    long long add_sum = 0;
    // 定义一个长整型变量rel_num，用于存储每次生成的随机数
    long long rel_num = 0;
    // 定义一个长整型变量number_copy，用于复制传入的number参数，以便在后续计算中使用
    long long number_copy = number;
    // 获取当前时间，用于随机数生成器的种子
    time_t now = time(NULL);
    // 设置随机数生成器的种子为当前时间
    srand((int)now);
    // 定义一个整型变量buffer_size，用于指定字符串缓冲区的大小
    int buffer_size = 5000;
    // 如果传入的number参数大于1000，则执行以下代码块
    if (number > 1000)
    {
        // 动态分配一个字符型数组buffer，大小为buffer_size
        char* buffer = (char*)calloc(buffer_size, sizeof(char));
        // 循环number参数除以1000的次数，用于生成多个包含1000个随机数的列表
        for (int j = 0; j < number / 1000; j++)
        {
            // 循环1000次，生成1000个随机数
            for (int i = 0; i <= 999; i++)
            {
                // 生成一个1到sq_number之间的随机数
                rel_num = rand() % sq_number + 1;
                // 将生成的随机数累加到add_sum变量中
                add_sum += rel_num;
                // 将生成的随机数转换为字符串，并追加到buffer字符串中，每个数后面跟一个逗号
                snprintf(buffer + strlen(buffer), buffer_size - strlen(buffer), "%lld,", rel_num);
            }
            // 打印buffer中的随机数列表
            printf("%s", buffer);
            // 增加Output_num的值，记录生成的随机数列表数量
            Output_num++;
            // 清空buffer，为下一次生成随机数列表做准备
            strcpy(buffer, "");
        }
        // 减少number的值，已经生成的随机数数量
        number -= Output_num * 1000;
        // 释放buffer所占用的内存
        free(buffer);
    }
    // 如果number小于或等于1000，则执行以下循环
    for (int i = 0; i < number; i++)
    {
        // 生成一个1到sq_number之间的随机数
        rel_num = rand() % sq_number + 1;
        // 将生成的随机数累加到add_sum变量中
        add_sum += rel_num;
        // 打印生成的随机数，后面跟一个逗号
        printf("%lld,", rel_num);
    }
    // 打印所有随机数的和add_sum，以及预期的最大和（number_copy * sq_number / 2）
    printf("\nSum=%lld,Exp=%lld\n", add_sum, number_copy * sq_number / 2);

    // 函数返回0
    return 0;
}