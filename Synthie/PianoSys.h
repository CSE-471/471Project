/**
* PianoSys.h
* Seongjin Park
* system class that creates a piano intrument.
*/

#pragma once
#include "Piano.h"
#include "Note.h"


class CPianoSys
{
public:
	// Constructor
	CPianoSys();

	// Destructor
	~CPianoSys();

	// Set the note for piano
	void SetNote(CNote *note);

	// Set the piano instrument in this system 
	CPiano* SetPiano();


private:

};

