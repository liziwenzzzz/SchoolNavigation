
// 校园导航View.h : C校园导航View 类的接口
//

#pragma once

#include"Graph.h"

//************************两个类都要使用，我想定义为全局变量


class C校园导航View : public CScrollView
{
protected: // 仅从序列化创建
	C校园导航View();
	DECLARE_DYNCREATE(C校园导航View)

// 特性
public:
	C校园导航Doc* GetDocument() const;

// 操作
public:
	CBitmap m_Bitmap;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~C校园导航View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On_ShowPath();
	afx_msg void On_Search();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CToolTipCtrl m_tip;
	//******************************************************点集
	CPoint p[32];
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//*******************************************************矩形区域
	CRect m_rect[15];
	CPoint m_save;                 //保存一个点
	CPoint m_pt;                   //保存滚动条当前的位置
	afx_msg void OnClear();
	bool choice;                   //用户是否已经要求绘图
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void On_Menu1();
	afx_msg void On_Menu2();
};

#ifndef _DEBUG  // 校园导航View.cpp 中的调试版本
inline C校园导航Doc* C校园导航View::GetDocument() const
   { return reinterpret_cast<C校园导航Doc*>(m_pDocument); }
#endif

