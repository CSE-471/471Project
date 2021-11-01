#include "stdafx.h"
#include "Compression.h"

CCompression::CCompression()
{
}

CCompression::~CCompression()
{
}

void CCompression::Process(double* frameIn, double* frameOut)
{
	double threshold = GetThreshold();
	double dry = GetDry();
	double wet = GetWet();

	double ratio = 1.5; // ratio for the compression effect

	// First channel
	if (frameIn[0] > threshold || frameIn[0] < -threshold)
	{
		double delta = frameIn[0] - threshold;
		double compressed = (delta / ratio) + threshold;
		frameOut[0] = dry * frameIn[0] + wet * compressed;

	}
	// Uncompressed case
	else
	{
		frameOut[0] = wet * frameIn[0];
	}

	// Second channel
	if (frameIn[1] > threshold || frameIn[1] < -threshold)
	{
		double delta = frameIn[1] - threshold;
		double compressed = (delta / ratio) + threshold;
		frameOut[1] = dry * frameIn[1] + wet * compressed;

	}
	// Uncompressed case
	else
	{
		frameOut[1] = wet * frameIn[1];
	}
}

void CCompression::Start()
{
}

bool CCompression::Generate()
{
	return true;
}


