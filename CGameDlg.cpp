﻿// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include "LLKDlg.h"
#include "CSeTTing.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//初始化起始点坐标
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	//初始化图片元素大小
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;

	//初始化图标选中状态表示第一次选中 
	m_bFirstPoint = true;
	m_bPlaying = false;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_PROMPT, &CGameDlg::OnClickedBtnPrompt)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnClickedBtnReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_STOP, &CGameDlg::OnClickedBtnStop)
	ON_EN_CHANGE(IDC_EDIT_TIME, &CGameDlg::OnChangeEditTime)
	ON_BN_CLICKED(IDC_BTN_HTLP, &CGameDlg::OnBnClickedBtnHtlp)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CGameDlg::OnBnClickedBtnSetting)
END_MESSAGE_MAP()

// CGameDlg 消息处理程序

void CGameDlg::InitBackground() 
{
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_b0g.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//获得当前对话框的视频内容
	CClientDC dc(this);

	//创建与视频内容兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcBG.SelectObject(bmp);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	//hu绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	//设置窗口大小
	//UpdateWindow();
}

//调整窗口大小
/*void CGameDlg::UpdateWindow()
{

	// TODO: 在此处添加实现代码.
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);		//获得窗口大小
	this->GetWindowRect(rtClient);	//获得客户区大小
									//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Width() - rtClient.Width();
	//设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();
}*/

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	if (IS_RELAX == true) {
		CString title;
		title.Format("%s", "欢乐连连看——休闲模式");//在标题栏动态显示Id的值
		this->SetWindowText(title);
	}
	if (level == 1) {
		CString title;
		title.Format("%s", "基本模式——简单");//在标题栏动态显示Id的值
		this->SetWindowText(title);
	}
	if (level == 2) {
		CString title;
		title.Format("%s", "基本模式——一般");//在标题栏动态显示Id的值
		this->SetWindowText(title);
	}
	if (level == 3) {
		CString title;
		title.Format("%s", "基本模式——困难");//在标题栏动态显示Id的值
		this->SetWindowText(title);
	}
	InitBackground();
	InitElement();
	this->GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_BTN_RESET)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_BTN_RANK)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_BTN_SETTING)->EnableWindow(TRUE);
	//设置进度条隐藏和剩余时间控件
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_EDIT_TIME)->ShowWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

void CGameDlg::InitElement() {
	CClientDC dc(this);
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcElm.CreateCompatibleDC(&dc);

	m_dcElm.SelectObject(hBmpBG);

	//掩码图加载
	HANDLE Maskbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcMask.CreateCompatibleDC(&dc);

	m_dcMask.SelectObject(Maskbmp);
	//加载掩盖图片
	//加载BMP图片资源
	HANDLE hCache = ::LoadImage(NULL, _T("theme\\picture\\fruit_b0g.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcCache.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcCache.SelectObject(hCache);

}

void CGameDlg::OnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	this->GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_BTN_RESET)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_BTN_RANK)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_BTN_SETTING)->EnableWindow(FALSE);
	//暂停时不响应
	if (m_bPause == true) return;
	m_gameControl.StartGame();
	//绘制游戏界面
	UpdateMap();
	//更新窗口
	Invalidate(FALSE);
	//判断是否正在玩游戏
	m_bPlaying = true;
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(false);
	if (level == 1) {
		//初始时间是500
		timeCount = 500;
		//初始化进度条
		m_GameProgress.SetRange(0, 100 * 5);    //初始范围
		m_GameProgress.SetStep(-1);            //初始步数值
		m_GameProgress.SetPos(100 * 5);         //设置初始值
	}
	else if (level == 2) {
		//初始时间是100
		timeCount = 100;
		//初始化进度条
		m_GameProgress.SetRange(0, 20 * 5);    //初始范围
		m_GameProgress.SetStep(-1);            //初始步数值
		m_GameProgress.SetPos(20 * 5);         //设置初始值
	}
	else if (level == 3) {
		//初始时间是50
		timeCount = 50;
		//初始化进度条
		m_GameProgress.SetRange(0, 10 * 5);    //初始范围
		m_GameProgress.SetStep(-1);            //初始步数值
		m_GameProgress.SetPos(10 * 5);         //设置初始值
	}
	else {
		//初始时间是300
		timeCount = 300;
		//初始化进度条
		m_GameProgress.SetRange(0, 60 * 5);    //初始范围
		m_GameProgress.SetStep(-1);            //初始步数值
		m_GameProgress.SetPos(60 * 5);         //设置初始值
	}
	//启动定时器
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
	//设置进度条隐藏和剩余时间控件
	if (IS_RELAX==false) {
		this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(TRUE);
		this->GetDlgItem(IDC_EDIT_TIME)->ShowWindow(TRUE);
	}
}

