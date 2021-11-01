/**
* Piano.h
* Seongjin Park
* The class that generates a dynamic sound of the acoustic piano.
*/

#pragma once
#include "Instrument.h"
#include "SineWave.h"
#include "Note.h"
#include <vector>


class CPiano :
    public CInstrument 
{
public:
    // constructor
    CPiano();

    // Destructor
    ~CPiano();

    // Set up values to prepare piano audio 
    void Start(void);

    // Set an individual note for piano 
    virtual void SetNote(CNote* note) {};

    // Generate function overrided 
    virtual bool Generate() { return false; }

    // Play notes to generate a piano sound (Similar to Generate function)
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

