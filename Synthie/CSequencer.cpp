#include "stdafx.h"
#include "CSequencer.h"

CSequencer::CSequencer()
{
    m_channels = 2;
    m_sampleRate = 44100.;
    m_samplePeriod = 1 / m_sampleRate;
    m_time = 0;
}
//! Start the synthesizer
void CSequencer::Start(void)
{
    m_time = 0;
    m_synthesizers.clear();
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

        // Call the generate function
        if (synth->Generate(frame))
        {
            // True, so Synthesizer still active
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
    m_synthesizers.clear();
}