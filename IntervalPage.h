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
	CSpinButtonCtrl	m_spinTempo;
	CEdit	m_editResult;
	CString	m_csResult;
	CString	m_csNotesPlayed;
	BOOL	m_bCheckFixedRoot;
	int		m_nInputInterval;
	BOOL	m_bCheckAsc1;
	BOOL	m_bCheckAsc10;
	BOOL	m_bCheckAsc11;
	BOOL	m_bCheckAsc12;
	BOOL	m_bCheckAsc3;
	BOOL	m_bCheckAsc4;
	BOOL	m_bCheckAsc5;
	BOOL	m_bCheckAsc6;
	BOOL	m_bCheckAsc7;
	BOOL	m_bCheckAsc8;
	BOOL	m_bCheckAsc9;
	BOOL	m_bCheckAsc2;
	BOOL	m_bCheckDesc1;
	BOOL	m_bCheckDesc10;
	BOOL	m_bCheckDesc11;
	BOOL	m_bCheckDesc12;
	BOOL	m_bCheckDesc2;
	BOOL	m_bCheckDesc3;
	BOOL	m_bCheckDesc5;
	BOOL	m_bCheckDesc4;
	BOOL	m_bCheckDesc6;
	BOOL	m_bCheckDesc7;
	BOOL	m_bCheckDesc8;
	BOOL	m_bCheckDesc9;
	BOOL	m_bIsDiadMode;
	int		m_nComboPitchIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CIntervalPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	static VOID CALLBACK DiadTimer(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
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
	afx_msg void OnButtonClearResults();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL UpdateData(BOOL bSaveAndValidate=TRUE);

private:
	/*
	bool IsAscending();
	DWORD GetMajorInterval();
	DWORD GetSimpleInterval();
	DWORD GetChromaticInterval();
	*/
	void CreateNotes();
	void PlayNotes();
	BOOL PlayDiad();

	std::vector<DWORD> m_vNotes;
	
	DWORD GetFirstNote();
	DWORD GetInterval();

	bool m_bIsValidateInput;

	friend VOID CALLBACK DiadTimer(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERVALPAGE_H__A955AD45_A084_40C1_862A_3B609B22DF8D__INCLUDED_)
