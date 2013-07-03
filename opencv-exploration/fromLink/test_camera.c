
#include <stdio.h>
#include "/kovan/archives/rus_camera_interface.h"

int main() {
    int status;

    printf("Starting test_camera\n");

    motor(0, 100);
    msleep(1000);
    printf("Motor position: %i\n", get_motor_position_counter(0));

    rus_camera_open();
    status = rus_camera_update();
    printf("Status: %i\n", status);

//    find_pole();

    rus_camera_close();

    printf("Finished test_camera\n");
    return 0;
}
