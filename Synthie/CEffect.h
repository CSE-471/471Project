#pragma once
#include "Instrument.h"
#include <vector>

class CEffect : public CInstrument
{
public:
	// Constructor
	CEffect();

	// Destructor
	~CEffect();

	// Virtual function process the effect on audio
	virtual void Process(double* frameIn, double* frameOut);

	virtual void SetNote(CNote* note) override;

	// Get the threshold of the effect
	double GetThreshold() { return m_threshold; }

	// Get the dry value of the effect
	double GetDry() { return m_dry; }

	// Get the wet value of the effect
	double GetWet() { return m_wet; }

	// Get the delay value of the effect
	double GetDelay() { return m_delay; }

private:

	// Controllable effects sends
	double m_wet;
	double m_dry;

	// Threshold for noise gating and compression
	double m_threshold;
	double m_delay;

	std::vector<double> m_queueL;
	std::vector<double> m_queueR;

};

