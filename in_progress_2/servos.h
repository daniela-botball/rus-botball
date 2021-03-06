#ifndef _RUS_SERVOS_H_
#define _RUS_SERVOS_H_

#include "universal_library.h"
#include "create_library.h"

#define CLAW_SERVO 0
#define JOINT_SERVO 1
#define ARM_SERVO 2
#define CAMERA_SERVO 3
#define BOOSTER_MOTOR 1
#define GATE_MOTOR 2

#define GATE_DISTANCE 400 // was 550, FIXME
#define CLAW_SERVO_OPEN_POSITION 1500
#define CLAW_SERVO_CLOSE_POSITION 500
#define CLAW_SERVO_START_POSITION 1240
#define CLAW_SERVO_HALF_CLOSED_POSITION 1240
#define CLAW_SERVO_THROUGH_HOLE_POSITION 500

#define JOINT_SERVO_IN_POSITION 160
#define JOINT_SERVO_OUT_POSITION 1838
#define JOINT_SERVO_DOWN_POSITION 1103 // was 1203
#define JOINT_SERVO_START_POSITION 1900
#define JOINT_SERVO_THROUGH_HOLE_POSITION 1838

#define ARM_SERVO_UP_POSITION 1900 //1765, then 1639
#define ARM_SERVO_DOWN_POSITION 0
#define ARM_SERVO_START_POSITION 930
#define ARM_SERVO_DROP_POSITION 1480
#define ARM_SERVO_THROUGH_HOLE_POSITION 930

#define CAMERA_START_POSITION 2000
#define CAMERA_TRAVEL_POSITION 2000
#define CAMERA_PICKUP_BOOSTER_POSITION 950 // was 1110
#define CAMERA_THROUGH_HOLE_POSITION 800

typedef enum {DROP_BOOSTER, LOWER_BOOSTER} Drop_or_lower_booster;

void open_claw(int sleeptime);
void close_claw(int sleeptime);
void half_close_claw(int sleeptime);
void fold_joint_for_lift(int sleeptime);
void fold_joint_for_pickup(int sleeptime);
void fold_joint_for_drop(int sleeptime);
void raise_arm(int sleeptime);
void lower_arm(int sleeptime);
void move_arm_to_drop_position(int sleeptime);
void close_gate(int sleeptime);
void open_gate(int sleeptime);
void motor_push_down(int sleeptime);

void start_claw();
void start_arm();
void start_joint();
void start_gate();
void start_servos();
void set_servos_for_driving_to_birdie();
void set_servos_and_gate_for_going_through_hole();

void press_a_to_continue(int off_or_on);
void relax_servos();
void unrelax_servos();
void grab_booster(int distance);
void lift_booster();
void drop_booster(Drop_or_lower_booster drop_or_lower);
void move_servo_gently(int servo, int desired_position);

void open_claw(int sleeptime)
{
	set_servo_position(CLAW_SERVO, CLAW_SERVO_OPEN_POSITION);
	msleep(sleeptime);
}

void close_claw(int sleeptime)
{
	set_servo_position(CLAW_SERVO, CLAW_SERVO_CLOSE_POSITION);
	msleep(sleeptime);
}

void fold_joint_for_lift(int sleeptime)
{
	set_servo_position(JOINT_SERVO, JOINT_SERVO_IN_POSITION);
	msleep(sleeptime);
}

void fold_joint_for_drop(int sleeptime)
{
	set_servo_position(JOINT_SERVO, JOINT_SERVO_OUT_POSITION);
	msleep(sleeptime);
}

void fold_joint_for_pickup(int sleeptime)
{
	set_servo_position(JOINT_SERVO, JOINT_SERVO_DOWN_POSITION);
	msleep(sleeptime);
}

void raise_arm(int sleeptime)
{
	set_servo_position(ARM_SERVO, ARM_SERVO_UP_POSITION);
	msleep(sleeptime);
}

void move_arm_to_drop_position(int sleeptime)
{
	set_servo_position(ARM_SERVO, ARM_SERVO_DROP_POSITION);
	msleep(sleeptime);
}

void lower_arm(int sleeptime)
{
	set_servo_position(ARM_SERVO, ARM_SERVO_DOWN_POSITION);
	msleep(sleeptime);
}

void close_gate(int sleeptime)	// Precondition: Gagte must be in the OPEN position
{
    clear_motor_position_counter(GATE_MOTOR);
    motor(GATE_MOTOR, 100);
	while (get_motor_position_counter(GATE_MOTOR) < GATE_DISTANCE) ;
	off(GATE_MOTOR);
	msleep(sleeptime);
}

