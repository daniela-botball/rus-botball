/*
Top-level functions for the strategy:
 "score_8_plus_8_in_upper_bins"
which is:
  1. Get and sort 4 poms closest to start box.
  2. Get and sort other 4 poms on our side.
  3. Dump 4 poms into our upper storage.
  4. Dump 4 poms into opponent's upper storage.
  5. Get and sort 4 poms closest to opponent's start box.
  6. Get and sort other 4 poms on opponent's storage.
  7. Dump 4 poms into opponent's upper storage.
  8. Dump 4 poms into our upper storage.
  */

#include "score_8_plus_8.h"
#include "utilities.h"
#include "tournamentFunctions.h"
#include "camera_rus.h"

extern int _OUR_COLOR;
extern int _THEIR_COLOR;

// FIXME: Make the following function robot-neutral and put it in a servo_motor file.
void initialize_servos() {
	// FIXME: THESE SHOULD SAY "START POSITIONS", with those defined as DATA elsewhere.
	// Really, there should be a way to say what the four servo ports are used for,
	// with unused a possibility, and this code initializes and enables if there is at least one used.
	set_servo_position(CLAW_SERVO, CLAW_START_POSITION);
	set_servo_position(SORTER_SERVO, SORTER_START_POSITION);
	set_servo_position(CAMERA_SERVO, CAMERA_START_POSITION);
	set_servo_position(DUMPER_SERVO, DUMPER_START_POSITION);
	
	enable_servos();
}

void setup_score_8_plus_8_poms_in_upper_storage() {
	initialize_camera();
	initialize_servos(); // FIXME: Make this take an argument to be robot-neutral.
	
	// FIXME: Must ask for these at run-time.
	_OUR_COLOR = PINK;
	_THEIR_COLOR = GREEN;
}

void score_8_plus_8_poms_in_upper_storage() {
	
	// 1. Get and sort 4 poms closest to start box.
	// go_close_to_first_pom_pile(); // FIXME
	eat_poms();
	
	turn_to_second_pom_pile();
	sort_while_moving(7); // FIXME: Add DISTANCE parameter.
	
	//  2. Get and sort other 4 poms on our side.
	go_close_to_second_pom_pile();
	eat_poms();
	
	turn_to_first_dump();
	sort_while_moving(7); // FIXME: Add DISTANCE parameter.
	
	// 3. Dump 4 poms into our upper bin.
	go_close_to_our_upper_storage();
	dump_cage(_OUR_COLOR);
	  
    // 4. Dump 4 poms into opponent's upper storage area.
	go_close_to_opponents_upper_storage();
	dump_cage(_THEIR_COLOR);
	
    // 5. Get and sort 4 poms closest to opponent's start box.
	go_close_to_third_pom_pile();
	eat_poms();
	
	turn_to_third_pom_pile();
	sort_while_moving(7); // FIXME: Add DISTANCE parameter.

    // 6. Get and sort other 4 poms on opponent's side.
	go_close_to_fourth_pom_pile();
	eat_poms();
	
	turn_to_third_dump();
	sort_while_moving(7); // FIXME: Add DISTANCE parameter.
	
    // 7. Dump 4 poms into opponent's upper bin.
	go_close_to_opponents_upper_storage_again();
	dump_cage(_THEIR_COLOR);
	
	// 8. Dump 4 poms into our upper bin.
	go_close_to_our_upper_storage_again();
	dump_cage(_OUR_COLOR);
}

	/*turn_until_poms_in_sight();
	press_a_to_continue();
	
	pom_drive(110); // Turn 110 degrees when eating poms.
	press_a_to_continue();
	
	turn_until_poms_in_sight();
	press_a_to_continue();
	
	drive_to_poms();
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION);
	
	
	
	
	
	motor(0, 100);
	lego_spin(100, LEFT);
	msleep(1600);
	lego_stop();press_a_to_continue();
	
	lego_drive(100, FORWARDS);
	for (k = 0; k < 6; k++) {
		move_servo_slowly(CLAW_SERVO, CLAW_CLOSED_POSITION);
		set_servo_position(CLAW_SERVO, CLAW_HALF_OPEN_POSITION);
	}
	lego_stop();*/


