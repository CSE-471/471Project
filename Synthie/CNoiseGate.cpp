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
	double gain = 0;
	if (framein[0] < threshold)
	{
		gain = 0;
	}
	else
	{
		gain = 1;
	}

	if (framein[1] < threshold)
	{
		gain = 0;
	}
	else
	{
		gain = 1;
	}
	frameout[0] = (dry + wet) * framein[0] * gain;
	frameout[1] = (dry + wet) * framein[1] * gain;
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
