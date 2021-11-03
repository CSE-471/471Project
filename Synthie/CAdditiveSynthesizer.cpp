#include "stdafx.h"
#include "CAdditiveSynthesizer.h"

CAdditiveSynthesizer::CAdditiveSynthesizer()
{
	// Initialize vector to zero
	for (int i = 0; i < 8; i++)
	{
		m_harmonics[i] = 0;
		m_cross[i] = 0;
	}

	m_nyquist = GetSampleRate() / 2;
}


CAdditiveSynthesizer::~CAdditiveSynthesizer()
{
}

void CAdditiveSynthesizer::Start()
{
	m_phase = 0;
	m_vibrato = 0;
	m_time = 0;
}

bool CAdditiveSynthesizer::Generate()
{
	double output = 0;
	double temp_primary = 0;
	double temp_cross = 0;

	// Process cross fading if cross-fade vector is in use
	double time_frac = (1 - (m_time / m_duration)); // Starts at 1, declines to 0

	for (int i = 0; i < 8; i++)
	{
		// Check for nyquist before adding
		if (m_freq * (i + 1) > m_nyquist)
		{
			break;
		}
		// Add every provided harmonic to the sample (include the vibrato freq)
		temp_primary = (m_harmonics[i] / (i+1)) * sin(m_phase * (i + 1) + sin(m_vibrato));
		temp_cross = (m_cross[i] / (i + 1)) * sin(m_phase * (i + 1) + sin(m_vibrato));

		if (temp_primary != 0 && temp_cross == 0)
		{
			output += temp_primary;
		}
		else if(temp_primary == 0 && temp_cross != 0)
		{
			output += temp_cross;
		}
		else
		{
			output += (time_frac * temp_primary) + ((1 - time_frac) * temp_cross);
		}

		//output += (time_frac * temp_primary) + ((1 - time_frac) * temp_cross);
		//output += (m_harmonics[i] / (i + 1)) * sin(m_phase * (i + 1) + sin(m_vibrato));
	}

	m_frame[0] = output ;
	m_frame[1] = output ;

	m_vibrato += m_vFreq * GetSamplePeriod() * 2 * PI;
	m_phase += (m_freq + m_vAmp * sin(m_vibrato)) * GetSamplePeriod() * 2 * PI;

	m_time += GetSamplePeriod();

	return true;
}