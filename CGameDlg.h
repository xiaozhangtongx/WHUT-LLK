#pragma once
#include "global.h"
#include "CGameControl.h"
#include "CHelpDialog.h"
#include "LLK.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//初始化背景
	void InitBackground();
	void InitElement();
	DECLARE_MESSAGE_MAP()
	CGameControl m_gameControl;
	CProgressCtrl m_GameProgress;
public:
	CDC m_dcMem;    //内存DC
	CDC m_dcElm;    //元素内存DC
	CDC m_dcMask;   //掩码内存DC
	CDC m_dcBG;				//背景DC
	CDC m_dcCache;			//掩盖游戏地图

	//int m_anMap[4][4];     //初始化游戏地图
	CPoint m_ptGameTop;		//起始点坐标
	CSize m_sizeElem;		//图片元素大小
	CRect m_rtGameRect;     //游戏区域的大小

	bool m_bFirstPoint;		//选中的图片是不是第一次选中的
	Vertex m_ptSelFirst;	//第一次选中的点
	Vertex m_ptSelSec;		//第二次选中的点
	bool m_bPause;	        //是否暂停 false 进行游戏中
	int timeCount;          //计时
	bool m_bPlaying;        //是否在玩游戏
	bool IS_RELAX;          //是否是休闲模式
	int level;              //游戏等级
	void UpdateMap();
	//void UpdateWindow();
	void DrawTipFrame(int nRow, int nCol);     //画框框
	void DrawTipLine(Vertex avPath[MAX_VERTEX_NUM], int nVexnum);		//绘制提示线
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedBtnStart();   // 开始按钮
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedBtnPrompt();   // 提示按钮 
	afx_msg void OnClickedBtnReset();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawGameTime();
	void JudgeWin(int timeCount);       //判断胜负
	afx_msg void OnClickedBtnStop();
	afx_msg void OnChangeEditTime();
	afx_msg void OnBnClickedBtnHtlp();
	afx_msg void OnBnClickedBtnSetting();
};



