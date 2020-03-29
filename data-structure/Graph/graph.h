#ifndef GRAPH_H
#define GRAPH_H

#define MAX 20	//矩阵容量
#define INF (-1)
#define isLetter(a) ((((a)>='a')&&((a)<='z'))||(((a)>='A')&&((a)<='Z')))
//邻接矩阵
typedef struct _graph
{
	char vexs[MAX];	//顶点集合
	int vexnum;		//顶点数
	int edgnum;		//边数
	int matrix[MAX][MAX]; //邻接矩阵	
}Graph,*pGraph;

//边的结构体
typedef struct _EdgeData
{
	char start;	//边的起点
	char end;	//边的终点
	int weight;	//边的权重
}EData;


#endif