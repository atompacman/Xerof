#include "FatalErrorDialog.h"

FatalErrorDialog::FatalErrorDialog(const char* i_Msg)
{
	al_show_native_message_box(al_get_current_display(),
		"Fatal error", i_Msg, "The game will now exit", 
		NULL, ALLEGRO_MESSAGEBOX_ERROR);

	LOG(FATAL) << i_Msg;
}