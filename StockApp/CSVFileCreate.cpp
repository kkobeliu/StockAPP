// CSVFileCreate.cpp : 實作檔
//

#include "stdafx.h"
#include "StockApp.h"
#include "CSVFileCreate.h"
#include "afxdialogex.h"


// CCSVFileCreate 對話方塊

IMPLEMENT_DYNAMIC(CCSVFileCreate, CDialogEx)

CCSVFileCreate::CCSVFileCreate(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCSVFileCreate::IDD, pParent)
{

}

CCSVFileCreate::~CCSVFileCreate()
{
}

void CCSVFileCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCSVFileCreate, CDialogEx)

	ON_BN_CLICKED(IDOK, &CCSVFileCreate::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SEL_CSV, &CCSVFileCreate::OnBnClickedButtonSelCsv)
	ON_BN_CLICKED(IDC_BUTTON_CSV_TRANSFORM, &CCSVFileCreate::OnBnClickedButtonCsvTransform)
END_MESSAGE_MAP()


// CCSVFileCreate 訊息處理常式
int CCSVFileCreate::GetStockInfo(StockInfo *Info, char *InputStr)
{
	char * pch;
	int info_index = 0;

	int ItemCnts = 0;
	char cpstr[100] = "";

	sprintf(cpstr,"%s",InputStr);

	ItemCnts = Itemcounts(cpstr);

	pch = strtok (InputStr,",");
	while (pch != NULL)
	{
		switch(info_index)
		{
		case 0://get stock name
			sprintf(Info->StockName, "%s", pch);
			break;
		case 1://get stock price
			Info->Price = atof(pch);
			break;
		case 3://get stock lots
			Info->Lots = atoi(pch);
			break;
		case 4://get stock shares if the stock has no shares
			Info->Shares = atoi(pch);
			break;
		case 5://get stock shares if the stock has shares > 0
			if (ItemCnts == 10)
			{
				Info->Shares = atoi(pch);
			}
			break;
		default:
			break;
		}

		info_index++ ;
		pch = strtok (NULL, ",");
	}

	Info->TotalShares = Info->Lots*1000 + Info->Shares;
	Info->TotalPrice = Info->TotalShares * Info->Price;
	return 0;
}

void CCSVFileCreate::OnBnClickedOk()
{
	//char buffer[100] = "佳格(1227),89.6,1,,1,,0,89600,89600";
	char buffer[100] = "";
	//股票名稱,現價,集保庫存,,,零股,,現值,市值
	char *input = NULL;
	StockInfo Stock_Info;
	int skip1,  skip2,  skip3;
	int info_index = 0;
	//FILE *InputFile = fopen("20140811.csv","r+");
	//FILE *OutputFile = fopen("Out.csv","w+");
	FILE *InputFile = fopen(chCSVFilePath,"r+");
	FILE *OutputFile = fopen(chCSVOutPath,"w+");
	char * pch;

	if (InputFile==NULL)
	{
		printf("can't open output file");
	//	return 1;
	}
	if (OutputFile==NULL)
	{
		printf("can't open output file");
	//	return 1;
	}

	input = buffer;

	int i = 0;
	while(i <3)//skip header line
	{		
		if(fgets(buffer,128,InputFile)!=NULL)
		{
			i++;
		}
	}
	//print new header line
	fprintf(OutputFile,"股票名稱,現價,總股數,市值,現有張數,現有零股\n");

	while(!feof(InputFile))
	{
		if(fgets(buffer,128,InputFile)!=NULL)
		{
			GetStockInfo(&Stock_Info,buffer);
			fprintf(OutputFile,"%s,%.2f,%d,%d,%d,%d\n",Stock_Info.StockName,Stock_Info.Price,Stock_Info.TotalShares,Stock_Info.TotalPrice, Stock_Info.Lots,Stock_Info.Shares);
		}
	}

	fclose (InputFile);
	fclose (OutputFile);

	//return 0;
	// TODO: 在此加入控制項告知處理常式程式碼
	//CDialogEx::OnOK();
}


