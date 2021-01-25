#include "3_1952211_�ƽ���.h"   //ͷ�ļ�����ջ�ࡢ�ڵ��ࡢ��ͼ�������
#include<iomanip>

/*****************Stack��ĳ�Ա��������******************/
void Stack::push(stacknode* p) //��ջ
{
	p->next = top;
	top = p;
}

stacknode* Stack::pop()       //��ջ
{
	if (top == NULL)return NULL;//ջ��ʱ����NULL
	else
	{
		stacknode* p = top;     //������ջ
		top = top->next;
		return p;
	}
}

int Stack::is_empty()           //���ջ
{
	if (top == NULL)return 1;
	else return 0;
}


/******************Maze��ĳ�Ա��������*******************/
void Maze::set_maze(int option) //����option������ͼ�����÷�ʽ
{
	start = new stacknode;      //��ʼλ��
	exit = new stacknode;       //�յ�λ��

	//option==1���û��Լ��趨�Թ�
	if (option == 1)            
	{
		cout << "����������������:";
		cin >> row >> col;
		while (row < 1 || col < 1)
		{
			cout << "��������ȷ��������������";
			cin >> row >> col;
		}

		maze = new char* [row]; //�Թ��ö�ά����洢
		visit = new bool* [row];//visit�����������ĳЩλ���Ƿ��߹�
		for (int i = 0; i < row; i++)
		{
			maze[i] = new char[col];
			visit[i] = new bool[col];
		}

		cout << "�����·�����ÿ��λ�õı�־('#'����ǽ��'0'����ͨ��)��\n";
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				cin >> maze[i][j];//�û�����ÿ��λ�õ���Ϣ
				visit[i][j] = 0;  //��ʼ��ȫΪ0����ʾû���߹��κεط�
			}
		}
		print_maze();             //��ӡ��ʼ���ĵ�ͼ

		cout << "�������Թ����������ͳ������꣺";
		cin >> start->x >> start->y >> exit->x >> exit->y;

		//��ڡ����ڲ��Ϸ�ʱ����Ҫ��������
		if (start->x<0 || start->x>row - 1|| start->y<0 || start->y>col - 1 || maze[start->x][start->y]=='#')
		{
			cout << "�����������겻�Ϸ�������������������꣺";
			cin >> start->x >> start->y;
		}
		if (exit->x<0 || exit->x>row - 1 || exit->y<0 || exit->y>col - 1 || maze[exit->x][exit->y] == '#')
		{
			cout << "����ĳ������겻�Ϸ�������������������꣺";
			cin >> exit->x >> exit->y;
		}
	}

	//option==2������Ĭ���Թ�
	else if (option == 2)
	{
		row = col = 7;        //Ĭ�ϵ�7X7�Թ�
		maze = new char* [7]; //�Թ�����
		for (int i = 0; i < 7; i++)
		{
			maze[i] = new char[7];
		}
		char array[7][7] =
		{
		{'#','#','#','#','#','#','#'},
		{'#','0','#','0','0','0','#'},
		{'#','0','#','0','#','#','#'},
		{'#','0','0','0','#','0','#'},
		{'#','0','#','0','0','0','#'},
		{'#','0','#','0','#','0','#'},
		{'#','#','#','#','#','#','#'} 
		};
		visit = new bool* [7]; //�������
		for (int i = 0; i < 7; i++)
		{
			visit[i] = new bool[7];
		}
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				maze[i][j] = array[i][j];//��Ĭ���Թ������Թ�����
				visit[i][j] = 0;
			}
		}
		start->x = 1; start->y = 1;      //Ĭ����㣨1��1��
		exit->x = 5; exit->y = 5;        //Ĭ���յ㣨5��5��
		print_maze();                    //��ӡ��ʼ���ĵ�ͼ
	}
}

void Maze::print_maze()                  //��ӡ�Թ�
{
	cout << "�Թ���ͼ��\n\n";
	cout << setiosflags(ios::left) << setw(8) << ' ';
	for (int i = 0; i < col; i++)
	{
		cout << i << setw(7) << "��";
	}
	cout << endl;
	for (int j = 0; j < row; j++)
	{
		cout << j << setw(7) << "��";
		for (int k = 0; k < col; k++)
		{
			cout << setw(8) << maze[j][k];
		}
		cout << endl << endl;
	}
}

