// CSVFileCreate.cpp : ��@��
//

#include "stdafx.h"
#include "StockApp.h"
#include "CSVFileCreate.h"
#include "afxdialogex.h"


// CCSVFileCreate ��ܤ��

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


// CCSVFileCreate �T���B�z�`��
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
	//char buffer[100] = "�ή�(1227),89.6,1,,1,,0,89600,89600";
	char buffer[100] = "";
	//�Ѳ��W��,�{��,���O�w�s,,,�s��,,�{��,����
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
	fprintf(OutputFile,"�Ѳ��W��,�{��,�`�Ѽ�,����,�{���i��,�{���s��\n");

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
	// TODO: �b���[�J����i���B�z�`���{���X
	//CDialogEx::OnOK();
}


void CCSVFileCreate::OnBnClickedButtonSelCsv()
{

//	CString szPathName;
	
	WCHAR szSelectFileBuffer[0x10000] = {0};
	LPWSTR pszSelectFileBuffer = NULL;
	CString szFileName;
	CString CSVOnlyPath;
	// �[�J OFN_ALLOWMULTISELECT �ݩ�
	CFileDialog fd(TRUE,NULL,NULL,OFN_ALLOWMULTISELECT,
		L"All supported file(*.*)|*.*||",this);
	// ���w�Ǧ^ buffer
	pszSelectFileBuffer = szSelectFileBuffer;
	fd.m_ofn.lpstrFile = pszSelectFileBuffer;
	// �]�w buffer �j�p
	fd.m_ofn.nMaxFile = 0x10000;

	if(fd.DoModal())
	{
		// ���o�Ĥ@���ɮצW�٪���m �Y�S�����ܶǦ^NULL
		POSITION pos = fd.GetStartPosition();
		while(pos != NULL)
		{
			// �z�L��m�Ө��o�ɮצW�� �ɮצW�٥]�t������|
			 cstrCSVFilePath = fd.GetNextPathName(pos);
			// �p�G�u�n�ɮצW�٤��n���|���� �i�H�ΤU�����{���X
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
	fprintf(OutputFile,"�Ѳ��W��,�{��,�`�Ѽ�,����,�{���i��,�{���s��\n");

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
