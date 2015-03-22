#pragma once
#include "allegro5\allegro_native_dialog.h"
#include <easylogging++.h>
#include <stdio.h>

class FatalErrorDialog
{
public:
	FatalErrorDialog(const char* description);
};

