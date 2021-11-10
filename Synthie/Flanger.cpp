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
	int level = 2;

	// Calculate delay with the delay step
	double delay_step = (m_range * m_delay) * sin(2 * M_PI * m_rate);
	double new_delay = m_delay + delay_step;

	mWrloc = (mWrloc + 1) % MAXQUEUESIZE;
	m_queueL[mWrloc] = frameIn[0];

	// Read location
	int delay_length = int((new_delay * GetSampleRate() + 0.5)) * 2;
	int rdloc = (mWrloc + MAXQUEUESIZE - delay_length) % MAXQUEUESIZE;

	// Wet and dry
	frameOut[0] = (frameIn[0] / 3) + (m_queueL[rdloc] / 3) + (m_outl[rdloc] * level) / 3;
	frameOut[0] *= wet;
	frameOut[0] += frameIn[0] * dry;
	m_outl[mWrloc] = frameOut[0];

	// right channel
	m_queueR[mWrloc] = frameIn[1];
	frameOut[1] = (frameIn[1] / 3) + (m_queueR[(rdloc+1) % MAXQUEUESIZE]  / 3) + (m_outr[(rdloc + 1) % MAXQUEUESIZE] * level) / 3;
	frameOut[1] *= wet;
	frameOut[1] += frameIn[1] * dry;
	m_outr[mWrloc] = frameOut[1];
}

void CFlanger::Start()
{
	mWrloc = 0;
	mRdloc = 0;
	m_queueL.resize(MAXQUEUESIZE);
	m_queueR.resize(MAXQUEUESIZE);
	m_outl.resize(MAXQUEUESIZE);
	m_outr.resize(MAXQUEUESIZE);
	m_delay = GetDelay();
	m_rate = GetRate();
	m_range = GetRange();
}

bool CFlanger::Generate()
{
	return true;
}
