// IntervalPage.cpp : implementation file
//

#include "stdafx.h"
#include "EarTrainer.h"
#include "IntervalPage.h"

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

const int ELAPSE_TIME = 2000;

CIntervalPage::CIntervalPage() : CPropertyPage(CIntervalPage::IDD), m_dwElapse(ELAPSE_TIME)
{
	//{{AFX_DATA_INIT(CIntervalPage)
	m_csResult = _T("");
	m_nInputInterval = 0;
	m_csNotesPlayed = _T("");
	//}}AFX_DATA_INIT

	if (MMSYSERR_NOERROR != midiOutOpen(&m_hMidiOut, MIDIMAPPER, 0, 0, 0))
	{
		AfxMessageBox("Unable to open Midi O/P device");
		return ;
	}
}

CIntervalPage::~CIntervalPage()
{
}

void CIntervalPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIntervalPage)
	DDX_Control(pDX, IDC_EDIT_RESULT, m_editResult);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_csResult);
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_nInputInterval);
	DDV_MinMaxUInt(pDX, m_nInputInterval, 0, 12);
	DDX_Text(pDX, IDC_EDIT_NOTES_PLAYED, m_csNotesPlayed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIntervalPage, CPropertyPage)
	//{{AFX_MSG_MAP(CIntervalPage)
	ON_BN_CLICKED(IDC_BUTTON_PLAYNOTES, OnButtonPlayNotes)
	ON_BN_CLICKED(IDC_BUTTON_SHOWNOTESPLAYED, OnButtonShowNotesPlayed)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_AND_SHOW_NOTES, OnButtonPlayAndShowNotes)
	ON_BN_CLICKED(IDC_BUTTON_REPEAT_LAST_PLAYED, OnButtonRepeatLastPlayed)
	ON_BN_CLICKED(IDC_BUTTON_VALIDATE, OnButtonValidate)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


std::string CIntervalPage::Dword2Note(DWORD dwNote)
{
	std::string csNote = "";

	int nPos = (dwNote + 3) % 12;
	switch(nPos)
	{
	case 0:
		csNote = "A";
		break;
	case 1:
		csNote = "A#";
		break;
	case 2:
		csNote = "B";
		break;
	case 3:
		csNote = "C";
		break;
	case 4:
		csNote = "C#";
		break;
	case 5:
		csNote = "D";
		break;
	case 6:
		csNote = "D#";
		break;
	case 7:
		csNote = "E";
		break;
	case 8:
		csNote = "F";
		break;
	case 9:
		csNote = "F#";
		break;
	case 10:
		csNote = "G";
		break;
	case 11:
		csNote = "G#";
		break;
	}

	return csNote;
}

/////////////////////////////////////////////////////////////////////////////
// CIntervalPage message handlers

void CIntervalPage::OnButtonPlayNotes() 
{
	CreateNotes();
	PlayNotes();	
}

void CIntervalPage::OnButtonShowNotesPlayed() 
{
	std::ostringstream os;
	std::transform(m_vNotes.begin(), m_vNotes.end(), std::ostream_iterator<std::string>(os, " "), Dword2Note);
	
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

	UpdateData();

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

	std::transform(m_vNotes.begin(), m_vNotes.end(), std::ostream_iterator<std::string>(os, " "), Dword2Note);
	
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
	int nMinNote = 57;
	int nMaxNote = 70;

	int nRand = rand() * (nMaxNote - nMinNote) / RAND_MAX;
	return nMinNote + nRand;
}

DWORD CIntervalPage::GetInterval()
{

	DWORD nInterval = 0;
	int nRand = rand() * 5 / RAND_MAX;

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
		nInterval = 5;
		break;
	case 4:
		nInterval = 7;
		break;
	}
	return nInterval;
}

void CIntervalPage::CreateNotes() 
{
	m_csNotesPlayed = "";
	UpdateData(FALSE);

	m_vNotes.clear();

	DWORD dwFirstNote = GetFirstNote();
	DWORD dwInterval = GetInterval();
	DWORD dwNextNote = dwFirstNote + dwInterval;

	m_vNotes.push_back(dwFirstNote);
	m_vNotes.push_back(dwNextNote);
}

void CIntervalPage::PlayNotes() 
{
	if (m_vNotes.size() > 0)
		SetTimer(0, 0, NULL);
}

void CIntervalPage::UpdateData(BOOL bSaveAndValidate)
{
	DWORD dwLines = m_editResult.GetFirstVisibleLine();
	CDialog::UpdateData(bSaveAndValidate);

	m_editResult.LineScroll(dwLines);
}


void CIntervalPage::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	DWORD dwNote = m_vNotes[nIDEvent];
	DWORD dwMsg = 0x007F0095 | (dwNote << 8);
	
	midiOutShortMsg(m_hMidiOut, dwMsg);

	KillTimer(nIDEvent);
	if (m_vNotes.size() - nIDEvent > 1)
		SetTimer(++nIDEvent, m_dwElapse, NULL);

	CPropertyPage::OnTimer(nIDEvent);
}
