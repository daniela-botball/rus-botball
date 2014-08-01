#ifndef _TESTS_H_
#define _TESTS_H_

void test();

void test_show_blobs();
int get_ticks_per_rotation(int motor);

void test_face_poms();
void test_sucker_upper();
void test_camera_speed();
void test_spin_left_until_see_a_pom_pile();
void test_multiple_cameras();

void sorter_test(int speed_pot, int button_port);
void try_motor_speeds();
void run_wheel_motors(int port1, int port2, int power1, int power2, float seconds_to_run);
void run_motor(int port, int power, float seconds_to_run);
void test_motor_speeds();
void test_distance_degrees();
void test_drive_straight();
void test_degrees();
void test_sorting();

#endif
