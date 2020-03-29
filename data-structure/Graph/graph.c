#include "graph.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


//创建图（用已提供的矩阵）
Graph* create_example_graph()
{
	char vexs[] = {'A','B','C','D','E','F','G'};
	int matrix[][7] = {
		   /*A*//*B*//*C*//*D*//*E*//*F*//*G*/
	/*A*/{   0,  12, INF, INF, INF, INF,  14 },
	/*B*/{  12,	  0,  10, INF, INF,   7, INF },
	/*C*/{ INF,  10,   0,   3, INF,   6, INF },
	/*D*/{ INF, INF,   3,   0,   4, INF, INF },
	/*E*/{ INF, INF, INF,   4,   0,   2,   8 },
	/*F*/{ INF,   7,   6, INF,   2,   0,   9 },
	/*G*/{  14, INF, INF, INF,   8,   9,   0 },
	};
	int i,j;
	Graph* pG;

	pG = (Graph*)malloc(sizeof(Graph));
	if(pG != NULL) 
		memset(pG,0,sizeof(Graph));
	else
	{ 
		printf("create fail\n");
		return NULL;
	}

	//初始化顶点
	pG->vexnum = sizeof(vexs)/sizeof(vexs[0]);
	for(i=0; i<pG->vexnum; i++)
		pG->vexs[i] = vexs[i];

	//初始化边
	for(i=0; i<pG->vexnum; i++)
		for(j=0; j<pG->vexnum; j++)
			pG->matrix[i][j] = matrix[i][j];

	//统计边的数目
	for(i=0; i<pG->vexnum; i++)
	{
		for(j=0; j<pG->vexnum; j++)
		{
			if((i!=j)&&(pG->matrix[i][j]!=INF))
				pG->edgnum++;
		}
	}
	pG->edgnum /= 2;
	
	printf("vlen:%d\telen:%d\n",pG->vexnum,pG->edgnum);
	return pG;	
}


//获取图中的边
EData* get_edges(Graph G)
{
	int i,j;
	int index = 0;
	EData *edges;

	edges = (EData *)malloc(sizeof(EData)*G.edgnum);
	for(i=0; i<G.vexnum; i++)
	{
		for(j=i+1; j<G.vexnum; j++)
		{
			if(G.matrix[i][j] != INF)
			{
				edges[index].start = G.vexs[i];
				edges[index].end = G.vexs[j];
				edges[index].weight = G.matrix[i][j];
				index++;
			}
		}
	}
	return edges;
}

//对边按权值大小进行选择排序
void sort_edges(EData *edges, int elen)
{
	int i,j;
	EData tmp;
	for(i=0; i<elen; i++)
	{
		for(j=i+1; j<elen; j++)
		{
			if(edges[i].weight > edges[j].weight)
			{
				tmp = edges[i];
				edges[i] = edges[j];
				edges[j] = tmp;
			}
		}
	}
}
//返回ch顶点在matrix矩阵中的位置
static int get_position(Graph G, char ch)
{
	int i;
	for(i=0;i<G.vexnum;i++)
		if(G.vexs[i] == ch)	return i;
	return -1;
}
//获取i的根结点
int get_end(int vends[], int i)
{
	while(vends[i]!=0)//父结点不存在时跳出
		i = vends[i];//i为结点序号，vends[i]的值是其父结点序号
	return i;
}

void kruskal(Graph G)
{
	int i,m,n,p1,p2;
	int elen = G.edgnum;	
	int index = 0,weight_sum; //权值总和
	int vends[MAX] = {0};//保存父结点的序号
	EData rets[MAX];//结果数组，保存kruskal最小生成树的边
	EData *edges; //图对应的所有边
	
	edges = get_edges(G);
	sort_edges(edges, G.edgnum);	

	for(i=0; i<G.edgnum; i++)
	{
		p1 = get_position(G, edges[i].start);//第i条边的起点的序号
		p2 = get_position(G, edges[i].end);//第i条边的终点的序号

		//m,n分别表示两个结点所在生成树的根结点
		m = get_end(vends, p1);
		n = get_end(vends, p2);

		//m != n时，没有形成环路，将边添加到“已有最小生成树”
		if(m != n)
		{
			vends[m] = n;
			rets[index++] = edges[i];
		}
	}
	free(edges); //已获得最小生成树

	weight_sum = 0;
	for(i=0; i<index; i++)
		weight_sum += rets[i].weight;
	printf("kruskal = %d\n",weight_sum);//权值总和
	for(i=0; i<index; i++)
		printf("(%c,%c)",rets[i].start,rets[i].end);
	printf("\n");	

}

void main()
{
	Graph* pG = create_example_graph();
	kruskal(*pG);
}