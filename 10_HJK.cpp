#include<iostream>
#include<iomanip>
#include<stdlib.h>        //随机数函数所在头文件
using namespace std;
 
/************************sort_compare类定义***************************/
class sort_compare
{
private:
	int* data;            //存储待排序数据的整型数组
	int size;             //数组大小
	void bubble_sort(double& exchange_times,int Data[]);   //冒泡排序 
	void select_sort(double& exchange_times,int Data[]);   //选择排序
	void insert_sort(double& exchange_times,int Data[]);   //直接插入排序
	void shell_sort(double& exchange_times,int Data[]);    //希尔排序
	int partition(double& exchange_times, int Data[], int left, int right); //快速排序的辅助函数
	void quick_sort(double& exchange_times,int Data[], int left, int right);//快速排序
	void filter_down(double& exchange_times, int Data[], int start, int end_of_heap);//堆排序的辅助函数
	void heap_sort(double& exchange_times,int Data[]);     //堆排序
	void merge(double& exchange_times, int Data[], int list[], int start, int end1, int end2);//归并排序的归并操作
	void merge_pass(double& exchange_times, int Data[], int list[], int length);              //归并操作的流程控制
	void merge_sort(double& exchange_times,int Data[]);    //归并排序
	void radix_sort(double& exchange_times,int Data[]);    //基数排序
public:
	sort_compare(int N)   //构造函数，初始化待排序的数组
	{
		size = N;
		data = new int[size];
		srand(time(NULL));//避免每次程序运行的随机数都一样
		for (int i = 0; i < size; i++)
		{
			data[i] = rand();
		}
	}
	void compare(int choice, int& sort_time, double& exchange_times);//调用排序函数，返回排序时间和交换次数
};


/*******************sort_compare类的成员函数定义**********************/
void sort_compare::bubble_sort(double& exchange_times, int Data[])
{
	bool if_exchange;               //标记是否发生交换

	for (int i = 1; i < size; i++)  //n个数据，最多排序n-1次
	{
		if_exchange = false;        //初始为“未发生交换”的状态
		for (int j = 0; j < size - i; j++)
		{
			if (Data[j] > Data[j + 1])
			{
				int temp = Data[j];
				Data[j] = Data[j + 1];
				Data[j + 1] = temp;

				exchange_times++;   //交换次数+1
				if_exchange = true; //发生交换，标记更新
			}
		}

		if (!if_exchange)           //没有发生交换，代表已经排序完成，可以提前结束
		{
			break;
		}
	}
}