int Maze::seek()                        //���ݷ���������������������Թ���·����
{
	stacknode* p = start;               //����㿪ʼ
	visit[start->x][start->y] = 1;      //�������߹�

	while (p->x != exit->x || p->y != exit->y)//�ߵ��յ�Ϊֹ
	{
		int i;                          //i�����ж�ǰ���ķ����������ң�������ж��Ĵ�
		for (i = 0; i < 4; i++)         //���ա���������������˳����̽
		{
			if (i == 0)    //����
			{
				if (p->y > 0 && maze[p->x][p->y - 1] == '0' && visit[p->x][p->y - 1] == 0)//�����߲���û�г���
				{
					stacknode* newnode = new stacknode;
					newnode->x = p->x; newnode->y = p->y - 1;
					path.push(p);      //��ǰλ�ý�վ
					p = newnode;       //ǰ��һ��
					visit[p->x][p->y] = 1;
					break;             //���µ�����ѭ��
				}
			}

			else if (i == 1)//����
			{
				if (p->x > 0 && maze[p->x - 1][p->y] == '0' && visit[p->x - 1][p->y] == 0)//�����߲���û�г���
				{
					stacknode* newnode = new stacknode;
					newnode->x = p->x - 1; newnode->y = p->y;
					path.push(p);      //��ǰλ�ý�վ
					p = newnode;       //ǰ��һ��
					visit[p->x][p->y] = 1;
					break;             //���µ�����ѭ��
				}
			}

			else if (i == 2)//����
			{
				if (p->y < col - 1 && maze[p->x][p->y + 1] == '0' && visit[p->x][p->y + 1] == 0)//�����߲���û�г���
				{
					stacknode* newnode = new stacknode;
					newnode->x = p->x; newnode->y = p->y + 1;
					path.push(p);      //��ǰλ�ý�վ
					p = newnode;       //ǰ��һ��
					visit[p->x][p->y] = 1;
					break;             //���µ�����ѭ��
				}
			}

			else if (i == 3)//����
			{
				if (p->x < row - 1 && maze[p->x + 1][p->y] == '0' && visit[p->x + 1][p->y] == 0)//�����߲���û�г���
				{
					stacknode* newnode = new stacknode;
					newnode->x = p->x + 1; newnode->y = p->y;
					path.push(p);      //��ǰλ�ý�վ
					p = newnode;       //ǰ��һ��
					visit[p->x][p->y] = 1;
					break;             //���µ�����ѭ��
				}
			}
		}

		if (i == 4)//i==4��˵�����з���û����ͨ��Ҫ��ʼ����
		{
			if (!path.is_empty())
			{
				delete p;              //�ͷŵ�ǰ��·���ߵĽڵ�ռ�
				p = path.pop();        //��ʼ����
			}
			else                       //ջ�գ�˵��������·��������ʧ�ܵı�־����������
			{
				return 0;
			}
		}
	}
	path.push(p);  //���յ��ջ
	return 1;      //�ɹ��ҵ�·�������سɹ��ı�־
}

void Maze::print_path()             //��ӡ�Թ�
{
	cout << "�Թ�·����\n\n";
	Stack way;                     
	stacknode* p;
	while ((p = path.pop()) != NULL)//����ջ�ڽڵ��˳�򣬷���������˳�����ȷ��
	{
		way.push(p);
	}
	while ((p = way.pop()) != NULL)
	{
		maze[p->x][p->y] = 'x';//��·�߼�¼�ڵ�ͼ��
		cout << '<' << p->x << ',' << p->y << "> ";//���·��
		if (p->x != exit->x || p->y != exit->y)cout << "---> ";
	}
	cout << endl << endl;
}

int main()
{
	int option;                //�û�ѡ��һ���Թ��趨��ʽ
	cout << "�����趨�Թ�������1��ʼ�ֶ����ã�����2��ʼ����Ĭ���Թ�����";
	cin >> option;
	while (option != 2 && option != 1)
	{
		cout << "����ѡ��ڷ�Χ�ڣ����������룺";
		cin.ignore(100,'\n');
		cin >> option;
	}

	Maze maze1(option);       //�����Թ�

	int result = maze1.seek();//Ѱ·�Ľ��

	if (result)               //�ɹ�
	{
		maze1.print_path();   //��ӡ��·
		maze1.print_maze();   //��ӡ����·���ĵ�ͼ
	}
	else                      //ʧ��
	{
		cout << "û���ҵ�·��";
	}
}