
// Keyplayers_GUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Keyplayers_GUI.h"
#include "Keyplayers_GUIDlg.h"
#include "afxdialogex.h"

#include "iostream"
#include "fstream"
#include "iomanip"
#include "conio.h"
#include "cstdlib"
#include "windows.h"
#include "ctime"
#include "fstream"
#include "string"
#include <vector>
#include <sstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CTH 10

int MTLIKE[1024][1024]={0,0},n,a[1024]={0}, vertex, numOfEffect[1024] = {0}, b1[1024]={0};
float MTWEIGHTED[1024][1024]={0,0},b[1024]={0};
double LenPath[1024][1024] = {0,0};
string member[1024], member1[1024], affectionTop[1024],stringLenPath[1024],affectionTop1[1024],stringLenPath1[1024], pathMT;
float LenSum[1024]={0};
bool m_sDone = false, m_sPp1Done = false, m_sPp2Done = false, m_IsPath[1024][1024] = {false, false};
vector<vector<int> > effect(1024, vector<int> (1,0));
HANDLE myMutex;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKeyplayers_GUIDlg dialog




CKeyplayers_GUIDlg::CKeyplayers_GUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeyplayers_GUIDlg::IDD, pParent)
	, m_sFileIn(_T(""))
	, m_sNumOfKey(_T(""))
	, m_sResult1(_T(""))
	, m_sThreshold(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyplayers_GUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILEIN, m_sFileIn);
	DDX_Text(pDX, IDC_EDIT_NUM_KEY, m_sNumOfKey);
	DDX_Text(pDX, IDC_EDIT_KQ_PP1, m_sResult1);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_sThreshold);
}

BEGIN_MESSAGE_MAP(CKeyplayers_GUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CKeyplayers_GUIDlg::OnBnClickedBtnOpenfile)
	ON_BN_CLICKED(IDC_BTN_PP1, &CKeyplayers_GUIDlg::OnBnClickedBtnPp1)
	ON_BN_CLICKED(IDC_BTN_PP2, &CKeyplayers_GUIDlg::OnBnClickedBtnPp2)
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CKeyplayers_GUIDlg::OnBnClickedBtnAbout)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CKeyplayers_GUIDlg::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BUTTON1, &CKeyplayers_GUIDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CKeyplayers_GUIDlg message handlers

