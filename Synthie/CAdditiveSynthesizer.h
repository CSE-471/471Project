#pragma once
#include "AudioNode.h"
class CAdditiveSynthesizer :
    public CAudioNode
{
public:
	CAdditiveSynthesizer();
	virtual ~CAdditiveSynthesizer();

	virtual void Start() override;
	virtual bool Generate() override;
	void SetFreq(double f) { m_freq = f; }
	void SetAmplitude(int i, double amp) { m_harmonics[i] = amp; }
	void SetCross(int i, double amp) { m_cross[i] = amp; }

	//vibrato rate/freq
	void SetVibAmp(double amp) { m_vAmp = amp; }
	void SetVibFreq(double f) { m_vFreq = f; }

	void SetDuration(double d) { m_duration = d; }

private:
	double m_vAmp = 0;
	double m_vFreq = 0;
	double m_vibrato = 0;
	double m_time = 0;
	double m_duration = 0;
	double m_nyquist = 0;
	double m_freq;
	double m_phase = 0;
	double m_harmonics[8] = { 0, 0, 0, 0, 0, 0, 0, 0};
	double m_cross[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
};

