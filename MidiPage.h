#if !defined(AFX_MIDIPAGE_H__01A514F0_C02C_483B_A6BF_A3CAEC1859EB__INCLUDED_)
#define AFX_MIDIPAGE_H__01A514F0_C02C_483B_A6BF_A3CAEC1859EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MidiPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMidiPage dialog

class CMidiPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMidiPage)

// Construction
public:
	CMidiPage();
	~CMidiPage();

// Dialog Data
	//{{AFX_DATA(CMidiPage)
	enum { IDD = _UNKNOWN_RESOURCE_ID_ };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMidiPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMidiPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIDIPAGE_H__01A514F0_C02C_483B_A6BF_A3CAEC1859EB__INCLUDED_)