BOOL CKeyplayers_GUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_sFileIn = "";
	m_sNumOfKey = "";
	m_sThreshold = "";
	m_sResult1 = "";
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKeyplayers_GUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKeyplayers_GUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKeyplayers_GUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void ReplaceStringInPlace(std::string& subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

string IntToString ( int number )
{
  std::ostringstream oss;

  // Works just like cout
  oss<< number;

  // Return the underlying string
  return oss.str();
}

string FloatToString ( float number )
{
  std::ostringstream oss;

  // Works just like cout
  oss<< number;

  // Return the underlying string
  return oss.str();
}

void swap(int &a,int &b)
{
	int temp=a;
	a=b;
	b=temp;
}

void swapf(float &a,float &b)
{
	float temp=a;
	a=b;
	b=temp;
}

void SortMT()
{
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			if(b[i]<b[j])
			{
				swapf(b[i],b[j]);
				swap(a[i],a[j]);
				swap(member[i],member[j]);
				swap(affectionTop[i], affectionTop[j]);
				swap(stringLenPath[i], stringLenPath[j]);
			}
}

void SortMT2()
{
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			if(b1[i]<b1[j])
			{
				swap(b1[i],b1[j]);
				swap(a[i],a[j]);
				swap(member1[i],member1[j]);
				swap(affectionTop1[i], affectionTop1[j]);
				swap(stringLenPath1[i], stringLenPath1[j]);
				swap(numOfEffect[i], numOfEffect[j]);
				//swap(effect[i], effect[j]);
			}
}

void writeMT(string strMtLike, float mtg[1024], int top)
{
	ReplaceStringInPlace(strMtLike, ".txt", "_" );
	string path= strMtLike +"result_keyplayers.txt";
	ofstream write (path);
	//write<<n<<"\n";
	write<<"Danh sach "<<top<<" phan tu co suc anh huong lon nhat trong do thi: "<<endl;
	for(int i=1;i<=n;i++)
	{
		a[i]=i;
		b[i]=mtg[i];
	}
	SortMT();
	for(int i=1;i<=top;i++)
	{
		write<<"Suc anh huong cua dinh "<<a[i]<< "(" <<member[i] <<") : "<<b[i];
		write<<"\n";
		write<<"Dinh nay anh huong toi dinh: "<<"\n";
		write<<affectionTop[i]<<"\n";
		write<<"Suc anh huong toi tung dinh:\n";
		write<<stringLenPath[i]<<"\n";
	}
}

void writeMT2(string strMtLike, int mtg[1024], int top, float threshold )
{
	ReplaceStringInPlace(strMtLike, ".txt", "_" );
	string tempthres = FloatToString(threshold);
	string path = strMtLike + "result_keyplayers_threshold_" + tempthres +"_.txt";
	ofstream write (path);
	//write<<n<<"\n";
	write<<"Danh sach "<<top<<" phan tu co suc anh huong lon nhat trong do thi: "<<endl;
	for(int i=1;i<=n;i++)
	{
		a[i]=i;
		b1[i]=mtg[i];
	}
	SortMT2();
	for(int i=1;i<=top;i++)
	{
		write<<"So dinh chiu anh huong cua dinh "<<a[i]<<"("<<member1[i]<<") dat nguong "<<threshold<<" : "<<b1[i];
		write<<"\n";
		write<<"Dinh nay anh huong dat nguong toi dinh: "<<"\n";
		write<<affectionTop1[i]<<"\n";
		write<<"Suc anh huong toi tung dinh:\n";
		write<<stringLenPath1[i]<<"\n";
	}
}

vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  return internal;
}

void readMT(string filename)
{
    ifstream readMTLike (filename);
	ifstream readMTLike1 (filename);
	ReplaceStringInPlace(filename, ".txt", "_member.txt" );
	ifstream readMember (filename);
	if(!readMTLike.is_open())
    {
        cout<<"Can't open the file.\n";
        return ;
    }
    else 
	{		
		string line;
		std::getline(readMTLike, line);
		vector<string> sep = split(line, ' ');
		n = sep.size();
		//read the member
		if (readMember.is_open())
		{
			string line1;
			std::getline(readMember, line1);
			vector<string> sep1 = split(line1, '_');
   			for(int i = 0; i < n; i++)
			{
				int	j = i+1;
				member[j] = sep1[i];
				member1[j] = sep1[i];
			}
		}
        for(int i = 1; i <= n; i++)
			for(int j=1;j<=n;j++)
			{
				readMTLike1>>MTLIKE[i][j];
				//spreadRatio[i][j] = 1.0;
			}
    }
    readMTLike.close();
	readMTLike1.close();
	readMember.close();
}

void createMT(string filename)
{
	readMT(filename);
	int i,j;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i==j)
			{
				MTWEIGHTED[i][j]=0;
			}
			else
			{
				if(MTLIKE[i][j]!=0)
				{
					{
						MTWEIGHTED[i][j]=(1.0*MTLIKE[i][j])/MTLIKE[i][i];						
					}
				}
				else
					MTWEIGHTED[i][j]=MTLIKE[i][j];
			}
		}
	}
}


/*Xuat ket qua tim duoc ra man hinh*/
void CalculateLen2(int arrayStack2[1024],int countStack2, int source, int end)
{
	float lenValue = 1.0;
	//printf("%d",Stack2[1]);
	for (int i = 2; i<= countStack2; i++)
	{
		lenValue *= MTWEIGHTED[arrayStack2[i-1]][arrayStack2[i]];
	}
	//cout<<"lenvalue"<<lenValue<<"\n";
	if (LenPath[source][end] == 0)
	{
		LenPath[source][end] = 1 - lenValue;
		m_IsPath[source][end] = true;
	}
	else
	{
		LenPath[source][end] *= ( 1- lenValue); 
		m_IsPath[source][end] = true;
	}
}

