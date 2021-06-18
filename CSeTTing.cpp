// CSeTTing.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "CSeTTing.h"
#include "afxdialogex.h"
#include "global.h"
#include "CGameDlg.h"
#include "LLKDlg.h"


// CSeTTing 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_EASY, &CSettingDlg::OnBnClickedBtnEasy)
	ON_BN_CLICKED(IDC_BTN_COMMON, &CSettingDlg::OnBnClickedBtnCommon)
	ON_BN_CLICKED(IDC_BTN_DIFFICULT, &CSettingDlg::OnBnClickedBtnDifficult)
END_MESSAGE_MAP()


// CSeTTing 消息处理程序

// 简单按钮
void CSettingDlg::OnBnClickedBtnEasy()
{
	// TODO: 在此添加控件通知处理程序代码
	CGameDlg dlg;
	this->ShowWindow(SW_HIDE);
	dlg.level = 1;
	dlg.DoModal();
	CLLKDlg dlg1;
	dlg1.DoModal();
}


void CSettingDlg::OnBnClickedBtnCommon()
{
	// TODO: 在此添加控件通知处理程序代码
	CGameDlg dlg;
	this->ShowWindow(SW_HIDE);
	dlg.level = 2;
	dlg.DoModal();
	CLLKDlg dlg1;
	dlg1.DoModal();
}


void CSettingDlg::OnBnClickedBtnDifficult()
{
	// TODO: 在此添加控件通知处理程序代码
	CGameDlg dlg;
	this->ShowWindow(SW_HIDE);
	dlg.level = 3;
	dlg.DoModal();
	CLLKDlg dlg1;
	dlg1.DoModal();
}
