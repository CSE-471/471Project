#include "stdafx.h"
#include "CAdditive.h"
#include "Notes.h"
#include <string>
#include <vector>

using namespace std;

CAdditive::CAdditive()
{
	m_nyquist = 20000;
}

CAdditive::CAdditive(double bpm)
{
    m_bpm = bpm;
	m_nyquist = 20000;
}

CAdditive::~CAdditive()
{
}

void CAdditive::Start()
{
    m_ar.SetSource(&m_additive);
    m_ar.SetSampleRate(GetSampleRate());
    m_ar.Start();
}

bool CAdditive::Generate()
{
	bool valid = m_ar.Generate();

	m_frame[0] = m_ar.Frame(0);
	m_frame[1] = m_ar.Frame(1);

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
			m_additive.SetDuration(value.dblVal * (NUM_SECS_IN_MINUTE / m_bpm));
			m_duration = value.dblVal * (NUM_SECS_IN_MINUTE / m_bpm);

		}
		else if (name == "note") // Notes for additive should just be a freq value
		{
			//value.ChangeType(VT_R8);
			//m_freq = value.dblVal;
			//SetFreq(m_freq);
			SetFreq(NoteToFrequency(value.bstrVal));
		}
		else if (name == "vAmp")
		{
			value.ChangeType(VT_R8);
			m_vAmp = value.dblVal;
			m_additive.SetVibAmp(m_vAmp);
		}
		else if (name == "vFreq")
		{
			value.ChangeType(VT_R8);
			m_vFreq = value.dblVal;
			m_additive.SetVibFreq(m_vFreq);
		}
		//else if (name == "vibrato")
		//{
		//	// Need to extract both vibrato components
		//	wstring comp(value.bstrVal);
		//	wstring vString(comp.begin(), comp.end());

		//	wstring component;
		//	vector<wstring> vComponent;
		//	for (int i = 0; i <= vString.size(); i++)
		//	{
		//		if (vString[i] != ' ')
		//		{
		//			component += vString[i];
		//		}
		//		else if (vString[i] == ' ' && component.size() >= 1)
		//		{
		//			vComponent.push_back(component);
		//			component.clear();
		//		}
		//	}

		//	if (component.size() >= 1)
		//	{
		//		vComponent.push_back(component);
		//		component.clear();
		//	}

		//	m_vAmp = stof(vComponent[0]);
		//	m_vFreq = stof(vComponent[1]);

		//	m_additive.SetVibAmp(m_vAmp);

		//	m_additive.SetVibFreq(m_vFreq);
		//}
		else if (name == "a1")
		{
			value.ChangeType(VT_R8);
			m_amplitude = value.dblVal;
			m_additive.SetAmplitude(0, value.dblVal);
		}
		else if (name == "a2")
		{
			value.ChangeType(VT_R8);
			m_additive.SetAmplitude(1, value.dblVal);
		}
		else if (name == "a3")
		{
			value.ChangeType(VT_R8);
			m_additive.SetAmplitude(2, value.dblVal);
		}
		else if (name == "a4")
		{
			value.ChangeType(VT_R8);
			m_additive.SetAmplitude(3, value.dblVal);
		}
		else if (name == "a5")
		{
			value.ChangeType(VT_R8);
			m_additive.SetAmplitude(4, value.dblVal);
		}
		else if (name == "a6")
		{
			value.ChangeType(VT_R8);
			m_additive.SetAmplitude(5, value.dblVal);
		}
		else if (name == "a7")
		{
			value.ChangeType(VT_R8);
			m_additive.SetAmplitude(6, value.dblVal);
		}
		else if (name == "a8")
		{
			value.ChangeType(VT_R8);
			m_additive.SetAmplitude(7, value.dblVal);
		}
		else if (name == "b1")
		{
			value.ChangeType(VT_R8);
			m_additive.SetCross(0, value.dblVal);
		}
		else if (name == "b2")
		{
			value.ChangeType(VT_R8);
			m_additive.SetCross(1, value.dblVal);
		}
		else if (name == "b3")
		{
			value.ChangeType(VT_R8);
			m_additive.SetCross(2, value.dblVal);
		}
		else if (name == "b4")
		{
			value.ChangeType(VT_R8);
			m_additive.SetCross(3, value.dblVal);
		}
		else if (name == "b5")
		{
			value.ChangeType(VT_R8);
			m_additive.SetCross(4, value.dblVal);
		}
		else if (name == "b6")
		{
			value.ChangeType(VT_R8);
			m_additive.SetCross(5, value.dblVal);
		}
		else if (name == "b7")
		{
			value.ChangeType(VT_R8);
			m_additive.SetCross(6, value.dblVal);
		}
		else if (name == "b8")
		{
			value.ChangeType(VT_R8);
			m_additive.SetCross(7, value.dblVal);
		}
	}
}
