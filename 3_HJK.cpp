#include "3_1952211_黄金坤.h"   //头文件包含栈类、节点类、地图类的声明
#include<iomanip>

/*****************Stack类的成员函数定义******************/
void Stack::push(stacknode* p) //入栈
{
	p->next = top;
	top = p;
}

stacknode* Stack::pop()       //出栈
{
	if (top == NULL)return NULL;//栈空时返回NULL
	else
	{
		stacknode* p = top;     //正常出栈
		top = top->next;
		return p;
	}
}

int Stack::is_empty()           //清空栈
{
	if (top == NULL)return 1;
	else return 0;
}


/******************Maze类的成员函数定义*******************/
void Maze::set_maze(int option) //根据option决定地图的设置方式
{
	start = new stacknode;      //开始位置
	exit = new stacknode;       //终点位置

	//option==1，用户自己设定迷宫
	if (option == 1)            
	{
		cout << "请输入行数、列数:";
		cin >> row >> col;
		while (row < 1 || col < 1)
		{
			cout << "请输入正确的行数和列数：";
			cin >> row >> col;
		}

		maze = new char* [row]; //迷宫用二维数组存储
		visit = new bool* [row];//visit数组用来标记某些位置是否走过
		for (int i = 0; i < row; i++)
		{
			maze[i] = new char[col];
			visit[i] = new bool[col];
		}

		cout << "请在下方输入每个位置的标志('#'代表墙，'0'代表通道)：\n";
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				cin >> maze[i][j];//用户输入每个位置的信息
				visit[i][j] = 0;  //初始化全为0，表示没有走过任何地方
			}
		}
		print_maze();             //打印初始化的地图

		cout << "请输入迷宫的入口坐标和出口坐标：";
		cin >> start->x >> start->y >> exit->x >> exit->y;

		//入口、出口不合法时，需要重新输入
		if (start->x<0 || start->x>row - 1|| start->y<0 || start->y>col - 1 || maze[start->x][start->y]=='#')
		{
			cout << "输入的入口坐标不合法，请重新输入入口坐标：";
			cin >> start->x >> start->y;
		}
		if (exit->x<0 || exit->x>row - 1 || exit->y<0 || exit->y>col - 1 || maze[exit->x][exit->y] == '#')
		{
			cout << "输入的出口坐标不合法，请重新输入出口坐标：";
			cin >> exit->x >> exit->y;
		}
	}

	//option==2，采用默认迷宫
	else if (option == 2)
	{
		row = col = 7;        //默认的7X7迷宫
		maze = new char* [7]; //迷宫数组
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
		visit = new bool* [7]; //标记数组
		for (int i = 0; i < 7; i++)
		{
			visit[i] = new bool[7];
		}
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				maze[i][j] = array[i][j];//用默认迷宫设置迷宫数组
				visit[i][j] = 0;
			}
		}
		start->x = 1; start->y = 1;      //默认起点（1，1）
		exit->x = 5; exit->y = 5;        //默认终点（5，5）
		print_maze();                    //打印初始化的地图
	}
}

void Maze::print_maze()                  //打印迷宫
{
	cout << "迷宫地图：\n\n";
	cout << setiosflags(ios::left) << setw(8) << ' ';
	for (int i = 0; i < col; i++)
	{
		cout << i << setw(7) << "列";
	}
	cout << endl;
	for (int j = 0; j < row; j++)
	{
		cout << j << setw(7) << "行";
		for (int k = 0; k < col; k++)
		{
			cout << setw(8) << maze[j][k];
		}
		cout << endl << endl;
	}
}

int Maze::seek()                        //回溯法（深度优先搜索）搜索迷宫道路函数
{
	stacknode* p = start;               //从起点开始
	visit[start->x][start->y] = 1;      //标记起点走过

	while (p->x != exit->x || p->y != exit->y)//走到终点为止
	{
		int i;                          //i用来判断前进的方向（上下左右），最多判断四次
		for (i = 0; i < 4; i++)         //按照←、↑、→、↓的顺序试探
		{
			if (i == 0)    //向左
			{
				if (p->y > 0 && maze[p->x][p->y - 1] == '0' && visit[p->x][p->y - 1] == 0)//可以走并且没有尝试
				{
					stacknode* newnode = new stacknode;
					newnode->x = p->x; newnode->y = p->y - 1;
					path.push(p);      //当前位置进站
					p = newnode;       //前进一格
					visit[p->x][p->y] = 1;
					break;             //从新点重新循环
				}
			}

			else if (i == 1)//向上
			{
				if (p->x > 0 && maze[p->x - 1][p->y] == '0' && visit[p->x - 1][p->y] == 0)//可以走并且没有尝试
				{
					stacknode* newnode = new stacknode;
					newnode->x = p->x - 1; newnode->y = p->y;
					path.push(p);      //当前位置进站
					p = newnode;       //前进一格
					visit[p->x][p->y] = 1;
					break;             //从新点重新循环
				}
			}

			else if (i == 2)//向右
			{
				if (p->y < col - 1 && maze[p->x][p->y + 1] == '0' && visit[p->x][p->y + 1] == 0)//可以走并且没有尝试
				{
					stacknode* newnode = new stacknode;
					newnode->x = p->x; newnode->y = p->y + 1;
					path.push(p);      //当前位置进站
					p = newnode;       //前进一格
					visit[p->x][p->y] = 1;
					break;             //从新点重新循环
				}
			}

			else if (i == 3)//向下
			{
				if (p->x < row - 1 && maze[p->x + 1][p->y] == '0' && visit[p->x + 1][p->y] == 0)//可以走并且没有尝试
				{
					stacknode* newnode = new stacknode;
					newnode->x = p->x + 1; newnode->y = p->y;
					path.push(p);      //当前位置进站
					p = newnode;       //前进一格
					visit[p->x][p->y] = 1;
					break;             //从新点重新循环
				}
			}
		}

		if (i == 4)//i==4，说明所有方向都没有走通，要开始回溯
		{
			if (!path.is_empty())
			{
				delete p;              //释放当前无路可走的节点空间
				p = path.pop();        //开始回溯
			}
			else                       //栈空，说明不存在路径，返回失败的标志，结束函数
			{
				return 0;
			}
		}
	}
	path.push(p);  //将终点进栈
	return 1;      //成功找到路径，返回成功的标志
}

void Maze::print_path()             //打印迷宫
{
	cout << "迷宫路径：\n\n";
	Stack way;                     
	stacknode* p;
	while ((p = path.pop()) != NULL)//调整栈内节点的顺序，方便输出结果顺序的正确性
	{
		way.push(p);
	}
	while ((p = way.pop()) != NULL)
	{
		maze[p->x][p->y] = 'x';//将路线记录在地图中
		cout << '<' << p->x << ',' << p->y << "> ";//输出路径
		if (p->x != exit->x || p->y != exit->y)cout << "---> ";
	}
	cout << endl << endl;
}

int main()
{
	int option;                //用户选择一个迷宫设定方式
	cout << "请先设定迷宫（输入1开始手动设置，输入2开始采用默认迷宫）：";
	cin >> option;
	while (option != 2 && option != 1)
	{
		cout << "输入选项不在范围内，请重新输入：";
		cin.ignore(100,'\n');
		cin >> option;
	}

	Maze maze1(option);       //创建迷宫

	int result = maze1.seek();//寻路的结果

	if (result)               //成功
	{
		maze1.print_path();   //打印道路
		maze1.print_maze();   //打印带有路径的地图
	}
	else                      //失败
	{
		cout << "没有找到路径";
	}
}