void CGameDlg::UpdateMap()
{
	// TODO: 在此处添加实现代码.

	//计算图片的顶点坐标与图片大小
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	//加载背景图片
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			//m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElm, 0, m_anMap[i][j] * nElemH, SRCCOPY);
			int nInfo = m_gameControl.GetElement(i, j);       //当前元素图片的数值
			if (nInfo == BLANK)  continue;
			//将背景与掩码相或，边保留
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nInfo * nElemH, SRCPAINT);
			//将元素图片相与，边保留，图像区域为元素图片
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElm, 0, nInfo * nElemH, SRCAND);

		}
	}

}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	//行号
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	//列号
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nRow > MAX_ROW-1 || nCol > MAX_COL-1) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstPoint) {
		//绘制框框
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	//第二个点
	else {
		//绘制框框
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecPoint(nRow, nCol);
		Vertex avPath[MAX_VERTEX_NUM];     //获得路径
		int nVexnum = 0;      //顶点个数
		//判断是否是相同图片
		if (m_gameControl.Link(avPath, nVexnum)) {
			//画提示线
			DrawTipLine(avPath, nVexnum);
			// m_anMap[m_ptSelFirst.row][m_ptSelFirst.col] = -1;
			// m_anMap[m_ptSelSec.row][m_ptSelSec.col] = -1;
			UpdateMap();
		}
		Sleep(200);    //延迟
		InvalidateRect(m_rtGameRect, FALSE); //局部矩形更新
		//判断胜负
		//JudgeWin(timeCount);
        /*if (m_gameControl.IsWin()) {
			MessageBox(_T("\t获胜！\n你太棒了！"));
			this->GetDlgItem(IDC_BTN_START)->EnableWindow(true);
			m_bPlaying = false;
			return;
		}*/
	}
	m_bFirstPoint = !m_bFirstPoint; //赋反值
	CDialogEx::OnLButtonUp(nFlags, point);
}

