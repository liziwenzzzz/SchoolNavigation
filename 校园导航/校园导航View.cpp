
// 校园导航View.cpp : C校园导航View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "校园导航.h"
#endif

#include "校园导航Doc.h"
#include "校园导航View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include"MainFrm.h"
#include "Resource.h"
#include "FindPath.h"


//***********************使用全局变量
extern int First;
extern int End;
extern Graph<CPoint> Map;

// C校园导航View

IMPLEMENT_DYNCREATE(C校园导航View, CScrollView)

BEGIN_MESSAGE_MAP(C校园导航View, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_32772, &C校园导航View::On_ShowPath)
	ON_COMMAND(ID_32771, &C校园导航View::On_Search)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32773, &C校园导航View::OnClear)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_0_32774, &C校园导航View::On_Menu1)
	ON_COMMAND(ID_0_32775, &C校园导航View::On_Menu2)
END_MESSAGE_MAP()

// C校园导航View 构造/析构

C校园导航View::C校园导航View()
{
	// TODO:  在此处添加构造代码
	choice = false;
	m_Bitmap.LoadBitmap(IDB_BITMAP1);              //导入位图
	//**************************************************点集
	p[0] = CPoint(213,144);
	p[1] = CPoint(158,144);
	p[2] = CPoint(275,144);
	p[3] = CPoint(113,144);
	p[4] = CPoint(161,209);
	p[5] = CPoint(72,218);
	p[6] = CPoint(72,192);
	p[7] = CPoint(72,246);
	p[8] = CPoint(72,281);
	p[9] = CPoint(156,296);
	p[10] = CPoint(275,209);
	p[11] = CPoint(275,296);
	p[12] = CPoint(156, 321);
	p[13] = CPoint(156, 363);
	p[14] = CPoint(117, 363);
	p[15] = CPoint(156, 397);
	p[16] = CPoint(156,455);
	p[17] = CPoint(156, 492);
	p[18] = CPoint(156, 528);
	p[19] = CPoint(275, 339);
	p[20] = CPoint(275, 364);
	p[21] = CPoint(364, 364);
	p[22] = CPoint(275, 399);
	p[23] = CPoint(333, 399);
	p[24] = CPoint(410, 399);
	p[25] = CPoint(156, 548);
	p[26] = CPoint(275, 548);
	p[27] = CPoint(344, 590);
	p[28] = CPoint(367, 296);
	p[29] = CPoint(344, 548);
	p[30] = CPoint(416, 548);
	p[31] = CPoint(456, 590);
	//************************************************导入边和点
	for (int i = 0; i < 32; i++)
		Map.insertVertex(p[i]);
	Map.insertEdge(3, 1, 45);
	Map.insertEdge(1, 0, 55);
	Map.insertEdge(0, 2, 59);
	Map.insertEdge(1, 4, 65);
	Map.insertEdge(2, 10, 65);
	Map.insertEdge(4, 10, 114);
	Map.insertEdge(6, 5, 26);
	Map.insertEdge(5, 4, 89);
	Map.insertEdge(5, 7, 28);
	Map.insertEdge(7, 8, 35);
	Map.insertEdge(4, 9, 87);
	Map.insertEdge(10, 11, 87);
	Map.insertEdge(9, 11, 119);
	Map.insertEdge(11, 28, 92);
	Map.insertEdge(9, 12, 25);
	Map.insertEdge(11, 19, 43);
	Map.insertEdge(12, 13, 42);
	Map.insertEdge(14, 13, 39);
	Map.insertEdge(19, 20, 25);
	Map.insertEdge(13, 15, 34);
	Map.insertEdge(15, 16, 58);
	Map.insertEdge(16, 17, 37);
	Map.insertEdge(17, 18, 36);
	Map.insertEdge(18, 25, 20);
	Map.insertEdge(20, 21, 89);
	Map.insertEdge(20, 22, 35);
	Map.insertEdge(22, 23, 58);
	Map.insertEdge(21, 23, 47);
	Map.insertEdge(21, 24, 47);
	Map.insertEdge(23, 24, 77);
	Map.insertEdge(25, 26, 119);
	Map.insertEdge(22, 26, 149);
	Map.insertEdge(26, 29, 69);
	Map.insertEdge(29, 30, 72);
	Map.insertEdge(29, 27, 42);
	Map.insertEdge(27, 31, 112);
	//***********************************************矩形区域
	m_rect[0].SetRect(62, 452, 129, 499);//52栋
	m_rect[1].SetRect(61, 348, 91, 426);//学三食堂
	m_rect[2].SetRect(2, 272, 46, 291);//学二食堂
	m_rect[3].SetRect(2, 230, 45, 258);//学一食堂
	m_rect[4].SetRect(63, 260, 124, 301);//公主楼
	m_rect[5].SetRect(97, 310, 124, 354);//大活
	m_rect[6].SetRect(97, 369, 120, 426);//弘毅堂
	m_rect[7].SetRect(144, 211, 248, 291);//体育馆
	m_rect[8].SetRect(265, 322, 283, 362);//教三
	m_rect[9].SetRect(376, 416, 445, 433);//教一
	m_rect[10].SetRect(291, 346, 408, 355);//主楼
	m_rect[11].SetRect(269, 566, 312, 623);//图书馆
	m_rect[12].SetRect(150, 115, 244, 127);//教二楼
	m_rect[13].SetRect(158, 155, 247, 201);//荷花池
	m_rect[14].SetRect(170, 343, 239, 473);//操场
}

C校园导航View::~C校园导航View()
{
}

