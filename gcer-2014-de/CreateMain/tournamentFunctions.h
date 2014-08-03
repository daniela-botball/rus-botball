// Created on Thu March 13 2014
#ifndef _TOURNAMENT_FUNCTIONS_H_
#define _TOURNAMENT_FUNCTIONS_H_

#define WINCH_MOTOR 0
#define EXTENDER_MOTOR 1

#define EXTENSION_DISTANCE 2300 

#define THIRD_RACK_POSITION -1
#define WINCH_DROP_DISTANCE 100 // 80

#define BAR_SERVO 0
#define CLAW_SERVO 1
#define GYRO_SERVO 3
#define LOCK_SERVO 0

#define LOCKED_POSITION 1000
#define UNLOCKED_POSITION 2000

#define HIGH_SENSOR 1
#define LOW_SENSOR 0

#define UP 1
#define DOWN -1

#define DOUBLER_POSITION -2050
#define DOUBLER_PICK_UP_POSITION 400

#define WINCH_START_POSITION -1440 //-1550
#define WINCH_DUMPING_POSITION -1295 // DCM was -1050
#define WINCH_RELEASING_POSITION -434 // -425
#define WINCH_SCORING_POSITION -115 // DCM was 25
#define WINCH_TRAVEL_POSITION -2250
#define WINCH_FIRST_CUBE_POSITION 680 // DCM was 527
#define WINCH_SECOND_CUBE_POSITION -600 //DCM was -570

#define GYRO_FIRST_CUBE_POSITION 1940
#define GYRO_SECOND_CUBE_POSITION 1777
#define GYRO_DROP_POSITION 245 // DCM was 325
#define GYRO_START_POSITION 0
#define CLAW_CLOSED_POSITION 50  // DCM was 100
#define CLAW_OPEN_POSITION 1550
#define CLAW_START_POSITION 130 // was 260
#define CLAW_RELEASE_POSITION 1000
#define BAR_START_POSITION 620 // DCM was 420
#define BAR_OPEN_POSITION 100
#define BAR_CLOSED_POSITION 1050

#define SERVO_INCREMENT 15

#define DESIRED_DISTANCE 450
#define DESIRED_X_POSITION 57
#define CENTER_OF_SCREEN_Y 60
#define CUBE_CHANNEL 0

#define SLOW_CREATE_LINEAR_SPEED 30
#define SLOW_CREATE_ANGULAR_SPEED 20
#define SPEED_FOR_TIGHTENING_WINCH 75
#define SPEED_FOR_RELEASING_WINCH 20
#define GYRO_SERVO_ADJUSTMENT_AMOUNT 10
#define GYRO_SERVO_ADJUSTMENT_MSECONDS 200
#define CLAW_SERVO_ADJUSTMENT_AMOUNT 10
#define CLAW_SERVO_ADJUSTMENT_MSECONDS 200
#define BAR_SERVO_ADJUSTMENT_AMOUNT 10
#define BAR_SERVO_ADJUSTMENT_MSECONDS 200

#define NUMBER_ERRORS_ALLOWED 3 // DCM
#define AMOUNT_ERROR_ALLOWED 100 // DCM

void unlock_winch_new();
void lock_winch_new();

void adjust();
void adjust_winch_or_gyro();
void adjust_movement();
int adjust_claw_or_bar();
void set_buttons_for_winch_and_gyro();
void set_buttons_for_movement();
void set_buttons_for_claw_and_bar();
void set_buttons_to_abc();


void get_first_doubler();
int int_abs(int x);

void lock_winch();
void unlock_winch();

void raise_winch();
void raise_winch_old();
void operate_winch(int position);
void pick_up_first_doubler();
void score_cubes();
void move_to_cubes();
void move_to_second_cube();
void pick_up_cube();
void drop_cube();
void drop_three_hangers();
void center_on_cube(int port, int direction);
void center_on_cube_with_camera();
void move_servo_slowly(int port, int position);

void drop_three_hangers_on_third_rack(int strategy);
void drive_to_hanger_racks(int strategy);
void drop_hangers(int strategy);
void extend_arm();
#endif

