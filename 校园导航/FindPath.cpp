// FindPath.cpp : 实现文件
//

#include "stdafx.h"
#include "校园导航.h"
#include "FindPath.h"
#include "afxdialogex.h"

//******************************保存起始距离的全局变量
int First=100;
int End=100;
Graph<CPoint> Map;

// FindPath 对话框

IMPLEMENT_DYNAMIC(FindPath, CDialogEx)

FindPath::FindPath(CWnd* pParent /*=NULL*/)
	: CDialogEx(FindPath::IDD, pParent)
	, m_Path1(_T(""))
	, m_Path2(_T(""))
	, m_ShowPath(_T(""))
{

}

FindPath::~FindPath()
{
}

void FindPath::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, m_Path1);
	DDX_CBString(pDX, IDC_COMBO2, m_Path2);
	DDX_Text(pDX, IDC_EDIT1, m_ShowPath);
}


BEGIN_MESSAGE_MAP(FindPath, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &FindPath::On_close)
	ON_BN_CLICKED(IDC_BUTTON1, &FindPath::On_Deal)
END_MESSAGE_MAP()


// FindPath 消息处理程序


void FindPath::On_close()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void FindPath::On_Deal()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_Path1==m_Path2)
	{
		MessageBox(_T("路径不能相等！"),_T("Error"),MB_OK);
		return;
	}
	if (m_Path1.IsEmpty() || m_Path2.IsEmpty())
	{
		MessageBox(_T("路径不能为空！"), _T("Error"), MB_OK);
		return;
	}
	//************************************************起点
	if (m_Path1 == _T("教二楼"))
		First=0;
	else if (m_Path1 == _T("研究生楼"))
		First=3;
	else if (m_Path1 == _T("映荷轩"))
		First= 6;
	else if (m_Path1 == _T("学一食堂"))
		First= 7;
	else if (m_Path1 == _T("学二食堂"))
		First= 8;
	else if (m_Path1 == _T("公主楼"))
		First=9;
	else if (m_Path1 == _T("保卫部"))
		First = 11;
	else if (m_Path1 == _T("大学生活动中心"))
		First= 12;
	else if (m_Path1 == _T("学三食堂"))
		First= 14;
	else if (m_Path1 == _T("弘毅堂"))
		First= 15;
	else if (m_Path1 == _T("52栋"))
		First= 16;
	else if (m_Path1 == _T("53栋"))
		First= 17;
	else if (m_Path1 == _T("63栋"))
		First= 18;
	else if (m_Path1 == _T("教三楼"))
		First= 19;
	else if (m_Path1 == _T("主楼"))
		First= 21;
	else if (m_Path1 == _T("基础楼"))
		First= 23;
	else if (m_Path1 == _T("教一楼"))
		First= 24;
	else if (m_Path1 == _T("图书馆"))
		First= 27;
	else if (m_Path1 == _T("物探楼"))
		First= 29;
	else if (m_Path1 == _T("水工楼"))
		First= 30;
	else if (m_Path1 == _T("西一门"))
		First= 31;
	//*************************************************终点
	if (m_Path2 == _T("教二楼"))
		End = 0;
	else if (m_Path2 == _T("研究生楼"))
		End = 3;
	else if (m_Path2 == _T("映荷轩"))
		End = 6;
	else if (m_Path2 == _T("学一食堂"))
		End = 7;
	else if (m_Path2 == _T("学二食堂"))
		End = 8;
	else if (m_Path2 == _T("公主楼"))
		End = 9;
	else if (m_Path2 == _T("保卫部"))
		End = 11;
	else if (m_Path2 == _T("大学生活动中心"))
		End = 12;
	else if (m_Path2 == _T("学三食堂"))
		End = 14;
	else if (m_Path2 == _T("弘毅堂"))
		End = 15;
	else if (m_Path2 == _T("52栋"))
		End = 16;
	else if (m_Path2 == _T("53栋"))
		End = 17;
	else if (m_Path2 == _T("63栋"))
		End = 18;
	else if (m_Path2 == _T("教三楼"))
		End = 19;
	else if (m_Path2 == _T("主楼"))
		End = 21;
	else if (m_Path2 == _T("基础楼"))
		End = 23;
	else if (m_Path2 == _T("教一楼"))
		End = 24;
	else if (m_Path2 == _T("图书馆"))
		End = 27;
	else if (m_Path2 == _T("物探楼"))
		End = 29;
	else if (m_Path2 == _T("水工楼"))
		End = 30;
	else if (m_Path2 == _T("西一门"))
		End = 31;
	//***************************************计算并显示路径
	Map.ShortestPath(First);
	m_ShowPath = Map.showPath(End);
	UpdateData(false);
	MessageBox(_T("查询完成！"), _T("提示"), MB_OK);
}
