
// StockAppDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "StockApp.h"
#include "StockAppDlg.h"
#include "afxdialogex.h"
#include "SpreadProfit.h"

//2014012 for first bank CSV create >>>

#include "CSVFileCreate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//strtok
//2014012 for first bank CSV create <<<

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStockAppDlg 對話方塊




CStockAppDlg::CStockAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStockAppDlg::IDD, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStockAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN1, m_PriceSpin);
}

BEGIN_MESSAGE_MAP(CStockAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CStockAppDlg::OnDeltaposSpin1)
//	ON_EN_CHANGE(IDC_EDIT_PRICE, &CStockAppDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &CStockAppDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CStockAppDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CStockAppDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_FB_CSV, &CStockAppDlg::OnBnClickedButtonFbCsv)
	ON_BN_CLICKED(IDC_BUTTON_CAL_SP, &CStockAppDlg::OnBnClickedButtonCalSp)
END_MESSAGE_MAP()


// CStockAppDlg 訊息處理常式

BOOL CStockAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	
	m_PriceSpin.SetBuddy(GetDlgItem(IDC_EDIT_PRICE));
	m_PriceSpin.SetRange(50,1000);
	m_PriceSpin.SetBase(10);
	SetDlgItemTextW(IDC_EDIT_PRICE,L"50.00");

	//set font size
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PRICE);
	CFont* pFont=new CFont;
	pFont->CreatePointFont(15*10,L"Arial");
	pEdit->SetFont(pFont, 1);

	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LIMITDOWN);
	pEdit->SetFont(pFont, 1);

	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LIMITUP);
	pEdit->SetFont(pFont, 1);

	pEdit = (CEdit*)GetDlgItem(IDC_STATIC_LIMITDOWN);
	pEdit->SetFont(pFont, 1);
	pEdit = (CEdit*)GetDlgItem(IDC_STATIC_LIMITUP);
	pEdit->SetFont(pFont, 1);
	pEdit = (CEdit*)GetDlgItem(IDC_STATIC_PRICE);
	pEdit->SetFont(pFont, 1);
	
	pEdit = (CEdit*)GetDlgItem(IDC_STATIC_FUNC);
	pEdit->SetFont(pFont, 1);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CStockAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CStockAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CStockAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStockAppDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	CString str;


	float InputPrice ;
	float tmp = 0.0;
	CString ValStr;
	CString LimitUp;
	CString LimitDown;
	PriceStruct sPrice;
	//init price struct
	sPrice.NumOfDecPlace = 0;
	sPrice.Price = 0.0;
////////////////////////////// struct method
	GetDlgItemTextW(IDC_EDIT_PRICE,str);
	sPrice.Price = (float) _wtof(str);

	//after do this function the sPrice->price will change 
	ValStr = PriceIncOrDec(&sPrice,pNMUpDown->iDelta);
	//set results to price edit control
	SetDlgItemTextW(IDC_EDIT_PRICE,ValStr);

	//set results to price edit control
	tmp = CalPriceChange(&sPrice,0.07);
	LimitUp.Format(L"%.2f",tmp);
	SetDlgItemTextW(IDC_EDIT_LIMITUP,LimitUp);

	//v = x - x*0.07
	tmp = CalPriceChange(&sPrice,-0.07);
	LimitDown.Format(L"%.2f",tmp);
	SetDlgItemTextW(IDC_EDIT_LIMITDOWN,LimitDown);

////////////////////////////// struct method







//////////////////////////////non struct method
	/*
	GetDlgItemTextW(IDC_EDIT_PRICE,str);
	InputPrice = (float) _wtof(str);

	ValStr = PriceIncOrDec(InputPrice,pNMUpDown->iDelta);
	//set results to price edit control
	SetDlgItemTextW(IDC_EDIT_PRICE,ValStr);

	//set results to price edit control
	tmp = CalPriceChange((float)_wtof(ValStr),0.07);
	LimitUp.Format(L"%.1f",tmp);
	SetDlgItemTextW(IDC_EDIT_LIMITUP,LimitUp);

	//v = x - x*0.07
	tmp = CalPriceChange((float)_wtof(ValStr),-0.07);
	LimitDown.Format(L"%.1f",tmp);
	SetDlgItemTextW(IDC_EDIT_LIMITDOWN,LimitDown);
	*/
//////////////////////////////non struct method

	*pResult = 0;
}

