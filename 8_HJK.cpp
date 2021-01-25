#include"8_1952211_�ƽ���.h"
/***************************graph(ͼ)�ĳ�Ա�����Ķ���***************************************/
template<class T>
void graph<T>::insert_edge(edge<T>* new_edge)//����±ߣ������ڽӱ�
{
	int index1 = find(new_edge->node1);    //�ҵ��±ߵ������������ڵ�λ��
	int index2 = find(new_edge->node2);

	edge_of_adj<T>* p = new edge_of_adj<T>;//�����µı߽��p��q
	edge_of_adj<T>* q = new edge_of_adj<T>;
	p->index = index2;
	p->key = new_edge->key;
	q->index = index1;
	q->key = new_edge->key;

	if (node_table[index1].first == NULL)   //�ֱ��µı߽��p��q�����ڽӱ�
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

	edge_number++;                          //ͼ�ڱ���+1
}

template<class T>
int graph<T>::find(string name)                //�ҵ���Ϊname�Ķ��㣬�����±�
{
	int index = 0;
	while (index<vertex_number&&node_table[index].name != name)
	{
		index++;
	}
	if (index < vertex_number)                 //����õ���ڷ����±� 
	{
		return index;                            
	}
	else                                       //����㲻���ڷ���-1
	{
		return -1;
	}
}

template<class T>
int graph<T>::get_first_neighbor(int index)
{
	edge_of_adj<T>* p = node_table[index].first;
	if (p != NULL)              //���е�һ���ڽӵ㣬�򷵻��ڽӵ��λ��
	{
		return p->index;
	}
	else return -1;             //��û�е�һ���ڽӵ㣬�򷵻�-1
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
	if (p != NULL)              //��������һ���ڽӵ㣬�򷵻���һ���ڽӵ��λ��
	{
		return p->index;
	}
	else return -1;             //�������򷵻�-1
}

template<class T>
T graph<T>::get_key(int index1, int index2)
{
	//index1��index2��ͬһ����ʱ
	if (index1 == index2)
	{
		return 0;               //�㵽�Լ��ľ�����0
	}

	//index1��index2����ͬһ����ʱ
	edge_of_adj<T>* p = node_table[index1].first;
	while (p!=NULL&&p->index != index2)  //ѭ�����ڽӵ���index2Ϊֹ
	{
		p = p->next;
	}
	if (p != NULL)
	{
		return p->key;           //����֮������ʱ�����������ľ���
	}
	else return disconnection;         //����֮��û�б�����ʱ�����������
}

