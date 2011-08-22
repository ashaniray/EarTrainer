// NoteUtils.cpp: implementation of the CNoteUtils class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EarTrainer.h"
#include "NoteUtils.h"

#include <MMREG.H>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNoteUtils::CNoteUtils()
{

}

CNoteUtils::~CNoteUtils()
{

}

std::string CNoteUtils::Dword2Note(DWORD dwNote)
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

DWORD CNoteUtils::GetRandomNote(DWORD dwMin, DWORD dwMax)
{
	DWORD dwRand = rand() * (dwMax - dwMin) / RAND_MAX;
	return dwMin + dwRand;
}

std::string CNoteUtils::GetProductFromIdentifier(WORD wPid)
{
	//TODO: Only MS Products are given..

	std::string csProduct;
	switch(wPid)
	{
	case MM_ADLIB: 
		csProduct = _T("Adlib-compatible synthesizer ");
		break;
	case MM_MSFT_ACM_G711: 
		csProduct = _T("G.711 codec ");
		break;
	case MM_MSFT_ACM_GSM610: 
		csProduct = _T("GSM 610 codec ");
		break;
	case MM_MSFT_ACM_IMAADPCM: 
		csProduct = _T("IMA ADPCM codec ");
		break;
	case MM_PC_JOYSTICK: 
		csProduct = _T("Joystick adapter ");
		break;
	case MM_MIDI_MAPPER: 
		csProduct = _T("MIDI mapper ");
		break;
	case MM_MPU401_MIDIIN: 
		csProduct = _T("MPU 401-compatible MIDI input port ");
		break;
	case MM_MPU401_MIDIOUT: 
		csProduct = _T("MPU 401-compatible MIDI output port ");
		break;
	case MM_MSFT_ACM_MSADPCM: 
		csProduct = _T("MS ADPCM codec ");
		break;
	case MM_MSFT_WSS_FMSYNTH_STEREO: 
		csProduct = _T("MS audio board stereo FM synthesizer ");
		break;
	case MM_MSFT_WSS_AUX: 
		csProduct = _T("MS audio board aux port ");
		break;
	case MM_MSFT_WSS_MIXER: 
		csProduct = _T("MS audio board mixer driver ");
		break;
	case MM_MSFT_WSS_WAVEIN: 
		csProduct = _T("MS audio board waveform input ");
		break;
	case MM_MSFT_WSS_WAVEOUT: 
		csProduct = _T("MS audio board waveform output ");
		break;
	case MM_MSFT_MSACM: 
		csProduct = _T("MS audio compression manager ");
		break;
	case MM_MSFT_ACM_MSFILTER: 
		csProduct = _T("MS filter ");
		break;
	case MM_MSFT_WSS_OEM_AUX: 
		csProduct = _T("MS OEM audio aux port ");
		break;
	case MM_MSFT_WSS_OEM_MIXER: 
		csProduct = _T("MS OEM audio board mixer driver ");
		break;
	case MM_MSFT_WSS_OEM_FMSYNTH_STEREO: 
		csProduct = _T("MS OEM audio board stereo FM synthesizer ");
		break;
	case MM_MSFT_WSS_OEM_WAVEIN: 
		csProduct = _T("MS OEM audio board waveform input ");
		break;
	case MM_MSFT_WSS_OEM_WAVEOUT: 
		csProduct = _T("MS OEM audio board waveform output ");
		break;
	case MM_MSFT_GENERIC_AUX_CD: 
		csProduct = _T("MS vanilla driver aux (CD) ");
		break;
	case MM_MSFT_GENERIC_AUX_LINE: 
		csProduct = _T("MS vanilla driver aux (line in) ");
		break;
	case MM_MSFT_GENERIC_AUX_MIC: 
		csProduct = _T("MS vanilla driver aux (mic) ");
		break;
	case MM_MSFT_GENERIC_MIDIOUT: 
		csProduct = _T("MS vanilla driver MIDI external out ");
		break;
	case MM_MSFT_GENERIC_MIDIIN: 
		csProduct = _T("MS vanilla driver MIDI in ");
		break;
	case MM_MSFT_GENERIC_MIDISYNTH: 
		csProduct = _T("MS vanilla driver MIDI synthesizer ");
		break;
	case MM_MSFT_GENERIC_WAVEIN: 
		csProduct = _T("MS vanilla driver waveform input ");
		break;
	case MM_MSFT_GENERIC_WAVEOUT: 
		csProduct = _T("MS vanilla driver wavefrom output ");
		break;
	case MM_PCSPEAKER_WAVEOUT: 
		csProduct = _T("PC speaker waveform output ");
		break;
	case MM_MSFT_ACM_PCM: 
		csProduct = _T("PCM converter ");
		break;
	case MM_SNDBLST_SYNTH: 
		csProduct = _T("Sound Blaster internal synthesizer ");
		break;
	case MM_SNDBLST_MIDIIN: 
		csProduct = _T("Sound Blaster MIDI input port ");
		break;
	case MM_SNDBLST_MIDIOUT: 
		csProduct = _T("Sound Blaster MIDI output port ");
		break;
	case MM_SNDBLST_WAVEIN: 
		csProduct = _T("Sound Blaster waveform input ");
		break;
	case MM_SNDBLST_WAVEOUT: 
		csProduct = _T("Sound Blaster waveform output ");
		break;
	case MM_WAVE_MAPPER: 
		csProduct = _T("Wave mapper ");
		break;
	
	default:
		csProduct = _T("Unknown");
		break;
	}

	return csProduct;
}

