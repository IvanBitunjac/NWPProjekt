// DialogRetrieveData.cpp : implementation file
//

#include "pch.h"
#include "NWPProjekt.h"
#include "DialogRetrieveData.h"
#include "afxdialogex.h"
#include <string>


// DialogRetrieveData dialog

IMPLEMENT_DYNAMIC(DialogRetrieveData, CDialogEx)

DialogRetrieveData::DialogRetrieveData(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RETRIEVEDATA, pParent)
{

}

DialogRetrieveData::~DialogRetrieveData()
{
}

void DialogRetrieveData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATALIST, queryListbox);
}


BEGIN_MESSAGE_MAP(DialogRetrieveData, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &DialogRetrieveData::OnBtnSearchClicked)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &DialogRetrieveData::OnBtnBackClicked)
	ON_BN_CLICKED(IDC_BUTTON_SEARCHALL, &DialogRetrieveData::OnBtnGetAllClicked)
END_MESSAGE_MAP()


// DialogRetrieveData message handlers


void DialogRetrieveData::OnBtnSearchClicked()
{
	SearchDatabase(SearchType::Specific);
}

void DialogRetrieveData::OnBtnGetAllClicked()
{
	SearchDatabase(SearchType::All);
}

// If searchType = All -> Get all records, if searchType = specific -> Get search text and then perform query
void DialogRetrieveData::SearchDatabase(SearchType searchType)
{
	DatabaseControl dbControl;
	CString message, caption;
	if (!dbControl.OpenConnection()) {
		message.LoadString(IDS_DBCONNECTERRORMSG);
		caption.LoadString(IDS_CAPTIONERRORMSGBOX);
		MessageBox(message, caption, MB_OK);
		return;
	}
	CRecordset recordSet(&dbControl.database);
	CString dataID, firstName, surname, username, email, password, platform, lastAccess, latestOp;
	queryListbox.ResetContent();

	if (searchType == SearchType::All) {
		if (!recordSet.Open(CRecordset::forwardOnly, _T("SELECT * FROM UserData"), CRecordset::readOnly)) {
			message.LoadString(IDS_RSOPENERROR);
			caption.LoadString(IDS_CAPTIONERRORMSGBOX);
			MessageBox(message, caption, MB_OK);
			return;
		}
	}
	else {
		CString search;
		GetDlgItemText(IDC_EDIT_SEARCH, search);
		search = _T('\'') + search + _T('\'');
		if (!recordSet.Open(CRecordset::forwardOnly, _T("SELECT * FROM UserData WHERE Platform=") + search, CRecordset::readOnly)) {
			message.LoadString(IDS_RSOPENERROR);
			caption.LoadString(IDS_CAPTIONERRORMSGBOX);
			MessageBox(message, caption, MB_OK);
			return;
		}
	}

	int listboxIndex = 0;
	while (!recordSet.IsEOF()) {
		CRecordset recordLastAccess(&dbControl.database);
		recordSet.GetFieldValue(L"DataID", dataID);
		recordSet.GetFieldValue(L"FirstName", firstName);
		recordSet.GetFieldValue(L"Surname", surname);
		recordSet.GetFieldValue(L"Username", username);
		recordSet.GetFieldValue(L"Email", email);
		recordSet.GetFieldValue(L"Password", password);
		recordSet.GetFieldValue(L"Platform", platform);

		recordLastAccess.Open(CRecordset::forwardOnly, _T("SELECT LastAccess, LatestOperation FROM LastAccessed WHERE DataID=" + dataID), CRecordset::readOnly);

		recordLastAccess.GetFieldValue(L"LastAccess", lastAccess);
		recordLastAccess.GetFieldValue(L"LatestOperation", latestOp);

		queryListbox.InsertString(listboxIndex, _T("DataID: ") + dataID); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, _T("FirstName: ") + firstName); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, _T("Surname: ") + surname); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, _T("Username: ") + username); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, _T("E-mail: ") + email); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, _T("Password: ") + password); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, _T("Platform: ") + platform); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, _T("Last accessed: ") + lastAccess); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, _T("Last operation: ") + latestOp); ++listboxIndex;

		queryListbox.InsertString(listboxIndex, _T("<---------------->")); ++listboxIndex;

		recordSet.MoveNext();
	}
}

void DialogRetrieveData::OnBtnBackClicked()
{
	this->EndDialog(IDCANCEL);
}

