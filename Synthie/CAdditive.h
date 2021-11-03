#pragma once
#include "Instrument.h"
#include "SineWave.h"
#include "AR.h"
#include "CAdditiveSynthesizer.h"
#include <vector>
#include <map>
class CAdditive :
    public CInstrument
{
public:
	CAdditive();
	CAdditive(double bpm);
	virtual ~CAdditive();
public:
	const double NUM_SECS_IN_MINUTE = 60.0;
	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f) { m_additive.SetFreq(f); }
	void SetDuration(double d) { m_duration = d; }
	virtual void SetNote(CNote* note);
private:
	CAdditiveSynthesizer   m_additive;
	CAR m_ar;
	double m_duration;
	double m_time;
	double m_freq;
	double m_second;
	double m_amplitude;
	bool m_glissando;
	bool m_envelope;
	std::vector<double> m_harmonics{ 0, 0, 0, 0, 0, 0, 0 };
	std::vector<double> m_secondHarmonics{ 0, 0, 0, 0, 0, 0, 0 };
	std::map<std::string, double> m_harm;
	double m_nyquist;
	double m_vibrato;
	double m_vFreq;
	double m_vAmp;
};