std::string CNoteUtils::GetManufacturerFromIdentifier(WORD mMid)
{
	std::string csManufacturer;

	switch(mMid)
	{
	case MM_GRAVIS: 
		csManufacturer = _T("Advanced Gravis Computer Technology, Ltd. ");
		break;
	case MM_ANTEX: 
		csManufacturer = _T("Antex Electronics Corporation ");
		break;
	case MM_APPS: 
		csManufacturer = _T("APPS Software  ");
		break;
	case MM_ARTISOFT: 
		csManufacturer = _T("Artisoft, Inc. ");
		break;
	case MM_AST: 
		csManufacturer = _T("AST Research, Inc. ");
		break;
	case MM_ATI: 
		csManufacturer = _T("ATI Technologies, Inc. ");
		break;
	case MM_AUDIOFILE: 
		csManufacturer = _T("Audio, Inc. ");
		break;
	case MM_APT: 
		csManufacturer = _T("Audio Processing Technology ");
		break;
	case MM_AUDIOPT: 
		csManufacturer = _T("Audio Processing Technology ");
		break;
	case MM_AURAVISION: 
		csManufacturer = _T("Auravision Corporation ");
		break;
	case MM_AZTECH: 
		csManufacturer = _T("Aztech Labs, Inc. ");
		break;
	case MM_CANOPUS: 
		csManufacturer = _T("Canopus, Co., Ltd. ");
		break;
	case MM_COMPUSIC: 
		csManufacturer = _T("Compusic ");
		break;
	case MM_CAT: 
		csManufacturer = _T("Computer Aided Technology, Inc. ");
		break;
	case MM_COMPUTER_FRIENDS: 
		csManufacturer = _T("Computer Friends, Inc. ");
		break;
	case MM_CONTROLRES: 
		csManufacturer = _T("Control Resources Corporation ");
		break;
	case MM_CREATIVE: 
		csManufacturer = _T("Creative Labs, Inc. ");
		break;
	case MM_DIALOGIC: 
		csManufacturer = _T("Dialogic Corporation ");
		break;
	case MM_DOLBY: 
		csManufacturer = _T("Dolby Laboratories, Inc. ");
		break;
	case MM_DSP_GROUP: 
		csManufacturer = _T("DSP Group, Inc. ");
		break;
	case MM_DSP_SOLUTIONS: 
		csManufacturer = _T("DSP Solutions, Inc. ");
		break;
	case MM_ECHO: 
		csManufacturer = _T("Echo Speech Corporation ");
		break;
	case MM_ESS: 
		csManufacturer = _T("ESS Technology, Inc. ");
		break;
	case MM_EVEREX: 
		csManufacturer = _T("Everex Systems, Inc. ");
		break;
	case MM_EXAN: 
		csManufacturer = _T("EXAN, Ltd. ");
		break;
	case MM_FUJITSU: 
		csManufacturer = _T("Fujitsu, Ltd. ");
		break;
	case MM_IOMAGIC: 
		csManufacturer = _T("I/O Magic Corporation ");
		break;
	case MM_ICL_PS: 
		csManufacturer = _T("ICL Personal Systems ");
		break;
	case MM_OLIVETTI: 
		csManufacturer = _T("Ing. C. Olivetti & C., S.p.A. ");
		break;
	case MM_ICS: 
		csManufacturer = _T("Integrated Circuit Systems, Inc. ");
		break;
	case MM_INTEL: 
		csManufacturer = _T("Intel Corporation ");
		break;
	case MM_INTERACTIVE: 
		csManufacturer = _T("InterActive, Inc. ");
		break;
	case MM_IBM: 
		csManufacturer = _T("International Business Machines  ");
		break;
	case MM_ITERATEDSYS : 
		csManufacturer = _T("Iterated Systems, Inc. ");
		break;
	case MM_LOGITECH: 
		csManufacturer = _T("Logitech, Inc. ");
		break;
	case MM_LYRRUS: 
		csManufacturer = _T("Lyrrus, Inc. ");
		break;
	case MM_MATSUSHITA: 
		csManufacturer = _T("Matsushita Electric Corporation of America ");
		break;
	case MM_MEDIAVISION: 
		csManufacturer = _T("Media Vision, Inc. ");
		break;
	case MM_METHEUS: 
		csManufacturer = _T("Metheus Corporation ");
		break;
	case MM_MELABS: 
		csManufacturer = _T("microEngineering Labs ");
		break;
	case MM_MICROSOFT: 
		csManufacturer = _T("Microsoft Corporation ");
		break;
	case MM_MOSCOM: 
		csManufacturer = _T("MOSCOM Corporation ");
		break;
	case MM_MOTOROLA: 
		csManufacturer = _T("Motorola, Inc. ");
		break;
	case MM_NMS: 
		csManufacturer = _T("Natural MicroSystems Corporation ");
		break;
	case MM_NCR: 
		csManufacturer = _T("NCR Corporation ");
		break;
	case MM_NEC: 
		csManufacturer = _T("NEC Corporation ");
		break;
	case MM_NEWMEDIA: 
		csManufacturer = _T("New Media Corporation ");
		break;
	case MM_OKI: 
		csManufacturer = _T("OKI ");
		break;
	case MM_OPTI: 
		csManufacturer = _T("OPTi, Inc. ");
		break;
	case MM_ROLAND: 
		csManufacturer = _T("Roland Corporation ");
		break;
	case MM_SCALACS: 
		csManufacturer = _T("SCALACS ");
		break;
	case MM_EPSON: 
		csManufacturer = _T("Seiko Epson Corporation, Inc. ");
		break;
	case MM_SIERRA: 
		csManufacturer = _T("Sierra Semiconductor Corporation ");
		break;
	case MM_SILICONSOFT: 
		csManufacturer = _T("Silicon Software, Inc. ");
		break;
	case MM_SONICFOUNDRY: 
		csManufacturer = _T("Sonic Foundry ");
		break;
	case MM_SPEECHCOMP: 
		csManufacturer = _T("Speech Compression ");
		break;
	case MM_SUPERMAC: 
		csManufacturer = _T("Supermac Technology, Inc. ");
		break;
	case MM_TANDY: 
		csManufacturer = _T("Tandy Corporation ");
		break;
	case MM_KORG: 
		csManufacturer = _T("Toshihiko Okuhura, Korg, Inc. ");
		break;
	case MM_TRUEVISION: 
		csManufacturer = _T("Truevision, Inc. ");
		break;
	case MM_TURTLE_BEACH: 
		csManufacturer = _T("Turtle Beach Systems ");
		break;
	case MM_VAL: 
		csManufacturer = _T("Video Associates Labs, Inc. ");
		break;
	case MM_VIDEOLOGIC: 
		csManufacturer = _T("VideoLogic, Inc. ");
		break;
	case MM_VITEC: 
		csManufacturer = _T("Visual Information Technologies, Inc. ");
		break;
	case MM_VOCALTEC: 
		csManufacturer = _T("VocalTec, Inc. ");
		break;
	case MM_VOYETRA: 
		csManufacturer = _T("Voyetra Technologies ");
		break;
	case MM_WANGLABS: 
		csManufacturer = _T("Wang Laboratories ");
		break;
	case MM_WILLOWPOND: 
		csManufacturer = _T("Willow Pond Corporation ");
		break;
	case MM_WINNOV: 
		csManufacturer = _T("Winnov, LP ");
		break;
	case MM_XEBEC: 
		csManufacturer = _T("Xebec Multimedia Solutions Limited ");
		break;
	case MM_YAMAHA: 
		csManufacturer = _T("Yamaha Corporation of America ");
		break;
	default:
		csManufacturer = _T("Unknown");
		break;

	}

	return csManufacturer;
}