/*Kiem tra dinh i co nam trong Stack2, neu co tra ve ket qua 0 va neu khong co tra ve ket qua 1*/
char CheckVertexInStack(int i, int arrayStack2[1024],int countVertex2)
{
	for(int j=1;j<=countVertex2; j++)
	if(i==arrayStack2[j])   return 0;
	return 1;
}

/*Xoa tat ca cac phan tu giong nhau o dau Stack1 va Stack2 khi co duong di hoac gap dinh treo khong the di duoc nua*/
void DeleteArrayVertex(int arrayVertex1[1024],int &countStack1,int arrayVertex2[1024],int &countStack2) 
{
	while(arrayVertex1[countStack1]==arrayVertex2[countStack2]) 
	{
		countStack1--;
		countStack2--;
	}
	countStack2++;
	arrayVertex2[countStack2]=arrayVertex1[countStack1];
}

/*Tim kiem tat ca cac duong di neu co, neu bien Dem>0 thi ton tai duong di va nguoc lai neu Dem=0 thi khong co duong di tu source den end*/
void FindPathTwoVertex2(float A[1024][1024], int source, int end)
{
	int arrayVertex1[1024],arrayVertex2[1024];
	int countStack1=1,countStack2=1, hangVertex;
	int index;

	//init 2 array stack
	arrayVertex1[countStack1]=source;
	arrayVertex2[countStack2]=source;

	while( countStack1>0 && countStack2>0 )
	{
		index = arrayVertex1[countStack1];
		if ( index == end )
		{
			arrayVertex2[0] = source;
			CalculateLen2(arrayVertex2,countStack2, source, end);
			DeleteArrayVertex(arrayVertex1,countStack1,arrayVertex2,countStack2);
		}
		else
		{
			hangVertex = 1; //Gia su ton tai dinh treo

			for(int i=1; i<=n; i++)
				if(A[index][i] > 0 && CheckVertexInStack(i,arrayVertex2,countStack2)==1)
				{
					countStack1++;
					arrayVertex1[countStack1] = i;
					hangVertex = 0;
				}
      
			if(hangVertex==1)
			{
				DeleteArrayVertex(arrayVertex1,countStack1,arrayVertex2,countStack2);
			}
			else 
			{
				countStack2++;
				arrayVertex2[countStack2]=arrayVertex1[countStack1];
			}
			if(arrayVertex2[countStack2]==end)
			{			
				arrayVertex2[0] = source;
				CalculateLen2(arrayVertex2,countStack2, source, end);
				DeleteArrayVertex(arrayVertex1,countStack1,arrayVertex2,countStack2);
			}
		}
	}
}

DWORD WINAPI taske(LPVOID) 
{
	int node=0;
	while(node<n)
	{
		 DWORD dwWaitResult; 
         dwWaitResult = WaitForSingleObject(myMutex, INFINITE);
        switch (dwWaitResult) 
        {
            case WAIT_OBJECT_0: 
            { 
					node = vertex; 
					vertex++;
					ReleaseMutex(myMutex);
					if (node<=n)
					{
						for(int j=1;j<=n;j++)
							if ( node !=j )
							{
								//LenOfTwoVertexDijkstra(node, j, MTWEIGHTED);
								FindPathTwoVertex2(MTWEIGHTED, node, j);
							}
					}

				break; 
			} 
			
			  case WAIT_ABANDONED: 
					 return FALSE; 
        }
   }
	return 0;
}

