#include "FatalErrorDialog.h"

FatalErrorDialog::FatalErrorDialog(const char* msg)
{
	al_show_native_message_box(al_get_current_display(),
		"Fatal error", msg, "The game will now exit", 
		NULL, ALLEGRO_MESSAGEBOX_ERROR);

	LOG(FATAL) << msg;
}