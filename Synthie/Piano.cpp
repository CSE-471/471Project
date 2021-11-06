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
	m_time = 0;
	m_sampletotal = int(m_waves.size());
}

/**
* Generate a piano sound 
*/
bool CPiano::Generate()
{
	bool valid = false;

	if (m_index < m_sampletotal)
	{
		valid = true;
		m_frame[0] = m_waves.at(m_index) / 32768.0;
		m_frame[1] = m_frame[0];
		m_index += 1;
	}
	else 
	{
		valid = false;
		m_frame[0] = 0;
		m_frame[1] = m_frame[0];
		//m_index = 0;
	}

	m_time += GetSamplePeriod();
	if (m_time >= m_duration)
	{
		valid = false;
	}

	return valid;
}

/**
* Set the individual note for the piano 
*/

void CPiano::SetNote(CNote* note)
{
}
