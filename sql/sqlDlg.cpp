
// sqlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sql.h"
#include "sqlDlg.h"
#include "afxdialogex.h"
#include "score.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CsqlDlg �Ի���



CsqlDlg::CsqlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SQL_DIALOG, pParent)
	, m_numEdit(_T("0"))
	, m_nameEdit(_T("0"))
	, m_classEdit(_T("0"))
	, m_usualEdit(0)
	, m_testEdit(0)
	, m_totalEdit(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsqlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Text(pDX, IDC_NUM_EDIT, m_numEdit);
	DDX_Text(pDX, IDC_NAME_EDIT, m_nameEdit);
	DDX_Text(pDX, IDC_USUAL_EDIT, m_usualEdit);
	DDX_Text(pDX, IDC_TEST_EDIT, m_testEdit);
	DDX_Text(pDX, IDC_TOTAL_EDIT, m_totalEdit);
	DDX_Control(pDX, IDC_CLASS_COMBO, m_class);
}

BEGIN_MESSAGE_MAP(CsqlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_LIST, &CsqlDlg::OnNMClickList)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CsqlDlg::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_ALTER_BUTTON, &CsqlDlg::OnBnClickedAlterButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CsqlDlg::OnBnClickedDeleteButton)
END_MESSAGE_MAP()


// CsqlDlg ��Ϣ�������

BOOL CsqlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_class.AddString(_T("1"));
	m_class.AddString(_T("2"));
	m_class.AddString(_T("3"));
	m_class.AddString(_T("4"));
	m_class.AddString(_T("5"));
	m_class.SetCurSel(0);  // ָ���ַ�����0��ʼ�������ʼ
	m_class.GetLBText(0, m_classEdit); // ���ƴ�0��ʼ�������m_classEdit

	//Cscore m_set;
	//m_set.Open();
	//m_set.MoveFirst();
	//m_numEdit = m_set.m_stuid;
	//m_nameEdit = m_set.m_stuname;
	//m_classEdit = m_set.m_stuclass;
	//m_testEdit = m_set.m_testscore;
	//m_usualEdit = m_set.m_usualscore;
	//m_totalEdit = m_set.m_totalscore;
	//UpdateData(FALSE); // ����

	// Ϊ�б����     ȫ��ѡ��                դ��(������)       ������ͷ������ק      ��������
	//DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE;
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE);
	//m_list.SetTextBkColor(RGB(255, 0, 0)); // �����ı�������ɫ
	m_list.SetBkColor(RGB(240, 247, 233)); // ���ñ�����ɫ
	m_list.SetTextColor(RGB(255, 0, 0)); // �����ı���ɫ

	// ���� ,���� , ��ʽ(LVCFMT_LEFT�� LVCFMT_RIGHT�� LVCFMT_CENTER) ,��� , ����(-1Ϊû��)
	m_list.InsertColumn(0, _T("ѧ��"), LVCFMT_CENTER, 60, 0);
	m_list.InsertColumn(1, _T("����"), LVCFMT_CENTER, 60, 0);
	m_list.InsertColumn(2, _T("�༶"), LVCFMT_CENTER, 60, 0);
	m_list.InsertColumn(3, _T("ƽʱ�ɼ�"), LVCFMT_CENTER, 60, 0);
	m_list.InsertColumn(4, _T("��ĩ�ɼ�"), LVCFMT_CENTER, 60, 0);
	m_list.InsertColumn(5, _T("�ܳɼ�"), LVCFMT_CENTER, 60, 0);

	CString strsql;
	strsql.Format(_T("select * from score order by stuid"));
	list_All(strsql); // �б���ʾ��������



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CsqlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CsqlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CsqlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CsqlDlg::list_All(CString str)
{
	m_list.DeleteAllItems();
	Cscore m_score;
	try {
		if (m_score.IsOpen())
			m_score.Close();
		if (!m_score.Open(CRecordset::snapshot, str)) {
			MessageBox(L"�����ݿ�ʧ��", L"���ݿ����", MB_OK);
			return;
		}
	}
	catch (CDBException *e) {
		e->ReportError();
	}
	int nindex = 0;
	m_score.MoveFirst();
	CString uscore, tscore, fscore;

	while (!m_score.IsEOF()) {
		LV_ITEM litem;           // ����һ��LVITEM�ṹ��
		litem.mask = LVIF_TEXT;  // ˵��LVITEM�ṹ����Щ��Ա��Ч
		litem.iItem = nindex;    // �������ֵ(������Ϊ�к�)��0��ʼ
		litem.iSubItem = 0;      // ���������ֵ(������Ϊ�к�)��0��ʼ
		litem.pszText = _T("");  // ��������������

		m_list.InsertItem(&litem); // ���������list_control

		m_list.SetItemText(nindex, 0, m_score.m_stuid);
		m_list.SetItemText(nindex, 1, m_score.m_stuname);
		m_list.SetItemText(nindex, 2, m_score.m_stuclass);

		uscore.Format(_T("%3.2f"), m_score.m_usualscore);
		tscore.Format(_T("%3.2f"), m_score.m_testscore);
		fscore.Format(_T("%3.2f"), m_score.m_totalscore);

		m_list.SetItemText(nindex, 3, uscore);
		m_list.SetItemText(nindex, 4, tscore);
		m_list.SetItemText(nindex, 5, fscore);

		m_score.MoveNext();
		nindex++;
	}
	m_score.Close();

}



void CsqlDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int r = m_list.GetNextSelectedItem(pos);
	m_nameEdit = m_list.GetItemText(r, 1); 
	m_numEdit = m_list.GetItemText(r, 0);
	UpdateData(FALSE);

}


void CsqlDlg::OnBnClickedAddButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Cscore m_set;
	if (m_set.IsOpen())
		m_set.Close();
	m_set.Open();
	m_set.AddNew();
	UpdateData(TRUE);
	m_set.m_stuid = m_numEdit;
	m_set.m_stuclass = m_classEdit;
	m_set.m_stuname = m_nameEdit;
	m_set.m_usualscore = m_usualEdit;
	m_set.m_testscore = m_testEdit;
	m_set.m_totalscore = m_totalEdit;
	UpdateData(FALSE);
	m_set.Update();
	m_set.Close();
	list_All(_T("select * from score order by stuid"));
}


void CsqlDlg::OnBnClickedAlterButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CsqlDlg::OnBnClickedDeleteButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//UpdateData(TRUE);
	CString str;
	GetDlgItemText(IDC_NUM_EDIT, str);
	Cscore m_set;
	if (m_set.IsOpen())
		m_set.Close();
	m_set.Open();
	m_set.MoveFirst();
	while (!m_set.IsEOF()) {
		if (m_set.m_stuid == str) {
			m_set.Delete();
			MessageBox(_T("ɾ���ɹ���"));
			break;
		}
		m_set.MoveNext();
	}
	m_set.Close();
	list_All(_T("select * from score order by stuid"));
}
