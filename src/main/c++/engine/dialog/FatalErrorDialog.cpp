#include "FatalErrorDialog.h"

FatalErrorDialog::FatalErrorDialog(const char* description)
{
	fprintf(stderr, description);

	al_show_native_message_box(al_get_current_display(),
		"Fatal error", description, "The game will now exit", 
		NULL, ALLEGRO_MESSAGEBOX_ERROR);
}