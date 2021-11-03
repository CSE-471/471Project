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
	SetSampleRate(GetSampleRate());
	m_index = 0;
	m_sampletotal = 0;
}

/**
* Generate a piano sound 
*/
bool CPiano::Generate()
{
	bool gen = false;

	if (m_index < m_sampletotal)
	{
		gen = true;
		m_frame[0] = m_waves[m_index] * 32768;
		m_frame[1] = m_frame[0];
		m_index += 1;
	}
	else 
	{
		gen = false;
		m_frame[0] = 0;
		m_frame[1] = m_frame[0];
		m_index = 0;
	}


	return gen;
}

/**
* Set the individual note for the piano 
*/

void CPiano::SetNote(CNote* note)
{
	m_sampletotal = int(m_waves.size());
}
