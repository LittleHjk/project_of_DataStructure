#include<iostream>
using namespace std;
/***********************��С�ѵ��ඨ��*************************/
class min_heap
{
private:
	double* wood;            //�������ݵĴ洢�ṹΪ����
	int maxSize;             //��������Ԫ�ظ���
	int currentSize;         //�����ڵĵ�ǰԪ�ظ���
	int first, second, expense;//first�Ƕ��ڵ���С����second�ǵڶ�С������expense�ǻ���
public:
	min_heap(int N =10)      //���캯������ʼ�����ݡ���������ռ�
	{
		maxSize = N;
		currentSize = 0;
		expense = 0;
		wood = new double[maxSize];
	}
	~min_heap()              //������������ն�
	{
		delete wood;
	}
	void input();            //��������
	void sort();             //�ų���С��
	void down(int start);    //���϶��±Ƚ�
	bool get_root(int& item);//ȡ���Ѷ������������������Ͳ�������ʽ����ֵ
	void insert(int new_wood)//������ľͷ,�ܸ�����һ������
	{ 
		wood[currentSize++] = new_wood;
		sort(); 
	}
	void calculate();        //�����ܷ���
};


/***********************��С�ѵĳ�Ա��������*************************/
void min_heap::input()
{
	for (int i = 0; i < maxSize; i++)
	{
		cin >> wood[i];
		currentSize++;
	}
	sort();                  //��������ų���С��
}

void min_heap::down(int start)
{
	int i = start;                        //��ǰ�ڵ��λ��
	int j = 2 * i + 1;                    //��ǰ�ڵ������Ů
	int temp = wood[i];                   //���������������洢��ǰ�ڵ����ֵ��С
	while (j < currentSize)
	{
		if (j + 1 < currentSize)          //�ýڵ�������Ůʱ
		{
			if (wood[j] > wood[j + 1])j++;//jȡ��ֵ��С����Ů���
		}
		if (wood[i] > wood[j])            //��ֵС�Ľڵ�����
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
	int start = (currentSize - 1) / 2;//�����һ����Ҷ�ӽڵ㿪ʼ��
	while (start > -1)                //ѭ�������ڵ��ֹ
	{
		down(start);                  //����ÿ���ڵ㶼�������϶���ʽ����
		start--;                      //���굱ǰ�ڵ�Ϊ����������ʼ��һ���ڵ�
	}
}

bool min_heap::get_root(int& item)
{
	if (currentSize == 0)             //�ѿ�ʱ����ʧ�ܱ�־
	{
		return false;
	}
	else
	{
		item = wood[0];               //���ݶѶ���ֵ
		wood[0] = wood[--currentSize];//���һ��ֵ����ȡ����ֵ
		sort();                       //�ٴ��������С��
		return true;                  //���سɹ��ı�־
	}
}

void min_heap::calculate()
{
	while (get_root(first) && get_root(second))//�����������ɹ�ȡ��ʱ���ܼ���ѭ��
	{
		int new_wood = first + second;          
		expense = expense + new_wood;
		insert(new_wood);
	}
	get_root(expense);                         //ȡ����С����
	cout << "��С�����ǣ�" << expense << endl;  //��С����ֻʣһ����ʱ˵���Ѿ������С������
}


/****************************������main******************************/
int main()
{
	int N;
	cout << "������ľͷҪ��ĸ�����";
	cin >> N;
	while (N < 2)
	{
		cout << "ľͷ�ĸ���������2�����������룺";
		cin >> N;
	}
	cout << "������ÿ��ľͷ���ĳ��ȣ�";
	min_heap Heap(N);     //���ù��캯������������
	Heap.input();         //����ľ�鳤��
	Heap.calculate();     //���㲢������
}