/**
* PianoSys.h
* Seongjin Park
* system class that creates a piano intrument.
*/

#pragma once
#include "Piano.h"
#include "Note.h"
#include "audio/DirSoundSource.h"


class CPianoSys
{
public:
	// Constructor
	CPianoSys();

	// Destructor
	~CPianoSys();

	const double NUM_SECS_IN_MINUTE = 60.0;

	// Set the piano instrument in this system 
	CPiano* SetPiano(CNote* note, double bpm);

	bool OpenWavFile(const char* filename);

	// Clear out wave frames whenever file is changed 
	void Clear();


private:
	std::vector<short> m_waves;
	double m_duration;
	bool m_pedalpress;
};

