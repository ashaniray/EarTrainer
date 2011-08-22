#if !defined(AFX_CHORDPAGE_H__287EA8D0_4ED8_4CF4_8A0F_725847383D0E__INCLUDED_)
#define AFX_CHORDPAGE_H__287EA8D0_4ED8_4CF4_8A0F_725847383D0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChordPage.h : header file
//

#include <Mmsystem.h>
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CChordPage dialog

class CChordPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CChordPage)

// Construction
public:
	CChordPage();
	~CChordPage();

// Dialog Data
	//{{AFX_DATA(CChordPage)
	enum { IDD = IDD_DIALOG_CHORD };
	int		m_nRadioChords;
	CString	m_csChordPlayed;
	BOOL	m_bCheckFixedRoot;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CChordPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void PlayChord();
	// Generated message map functions
	//{{AFX_MSG(CChordPage)
	afx_msg void OnButtonChordPlay();
	afx_msg void OnButtonChordValidate();
	afx_msg void OnButtonShowChordPlayed();
	afx_msg void OnButtonPlayAndShowChord();
	afx_msg void OnButtonRepeatLastPlayed();
	afx_msg void OnButtonChordPlayCorrespondingMajorMinor();
	afx_msg void OnButtonChordStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	enum ChordType 
	{
		NONE,
		MAJOR, 
		MINOR, 
		SUS4, 
		AUG 
	};

	enum Root 
	{ 
		C, 
		C_SHARP, 
		D, 
		D_SHARP, 
		E, 
		F, 
		F_SHARP, 
		G, 
		G_SHARP, 
		A, 
		A_SHARP, 
		B 
	};


private:
	void GetMajorChordNotes(DWORD nRoot, std::vector<DWORD>& vChordNotes, int nInversion = 0);
	void GetMinorChordNotes(DWORD nRoot, std::vector<DWORD>& vChordNotes, int nInversion = 0);

	DWORD GetRootNote();
	void CreateChord();

private:
	std::vector<DWORD> m_vChord;
	ChordType m_chordCurrent;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHORDPAGE_H__287EA8D0_4ED8_4CF4_8A0F_725847383D0E__INCLUDED_)
