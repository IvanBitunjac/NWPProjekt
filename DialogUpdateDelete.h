#pragma once
#pragma warning(disable : 4996) //For ctime deprecation warning

#include "DatabaseControl.h"
#include <chrono>
#include <ctime>

// DialogUpdateDelete dialog

class DialogUpdateDelete : public CDialogEx
{
	DECLARE_DYNAMIC(DialogUpdateDelete)

public:
	DialogUpdateDelete(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogUpdateDelete();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATEDELETE_DATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnDeleteClicked();
	afx_msg void OnClose();
	afx_msg void OnBtnBackClicked();
	afx_msg void OnBtnUpdateClicked();
};