void open_gate(int sleeptime)	// Precondition: Gate must be in the CLOSED position
{
	clear_motor_position_counter(GATE_MOTOR);
    motor(GATE_MOTOR, -100);
	while (-get_motor_position_counter(GATE_MOTOR) < GATE_DISTANCE) ;
	off(GATE_MOTOR);
	msleep(sleeptime);
}

void half_close_claw(int sleeptime)
{
	set_servo_position(CLAW_SERVO, CLAW_SERVO_HALF_CLOSED_POSITION);
	msleep(sleeptime);
}

void motor_push_down(int sleeptime)
{
	relax_servos();
	motor(BOOSTER_MOTOR, 50);
	msleep(sleeptime);
	off(BOOSTER_MOTOR);
	unrelax_servos();
}

void start_claw()
{
	set_servo_position(CLAW_SERVO, CLAW_SERVO_START_POSITION);
}

void start_arm()
{
	set_servo_position(ARM_SERVO, ARM_SERVO_START_POSITION);
}

void start_joint()
{
	set_servo_position(JOINT_SERVO, JOINT_SERVO_START_POSITION);
}

void start_gate()	// Precondition: Motor arm must be against the "gate is open" stop
{					// POSITIVE motor direction should CLOSE the gate.
	// Purposefully does nothing.
}

void start_camera_servo()
{
    set_servo_position(CAMERA_SERVO, CAMERA_START_POSITION);
}

void start_servos()
{
	start_claw();
	start_joint();
	start_arm();
	start_camera_servo();
	start_gate();
	enable_servos();
	msleep(1000);
}

void relax_servos()
{
	fold_joint_for_lift(600);
	disable_servos();
}

void unrelax_servos()
{
	set_servo_position(JOINT_SERVO, get_servo_position(JOINT_SERVO));
	set_servo_position(ARM_SERVO, get_servo_position(ARM_SERVO));
	set_servo_position(CLAW_SERVO, get_servo_position(CLAW_SERVO));
	move_servo_gently(CAMERA_SERVO, CAMERA_PICKUP_BOOSTER_POSITION); // FIXME: Maybe too far motion for camera??
	enable_servos();
}

void set_servos_for_driving_to_birdie() {
	move_servo_gently(CLAW_SERVO, CLAW_SERVO_CLOSE_POSITION);
	move_servo_gently(JOINT_SERVO, JOINT_SERVO_IN_POSITION);
	move_servo_gently(ARM_SERVO, ARM_SERVO_UP_POSITION);
	move_servo_gently(CAMERA_SERVO, CAMERA_TRAVEL_POSITION);
}

void set_servos_and_gate_for_going_through_hole()
{
	open_gate(200);
	move_servo_gently(CAMERA_SERVO, CAMERA_THROUGH_HOLE_POSITION);
	move_servo_gently(ARM_SERVO, ARM_SERVO_THROUGH_HOLE_POSITION);
	move_servo_gently(JOINT_SERVO, JOINT_SERVO_THROUGH_HOLE_POSITION);
	move_servo_gently(CLAW_SERVO, CLAW_SERVO_THROUGH_HOLE_POSITION);
}
	
void grab_booster(int distance)
{
	//function assumes all servos begin in the relax position
	lower_arm(200);
	press_A_to_continue();
	
	//motor_push_down();
	open_claw(200);
	press_A_to_continue();
	
	fold_joint_for_pickup(200);
	press_A_to_continue();
	
	half_close_claw(200);
	press_A_to_continue();
	
	create_drive_distance(distance, 5, BACKWARDS);
	press_A_to_continue();
	
	close_claw(1000);
	press_A_to_continue();
	
	create_drive_distance(2, 5, FORWARDS);
	press_A_to_continue();
}

void lift_booster()
{
	fold_joint_for_lift(1500);
	press_A_to_continue();
	raise_arm(2000);
	close_gate(200);
}

void move_servo_gently(int servo, int desired_position)
{
	int current_position, k;
	int delta = 5;
	int sleeptime = 10;

	current_position = get_servo_position(servo);
	if (desired_position < current_position)
	{
		while (current_position > desired_position + delta) {
			current_position = current_position - delta;
			set_servo_position(servo, current_position);
			msleep(sleeptime);
		}
		
	} else {
		while (current_position < desired_position - delta) {
			current_position = current_position + delta;
			set_servo_position(servo, current_position);
			msleep(sleeptime);
		}
	}
	set_servo_position(servo, desired_position);
	msleep(sleeptime);
}

void drop_booster(Drop_or_lower_booster drop_or_lower)
{
	if (drop_or_lower == DROP_BOOSTER)
	{
		fold_joint_for_drop(3000);
		open_claw(200);
	}
	else
	{
		//create_drive_distance(1, 5, FORWARDS);
		//fold_joint_for_drop(2000);
		//start_gate();
		//move_arm_to_drop_position(200);
		//open_claw(200);
		// Should probably go away.
	}
}

#endif