std::string CNoteUtils::GetTechnologyAsString(WORD wTechnology)
{
	std::string csTechnology;
	switch(wTechnology)
	{
	case MOD_FMSYNTH:
		csTechnology = _T("The device is an FM synthesizer.");
		break;
	case MOD_MAPPER :
		csTechnology = _T("The device is the Microsoft MIDI mapper.");
		break;
	case MOD_MIDIPORT :
		csTechnology = _T("The device is a MIDI hardware port.");
		break;
	case MOD_SQSYNTH :
		csTechnology = _T("The device is a square wave synthesizer.");
		break;
	case MOD_SYNTH :
		csTechnology = _T("The device is a synthesizer.");
		break;
	default:
		csTechnology = _T("Unknown");
		break;
	}
	return csTechnology;
}

DWORD CNoteUtils::MidiOutMessage(int nStatus, int nData1, int nData2)
{
	MidiData* pData = ((CEarTrainerApp*)AfxGetApp())->GetMidiData();
	
	int nChannel = pData->m_nChannel;
	HMIDIOUT hMidi = pData->m_hMidiOut;

	if (nData2 == -1)
		nData2 = pData->m_nVelocity;

	return MidiOutMessage(hMidi, nStatus, nChannel, nData1, nData2);
}

DWORD CNoteUtils::MidiOutMessage (HMIDIOUT hMidi, int iStatus, int iChannel,
                      int iData1,  int iData2)
{
     DWORD dwMessage = iStatus | iChannel | (iData1 << 8) | (iData2 << 16) ;
     return midiOutShortMsg (hMidi, dwMessage) ;
}


