#pragma once
#include "CEffect.h"

class CCompression :
    public CEffect
{
public:
    CCompression();
    // Destructor
    ~CCompression();

    virtual void Process(double* frameIn, double* frameOut) override;

    //Start
    virtual void Start() override;

    // Generate
    virtual bool Generate() override;
};

