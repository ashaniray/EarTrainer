// IntervalPage.cpp : implementation file
//

#include "stdafx.h"
#include "EarTrainer.h"
#include "IntervalPage.h"

#include "NoteUtils.h"

#include <iterator>
#include <sstream>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntervalPage property page

IMPLEMENT_DYNCREATE(CIntervalPage, CPropertyPage)


CIntervalPage::CIntervalPage() : CPropertyPage(CIntervalPage::IDD)
{
	//{{AFX_DATA_INIT(CIntervalPage)
	m_csResult = _T("");
	m_csNotesPlayed = _T("");
	m_bCheckFixedRoot = FALSE;
	m_nInputInterval = 0;
	m_bCheckAsc1 = FALSE;
	m_bCheckAsc10 = FALSE;
	m_bCheckAsc11 = FALSE;
	m_bCheckAsc12 = FALSE;
	m_bCheckAsc3 = FALSE;
	m_bCheckAsc4 = FALSE;
	m_bCheckAsc5 = FALSE;
	m_bCheckAsc6 = FALSE;
	m_bCheckAsc7 = FALSE;
	m_bCheckAsc8 = FALSE;
	m_bCheckAsc9 = FALSE;
	m_bCheckAsc2 = FALSE;
	m_bCheckDesc1 = FALSE;
	m_bCheckDesc10 = FALSE;
	m_bCheckDesc11 = FALSE;
	m_bCheckDesc12 = FALSE;
	m_bCheckDesc2 = FALSE;
	m_bCheckDesc3 = FALSE;
	m_bCheckDesc5 = FALSE;
	m_bCheckDesc4 = FALSE;
	m_bCheckDesc6 = FALSE;
	m_bCheckDesc7 = FALSE;
	m_bCheckDesc8 = FALSE;
	m_bCheckDesc9 = FALSE;
	m_bIsValidateInput = false;
	m_nComboPitchIndex = -1;
	//}}AFX_DATA_INIT


}

CIntervalPage::~CIntervalPage()
{
}

void AFXAPI DDV_MinMaxInterval(CDataExchange* pDX, int value, int minVal, int maxVal)
{
	ASSERT(minVal <= maxVal);
	if (!pDX->m_bSaveAndValidate)
	{
		return;
	}

	if (value < minVal || value > maxVal)
	{
		CString prompt;
		prompt.Format("Interval must be between %d and %d", minVal, maxVal);
		AfxMessageBox(prompt, MB_ICONEXCLAMATION);
		prompt.Empty();
		pDX->Fail();
	}
}

void CIntervalPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	
	//{{AFX_DATA_MAP(CIntervalPage)
	DDX_Control(pDX, IDC_SPIN_INTERVAL_TEMPO, m_spinTempo);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_editResult);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_csResult);
	DDX_Text(pDX, IDC_EDIT_NOTES_PLAYED, m_csNotesPlayed);
	DDX_Check(pDX, IDC_CHECK_FIXED_ROOT, m_bCheckFixedRoot);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_ASC_1, m_bCheckAsc1);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_ASC_10, m_bCheckAsc10);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_ASC_11, m_bCheckAsc11);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_ASC_12, m_bCheckAsc12);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_ASC_3, m_bCheckAsc3);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_ASC_4, m_bCheckAsc4);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_ASC_5, m_bCheckAsc5);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_ASC_6, m_bCheckAsc6);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_ASC_7, m_bCheckAsc7);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_ASC_8, m_bCheckAsc8);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_ASC_9, m_bCheckAsc9);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_ASC_2, m_bCheckAsc2);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_DESC_1, m_bCheckDesc1);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_DESC_10, m_bCheckDesc10);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_DESC_11, m_bCheckDesc11);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_DESC_12, m_bCheckDesc12);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_DESC_2, m_bCheckDesc2);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_DESC_3, m_bCheckDesc3);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_DESC_5, m_bCheckDesc5);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_DESC_4, m_bCheckDesc4);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_DESC_6, m_bCheckDesc6);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_DESC_7, m_bCheckDesc7);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_DESC_8, m_bCheckDesc8);
	DDX_Check(pDX, IDC_CHECK_INTERVAL_DESC_9, m_bCheckDesc9);
	DDX_CBIndex(pDX, IDC_COMBO_INTERVAL_PITCH, m_nComboPitchIndex);
	//}}AFX_DATA_MAP

	if (m_bIsValidateInput)
	{
		DDX_Text(pDX, IDC_EDIT_INTERVAL, m_nInputInterval);
		DDV_MinMaxInterval(pDX, m_nInputInterval, -12, 12);
	}
}


