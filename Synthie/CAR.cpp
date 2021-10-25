#include "stdafx.h"
#include "CAR.h"

CAR::CAR()
{
	m_attack = 0.05;
	m_release = 0.05;
	m_duration = 0.1; // Set by SetNote in CToneInstrument throughout playback
	m_time = 0;
}

void CAR::Start()
{
	m_time = 0;
	m_fadetime = 0;
}

bool CAR::Generate()
{
	// Read the component's sample and make it our resulting frame.
	m_frame[0] = m_node->Frame(0);
	m_frame[1] = m_node->Frame(1);
	const double beat_dur = m_duration * (1 / (m_bpm / 60));

	double ramp;

	if (m_time < m_attack)
	{
		ramp = (m_time / m_attack);
	}
	else if (m_time > (beat_dur - m_release))
	{
		ramp = 1 - ((m_time - m_fadetime) / m_release);
	}
	else
	{
		ramp = 1;
		m_fadetime = m_time; // Record the time fading begins for fade calculation
	}

	m_frame[0] = m_frame[0] * ramp;
	m_frame[1] = m_frame[1] * ramp;

	// Update time
	m_time += GetSamplePeriod();

	// We return true until the time reaches the duration.
	return m_time < beat_dur;
}

void CAR::SetSource(CAudioNode* node)
{
	m_node = node;
}
