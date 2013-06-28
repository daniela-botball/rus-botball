/*
 * Tests that the libraries compile successfully.
 *
 */

 #include "../libraries/universal_library.h"
#include "../libraries/gui_library.h"

extern Robot _ROBOT;

int main()
{
	_ROBOT = ANY;

	printf("Testing the gui library.\n");
	
	show_message("A message on the first message line");
	show_message("A message on the second message line");
	
	use_display_printf(FALSE);
	show_message("A message that scrolls");
	show_another_message("Another message that scrolls");
	
	return 0;
}
	/*
	void show_message(char* message);
void show_another_message(char* message);
void show_message_on_line(char* message, int line);

void press_A_to_continue();
void always_press_A_to_continue();

Button which_button_is_pressed();
Button wait_for_button_press();
void hands_off(Button button);

void skip_press_A_to_continue(Boolean b);
void use_display_printf(Boolean b);
void set_first_message_line(int line);
void set_second_message_line(int line);
*/
