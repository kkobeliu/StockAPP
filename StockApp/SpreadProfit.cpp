// SpreadProfit.cpp : 實作檔
//

#include "stdafx.h"
#include "StockApp.h"
#include "SpreadProfit.h"
#include "afxdialogex.h"
#include "define.h"
#include <math.h>  
// SpreadProfit 對話方塊

IMPLEMENT_DYNAMIC(SpreadProfit, CDialogEx)

SpreadProfit::SpreadProfit(CWnd* pParent /*=NULL*/)
	: CDialogEx(SpreadProfit::IDD, pParent)
{
}

SpreadProfit::~SpreadProfit()
{
}

void SpreadProfit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SpreadProfit, CDialogEx)
	ON_BN_CLICKED(IDOK, &SpreadProfit::OnBnClickedOk)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BUY_PRICE, &SpreadProfit::OnDeltaposSpinBuyPrice)
	ON_BN_CLICKED(IDC_BUTTON_CAL_PROFIT, &SpreadProfit::OnBnClickedButtonCalProfit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMOUNT, &SpreadProfit::OnDeltaposSpinAmount)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SELL_PRICE, &SpreadProfit::OnDeltaposSpinSellPrice)
END_MESSAGE_MAP()


// SpreadProfit 訊息處理常式


void SpreadProfit::OnBnClickedOk()
{

	// TODO: 在此加入控制項告知處理常式程式碼
	//CDialogEx::OnOK();
}


void SpreadProfit::PreInitDialog()
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別

	CDialogEx::PreInitDialog();
}




BOOL SpreadProfit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CEdit *pedit = (CEdit *)GetDlgItem(IDC_EDIT_BUY_PRICE);

//	pedit->SetWindowText(BuyDefualtVal);
	SetDlgItemTextW(IDC_EDIT_BUY_PRICE,BUY_DEFAULT_VALUE);
	SetDlgItemTextW(IDC_EDIT_SELL_PRICE,SELL_DEFAULT_VALUE);
	SetDlgItemTextW(IDC_EDIT_AMOUNT,AMOUNT_DEFAULT_VALUE);
	SetDlgItemTextW(IDC_EDIT_PROFIT,PROFIT_DEFAULT_VALUE);
	SetDlgItemTextW(IDC_EDIT_ROI,ROI_DEFAULT_VALUE);
	SetDlgItemTextW(IDC_EDIT_FEE,FEE_DEFAULT_VALUE);
	SetDlgItemTextW(IDC_EDIT_TRANSACTION_TAX,TAX_DEFAULT_VALUE);
	SetDlgItemTextW(IDC_EDIT_DISCOUNT,DISCOUNT_DEFAULT_VALUE);
	SetDlgItemTextW(IDC_EDIT_FEE_SUM,FEE_SUM_DEFAULT_VALUE);



	SetDlgItemTextW(IDC_EDIT_PROFIT,PROFIT_DEFAULT_VALUE);
	SetDlgItemTextW(IDC_EDIT_PROFIT,PROFIT_DEFAULT_VALUE);
	SetDlgItemTextW(IDC_EDIT_PROFIT,PROFIT_DEFAULT_VALUE);
	CString fff = L"123.5aaa";
	bool aa = isNumeric(fff);
	/*
	CButton * pWnd = (CButton *)GetDlgItem(IDC_BUTTON_CAL_PROFIT); 
	pWnd->ModifyStyle(0, SS_BITMAP); 
	pWnd->SetBitmap((HBITMAP)::LoadImage(NULL, L"./image/arrow.bmp",   
		IMAGE_BITMAP,   
		20,   
		20,   
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));  
	CBitmapButton *btnMap = new CBitmapButton;

	btnMap->Create(NULL, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 
		CRect(10,10,100,100), this, 22222);
		*/
	/*
	CBitmap Bitmap;
	Bitmap.LoadBitmap(L"./image/arrow.bmp");
	HBITMAP hBitmap=(HBITMAP)Bitmap.Detach();
	CButton *pButton=(CButton*)GetDlgItem(IDC_BUTTON_CAL_PROFIT);
	pButton->SetBitmap(hBitmap); */
	//pWnd->SetBitmap((HBITMAP)::LoadBitmapW(NULL,L"./image/arrow.bmp"));
	/*
	pWnd->ModifyStyle(0, SS_BITMAP); 
	pWnd->SetBitmap((HBITMAP)::LoadImage(NULL, L"./image/arrow.bmp",   
		IMAGE_BITMAP,   
		70,   
		50,   
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));  
		*/
	return TRUE;  // return TRUE unless you set the focus to a control
	
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}


