// TODO: Put authors and description here.

#include "createMovement.h"
#include "universal.h"
#include "tournamentFunctions.h"

void start();
void score_our_cubes();

#define STARTING_LIGHT_PORT 0
#define ORANGE 3
#define STARTING_ANGLE 20 // degrees

int main()
{
	// Things to happen BEFORE lights-off:
	start();
	
	// Lights turn on at this point:
	score_our_cubes();
	
	return 0;
}

// Things to happen BEFORE lights-off.
void start() {
	int mode_human_chose;
	
	// Connect to the Create.
	printf("Trying to connect...\n");
	create_connect();
	create_full();
	printf("Connected.\n");
	
	initialize_camera();
	
	// Human operator selects TOURNAMENT or PRACTICE mode.
	set_mode(get_mode());
	mode_human_chose = _MODE;
	
	// Set the robot into its starting position.
	// The human operator should:
	//   -- First put the robot in the corner, turned so that its claw is grabbing on the starting line.
	//   -- And put the two cubes in the right position for the claw.
	//   -- When the claw grabs and then releases the cubes, do a final adjustment of the cubes position.
	pause_for_sure();
	set_mode(TOURNAMENT_MODE);
	
	open_claw();
	enable_servos();
	operate_winch(WINCH_MIDDLE_POSITION);
	create_spin_degrees(LEFT, STARTING_ANGLE, 20);
	operate_winch(WINCH_GROUND_POSITION);
	
	// Human readjusts cubes now.
	pause_for_sure();
	
	// And again after the claw closes, then opens.
	close_claw();
	pause_for_sure();
	open_claw();
	pause_for_sure();
	
	operate_winch(WINCH_MIDDLE_POSITION);
	create_spin_degrees(RIGHT, STARTING_ANGLE, 20);
	pause_for_sure();
	
	// Back to the human's choice of mode:
	set_mode(mode_human_chose);
	
	// Now the starting-light protocol:
	wait_for_light(STARTING_LIGHT_PORT);
	
	if (_MODE == TOURNAMENT_MODE) {
		_ADJUST = FALSE;
		shut_down_in(119);
	} else {
		_ADJUST = TRUE;
	}
}

void score_our_cubes() {
	//set_mode(TOURNAMENT_MODE); // This first part works fine, I think.
	
	// Grab 2 cubes on our starting zone line.
	create_spin_degrees(LEFT, STARTING_ANGLE, 20); 
	operate_winch(WINCH_GROUND_POSITION);
	close_claw();
	   
	// Put those 2 cubes into the bin.
	create_spin_degrees(LEFT, 28, 20);
	operate_winch(WINCH_DROP_POSITION);
	create_drive_distance(FORWARDS, 68, 20);
	open_claw(); 
	
	// get cube on mesa into bin.
	create_drive_distance(BACKWARDS,10,20);
	create_spin_degrees(LEFT,5,20);
	operate_winch(WINCH_MESA_POSITION);
	//create_drive_distance(FORWARDS,8,20);
	close_claw();
	create_spin_degrees(RIGHT,5,20);
	open_claw();
	
	// Back up, lower arm, go under the Mesa and raise arm. 
	create_drive_distance(BACKWARDS, 50, 30);
	operate_winch(WINCH_MIDDLE_POSITION);
		
	create_spin_degrees(LEFT, 40, 20); // this moves somewhat erratically.  Why?
	create_drive_distance(FORWARDS, 130, 30);
	operate_winch(WINCH_DROP_POSITION);
	
	// Go forward until the front hits the PVC.  Square up.
	create_drive_distance(FORWARDS, 70, 20);
	create_drive_distance(FORWARDS, 5, 10);

	// Back up the right amount so that this step ends
	// in the right position.  Turn right 90 degrees.
	// Close the claw (so that it does not accidentally grab a pole).
	// Drive straight until the front hits the PVC.  Square up.
	
	create_drive_distance(BACKWARDS, 5, 20); // was 9
	create_spin_degrees(RIGHT, 90, 20);
	create_drive_until_event(BACKWARDS, 10, BUMP);
	close_claw();
	create_drive_distance(FORWARDS, 62, 20);
	create_drive_distance(FORWARDS, 5, 10);
	
	// Grab the 2 cubes on the opponent's starting zone line:
	//   -- Lower arm to middle position.
	//   -- Spin right to the cubes.
	//   -- Open the claw.
	//   -- Lower arm to ground.
	//   -- Grab the cubes.
	operate_winch(WINCH_MIDDLE_POSITION);
	create_spin_degrees(RIGHT, 15, 10);
	open_claw();
	operate_winch(WINCH_GROUND_POSITION);
	close_claw();
	
	// ** Darrian, Step 1: **  Run the program to this point.
	// If the grab was not quite right, gently fix it by hand.
	// Do NOT spend any time fixing the previous step;
	// we will do that when I am next with you, using camera
	// ideas like those you learned last night.
	// Just be sure that the previous step does not break the robot.
	
	set_mode(PRACTICE_MODE);
	
	// ** Darrian, Step 2: ** Write and test the following.
	// Put those 2 cubes into the bin by:
	//   -- Raise the arm.
	//   -- Back up the right amount.
	//   -- Spin right the right amount.
	//   -- Go forward the right amount.
	//   -- Open the claw.
	operate_winch(WINCH_DROP_POSITION);
	create_drive_distance(BACKWARDS, 43, 20);
	create_spin_degrees(RIGHT, 35, 20);
	create_drive_distance(FORWARDS, 47, 20);
	create_spin_degrees(RIGHT, 5, 20);
	open_claw();
	
	// ** Darrian, Step 3: ** AFTER getting Step 2 to work reliably,
	//                        write and test the following.
	// Score the cube on our side of the Mesa and
	// the 2 gold poms between the BotThing and the bin, by:
	//    -- Darian, you decide what motions seem to work here.
	//    -- Strive for FEW MOTIONS and KISS.
	
	// ** Darrian, Step 4: ** [we will do this together]
	// If time permits, score ping-pong balls.
}