void sort_compare::select_sort(double& exchange_times, int Data[])
{
	for (int i = 0; i < size-1 ; i++)//n个数据，最多排序n-1次
	{
		int min = i;                 //存下最小数据的位置
		for (int j = i + 1; j < size; j++)
		{
			if (Data[j] < Data[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			int temp = Data[i];
			Data[i] = Data[min];
			Data[min] = temp;

			exchange_times++;        //发生交换，交换次数+1
		}
	}
}

void sort_compare::insert_sort(double& exchange_times, int Data[])
{
	for (int i = 1; i < size; i++)    //n个数据，排序n-1次
	{
		int temp = Data[i];           //暂存当前位置数值
		int j = i-1;
		while (j >= 0 && temp < Data[j])
		{
			Data[j+1 ] = Data[j];     //逆序的向后移动一位
			exchange_times++;         //交换次数+1
			j--;
		}
		Data[j + 1] = temp;
	}
}

void sort_compare::shell_sort(double& exchange_times, int Data[])
{
	int gap = size / 2;               //初始化gap的值

	while (gap)                       //当间隔为0时终止
	{
		for (int i = gap; i < size; i++)//对间隔为gap的数据使用直接插入排序法
		{
			int j = i - gap;
			int temp = Data[i];
			while (j >= 0 && temp < Data[j])
			{
				Data[j + gap] = Data[j];
				j = j - gap;

				exchange_times++;     //交换次数+1
			}
			Data[j + gap] = temp;
		}

		gap = gap / 2;                //缩小子序列的数据间隔
	}
}

int sort_compare::partition(double& exchange_times, int Data[], int left, int right)
{
	int middle = (left + right) / 2;    //先找到中间位置的数据，并作为基准
	int temp = Data[middle];
	if (middle != left)
	{
		Data[middle] = Data[left];      //把中间的数据和首个数据交换位置
		exchange_times++;
	}

	int pivotpos = left;
	int i = left+1;
	while (i <= right)
	{
		if (Data[i] < temp)             //比基准小的数移动到左边
		{
			if (++pivotpos != i)
			{
				int t = Data[pivotpos];
				Data[pivotpos] = Data[i];
				Data[i] = t;
				exchange_times++;
			}
		}
		i++;
	}
	Data[left] = Data[pivotpos];        
	Data[pivotpos] = temp;
	exchange_times++;

	return pivotpos;                    //返回最终基准的位置
}

void sort_compare::quick_sort(double& exchange_times, int Data[], int left, int right)
{
	if (left < right) //当待排子序列只有一个数据时停止排序
	{
		int pivotpos = partition(exchange_times, Data, left, right); //对当前大的数组进行一次快排
		quick_sort(exchange_times, Data, left, pivotpos - 1);       //对左子序列进行快排
		quick_sort(exchange_times, Data, pivotpos + 1, right);      //对右子序列进行快排
	}
}

void sort_compare::filter_down(double& exchange_times, int Data[], int start, int end_of_heap)
{
	int temp = Data[start];                        //暂存子树根结点的数值
	int j = start * 2 + 1;                         //左子女

	while ( j<=end_of_heap)                        //左子女存在时继续比较
	{
		if (j+1<= end_of_heap&&Data[j+1]>Data[j])  //存在右子女，且右子女更大时
		{                                          //j记录最大子女的位置
			j++;                                   
		}

		if (temp < Data[j])                        //子女更大则交换子女和父节点的数值                   
		{
			Data[start] = Data[j];
			exchange_times++;                      //交换次数+1
			start = j;                             //父节点下移
			j = 2 * j + 1;                         //新的左子女
		}
		else break;                                //不用交换时直接结束
	}
	Data[start] = temp;                            
}

void sort_compare::heap_sort(double& exchange_times, int Data[])
{
	//构建初始堆
	int i= (size - 2) / 2; //最后一个非叶子结点的位置
	while (i >= 0)
	{
		filter_down(exchange_times, Data, i, size-1);
		i--;
	}

	//基于初始堆
	for (int i = size-1; i >=1; i--)    //只需排好第n-1~第1个数据
	{
		//交换排序后的最大值和最后一个数据
		int temp = Data[0];
		Data[0] = Data[i];
		Data[i] = temp;
		exchange_times++;

		//再次排成最大堆
		filter_down(exchange_times, Data, 0, i-1);    
	}
}

void sort_compare::merge(double& exchange_times, int Data[], int list[], int start, int end1, int end2)
{
	int i = start;    //指向第一个子序列的开头
	int j = end1 + 1; //指向第二个子序列的开头
	int k = start;    //指向归并结果存储链表的新存储位

	while (i <= end1 && j <= end2)
	{
		if (Data[i] <= Data[j])
		{
			list[k] = Data[i];
			i++;
			k++;
		}
		else
		{
			list[k] = Data[j];
			j++;
			k++;
			exchange_times++;
		}
	}
	if (i <= end1) //若子序列1还有剩余
	{
		for (; i <= end1; i++,k++)
		{
			list[k] = Data[i];
		}
	}
	else
	{
		for (; j <= end2; j++, k++)
		{
			list[k] = Data[j];
		}
	}
}

void sort_compare::merge_pass(double& exchange_times, int Data[], int list[], int length)
{
	int current = 0;                      //归并操作的开始为止
	while (current + 2 * length <= size-1)//当即将轮到不完整的子序列时停止
	{
		merge(exchange_times, Data, list, current, current + length-1, current + 2 * length-1);
		current = current + 2 * length;   //下一对子序列的开始位置
	}
	if (current + length-1 >= size - 1)   //若剩余的部分最多构成一个子序列
	{
		for (int i = current; i < size; i++)
		{
			list[i] = Data[i];
		}
	}
	else                                  //若剩余的部分不能构成两个完整子序列
	{
		merge(exchange_times, Data, list, current, current + length - 1, size - 1);
	}
}

void sort_compare::merge_sort(double& exchange_times, int Data[])
{
	int* list = new int[size]; //辅助数组

	int length = 1;        //初始的子序列长度
	while (length < size)  //子序列长度要小于序列的总大小
	{
		merge_pass(exchange_times, Data, list, length); //进行一轮归并
		length *= 2;                                    //下次子序列的长度扩大2倍

		merge_pass(exchange_times, list, Data, length); //将辅助数组list中的数据返回到原数组Data中
		length *= 2;
	}

	delete list;           //释放辅助数组的空间
}

void  sort_compare::radix_sort(double& exchange_times, int Data[])
{
	struct Key       //Key结构体，存下关键码key和下一个元素的位置
	{
		int key;
		int next;
	};

	Key* list = new Key[size];
	int* temp = new int[size]; //辅助数组
	int d = 5;                 //随机数最多五位
	int radix = 10;            //0~9共10种基数
	int front[10];             //指向队头
	int rear[10];              //指向队尾
    int p=1;

	for (int i = 1; i <= d; i++)      //d个关键码，“分配”、“收集”d次
	{
		for (int j = 0; j < size; j++)//先求所有数据的第i个关键码
		{
			list[j].key = Data[j] / p % 10;
		}

		for (int j = 0; j < radix; j++)//初始化front的指向
		{
			front[j] = -1;
			rear[j] = -1;
		}

		for (int j = 0; j < size; j++) //查看list所有元素的关键码，并分成0~9队
		{
			int k = list[j].key;
			if (front[k] == -1)        //该队列为空时
			{
				front[k] = j;
				rear[k] = j;
				list[j].next = -1;
			}
			else                       //该队列不为空时
			{
				list[rear[k]].next = j;//该列原来最后一个元素的next指向list[j]
				rear[k] = j;           //更新raer[k]
				list[j].next = -1;     //新的队尾
			}
		}

		int current = 0;            //current记下开始不为空的队列
		int current_size = 0;       //辅助数组的当前数据个数
		while (front[current] == -1)current++;//队列为空时直接跳过

		//完成第一个非空队列的出队
		for (int j = front[current]; j != -1; j = list[j].next)
		{
			temp[current_size++] = Data[j];   //按队列顺序存放数据
		}

		//完成剩余队列的出队
		for (current += 1; current < radix; current++)
		{
			if (front[current] == -1)continue;      //队列为空时直接跳过
			for (int j = front[current]; j != -1; j = list[j].next)
			{
				temp[current_size++] = Data[j];     //按队列顺序存放数据
			}
		}

		//把Data中的数据按照temp种的数据更新一遍，记录下排序一次后的结果
		for (int j = 0; j < size; j++)        
		{
			Data[j] = temp[j];
		}

		p = p * 10;
	}

	delete list;
	delete temp;
}

void sort_compare::compare(int choice, int& sort_time, double& exchange_times)
{
	int* Data = new int[size];      //辅助数组
	for (int i = 0; i < size; i++)  //保证同一次程序运行时，每个排序算法处理的数据都一样
	{
		Data[i] = data[i];
	}

	clock_t start = clock();        //开始计时
	switch (choice)
	{
	case 1:
		bubble_sort(exchange_times,Data);
		break;
	case 2:
		select_sort(exchange_times,Data);
		break;
	case 3:
		insert_sort(exchange_times,Data);
		break;
	case 4:
		shell_sort(exchange_times,Data);
		break;
	case 5:
		quick_sort(exchange_times,Data,0, size-1);
		break;
	case 6:
		heap_sort(exchange_times,Data);
		break;
	case 7:
		merge_sort(exchange_times,Data);
		break;
	case 8:
		radix_sort(exchange_times,Data);
		break;
	}
	clock_t end = clock();         //结束计时
	sort_time = end - start;       //计算排序时间

	delete Data;                   //清除辅助数组
}



/**************************主函数main()*****************************/
int main()
{
	cout << "**            排序算法比较             **" << endl;
	cout << "=========================================" << endl;
	cout << "**            1---冒泡排序             **" << endl;
	cout << "**            2---选择排序             **" << endl;
	cout << "**            3---直接插入排序         **" << endl;
	cout << "**            4---希尔排序             **" << endl;
	cout << "**            5---快速排序             **" << endl;
	cout << "**            6---堆排序               **" << endl;
	cout << "**            7---归并排序             **" << endl;
	cout << "**            8---基数排序             **" << endl;
	cout << "**            9---退出程序             **" << endl;
	cout << "=========================================" << endl;

	cout << "请输入要产生的随机数的个数：";
	int number;                //随机数的个数
	cin >> number;     
	while (number < 1)
	{
		cout << "随机数个数至少为1，请重新输入随机数个数：";
		cin >> number;
	}

	sort_compare SortCompare(number);
	string sort_name[8] = { "冒泡排序" , "选择排序","直接插入排序","希尔排序","快速排序","堆排序","归并排序","基数排序" };

	int choice;                //用户选择的排序算法
	cout << "请选择排序算法：";
	cin >> choice;
	while (choice < 1 || choice>9)
	{
		cout << "该指令不存在，请重新选择操作：";
		cin >> choice;
	}

	while (choice != 9)
	{
		int sort_time = 0;         //排序时间
		double exchange_times = 0; //交换次数
		SortCompare.compare(choice, sort_time, exchange_times);
		cout << sort_name[choice - 1] << "所用时间：" << sort_time << endl;
		cout << sort_name[choice - 1] << "交换次数：" <<setprecision(16) << exchange_times << endl << endl;
		cout << "请选择排序算法：";

		cin >> choice;
		while (choice < 1 || choice>9)
		{
			cout << "该指令不存在，请重新选择操作：";
			cin >> choice;
		}
	}
}