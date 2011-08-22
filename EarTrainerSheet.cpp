// EarTrainerSheet.cpp : implementation file
//

#include "stdafx.h"
#include "EarTrainer.h"
#include "EarTrainerSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEarTrainerSheet

IMPLEMENT_DYNAMIC(CEarTrainerSheet, CPropertySheet)

CEarTrainerSheet::CEarTrainerSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	Intialize();
}

CEarTrainerSheet::CEarTrainerSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	Intialize();

	SetTitle(_T("Ear Trainer by Ashani Ray"));
}

CEarTrainerSheet::~CEarTrainerSheet()
{
}

BOOL CEarTrainerSheet::Intialize()
{
	AddPage(&m_pageInterval);
	AddPage(&m_pagePitch);
	AddPage(&m_pageChord);
	AddPage(&m_pageConfig);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CEarTrainerSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CEarTrainerSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEarTrainerSheet message handlers