int SpreadProfit::testt(void)
{
	CString BuyDefualtVal = L"50";
	CString CellDefualtVal = L"50";
	CString AmountDefualtVal = L"1000";
	CString ProfitDefualt_Val = L"0";

	return 0;
}


void SpreadProfit::OnBnClickedButtonCalProfit()
{

	CalProfit();
	
}

char * SpreadProfit::CStringToCharPtr(CString input)
{
	char* Buffer = new char[input.GetLength()];

	sprintf(Buffer,"%ls",input);

	return Buffer;
}


void SpreadProfit::OnDeltaposSpinAmount(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	CString str;
	
	GetDlgItemTextW(IDC_EDIT_AMOUNT,str);
	Shares = _wtof(str);
	if (pNMUpDown->iDelta == -1)//click up
	{
		Shares = Shares + 100;
	} 
	else//click down pNMUpDown->iDelta == 1
	{
		Shares = Shares - 100;
	}
	str.Format(L"%d",Shares);
	SetDlgItemTextW(IDC_EDIT_AMOUNT,str);

	CalProfit();
	*pResult = 0;

}

int SpreadProfit::CalProfit()
{
	CString TmpStr;


	GetDlgItemTextW(IDC_EDIT_BUY_PRICE,TmpStr);
	BuyingPrice = atof( CStringToCharPtr(TmpStr));

	GetDlgItemTextW(IDC_EDIT_SELL_PRICE,TmpStr);
	SellingPrice = atof(CStringToCharPtr(TmpStr));

	GetDlgItemTextW(IDC_EDIT_AMOUNT,TmpStr);
	Shares = atof( CStringToCharPtr(TmpStr));

	GetDlgItemTextW(IDC_EDIT_TRANSACTION_TAX,TmpStr);
	TransactionTaxRate = atof( CStringToCharPtr(TmpStr))/100;

	GetDlgItemTextW(IDC_EDIT_FEE,TmpStr);
	TransactionFeeRate = atof( CStringToCharPtr(TmpStr))/100;

	GetDlgItemTextW(IDC_EDIT_DISCOUNT,TmpStr);
	TransactionDiscountRate = atof( CStringToCharPtr(TmpStr))/100;

	//交易稅 = 賣出價*股數*交易稅率
	TransactionTax = SellingPrice*Shares*TransactionTaxRate;

	//手續費 = (買進價 + 賣出價)*股數*手續費率
	TransactionFee = (BuyingPrice + SellingPrice)*Shares*TransactionFeeRate;

	//折扣後手續費 = 手續費*手續費折扣率
	TransactionFeeDiscount = TransactionFee*TransactionDiscountRate;

	//獲利 = (賣出價 - 買進價)*股數 - 交易稅 - 折扣後手續費
	Profit = (SellingPrice - BuyingPrice)*Shares - TransactionTax - TransactionFeeDiscount;
	TmpStr.Format(L"%.2f",Profit);
	SetDlgItemTextW(IDC_EDIT_PROFIT,TmpStr);
	//投資報酬率 = 獲利 / 成本 *100%
	ReturnOnInvestment = (Profit / (BuyingPrice*Shares + TransactionTax + TransactionFeeDiscount))*100;
	TmpStr.Format(L"%.2f", ReturnOnInvestment);
	SetDlgItemTextW(IDC_EDIT_ROI,TmpStr);

	//折扣後手續費 + 交易稅
	TmpStr.Format(L"%.2f", TransactionTax + TransactionFeeDiscount);
	SetDlgItemTextW(IDC_EDIT_FEE_SUM,TmpStr);

	return 0;
}


