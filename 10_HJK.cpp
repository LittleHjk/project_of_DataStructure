#include<iostream>
#include<iomanip>
#include<stdlib.h>        //�������������ͷ�ļ�
using namespace std;
 
/************************sort_compare�ඨ��***************************/
class sort_compare
{
private:
	int* data;            //�洢���������ݵ���������
	int size;             //�����С
	void bubble_sort(double& exchange_times,int Data[]);   //ð������ 
	void select_sort(double& exchange_times,int Data[]);   //ѡ������
	void insert_sort(double& exchange_times,int Data[]);   //ֱ�Ӳ�������
	void shell_sort(double& exchange_times,int Data[]);    //ϣ������
	int partition(double& exchange_times, int Data[], int left, int right); //��������ĸ�������
	void quick_sort(double& exchange_times,int Data[], int left, int right);//��������
	void filter_down(double& exchange_times, int Data[], int start, int end_of_heap);//������ĸ�������
	void heap_sort(double& exchange_times,int Data[]);     //������
	void merge(double& exchange_times, int Data[], int list[], int start, int end1, int end2);//�鲢����Ĺ鲢����
	void merge_pass(double& exchange_times, int Data[], int list[], int length);              //�鲢���������̿���
	void merge_sort(double& exchange_times,int Data[]);    //�鲢����
	void radix_sort(double& exchange_times,int Data[]);    //��������
public:
	sort_compare(int N)   //���캯������ʼ�������������
	{
		size = N;
		data = new int[size];
		srand(time(NULL));//����ÿ�γ������е��������һ��
		for (int i = 0; i < size; i++)
		{
			data[i] = rand();
		}
	}
	void compare(int choice, int& sort_time, double& exchange_times);//��������������������ʱ��ͽ�������
};


/*******************sort_compare��ĳ�Ա��������**********************/
void sort_compare::bubble_sort(double& exchange_times, int Data[])
{
	bool if_exchange;               //����Ƿ�������

	for (int i = 1; i < size; i++)  //n�����ݣ��������n-1��
	{
		if_exchange = false;        //��ʼΪ��δ������������״̬
		for (int j = 0; j < size - i; j++)
		{
			if (Data[j] > Data[j + 1])
			{
				int temp = Data[j];
				Data[j] = Data[j + 1];
				Data[j + 1] = temp;

				exchange_times++;   //��������+1
				if_exchange = true; //������������Ǹ���
			}
		}

		if (!if_exchange)           //û�з��������������Ѿ�������ɣ�������ǰ����
		{
			break;
		}
	}
}

void sort_compare::select_sort(double& exchange_times, int Data[])
{
	for (int i = 0; i < size-1 ; i++)//n�����ݣ��������n-1��
	{
		int min = i;                 //������С���ݵ�λ��
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

			exchange_times++;        //������������������+1
		}
	}
}

void sort_compare::insert_sort(double& exchange_times, int Data[])
{
	for (int i = 1; i < size; i++)    //n�����ݣ�����n-1��
	{
		int temp = Data[i];           //�ݴ浱ǰλ����ֵ
		int j = i-1;
		while (j >= 0 && temp < Data[j])
		{
			Data[j+1 ] = Data[j];     //���������ƶ�һλ
			exchange_times++;         //��������+1
			j--;
		}
		Data[j + 1] = temp;
	}
}

void sort_compare::shell_sort(double& exchange_times, int Data[])
{
	int gap = size / 2;               //��ʼ��gap��ֵ

	while (gap)                       //�����Ϊ0ʱ��ֹ
	{
		for (int i = gap; i < size; i++)//�Լ��Ϊgap������ʹ��ֱ�Ӳ�������
		{
			int j = i - gap;
			int temp = Data[i];
			while (j >= 0 && temp < Data[j])
			{
				Data[j + gap] = Data[j];
				j = j - gap;

				exchange_times++;     //��������+1
			}
			Data[j + gap] = temp;
		}

		gap = gap / 2;                //��С�����е����ݼ��
	}
}

