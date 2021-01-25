#include"8_1952211_黄金坤.h"
/***************************graph(图)的成员函数的定义***************************************/
template<class T>
void graph<T>::insert_edge(edge<T>* new_edge)//添加新边，完善邻接表
{
	int index1 = find(new_edge->node1);    //找到新边的两个顶点所在的位置
	int index2 = find(new_edge->node2);

	edge_of_adj<T>* p = new edge_of_adj<T>;//创建新的边结点p、q
	edge_of_adj<T>* q = new edge_of_adj<T>;
	p->index = index2;
	p->key = new_edge->key;
	q->index = index1;
	q->key = new_edge->key;

	if (node_table[index1].first == NULL)   //分别将新的边结点p、q接入邻接表
	{
		node_table[index1].first = p;
	}
	else
	{
		node_table[index1].tail->next = p;
	}
	node_table[index1].tail = p;
	if (node_table[index2].first == NULL)
	{
		node_table[index2].first = q;
	}
	else
	{
		node_table[index2].tail->next = q;
	}
	node_table[index2].tail = q;

	edge_number++;                          //图内边数+1
}

template<class T>
int graph<T>::find(string name)                //找到名为name的顶点，返回下标
{
	int index = 0;
	while (index<vertex_number&&node_table[index].name != name)
	{
		index++;
	}
	if (index < vertex_number)                 //如果该点存在返回下标 
	{
		return index;                            
	}
	else                                       //如果点不存在返回-1
	{
		return -1;
	}
}

template<class T>
int graph<T>::get_first_neighbor(int index)
{
	edge_of_adj<T>* p = node_table[index].first;
	if (p != NULL)              //若有第一个邻接点，则返回邻接点的位置
	{
		return p->index;
	}
	else return -1;             //若没有第一个邻接点，则返回-1
}

template<class T>
int graph<T>::get_next_neighbor(int index1, int index2)
{
	edge_of_adj<T>* p = node_table[index1].first;
	while (p->index != index2)
	{
		p = p->next;
	}

	p = p->next;
	if (p != NULL)              //若存在下一个邻接点，则返回下一个邻接点的位置
	{
		return p->index;
	}
	else return -1;             //不存在则返回-1
}

template<class T>
T graph<T>::get_key(int index1, int index2)
{
	//index1与index2是同一个点时
	if (index1 == index2)
	{
		return 0;               //点到自己的距离是0
	}

	//index1与index2不是同一个点时
	edge_of_adj<T>* p = node_table[index1].first;
	while (p!=NULL&&p->index != index2)  //循环到邻接点在index2为止
	{
		p = p->next;
	}
	if (p != NULL)
	{
		return p->key;           //两点之间相连时，返回两点间的距离
	}
	else return disconnection;         //两点之间没有边相连时，返回无穷大
}

template<class T>
void graph<T>::Prim(edge<T> min_span_tree[], string start_vertex)
{
	int start_index = find(start_vertex);     //起点的位置
	int vertex_number = get_vertex_number();  //图的顶点数
	T* low_cost = new T[vertex_number];       //起点到各个顶点的开销
	int* near_vertex = new int[vertex_number];//生成图外的顶点距生成图内最近的顶点的位置
	for (int i = 0; i < vertex_number; i++)
	{
		near_vertex[i] = start_index;         //初始化所有顶点到生成树内的最近位置是start_index
		low_cost[i] = get_key(i, start_index);//各顶点到起点的开销
	}
	near_vertex[start_index] = -1;            //起点已经在生成图内，所以最近位置为-1

	for (int i = 0; i < vertex_number - 1; i++) //最小生成树有n-1条边，所以循环n-1次
	{
		T min = disconnection;
		int the_index ;                       //记录距离生成图最近的顶点的位置
		for (int j = 0; j < vertex_number; j++)
		{
			//找到不在生成图内且距离更小的点
			if (near_vertex[j] != -1 && low_cost[j] < min)
			{
				min = low_cost[j];
				the_index = j;
			}
		}
		
		//还有点没有加入最小生成树，但是没有边与树内顶点相连了。说明无法成功生成最小生成树
		if (min == disconnection)
		{
			cout << "生成最小生成树失败！\n\n";
			return;
		}
		
		//得到距离最近的点后，向最小生成树内加入新边
		edge<T> new_edge;          //用来存储要加入生成图的边
		int index1 = near_vertex[the_index];
		int index2 = the_index;
		new_edge.node1 = node_table[index1].name;//边的一个顶点
		new_edge.node2 = node_table[index2].name;//边的另一个顶点
		new_edge.key = min;                      //边的权值
		min_span_tree[i] = new_edge;             //加入最小生成树

		//更新near_vertex的内容
		near_vertex[the_index] = -1;
		for (int k = 0; k < vertex_number; k++)
		{
			if (near_vertex[k] != -1 && get_key(the_index, k) < low_cost[k])
			{
				low_cost[k] = get_key(the_index, k);
				near_vertex[k] = the_index;
			}
		}
	}
	cout << "生成Prim最小生成树！\n\n";
}


