#pragma once
class CEffect
{
public:
	// Constructor
	CEffect::CEffect();

	// Destructor
	CEffect::~CEffect();

private:

	// Controllable effects sends
	double m_wet;
	double m_dry;

	// Threshold for noise gating and compression
	double m_threshold;
	double m_delay;

};

