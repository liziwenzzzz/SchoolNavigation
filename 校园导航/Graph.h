#ifndef Graph_H
#define Graph_H

#include<iostream>
#include<limits.h>


template<class T>
class Graph
{
protected:
	int maxVertices;                             //图中最大顶点数
	int numEdges;                                //当前边数
	int numVertices;                             //当前顶点数
	CString load[32];                            //下标景点代号，内容景点
private:
	T* VerticesList; 			                 //顶点表
	int** Edge;				                     //邻接矩阵
	int* dist;                                   //辅助数组
	int* path;                                   //路径数组
	int first;                                   //起点
public:
	Graph(int sz = 100);                         //构造
	~Graph()
	{ 
		delete[]VerticesList; 
		delete[]dist;
		delete[]path; 
		for (int i = 0; i<maxVertices; i++)
		{
			delete[] Edge[i];
		}
		delete[] Edge;
	};
	T getValue(int i)                            //取位置为i的顶点中的值
	{
		return (i >= 0 && i < numVertices) ? VerticesList[i] :0;
	}
	int getWeight(int v1, int v2)                //取边(v1,v2)权值
	{
		return (v1 != -1 && v2 != -1) ? Edge[v1][v2] : 0;
	}
	int NumberOfVertices()const{ return numVertices; };
	int getVertexPos(const T vertex)              //给出顶点vertex在图中的位置
	{
		for (int i = 0; i < numVertices; i++)
		if (VerticesList[i]== vertex)
			return i;
		return -1;
	}
	bool insertVertex(const T& vertex);           //在图中插入一个顶点
	bool insertEdge(int v1, int v2, int weight);  //在图中插入一条边(v1,v2)
	void ShortestPath(int v);
	void getPath(int k, CDC*&dc, CPoint point);   //画线
	CString showPath(int end);                    //显示路径
};
//******************************************构造函数
template <class T>
Graph<T>::Graph(int sz) 
{
	maxVertices = sz;
	numVertices = 0;  
	numEdges = 0;
	VerticesList = new T[maxVertices];            //创建顶点表
	Edge = (int **) new int *[maxVertices];
	for (int i = 0; i < maxVertices; i++)
		Edge[i] = new int[maxVertices];           //邻接矩阵 
	for (int i = 0; i < maxVertices; i++)         //矩阵初始化
	for (int j = 0; j < maxVertices; j++)
		Edge[i][j] = (i == j) ? 0 : INT_MAX;
	dist = new int[maxVertices];
	path = new int[maxVertices];
	//***************************************景点
	for (int i = 0; i < 32; i++)
		load[i] = _T("");
	load[0] = _T("教二楼");
	load[3] = _T("研究生楼");
	load[31] = _T("西一门");
	load[6] = _T("映荷轩");
	load[7] = _T("学一食堂");
	load[8] = _T("学二食堂");
	load[9] = _T("公主楼");
	load[11] = _T("保卫部");
	load[12] = _T("大学生活动中心");
	load[14] = _T("学三食堂");
	load[15] = _T("弘毅堂");
	load[16] = _T("52栋");
	load[17] = _T("53栋");
	load[18] = _T("63栋");
	load[19] = _T("教三楼");
	load[21] = _T("主楼");
	load[23] = _T("基础楼");
	load[24] = _T("教一楼");
	load[27] = _T("图书馆");
	load[29] = _T("物探楼");
	load[30] = _T("水工楼");
}
//******************************************在图中插入一个顶点
template <class T>
bool Graph<T>::insertVertex(const T& vertex)
{
	if (numVertices == maxVertices) 
		return false;
	VerticesList[numVertices++] = vertex;
	return true;
}
//******************************************在图中插入一条边
template <class T>
bool Graph<T>::insertEdge(int v1, int v2, int weight)
{
	if (v1 > -1 && v1 < numVertices && v2 > -1 &&v2 < numVertices && Edge[v1][v2] == INT_MAX)
	{
		Edge[v1][v2] = Edge[v2][v1] = weight;
		numEdges++;
		return true;
	}
	else 
		return false;
}
//*******************************************最短路径算法
template <class T>
void Graph<T>::ShortestPath(int v)
{
    first = v;                      //终点标记为v
	int n = numVertices;
	bool* S = new bool[n]; 	  
	int w, min;
	for (int i = 0; i < n; i++)  
	{
		dist[i] = getWeight(v, i);
		S[i] = false;
		if (i != v && dist[i] < INT_MAX) 
			path[i] = v;
		else 
			path[i] = -1;
	}
	S[v] = true;  
	dist[v] = 0;   
	for (int i = 0; i < n - 1; i++)   
	{
		min = INT_MAX;  
		int u = v;
		for (int j = 0; j < n; j++)
		if (S[j]==false && dist[j] < min)
		{
			u = j;   
			min = dist[j];
		}
		S[u] = true;	            
		for (int k = 0; k < n; k++)
		{         
			w = getWeight(u, k);
			if (S[k]==false && w < INT_MAX &&dist[u] + w < dist[k])
			{   
				dist[k] = dist[u] + w;
				path[k] = u;     		
			}
		}
	}
}
//********************************************画线
template <class T>
void Graph<T>::getPath(int k, CDC*&dc, CPoint point)
{
	while (path[k] != first)
	{
		dc->Ellipse(getValue(k).x - 5 - point.x, getValue(k).y - 5 - point.y, getValue(k).x + 5 - point.x, getValue(k).y + 5 - point.y);
		dc->MoveTo(getValue(k).x - point.x, getValue(k).y - point.y);
		dc->LineTo(getValue(path[k]).x - point.x, getValue(path[k]).y - point.y);
		k = path[k];
	}
	dc->Ellipse(getValue(k).x - 5 - point.x, getValue(k).y - 5 - point.y, getValue(k).x + 5 - point.x, getValue(k).y + 5 - point.y);
	dc->MoveTo(getValue(k).x - point.x, getValue(k).y - point.y);
	dc->LineTo(getValue(path[k]).x - point.x, getValue(path[k]).y - point.y);
	dc->Ellipse(getValue(path[k]).x - 5 - point.x, getValue(path[k]).y - 5 - point.y, getValue(path[k]).x + 5 - point.x, getValue(path[k]).y + 5 - point.y);
}

//********************************************显示路径
template <class T>
CString Graph<T>::showPath(int end)
{
	CString sum = _T("");
	CString len;
	len.Format(_T("总路线长： %d"),dist[end]);
	CString line = _T("\r\n");
	CString a1 = _T("起点：");
	CString a2 = _T("终点：");
	sum = len + line + a1;
	//***************************路线要倒过来输出
	CString temp[32] = {_T("")};
	int i = 0;
	for (; path[end] != first;i++,end=path[end])
		temp[i] = load[end];
	temp[i++] = load[end];
    temp[i] = load[path[end]];     //别忘了最后一个景点
	sum += temp[i];                //起点
	sum += line;                   //换行
	i--;
	for (; i>0;i--)
	{
		if (temp[i] != _T(""))
			sum = sum + temp[i] + line;
	}
	sum = sum + a2 + temp[0];
	return sum;
}


#endif