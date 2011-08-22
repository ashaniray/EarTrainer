#if !defined(AFX_PITCHPAGE_H__53D31B66_D9DA_4FFD_A633_4077901DC3CD__INCLUDED_)
#define AFX_PITCHPAGE_H__53D31B66_D9DA_4FFD_A633_4077901DC3CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PitchPage.h : header file
//

#include <Mmsystem.h>
#include <vector>


/////////////////////////////////////////////////////////////////////////////
// CPitchPage dialog

class CPitchPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPitchPage)

// Construction
public:
	CPitchPage();
	~CPitchPage();

// Dialog Data
	//{{AFX_DATA(CPitchPage)
	enum { IDD = IDD_DIALOG_PITCH };
	CSliderCtrl	m_sliderProbability;
	CSpinButtonCtrl	m_spinTempo;
	CEdit	m_editResult;
	int		m_nComboPitchIndex;
	CString	m_csResult;
	CString	m_csNotesPlayed;
	int		m_nSliderProbability;
	int		m_nComboPitchMin;
	int		m_nComboPitchMax;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPitchPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPitchPage)
	afx_msg void OnButtonPitchPlay();
	afx_msg void OnButtonPitchPlayNoteSequence();
	afx_msg void OnButtonPitchStopNoteSequence();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonPressIfMatched();
	afx_msg void OnButtonShowNotesPlayed();
	afx_msg void OnButtonStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:

private:
	void AddAllNotesToCombo(CComboBox* pWnd);
	void InitCombos();
	DWORD GetComboPitch();
	bool m_bIsNeedPressButton;
	DWORD m_dwElapse;
	std::vector <DWORD> m_vNotes;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PITCHPAGE_H__53D31B66_D9DA_4FFD_A633_4077901DC3CD__INCLUDED_)