BEGIN_MESSAGE_MAP(CIntervalPage, CPropertyPage)
	//{{AFX_MSG_MAP(CIntervalPage)
	ON_BN_CLICKED(IDC_BUTTON_PLAYNOTES, OnButtonPlayNotes)
	ON_BN_CLICKED(IDC_BUTTON_SHOWNOTESPLAYED, OnButtonShowNotesPlayed)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_AND_SHOW_NOTES, OnButtonPlayAndShowNotes)
	ON_BN_CLICKED(IDC_BUTTON_REPEAT_LAST_PLAYED, OnButtonRepeatLastPlayed)
	ON_BN_CLICKED(IDC_BUTTON_VALIDATE, OnButtonValidate)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_INTERVAL_CLEAR_RESULTS, OnButtonClearResults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CIntervalPage message handlers

void CIntervalPage::OnButtonPlayNotes() 
{
	CreateNotes();
	PlayNotes();	
}

void CIntervalPage::OnButtonShowNotesPlayed() 
{
	UpdateData(TRUE);

	std::ostringstream os;
	std::transform(m_vNotes.begin(), m_vNotes.end(), std::ostream_iterator<std::string>(os, " "), CNoteUtils::Dword2Note);
	
	os << "\r\n";
	std::copy(m_vNotes.begin(), m_vNotes.end(), std::ostream_iterator<DWORD>(os, " "));
	
	std::string csOut = os.str();
	m_csNotesPlayed = csOut.c_str();

	UpdateData(FALSE);	
}

void CIntervalPage::OnButtonPlayAndShowNotes() 
{
	OnButtonPlayNotes();
	OnButtonShowNotesPlayed();
}

void CIntervalPage::OnButtonRepeatLastPlayed() 
{
	PlayNotes();	
}

void CIntervalPage::OnButtonValidate() 
{
	if (m_vNotes.size() != 2)
	{
		AfxMessageBox("Vector size is not 2 !", MB_ICONERROR);
		return;
	}

	m_bIsValidateInput = true;
	BOOL bValidationSuccessful = UpdateData(TRUE);
	m_bIsValidateInput = false;

	if (!bValidationSuccessful)
		return;

	DWORD dwActualDiff = m_vNotes[1] - m_vNotes[0];


	std::ostringstream os;
	if (dwActualDiff == m_nInputInterval)
	{
		os << "OK";
	}
	else
	{
		os << "ERROR";
	}
	os << " Diff:" << (int)dwActualDiff - (int)m_nInputInterval << " ";

	std::transform(m_vNotes.begin(), m_vNotes.end(), std::ostream_iterator<std::string>(os, " "), CNoteUtils::Dword2Note);
	
	os << " ( ";
	std::copy(m_vNotes.begin(), m_vNotes.end(), std::ostream_iterator<DWORD>(os, " "));
	os << " ) ";

	os << " Guess:" << m_nInputInterval << " ";


	os << "\r\n";

	std::string csDisplay = os.str();

	m_csResult += csDisplay.c_str();

	UpdateData(FALSE);

	DWORD dwLines = m_editResult.GetLineCount();
	m_editResult.LineScroll(dwLines);

}

DWORD CIntervalPage::GetFirstNote()
{
	if (m_bCheckFixedRoot)
	{
		return m_nComboPitchIndex + 24;
	}

	int nMinNote = 57;
	int nMaxNote = 70;

	int nRand = rand() * (nMaxNote - nMinNote) / RAND_MAX;
	return nMinNote + nRand;
}



