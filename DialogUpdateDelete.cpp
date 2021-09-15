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
	CString message, caption;
	if (dbControl.OpenConnection()) {
		CRecordset recordset(&dbControl.database);

		//Open recordset and check if specified ID exists in database
		if (recordset.Open(CRecordset::forwardOnly, _T("SELECT * FROM UserData WHERE DataID=") + dataID, CRecordset::readOnly)) {
			if (recordset.IsEOF()) {
				message.LoadString(IDS_NODATAID);
				caption.LoadString(IDS_CAPTIONERRORMSGBOX);
				MessageBox(message, caption, MB_OK);
				recordset.Close();
				dbControl.CloseConnection();
				return;
			}
		}
		else {
			message.LoadString(IDS_RSOPENERROR);
			caption.LoadString(IDS_CAPTIONERRORMSGBOX);
			MessageBox(message, caption, MB_OK);
			recordset.Close();
			dbControl.CloseConnection();
			return;
		}

		dbControl.ExecuteSQLCommand(_T("DELETE * FROM UserData WHERE DataID=") + dataID);
		dbControl.ExecuteSQLCommand(_T("DELETE * FROM LastAccessed WHERE DataID=") + dataID);
		SetDlgItemText(IDC_EDIT_DATAIDDELETE, 0);
		message.LoadString(IDS_OKDELETEDATAMSG);
		caption.LoadString(IDS_CAPTIONSUCCESSMSGBOX);
		MessageBox(message, caption, MB_OK);
		recordset.Close();
		dbControl.CloseConnection();
		return;
	}
	message.LoadString(IDS_DBCONNECTERRORMSG);
	caption.LoadString(IDS_CAPTIONERRORMSGBOX);
	MessageBox(message, caption, MB_OK);
}

void DialogUpdateDelete::OnBtnUpdateClicked()
{
	DatabaseControl dbControl;
	CString message, caption;
	if (dbControl.OpenConnection()) {
		CString dataID, firstName, surname, username, email, password, platform;
		CRecordset recordset(&dbControl.database);

		GetDlgItemText(IDC_EDIT_DATAIDUPDATE, dataID); GetDlgItemText(IDC_EDIT_FIRSTNAMEUPDATE, firstName);
		GetDlgItemText(IDC_EDIT_SURNAMEUPDATE, surname); GetDlgItemText(IDC_EDIT_USERNAMEUPDATE, username);
		GetDlgItemText(IDC_EDIT_EMAILUPDATE, email); GetDlgItemText(IDC_EDIT_PASSWORDUPDATE, password);
		GetDlgItemText(IDC_EDIT_PLATFORMUPDATE, platform);
		if (dataID == "") {
			
			message.LoadString(IDS_DATAIDEMPTY);
			caption.LoadString(IDS_CAPTIONERRORMSGBOX);
			MessageBox(message, caption, MB_OK);
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
			message.LoadString(IDS_RSOPENERROR);
			caption.LoadString(IDS_CAPTIONERRORMSGBOX);
			MessageBox(message, caption, MB_OK);
			return;
		}

		//Wrap values in ' ' so they can be used in UPDATE statement
		firstName = '\'' + firstName + '\'';
		surname = '\'' + surname + '\'';
		username = '\'' + username + '\'';
		email = '\'' + email + '\'';
		password = '\'' + password + '\'';
		platform = '\'' + platform + '\'';

		//Get current time
		auto time = std::chrono::system_clock::now();
		std::time_t time_to_timet = std::chrono::system_clock::to_time_t(time);
		CString timeOperated(std::ctime(&time_to_timet));
		timeOperated = '\'' + timeOperated + '\'';

		//Update user data
		dbControl.ExecuteSQLCommand((_T("UPDATE UserData SET FirstName=" + firstName) +
			_T(", Surname=" + surname) + _T(", Username=" + username) + _T(", Email=" + email) +
			_T(", Password=" + password) + _T(", Platform=" + platform) + _T(" WHERE DataID=" + dataID)));

		//Update LastAccessed table with the dataID thats been updated
		dbControl.ExecuteSQLCommand(_T("UPDATE LastAccessed SET LastAccess=" + timeOperated) + _T(", LatestOperation='Updated' WHERE DataID=" + dataID));

		message.LoadString(IDS_OKUPDATEDATAMSG);
		caption.LoadString(IDS_CAPTIONSUCCESSMSGBOX);
		MessageBox(message, caption, MB_OK);
	}
}


void DialogUpdateDelete::OnClose()
{
	CDialogEx::OnClose();
}



void DialogUpdateDelete::OnBtnBackClicked()
{
	EndDialog(IDCANCEL);
}

