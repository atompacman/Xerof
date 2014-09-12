#pragma once
#include "dialog\FatalErrorDialog.h"

class Initializable
{
protected:
	bool initSuccess;

public:
	bool initFailed() {	return !initSuccess; }
};