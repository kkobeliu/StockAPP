
// StockAppDlg.h : ���Y��
//

#pragma once
#include "afxcmn.h"


// CStockAppDlg ��ܤ��
class CStockAppDlg : public CDialogEx
{
// �غc
public:
	CStockAppDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_STOCKAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	CSpinButtonCtrl m_PriceSpin;
//	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	CString PriceIncOrDec(float InputPrice, float Delta);
	float CalPriceChange(float Price, float Percentage);
	float PriceRangeCheck(int NumOfDecPlace, float Price);

////////////////////////////// struct method
	struct PriceStruct
	{
		float Price;
		int NumOfDecPlace;
	};
	CString PriceIncOrDec(struct PriceStruct *sPrice, float Delta);
	float CalPriceChange(struct PriceStruct *sPrice, float Percentage);
	float PriceRangeCheck(struct PriceStruct *sPrice, float Price);
	//int SetDlgItemPriceTextW(struct PriceStruct *sPrice, int ItemID, );
////////////////////////////// struct method
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonFbCsv();
	afx_msg void OnBnClickedButtonCalSp();
};
