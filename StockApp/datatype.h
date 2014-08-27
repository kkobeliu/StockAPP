

struct _StockInfo 
{
	char StockName[30];
	float Price;
	int Lots; // 1000 shares
	int Shares; 
	int TotalShares; // Lots*1000 + Shares
	int TotalPrice; // Price*TotalShares
	
};

typedef struct _StockInfo StockInfo;