void handlerResult(float threshold, bool flag, bool sDone)
{
	if ( sDone == false)
	{	
		vertex = 1;
		myMutex = CreateMutex(NULL, FALSE, NULL);           
		if (myMutex == NULL) 
		{
			printf("CreateMutex error: %d\n", GetLastError());
		}
		HANDLE thr[100]; 
		DWORD thrid; 
		for(int i=0;i<CTH;i++)
		{
			thr[i]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)taske,0,0,&thrid);
			if( thr[i] == NULL )
			{
				printf("CreateThread error: %d\n", GetLastError());
			}
		}
		WaitForMultipleObjects(CTH, thr, TRUE, INFINITE);
		for( int i=0; i < CTH; i++ )
			CloseHandle(thr[i]);
		CloseHandle(myMutex);
	}

	for( int i=1; i<=n; i++)
	{
		for( int j=1; j<=n; j++)
		{
			if ( flag == false ) // flag cho pp1
			{
				//if ( LenPath[i][j] > 0 || m_IsPath[i][j] == true )
				if ( m_IsPath[i][j] == true )
				{
					if ( sDone == false )
					{
						LenPath[i][j] = 1 - LenPath[i][j];
					}
					string topValue = IntToString( j );
					affectionTop[i].empty();
					affectionTop[i].append(topValue);
					affectionTop[i].append(" ");
					stringLenPath[i].append(topValue);
					stringLenPath[i].append(" : ");
					stringLenPath[i].append(FloatToString( LenPath[i][j] ));
					stringLenPath[i].append("\n");
				}
			
				//cout<<"LenPath["<<i<<"]["<<j<<"]"<<LenPath[i][j]<<"\n";
				LenSum[i] += LenPath[i][j];
			}
			else // pp2
			{
				//if ( LenPath[i][j] > 0 || m_IsPath[i][j] == true )
				if ( m_IsPath[i][j] == true )
				{
					if ( sDone == false )
					{
						LenPath[i][j] = 1 - LenPath[i][j];
					}
				}
				if ( LenPath[i][j] >= threshold )
				{
					string topValue = IntToString( j );
					affectionTop1[i].empty();
					affectionTop1[i].append(topValue);
					affectionTop1[i].append(" ");
					effect[i].push_back(j);
					numOfEffect[i]++;
					stringLenPath1[i].append(topValue);
					stringLenPath1[i].append(" : ");
					stringLenPath1[i].append(FloatToString( LenPath[i][j] ));
					stringLenPath1[i].append("\n");
				}
			}
		}
	}
}

void CKeyplayers_GUIDlg::OnBnClickedBtnOpenfile()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrTitle = L"Choose the input file";
	dlg.m_ofn.lpstrInitialDir = L"E:\\DATA\\Study\\social network\\Coding\\BAO CAO\\Source Code\\data_test";
	if ( dlg.DoModal() == IDOK)
	{
		m_sFileIn = dlg.m_ofn.lpstrFile;
		UpdateData(FALSE);
	}
}

void CKeyplayers_GUIDlg::OnBnClickedBtnPp1()
{
	// TODO: Add your control notification handler code here
	if ( m_sPp1Done == false )
	{
		UpdateData(TRUE);
		time_t rawtime;
		time(&rawtime);	
		CString tempTime = (CString)ctime(&rawtime);
		SetDlgItemText(IDC_START_TIME1,tempTime);
		SetDlgItemText(IDC_STATUS1, L"Đang xử lý...");
		int top;
		top = _tstoi(m_sNumOfKey);
		float l_threshold;
		l_threshold = _tstof(m_sThreshold);
		if ( ProcessFiles(m_sFileIn, top, l_threshold, false, false ) == TRUE)
		{
			// Convert a TCHAR string to a LPCSTR
			CT2CA pszConvertedAnsiString (m_sFileIn);
			// construct a std::string using the LPCSTR input
			string strMtLike (pszConvertedAnsiString);
			//TRACE("ket qua tra ve là : [%s]\n", strStd.c_str());
			createMT(strMtLike);
			if ( ProcessFiles(m_sFileIn, top, l_threshold, false, true ) == TRUE)
			{
				handlerResult(l_threshold, false, m_sDone);
				writeMT(strMtLike, LenSum, top);
		
				//CString m_sResult = L"Danh sach " + m_sNumOfKey + L" phan tu co suc anh huong lon nhat trong do thi:\n" ;
				CString m_sResult;
				for(int i=1;i<=top;i++)
				{
					CString aStr, memberStr, bStr ;
					aStr.Format(L"%d", a[i]);
					memberStr.Format(L"%s", member[i].c_str());
					bStr.Format(L"%f", b[i]);
					//CString m_sResultTemp = L"    " + aStr + L" (" + memberStr + L")           " + bStr + L"\r\n";
					if (aStr.GetLength() == 4 )
					{
						m_sResult += L"          " + aStr + L"                            " + bStr + L"\r\n";
					}
					if (aStr.GetLength() == 3 )
					{
						m_sResult += L"          " + aStr + L"                              " + bStr + L"\r\n";
					}
					else if (aStr.GetLength() == 2 )
					{
						m_sResult += L"          " + aStr + L"                                " + bStr + L"\r\n";
					}
					else
					{
						m_sResult += L"          " + aStr + L"                                  " + bStr + L"\r\n";
					}
				}
				SetDlgItemText(IDC_EDIT_KQ_PP1, m_sResult);
				m_sDone = true;
				m_sPp1Done = true;
				SetDlgItemText(IDC_STATUS1, L"Đã xong!");
				time(&rawtime);
				CString tempTime = (CString)ctime(&rawtime);
				SetDlgItemText(IDC_END_TIME1,tempTime);
			}
		}
	}
	else
	{
		MessageBox(L"Đã tính xong", L"Information", MB_OK | MB_ICONINFORMATION);
	}
}

