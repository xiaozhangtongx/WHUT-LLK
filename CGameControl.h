#pragma once
#include "global.h"
#include "CGameLogic.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	void StartGame(void);								//��ʼ��Ϸ����
	int GetElement(int nRow, int nCol);					//���ĳ��ĳ�е�ͼƬ��ź���
	void SetFirstPoint(int nRow, int nCol);             //���õ�һ��������
	void SetSecPoint(int nRow, int nCol);               //���õڶ���������
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum);          //�����жϺ���
	int IsWin(int nTime);                                       // �ж��Ƿ�Ӯ
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum);  //��������ʾ����
	void Reset(void);        // ʵ�����Ź���
private:
	CGraph m_gragh;		//��ʼ��Ϸ��ͼ4*4
	Vertex m_ptSelFst;	//��һ��ѡ�еĵ�(x��ʾ��)
	Vertex m_ptSelSec;		//�ڶ���ѡ�еĵ�
};

