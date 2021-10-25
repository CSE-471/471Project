#pragma once
#include "CInstrument.h"
#include "CSineWave.h"
#include "CAR.h"
class CToneInstrument :
    public CInstrument
{
public:
    CToneInstrument::CToneInstrument();
    virtual void Start();
    virtual bool Generate();

    void SetNote(CNote* note);

    void SetFreq(double f) { m_sinewave.SetFreq(f); }
    void SetAmplitude(double a) { m_sinewave.SetAmplitude(a); }

private:
    CAR m_ar;
    CSineWave   m_sinewave;
    double m_time;
    double m_duration;
};

