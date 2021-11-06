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
    
    //Constructor that accepts bpm 
    CPiano(double bpm);

    // Set up values to prepare piano audio 
    virtual void Start(void);

    // Set an individual note for piano 
    virtual void SetNote(CNote* note);

    // Generate function overrided 
    virtual bool Generate();

    void SetDuration(double duration) { m_duration = duration; }
    void SetPedal(bool pedal) { m_pedal = pedal; }
    void SetWaves(std::vector<short> waves) { m_waves = waves; }

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

    double m_duration;
    double m_time;
    int m_index;
    int m_sampletotal;

    bool m_pedal = false;
    std::vector<short> m_waves;

    double m_dynamic = 0;
};

