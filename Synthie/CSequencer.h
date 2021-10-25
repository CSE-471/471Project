#pragma once
#pragma comment(lib, "msxml2.lib")
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
	//! Get the time since we started generating audio
	double GetTime() { return m_time; }

private:
	double m_time;
	int		m_channels;
	double	m_sampleRate;
	double	m_samplePeriod;
	std::list<CSynthesizer*> m_synthesizers;
};