DWORD CNoteUtils::MidiNoteOn(DWORD dwNote)
{
	return MidiOutMessage(0x90, dwNote);
}

DWORD CNoteUtils::MidiNoteOff(DWORD dwNote)
{
	return MidiOutMessage(0x80, dwNote);
}

DWORD CNoteUtils::MidiSetPatch(int nChannel, int nVoice)
{
	MidiData* pData = ((CEarTrainerApp*)AfxGetApp())->GetMidiData();
	pData->m_nChannel = nChannel;
	return MidiOutMessage(0xC0, nVoice, 0);
}

DWORD CNoteUtils::MidiPitchBend(int nChannel, int nBend)
{
	MidiData* pData = ((CEarTrainerApp*)AfxGetApp())->GetMidiData();
	pData->m_nChannel = nChannel;

	return MidiOutMessage (0x0E0, nBend & 0x7F, nBend >> 7) ;
}

void CNoteUtils::SetDevice(UINT nDevice)
{
	MidiData* pData = ((CEarTrainerApp*)AfxGetApp())->GetMidiData();
	pData->SetDevice(nDevice);
}

int CNoteUtils::GetVelocity()
{
	MidiData* pData = ((CEarTrainerApp*)AfxGetApp())->GetMidiData();
	return pData->m_nVelocity;
}

void CNoteUtils::SetVelocity(int nVelocity)
{
	MidiData* pData = ((CEarTrainerApp*)AfxGetApp())->GetMidiData();
	pData->m_nVelocity = nVelocity;
}