/*****************************主函数**********************************/
int main()
{
	cout << "**             电网造价模拟系统              **\n"
		<< "===============================================\n"
		<< "**             A --- 创建电网顶点            **\n"
		<< "**             B --- 添加电网的边            **\n"
		<< "**             C --- 构造最小生成树          **\n"
		<< "**             D --- 显示最小生成树          **\n"
		<< "**             E --- 退出   程序             **\n"
		<< "===============================================\n\n";

	cout << "请选择操作：";
	char operation;
	cin >> operation;
	while (operation < 'A' || operation > 'E')
	{
		cin.ignore(100, '\n');           //清空输入流缓存区
		cout << "请输入选项范围内的操作：";
		cin >> operation;
	}

	int number = 0;                      //顶点个数
	string vertex_name;                  //顶点的名称
	string start_vertex;                 //生成树的起点
	graph<int> Graph;                    //创建图
	edge<int> Edge;                      //用来输入新边信息
	edge<int>* min_span_tree = NULL;     //最小生成树的边

	while (operation != 'E')
	{
		switch (operation)
		{
		case'A':                                         //输入所有顶点个数和顶点名称
			cout << "请输入顶点的个数：";
			cin >> number;
			while (number < 2)                           //图内的顶点数不能少于2，否则没有意义
			{
				cout << "图内至少两个点，请重新输入顶点个数：";
				cin >> number;
			}
			Graph.create(number);                        //根据顶点个数，确定图的大小

			min_span_tree = new edge<int>[number - 1];   //创建最小生成树边的数组
			cout << "请依次输入各点的名称：\n";
			for (int i = 0; i < number; i++)
			{
				cin >> vertex_name;
				Graph.insert_vertex(vertex_name, i);     //给各点附上名称和位置
			}

			cout << "\n";
			break;
		case'B':                                         //输入所有边的信息
			if (Graph.get_vertex_number() == 0)          //避免图内为空而出错
			{
				cout << "请先选择操作A输入顶点个数！\n\n";
				break;
			}

			cout << "请输入两个顶点及边（边的顶点输入‘*’用来结束边的输入）：";
			cin >> Edge;
			
			//当输入的边的顶点不存在时，重新输入
			while (Graph.find(Edge.node1) == -1 || Graph.find(Edge.node2) == -1)
			{
				//结束输入的标志
				if (Edge.node1 == "*" || Edge.node2 == "*")
				{
					cout << endl;
					break;
				}
				cout << "边的顶点不存在，请重新输入边的信息：";
				cin >> Edge;
			}

			while (Edge.node1 != "*" && Edge.node2 != "*")//*作为结束边的输入的标志
			{
				Graph.insert_edge(&Edge);
				cout << "请输入两个顶点及边（边的顶点输入‘*’用来结束边的输入）：";
				cin >> Edge;

				//当输入的边的顶点不存在时，重新输入
				while (Graph.find(Edge.node1) == -1 || Graph.find(Edge.node2) == -1)
				{
					//结束输入的标志
					if (Edge.node1 == "*" || Edge.node2 == "*")
					{
						cout << endl;
						break;
					}
					cout << "边的顶点不存在，请重新输入边的信息：";
					cin >> Edge;
				}
			}

			cout << "\n";
			break;
		case'C':                                         //选择起始顶点，开始生成最小生成树
			if (Graph.get_vertex_number() == 0)          //寻找最小生成树前不能为空图
			{
				cout << "请先选择操作A输入顶点个数！\n\n";
				break;
			}

			else if (Graph.get_edge_number() == 0)       //寻找最小生成树前不能只有点没有边
			{
				cout << "请先选择操作B输入边的信息！\n\n";
				break;
			}

			cout << "请输入起始顶点：";                    
			cin >> start_vertex;

			Graph.Prim(min_span_tree, start_vertex);     //创建Prim最小生成树

			break;
		case'D':                                         //输出最小生成树的边
			cout << "最小生成树的顶点及边为：\n\n";

			for (int i = 0; i < number - 1; i++)
			{
				cout << min_span_tree[i].node1 << "-<" << min_span_tree[i].key << ">->"
					<< min_span_tree[i].node2 << "        ";
			}
			cout << "\n\n";
			break;
		}

		cout << "请选择操作：";
		cin >> operation;
		while (operation < 'A' || operation > 'E')
		{
			cin.ignore(100, '\n');           //清空输入流缓存区
			cout << "请输入选项范围内的操作：";
			cin >> operation;
		}
		
	}
	cout << "Press any key to continue.";
}