DWORD CIntervalPage::GetInterval()
{

	DWORD nInterval = 0;

	std::vector<int> vInterval;

	if (m_bCheckAsc1) vInterval.push_back(1);
	if (m_bCheckAsc2) vInterval.push_back(2);
	if (m_bCheckAsc3) vInterval.push_back(3);
	if (m_bCheckAsc4) vInterval.push_back(4);
	if (m_bCheckAsc5) vInterval.push_back(5);
	if (m_bCheckAsc6) vInterval.push_back(6);
	if (m_bCheckAsc7) vInterval.push_back(7);
	if (m_bCheckAsc8) vInterval.push_back(8);
	if (m_bCheckAsc9) vInterval.push_back(9);
	if (m_bCheckAsc10) vInterval.push_back(10);
	if (m_bCheckAsc11) vInterval.push_back(11);
	if (m_bCheckAsc12) vInterval.push_back(12);

	if (m_bCheckDesc1) vInterval.push_back(-1);
	if (m_bCheckDesc2) vInterval.push_back(-2);
	if (m_bCheckDesc3) vInterval.push_back(-3);
	if (m_bCheckDesc4) vInterval.push_back(-4);
	if (m_bCheckDesc5) vInterval.push_back(-5);
	if (m_bCheckDesc6) vInterval.push_back(-6);
	if (m_bCheckDesc7) vInterval.push_back(-7);
	if (m_bCheckDesc8) vInterval.push_back(-8);
	if (m_bCheckDesc9) vInterval.push_back(-9);
	if (m_bCheckDesc10) vInterval.push_back(-10);
	if (m_bCheckDesc11) vInterval.push_back(-11);
	if (m_bCheckDesc12) vInterval.push_back(-12);

	int nSize = vInterval.size();

	if (nSize == 0)
	{
		AfxMessageBox(_T("Please select an interval"), MB_ICONEXCLAMATION);
		return 0;
	}

	int nRand = rand() * nSize / RAND_MAX;
	nInterval = vInterval[nRand];

	/*
	switch (m_nRadioInterval)
	{
	case 0:
		nInterval = GetSimpleInterval();
		break;
	case 1:
		nInterval = GetMajorInterval();
		break;
	case 2:
		nInterval = GetChromaticInterval();
		break;
	default:
		nInterval = GetSimpleInterval();
		break;
	}
	*/

	return nInterval;
}

void CIntervalPage::CreateNotes() 
{
	UpdateData(TRUE);
	m_csNotesPlayed = "";
	UpdateData(FALSE);

	m_vNotes.clear();

	DWORD dwFirstNote = GetFirstNote();
	DWORD dwInterval = GetInterval();
	DWORD dwNextNote = dwFirstNote + dwInterval;

	if (dwInterval != 0)
	{
		m_vNotes.push_back(dwFirstNote);
		m_vNotes.push_back(dwNextNote);
	}
}

void CIntervalPage::PlayNotes() 
{
	UpdateData(TRUE);
	if (m_vNotes.size() > 0)
		SetTimer(0, 0, NULL);
}

BOOL CIntervalPage::UpdateData(BOOL bSaveAndValidate)
{
	DWORD dwLines = m_editResult.GetFirstVisibleLine();
	BOOL bRet = CDialog::UpdateData(bSaveAndValidate);
	m_editResult.LineScroll(dwLines);

	return bRet;
}


void CIntervalPage::OnTimer(UINT nIDEvent) 
{
	KillTimer(nIDEvent);
	if (nIDEvent > m_vNotes.size() - 1)
		return;

	DWORD dwNote = m_vNotes[nIDEvent];
	if (nIDEvent > 0)
	{
		CNoteUtils::MidiNoteOff(m_vNotes[nIDEvent - 1]);
	}
	if (m_vNotes.size() > nIDEvent)
	{
		CNoteUtils::MidiNoteOn(dwNote);
	}
	else
	{
		CNoteUtils::MidiNoteOff(m_vNotes[nIDEvent - 1]);
	}

	if (m_vNotes.size() > nIDEvent)
	{
		CString csTempo;
		GetDlgItemText(IDC_EDIT_INTERVAL_TEMPO, csTempo);
		DWORD dwTempo = atoi((LPCTSTR)csTempo);
		DWORD dwElapse = 1000*60/dwTempo;
		SetTimer(++nIDEvent, dwElapse, NULL);
	}

	CPropertyPage::OnTimer(nIDEvent);
}

