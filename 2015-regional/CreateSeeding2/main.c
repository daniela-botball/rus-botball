// Created on Thu April 2 2015

#include "createMovement.h"
#include "universal.h"
#include "tournamentFunctions.h"

// COMMENTS after Thursday 4/16 session:
//   -- Scores all 5, but have yet to get all 5 in a single run.
//   -- Winch has occasionally gone down completely wrong for the first pickup.  Disaster.  Easily fixed, IMO.
//   -- Scoring first 2 cubes was mostly reliable except:
//       -- Winch sometimes failed completely on first pickup.
//       -- Placement of cubes is important.
//       -- The fingers sometimes grab too high.  Either add lower fingers or ???
//       -- (Good that) The drop always worked.
//       -- (Good that) it is only 16 seconds.
//          However, it could easily be made faster without any loss in reliability.  Maybe important for double elimination.
//   -- For picking up the next 2 cubes:
//        -- IMO the path to get ready for the second pickup wastes a lot of time and is still not 100% reliable.
//        -- Even small errors cause failure either in the claw grabbing a pole (maybe should close, then later open, the claw?)
//           or (more typically) in not being in EXACTLY the right position for the pickup.
//        -- I looked at the camera with a pink model.  It did fine in saying where to go.
//           I strongly suspect that the camera is needed for the last little bit.
//        -- In any case, the motions after the robot has hit (and squared up on) the Cave PVC need to be reworked to work better
//           to cover unavoidable variations in position at that point.
//   -- Dropping the next 2 cubes is very practical but not fully tuned yet.
//        -- Using the camera or some sensor may help.
//        -- It is practical to score the 5th cube on the way to dropping cubes 3 and 4.
//   -- Timing is roughly:
//       -- 16 seconds to drop first 2 cubes
//       -- 25 more seconds to reach the opposite side (it would be more if the big-run speed were still at 20, I bumped it to 100)
//       -- 20 more seconds to grab the next 2 cubes
//       -- 20 more seconds to drop the last 2 cubes and also knock in the 5th cube on the way
//      So about 1 minutes and 20 seconds to that point.  That is good news!

// TODO: (talk to your coach about EACH of these before doing them)
//  Learn and practice the new   adjust   function.
//  Put comments in   score_our_cubes   for each major action (which will be a chunk of code).
//  Continue pushing actions forward:
//    -- Score 2 cubes on our starting zone line
//    -- Score 2 cubes on opponent's starting zone line
//    -- Score cube and two poms on Mesa.
//    -- Then ??
//  The library should allow the Create to specify either side as the "front".
// Failure points to check:
//  servo extender wire coming disconnected.
//  fishing wire getting too loose or tangled or off the winch.

/*
Create score the last 3 cubes.
Aaron will make mechanical changes Saturday.
Lego robot -- push it forward.
*/
void score_our_cubes();
void old_score_our_cubes();

void demo_adjust_functions();
void start();

int main()
{
	rectangle mybox;
	start();
	camera_open();
	camera_update();
	camera_update();
	camera_update();
	camera_update();
	camera_update();
	camera_update();
	camera_update();
	camera_update();
	camera_update();
	camera_update();
	operate_winch(WINCH_MIDDLE_POSITION);
	set_mode(PRACTICE_MODE);
	press_a_to_continue();
	create_spin(LEFT,2);
	while (TRUE){
		camera_update();
		if (get_object_count == 0) {
			continue;
		}
		
		mybox = get_object_bbox(0,0);
		
		printf("x coord %4d y coord %4d\n", mybox.ulx, mybox.uly);
		if (mybox.ulx<30) {
			create_halt();
			break;
		}
		//msleep(1000);
	}
	
	//score_our_cubes();
	
	return 0;
}

void start() {
	printf("Trying to connect...\n");
	create_connect();
	create_full();
	printf("Connected.\n");
	
	set_mode(PRACTICE_MODE);
	press_a_to_continue();
    set_mode(TOURNAMENT_MODE);
	open_claw();
	enable_servos();
	operate_winch(WINCH_MIDDLE_POSITION);
	create_spin_degrees(LEFT,18,20);
	operate_winch(WINCH_GROUND_POSITION);
	set_mode(PRACTICE_MODE);
	press_a_to_continue();
	close_claw();
	press_a_to_continue();
	open_claw();
	set_mode(TOURNAMENT_MODE);
	operate_winch(WINCH_MIDDLE_POSITION);
	create_spin_degrees(RIGHT,18,20);
	set_mode(PRACTICE_MODE);
	
	press_a_to_continue();
	
	//lights on
	 
	//_MODE = TOURNAMENT_MODE;
	//_ADJUST = FALSE;
}

