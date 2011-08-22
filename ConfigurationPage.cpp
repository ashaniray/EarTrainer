// ConfigurationPage.cpp : implementation file
//

#include "stdafx.h"
#include "EarTrainer.h"
#include "ConfigurationPage.h"
#include "NoteUtils.h"

#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CConfigurationPage property page

IMPLEMENT_DYNCREATE(CConfigurationPage, CPropertyPage)

CConfigurationPage::CConfigurationPage() : CPropertyPage(CConfigurationPage::IDD)
{
	//{{AFX_DATA_INIT(CConfigurationPage)
	m_nSliderVelocity = CNoteUtils::GetVelocity();;
	//}}AFX_DATA_INIT
}

CConfigurationPage::~CConfigurationPage()
{
}

void CConfigurationPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigurationPage)
	DDX_Control(pDX, IDC_SLIDER_CONFIG_VELOCITY, m_sliderVelocity);
	DDX_Control(pDX, IDC_COMBO_CONFIG_DEVICE, m_comboDevice);
	DDX_Control(pDX, IDC_COMBO_CONFIG_CHANNEL, m_comboChannel);
	DDX_Control(pDX, IDC_COMBO_CONFIG_VOICES, m_comboVoices);
	DDX_Slider(pDX, IDC_SLIDER_CONFIG_VELOCITY, m_nSliderVelocity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigurationPage, CPropertyPage)
	//{{AFX_MSG_MAP(CConfigurationPage)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_APPLY, OnButtonConfigApply)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigurationPage message handlers


void CConfigurationPage::OnButtonConfigApply() 
{
	UpdateData(TRUE);

	int nVoice = m_comboVoices.GetCurSel();
	int nChannel = m_comboChannel.GetCurSel();

	CString csDevice;
	int nComboDeviceIndex = m_comboDevice.GetCurSel();
	m_comboDevice.GetLBText(nComboDeviceIndex, csDevice);
	UINT nDevice = m_mapDevice[(LPCTSTR)csDevice];

	CNoteUtils::MidiSetPatch(nChannel, nVoice);
	CNoteUtils::SetDevice(nDevice);
	CNoteUtils::SetVelocity(m_nSliderVelocity);
}


void CConfigurationPage::OnButtonPlay() 
{
	int nChannel = m_comboChannel.GetCurSel();
	CNoteUtils::MidiNoteOn(60);
}

void CConfigurationPage::OnButtonStop() 
{
	int nChannel = m_comboChannel.GetCurSel();
	CNoteUtils::MidiNoteOff(60);
}