template<class T>
void graph<T>::Prim(edge<T> min_span_tree[], string start_vertex)
{
	int start_index = find(start_vertex);     //����λ��
	int vertex_number = get_vertex_number();  //ͼ�Ķ�����
	T* low_cost = new T[vertex_number];       //��㵽��������Ŀ���
	int* near_vertex = new int[vertex_number];//����ͼ��Ķ��������ͼ������Ķ����λ��
	for (int i = 0; i < vertex_number; i++)
	{
		near_vertex[i] = start_index;         //��ʼ�����ж��㵽�������ڵ����λ����start_index
		low_cost[i] = get_key(i, start_index);//�����㵽���Ŀ���
	}
	near_vertex[start_index] = -1;            //����Ѿ�������ͼ�ڣ��������λ��Ϊ-1

	for (int i = 0; i < vertex_number - 1; i++) //��С��������n-1���ߣ�����ѭ��n-1��
	{
		T min = disconnection;
		int the_index ;                       //��¼��������ͼ����Ķ����λ��
		for (int j = 0; j < vertex_number; j++)
		{
			//�ҵ���������ͼ���Ҿ����С�ĵ�
			if (near_vertex[j] != -1 && low_cost[j] < min)
			{
				min = low_cost[j];
				the_index = j;
			}
		}
		
		//���е�û�м�����С������������û�б������ڶ��������ˡ�˵���޷��ɹ�������С������
		if (min == disconnection)
		{
			cout << "������С������ʧ�ܣ�\n\n";
			return;
		}
		
		//�õ���������ĵ������С�������ڼ����±�
		edge<T> new_edge;          //�����洢Ҫ��������ͼ�ı�
		int index1 = near_vertex[the_index];
		int index2 = the_index;
		new_edge.node1 = node_table[index1].name;//�ߵ�һ������
		new_edge.node2 = node_table[index2].name;//�ߵ���һ������
		new_edge.key = min;                      //�ߵ�Ȩֵ
		min_span_tree[i] = new_edge;             //������С������

		//����near_vertex������
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
	cout << "����Prim��С��������\n\n";
}


/*****************************������**********************************/
int main()
{
	cout << "**             �������ģ��ϵͳ              **\n"
		<< "===============================================\n"
		<< "**             A --- ������������            **\n"
		<< "**             B --- ��ӵ����ı�            **\n"
		<< "**             C --- ������С������          **\n"
		<< "**             D --- ��ʾ��С������          **\n"
		<< "**             E --- �˳�   ����             **\n"
		<< "===============================================\n\n";

	cout << "��ѡ�������";
	char operation;
	cin >> operation;
	while (operation < 'A' || operation > 'E')
	{
		cin.ignore(100, '\n');           //���������������
		cout << "������ѡ�Χ�ڵĲ�����";
		cin >> operation;
	}

	int number = 0;                      //�������
	string vertex_name;                  //���������
	string start_vertex;                 //�����������
	graph<int> Graph;                    //����ͼ
	edge<int> Edge;                      //���������±���Ϣ
	edge<int>* min_span_tree = NULL;     //��С�������ı�

	while (operation != 'E')
	{
		switch (operation)
		{
		case'A':                                         //�������ж�������Ͷ�������
			cout << "�����붥��ĸ�����";
			cin >> number;
			while (number < 2)                           //ͼ�ڵĶ�������������2������û������
			{
				cout << "ͼ�����������㣬���������붥�������";
				cin >> number;
			}
			Graph.create(number);                        //���ݶ��������ȷ��ͼ�Ĵ�С

			min_span_tree = new edge<int>[number - 1];   //������С�������ߵ�����
			cout << "�����������������ƣ�\n";
			for (int i = 0; i < number; i++)
			{
				cin >> vertex_name;
				Graph.insert_vertex(vertex_name, i);     //�����㸽�����ƺ�λ��
			}

			cout << "\n";
			break;
		case'B':                                         //�������бߵ���Ϣ
			if (Graph.get_vertex_number() == 0)          //����ͼ��Ϊ�ն�����
			{
				cout << "����ѡ�����A���붥�������\n\n";
				break;
			}

			cout << "�������������㼰�ߣ��ߵĶ������롮*�����������ߵ����룩��";
			cin >> Edge;
			
			//������ıߵĶ��㲻����ʱ����������
			while (Graph.find(Edge.node1) == -1 || Graph.find(Edge.node2) == -1)
			{
				//��������ı�־
				if (Edge.node1 == "*" || Edge.node2 == "*")
				{
					cout << endl;
					break;
				}
				cout << "�ߵĶ��㲻���ڣ�����������ߵ���Ϣ��";
				cin >> Edge;
			}

			while (Edge.node1 != "*" && Edge.node2 != "*")//*��Ϊ�����ߵ�����ı�־
			{
				Graph.insert_edge(&Edge);
				cout << "�������������㼰�ߣ��ߵĶ������롮*�����������ߵ����룩��";
				cin >> Edge;

				//������ıߵĶ��㲻����ʱ����������
				while (Graph.find(Edge.node1) == -1 || Graph.find(Edge.node2) == -1)
				{
					//��������ı�־
					if (Edge.node1 == "*" || Edge.node2 == "*")
					{
						cout << endl;
						break;
					}
					cout << "�ߵĶ��㲻���ڣ�����������ߵ���Ϣ��";
					cin >> Edge;
				}
			}

			cout << "\n";
			break;
		case'C':                                         //ѡ����ʼ���㣬��ʼ������С������
			if (Graph.get_vertex_number() == 0)          //Ѱ����С������ǰ����Ϊ��ͼ
			{
				cout << "����ѡ�����A���붥�������\n\n";
				break;
			}

			else if (Graph.get_edge_number() == 0)       //Ѱ����С������ǰ����ֻ�е�û�б�
			{
				cout << "����ѡ�����B����ߵ���Ϣ��\n\n";
				break;
			}

			cout << "��������ʼ���㣺";                    
			cin >> start_vertex;

			Graph.Prim(min_span_tree, start_vertex);     //����Prim��С������

			break;
		case'D':                                         //�����С�������ı�
			cout << "��С�������Ķ��㼰��Ϊ��\n\n";

			for (int i = 0; i < number - 1; i++)
			{
				cout << min_span_tree[i].node1 << "-<" << min_span_tree[i].key << ">->"
					<< min_span_tree[i].node2 << "        ";
			}
			cout << "\n\n";
			break;
		}

		cout << "��ѡ�������";
		cin >> operation;
		while (operation < 'A' || operation > 'E')
		{
			cin.ignore(100, '\n');           //���������������
			cout << "������ѡ�Χ�ڵĲ�����";
			cin >> operation;
		}
		
	}
	cout << "Press any key to continue.";
}





