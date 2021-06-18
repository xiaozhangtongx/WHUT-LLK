
// LLKDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "afxdialogex.h"
#include"CGameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CSeTTing.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLLKDlg 对话框



CLLKDlg::CLLKDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LLK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BASIC, &CLLKDlg::OnClickedBtnBasic)
	ON_BN_CLICKED(IDC_BTN_HELP, &CLLKDlg::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_RELAX, &CLLKDlg::OnBnClickedBtnRelax)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CLLKDlg::OnBnClickedBtnSetting)
END_MESSAGE_MAP()


// CLLKDlg 消息处理程序

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	InitBackground();

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLLKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//创建CPaintDC对象
		CPaintDC dc(this);

		//BitBlt()将位图拷贝到视频内存中，进行显示
		dc.BitBlt(0, 0, 800, 600, &m_dcMen, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLLKDlg::InitBackground()
{
	//加载位图
	CBitmap bmpMain;
	bmpMain.LoadBitmapA(IDB_MAIN_BG);

	//创建一个兼容DC
	CClientDC dc(this);
	m_dcMen.CreateCompatibleDC(&dc);

	//将位图选入DC
	m_dcMen.SelectObject(&bmpMain);
	/* 
	//调整窗口的大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);    //获取窗口的大小
	this->GetClientRect(rtClient);     //获取客户端的大小
	
	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	//设置窗口的大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight); 
*/
}



void CLLKDlg::OnClickedBtnBasic()
{
	this->ShowWindow(SW_HIDE);
	// TODO: 在此添加控件通知处理程序代码
	CGameDlg dlg;
	dlg.IS_RELAX = false;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnBnClickedBtnHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	CHelpDialog dlg;
	dlg.DoModal();
}

// 休闲模式
void CLLKDlg::OnBnClickedBtnRelax()
{
	this->ShowWindow(SW_HIDE);
	// TODO: 在此添加控件通知处理程序代码
	CGameDlg dlg;
	//dlg.SetWindowText(L"欢乐连连看");
	dlg.IS_RELAX = true;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnBnClickedBtnSetting()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	// TODO: 在此添加控件通知处理程序代码
	CSettingDlg dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}
