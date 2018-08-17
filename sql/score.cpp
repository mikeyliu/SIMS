// score.h : Cscore 类的实现



// Cscore 实现

// 代码生成在 2018年8月16日, 10:28

#include "stdafx.h"
#include "score.h"
IMPLEMENT_DYNAMIC(Cscore, CRecordset)

Cscore::Cscore(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_stuid = L"";
	m_stuname = L"";
	m_stuclass = L"";
	m_usualscore = 0.0;
	m_testscore = 0.0;
	m_totalscore = 0.0;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString Cscore::GetDefaultConnect()
{
	return _T("DSN=_SQL_SERVER;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=MOCHANGQIANG-PC;DATABASE=student");
}

CString Cscore::GetDefaultSQL()
{
	return _T("[dbo].[score]");
}

void Cscore::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[stuid]"), m_stuid);
	RFX_Text(pFX, _T("[stuname]"), m_stuname);
	RFX_Text(pFX, _T("[stuclass]"), m_stuclass);
	RFX_Single(pFX, _T("[usualscore]"), m_usualscore);
	RFX_Single(pFX, _T("[testscore]"), m_testscore);
	RFX_Single(pFX, _T("[totalscore]"), m_totalscore);

}
/////////////////////////////////////////////////////////////////////////////
// Cscore 诊断

#ifdef _DEBUG
void Cscore::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cscore::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


