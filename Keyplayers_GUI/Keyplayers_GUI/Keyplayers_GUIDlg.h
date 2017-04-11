
// Keyplayers_GUIDlg.h : header file
//

#pragma once


// CKeyplayers_GUIDlg dialog
class CKeyplayers_GUIDlg : public CDialogEx
{
// Construction
public:
	CKeyplayers_GUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_KEYPLAYERS_GUI_DIALOG };

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
	afx_msg void OnBnClickedBtnOpenfile();
	CString m_sFileIn;
	afx_msg void OnBnClickedBtnPp1();
	BOOL ProcessFiles(CString sFileIn, int top, float threshold, bool flagPp, bool loadFile);
	CString m_sNumOfKey;
	CString m_sResult1;
	CString m_sThreshold;
	afx_msg void OnBnClickedBtnPp2();
	afx_msg void OnBnClickedBtnAbout();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedButton1();
};
