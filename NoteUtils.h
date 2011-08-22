// NoteUtils.h: interface for the CNoteUtils class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTEUTILS_H__2790A5E6_9487_4620_84B6_C2AD76752E20__INCLUDED_)
#define AFX_NOTEUTILS_H__2790A5E6_9487_4620_84B6_C2AD76752E20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <Mmsystem.h>

class CNoteUtils  
{
public:
	static void SetVelocity(int nVelocity);
	static int GetVelocity();
	static void SetDevice(UINT nDevice);
	CNoteUtils();
	virtual ~CNoteUtils();

	static DWORD GetRandomNote(DWORD dwMin, DWORD dwMax);
	static std::string Dword2Note(DWORD dwNote);
	static std::string GetProductFromIdentifier(WORD wPid);
	static std::string GetManufacturerFromIdentifier(WORD mMid);
	static std::string GetTechnologyAsString(WORD wTechnology);
	static DWORD MidiOutMessage (HMIDIOUT hMidi, int iStatus, int iChannel, int iData1,  int iData2);
	static DWORD MidiOutMessage(int nStatus, int iData1, int iData2 = -1);
	static DWORD MidiNoteOn(DWORD dwNote);
	static DWORD MidiNoteOff(DWORD dwNote);
	static DWORD MidiSetPatch(int nChannel, int nVoice);
	static DWORD MidiPitchBend(int nChannel, int Bend);

};

#endif // !defined(AFX_NOTEUTILS_H__2790A5E6_9487_4620_84B6_C2AD76752E20__INCLUDED_)
