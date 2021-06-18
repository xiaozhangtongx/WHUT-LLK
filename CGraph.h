#pragma once
#include"global.h"
// ͼ����
class CGraph
{
public:
	CGraph(void);
	~CGraph(void); 
	void InitGraph();		//��ʼ��ͼ	
	int AddVertex(int nInfo);//��Ӷ��㣬����ö������
	void AddArc(int nIndex1, int nIndex2);//������ɱ�
	int GetVertex(int nIndex);//��ȡ����������
	bool GetArc(int nV1Index, int nV2Index);//�����������ı���Ϣ
	void UpdateVertex(int nIndex, int info);//���¶���,��ͼ����������������ΪNIndex�Ķ����ֵ����Ϊinfo
	int GetVexnum();   //��ȡͼ�ж���ĸ���
	typedef int Vertices[MAX_VERTEX_NUM];	//������������
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//����������  ����

protected:
	Vertices m_Vertices;					//��������  һλ���飬������������Ϸ��ͼ�еĶ���
	int m_nVexnum;		//������
	AdjMatrix m_AdjMatrix;					//��ϵ����  ��λ���飬������������Ϸ�еĶ���ı�
	int m_nArcnum;		//����
public:
	// ����ͼ�ṹ
	void ClearGraph();
	// �����������λ��
	void ChangeVerex(int nIndex1, int nIndex2);
};