void CCSVFileCreate::OnBnClickedButtonSelCsv()
{

//	CString szPathName;
	
	WCHAR szSelectFileBuffer[0x10000] = {0};
	LPWSTR pszSelectFileBuffer = NULL;
	CString szFileName;
	CString CSVOnlyPath;
	// 加入 OFN_ALLOWMULTISELECT 屬性
	CFileDialog fd(TRUE,NULL,NULL,OFN_ALLOWMULTISELECT,
		L"All supported file(*.*)|*.*||",this);
	// 指定傳回 buffer
	pszSelectFileBuffer = szSelectFileBuffer;
	fd.m_ofn.lpstrFile = pszSelectFileBuffer;
	// 設定 buffer 大小
	fd.m_ofn.nMaxFile = 0x10000;

	if(fd.DoModal())
	{
		// 取得第一個檔案名稱的位置 若沒有的話傳回NULL
		POSITION pos = fd.GetStartPosition();
		while(pos != NULL)
		{
			// 透過位置來取得檔案名稱 檔案名稱包含完整路徑
			 cstrCSVFilePath = fd.GetNextPathName(pos);
			// 如果只要檔案名稱不要路徑的話 可以用下面的程式碼
			int nFileNameStart = cstrCSVFilePath.ReverseFind('\\') + 1;
			szFileName = cstrCSVFilePath.Mid(nFileNameStart);
			CSVOnlyPath = cstrCSVFilePath.Left(nFileNameStart);
			//CCSVOnFilePath.
		}

		SetDlgItemTextW(IDC_EDIT_IN_CSV,szFileName);
	}
	

	sprintf(chCSVFilePath,"%ls",(LPCTSTR) cstrCSVFilePath);
	sprintf(chCSVOutPath,"%ls",(LPCTSTR) CSVOnlyPath);
	//20140812 TODO: 1. how to convert Cstring to char * for fopen?
	//				 2.	why file path can not deal with Chinese?
	//strcpy(CSVFilePath,(char*) CCSVFilePath.GetString());
}

int CCSVFileCreate::Itemcounts(char *InputStr)
{
	int counts = 0;
	char * pch;
	pch = strtok (InputStr,",");
	while (pch != NULL)
	{
		counts ++;
		pch = strtok (NULL, ",");
	}
	return counts;
}

void CCSVFileCreate::OnBnClickedButtonCsvTransform()
{

	char buffer[100] = "";
	char *input = NULL;
	StockInfo Stock_Info;
	int skip1,  skip2,  skip3;
	int info_index = 0;
	FILE *InputFile = fopen(chCSVFilePath,"r+");
	FILE *OutputFile = NULL;
	CEdit * pEdt = (CEdit *)GetDlgItem(IDC_EDIT_OUT_CSV_NAME);
	CString filename;
	char * pch;
	char CSVOutPath[100] = "";

	pEdt->GetWindowText(filename);
	sprintf(CSVOutPath,"%s\%ls",chCSVOutPath,(LPCTSTR)filename);
	OutputFile = fopen(CSVOutPath,"w+");
	

	if (InputFile==NULL)
	{
		AfxMessageBox(L"Can't open input file!");
	}
	if (OutputFile==NULL)
	{
		AfxMessageBox(L"Can't open output file!");
	}

	input = buffer;
	Stock_Info.StockName;

	int i = 0;
	while(i <3)//skip header line
	{		
		if(fgets(buffer,128,InputFile)!=NULL)
		{
			i++;
		}
	}
	//print new header line
	fprintf(OutputFile,"股票名稱,現價,總股數,市值,現有張數,現有零股\n");

	while(!feof(InputFile))
	{
		if(fgets(buffer,128,InputFile)!=NULL)
		{
			GetStockInfo(&Stock_Info,buffer);
			fprintf(OutputFile,"%s,%.2f,%d,%d,%d,%d\n",Stock_Info.StockName,Stock_Info.Price,Stock_Info.TotalShares,Stock_Info.TotalPrice, Stock_Info.Lots,Stock_Info.Shares);
		}
	}

	fclose (InputFile);
	fclose (OutputFile);

}


BOOL CCSVFileCreate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strValue = L"Out.csv";
	
	CEdit * pEdt = (CEdit *)GetDlgItem(IDC_EDIT_OUT_CSV_NAME);
	//CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	CFont* pFont=new CFont;
	pFont->CreatePointFont(13*10, L"Arial");
	pEdt->SetFont(pFont, 1);
	pEdt->SetWindowText(strValue);
	
	pEdt = (CEdit *)GetDlgItem(IDC_EDIT_IN_CSV);
	pEdt->SetFont(pFont, 1);

	pEdt = (CEdit *)GetDlgItem(IDC_BUTTON_CSV_TRANSFORM);
	pEdt->SetFont(pFont, 1);

	pEdt = (CEdit *)GetDlgItem(IDC_BUTTON_SEL_CSV);
	pEdt->SetFont(pFont, 1);

	pEdt = (CEdit *)GetDlgItem(IDC_STATIC_OUT_CSV);
	pEdt->SetFont(pFont, 1);

	return TRUE;  // return TRUE unless you set the focus to a control

}
