#include<iostream>
using namespace std;
/***********************最小堆的类定义*************************/
class min_heap
{
private:
	double* wood;            //堆内数据的存储结构为数组
	int maxSize;             //数组的最大元素个数
	int currentSize;         //数组内的当前元素个数
	int first, second, expense;//first是堆内的最小数、second是第二小的数、expense是花费
public:
	min_heap(int N =10)      //构造函数，初始化数据、开辟数组空间
	{
		maxSize = N;
		currentSize = 0;
		expense = 0;
		wood = new double[maxSize];
	}
	~min_heap()              //析构函数，清空堆
	{
		delete wood;
	}
	void input();            //输入数据
	void sort();             //排成最小堆
	void down(int start);    //自上而下比较
	bool get_root(int& item);//取出堆顶的数，采用引用类型参数的形式传递值
	void insert(int new_wood)//插入新木头,总个数加一并排序
	{ 
		wood[currentSize++] = new_wood;
		sort(); 
	}
	void calculate();        //计算总费用
};


/***********************最小堆的成员函数定义*************************/
void min_heap::input()
{
	for (int i = 0; i < maxSize; i++)
	{
		cin >> wood[i];
		currentSize++;
	}
	sort();                  //输入完就排成最小堆
}

void min_heap::down(int start)
{
	int i = start;                        //当前节点的位置
	int j = 2 * i + 1;                    //当前节点的左子女
	int temp = wood[i];                   //辅助变量，用来存储当前节点的数值大小
	while (j < currentSize)
	{
		if (j + 1 < currentSize)          //该节点有右子女时
		{
			if (wood[j] > wood[j + 1])j++;//j取数值最小的子女序号
		}
		if (wood[i] > wood[j])            //数值小的节点上移
		{
			wood[i] = wood[j];
			wood[j] = temp;
			i = j;
			j = 2 * j + 1;
		}
		else break;
	}
}

void min_heap::sort()
{
	int start = (currentSize - 1) / 2;//从最后一个非叶子节点开始排
	while (start > -1)                //循环到根节点截止
	{
		down(start);                  //对于每个节点都采用自上而下式排序
		start--;                      //排完当前节点为根结点的树后开始下一个节点
	}
}

bool min_heap::get_root(int& item)
{
	if (currentSize == 0)             //堆空时返回失败标志
	{
		return false;
	}
	else
	{
		item = wood[0];               //传递堆顶的值
		wood[0] = wood[--currentSize];//最后一个值覆盖取出的值
		sort();                       //再次排序成最小堆
		return true;                  //返回成功的标志
	}
}

void min_heap::calculate()
{
	while (get_root(first) && get_root(second))//当两个数都成功取出时才能继续循环
	{
		int new_wood = first + second;          
		expense = expense + new_wood;
		insert(new_wood);
	}
	get_root(expense);                         //取出最小费用
	cout << "最小花费是：" << expense << endl;  //最小堆内只剩一个树时说明已经求出最小开销。
}


/****************************主函数main******************************/
int main()
{
	int N;
	cout << "请输入木头要锯的个数：";
	cin >> N;
	while (N < 2)
	{
		cout << "木头的个数至少是2，请重新输入：";
		cin >> N;
	}
	cout << "请输入每个木头锯后的长度：";
	min_heap Heap(N);     //调用构造函数，开辟数组
	Heap.input();         //输入木块长度
	Heap.calculate();     //计算并输出结果
}