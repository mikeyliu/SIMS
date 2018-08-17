// score.h : Cscore ���ʵ��



// Cscore ʵ��

// ���������� 2018��8��16��, 10:28

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
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[stuid]"), m_stuid);
	RFX_Text(pFX, _T("[stuname]"), m_stuname);
	RFX_Text(pFX, _T("[stuclass]"), m_stuclass);
	RFX_Single(pFX, _T("[usualscore]"), m_usualscore);
	RFX_Single(pFX, _T("[testscore]"), m_testscore);
	RFX_Single(pFX, _T("[totalscore]"), m_totalscore);

}
/////////////////////////////////////////////////////////////////////////////
// Cscore ���

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


