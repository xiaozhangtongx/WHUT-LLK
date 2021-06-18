#pragma once
#include "global.h"
#include "CGameLogic.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	void StartGame(void);								//开始游戏函数
	int GetElement(int nRow, int nCol);					//获得某行某列的图片编号函数
	void SetFirstPoint(int nRow, int nCol);             //设置第一个点坐标
	void SetSecPoint(int nRow, int nCol);               //设置第二个点坐标
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum);          //连接判断函数
	int IsWin(int nTime);                                       // 判断是否赢
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum);  //帮助、提示方法
	void Reset(void);        // 实现重排功能
private:
	CGraph m_gragh;		//初始游戏地图4*4
	Vertex m_ptSelFst;	//第一次选中的点(x表示列)
	Vertex m_ptSelSec;		//第二次选中的点
};

