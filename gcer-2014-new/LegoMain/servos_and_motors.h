#ifndef _SERVOS_AND_MOTORS_H_
#define _SERVOS_AND_MOTORS_H_

// FIXME: Tune the following constants
#define SLOW_SERVO_SPEED 50 // ticks per second
#define VERY_SLOW_SERVO_SPEED 200 // ticks per second
#define MINIMUM_SERVO_INCREMENT 10

void move_servo_at_speed(int port, int desired_position, int ticks_per_second);

#endif
