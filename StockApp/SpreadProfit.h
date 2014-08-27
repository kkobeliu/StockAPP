#pragma once


// SpreadProfit ��ܤ��

class SpreadProfit : public CDialogEx
{
	DECLARE_DYNAMIC(SpreadProfit)

public:
	SpreadProfit(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~SpreadProfit();

// ��ܤ�����
	enum { IDD = IDD_SPREAD_FROFIT };
	float TransactionTaxRate;
	float TransactionFeeRate;
	float TransactionDiscountRate;
	float TransactionDiscount;
	float TransactionTax;
	float TransactionFee;
	float TransactionFeeDiscount;
	float Profit;
	float ReturnOnInvestment;
	int Shares;
	float BuyingPrice;
	float SellingPrice;
	int RevisedFlag;// 0: no need adjust , 1:already adjust, 
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual void PreInitDialog();
	afx_msg void OnDeltaposSpinBuyPrice(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	int testt(void);
	char *CStringToCharPtr(CString input);
	float CalChangeUnit(float InputPrice);
	int CalProfit();
	BOOL isNumeric( CString text);
	int PriceRevise(float *CurPrice , LPNMUPDOWN pNMUpDown);
	afx_msg void OnBnClickedButtonCalProfit();
	afx_msg void OnDeltaposSpinAmount(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSellPrice(NMHDR *pNMHDR, LRESULT *pResult);
};
