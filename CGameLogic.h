#pragma once
#include "global.h"
#include "CGraph.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();
	//初始化游戏地图
	void InitMap(CGraph& graph);
	void InitMap1();
	//生成图的边的数组，更新边
	void UpdateArc(CGraph& graph, int nRow, int nCol);
	//连接判断函数
	bool IsLink(CGraph& graph, Vertex v1, Vertex v2);
	//消子函数
	void Clear(CGraph& graph, Vertex v1, Vertex v2);
	//判断选择的两个顶点是否联通
	bool SearchPath(CGraph& graph, int nV0, int nV1);
	//判断顶点是否已在路径中存在
	bool IsExsit(int nVi);
	//判断拐点的有效性
	bool IsCornor(void);
	//添加一个路径顶点
	void PushVertex(int v);
	//取出一个路径顶点
	void PopVertex();
	//得到路径，返回的是顶点数
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]);
	//判断是否还有剩余的
	bool IsBlank(CGraph& graph);
	//提示算法，
	bool SearchValidPath(CGraph& graph);
	//实现图结构的重排
	void ResetGraph(CGraph& graph);
protected:
	Vertex m_avPath[MAX_VERTEX_NUM];    //保存连接路径的起始点、拐点、终点
	int m_anPath[MAX_VERTEX_NUM];      //保存在进行连接判断时所经过的顶点
	int m_nCorner;         //保存路径中的拐点数
	int m_nVexNum;         //表示顶点数
	int m_anMap[4][4];		//初始游戏地图4*4
};

