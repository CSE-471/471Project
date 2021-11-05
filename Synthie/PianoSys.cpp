/**
* PianoSys.cpp
* Seongjin Park
* system class that creates a piano intrument. 
*/

#include "stdafx.h"
#include "PianoSys.h"
#include "Note.h"
#include <vector>


/**
* Constructor
*/
CPianoSys::CPianoSys()
{
	m_beat = 0;
	m_duration = 0;
	m_pedalpress = false;
}

/**
* Destructor
*/
CPianoSys::~CPianoSys()
{

}


/**
* Set the piano instrument in this system 
*/
CPiano* CPianoSys::SetPiano(CNote* note)
{
	// Create a piano instrument 
	CPiano* piano = new CPiano();


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


		// Find beat, duration and pedal 

		if (name == L"beat")
		{
			value.ChangeType(VT_R8);
			m_beat = value.dblVal;
		}

		if (name == L"duration")
		{
			value.ChangeType(VT_R8);
			m_duration = value.dblVal;
		}

		if (name == L"pedald")
		{
			m_pedalpress = true;
		}
		
		if (name == L"pedalu")
		{
			m_pedalpress = false;
		}

		// Now Load the wav file 
		if (name == "note")
		{
			char filename[200];
			value.ChangeType(VT_BSTR);
			wcstombs(filename, value.bstrVal, 200);
			OpenWavFile(filename);
		}
	}

	piano->SetBeat(m_beat);
	piano->SetDuration(m_duration);
	piano->SetPedal(m_pedalpress);
	piano->SetWaves(m_waves);

	return piano;
}

/**
* Open the audio file from the piano wav folder 
*/
bool CPianoSys::OpenWavFile(const char* filename)
{
	CDirSoundSource file;
	bool opened = false;

	Clear();

	if (file.Open(filename) == true)
	{
		opened = true; 
		for (int i = 0; i < file.NumSampleFrames(); i++)
		{
			short audio[2];
			file.ReadFrame(audio);
			m_waves.push_back(audio[0]);

		}
	}

	else
	{
		opened = false;
		CString mes = L"Unable to open wav file: ";
		mes += filename;
		AfxMessageBox(mes);
	}

	file.Close();
	return opened;
}

/**
* Clear out wav frames when a new file is called 
*/
void CPianoSys::Clear()
{
	m_waves.clear();
}