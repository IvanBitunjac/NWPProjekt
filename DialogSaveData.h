#pragma once
#pragma warning(disable : 4996) //For ctime deprecation warning

#include "resource.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "DatabaseControl.h"
#include <chrono>
#include <ctime>



// DialogSaveData dialog

class DialogSaveData : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSaveData)

public:
	DialogSaveData(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogSaveData();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SAVE_DATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnBackClicked();
	afx_msg void OnClose();
	afx_msg void OnBtnSaveDataClicked();
};
