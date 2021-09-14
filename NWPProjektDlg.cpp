
// NWPProjektDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "NWPProjekt.h"
#include "NWPProjektDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CNWPProjektDlg dialog



CNWPProjektDlg::CNWPProjektDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_START, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNWPProjektDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNWPProjektDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SAVEDATA, &CNWPProjektDlg::OnBtnSaveDataClicked)
	ON_BN_CLICKED(IDC_BUTTON_RETRIEVEDATA, &CNWPProjektDlg::OnBtnRetrieveDataClicked)
	ON_BN_CLICKED(IDC_BUTTON_CREATETABLES, &CNWPProjektDlg::OnBtnCreateTablesClicked)
	ON_BN_CLICKED(IDC_BUTTON_UPDATEDELETE, &CNWPProjektDlg::OnBtnUpdateDeleteClicked)
END_MESSAGE_MAP()


// CNWPProjektDlg message handlers

BOOL CNWPProjektDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Extra initialization

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNWPProjektDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNWPProjektDlg::OnPaint()
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
HCURSOR CNWPProjektDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNWPProjektDlg::OnBtnSaveDataClicked()
{
	DialogSaveData dlgSaveData;
	CString message, caption;
	message.LoadString(IDS_DLGOPENERROR);
	message.LoadString(IDS_CAPTIONERRORMSGBOX);
	if (dlgSaveData.DoModal() == -1) MessageBox(message, caption, MB_OK);
}


void CNWPProjektDlg::OnBtnRetrieveDataClicked()
{
	DialogRetrieveData dlgRetrieveData;
	CString message, caption;
	message.LoadString(IDS_DLGOPENERROR);
	message.LoadString(IDS_CAPTIONERRORMSGBOX);
	if (dlgRetrieveData.DoModal() == -1) MessageBox(message, caption, MB_OK);
}



void CNWPProjektDlg::OnBtnCreateTablesClicked()
{
	DatabaseControl dbControl;
	CString message, caption;
	dbControl.OpenConnection();
	dbControl.ExecuteSQLCommand((CString)"CREATE TABLE UserData(" + (CString)"DataID AUTOINCREMENT, " + (CString)"FirstName TEXT(20), " +
		(CString)"Surname TEXT(25)," + (CString)"Username TEXT(25), " + (CString)"Email TEXT(30)," + (CString)"Password TEXT(20)," +
		(CString)"Platform TEXT(30))");

	dbControl.ExecuteSQLCommand((CString)"CREATE TABLE LastAccessed(" + (CString)"DataID INTEGER, " + (CString)"LastAccess TEXT(40), " +
		(CString)"LatestOperation TEXT(10))");

	message.LoadString(IDS_CREATETABLEOKMSG);
	caption.LoadString(IDS_CAPTIONSUCCESSMSGBOX);
	MessageBox(message, caption, MB_OK);
	dbControl.CloseConnection();
}


void CNWPProjektDlg::OnBtnUpdateDeleteClicked()
{
	DialogUpdateDelete dlgUpdateDelete;
	CString message, caption;
	message.LoadString(IDS_DLGOPENERROR);
	message.LoadString(IDS_CAPTIONERRORMSGBOX);
	if (dlgUpdateDelete.DoModal() == -1) MessageBox(message, caption, MB_OK);
}