BOOL C校园导航View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// C校园导航View 绘制

void C校园导航View::OnDraw(CDC* pDC)
{
	C校园导航Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SelectObject(&m_Bitmap);
	pDC->StretchBlt(0, 0, 598, 768, &MemDC, 0, 0, 598, 768, SRCCOPY);
	//**********************************************得到滚动条移动的位置
	m_pt = GetScrollPosition();
	//**********************************************防止窗口改变后画线的消失
	if (choice)
		this->On_ShowPath();
}

void C校园导航View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	sizeTotal.cx = 598;
	sizeTotal.cy = 768;
	SetScrollSizes(MM_TEXT, sizeTotal);
	//************************************初始化标签
	m_tip.Create(this);
	m_tip.AddTool(this);
}


// C校园导航View 打印

BOOL C校园导航View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C校园导航View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void C校园导航View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// C校园导航View 诊断

#ifdef _DEBUG
void C校园导航View::AssertValid() const
{
	CScrollView::AssertValid();
}

void C校园导航View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

C校园导航Doc* C校园导航View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C校园导航Doc)));
	return (C校园导航Doc*)m_pDocument;
}
#endif //_DEBUG


// C校园导航View 消息处理程序


void C校园导航View::On_ShowPath()
{
	// TODO:  在此添加命令处理程序代码
	//*******************************************显示路径
	if (First == 100)
	{
		MessageBox(_T("未选择路径！"),_T("提示"),MB_OK);
		return;
	}
	choice = true;               //用户已要求画图
	CDC* dc = GetDC();
	CPen pen(PS_SOLID, 3, RGB(255, 0, 0));
	dc->SelectObject(&pen);
	Map.getPath(End,dc,m_pt);
	ReleaseDC(dc);
}


void C校园导航View::On_Search()
{
	// TODO:  在此添加命令处理程序代码
	FindPath find;
	find.DoModal();
}



void C校园导航View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//***********************************************调整坐标的位置
	point.x += m_pt.x;
	point.y += m_pt.y;
	//***********************************************显示坐标
	CString str;
	str.Format(_T("x=%d, y=%d"), point.x, point.y); 
	((CMainFrame*)GetParent())->SetMessageText(str);
	//***********************************************显示标签
	if (m_save != point)
	{
		if (m_rect[0].PtInRect(point))
			m_tip.UpdateTipText(_T("52栋，我们的寝室楼。"), this);
		else if (m_rect[1].PtInRect(point))
			m_tip.UpdateTipText(_T("三食堂，我们吃饭的位置。"), this);
		else if (m_rect[2].PtInRect(point))
			m_tip.UpdateTipText(_T("二食堂，也是我们吃饭的位置。"), this);
		else if (m_rect[3].PtInRect(point))
			m_tip.UpdateTipText(_T("一食堂，我们不用去的食堂。"), this);
		else if (m_rect[4].PtInRect(point))
			m_tip.UpdateTipText(_T("女生寝室，不用解释了吧。"), this);
		else if (m_rect[5].PtInRect(point))
			m_tip.UpdateTipText(_T("大学生活动的场所。"), this);
		else if (m_rect[6].PtInRect(point))
			m_tip.UpdateTipText(_T("弘毅堂，看电影得抢位置。"), this);
		else if (m_rect[7].PtInRect(point))
			m_tip.UpdateTipText(_T("体育馆，由羽毛球馆，攀岩馆等组成。"), this);
		else if (m_rect[8].PtInRect(point))
			m_tip.UpdateTipText(_T("教三，平时上课的位置。"), this);
		else if (m_rect[9].PtInRect(point))
			m_tip.UpdateTipText(_T("教一，很多考试在这里。"), this);
		else if (m_rect[10].PtInRect(point))
			m_tip.UpdateTipText(_T("主楼八楼有好点的机房。"), this);
		else if (m_rect[11].PtInRect(point))
			m_tip.UpdateTipText(_T("图书馆是学习和邂逅的好地方。"), this);
		else if (m_rect[12].PtInRect(point))
			m_tip.UpdateTipText(_T("教二楼传说有许多鬼故事的地方。"), this);
		else if (m_rect[13].PtInRect(point))
			m_tip.UpdateTipText(_T("荷花池，西区有水的地方。"), this);
		else if (m_rect[14].PtInRect(point))
			m_tip.UpdateTipText(_T("每天痛苦的早操就在这里。"), this);
		else
			m_tip.UpdateTipText(_T(""), this);
	}
	m_save = point;                            //防止标签一直闪烁
	CScrollView::OnMouseMove(nFlags, point);
}


BOOL C校园导航View::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	m_tip.RelayEvent(pMsg);
	return CScrollView::PreTranslateMessage(pMsg);
}


void C校园导航View::OnClear()
{
	// TODO:  在此添加命令处理程序代码
	choice = false;                   //状态重新变为未画图的状态   
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	ScrollToPosition(pt);
	Invalidate();
}


void C校园导航View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CMenu menu, *pSubMenu;
	menu.LoadMenuW(IDR_MENU1);
	pSubMenu = menu.GetSubMenu(0);
	GetCursorPos(&point);                                            //得到光标处
	pSubMenu->TrackPopupMenu(nFlags, point.x, point.y, this);        //确保右键点击在哪菜单出现在哪
	CScrollView::OnRButtonDown(nFlags, point);
}


void C校园导航View::On_Menu1()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox(_T("2015.12.11"));
}


void C校园导航View::On_Menu2()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox(_T("111141 张超"));
}
