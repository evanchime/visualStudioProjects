
// MFCComboBoxDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMFCComboBoxDlg dialog
class CMFCComboBoxDlg : public CDialogEx
{
// Construction
public:
	CMFCComboBoxDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCOMBOBOX_DIALOG };
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
	CComboBox m_comboBoxCtrl;
	CString m_strTextCtrl;
	afx_msg void OnCbnSelchangeCombo1();
};
