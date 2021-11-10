#pragma once
#include "CEffect.h"
class CFlanger :
    public CEffect
{
public:
    CFlanger();
    ~CFlanger();
    virtual void Process(double* frameIn, double* frameOut) override;

    //Start
    virtual void Start() override;

    // Generate
    virtual bool Generate() override;

private:
    // Left and right queue
    std::vector<double> m_queueL;
    std::vector<double> m_queueR;

    // vectors to keep track of left and right output
    std::vector<double> m_outl;
    std::vector<double> m_outr;

    int mWrloc;
    int mRdloc;
    const int MAXQUEUESIZE = 200000;
    const double M_PI = 3.14159265359;
    double m_delay;
    double m_rate;
    double m_range;
};

