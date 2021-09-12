#pragma once

#include "resource.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "DatabaseControl.h"


// DialogRetrieveData dialog

class DialogRetrieveData : public CDialogEx
{
	DECLARE_DYNAMIC(DialogRetrieveData)

public:
	DialogRetrieveData(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogRetrieveData();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RETRIEVEDATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnSearchClicked();
	afx_msg void OnBtnBackClicked();
	CListBox queryListbox;
	afx_msg void OnBtnSearchAllClicked();
};
