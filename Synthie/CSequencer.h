#pragma once
#include "msxml2.h"
#include "CSynthesizer.h"
#include <list>
class CSequencer
{
public:
	CSequencer::CSequencer();
	//! Number of audio channels
	int GetNumChannels() { return m_channels; }

	//! Sample rate in samples per second
	double GetSampleRate() { return m_sampleRate; }

	//! Sample period in seconds (1/samplerate)
	double GetSamplePeriod() { return m_samplePeriod; }

	//! Set the number of channels
	void SetNumChannels(int n) { m_channels = n; }

	//! Set the sample rate
	void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1.0 / s; }
	void Start(void);
	bool Generate(double* frame);
	void Clear(void);
	void OpenScore(CString& filename);
	void XmlLoadScore(IXMLDOMNode* xml);
	void XmlLoadSynthesizer(IXMLDOMNode* xml);
	//! Get the time since we started generating audio
	double GetTime() { return m_time; }

private:
	double m_time;
	int		m_channels;
	double	m_sampleRate;
	double	m_samplePeriod;
	std::list<CSynthesizer*> m_synthesizers;
	double  m_bpm;                  //!< Beats per minute
	int     m_beatspermeasure;  //!< Beats per measure
	double  m_secperbeat;        //!< Seconds per beat
};


#pragma comment(lib, "msxml2.lib")

