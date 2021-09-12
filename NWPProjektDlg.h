
// NWPProjektDlg.h : header file
//

#pragma once
#include "resource.h"
#include "DialogSaveData.h"
#include "DialogRetrieveData.h"
#include "DialogUpdateDelete.h"
#include "DatabaseControl.h"
#include <exception>

// CNWPProjektDlg dialog
class CNWPProjektDlg : public CDialogEx
{
// Construction
public:
	CNWPProjektDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_START };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnSaveDataClicked();
	afx_msg void OnBtnRetrieveDataClicked();
	afx_msg void OnBtnCreateTablesClicked();
	afx_msg void OnBtnUpdateDeleteClicked();
};
