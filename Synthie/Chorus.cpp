#include "stdafx.h"
#include "Chorus.h"

CChorus::CChorus()
{
}

CChorus::~CChorus()
{
}

void CChorus::Process(double* frameIn, double* frameOut)
{
	double dry = GetDry();
	double wet = GetWet();

	// Calculate delay with the delay step
	double delay_step = (m_range * m_delay) * sin(2 * PI * m_rate);
	double new_delay = m_delay + delay_step;

	mWrloc = (mWrloc + 1) % MAXQUEUESIZE;
	m_queueL[mWrloc] = frameIn[0];

	// Read location
	int delay_length = int(( new_delay * GetSampleRate() + 0.5)) * 2;
	int rdloc = (mWrloc + MAXQUEUESIZE - delay_length) % MAXQUEUESIZE;

	frameOut[0] = frameIn[0] / 2 + m_queueL[rdloc] / 2;
	frameOut[0] *= wet;
	frameOut[0] += frameIn[0] * dry;

	mWrloc = (mWrloc + 1) % MAXQUEUESIZE;
	m_queueR[mWrloc] = frameIn[1];

	frameOut[1] = frameIn[1] / 2 + m_queueL[rdloc] / 2;
	frameOut[1] *= wet;
	frameOut[1] += frameIn[1] * dry;
}

void CChorus::Start()
{
	mWrloc = 0;
	mRdloc = 0;
	m_queueL.resize(MAXQUEUESIZE);
	m_queueR.resize(MAXQUEUESIZE);
	m_delay = GetDelay();
	m_rate = GetRate();
	m_range = GetRange();
}

bool CChorus::Generate()
{
	return true;
}