void score_our_cubes() {
	set_mode(TOURNAMENT_MODE);
	
	// Grab 2 cubes on our starting zone line.
	create_spin_degrees(LEFT, 18, 20); 
	operate_winch(WINCH_GROUND_POSITION);
	close_claw();
	   
	// Put those 2 cubes into the bin.
	create_spin_degrees(LEFT, 28, 20);
	operate_winch(WINCH_DROP_POSITION);
	create_drive_distance(FORWARDS, 68, 20);
	open_claw(); 
	
	// Back up, lower arm, go under the Mesa and raise arm. 
	create_drive_distance(BACKWARDS, 50, 30);
	operate_winch(WINCH_MIDDLE_POSITION);
		
	create_spin_degrees(LEFT, 40, 20); // this has been the variable one.  Why?
	create_drive_distance(FORWARDS, 130, 30);
	operate_winch(WINCH_DROP_POSITION);
	
	// Go forward until the front hits the PVC.  Square up.
	//set_mode(PRACTICE_MODE);
	create_drive_distance(FORWARDS, 70, 20);
	create_drive_distance(FORWARDS, 5, 10);

	// Back up the right amount so that this step ends
	// in the right position.  Turn right 90 degrees.
	// Close the claw (so that it does not accidentally grab a pole).
	// Drive straight until the front hits the PVC.  Square up.
	
	create_drive_distance(BACKWARDS, 9, 20);
	create_spin_degrees(RIGHT, 90, 20);
	create_drive_until_event(BACKWARDS, 10, BUMP);
	close_claw();
	create_drive_distance(FORWARDS, 60, 20);
	create_drive_distance(FORWARDS, 7, 10);
	
	
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
	
	// Put those 2 cubes into the bin.
	
	// Score the cube on our side of the Mesa and
	// the 2 gold poms to the left of the BotThing on our side.
	
	// If time permits, score ping-pong balls.
}

void old_score_our_cubes() {
	//grab the cubes
	create_spin_degrees(LEFT, 18, 20); 
	//lower_winch();
	//operate_winch(WINCH_GROUND_POSITION);

	create_drive_distance(FORWARDS, 8, 10);
	operate_winch(WINCH_GROUND_POSITION);
	close_claw();
		
	//score our cubes
	create_spin_degrees(LEFT, 28, 20);
	operate_winch(WINCH_DROP_POSITION);
	
	create_drive_distance(FORWARDS, 64, 20);
	open_claw();
	
	//set_mode(PRACTICE_MODE);
	
	//go back from bin
	create_drive_until_event(BACKWARDS, 20, BUMP); 
	
	// go to other side of board
	create_spin_degrees(RIGHT, 136, 20);
	create_drive_distance(FORWARDS, 5, 5);
	operate_winch(WINCH_MIDDLE_POSITION);
	create_drive_until_event(BACKWARDS, 50, BUMP); // was 20
	
	//get ready to grab next cubes
	operate_winch(WINCH_DROP_POSITION);
	create_spin_degrees(LEFT, 90, 20);
	create_drive_until_event(BACKWARDS, 20, BUMP);
	create_spin_degrees(RIGHT, 90, 20);
	create_drive_distance(FORWARDS, 10, 20); // was 6
	create_spin_degrees(LEFT, 90, 20);
	create_drive_distance(FORWARDS, 65, 20);
	create_drive_distance(BACKWARDS, 8, 20);
	
	//grab 2nd cubes 
	//lower_winch();
	operate_winch(WINCH_GROUND_POSITION);
	create_drive_distance(FORWARDS, 6, 20);
	create_spin_degrees(RIGHT, 10, 20);
	msleep(2000); // Why this?
	close_claw();
	create_drive_distance(BACKWARDS, 2, 20);
	operate_winch(WINCH_DROP_POSITION);
	
	//score their cubes
	create_spin_degrees(LEFT, 7, 20);
	create_drive_until_event(BACKWARDS, 20, BUMP);
	create_spin_degrees(RIGHT, 50, 20);
	create_drive_distance(FORWARDS, 60, 20);
	create_spin_degrees(LEFT, 10, 20);
	create_drive_distance(FORWARDS, 10, 20);
	open_claw();
	
	//back up from bin/mesa
	// Need to sleep and then close claw here, maybe.  Or ???
	//create_drive_until_event(BACKWARDS, 20, BUMP);
	return;
}

void demo_adjust_functions() {
	printf("Trying to connect...\n");
	create_connect();
	create_full();
	printf("Connected.\n");
	
	set_mode(PRACTICE_MODE);
	_ADJUST = TRUE;
	
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION); // TODO: Make claw open slower
	enable_servos();
	
	// Demo adjusting forwards / backwards:
	create_drive_distance(FORWARDS, 10, 50);
	create_drive_distance(BACKWARDS, 15, 30);
	
	// Demo adjusting left / right:
	create_spin_degrees(LEFT, 90, 20);
	create_spin_degrees(RIGHT, 30, 50);
	
	// Demo adjusting claw servo:
	close_claw();
	
	// Demo adjusting winch motor:
	operate_winch(WINCH_MIDDLE_POSITION);
	
	disable_servos();
	create_disconnect();
}