//calculate input price and plus(minus) corresponding base
CString CStockAppDlg::PriceIncOrDec(struct PriceStruct *sPrice, float Delta)
{
	float tmp = 0.0;
	CString ValStr;
	const float Base001 = 0.01;//price 0.01~9.99
	const float Base005 = 0.05;//price 10~49.95
	const float Base01 = 0.1;//price 50~99.9
	const float Base05 = 0.5;//price 100~499.5
	const float Base1 = 1.00;//price 500~1000
	const float Base5 = 5.00;//price 1000~up

	if (sPrice->Price < 10)
	{
		sPrice->NumOfDecPlace = 2;
		sPrice->Price = (float)sPrice->Price + Base001*Delta;
		ValStr.Format(L"%.2f",(float)sPrice->Price);
	}
	else if (sPrice->Price == 10)
	{
		sPrice->NumOfDecPlace = 2;
		if (Delta > 0)
		{
			sPrice->Price = (float)sPrice->Price + Base005*Delta;
			ValStr.Format(L"%.2f",(float)sPrice->Price);
			
		} 
		else
		{
			sPrice->Price = (float)sPrice->Price + Base001*Delta;
			ValStr.Format(L"%.2f",(float)sPrice->Price);
		}
	}
	else if (sPrice->Price > 10 && sPrice->Price < 50)
	{
		sPrice->NumOfDecPlace = 2;
		sPrice->Price = (float)sPrice->Price + Base005*Delta;
		ValStr.Format(L"%.2f",(float)sPrice->Price);
	}
	else if (sPrice->Price == 50)
	{
		if (Delta > 0)
		{
			sPrice->NumOfDecPlace = 1;
			sPrice->Price = (float)sPrice->Price + Base01*Delta;
			ValStr.Format(L"%.1f",(float)sPrice->Price);
		} 
		else
		{
			sPrice->NumOfDecPlace = 2;
			sPrice->Price = (float)sPrice->Price + Base005*Delta;
			ValStr.Format(L"%.2f",(float)sPrice->Price);
		}

	}
	else if (sPrice->Price > 50 && sPrice->Price < 100)
	{
		sPrice->NumOfDecPlace = 1;
		sPrice->Price = (float)sPrice->Price + Base01*Delta;
		ValStr.Format(L"%.1f",(float)sPrice->Price);
	}
	else if (sPrice->Price == 100)
	{
		sPrice->NumOfDecPlace = 1;
		if (Delta > 0)
		{
			sPrice->Price = (float)sPrice->Price + Base05*Delta;
			ValStr.Format(L"%.1f",(float)sPrice->Price);
		} 
		else
		{
			sPrice->Price = (float)sPrice->Price + Base01*Delta;
			ValStr.Format(L"%.1f",(float)sPrice->Price);
		}
	}
	else if (sPrice->Price > 100 && sPrice->Price < 500)
	{
		sPrice->NumOfDecPlace = 1;
		sPrice->Price = (float)sPrice->Price + Base05*Delta;
		ValStr.Format(L"%.1f",(float)sPrice->Price);
	}
	else if (sPrice->Price == 500)
	{
		if (Delta > 0)
		{
			sPrice->NumOfDecPlace = 0;
			sPrice->Price = (float)sPrice->Price + Base1*Delta;
			ValStr.Format(L"%.0f",(float)sPrice->Price);
		} 
		else
		{
			sPrice->NumOfDecPlace = 1;
			sPrice->Price = (float)sPrice->Price + Base05*Delta;
			ValStr.Format(L"%.1f",(float)sPrice->Price);
		}
	}
	else if (sPrice->Price > 500 && sPrice->Price < 1000)
	{
		sPrice->NumOfDecPlace = 0;
		sPrice->Price = (float)sPrice->Price + Base1*Delta;
		ValStr.Format(L"%.0f",(float)sPrice->Price);
	}
	else if (sPrice->Price == 1000)
	{
		sPrice->NumOfDecPlace = 0;
		if (Delta > 0)
		{
			sPrice->Price = (float)sPrice->Price + Base5*Delta;
			ValStr.Format(L"%.0f",(float)sPrice->Price);
		} 
		else
		{
			sPrice->Price = (float)sPrice->Price + Base1*Delta;
			ValStr.Format(L"%.0f",(float)sPrice->Price);
		}
	}
	else if (sPrice->Price > 1000)
	{
		sPrice->NumOfDecPlace = 0;
		sPrice->Price = (float)sPrice->Price + Base5*Delta;
		ValStr.Format(L"%.0f",(float)sPrice->Price);
	}
	return ValStr;
}

float CStockAppDlg::CalPriceChange(struct PriceStruct *sPrice, float Percentage)
{
	// percentage can be positive or negative
	//return price*(1 + perenctage)
	//and check the price of all price level

	float Price = 0.0;

	Price = sPrice->Price * (1 + Percentage);
	Price = PriceRangeCheck(sPrice,Price);

	//Price = PriceRangeCheck(0,Price);

	//range check

	return Price;
}

