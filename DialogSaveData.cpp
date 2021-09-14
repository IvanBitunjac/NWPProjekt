// DialogSaveData.cpp : implementation file
//

#include "pch.h"
#include "NWPProjekt.h"
#include "DialogSaveData.h"
#include "afxdialogex.h"


// DialogSaveData dialog

IMPLEMENT_DYNAMIC(DialogSaveData, CDialogEx)

DialogSaveData::DialogSaveData(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SAVE_DATA, pParent)
{
	
}

DialogSaveData::~DialogSaveData()
{
}

void DialogSaveData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogSaveData, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &DialogSaveData::OnBtnBackClicked)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SAVE_DATA, &DialogSaveData::OnBtnSaveDataClicked)
END_MESSAGE_MAP()


// DialogSaveData message handlers


void DialogSaveData::OnBtnBackClicked()
{
	PostMessage(WM_CLOSE, 0, 0);
}

void DialogSaveData::OnClose()
{
	CString editName, editSurname, editUsername, editEmail, editPassword, editPlatform;
	CString message, caption;

	//Get edit controls text
	GetDlgItemText(IDC_EDIT_NAME, editName); GetDlgItemText(IDC_EDIT_SURNAME, editSurname); GetDlgItemText(IDC_EDIT_USERNAME, editUsername);
	GetDlgItemText(IDC_EDIT_EMAIL, editEmail); GetDlgItemText(IDC_EDIT_PASSWORD, editPassword); GetDlgItemText(IDC_EDIT_PLATFORM, editPlatform);

	//Check if any edit controls contain text
	if (editName != "" || editSurname != "" || editUsername != "" || editEmail != "" || editPassword != "" || editPlatform != "") {
		message.LoadString(IDS_CLOSEDIALOGMSG);
		caption.LoadString(IDS_EXIT);
		int result = MessageBox(message, caption, MB_YESNO);
		switch (result) {
		case IDNO:
			break;
		case IDYES:
			CDialogEx::OnClose();
			break;
		default:
			return;
		}
	}
	else {
		CDialogEx::OnClose();
	}
}

void DialogSaveData::OnBtnSaveDataClicked()
{
	DatabaseControl dbControl;
	CString firstName, surname, username, email, password, platform;
	CString message, caption;

	//Get all edit control values
	GetDlgItemText(IDC_EDIT_NAME, firstName); GetDlgItemText(IDC_EDIT_SURNAME, surname); GetDlgItemText(IDC_EDIT_USERNAME, username);
	GetDlgItemText(IDC_EDIT_EMAIL, email); GetDlgItemText(IDC_EDIT_PASSWORD, password); GetDlgItemText(IDC_EDIT_PLATFORM, platform);

	if (!dbControl.OpenConnection()) { 
		message.LoadString(IDS_DBCONNECTERRORMSG);
		caption.LoadString(IDS_CAPTIONERRORMSGBOX);
		MessageBox(message, caption, MB_OK);
		return;
	}

	if (platform == "") {
		message.LoadString(IDS_PLATFORMOTHERSEMPTY);
		caption.LoadString(IDS_CAPTIONERRORMSGBOX);
		MessageBox(message, caption, MB_OK);
		dbControl.CloseConnection();
		return;
	}

	//Wrap values in ' ' so they can be used for INSERT query
	firstName.Insert(0, '\''); firstName.Insert(firstName.GetLength() + 1, L"\', ");
	surname.Insert(0, '\''); surname.Insert(surname.GetLength() + 1, L"\', ");
	username.Insert(0, '\''); username.Insert(username.GetLength() + 1, L"\', ");
	email.Insert(0, '\''); email.Insert(email.GetLength() + 1, L"\', ");
	password.Insert(0, '\''); password.Insert(password.GetLength() + 1, L"\', ");
	platform.Insert(0, '\''); platform.Insert(platform.GetLength() + 1, '\''); //Skip adding ',' on last edit

	//Insert into UserData table
	CString insert("INSERT INTO UserData(FirstName, Surname, Username, Password, Email, Platform)");
	CString values = _T(" VALUES(" + firstName + surname + username + email + password + platform + ")");
	dbControl.ExecuteSQLCommand(insert + values);

	CRecordset recordset(&dbControl.database);
	if (recordset.Open(CRecordset::forwardOnly, (CString)"SELECT Last(DataID) as DataIDNum FROM UserData", CRecordset::readOnly)) {
		CString dataID;
		recordset.GetFieldValue(L"DataIDNum", dataID);

		//Get current time and convert to CString
		auto time = std::chrono::system_clock::now();
		std::time_t time_to_timet = std::chrono::system_clock::to_time_t(time);
		CString timeOperated(ctime(&time_to_timet));

		//Wrap values in ' ' so they can be used for INSERT query
		dataID.Insert(0, '\''); dataID.Insert(dataID.GetLength() + 1, L"\', ");
		timeOperated.Insert(0, '\''); timeOperated.Insert(timeOperated.GetLength() + 1, L"\', ");

		//Insert into LastAccessed table
		insert = ("INSERT INTO LastAccessed(DataID, LastAccess, LatestOperation)");
		values = _T(" VALUES(" + dataID  + timeOperated + (CString)"'Written')");
		dbControl.ExecuteSQLCommand(insert + values);
	}
	else {
		message.LoadString(IDS_RSOPENERROR);
		caption.LoadString(IDS_CAPTIONERRORMSGBOX);
		MessageBox(message, caption, MB_OK);
		dbControl.CloseConnection();
		recordset.Close();
		return;
	}
	
	//Clear previous edit control text
	SetDlgItemText(IDC_EDIT_NAME, 0); SetDlgItemText(IDC_EDIT_SURNAME, 0); SetDlgItemText(IDC_EDIT_USERNAME, 0);
	SetDlgItemText(IDC_EDIT_EMAIL, 0); SetDlgItemText(IDC_EDIT_PASSWORD, 0); SetDlgItemText(IDC_EDIT_PLATFORM, 0);

	message.LoadString(IDS_OKSAVEDATAMSG);
	caption.LoadString(IDS_CAPTIONSUCCESSMSGBOX);
	MessageBox(message, caption, MB_OK);
	recordset.Close();
	dbControl.CloseConnection();
}
