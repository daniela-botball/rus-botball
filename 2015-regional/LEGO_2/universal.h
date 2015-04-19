#ifndef _UNIVERSAL_H_
#define _UNIVERSAL_H_

#define TRUE 1
#define FALSE 0

#define CREATE_ROBOT 1
#define LEGO_ROBOT 0

#define TOURNAMENT_MODE 1
#define PRACTICE_MODE 0

#define A_BUTTON 0
#define B_BUTTON 1
#define C_BUTTON 2
#define X_BUTTON 3
#define Y_BUTTON 4
#define Z_BUTTON 5
 
#define BIG_DRIVE_ADJUST 500
#define SMALL_DRIVE_ADJUST 100
#define BIG_SPIN_ADJUST 250
#define SMALL_SPIN_ADJUST 50
#define BIG_MOTOR_ADJUST 200
#define SMALL_MOTOR_ADJUST 40
#define BIG_SERVO_ADJUST 20
#define SMALL_SERVO_ADJUST 4

extern int _ROBOT;
extern int _MODE;
extern int _ADJUST;
extern int _TOURNAMENT_SLEEP;

void set_robot(int robot);
void set_mode(int mode);
void press_a_to_continue();

void adjust_drive(int direction, int amount);
void adjust_spin(int direction, int amount);
void adjust_motor(int motor_port, int position);
void adjust_servo(int servo_port, int position);

void motor_to_position(int motor_port, int position);

int get_choice();
void set_buttons_for_adjust(char labels [4][20]);

void initialize_camera();

#endif
