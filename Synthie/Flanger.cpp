#include "stdafx.h"
#include "Flanger.h"

CFlanger::CFlanger()
{
}

CFlanger::~CFlanger()
{
}

void CFlanger::Process(double* frameIn, double* frameOut)
{
	double dry = GetDry();
	double wet = GetWet();

	// Calculate delay with the delay step
	double delay_step = (m_range * m_delay) * sin(2 * M_PI * m_rate);
	double new_delay = m_delay + delay_step;

	mWrloc = (mWrloc + 1) % MAXQUEUESIZE;
	m_queueL[mWrloc] = frameIn[0];

	// Read location
	int delay_length = int((new_delay * GetSampleRate() + 0.5)) * 2;
	int rdloc = (mWrloc + MAXQUEUESIZE - delay_length) % MAXQUEUESIZE;
}

void CFlanger::Start()
{
	mWrloc = 0;
	mRdloc = 0;
	m_queueL.resize(MAXQUEUESIZE);
	m_queueR.resize(MAXQUEUESIZE);
	m_delay = GetDelay();
	m_rate = GetRate();
	m_range = GetRange();
}

bool CFlanger::Generate()
{
	return true;
}
