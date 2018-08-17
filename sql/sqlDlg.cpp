
// sqlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "sql.h"
#include "sqlDlg.h"
#include "afxdialogex.h"
#include "score.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CsqlDlg 对话框



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


// CsqlDlg 消息处理程序

BOOL CsqlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_class.AddString(_T("1"));
	m_class.AddString(_T("2"));
	m_class.AddString(_T("3"));
	m_class.AddString(_T("4"));
	m_class.AddString(_T("5"));
	m_class.SetCurSel(0);  // 指定字符串从0开始的索引项开始
	m_class.GetLBText(0, m_classEdit); // 复制从0开始的索引项到m_classEdit

	//Cscore m_set;
	//m_set.Open();
	//m_set.MoveFirst();
	//m_numEdit = m_set.m_stuid;
	//m_nameEdit = m_set.m_stuname;
	//m_classEdit = m_set.m_stuclass;
	//m_testEdit = m_set.m_testscore;
	//m_usualEdit = m_set.m_usualscore;
	//m_totalEdit = m_set.m_totalscore;
	//UpdateData(FALSE); // 更新

	// 为列表添加     全行选中                栅栏(网格线)       允许报表头可以拖拽      单击激活
	//DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE;
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE);
	//m_list.SetTextBkColor(RGB(255, 0, 0)); // 设置文本背景颜色
	m_list.SetBkColor(RGB(240, 247, 233)); // 设置背景颜色
	m_list.SetTextColor(RGB(255, 0, 0)); // 设置文本颜色

	// 索引 ,标题 , 格式(LVCFMT_LEFT、 LVCFMT_RIGHT或 LVCFMT_CENTER) ,宽度 , 子项(-1为没有)
	m_list.InsertColumn(0, _T("学号"), LVCFMT_CENTER, 60, 0);
	m_list.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 60, 0);
	m_list.InsertColumn(2, _T("班级"), LVCFMT_CENTER, 60, 0);
	m_list.InsertColumn(3, _T("平时成绩"), LVCFMT_CENTER, 60, 0);
	m_list.InsertColumn(4, _T("期末成绩"), LVCFMT_CENTER, 60, 0);
	m_list.InsertColumn(5, _T("总成绩"), LVCFMT_CENTER, 60, 0);

	CString strsql;
	strsql.Format(_T("select * from score order by stuid"));
	list_All(strsql); // 列表显示所有内容



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CsqlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
			MessageBox(L"打开数据库失败", L"数据库错误", MB_OK);
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
		LV_ITEM litem;           // 声明一个LVITEM结构体
		litem.mask = LVIF_TEXT;  // 说明LVITEM结构中哪些成员有效
		litem.iItem = nindex;    // 项的索引值(可以视为行号)从0开始
		litem.iSubItem = 0;      // 子项的索引值(可以视为列号)从0开始
		litem.pszText = _T("");  // 主项或子项的名称

		m_list.InsertItem(&litem); // 把项添加入list_control

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
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int r = m_list.GetNextSelectedItem(pos);
	m_nameEdit = m_list.GetItemText(r, 1); 
	m_numEdit = m_list.GetItemText(r, 0);
	UpdateData(FALSE);

}


void CsqlDlg::OnBnClickedAddButton()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
}


void CsqlDlg::OnBnClickedDeleteButton()
{
	// TODO: 在此添加控件通知处理程序代码
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
			MessageBox(_T("删除成功！"));
			break;
		}
		m_set.MoveNext();
	}
	m_set.Close();
	list_All(_T("select * from score order by stuid"));
}