BOOL CConfigurationPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	PopulateVoices();
	m_comboVoices.SetCurSel(0);

	PopulateChannel();
	m_comboChannel.SetCurSel(0);

	PopulateDevice();
	m_comboDevice.SetCurSel(0);

	m_sliderVelocity.SetRange(0, 127, TRUE);
	m_sliderVelocity.SetPos(CNoteUtils::GetVelocity());
	m_nSliderVelocity = CNoteUtils::GetVelocity();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigurationPage::PopulateVoices()
{
	m_comboVoices.Clear();
	m_comboVoices.AddString(_T("Acoustic Grand Piano"));
	m_comboVoices.AddString(_T("Bright Acoustic Piano"));
	m_comboVoices.AddString(_T("Electric Grand Piano"));
	m_comboVoices.AddString(_T("Honky-tonk Piano"));
	m_comboVoices.AddString(_T("Rhodes Piano"));
	m_comboVoices.AddString(_T("Chorused Piano"));
	m_comboVoices.AddString(_T("Harpsichord"));
	m_comboVoices.AddString(_T("Clavinet"));
	m_comboVoices.AddString(_T("Celesta"));
	m_comboVoices.AddString(_T("Glockenspiel"));
	m_comboVoices.AddString(_T("Music Box"));
	m_comboVoices.AddString(_T("Vibraphone"));
	m_comboVoices.AddString(_T("Marimba"));
	m_comboVoices.AddString(_T("Xylophone"));
	m_comboVoices.AddString(_T("Tubular Bells"));
	m_comboVoices.AddString(_T("Dulcimer"));
	m_comboVoices.AddString(_T("Hammond Organ"));
	m_comboVoices.AddString(_T("Percussive Organ"));
	m_comboVoices.AddString(_T("Rock Organ"));
	m_comboVoices.AddString(_T("Church Organ"));
	m_comboVoices.AddString(_T("Reed Organ"));
	m_comboVoices.AddString(_T("Accordian"));
	m_comboVoices.AddString(_T("Harmonica"));
	m_comboVoices.AddString(_T("Tango Accordian"));
	m_comboVoices.AddString(_T("Acoustic Guitar (nylon)"));
	m_comboVoices.AddString(_T("Acoustic Guitar (steel)"));
	m_comboVoices.AddString(_T("Electric Guitar (jazz)"));
	m_comboVoices.AddString(_T("Electric Guitar (clean)"));
	m_comboVoices.AddString(_T("Electric Guitar (muted)"));
	m_comboVoices.AddString(_T("Overdriven Guitar"));
	m_comboVoices.AddString(_T("Distortion Guitar"));
	m_comboVoices.AddString(_T("Guitar Harmonics"));
	m_comboVoices.AddString(_T("Acoustic Bass"));
	m_comboVoices.AddString(_T("Electric Bass (finger)"));
	m_comboVoices.AddString(_T("Electric Bass (pick)"));
	m_comboVoices.AddString(_T("Fretless Bass"));
	m_comboVoices.AddString(_T("Slap Bass 1"));
	m_comboVoices.AddString(_T("Slap Bass 2"));
	m_comboVoices.AddString(_T("Synth Bass 1"));
	m_comboVoices.AddString(_T("Synth Bass 2"));
	m_comboVoices.AddString(_T("Violin"));
	m_comboVoices.AddString(_T("Viola"));
	m_comboVoices.AddString(_T("Cello"));
	m_comboVoices.AddString(_T("Contrabass"));
	m_comboVoices.AddString(_T("Tremolo Strings"));
	m_comboVoices.AddString(_T("Pizzicato Strings"));
	m_comboVoices.AddString(_T("Orchestral Harp"));
	m_comboVoices.AddString(_T("Timpani"));
	m_comboVoices.AddString(_T("String Ensemble 1"));
	m_comboVoices.AddString(_T("String Ensemble 2"));
	m_comboVoices.AddString(_T("Synth Strings 1"));
	m_comboVoices.AddString(_T("Synth Strings 2"));
	m_comboVoices.AddString(_T("Choir Aahs"));
	m_comboVoices.AddString(_T("Voice Oohs"));
	m_comboVoices.AddString(_T("Synth Voice"));
	m_comboVoices.AddString(_T("Orchestra Hit"));
	m_comboVoices.AddString(_T("Trumpet"));
	m_comboVoices.AddString(_T("Trombone"));
	m_comboVoices.AddString(_T("Tuba"));
	m_comboVoices.AddString(_T("Muted Trumpet"));
	m_comboVoices.AddString(_T("French Horn"));
	m_comboVoices.AddString(_T("Brass Section"));
	m_comboVoices.AddString(_T("Synth Brass 1"));
	m_comboVoices.AddString(_T("Synth Brass 2"));
	m_comboVoices.AddString(_T("Soprano Sax"));
	m_comboVoices.AddString(_T("Alto Sax"));
	m_comboVoices.AddString(_T("Tenor Sax"));
	m_comboVoices.AddString(_T("Baritone Sax"));
	m_comboVoices.AddString(_T("Oboe"));
	m_comboVoices.AddString(_T("English Horn"));
	m_comboVoices.AddString(_T("Bassoon"));
	m_comboVoices.AddString(_T("Clarinet"));
	m_comboVoices.AddString(_T("Piccolo"));
	m_comboVoices.AddString(_T("Flute"));
	m_comboVoices.AddString(_T("Recorder"));
	m_comboVoices.AddString(_T("Pan Flute"));
	m_comboVoices.AddString(_T("Bottle Blow"));
	m_comboVoices.AddString(_T("Shakuhachi"));
	m_comboVoices.AddString(_T("Whistle"));
	m_comboVoices.AddString(_T("Ocarina"));
	m_comboVoices.AddString(_T("Lead 1 (square)"));
	m_comboVoices.AddString(_T("Lead 2 (sawtooth)"));
	m_comboVoices.AddString(_T("Lead 3 (caliope lead)"));
	m_comboVoices.AddString(_T("Lead 4 (chiff lead)"));
	m_comboVoices.AddString(_T("Lead 5 (charang)"));
	m_comboVoices.AddString(_T("Lead 6 (voice)"));
	m_comboVoices.AddString(_T("Lead 7 (fifths)"));
	m_comboVoices.AddString(_T("Lead 8 (brass + lead)"));
	m_comboVoices.AddString(_T("Pad 1 (new age)"));
	m_comboVoices.AddString(_T("Pad 2 (warm)"));
	m_comboVoices.AddString(_T("Pad 3 (polysynth)"));
	m_comboVoices.AddString(_T("Pad 4 (choir)"));
	m_comboVoices.AddString(_T("Pad 5 (bowed)"));
	m_comboVoices.AddString(_T("Pad 6 (metallic)"));
	m_comboVoices.AddString(_T("Pad 7 (halo)"));
	m_comboVoices.AddString(_T("Pad 8 (sweep)"));
	m_comboVoices.AddString(_T("FX 1 (rain)"));
	m_comboVoices.AddString(_T("FX 2 (soundtrack)"));
	m_comboVoices.AddString(_T("FX 3 (crystal)"));
	m_comboVoices.AddString(_T("FX 4 (atmosphere)"));
	m_comboVoices.AddString(_T("FX 5 (brightness)"));
	m_comboVoices.AddString(_T("FX 6 (goblins)"));
	m_comboVoices.AddString(_T("FX 7 (echoes)"));
	m_comboVoices.AddString(_T("FX 8 (sci-fi)"));
	m_comboVoices.AddString(_T("Sitar"));
	m_comboVoices.AddString(_T("Banjo"));
	m_comboVoices.AddString(_T("Shamisen"));
	m_comboVoices.AddString(_T("Koto"));
	m_comboVoices.AddString(_T("Kalimba"));
	m_comboVoices.AddString(_T("Bagpipe"));
	m_comboVoices.AddString(_T("Fiddle"));
	m_comboVoices.AddString(_T("Shanai"));
	m_comboVoices.AddString(_T("Tinkle Bell"));
	m_comboVoices.AddString(_T("Agogo"));
	m_comboVoices.AddString(_T("Steel Drums"));
	m_comboVoices.AddString(_T("Woodblock"));
	m_comboVoices.AddString(_T("Taiko Drum"));
	m_comboVoices.AddString(_T("Melodic Tom"));
	m_comboVoices.AddString(_T("Synth Drum"));
	m_comboVoices.AddString(_T("Reverse Cymbal"));
	m_comboVoices.AddString(_T("Guitar Fret Noise"));
	m_comboVoices.AddString(_T("Breath Noise"));
	m_comboVoices.AddString(_T("Seashore"));
	m_comboVoices.AddString(_T("Bird Tweet"));
	m_comboVoices.AddString(_T("Telephone Ring"));
	m_comboVoices.AddString(_T("Helicopter"));
	m_comboVoices.AddString(_T("Applause"));
	m_comboVoices.AddString(_T("Gunshot"));
}

void CConfigurationPage::PopulateChannel()
{
	m_comboChannel.Clear();
	for (int i = 0; i < 16; ++i)
	{
		ostringstream ossTemp;
		ossTemp << i;
		string csTemp = ossTemp.str();

		m_comboChannel.AddString(csTemp.c_str());
	}
}

void CConfigurationPage::PopulateDevice()
{
	m_comboDevice.Clear();
	m_mapDevice.clear();

	int nDevice = 0;
	int nNumDevs = midiOutGetNumDevs ();

	MIDIOUTCAPS moc ;
	
	if (!midiOutGetDevCaps (MIDIMAPPER, &moc, sizeof (moc)))
	{
		m_comboDevice.AddString(moc.szPname);
		m_mapDevice[moc.szPname] = MIDIMAPPER;
	}

	// Add the rest of the MIDI devices
	for (int i = 0 ; i < nNumDevs ; i++)
	{
		midiOutGetDevCaps (i, &moc, sizeof (moc)) ;
		m_comboDevice.AddString(moc.szPname) ;
		m_mapDevice[moc.szPname] = i;
	}
}
