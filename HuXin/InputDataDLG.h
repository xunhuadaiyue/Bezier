#pragma once
#include "afxdialogex.h"


// InputDataDLG 对话框

class InputDataDLG : public CDialogEx
{
	DECLARE_DYNAMIC(InputDataDLG)

public:
	InputDataDLG(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~InputDataDLG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float point1_x;
	float point1_y;
	float point2_x;
	float point2_y;
	float point3_x;
	float point3_y;
	float point4_x;
	float point4_y;
};
