// Created on Sun Jun 9 2013

/* This program moves a Create back and forth along a piece of black duct tape against a light colored surface.
The variable baseLength should be set to the length of the desired run in mm (note that it should be slightly shorter than the
desired run as the Create may overshoot my a cm or two).  Also note that the Create's version of a mm seems to be several %
larger than the official length.

The robot will start out moving forward a random amount of at least minLength between its current position and
baseLenght from its starting point.  It will then move backwards at least minLength a random amount between its current
positionand its initial starting position.  Its speed of movement will be baseSpeed +/- rand()%speedVar/2.

The robot uses the right front cliff sensor and a reflectance sensor plugged into port REARREFLECT and mounted on
the back of the create pointing down and slightly to the right of center (i.e., the same distance to the right of center as the
right front cliff sensor).  The Create will be centered on the tape (approximately with the sensors along the right edge.

When the program is run, the user has the option of calibrating -- which means that each of the 8 defining values can be modified
in the program.  These are stored in static variables and so should maintain their modified values until the program is
redownloaded (this is untested and the values may be lost during a reboot).  If calibrate is pressed the program
will run when the last variable has been set to its calibrated value.

If either front bumper is pressed (regardless of the present direction of movement) the Create will immediately halt for 30
seconds and then resume its activity.
*/

// put a rear reflectance sensor looking down in back to the right of center (right edge of tape)
#define REARREFLECT 0

void moveHoop(int fMid, int rMid, int baseSpeed, int baseLength, int speedVar, int minLength);
int calVal(char name[], int val);
int DriftModifier;


int main()
{
	static int fBlack=250, rBlack=900, fWhite=880, rWhite=500;// calibration values for the line sensors
	static int baseSpeed=100, baseLength=1000, speedVar=15, minLength=300;// calibration values for movement
	int fMid, rMid, i;
	DriftModifier=100;

	while(create_connect());

	set_a_button_text("Calibrate");
	set_b_button_text("Run");
	printf("Place robot at start \nposition and press:\n");
	printf("fBlack=%i, rBlack=%i\nfWhite=%i, rWhite=%i\n",fBlack,rBlack,fWhite,rWhite);
	printf("baseSpeed=%i, baseLength=%i\nspeedVar=%i, minLength=%i\n",baseSpeed, baseLength, speedVar, minLength);

	set_create_distance(0);

	while(!any_button()){msleep(10);}// wait for user
	if(a_button_clicked()){
		fBlack=calVal("fBlack",fBlack); rBlack=calVal("rBlack",rBlack);
		fWhite=calVal("fWhite",fWhite); rWhite=calVal("rWhite",rWhite);
		baseSpeed=calVal("baseSpeed",baseSpeed); baseLength=calVal("baseLength",baseLength);
		speedVar=calVal("speedVar",speedVar); minLength=calVal("minLength",minLength);
		display_clear();
		display_printf(0,1,"All values have been calibrated\nMoving in:");
	}
	if(b_button_clicked());// debounce button
	fMid = (fBlack+fWhite)/2;
	rMid = (rBlack+rWhite)/2;

	for(i=3;i>0;i--){display_printf(11,2,"%i",i); msleep(1000);}// count down from 3

	moveHoop(fMid,rMid,baseSpeed,baseLength,speedVar,minLength);

	create_stop();
	create_disconnect();

	return 0;
}

// This function takes the name of a variable and its current value and returns the new value for that
// variable.  The user uses the ^ and v buttons to adjust the value and the named button to set the value
// which causes the calibration to move on to the next value.

int calVal(char name[], int val)
{
	set_a_button_text("up ^");
	set_b_button_text("down v");
	set_c_button_text(name);
	while(!c_button_clicked()){
		printf("Front reflect %i\n Rear reflect %i",get_create_rfcliff_amt(), analog10(REARREFLECT));
		printf("Create Dist = %i\n",get_create_distance());
		printf("\n%s = %i\n",name,val);
		if(a_button())val++;
		if(b_button())val--;
		msleep(50);
		display_clear();
	}
	return(val);
}


void moveHoop(int fMid, int rMid, int baseSpeed, int baseLength, int speedVar, int minLength)
{
	int moveForward=1, speed=baseSpeed, dist=minLength,i;
	set_a_button_text("Stop");
	set_b_button_text("Stop");
	set_c_button_text("Stop");
	while(!any_button()){
		display_clear();
		display_printf(0,3,"Press any button to stop");
		if(moveForward==1){
			moveForward=0;
			speed=baseSpeed+(rand()%speedVar)-speedVar/2;
			dist=(get_create_distance()+(rand()%(baseLength-get_create_distance()-minLength))+minLength);
			display_printf(0,0,"%iMoving forward to %imm at %imm/s",moveForward,dist,speed);
			msleep(1000);
			if(dist <= baseLength){
				while(!any_button() && get_create_distance()<dist){
					display_printf(0,1,"Currently at %i\n",get_create_distance());
					display_printf(0,3,"fMid= %i lfcliff= %i",fMid,get_create_rfcliff_amt());
					if(get_create_rfcliff_amt()>fMid){//see white turn left
						create_drive_direct(speed-speed/5,speed+speed/5);
					}
					else{// on black turn right
						create_drive_direct(speed+speed/5,speed-speed/5);
					}
					if(get_create_lbump() || get_create_rbump()){// a front bumper is hit...
						create_stop(); // stop
						for(i=30;i>0;i--){// bumper pressed stop for 30s
							display_printf(0,3,"Pausing for %i more secs",i);
							msleep(995);
						}
					}
				}
			}
			create_stop();
			
		}
		else{// moving backwards
			moveForward=1;
			speed=-(baseSpeed+(rand()%speedVar)-speedVar/2);
			dist=(get_create_distance()-(rand()%(get_create_distance()-minLength)+minLength));
			//dist = get_create_distance() - 500;
			display_printf(0,0,"%iMoving backward to %imm at %imm/s",moveForward,dist,speed);
			display_printf(0,1,"Currently at %i\n",get_create_distance());
			msleep(1000);
			if(dist >= 0){
				while(!any_button() && get_create_distance()>dist){
					display_printf(0,1,"Currently at %i\n",get_create_distance());
					if(analog10(REARREFLECT)>fMid){//see black turn left (right if looking backwards)
						create_drive_direct(speed+speed/5,speed-speed/5);
					}
					else{// on white turn right
						create_drive_direct(speed-speed/5,speed+speed/5);
					}
					if(get_create_lbump() || get_create_rbump()){// a front bumper is hit...
						create_stop(); // stop
						for(i=30;i>0;i--){// bumper pressed stop for 30s
							display_printf(0,3,"Pausing for %i more secs",i);
							msleep(995);
						}
					}
				}
			}
			create_stop();
			
		}
	}
	create_stop();
}





