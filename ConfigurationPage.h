#if !defined(AFX_CONFIGURATIONPAGE_H__AD912818_E33D_461A_90AF_8B13AA78D0F8__INCLUDED_)
#define AFX_CONFIGURATIONPAGE_H__AD912818_E33D_461A_90AF_8B13AA78D0F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigurationPage.h : header file
//
#pragma warning (disable : 4786)

#include <Mmsystem.h>
#include <map>
#include <string>

/////////////////////////////////////////////////////////////////////////////
// CConfigurationPage dialog

class CConfigurationPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CConfigurationPage)

// Construction
public:
	CConfigurationPage();
	~CConfigurationPage();

// Dialog Data
	//{{AFX_DATA(CConfigurationPage)
	enum { IDD = IDD_DIALOG_CONFIGURATION };
	CSliderCtrl	m_sliderVelocity;
	CComboBox	m_comboDevice;
	CComboBox	m_comboChannel;
	CComboBox	m_comboVoices;
	int		m_nSliderVelocity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CConfigurationPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CConfigurationPage)
	afx_msg void OnButtonConfigApply();
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonStop();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void PopulateDevice();
	void PopulateChannel();
	void PopulateVoices();

private:
	std::map<std::string, UINT> m_mapDevice;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGURATIONPAGE_H__AD912818_E33D_461A_90AF_8B13AA78D0F8__INCLUDED_)
