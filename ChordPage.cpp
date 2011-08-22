// ChordPage.cpp : implementation file
//

#include "stdafx.h"
#include "EarTrainer.h"
#include "ChordPage.h"

#include "NoteUtils.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChordPage property page

IMPLEMENT_DYNCREATE(CChordPage, CPropertyPage)

CChordPage::CChordPage() : CPropertyPage(CChordPage::IDD)
{
	//{{AFX_DATA_INIT(CChordPage)
	m_nRadioChords = 0;
	m_csChordPlayed = _T("");
	m_bCheckFixedRoot = FALSE;
	//}}AFX_DATA_INIT

	m_chordCurrent = NONE;
}

CChordPage::~CChordPage()
{
}

void CChordPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChordPage)
	DDX_Radio(pDX, IDC_RADIO_MAJOR_MINOR, m_nRadioChords);
	DDX_Text(pDX, IDC_EDIT_CHORD_PLAYED, m_csChordPlayed);
	DDX_Check(pDX, IDC_CHECK_CHORD_FIXED_ROOT, m_bCheckFixedRoot);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChordPage, CPropertyPage)
	//{{AFX_MSG_MAP(CChordPage)
	ON_BN_CLICKED(IDC_BUTTON_CHORD_PLAY, OnButtonChordPlay)
	ON_BN_CLICKED(IDC_BUTTON_CHORD_VALIDATE, OnButtonChordValidate)
	ON_BN_CLICKED(IDC_BUTTON_CHORD_SHOW_CHORD_PLAYED, OnButtonShowChordPlayed)
	ON_BN_CLICKED(IDC_BUTTON_CHORD_PLAY_AND_SHOW, OnButtonPlayAndShowChord)
	ON_BN_CLICKED(IDC_BUTTON_CHORD_REPEAT_LAST_PLAYED, OnButtonRepeatLastPlayed)
	ON_BN_CLICKED(IDC_BUTTON_CHORD_PLAY_CORRESPONDING_MAJOR_MINOR, OnButtonChordPlayCorrespondingMajorMinor)
	ON_BN_CLICKED(IDC_BUTTON_CHORD_STOP, OnButtonChordStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CChordPage::GetMajorChordNotes(DWORD nRoot, std::vector<DWORD>& vChordNotes, int nInversion)
{
	vChordNotes.clear();
	
	vChordNotes.push_back(nRoot);

	switch(nInversion)
	{
	case 0:
		vChordNotes.push_back(nRoot + 4);
		vChordNotes.push_back(nRoot + 7);
		break;
	case 1:
		vChordNotes.push_back(nRoot + 4 - 12);
		vChordNotes.push_back(nRoot + 7 - 12);
		break;
	case 2:
		vChordNotes.push_back(nRoot + 4);
		vChordNotes.push_back(nRoot + 7 - 12);
		break;
	default:
		vChordNotes.push_back(nRoot + 4);
		vChordNotes.push_back(nRoot + 7);
		break;
	}
	
}

void CChordPage::GetMinorChordNotes(DWORD nRoot, std::vector<DWORD>& vChordNotes, int nInversion)
{
	vChordNotes.clear();
	
	vChordNotes.push_back(nRoot);

	switch(nInversion)
	{
	case 0:
		vChordNotes.push_back(nRoot + 3);
		vChordNotes.push_back(nRoot + 7);
		break;
	case 1:
		vChordNotes.push_back(nRoot + 3 - 12);
		vChordNotes.push_back(nRoot + 7 - 12);
		break;
	case 2:
		vChordNotes.push_back(nRoot + 3);
		vChordNotes.push_back(nRoot + 7 - 12);
		break;
	default:
		vChordNotes.push_back(nRoot + 3);
		vChordNotes.push_back(nRoot + 7);
		break;
	}
}

DWORD CChordPage::GetRootNote()
{
	if (m_bCheckFixedRoot)
		return 60;

	int nMinNote = 48;
	int nMaxNote = 60;

	int nRand = rand() * (nMaxNote - nMinNote) / RAND_MAX;
	return nMinNote + nRand;
}

void CChordPage::CreateChord()
{
	UpdateData(TRUE);
	m_csChordPlayed = "";
	UpdateData(FALSE);

	DWORD dwRoot = GetRootNote();
	
	m_vChord.clear();
	int nInversion = 0;

	int nRand = rand() * 2 / RAND_MAX;
	switch (nRand)
	{
	case 0:
		GetMajorChordNotes(dwRoot, m_vChord, nInversion);
		m_chordCurrent = MAJOR;
		break;
	case 1:
		GetMinorChordNotes(dwRoot, m_vChord, nInversion);
		m_chordCurrent = MINOR;
		break;

	default:
		GetMajorChordNotes(dwRoot, m_vChord, nInversion);
		m_chordCurrent = MAJOR;
		break;
	}

}
/////////////////////////////////////////////////////////////////////////////
// CChordPage message handlers

void CChordPage::OnButtonChordPlay() 
{
	CreateChord();
	PlayChord();
}

void CChordPage::OnButtonChordValidate() 
{
	// TODO: Add your control notification handler code here
	
}

void CChordPage::OnButtonShowChordPlayed() 
{
	if (m_vChord.empty())
	{
		AfxMessageBox(_T("Chord not played"), MB_OK);
		return;
	}
	string csNote = CNoteUtils::Dword2Note(m_vChord[0]);

	string csChordName;
	switch(m_chordCurrent)
	{
	case MAJOR:
		csChordName = "Major";
		break;
	case MINOR:
		csChordName = "Minor";
		break;
	case SUS4:
		csChordName = "Sus4";
		break;
	case AUG:
		csChordName = "Aug";
		break;
	default:
		csChordName = "None";
		break;
	}

	m_csChordPlayed =  CString(csNote.c_str()) + " " + csChordName.c_str();
	UpdateData(FALSE);
}

void CChordPage::OnButtonPlayAndShowChord() 
{
	OnButtonChordPlay();
	OnButtonShowChordPlayed();
}

void CChordPage::PlayChord()
{
	vector<DWORD>::iterator iterEnd = m_vChord.end();
	for (vector<DWORD>::iterator iter = m_vChord.begin(); iter != iterEnd; ++iter)
	{
		DWORD dwNote = *iter;
		CNoteUtils::MidiNoteOn(dwNote);
	}

}

void CChordPage::OnButtonRepeatLastPlayed() 
{
	PlayChord();	
}

void CChordPage::OnButtonChordPlayCorrespondingMajorMinor() 
{
	if (m_vChord.empty())
	{
		AfxMessageBox(_T("Chord not played"), MB_OK);
		return;
	}
	if (m_chordCurrent == MAJOR)
	{
		GetMinorChordNotes(m_vChord[0], m_vChord, 0);
		m_chordCurrent = MINOR;
	}
	else
	{
		GetMajorChordNotes(m_vChord[0], m_vChord, 0);
		m_chordCurrent = MAJOR;
	}

	PlayChord();

}

void CChordPage::OnButtonChordStop() 
{
	vector<DWORD>::iterator iterEnd = m_vChord.end();
	for (vector<DWORD>::iterator iter = m_vChord.begin(); iter != iterEnd; ++iter)
	{
		CNoteUtils::MidiNoteOff(*iter);
	}
}
