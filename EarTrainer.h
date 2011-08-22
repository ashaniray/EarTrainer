// EarTrainer.h : main header file for the EARTRAINER application
//

#if !defined(AFX_EARTRAINER_H__BE88E4C3_949A_4E93_9061_FD0229A8FEDC__INCLUDED_)
#define AFX_EARTRAINER_H__BE88E4C3_949A_4E93_9061_FD0229A8FEDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#pragma warning (disable : 4786)

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEarTrainerApp:
// See EarTrainer.cpp for the implementation of this class
//

#include <MmSystem.h>

struct MidiData
{
	MidiData() : m_nChannel(0), m_nVoice(0), m_hMidiOut(0), m_nVelocity(120),
				m_nDevice(MIDIMAPPER){}
	bool Initialize()
	{
		if (MMSYSERR_NOERROR != midiOutOpen(&m_hMidiOut, m_nDevice, 0, 0, 0))
		{
			AfxMessageBox("Unable to open Midi O/P device");
			return false;
		}


		return true;
	}

	void SetDevice(UINT nDevice)
	{
		if (nDevice == m_nDevice)
			return;

		for (int i = 0 ; i < 16 ; i++)
		{
			DWORD dwMessage = 0xB0 | 1 | (123 << 8);
			midiOutShortMsg (m_hMidiOut, dwMessage) ;
		}

		midiOutReset(m_hMidiOut);
		midiOutClose(m_hMidiOut);
		m_nDevice = nDevice;

		if (MMSYSERR_NOERROR != midiOutOpen(&m_hMidiOut, m_nDevice, 0, 0, 0))
		{
			AfxMessageBox("Unable to open Midi O/P device");
			return;
		}
	}

	~MidiData() 
	{
		midiOutReset(m_hMidiOut);
		midiOutClose(m_hMidiOut);
	}

	int m_nChannel;
	int m_nVoice;
	HMIDIOUT m_hMidiOut;
	int m_nVelocity;
	UINT m_nDevice;
};

class CEarTrainerApp : public CWinApp
{
public:
	CEarTrainerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEarTrainerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEarTrainerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	MidiData* GetMidiData() {return &m_MidiData;}

private:
	MidiData m_MidiData;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EARTRAINER_H__BE88E4C3_949A_4E93_9061_FD0229A8FEDC__INCLUDED_)