//20140819 TODO:看有沒有辦法把BUY跟SELL的處理血成FUNCTION直接CALL就好
void SpreadProfit::OnDeltaposSpinBuyPrice(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	float CurSellingVal = 0;
	float ChangeUnit = 0;
	GetDlgItemTextW(IDC_EDIT_BUY_PRICE,str);

	if (isNumeric(str))
	{
		CurSellingVal = (float)_wtof(str);
	} 
	else
	{
		AfxMessageBox(L"please enter a number!");
		return;
	}



	if (CurSellingVal == 10 || CurSellingVal == 50 || CurSellingVal == 100 || CurSellingVal == 500 || CurSellingVal == 1000)
	{//is price boundary
		if (pNMUpDown->iDelta == -1)//click up
		{
			ChangeUnit = CalChangeUnit(CurSellingVal+ 5*pNMUpDown->iDelta*(-1));
			CurSellingVal = CurSellingVal + ChangeUnit*pNMUpDown->iDelta*(-1);
		} 
		else//click down: pNMUpDown->iDelta == 1
		{
			ChangeUnit = CalChangeUnit(CurSellingVal+ 5*pNMUpDown->iDelta*(-1));
			CurSellingVal = CurSellingVal + ChangeUnit*pNMUpDown->iDelta*(-1);
		}
	} 
	else
	{//not price boundary
		PriceRevise(&CurSellingVal, pNMUpDown);
		if (RevisedFlag == 0) //no revise
		{
			ChangeUnit = CalChangeUnit(CurSellingVal);
			CurSellingVal = CurSellingVal + ChangeUnit*pNMUpDown->iDelta*(-1);
		}
	}

	str.Format(L"%.2f",CurSellingVal);
	SetDlgItemTextW(IDC_EDIT_BUY_PRICE,str);

	CalProfit();
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;
}

void SpreadProfit::OnDeltaposSpinSellPrice(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	float CurSellingVal = 0;
	float ChangeUnit = 0;
	GetDlgItemTextW(IDC_EDIT_SELL_PRICE,str);

	if (isNumeric(str))
	{
		CurSellingVal = (float)_wtof(str);
	} 
	else
	{
		AfxMessageBox(L"please enter a number!");
		return;
	}
	

	
	if (CurSellingVal == 10 || CurSellingVal == 50 || CurSellingVal == 100 || CurSellingVal == 500 || CurSellingVal == 1000)
	{//is price boundary
		if (pNMUpDown->iDelta == -1)//click up
		{
			ChangeUnit = CalChangeUnit(CurSellingVal+ 5*pNMUpDown->iDelta*(-1));
			CurSellingVal = CurSellingVal + ChangeUnit*pNMUpDown->iDelta*(-1);
		} 
		else//click down: pNMUpDown->iDelta == 1
		{
			ChangeUnit = CalChangeUnit(CurSellingVal+ 5*pNMUpDown->iDelta*(-1));
			CurSellingVal = CurSellingVal + ChangeUnit*pNMUpDown->iDelta*(-1);
		}
	} 
	else
	{//not price boundary
		PriceRevise(&CurSellingVal, pNMUpDown);
		if (RevisedFlag == 0) //no revise
		{
			ChangeUnit = CalChangeUnit(CurSellingVal);
			CurSellingVal = CurSellingVal + ChangeUnit*pNMUpDown->iDelta*(-1);
		}
	}
	
	str.Format(L"%.2f",CurSellingVal);
	SetDlgItemTextW(IDC_EDIT_SELL_PRICE,str);

	CalProfit();
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;
}

//using this function to get change unit for each price range
float SpreadProfit::CalChangeUnit(float InputPrice)
{//20142822 ToDo: 
	if (InputPrice < 10)
	{
		return BASE001;
	}
	else if (InputPrice > 10 && InputPrice < 50)
	{
		return BASE005;
	}
	else if (InputPrice > 50 && InputPrice < 100)
	{
		return BASE01;
	}
	else if (InputPrice > 100 && InputPrice < 500)
	{
		return BASE05;
	}
	else if (InputPrice > 500 && InputPrice < 1000)
	{
		return BASE1;
	}

	else if (InputPrice > 1000)
	{
		return BASE5;
	}
}//end CalChangeUnit

