// PitchPage.cpp : implementation file
//

#include "stdafx.h"
#include "EarTrainer.h"
#include "PitchPage.h"
#include "NoteUtils.h"

#include <sstream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CPitchPage property page

IMPLEMENT_DYNCREATE(CPitchPage, CPropertyPage)

const int TIMER_INTERVAL = 2000;

CPitchPage::CPitchPage() : CPropertyPage(CPitchPage::IDD), m_dwElapse(TIMER_INTERVAL)
{
	//{{AFX_DATA_INIT(CPitchPage)
	m_nComboPitchIndex = 9;
	m_csResult = _T("");
	m_csNotesPlayed = _T("");
	m_nSliderProbability = 6;
	m_nComboPitchMin = -1;
	m_nComboPitchMax = -1;
	//}}AFX_DATA_INIT

	m_bIsNeedPressButton = false;
}

CPitchPage::~CPitchPage()
{
}

void CPitchPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPitchPage)
	DDX_Control(pDX, IDC_SLIDER_PITCH_PROBABILITY, m_sliderProbability);
	DDX_Control(pDX, IDC_SPIN_PITCH_TEMPO, m_spinTempo);
	DDX_Control(pDX, IDC_EDIT_PITCH_RESULT, m_editResult);
	DDX_CBIndex(pDX, IDC_COMBO_PITCH_LIST, m_nComboPitchIndex);
	DDX_Text(pDX, IDC_EDIT_PITCH_RESULT, m_csResult);
	DDX_Text(pDX, IDC_EDIT_PITCH_NOTES_PLAYED, m_csNotesPlayed);
	DDX_Slider(pDX, IDC_SLIDER_PITCH_PROBABILITY, m_nSliderProbability);
	DDX_CBIndex(pDX, IDC_COMBO_PITCH_MIN, m_nComboPitchMin);
	DDX_CBIndex(pDX, IDC_COMBO_PITCH_MAX, m_nComboPitchMax);
	//}}AFX_DATA_MAP

	if (!pDX->m_bSaveAndValidate)
	{
		return;
	}

	if (m_nComboPitchMin > m_nComboPitchIndex || m_nComboPitchIndex > m_nComboPitchMax)
	{
		CString prompt = "Pitch choosen must lie between Min and Max pitches";
		AfxMessageBox(prompt, MB_ICONEXCLAMATION);
		prompt.Empty();
		pDX->Fail();
	}
}


