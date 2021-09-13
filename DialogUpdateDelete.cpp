// DialogUpdateDelete.cpp : implementation file
//

#include "pch.h"
#include "NWPProjekt.h"
#include "DialogUpdateDelete.h"
#include "afxdialogex.h"

// DialogUpdateDelete dialog

IMPLEMENT_DYNAMIC(DialogUpdateDelete, CDialogEx)

DialogUpdateDelete::DialogUpdateDelete(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPDATEDELETE_DATA, pParent)
{

}

DialogUpdateDelete::~DialogUpdateDelete()
{
}

void DialogUpdateDelete::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogUpdateDelete, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &DialogUpdateDelete::OnBtnDeleteClicked)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_UPDATEDELETE_BACK, &DialogUpdateDelete::OnBtnBackClicked)
	ON_BN_CLICKED(IDC_BUTTON_UPDATEDATA, &DialogUpdateDelete::OnBtnUpdateClicked)
END_MESSAGE_MAP()


// DialogUpdateDelete message handlers


void DialogUpdateDelete::OnBtnDeleteClicked()
{
	DatabaseControl dbControl;
	CString dataID;
	GetDlgItemText(IDC_EDIT_DATAIDDELETE, dataID);
	if (dbControl.OpenConnection()) {
		CRecordset recordset(&dbControl.database);

		//Open recordset and check if specified ID exists in database
		if (recordset.Open(CRecordset::forwardOnly, (CString)"SELECT * FROM UserData WHERE DataID=" + dataID, CRecordset::readOnly)) {
			if (recordset.IsEOF()) {
				MessageBox((CString)"No data with such ID!", (CString)"Error", MB_OK);
				recordset.Close();
				dbControl.CloseConnection();
				return;
			}
		}
		else {
			MessageBox((CString)"Could not open Recordset to check if specified ID exists!", (CString)"Error", MB_OK);
			recordset.Close();
			dbControl.CloseConnection();
			return;
		}

		dbControl.ExecuteSQLCommand((CString)"DELETE * FROM UserData WHERE DataID=" + dataID);
		dbControl.ExecuteSQLCommand((CString)"DELETE * FROM LastAccess WHERE DataID=" + dataID);
		SetDlgItemText(IDC_EDIT_DATAIDDELETE, 0);
		MessageBox((CString)"Success deleting data!", (CString)"Success", MB_OK);
		recordset.Close();
		dbControl.CloseConnection();
		return;
	}
	MessageBox((CString)"Could not connect to database!", (CString)"Error connecting", MB_OK);
}

void DialogUpdateDelete::OnBtnUpdateClicked()
{
	DatabaseControl dbControl;
	if (dbControl.OpenConnection()) {
		CString dataID, firstName, surname, username, email, password, platform;
		CRecordset recordset(&dbControl.database);

		GetDlgItemText(IDC_EDIT_DATAIDUPDATE, dataID); GetDlgItemText(IDC_EDIT_FIRSTNAMEUPDATE, firstName);
		GetDlgItemText(IDC_EDIT_SURNAMEUPDATE, surname); GetDlgItemText(IDC_EDIT_USERNAMEUPDATE, username);
		GetDlgItemText(IDC_EDIT_EMAILUPDATE, email); GetDlgItemText(IDC_EDIT_PASSWORDUPDATE, password);
		GetDlgItemText(IDC_EDIT_PLATFORMUPDATE, platform);
		if (dataID == "") {
			MessageBox((CString)"DataID cannot be empty!", (CString)"Error", MB_OK);
			return;
		}
		CString recordsetQuery("SELECT * FROM UserData WHERE DataID=");
		if (recordset.Open(CRecordset::forwardOnly, recordsetQuery + dataID, CRecordset::readOnly)) {
			//Check if any edit controls are empty, if yes set with values from DB so they dont become NULL
			if (firstName == "") recordset.GetFieldValue(L"FirstName", firstName);
			if (surname == "") recordset.GetFieldValue(L"Surname", surname);
			if (username == "") recordset.GetFieldValue(L"Username", username);
			if (email == "") recordset.GetFieldValue(L"Email", email);
			if (password == "") recordset.GetFieldValue(L"Password", password);
			if (platform == "") recordset.GetFieldValue(L"Platform", platform);
		}
		else {
			MessageBox((CString)"Could not open Recordset!", (CString)"Error", MB_OK);
			return;
		}

		//Wrap values in ' ' so they can be used in UPDATE statement
		firstName.Insert(0, '\''); firstName.Insert(firstName.GetLength() + 1, '\'');
		surname.Insert(0, '\''); surname.Insert(surname.GetLength() + 1, '\'');
		username.Insert(0, '\''); username.Insert(username.GetLength() + 1, '\'');
		email.Insert(0, '\''); email.Insert(email.GetLength() + 1, '\'');
		password.Insert(0, '\''); password.Insert(password.GetLength() + 1, '\'');
		platform.Insert(0, '\''); platform.Insert(platform.GetLength() + 1, '\'');

		//Get current time
		auto time = std::chrono::system_clock::now();
		std::time_t time_to_timet = std::chrono::system_clock::to_time_t(time);
		CString timeOperated(std::ctime(&time_to_timet));
		timeOperated.Insert(0, '\''); timeOperated.Insert(timeOperated.GetLength() + 1, L"\'");

		//Update user data
		dbControl.ExecuteSQLCommand((CString)"UPDATE UserData SET FirstName=" + firstName +
			(CString)", Surname=" + surname + (CString)", Username=" + username + (CString)", Email=" + email +
			(CString)", Password=" + password + (CString)", Platform=" + platform + (CString)" WHERE DataID=" + dataID);

		//Update LastAccessed table with the dataID thats been updated
		dbControl.ExecuteSQLCommand((CString)"UPDATE LastAccessed SET LastAccess=" +
			timeOperated + (CString)", LatestOperation='Updated' WHERE DataID=" + dataID);

		MessageBox((CString)"Success updating data!", (CString)"Success", MB_OK);
	}
}


void DialogUpdateDelete::OnClose()
{
	CDialogEx::OnClose();
}



void DialogUpdateDelete::OnBtnBackClicked()
{
	PostMessage(WM_CLOSE, 0, 0);
}