BOOL SpreadProfit::isNumeric( CString  text)
{
	BOOL bNumeric = TRUE;
	//LPCSTR szText =(LPCSTR) text; // Saves CString's array access overheads
	char * szText = CStringToCharPtr(text);
	int i = 0;
	while (bNumeric && szText[i])
	{
		if (!isdigit(szText[i]) && szText[i] != '-' && szText[i] != '.')
			bNumeric = FALSE;
		i++;
	}

	return bNumeric;
} 
#define EPS 1E-9 // 定義 EPS = 10^-6
int SpreadProfit::PriceRevise(float *CurPrice, LPNMUPDOWN pNMUpDown)
{
	float changeUnit = CalChangeUnit(*CurPrice);
	float FracPart = 0;
	float IntPart = 0;

	FracPart = modf(*CurPrice, &IntPart);
	RevisedFlag = 0;

	if (changeUnit == 0.01)
	//if (fabs(changeUnit - BASE001) < EPS)
	{
		//if(modf(*CurPrice*100, &IntPart) > 0 && modf(*CurPrice*100, &IntPart) <= 9)
		if(modf(*CurPrice*10, &IntPart) > 0 && modf(*CurPrice*10, &IntPart) <= 9)
		{
			if (pNMUpDown->iDelta == -1)//click up
			{
				*CurPrice = floor(*CurPrice) + ceil(FracPart/changeUnit)*changeUnit;
			}
			else //click down
			{
				*CurPrice = floor(*CurPrice) + (ceil(FracPart/changeUnit)-1)*changeUnit;
			}
			RevisedFlag = 1;
		} 
		else
		{
			RevisedFlag = 0;
		}
	} 
	else if (changeUnit == 0.05)
	{
		float diff = fabs(modf(*CurPrice, &IntPart) - changeUnit);
		if( diff < changeUnit  && fabs(diff - changeUnit) > EPS && diff > 0)
		{
			if (pNMUpDown->iDelta == -1)//click up
			{
				*CurPrice = floor(*CurPrice) + ceil(FracPart/changeUnit)*changeUnit;
			}
			else //click down
			{
				*CurPrice = floor(*CurPrice) + (ceil(FracPart/changeUnit)-1)*changeUnit;
			}
			RevisedFlag = 1;
		} 
		else
		{
			RevisedFlag = 0;
		}
	}
	else if (changeUnit == 0.1)
	{
		if(modf(*CurPrice*10, &IntPart) > 0 && modf(*CurPrice*10, &IntPart) <= 9)
		{
			if (pNMUpDown->iDelta == -1)//click up
			{
				*CurPrice = floor(*CurPrice) + ceil(FracPart/changeUnit)*changeUnit;
			}
			else //click down
			{
				*CurPrice = floor(*CurPrice) + (ceil(FracPart/changeUnit)-1)*changeUnit;
			}
			RevisedFlag = 1;
		} 
		else
		{
			RevisedFlag = 0;
		}
	}
	else if (changeUnit == 0.5)
	{
		float diff = fabs(modf(*CurPrice, &IntPart) - changeUnit);
		if( diff < changeUnit  && fabs(diff - changeUnit) > EPS && diff > 0)
		{
			if (pNMUpDown->iDelta == -1)//click up
			{
				*CurPrice = floor(*CurPrice) + ceil(FracPart/changeUnit)*changeUnit;
			}
			else //click down
			{
				*CurPrice = floor(*CurPrice) + (ceil(FracPart/changeUnit)-1)*changeUnit;
			}
			RevisedFlag = 1;
		} 
		else
		{
			RevisedFlag = 0;
		}
	}
	else if (changeUnit == 1)
	{
		if(modf(*CurPrice*10, &IntPart) > 0 )
		{
			if (pNMUpDown->iDelta == -1)//click up
			{
				*CurPrice = floor(*CurPrice) + changeUnit;
			}
			else //click down
			{
				*CurPrice = floor(*CurPrice) ;
			}
			RevisedFlag = 1;
		} 
		else
		{
			RevisedFlag = 0;
		}
	}
	else if (changeUnit == 5)
	{
		float remaider = fmod(*CurPrice,5);

		if( remaider > 0 )
		{
			if (pNMUpDown->iDelta == -1)//click up
			{
				*CurPrice = *CurPrice - remaider + changeUnit;
			}
			else //click down
			{
				*CurPrice = *CurPrice - remaider ;
			}
			RevisedFlag = 1;
		} 
		else
		{
			RevisedFlag = 0;
		}
	}

	return 0;
}