BEGIN_MESSAGE_MAP(CPitchPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPitchPage)
	ON_BN_CLICKED(IDC_BUTTON_PITCH_PLAY, OnButtonPitchPlay)
	ON_BN_CLICKED(IDC_BUTTON_PITCH_PLAY_NOTE_SEQUENCE, OnButtonPitchPlayNoteSequence)
	ON_BN_CLICKED(IDC_BUTTON_PITCH_STOP_NOTE_SEQUENCE, OnButtonPitchStopNoteSequence)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PITCH_PRESS_IF_MATCHED, OnButtonPressIfMatched)
	ON_BN_CLICKED(IDC_BUTTON_PITCH_SHOW_NOTES_PLAYED, OnButtonShowNotesPlayed)
	ON_BN_CLICKED(IDC_BUTTON_PITCH_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPitchPage message handlers

void CPitchPage::OnButtonPitchPlay() 
{
	if (!UpdateData(TRUE))
		return;

	DWORD dwNote = GetComboPitch();
	CNoteUtils::MidiNoteOn(dwNote);
}

void CPitchPage::OnButtonPitchPlayNoteSequence() 
{
	if (!UpdateData(TRUE))
		return;

	m_csNotesPlayed = "";
	m_csResult = "";

	UpdateData(FALSE);

	CWnd *pWndPlay = GetDlgItem(IDC_BUTTON_PITCH_PLAY);
	pWndPlay->EnableWindow(FALSE);
	
	CWnd *pWndPress = GetDlgItem(IDC_BUTTON_PITCH_PRESS_IF_MATCHED);
	pWndPress->EnableWindow(TRUE);

	CWnd *pWndPlaySeq = GetDlgItem(IDC_BUTTON_PITCH_PLAY_NOTE_SEQUENCE);
	pWndPlaySeq->EnableWindow(FALSE);

	m_vNotes.clear();
	SetTimer(0, 0, NULL);
}

void CPitchPage::OnButtonPitchStopNoteSequence() 
{
	CWnd *pWndPlay = GetDlgItem(IDC_BUTTON_PITCH_PLAY);
	pWndPlay->EnableWindow(TRUE);

	CWnd *pWndPress = GetDlgItem(IDC_BUTTON_PITCH_PRESS_IF_MATCHED);
	pWndPress->EnableWindow(FALSE);

	CWnd *pWndPlaySeq = GetDlgItem(IDC_BUTTON_PITCH_PLAY_NOTE_SEQUENCE);
	pWndPlaySeq->EnableWindow(TRUE);

	m_bIsNeedPressButton = false;

	if (m_vNotes.size() > 0)
		CNoteUtils::MidiNoteOff(m_vNotes.back());

	KillTimer(0);
}

void CPitchPage::OnTimer(UINT nIDEvent) 
{
	if (m_bIsNeedPressButton == true)
	{
		m_csResult += "Missed Note\r\n";
		UpdateData(FALSE);
		m_bIsNeedPressButton = false;

		DWORD dwLines = m_editResult.GetLineCount();
		m_editResult.LineScroll(dwLines);

	}

	if (!UpdateData(TRUE))
	{
		KillTimer(0);
		return;
	}

	DWORD dwRand = rand() * m_nSliderProbability / RAND_MAX;

	DWORD dwNote = dwRand == 0 ? GetComboPitch() : CNoteUtils::GetRandomNote(m_nComboPitchMin, m_nComboPitchMax);

	if (m_vNotes.size() > 0)
		CNoteUtils::MidiNoteOff(m_vNotes.back());
	CNoteUtils::MidiNoteOn(dwNote);
	m_vNotes.push_back(dwNote);
	if (abs((long)(dwNote - GetComboPitch())) % 12 == 0)
		m_bIsNeedPressButton = true;
	
	CWnd *pWndPress = GetDlgItem(IDC_BUTTON_PITCH_PRESS_IF_MATCHED);
	if (pWndPress->IsWindowEnabled() == 0)
		pWndPress->EnableWindow(TRUE);

	pWndPress->SetFocus();

	CString csTempo;
	GetDlgItemText(IDC_EDIT_PITCH_TEMPO, csTempo);
	DWORD dwTempo = atoi((LPCTSTR)csTempo);
	DWORD dwElapse = 1000*60/dwTempo;
	KillTimer(0);
	SetTimer(0, dwElapse, NULL);

	CPropertyPage::OnTimer(nIDEvent);
}

BOOL CPitchPage::OnInitDialog() 
{


	CPropertyPage::OnInitDialog();
	
	CWnd *pWndPress = GetDlgItem(IDC_BUTTON_PITCH_PRESS_IF_MATCHED);
	pWndPress->EnableWindow(FALSE);

	m_spinTempo.SetRange(20, 120);
	m_spinTempo.SetPos(60);

	m_sliderProbability.SetRange(2, 12, TRUE);
	m_sliderProbability.SetPos(6);
	
	InitCombos();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPitchPage::OnButtonPressIfMatched() 
{
	DWORD dwCurrentNote = m_vNotes.back();
	string csNote = CNoteUtils::Dword2Note(dwCurrentNote);
	if (m_bIsNeedPressButton)
		m_csResult = m_csResult + "Correct (" + csNote.c_str() + ")\r\n";
	else
		m_csResult = m_csResult + "Incorrect (" + csNote.c_str() + ")\r\n";

	m_bIsNeedPressButton = false;

	CWnd *pWndPress = GetDlgItem(IDC_BUTTON_PITCH_PRESS_IF_MATCHED);
	pWndPress->EnableWindow(FALSE);

	UpdateData(FALSE);

	DWORD dwLines = m_editResult.GetLineCount();
	m_editResult.LineScroll(dwLines);
}

void CPitchPage::OnButtonShowNotesPlayed() 
{
	
	string csNotesAsString;
	ostringstream oss;

	vector<DWORD>::iterator iterEnd = m_vNotes.end();
	for (vector<DWORD>::iterator iter = m_vNotes.begin(); iter != iterEnd; ++iter)
	{
		oss << *iter << " ";
		csNotesAsString = csNotesAsString + CNoteUtils::Dword2Note(*iter) + " ";
	}

	string csNotesAsDword = oss.str();

	m_csNotesPlayed.Empty();
	m_csNotesPlayed = csNotesAsString.c_str();
	m_csNotesPlayed += "\r\n";
	m_csNotesPlayed += csNotesAsDword.c_str();
	
	UpdateData(FALSE);
}


// Must call UpdateData(TRUE) before calling this function
DWORD CPitchPage::GetComboPitch()
{
	return m_nComboPitchIndex;
}

void CPitchPage::OnButtonStop() 
{
	UpdateData(TRUE);
	DWORD dwNote = GetComboPitch();
	
	CNoteUtils::MidiNoteOff(dwNote);

}

void CPitchPage::InitCombos()
{
	CComboBox *pWndCombo = 0;
	
	pWndCombo = (CComboBox*)GetDlgItem(IDC_COMBO_PITCH_LIST);
	AddAllNotesToCombo(pWndCombo);
	pWndCombo->SetCurSel(66);

	pWndCombo = (CComboBox*)GetDlgItem(IDC_COMBO_PITCH_MIN);
	AddAllNotesToCombo(pWndCombo);
	pWndCombo->SetCurSel(60);

	pWndCombo = (CComboBox*)GetDlgItem(IDC_COMBO_PITCH_MAX);
	AddAllNotesToCombo(pWndCombo);
	pWndCombo->SetCurSel(71);
}

void CPitchPage::AddAllNotesToCombo(CComboBox *pWnd)
{
	pWnd->Clear();

	for (int i = 0; i < 10; ++i)
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
}