float CStockAppDlg::PriceRangeCheck(struct PriceStruct *sPrice , float Price)
{
	//NumOfDecPlace : 
	//<50  --- 2   
	//<500 --- 1   
	//>500 --- 0   
	int NumOfDecPlace = sPrice->NumOfDecPlace;
	int base10 = 1;
	float FloorVal = 0.0;
	float Result = 0.0;

	if (Price < 10)
	{
//		NumOfDecPlace = 2;

	}
	else if (Price == 10)
	{
//		NumOfDecPlace = 2;


	}
	else if (Price > 10 && Price < 50)
	{
//		NumOfDecPlace = 2;
		FloorVal = floor(Price* powf(10.0, (float)NumOfDecPlace-1.0));
		if (Price* powf(10.0, (float)NumOfDecPlace-1.0) - FloorVal  >= 0.0 && Price* powf(10.0, (float)NumOfDecPlace-1.0) -FloorVal  <= 0.4)
		{
			Result = FloorVal / powf(10.0, (float)NumOfDecPlace-1.0);
		} 
		else
		{
			Result = (FloorVal + 0.5)  / powf(10.0, (float)NumOfDecPlace-1.0);
		}
	}
	/*
	else if (Price == 50)
	{
		NumOfDecPlace = 1;
	}
	*/
	else if (Price >= 50 && Price < 100)
	{
//		NumOfDecPlace = 1;

	}
	/*
	else if (Price == 100)
	{
		NumOfDecPlace = 1;

	}
	*/
	else if (Price >= 100 && Price < 500)
	{
		FloorVal = floor(Price* powf(10.0, (float)NumOfDecPlace-1.0));
		if (Price - FloorVal  >= 0.0 && Price -FloorVal  <= 0.4)
		{
			Result = FloorVal;
		} 
		else
		{
			Result = FloorVal + 0.5;
		}
	}
	else if (Price == 500)
	{
//		NumOfDecPlace = 0;
	}
	else if (Price > 500 && Price < 1000)
	{
//		NumOfDecPlace = 0;
	}
	else if (Price == 1000)
	{
//		NumOfDecPlace = 0;
	}
	else if (Price > 1000)
	{

	}

	return Result;
}


void CStockAppDlg::OnBnClickedOk()
{
	//calculate result after click enter at the price Edit control
	CString str;
	float InputPrice = (float) _wtof(str);
	float tmp = 0.0;
	CString ValStr;
	CString LimitUp;
	CString LimitDown;

	GetDlgItemTextW(IDC_EDIT_PRICE,ValStr);


	tmp = CalPriceChange((float)_wtof(ValStr),0.07);
	LimitUp.Format(L"%.2f",tmp);
	SetDlgItemTextW(IDC_EDIT_LIMITUP,LimitUp);

	//v = x - x*0.07
	tmp = CalPriceChange((float)_wtof(ValStr),-0.07);
	LimitDown.Format(L"%.2f",tmp);
	SetDlgItemTextW(IDC_EDIT_LIMITDOWN,LimitDown);
}

//calculate input price and plus(minus) corresponding base
CString CStockAppDlg::PriceIncOrDec(float InputPrice, float Delta)
{
	float tmp = 0.0;
	CString ValStr;
	const float Base001 = 0.01;//price 0.01~9.99
	const float Base005 = 0.05;//price 10~49.95
	const float Base01 = 0.1;//price 50~99.9
	const float Base05 = 0.5;//price 100~499.5
	const float Base1 = 1.00;//price 500~1000
	const float Base5 = 5.00;//price 1000~up

	if (InputPrice < 10)
	{
		ValStr.Format(L"%.2f",(float)InputPrice + Base001*Delta);
	}
	else if (InputPrice == 10)
	{
		if (Delta > 0)
		{
			ValStr.Format(L"%.2f",(float)InputPrice + Base005*Delta);
		} 
		else
		{
			ValStr.Format(L"%.2f",(float)InputPrice + Base001*Delta);
		}

	}
	else if (InputPrice > 10 && InputPrice < 50)
	{
		ValStr.Format(L"%.2f",(float)InputPrice + Base005*Delta);
	}
	else if (InputPrice == 50)
	{
		if (Delta > 0)
		{
			ValStr.Format(L"%.1f",(float)InputPrice + Base01*Delta);
		} 
		else
		{
			ValStr.Format(L"%.2f",(float)InputPrice + Base005*Delta);
		}

	}
	else if (InputPrice > 50 && InputPrice < 100)
	{
		ValStr.Format(L"%.1f",(float)InputPrice + Base01*Delta);
	}
	else if (InputPrice == 100)
	{
		if (Delta > 0)
		{
			ValStr.Format(L"%.1f",(float)InputPrice + Base05*Delta);
		} 
		else
		{
			ValStr.Format(L"%.1f",(float)InputPrice + Base01*Delta);
		}
	}
	else if (InputPrice > 100 && InputPrice < 500)
	{
		ValStr.Format(L"%.1f",(float)InputPrice + Base05*Delta);
	}
	else if (InputPrice == 500)
	{
		if (Delta > 0)
		{
			ValStr.Format(L"%.0f",(float)InputPrice + Base1*Delta);
		} 
		else
		{
			ValStr.Format(L"%.1f",(float)InputPrice + Base05*Delta);
		}
	}
	else if (InputPrice > 500 && InputPrice < 1000)
	{
		ValStr.Format(L"%.0f",(float)InputPrice + Base1*Delta);
	}
	else if (InputPrice == 1000)
	{
		if (Delta > 0)
		{
			ValStr.Format(L"%.0f",(float)InputPrice + Base5*Delta);
		} 
		else
		{
			ValStr.Format(L"%.0f",(float)InputPrice + Base1*Delta);
		}
	}
	else if (InputPrice > 1000)
	{
		ValStr.Format(L"%.0f",(float)InputPrice + Base5*Delta);
	}
	return ValStr;
}


