#include "stdafx.h"
#include "CAdditive.h"
#include "Notes.h"

CAdditive::CAdditive()
{
    m_duration = 0.1;
	m_nyquist = 20000;
}

CAdditive::CAdditive(double bpm)
{
    m_duration = 0.1;
    m_bpm = bpm;
	m_nyquist = 20000;

}

CAdditive::~CAdditive()
{
}

void CAdditive::Start()
{
    m_ar.SetSource(&m_sinewave);
    m_ar.SetSampleRate(GetSampleRate());
    m_ar.Start();
}

bool CAdditive::Generate()
{
	// Tell the component to generate an audio 
	bool valid = m_ar.Generate();
	// Read the component's sample and make it our resulting frame.
	m_frame[0] = m_ar.Frame(0);
	m_frame[1] = m_ar.Frame(1);

	double phase = m_sinewave.GetPrev();

	// Add harmonics
	for (int i = 0; i < m_harmonics.size(); i++)
	{
		// Check for nyquist first
		if ((i + 2) * m_freq > m_nyquist)
		{
			break; // End the loop
		}
		m_frame[0] += (m_harmonics[i] / (i+2)) * sin(phase * 2 * PI * ((i+2) * m_freq));
		m_frame[1] += (m_harmonics[i] / (i + 2)) * sin(phase * 2 * PI * ((i + 2) * m_freq));
	}


	// Update time
	m_time += GetSamplePeriod();

	// We return true until the time reaches the duration returned by the AR object.
	return valid;
}

void CAdditive::SetNote(CNote* note)
{

	// Get a list of all attribute nodes and the
// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			// SetDuration(value.dblVal); // play the note for the duration in terms of seconds
			m_ar.SetDuration(value.dblVal * (NUM_SECS_IN_MINUTE / m_bpm));

		}
		else if (name == "note") // Notes for additive should just be a freq value
		{
			value.ChangeType(VT_R8);
			m_freq = value.dblVal;
			SetFreq(m_freq);
		}
		else if (name == "a1")
		{
			value.ChangeType(VT_R8);
			SetAmplitude(value.dblVal);
		}
		else if (name == "a2")
		{
			value.ChangeType(VT_R8);
			m_harmonics.push_back(value.dblVal);
		}
		else if (name == "a3")
		{
			value.ChangeType(VT_R8);
			m_harmonics.push_back(value.dblVal);
		}
		else if (name == "a4")
		{
			value.ChangeType(VT_R8);
			m_harmonics.push_back(value.dblVal);
		}
		else if (name == "a5")
		{
			value.ChangeType(VT_R8);
			m_harmonics.push_back(value.dblVal);
		}
		else if (name == "a6")
		{
			value.ChangeType(VT_R8);
			m_harmonics.push_back(value.dblVal);
		}
		else if (name == "a7")
		{
			value.ChangeType(VT_R8);
			m_harmonics.push_back(value.dblVal);
		}
		else if (name == "a8")
		{
			value.ChangeType(VT_R8);
			m_harmonics.push_back(value.dblVal);
		}
		// Send attribute
		// send0 is dry audio
		else if (name == "send0")
		{
			value.ChangeType(VT_R8);
			SetSend(0, value.dblVal);
		}
		//send1 is noise gate
		else if (name == "send1")
		{
			value.ChangeType(VT_R8);
			SetSend(1, value.dblVal);
		}
		//send2 is compressor
		else if (name == "send2")
		{
			value.ChangeType(VT_R8);
			SetSend(2, value.dblVal);
		}
		//send3 is ...
		else if (name == "send3")
		{
			value.ChangeType(VT_R8);
			SetSend(3, value.dblVal);
		}
		//send4 is ...
		else if (name == "send4")
		{
			value.ChangeType(VT_R8);
			SetSend(4, value.dblVal);
		}
	}
}
