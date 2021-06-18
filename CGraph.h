#pragma once
#include"global.h"
// 图数据
class CGraph
{
public:
	CGraph(void);
	~CGraph(void); 
	void InitGraph();		//初始化图	
	int AddVertex(int nInfo);//添加顶点，并获得顶点个数
	void AddArc(int nIndex1, int nIndex2);//添加生成边
	int GetVertex(int nIndex);//获取顶点索引号
	bool GetArc(int nV1Index, int nV2Index);//获得两个顶点的边信息
	void UpdateVertex(int nIndex, int info);//更新顶点,将图顶点数组中索引号为NIndex的顶点的值更新为info
	int GetVexnum();   //获取图中顶点的个数
	typedef int Vertices[MAX_VERTEX_NUM];	//顶点数据类型
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//边数据类型  矩阵

protected:
	Vertices m_Vertices;					//顶点数组  一位数组，保存连连看游戏地图中的顶点
	int m_nVexnum;		//顶点数
	AdjMatrix m_AdjMatrix;					//关系矩阵  二位数组，保存连连看游戏中的顶点的边
	int m_nArcnum;		//边数
public:
	// 清理图结构
	void ClearGraph();
	// 调换两个点的位置
	void ChangeVerex(int nIndex1, int nIndex2);
};

