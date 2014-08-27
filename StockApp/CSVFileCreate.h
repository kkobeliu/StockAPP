#pragma once

#include "datatype.h"
// CCSVFileCreate 對話方塊

class CCSVFileCreate : public CDialogEx
{
	DECLARE_DYNAMIC(CCSVFileCreate)

public:
	CCSVFileCreate(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CCSVFileCreate();

// 對話方塊資料
	enum { IDD = IDD_DLG_FIRST_BANK_CSV };
	int GetStockInfo(StockInfo *Info, char *InputStr);
	int Itemcounts(char *InputStr);
	CString cstrCSVFilePath;
	
	char chCSVFilePath[100];
	char chCSVOutPath[100];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonSelCsv();
	afx_msg void OnBnClickedButtonCsvTransform();
	virtual BOOL OnInitDialog();
};
