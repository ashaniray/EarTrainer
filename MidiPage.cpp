// MidiPage.cpp : implementation file
//

#include "stdafx.h"
#include "EarTrainer.h"
#include "MidiPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMidiPage property page

IMPLEMENT_DYNCREATE(CMidiPage, CPropertyPage)

CMidiPage::CMidiPage() : CPropertyPage(CMidiPage::IDD)
{
	//{{AFX_DATA_INIT(CMidiPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMidiPage::~CMidiPage()
{
}

void CMidiPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMidiPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMidiPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMidiPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMidiPage message handlers