float CStockAppDlg::CalPriceChange(float Price, float Percentage)
{
	// percentage can be positive or negative
	//return price*(1 + perenctage)
	//and check the price of all price level

	//float 
	Price = Price * (1 + Percentage);


	Price = PriceRangeCheck(0,Price);

	//range check

	return Price;
}


float CStockAppDlg::PriceRangeCheck(int NumOfDecPlace1, float Price)
{
	//NumOfDecPlace : 
	//<50  --- 2   
	//<500 --- 1   
	//>500 --- 0   
	int NumOfDecPlace = 0;
	int base10 = 1;
	float FloorVal = 0.0;
	float Result = 0.0;
	if (Price < 10)
	{
		NumOfDecPlace = 2;

	}
	else if (Price == 10)
	{
		NumOfDecPlace = 2;


	}
	else if (Price > 10 && Price < 50)
	{
		NumOfDecPlace = 2;

	}
	/*
	else if (Price == 50)
	{
		NumOfDecPlace = 1;
	}
	*/
	else if (Price >= 50 && Price < 100)
	{
		NumOfDecPlace = 1;
		Result = Price;
	}
	/*
	else if (Price == 100)
	{
		NumOfDecPlace = 1;

	}
	*/
	else if (Price >= 100 && Price < 500)
	{
		NumOfDecPlace = 1;

		FloorVal = floor(Price* powf(10.0, (float)NumOfDecPlace-1.0));
		if (Price - FloorVal  >= 0.0 && Price -FloorVal  <= 0.4)
		{
			Result = FloorVal;
		} 
		else
		{
			Result = FloorVal + 0.5;
		}
	}
	else if (Price == 500)
	{
		NumOfDecPlace = 0;
	}
	else if (Price > 500 && Price < 1000)
	{
		NumOfDecPlace = 0;
	}
	else if (Price == 1000)
	{
		NumOfDecPlace = 0;
	}
	else if (Price > 1000)
	{

	}

	return Result;
}


void CStockAppDlg::OnBnClickedButton1()
{
	
	SpreadProfit SP;// = new
	//test.OnInitDialog();
	if(SP.DoModal() == IDOK)
	{
		CString BuyDefualtVal = L"50";
		CString CellDefualtVal = L"50";
		CString AmountDefualtVal = L"1000";
		CString ProfitDefualt_Val = L"0";


		SetDlgItemTextW(IDC_EDIT_BUY_PRICE,BuyDefualtVal);
		SetDlgItemTextW(IDC_EDIT_SELL_PRICE,CellDefualtVal);
		SetDlgItemTextW(IDC_EDIT_AMOUNT,AmountDefualtVal);
		SetDlgItemTextW(IDC_EDIT_PROFIT,ProfitDefualt_Val);
		/*
		string szFileName = fileDlg.GetFileName();
		m_txt1.SetWindowText( szFileName.c_str());

		std::ifstream infile(szFileName.c_str());
		const int MAX = 80; // 以後要修改每行字數時，只要修改此值即可
		char buffer[MAX];
		m_listbox1.ResetContent();
		while ( infile )
		{
			infile.getline(buffer, MAX);
			m_listbox1.AddString( buffer );
		}
		infile.close();
		*/
	}
	// TODO: 在此加入控制項告知處理常式程式碼

}


void CStockAppDlg::OnBnClickedButton2()
{

	CCSVFileCreate dlg;
	dlg.DoModal();
}


void CStockAppDlg::OnBnClickedButtonFbCsv()
{
	CCSVFileCreate dlg;
	dlg.DoModal();


}


void CStockAppDlg::OnBnClickedButtonCalSp()
{
	SpreadProfit SP;// = new
	//test.OnInitDialog();
	if(SP.DoModal() == IDOK)
	{
	}
	else
	{
		//AfxMessageBox(L"spread profit dlg create fail!");
	}
}