/*
DWORD CIntervalPage::GetSimpleInterval()
{
	DWORD nInterval = 0;
	bool bIsAscending = IsAscending();
	
	if (bIsAscending)
	{
		int nRand = rand() * 4 / RAND_MAX;
		switch(nRand)
		{
		case 0:
			nInterval = 2;
			break;
		case 1:
			nInterval = 4;
			break;
		case 2:
			nInterval = 5;
			break;
		default:
			nInterval = 7;
			break;
		}
	}
	else
	{
		int nRand = rand() * 4 / RAND_MAX;
		switch(nRand)
		{
		case 0:
			nInterval = -1;
			break;
		case 1:
			nInterval = -3;
			break;
		case 2:
			nInterval = -5;
			break;
		default:
			nInterval = -7;
			break;
		}
	}
	return nInterval;
}

DWORD CIntervalPage::GetMajorInterval()
{
	DWORD nInterval = 0;
	bool bIsAscending = IsAscending();

	int nRand = rand() * 7 / RAND_MAX;

	switch(nRand)
	{
	case 0:
		nInterval = 2;
		break;
	case 1:
		nInterval = 4;
		break;
	case 2:
		nInterval = 5;
		break;
	case 3:
		nInterval = 7;
		break;
	case 4:
		nInterval = 9;
		break;
	case 5:
		nInterval = 11;
		break;
	default:
		nInterval = 12;
		break;
	}

	
	if (!bIsAscending)
		nInterval -= 12;

	nInterval = nInterval == 0 ? nInterval - 12 : nInterval;
	return nInterval;
}

DWORD CIntervalPage::GetChromaticInterval()
{
	DWORD nInterval = 0;
	bool bIsAscending = IsAscending();

	int nRand = rand() * 12 / RAND_MAX;
	nInterval = nRand + 1;

	if (!bIsAscending)
		nInterval -= 12;

	nInterval = nInterval == 0 ? nInterval - 12 : nInterval;
	return nInterval;

}

bool CIntervalPage::IsAscending()
{
	bool bAscending = 0;
	switch (m_nRadioAscending)
	{
	case 0:
		bAscending = true;
		break;
	case 1:
		bAscending = false;
		break;
	default:
		bAscending = (rand() * 2 / RAND_MAX) == 0 ? true : false;;

	}
	return bAscending;
}
*/

void CIntervalPage::OnButtonClearResults() 
{
	m_csResult.Empty();
	UpdateData(FALSE);
}

BOOL CIntervalPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_spinTempo.SetRange(20, 200);
	m_spinTempo.SetPos(60);

	CComboBox *pWnd = (CComboBox*)GetDlgItem(IDC_COMBO_INTERVAL_PITCH);
	
	pWnd->Clear();
	for (int i = 2; i < 9; ++i)
	{
		CString csNote;

		csNote.Format("%dC (%d)", i, 12*i + 0);
		pWnd->AddString(csNote);
		csNote.Format("%dC# (%d)", i, 12*i + 1);
		pWnd->AddString(csNote);
		csNote.Format("%dD (%d)", i, 12*i + 2);
		pWnd->AddString(csNote);
		csNote.Format("%dD# (%d)", i, 12*i + 3);
		pWnd->AddString(csNote);
		csNote.Format("%dE (%d)", i, 12*i + 4);
		pWnd->AddString(csNote);
		csNote.Format("%dF (%d)", i, 12*i + 5);
		pWnd->AddString(csNote);
		csNote.Format("%dF# (%d)", i, 12*i + 6);
		pWnd->AddString(csNote);
		csNote.Format("%dG (%d)", i, 12*i + 7);
		pWnd->AddString(csNote);
		csNote.Format("%dG# (%d)", i, 12*i + 8);
		pWnd->AddString(csNote);
		csNote.Format("%dA (%d)", i, 12*i + 9);
		pWnd->AddString(csNote);
		csNote.Format("%dA# (%d)", i, 12*i + 10);
		pWnd->AddString(csNote);
		csNote.Format("%dB (%d)", i, 12*i + 11);
		pWnd->AddString(csNote);
	}

	pWnd->SetCurSel(36);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
