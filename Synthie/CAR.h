#pragma once
#include "CAudioNode.h"
#include "CSineWave.h"
class CAR :
    public CAudioNode
{
public:
    CAR::CAR();

    virtual void Start();
    virtual bool Generate();

    void SetSource(CAudioNode* node);
    void SetDuration(double d) { m_duration = d; }

private:
    CAudioNode*   m_node;
    double m_attack;
    double m_release;
    double m_duration;
    double m_time;
    double m_fadetime;
};

