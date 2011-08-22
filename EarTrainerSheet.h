#if !defined(AFX_EARTRAINERSHEET_H__AD1DAF62_4268_48A5_A400_ABB7FFFEF8B8__INCLUDED_)
#define AFX_EARTRAINERSHEET_H__AD1DAF62_4268_48A5_A400_ABB7FFFEF8B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EarTrainerSheet.h : header file
//

#include "IntervalPage.h"
#include "ChordPage.h"
#include "ConfigurationPage.h"
#include "PitchPage.h"

/////////////////////////////////////////////////////////////////////////////
// CEarTrainerSheet


class CEarTrainerSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CEarTrainerSheet)

// Construction
public:
	CEarTrainerSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CEarTrainerSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEarTrainerSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEarTrainerSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEarTrainerSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL Intialize();

private:
	CIntervalPage m_pageInterval;
	CChordPage m_pageChord;
	CConfigurationPage m_pageConfig;
	CPitchPage m_pagePitch;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EARTRAINERSHEET_H__AD1DAF62_4268_48A5_A400_ABB7FFFEF8B8__INCLUDED_)