//绘制矩形提示框
void CGameDlg::DrawTipFrame(int nRow, int nCol) {
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

//判断是否连接
/*bool CGameDlg::IsLink()
{
	if (m_anMap[m_ptSelFirst.row][m_ptSelFirst.col] == m_anMap[m_ptSelSec.row][m_ptSelSec.col]) {
		return true;
	}
	return false;
}*/

//绘制提示线
void CGameDlg::DrawTipLine(Vertex avPath[MAX_VERTEX_NUM], int nVexnum)
{
	//获取DC
	CClientDC dc(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	//绘制连接线
	for (int i = 0; i < nVexnum - 1; i++)
	{
		dc.LineTo(m_ptGameTop.x + avPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}

// 提示功能
void CGameDlg::OnClickedBtnPrompt()
{
	// TODO: 在此添加控件通知处理程序代码
	//如果没有进行游戏，则返回
	if (m_bPlaying == false)
		return;
	//如果能够连通，绘制提示框和连接线并更新游戏地图
	Vertex avPath[MAX_VERTEX_NUM];     //获得路径
	int nVexnum = 0;      //顶点个数
	if (m_gameControl.Help(avPath, nVexnum))
	{
		//画第一个点的提示框
		DrawTipFrame(avPath[0].row, avPath[0].col);
		//画第一个点的提示框
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);
		//画提示线
		DrawTipLine(avPath, nVexnum);
		Sleep(1000);    //延迟
		UpdateMap();	//更新地图
		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
	}
	//为了使用第二个提示框可以看到，暂停200ms后，再刷新界面
}

// 重置界面
void CGameDlg::OnClickedBtnReset()
{
	// TODO: 在此添加控件通知处理程序代码
	//调用CGameControl：：ResetGraph();
	m_gameControl.Reset();
	//更新地图，调用UpdateMap(),更新界面显示
	UpdateMap();
	//通知界面重绘
	InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
}

// 计时器
void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//设置进度条的位置之前，需要判断计时器的编号是否是当前的计时器
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying && m_bPause == false)
	{
		//游戏时间减一秒
		if (timeCount > -1)
		{
			CString str;
			str.Format(_T("%d"), timeCount);
			SetDlgItemText(IDC_EDIT_TIME, str);
			UpdateData(false);
			--timeCount;
			JudgeWin(timeCount);
			m_GameProgress.StepIt();
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::DrawGameTime()
{
	// TODO: 在此处添加实现代码.

}


//判断胜负
void CGameDlg::JudgeWin(int timeCount)
{
	//游戏胜负判断
	int bGameStatus = m_gameControl.IsWin(timeCount);
	//判断是否继续游戏
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		//将游戏标识改为false
		m_bPlaying = false;
		//关闭定时器
		KillTimer(PLAY_TIMER_ID);
		//提示获胜
		CString strTitle;
		this->GetWindowTextA(strTitle);
		if (bGameStatus == GAME_SUCCESS)
		{
			MessageBox(_T("获胜！"), strTitle);
			this->GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
			this->GetDlgItem(IDC_BTN_RESET)->EnableWindow(FALSE);
			this->GetDlgItem(IDC_BTN_RANK)->EnableWindow(FALSE);
			this->ShowWindow(SW_HIDE);
			CLLKDlg dlg;
			dlg.DoModal();
		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("很遗憾，时间到了！"), strTitle);
			this->GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
			this->GetDlgItem(IDC_BTN_RESET)->EnableWindow(FALSE);
			this->GetDlgItem(IDC_BTN_RANK)->EnableWindow(FALSE);
			this->ShowWindow(SW_HIDE);
			CLLKDlg dlg;
			dlg.DoModal();
		}
		//还原开始游戏按钮，使用按钮可以点击
		this->GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	}

}

void CGameDlg::OnClickedBtnStop()
{
	// TODO: 在此添加控件通知处理程序代码
	//获得当前对话框的视频内容
	CClientDC dc(this);
	//游戏没在进行时，直接返回
	if (m_bPlaying == false)
		return;
	//如果游戏没有暂停
	if (m_bPause == false)
	{
		// 绘制背景到内存DC中
		m_dcMem.BitBlt(MAP_LETF, MAP_TOP, 640, 400, &m_dcCache, 0, 0, SRCCOPY);
		GetDlgItem(IDC_BTN_PROMPT)->EnableWindow(0);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(0);
		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
		this->GetDlgItem(IDC_BTN_STOP)->SetWindowTextA(_T("继续游戏"));
	}
	//如果游戏暂停
	if (m_bPause == true)
	{
		UpdateMap();
		GetDlgItem(IDC_BTN_PROMPT)->EnableWindow(1);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(1);
		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
		this->GetDlgItem(IDC_BTN_STOP)->SetWindowTextA(_T("暂停游戏"));
	}
	m_bPause = !m_bPause;
}


void CGameDlg::OnChangeEditTime()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CGameDlg::OnBnClickedBtnHtlp()
{
	// TODO: 在此添加控件通知处理程序代码
	CHelpDialog dlg;
	dlg.DoModal();
}


// 设计按钮
void CGameDlg::OnBnClickedBtnSetting()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	CSettingDlg dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}
