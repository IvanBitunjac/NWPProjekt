// DialogRetrieveData.cpp : implementation file
//

#include "pch.h"
#include "NWPProjekt.h"
#include "DialogRetrieveData.h"
#include "afxdialogex.h"


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
	ON_BN_CLICKED(IDC_BUTTON_SEARCHALL, &DialogRetrieveData::OnBtnSearchAllClicked)
END_MESSAGE_MAP()


// DialogRetrieveData message handlers


void DialogRetrieveData::OnBtnSearchClicked()
{
	queryListbox.ResetContent();
	DatabaseControl dbControl;
	if (!dbControl.OpenConnection()) {
		MessageBox((CString)"Could not connect to database!", (CString)"Error connecting", MB_OK);
		return;
	}
	CRecordset recordSet(&dbControl.database);
	CRecordset recordLastAccess(&dbControl.database);
	CString dataID, firstName, surname, username, email, password, platform, lastAccess, latestOp;
	CString search;
	GetDlgItemText(IDC_EDIT_SEARCH, search);
	if (search == "") {
		MessageBox((CString)"Search is empty!", (CString)"Empty", MB_OK);
		dbControl.CloseConnection();
		return;
	}
	search.Insert(0, '\''); search.Insert(search.GetLength() + 1, '\'');
	if (!recordSet.Open(CRecordset::forwardOnly, (CString)"SELECT * FROM UserData WHERE Platform=" + search, CRecordset::readOnly)) {
		MessageBox((CString)"Cant open Recordset for UserData table!", (CString)"Error", MB_OK);
		dbControl.CloseConnection();
		recordSet.Close();
		return;
	}


	int listboxIndex = 0;
	while (!recordSet.IsEOF()) {
		recordSet.GetFieldValue(L"DataID", dataID);
		recordSet.GetFieldValue(L"FirstName", firstName);
		recordSet.GetFieldValue(L"Surname", surname);
		recordSet.GetFieldValue(L"Username", username);
		recordSet.GetFieldValue(L"Email", email);
		recordSet.GetFieldValue(L"Password", password);
		recordSet.GetFieldValue(L"Platform", platform);

		if (recordLastAccess.IsOpen()) recordLastAccess.Requery();
		else recordLastAccess.Open(CRecordset::forwardOnly, (CString)"SELECT LastAccessed, LatestOperation FROM LastAccessed WHERE DataID=" +
			dataID, CRecordset::readOnly);	

		recordLastAccess.GetFieldValue(L"LastAccessed", lastAccess);
		recordLastAccess.GetFieldValue(L"LatestOperation", latestOp);

		queryListbox.InsertString(listboxIndex, (CString)"DataID: " + dataID); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"FirstName: " + firstName); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"Surname: " + surname); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"Username: " + username); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"E-mail: " + email); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"Password: " + password); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"Platform: " + platform); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"Last accessed: " + lastAccess); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"Last operation: " + latestOp); ++listboxIndex;

		queryListbox.InsertString(listboxIndex, (CString)""); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"<---------------->"); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)""); ++listboxIndex;

		recordSet.MoveNext();
	}
	recordSet.Close();
	recordLastAccess.Close();
	dbControl.CloseConnection();
}

void DialogRetrieveData::OnBtnSearchAllClicked()
{
	DatabaseControl dbControl;
	if (!dbControl.OpenConnection()) {
		MessageBox((CString)"Could not connect to database!", (CString)"Error connecting", MB_OK);
		return;
	}
	CRecordset recordSet(&dbControl.database);
	CRecordset recordLastAccess(&dbControl.database);
	CString dataID, firstName, surname, username, email, password, platform, lastAccess, latestOp;

	queryListbox.ResetContent();
	CRecordset recordset(&dbControl.database);

	if (!recordSet.Open(CRecordset::forwardOnly, (CString)"SELECT * FROM UserData", CRecordset::readOnly)) {
		MessageBox((CString)"Cant open Recordset for UserData table!", (CString)"Error", MB_OK);
		dbControl.CloseConnection();
		recordSet.Close();
		return;
	}

	int listboxIndex = 0;
	while (!recordSet.IsEOF()) {
		recordSet.GetFieldValue(L"DataID", dataID);
		recordSet.GetFieldValue(L"FirstName", firstName);
		recordSet.GetFieldValue(L"Surname", surname);
		recordSet.GetFieldValue(L"Username", username);
		recordSet.GetFieldValue(L"Email", email);
		recordSet.GetFieldValue(L"Password", password);
		recordSet.GetFieldValue(L"Platform", platform);

		if (recordLastAccess.IsOpen()) recordLastAccess.Requery();
		else recordLastAccess.Open(CRecordset::forwardOnly, (CString)"SELECT LastAccessed, LatestOperation FROM LastAccessed WHERE DataID=" +
			dataID, CRecordset::readOnly);

		recordLastAccess.GetFieldValue(L"LastAccessed", lastAccess);
		recordLastAccess.GetFieldValue(L"LatestOperation", latestOp);

		queryListbox.InsertString(listboxIndex, (CString)"DataID: " + dataID); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"FirstName: " + firstName); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"Surname: " + surname); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"Username: " + username); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"E-mail: " + email); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"Password: " + password); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"Platform: " + platform); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"Last accessed: " + lastAccess); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"Last operation: " + latestOp); ++listboxIndex;

		queryListbox.InsertString(listboxIndex, (CString)""); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)"<---------------->"); ++listboxIndex;
		queryListbox.InsertString(listboxIndex, (CString)""); ++listboxIndex;

		recordSet.MoveNext();
	}
	recordSet.Close();
	recordLastAccess.Close();
	dbControl.CloseConnection();
}

void DialogRetrieveData::OnBtnBackClicked()
{
	// TODO: Add your control notification handler code here
	this->EndDialog(0);
}

