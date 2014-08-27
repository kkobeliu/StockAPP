#pragma once

#include "datatype.h"
// CCSVFileCreate ��ܤ��

class CCSVFileCreate : public CDialogEx
{
	DECLARE_DYNAMIC(CCSVFileCreate)

public:
	CCSVFileCreate(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CCSVFileCreate();

// ��ܤ�����
	enum { IDD = IDD_DLG_FIRST_BANK_CSV };
	int GetStockInfo(StockInfo *Info, char *InputStr);
	int Itemcounts(char *InputStr);
	CString cstrCSVFilePath;
	
	char chCSVFilePath[100];
	char chCSVOutPath[100];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonSelCsv();
	afx_msg void OnBnClickedButtonCsvTransform();
	virtual BOOL OnInitDialog();
};
