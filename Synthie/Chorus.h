#pragma once
#include "CEffect.h"
class CChorus : public CEffect
{
public:
    CChorus();
    // Destructor
    ~CChorus();

    virtual void Process(double* frameIn, double* frameOut) override;

    //Start
    virtual void Start() override;

    // Generate
    virtual bool Generate() override;

private:
    std::vector<double> m_queueL;
    std::vector<double> m_queueR;
    int mWrloc;
    int mRdloc;
    const int MAXQUEUESIZE = 200000;
    const double M_PI = 3.14159265359;
    double m_delay;
    double m_rate;
    double m_range;
};