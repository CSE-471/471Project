#include "stdafx.h"
#include "CEffect.h"

CEffect::CEffect()
{
	SetSend(0, 1.0);
	SetSend(1, 0.0);
	SetSend(2, 0.0);
	SetSend(3, 0.0);
	SetSend(4, 0.0);
}

CEffect::~CEffect()
{
}

void CEffect::Process(double* frameIn, double* frameOut)
{
}

void CEffect::SetNote(CNote* note)
{
	// Do work for set note here
	
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

		// Wet attribute
		if (name == "wet")
		{
			value.ChangeType(VT_R8);
			m_wet = value.dblVal;
		}
		// Dry attribute
		else if (name == "dry")
		{
			value.ChangeType(VT_R8);
			m_dry = value.dblVal;
		}
		else if (name == "delay")
		{
			value.ChangeType(VT_R8);
			m_delay = value.dblVal;
		}
		// Threshold attribute
		else if (name == "threshold")
		{
			value.ChangeType(VT_R8);
			m_threshold = value.dblVal;
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