BOOL CKeyplayers_GUIDlg::ProcessFiles(CString sFileIn, int top, float threshold, bool flagPp, bool loadFile)
{
	if (loadFile == false)
	{
		CFile fileIn;
		if ( fileIn.Open(sFileIn, CFile::modeRead) == FALSE )
		{
			CString sMsg;
			sMsg.Format(L"Không thể mở File %s", sFileIn);
			MessageBox(sMsg, L"Error", MB_OK | MB_ICONERROR);
			return FALSE;
		}
		if (top < 1 ) 
		{
			CString sMsg;
			sMsg.Format(L"Vui lòng kiểm tra số lượng Keyplayers");
			MessageBox(sMsg, L"Error", MB_OK | MB_ICONERROR);
			return FALSE;
		}
		if ( flagPp == true )
		{
			if ( threshold <= 0 || threshold > 1)
			{
				CString sMsg;
				sMsg.Format(L"Vui lòng kiểm tra giá trị ngưỡng");
				MessageBox(sMsg, L"Error", MB_OK | MB_ICONERROR);
				return FALSE;
			}
		}
		int a;
		fileIn.Read(&a, sizeof(int));
	}
	else
	{
		if (top < 1 || top > n) 
		{
			CString sMsg;
			sMsg.Format(L"Vui lòng kiểm tra số lượng Keyplayers");
			MessageBox(sMsg, L"Error", MB_OK | MB_ICONERROR);
			return FALSE;
		}		
	}
	return TRUE;
}

