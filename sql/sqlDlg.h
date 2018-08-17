
// sqlDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CsqlDlg �Ի���
class CsqlDlg : public CDialog
{
// ����
public:
	CsqlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SQL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	void list_All(CString);
	CString m_numEdit;
	CString m_nameEdit;
	CString m_classEdit;
	float m_usualEdit;
	float m_testEdit;
	float m_totalEdit;
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_class;
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedAlterButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedShowAllBt();
};