int sort_compare::partition(double& exchange_times, int Data[], int left, int right)
{
	int middle = (left + right) / 2;    //���ҵ��м�λ�õ����ݣ�����Ϊ��׼
	int temp = Data[middle];
	if (middle != left)
	{
		Data[middle] = Data[left];      //���м�����ݺ��׸����ݽ���λ��
		exchange_times++;
	}

	int pivotpos = left;
	int i = left+1;
	while (i <= right)
	{
		if (Data[i] < temp)             //�Ȼ�׼С�����ƶ������
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

	return pivotpos;                    //�������ջ�׼��λ��
}

void sort_compare::quick_sort(double& exchange_times, int Data[], int left, int right)
{
	if (left < right) //������������ֻ��һ������ʱֹͣ����
	{
		int pivotpos = partition(exchange_times, Data, left, right); //�Ե�ǰ����������һ�ο���
		quick_sort(exchange_times, Data, left, pivotpos - 1);       //���������н��п���
		quick_sort(exchange_times, Data, pivotpos + 1, right);      //���������н��п���
	}
}

void sort_compare::filter_down(double& exchange_times, int Data[], int start, int end_of_heap)
{
	int temp = Data[start];                        //�ݴ�������������ֵ
	int j = start * 2 + 1;                         //����Ů

	while ( j<=end_of_heap)                        //����Ů����ʱ�����Ƚ�
	{
		if (j+1<= end_of_heap&&Data[j+1]>Data[j])  //��������Ů��������Ů����ʱ
		{                                          //j��¼�����Ů��λ��
			j++;                                   
		}

		if (temp < Data[j])                        //��Ů�����򽻻���Ů�͸��ڵ����ֵ                   
		{
			Data[start] = Data[j];
			exchange_times++;                      //��������+1
			start = j;                             //���ڵ�����
			j = 2 * j + 1;                         //�µ�����Ů
		}
		else break;                                //���ý���ʱֱ�ӽ���
	}
	Data[start] = temp;                            
}

void sort_compare::heap_sort(double& exchange_times, int Data[])
{
	//������ʼ��
	int i= (size - 2) / 2; //���һ����Ҷ�ӽ���λ��
	while (i >= 0)
	{
		filter_down(exchange_times, Data, i, size-1);
		i--;
	}

	//���ڳ�ʼ��
	for (int i = size-1; i >=1; i--)    //ֻ���źõ�n-1~��1������
	{
		//�������������ֵ�����һ������
		int temp = Data[0];
		Data[0] = Data[i];
		Data[i] = temp;
		exchange_times++;

		//�ٴ��ų�����
		filter_down(exchange_times, Data, 0, i-1);    
	}
}

void sort_compare::merge(double& exchange_times, int Data[], int list[], int start, int end1, int end2)
{
	int i = start;    //ָ���һ�������еĿ�ͷ
	int j = end1 + 1; //ָ��ڶ��������еĿ�ͷ
	int k = start;    //ָ��鲢����洢������´洢λ

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
	if (i <= end1) //��������1����ʣ��
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
	int current = 0;                      //�鲢�����Ŀ�ʼΪֹ
	while (current + 2 * length <= size-1)//�������ֵ���������������ʱֹͣ
	{
		merge(exchange_times, Data, list, current, current + length-1, current + 2 * length-1);
		current = current + 2 * length;   //��һ�������еĿ�ʼλ��
	}
	if (current + length-1 >= size - 1)   //��ʣ��Ĳ�����๹��һ��������
	{
		for (int i = current; i < size; i++)
		{
			list[i] = Data[i];
		}
	}
	else                                  //��ʣ��Ĳ��ֲ��ܹ�����������������
	{
		merge(exchange_times, Data, list, current, current + length - 1, size - 1);
	}
}

void sort_compare::merge_sort(double& exchange_times, int Data[])
{
	int* list = new int[size]; //��������

	int length = 1;        //��ʼ�������г���
	while (length < size)  //�����г���ҪС�����е��ܴ�С
	{
		merge_pass(exchange_times, Data, list, length); //����һ�ֹ鲢
		length *= 2;                                    //�´������еĳ�������2��

		merge_pass(exchange_times, list, Data, length); //����������list�е����ݷ��ص�ԭ����Data��
		length *= 2;
	}

	delete list;           //�ͷŸ�������Ŀռ�
}

void  sort_compare::radix_sort(double& exchange_times, int Data[])
{
	struct Key       //Key�ṹ�壬���¹ؼ���key����һ��Ԫ�ص�λ��
	{
		int key;
		int next;
	};

	Key* list = new Key[size];
	int* temp = new int[size]; //��������
	int d = 5;                 //����������λ
	int radix = 10;            //0~9��10�ֻ���
	int front[10];             //ָ���ͷ
	int rear[10];              //ָ���β
    int p=1;

	for (int i = 1; i <= d; i++)      //d���ؼ��룬�����䡱�����ռ���d��
	{
		for (int j = 0; j < size; j++)//�����������ݵĵ�i���ؼ���
		{
			list[j].key = Data[j] / p % 10;
		}

		for (int j = 0; j < radix; j++)//��ʼ��front��ָ��
		{
			front[j] = -1;
			rear[j] = -1;
		}

		for (int j = 0; j < size; j++) //�鿴list����Ԫ�صĹؼ��룬���ֳ�0~9��
		{
			int k = list[j].key;
			if (front[k] == -1)        //�ö���Ϊ��ʱ
			{
				front[k] = j;
				rear[k] = j;
				list[j].next = -1;
			}
			else                       //�ö��в�Ϊ��ʱ
			{
				list[rear[k]].next = j;//����ԭ�����һ��Ԫ�ص�nextָ��list[j]
				rear[k] = j;           //����raer[k]
				list[j].next = -1;     //�µĶ�β
			}
		}

		int current = 0;            //current���¿�ʼ��Ϊ�յĶ���
		int current_size = 0;       //��������ĵ�ǰ���ݸ���
		while (front[current] == -1)current++;//����Ϊ��ʱֱ������

		//��ɵ�һ���ǿն��еĳ���
		for (int j = front[current]; j != -1; j = list[j].next)
		{
			temp[current_size++] = Data[j];   //������˳��������
		}

		//���ʣ����еĳ���
		for (current += 1; current < radix; current++)
		{
			if (front[current] == -1)continue;      //����Ϊ��ʱֱ������
			for (int j = front[current]; j != -1; j = list[j].next)
			{
				temp[current_size++] = Data[j];     //������˳��������
			}
		}

		//��Data�е����ݰ���temp�ֵ����ݸ���һ�飬��¼������һ�κ�Ľ��
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
	int* Data = new int[size];      //��������
	for (int i = 0; i < size; i++)  //��֤ͬһ�γ�������ʱ��ÿ�������㷨��������ݶ�һ��
	{
		Data[i] = data[i];
	}

	clock_t start = clock();        //��ʼ��ʱ
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
	clock_t end = clock();         //������ʱ
	sort_time = end - start;       //��������ʱ��

	delete Data;                   //�����������
}



/**************************������main()*****************************/
int main()
{
	cout << "**            �����㷨�Ƚ�             **" << endl;
	cout << "=========================================" << endl;
	cout << "**            1---ð������             **" << endl;
	cout << "**            2---ѡ������             **" << endl;
	cout << "**            3---ֱ�Ӳ�������         **" << endl;
	cout << "**            4---ϣ������             **" << endl;
	cout << "**            5---��������             **" << endl;
	cout << "**            6---������               **" << endl;
	cout << "**            7---�鲢����             **" << endl;
	cout << "**            8---��������             **" << endl;
	cout << "**            9---�˳�����             **" << endl;
	cout << "=========================================" << endl;

	cout << "������Ҫ������������ĸ�����";
	int number;                //������ĸ���
	cin >> number;     
	while (number < 1)
	{
		cout << "�������������Ϊ1�����������������������";
		cin >> number;
	}

	sort_compare SortCompare(number);
	string sort_name[8] = { "ð������" , "ѡ������","ֱ�Ӳ�������","ϣ������","��������","������","�鲢����","��������" };

	int choice;                //�û�ѡ��������㷨
	cout << "��ѡ�������㷨��";
	cin >> choice;
	while (choice < 1 || choice>9)
	{
		cout << "��ָ����ڣ�������ѡ�������";
		cin >> choice;
	}

	while (choice != 9)
	{
		int sort_time = 0;         //����ʱ��
		double exchange_times = 0; //��������
		SortCompare.compare(choice, sort_time, exchange_times);
		cout << sort_name[choice - 1] << "����ʱ�䣺" << sort_time << endl;
		cout << sort_name[choice - 1] << "����������" <<setprecision(16) << exchange_times << endl << endl;
		cout << "��ѡ�������㷨��";

		cin >> choice;
		while (choice < 1 || choice>9)
		{
			cout << "��ָ����ڣ�������ѡ�������";
			cin >> choice;
		}
	}
}