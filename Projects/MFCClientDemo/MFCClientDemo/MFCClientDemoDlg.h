
// MFCClientDemoDlg.h : header file
//

#pragma once


// CMFCClientDemoDlg dialog
class CMFCClientDemoDlg : public CDialogEx
{
// Construction
public:
	CMFCClientDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCLIENTDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CClientSocket m_clientSocket;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSend();
	CString m_ip_address;
	UINT m_port;
	CString m_message_box;
};