void CKeyplayers_GUIDlg::OnBnClickedBtnPp2()
{
	// TODO: Add your control notification handler code here
	if ( m_sPp2Done == false )
	{
		UpdateData(TRUE);
		time_t rawtime;
		time(&rawtime);	
		CString tempTime = (CString)ctime(&rawtime);
		SetDlgItemText(IDC_START_TIME2,tempTime);
		SetDlgItemText(IDC_STATUS2, L"Đang xử lý...");
		float l_threshold;
		l_threshold = _tstof(m_sThreshold);
		int top;
		top = _tstoi(m_sNumOfKey);
		if ( ProcessFiles(m_sFileIn, top, l_threshold, true, false) == TRUE)
		{
			// Convert a TCHAR string to a LPCSTR
			CT2CA pszConvertedAnsiString (m_sFileIn);
			// construct a std::string using the LPCSTR input
			string strMtLike (pszConvertedAnsiString);			
			//TRACE("ket qua tra ve là : [%s]\n", strStd.c_str());
			if ( m_sDone == false)
			{
				createMT(strMtLike);
			}
			if ( ProcessFiles(m_sFileIn, top, l_threshold, true, true ) == TRUE)
			{
				handlerResult(l_threshold, true, m_sDone);
				writeMT2(strMtLike, numOfEffect, top, l_threshold);
				CString m_sResult;
				for(int i=1;i<=top;i++)
				{
					CString aStr, memberStr, bStr ;
					aStr.Format(L"%d", a[i]);
					memberStr.Format(L"%s", member1[i].c_str());
					bStr.Format(L"%d", b1[i]);
					//CString m_sResultTemp = L"    " + aStr + L" (" + memberStr + L")           " + bStr + L"\r\n";
					if (aStr.GetLength() == 4 )
					{
						m_sResult += L"          " + aStr + L"                               " + bStr + L"\r\n";
					}
					if (aStr.GetLength() == 3 )
					{
						m_sResult += L"          " + aStr + L"                                 " + bStr + L"\r\n";
					}
					else if (aStr.GetLength() == 2 )
					{
						m_sResult += L"          " + aStr + L"                                   " + bStr + L"\r\n";
					}
					else
					{
						m_sResult += L"          " + aStr + L"                                     " + bStr + L"\r\n";
					}
				}
				SetDlgItemText(IDC_EDIT_KQ_PP2, m_sResult);
				m_sDone = true;
				m_sPp2Done = true;
				SetDlgItemText(IDC_STATUS2, L"Đã xong!");
				time(&rawtime);
				CString tempTime = (CString)ctime(&rawtime);
				SetDlgItemText(IDC_END_TIME2,tempTime);
			}
		}
	}
	else
	{
		MessageBox(L"Đã tính xong", L"Information", MB_OK | MB_ICONINFORMATION);
	}
}

void CKeyplayers_GUIDlg::OnBnClickedBtnAbout()
{
	// TODO: Add your control notification handler code here
	MessageBox(L"Xác định Keyplayers v1.0\r\nCH1301114 - Huỳnh Thanh Việt", L"Information", MB_OK | MB_ICONINFORMATION);
}


void CKeyplayers_GUIDlg::OnBnClickedBtnExit()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}



void CKeyplayers_GUIDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	if (n>0)
	{
		vertex = 0;
		for( int i = 0; i<=n; i++)
		{
			a[i] = 0;
			numOfEffect[i] = 0;
			b1[i] = 0;
			b[i] = 0.0;
			member[i] = "";
			member1[i] = "";
			affectionTop[i] ="";
			stringLenPath[i] = "";
			affectionTop1[i] = "";
			stringLenPath1[i] = "";
			LenSum[i] = 0.0;
			m_sDone = false;
			m_sPp1Done = false;
			m_sPp2Done = false;
			for ( int j = 0; j<=n; j++)
			{
				MTLIKE[i][j] = 0;
				MTWEIGHTED[i][j] = 0.0;
				LenPath[i][j] = 0.0;
				m_IsPath[i][j] = false;
				//effect[i][j] = 0;
			}
		}
		n = 0;
		CString temp;
		temp.Format(L"%s", "");
		UpdateData(FALSE);
		SetDlgItemText(IDC_EDIT_KQ_PP2, temp);
		SetDlgItemText(IDC_STATUS2, temp);
		SetDlgItemText(IDC_START_TIME2,temp);
		SetDlgItemText(IDC_END_TIME2,temp);

		SetDlgItemText(IDC_EDIT_KQ_PP1, temp);
		SetDlgItemText(IDC_STATUS1, temp);
		SetDlgItemText(IDC_START_TIME1,temp);
		SetDlgItemText(IDC_END_TIME1,temp);

		SetDlgItemText(IDC_EDIT_FILEIN, temp);
		SetDlgItemText(IDC_EDIT_NUM_KEY, temp);
		SetDlgItemText(IDC_EDIT_THRESHOLD, temp);
		m_sFileIn = "";
		m_sNumOfKey = "";
		m_sThreshold = "";
		m_sResult1 = "";
	}
}
