#pragma once

#include "Graph.h"


// FindPath 对话框

class FindPath : public CDialogEx
{
	DECLARE_DYNAMIC(FindPath)

public:
	FindPath(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FindPath();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Path1;
	CString m_Path2;
	afx_msg void On_close();
	afx_msg void On_Deal();
	// 显示路径
	CString m_ShowPath;
};
