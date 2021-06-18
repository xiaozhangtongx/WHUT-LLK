#include "pch.h"
#include "CGameControl.h"

CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

//��ʼ��Ϸ����
void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_gragh);
}

//���ĳ��ĳ�е�ͼƬ��ź���
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_gragh.GetVertex(nRow * MAX_COL+ nCol);
}

//���õ�һ��������
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFst.row = nRow;
	m_ptSelFst.col = nCol;
}

//���õڶ���������
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

bool CGameControl::Link(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum)
{
	//�ж�ѡ�еĵ��Ƿ�Ϊͬһ��ͼƬ����Ϊͬһ��ͼƬ��������ͨ
	if (m_ptSelFst.row == m_ptSelSec.row && m_ptSelFst.col == m_ptSelSec.col)
	{
		return false;
	}

	//�ж�ͼƬ�Ƿ���ͬ�������ͬ������ͨ
	int	nInfo1 = m_gragh.GetVertex(m_ptSelFst.row * MAX_COL+ m_ptSelFst.col);
	int	nInfo2 = m_gragh.GetVertex(m_ptSelSec.row * MAX_COL + m_ptSelSec.col);

	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
	{
		return false;
	}
	//�ж��Ƿ������ͨ
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_gragh, m_ptSelFst, m_ptSelSec) == true)
	{
		//����
		gameLogic.Clear(m_gragh, m_ptSelFst, m_ptSelSec);
		//����·������
		nVexnum = gameLogic.GetVexPath(avPath);
		return true;
	}

	return false;
}

// �ж��Ƿ���Ӯ
int CGameControl::IsWin(int nTime)
{
	//return GAME_LOSE;
	//�����߼�������
	CGameLogic logic;

	//�ж���Ϸʱ��
	if (nTime <= 0)
	{
		//���ͼ
		m_gragh.ClearGraph();
		return GAME_LOSE;
	}

	//�ж��Ƿ�ͼ�����е�Ϊ��
	if (logic.IsBlank(m_gragh))
	{
		//���ͼ
		m_gragh.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

//��������ʾ����
bool CGameControl::Help(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum)
{
	CGameLogic logic;
	//�ж��Ƿ�Ϊ��
	if (logic.IsBlank(m_gragh) == true)
	{
		return false;
	}
	//����һ����Ч����ʾ·��
	if (logic.SearchValidPath(m_gragh))
	{
		//����·������
		nVexnum = logic.GetVexPath(avPath);
		return true;
	}
	return false;
}

//ʵ�����Ź���
void CGameControl::Reset(void)
{
	//����ͼ�ж���
	CGameLogic logic;
	logic.ResetGraph(m_gragh);
}