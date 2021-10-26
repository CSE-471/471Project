#include "stdafx.h"
#include "CSequencer.h"
#include "xmlhelp.h"

CSequencer::CSequencer()
{
    CoInitialize(NULL);

    m_channels = 2;
    m_sampleRate = 44100.;
    m_samplePeriod = 1 / m_sampleRate;
    m_time = 0;

    m_bpm = 120;
    m_secperbeat = 0.5;
    m_beatspermeasure = 4;
}

//! Start the synthesizer
void CSequencer::Start(void)
{
    m_time = 0;
    //m_synthesizers.clear();
}

//! Generate one audio frame
bool CSequencer::Generate(double* frame)
{
    //
    // Phase 2: Clear all channels to silence 
    //

    for (int c = 0; c < GetNumChannels(); c++)
    {
        frame[c] = 0;
    }

    //
    // Phase 3: Play an active instruments
    //

    //
    // We have a list of active (playing) instruments.  We iterate over 
    // that list.  For each instrument we call generate If an instrument is done (Generate()
    // returns false), we remove it from the list.
    //

    for (list<CSynthesizer*>::iterator node = m_synthesizers.begin(); node != m_synthesizers.end(); )
    {
        // Since we may be removing an item from the list, we need to know in 
        // advance, what is after it in the list.  We keep that node as "next"
        list<CSynthesizer*>::iterator next = node;
        next++;

        // Get a pointer to the allocated instrument
        CSynthesizer* synth = *node;

        // Configure the instrument object
        if (synth != NULL)
        {
            synth->SetSampleRate(GetSampleRate());
        }

        // Call the generate function
        if (synth->Generate(frame))
        {
        }
        else
        {
            // If we returned false, the instrument is done.  Remove it
            // from the list and delete it from memory.
            m_synthesizers.erase(node);
            delete synth;
        }

        // Move to the next instrument in the list
        node = next;
    }


    //
    // Phase 5: Determine when we are done
    //

    // We are done when there is nothing to play.  We'll put something more 
    // complex here later.
    return !m_synthesizers.empty();
}

void CSequencer::Clear(void)
{
    for (CSynthesizer* synth : m_synthesizers)
    {
        delete(synth);
    }
    m_synthesizers.clear();
}

void CSequencer::OpenScore(CString& filename)
{
    Clear();

    //
    // Create an XML document
    //

    CComPtr<IXMLDOMDocument>  pXMLDoc;
    bool succeeded = SUCCEEDED(CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
        IID_IXMLDOMDocument, (void**)&pXMLDoc));
    if (!succeeded)
    {
        AfxMessageBox(L"Failed to create an XML document to use");
        return;
    }

    // Open the XML document
    VARIANT_BOOL ok;
    succeeded = SUCCEEDED(pXMLDoc->load(CComVariant(filename), &ok));
    if (!succeeded || ok == VARIANT_FALSE)
    {
        AfxMessageBox(L"Failed to open XML score file");
        return;
    }

    //
    // Traverse the XML document in memory!!!!
    // Top level tag is <score>
    //

    CComPtr<IXMLDOMNode> node;
    pXMLDoc->get_firstChild(&node);
    for (; node != NULL; NextNode(node))
    {
        // Get the name of the node
        CComBSTR nodeName;
        node->get_nodeName(&nodeName);

        if (nodeName == "score")
        {
            XmlLoadScore(node);
        }
    }
}

void CSequencer::XmlLoadScore(IXMLDOMNode* xml)
{
    // Get a list of all attribute nodes and the
// length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    xml->get_attributes(&attributes);
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

        if (name == L"bpm")
        {
            value.ChangeType(VT_R8);
            m_bpm = value.dblVal;
            m_secperbeat = 1 / (m_bpm / 60);
        }
        else if (name == L"beatspermeasure")
        {
            value.ChangeType(VT_I4);
            m_beatspermeasure = value.intVal;
        }

    }


    CComPtr<IXMLDOMNode> node;
    xml->get_firstChild(&node);
    for (; node != NULL; NextNode(node))
    {
        // Get the name of the node
        CComBSTR name;
        node->get_nodeName(&name);

        if (name == L"synthesizer")
        {
            XmlLoadSynthesizer(node);
        }
    }
}

void CSequencer::XmlLoadSynthesizer(IXMLDOMNode* xml)
{
    wstring synthesizer = L"";

    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    xml->get_attributes(&attributes);
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

        // Get the value of the attribute.  
        CComVariant value;
        attrib->get_nodeValue(&value);

        if (name == "synthesizer")
        {
            synthesizer = value.bstrVal;
        }

    }


    CComPtr<IXMLDOMNode> node;
    xml->get_firstChild(&node);
    for (; node != NULL; NextNode(node))
    {
        // Get the name of the node
        CComBSTR name;
        node->get_nodeName(&name);

        if (name == L"instrument")
        {
            if (synthesizer == L"Additive")
            {
                CSynthesizer* synth = new CSynthesizer(m_bpm, m_beatspermeasure, m_secperbeat);
                m_synthesizers.push_back(synth); // Make this Cadditive once that's setup
                m_synthesizers.back()->XmlLoadInstrument(node);
                m_synthesizers.back()->Start();
            }
            else
            {
                m_synthesizers.push_back(&CSynthesizer());
                m_synthesizers.back()->XmlLoadInstrument(node);
                m_synthesizers.back()->Start();
            }
        }

    }

}