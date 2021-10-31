#pragma once
#include "CEffect.h"
class CNoiseGate : public CEffect
{
public:
    CNoiseGate();
    virtual ~CNoiseGate();

    virtual void Process(double* frameIn, double* frameOut) override;

    //Start
    virtual void Start() override;

    // Generate
    virtual bool Generate() override;



private:
    double m_gate_left;
    double m_gate_right;
};

