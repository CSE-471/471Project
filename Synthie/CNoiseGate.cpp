#include "stdafx.h"
#include "CNoiseGate.h"
#include "CEffect.h"

CNoiseGate::CNoiseGate()
{
	
}

CNoiseGate::~CNoiseGate()
{
}

void CNoiseGate::Process(double* framein, double* frameout)
{
	double threshold = GetThreshold();
	double dry = GetDry();
	double wet = GetWet();

	if (framein[0] < threshold && framein[0] > -threshold)
	{
		m_gate_left -= 0.005;
		if (m_gate_left < 0) m_gate_left = 0;
	}
	else
	{
		m_gate_left += 0.005;
		if (m_gate_left > 1) m_gate_left = 1;
	}

	if (framein[1] < threshold && framein[1] > -threshold)
	{
		m_gate_right -= 0.005;
		if (m_gate_right < 0) m_gate_right = 0;
	}
	else
	{
		m_gate_right += 0.005;
		if (m_gate_right > 1) m_gate_right = 1;
	}

	frameout[0] = (dry * framein[0]) + (wet * framein[0] * m_gate_left);
	frameout[1] = (dry * framein[1]) + (wet * framein[1] * m_gate_right);
}

void CNoiseGate::Start()
{
	m_gate_left = 1;
	m_gate_right = 1;
}

bool CNoiseGate::Generate()
{
	return true;
}
