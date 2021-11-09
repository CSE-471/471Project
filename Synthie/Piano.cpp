/**
* Piano.cpp
* Seongjin Park
* The class that generates a dynamic sound of the acoustic piano.
*/

#include "stdafx.h"
#include "Piano.h"
#include "Note.h"
#include "Instrument.h"
#include <vector>


/**
* Constructor 
*/
CPiano::CPiano()
{
	m_duration = 1.0;
	m_sampletotal = 0;
	m_attack = 0.05;
	m_release = 0.05;
	m_time = 0;
}

/**
* Destructor
*/
CPiano::~CPiano()
{

}

/**
* Set up components for the piano to begin playing 
*/
void CPiano::Start()
{
	m_index = 0;
	m_dynamic = 0;
	m_sampletotal = int(m_waves.size());
}

/**
* Generate a piano sound 
*/
bool CPiano::Generate()
{
	if (m_index < m_sampletotal && m_time < m_duration)
	{
		m_frame[0] = (m_waves.at(m_index) / 32768.0);
		m_frame[1] = (m_waves.at(m_index) / 32768.0);
		m_index += 1;
	}
	else 
	{
		m_frame[0] = 0;
		m_frame[1] = 0;
		return false;
	}

	m_time += GetSamplePeriod();

	return true;
}

/**
* Set the individual note for the piano 
*/

void CPiano::SetNote(CNote* note)
{
	double ramp;

	m_duration += (int(m_waves.size()) / GetSampleRate());

	// Now adjust the frame to handle a case when wave needs to be cut off 
	for (int i = 0; i < int(m_waves.size()); i++)
	{
		// Read the component's sample and make it our resulting frame.
		if (m_time < m_attack)
		{
			ramp = m_dynamic * (m_time / m_attack);
		}
		else if (m_time > (int(m_waves.size()) / GetSampleRate()) - m_release)
		{
			ramp = m_dynamic * (((int(m_waves.size()) / GetSampleRate()) - m_time) / m_release);
		}

		m_waves.at(i) = short(m_waves.at(i) * ramp);

		m_time += GetSamplePeriod();
	}
}
