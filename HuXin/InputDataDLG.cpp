// InputDataDLG.cpp: 实现文件
//

#include "pch.h"
#include "HuXin.h"
#include "afxdialogex.h"
#include "InputDataDLG.h"


// InputDataDLG 对话框

IMPLEMENT_DYNAMIC(InputDataDLG, CDialogEx)

InputDataDLG::InputDataDLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, point1_x(0)
	, point1_y(0)
	, point2_x(0)
	, point2_y(0)
	, point3_x(0)
	, point3_y(0)
	, point4_x(0)
	, point4_y(0)
{

}

InputDataDLG::~InputDataDLG()
{
}

void InputDataDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Point1_x, point1_x);
	DDX_Text(pDX, IDC_Point1_y, point1_y);
	DDX_Text(pDX, IDC_Point2_x, point2_x);
	DDX_Text(pDX, IDC_Point2_y, point2_y);
	DDX_Text(pDX, IDC_Point3_x, point3_x);
	DDX_Text(pDX, IDC_Point3_y, point3_y);
	DDX_Text(pDX, IDC_Point4_x, point4_x);
	DDX_Text(pDX, IDC_Point4_y, point4_y);
}


BEGIN_MESSAGE_MAP(InputDataDLG, CDialogEx)
END_MESSAGE_MAP()


// InputDataDLG 消息处理程序
