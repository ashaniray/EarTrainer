#if !defined(AFX_INTERVALPAGE_H__A955AD45_A084_40C1_862A_3B609B22DF8D__INCLUDED_)
#define AFX_INTERVALPAGE_H__A955AD45_A084_40C1_862A_3B609B22DF8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IntervalPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIntervalPage dialog

#include <Mmsystem.h>
#include <vector>

class CIntervalPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CIntervalPage)

// Construction
public:
	CIntervalPage();
	~CIntervalPage();

// Dialog Data
	//{{AFX_DATA(CIntervalPage)
	enum { IDD = IDD_DIALOG_INTERVAL };
	CEdit	m_editResult;
	CString	m_csResult;
	UINT	m_nInputInterval;
	CString	m_csNotesPlayed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CIntervalPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CIntervalPage)
	afx_msg void OnButtonPlayNotes();
	afx_msg void OnButtonShowNotesPlayed();
	afx_msg void OnButtonPlayAndShowNotes();
	afx_msg void OnButtonRepeatLastPlayed();
	afx_msg void OnButtonValidate();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual void UpdateData(BOOL bSaveAndValidate=TRUE);

private:
	void CreateNotes();
	void PlayNotes();

	HMIDIOUT m_hMidiOut;
	std::vector<DWORD> m_vNotes;
	DWORD m_dwElapse;
	
	static std::string Dword2Note(DWORD dwNote);
	static DWORD GetFirstNote();
	static DWORD GetInterval();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERVALPAGE_H__A955AD45_A084_40C1_862A_3B609B22DF8D__INCLUDED_)
