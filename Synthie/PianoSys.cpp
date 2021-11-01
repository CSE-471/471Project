/**
* PianoSys.cpp
* Seongjin Park
* system class that creates a piano intrument. 
*/

#include "stdafx.h"
#include "PianoSys.h"
#include "Note.h"
#include <vector>


/**
* Constructor
*/
CPianoSys::CPianoSys()
{

}

/**
* Destructor
*/
CPianoSys::~CPianoSys()
{

}

/**
* Set the attributes of a note for a piano 
*/
void CPianoSys::SetNote(CNote *note)
{

}


/**
* Set the piano instrument in this system 
*/
CPiano* CPianoSys::SetPiano()
{
	CPiano* piano = new CPiano();

	return piano;
}
