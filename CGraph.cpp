#include "pch.h"
#include "CGraph.h"
CGraph::CGraph()
{
	InitGraph();   //初始化图
}

CGraph::~CGraph()
{
}
//初始化图
void CGraph::InitGraph()
{
	//初始化顶点与边信息
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		//初始化顶点
		m_Vertices[i] = -1;
	}

	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			//初始化边
			m_AdjMatrix[i][j] = false;
		}
	}
}

//添加顶点，并获得顶点个数
int CGraph::AddVertex(int nInfo)
{
	// TODO: 在此处添加实现代码.
	//如果超过就不添加
	if (m_nVexnum >= MAX_VERTEX_NUM) {
		return 0;
	}
	m_Vertices[m_nVexnum] = nInfo;
	m_nVexnum++;
	return m_nVexnum;
}

//添加边
void CGraph::AddArc(int nIndex1, int nIndex2)
{
	m_AdjMatrix[nIndex1][nIndex2] = true;
	m_AdjMatrix[nIndex2][nIndex1] = true;
}

//从顶点数组中取出相应的顶点
int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

//获得两个顶点的弧信息
bool CGraph::GetArc(int nV1Index, int nV2Index)
{
	return m_AdjMatrix[nV1Index][nV2Index];
}

//将要消去的顶点的图设置为BLANK（-1）
void CGraph::UpdateVertex(int nIndex, int info)
{
	m_Vertices[nIndex] = info;
}

//获取图中顶点的个数
int CGraph::GetVexnum()
{
	return m_nVexnum;
}

void CGraph::ClearGraph()
{
	// TODO: 在此处添加实现代码.
	InitGraph();
}

//调换两个点的位置
void CGraph::ChangeVerex(int nIndex1, int nIndex2)
{
	int Temp = m_Vertices[nIndex1];
	m_Vertices[nIndex1] = m_Vertices[nIndex2];
	m_Vertices[nIndex2] = Temp;
}