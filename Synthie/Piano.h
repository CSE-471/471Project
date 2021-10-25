/**
* Piano.h
* Seongjin Park
* The class that generates a dynamic sound of the acoustic piano.
*/

#pragma once
#include "CSynthesizer.h"
#include "CNote.h"
#include <vector>


class CPiano :
    public CSynthesizer
{
public:
    // constructor
    CPiano();

    // Destructor
    ~CPiano();

    // Play notes to generate a piano sound 
    // virtual void Play() override;

    // Determine when pedal is pressed
    bool PedalPressed();

    // Calculate duration based on the use of pedal and duration of key pressure
    double CalcDuration();

    // Get the dynamic
    double GetDynamic() { return m_dynamic; }

    // Calculate dynamic based on the key pressure 
    double CalcDynamic();


private:
    // Collection of notes used for piano
    std::vector<CNote> m_notes;

    bool m_pedal = false;
    bool m_pressed = false;

    double m_dynamic = 0;
};

