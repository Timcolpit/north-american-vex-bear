#pragma config(Sensor, dgtl1,  hook1,          sensorDigitalOut)
#pragma config(Sensor, dgtl2,  hook2,          sensorDigitalOut)
#pragma config(Sensor, dgtl3,  pistonLock1,    sensorDigitalOut)
#pragma config(Sensor, dgtl4,  pistonLock2,    sensorDigitalOut)
#pragma config(Motor,  port1,  frontRightMotor, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,  backRightMotor, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,  backLeftMotor, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,  bottomRightTower, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,  bottomLeftTower, tmotorVex393, openLoop)
#pragma config(Motor,  port6,  takeLeft,      tmotorVex393, openLoop)
#pragma config(Motor,  port7,  takeRight,     tmotorVex393, openLoop)
#pragma config(Motor,  port8,  topLeftTower,  tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,  topRightTower, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10, frontLeftMotor, tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define FULL_POWER 127
#define HALF_POWER 63
#define STOP 0

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
string mainBattery;
string backupBattery;

short programChoice;

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c" � //Main competition background code...do not modify!

// Move drive at full power for �timer� milliseconds either forward (1) or backward (-1)
void moveDrive(int direction, int timer=0) {
	// Check for function input error
	if(direction == 1 || direction == -1 || direction == 0){
		// Move at 100% power
		motor[frontRightMotor]	 = FULL_POWER * direction;
		motor[frontLeftMotor] 	 = FULL_POWER * direction;
		motor[backRightMotor]	   = FULL_POWER * direction;
		motor[backLeftMotor]	   = FULL_POWER * direction;
	}

	if(timer != 0) {
		// Wait �timer� ms
		wait1Msec(timer);

		// Stop
		motor[frontRightMotor]	 = STOP;
		motor[frontLeftMotor] 	 = STOP;
		motor[backRightMotor]	   = STOP;
		motor[backLeftMotor]	   = STOP;
	}
}

// Move arm at full power for �timer� milliseconds either forward (1) or backward (-1)
void moveArm(int direction, int timer=0) {
	// Check for function input error
	if(direction == 1 || direction == -1 || direction == 0){
		// Move at 100% power
		motor[topRightTower]	   = FULL_POWER * direction;
		motor[topLeftTower] 	   = FULL_POWER * direction;
		motor[bottomRightTower]  = FULL_POWER * direction;
		motor[bottomLeftTower]   = FULL_POWER * direction;
	}

	if(timer != 0) {
		// Wait �timer� ms
		wait1Msec(timer);

		// Stop
		motor[topRightTower]	   = STOP;
		motor[topLeftTower] 	   = STOP;
		motor[bottomRightTower]  = STOP;
		motor[bottomLeftTower]   = STOP;
	}
}

// Move intake motors at full power in specified direction /*
void moveIntake(int direction) {
	// Check for function input error
	if (direction == 1 || direction == -1 || direction == 0){
		// Move at 100% power
		motor[takeLeft]	   = FULL_POWER * direction;
		motor[takeRight]   = FULL_POWER * direction;
	}
}
//Wait for Press--------------------------------------------------
void waitForPress()
{
  while(nLCDButtons == 0){}
  wait1Msec(5);
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
  while(nLCDButtons != 0){}
  wait1Msec(5);
}
//----------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0, 'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		//Display the Backup battery voltage
		displayLCDString(1, 0, "Backup: ");
		sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
		displayNextLCDString(backupBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);

 
  clearLCDLine(0); //Clear LCD
  clearLCDLine(1);
  
  //displayLCDCenteredString(0, "Test");
  //Declare count variable to keep track of our choice
  
  int count = 0;
  
  while(nLCDButtons != centerButton)
  {
    //Switch case that allows the user to choose from 2 different options
    switch(count){
    case 0: //Display first choice
      displayLCDCenteredString(0, "Goal Auto");
      displayLCDCenteredString(1, "<     Enter    >");
      waitForPress();
        
      //Increment or decrement "count" based on button press
      if(nLCDButtons == leftButton)
      {
        waitForRelease();
        count = 1;
      }
      else if(nLCDButtons == rightButton)
      {
        waitForRelease();
        count++;
      }
      break;

    case 1: //Display second choice
      displayLCDCenteredString(0, "Hang auto");
      displayLCDCenteredString(1, "<     Enter    >");
      waitForPress();
      //Increment or decrement "count" based on button press
      if(nLCDButtons == leftButton)
      {
        waitForRelease();
        count--;
      }
      else if(nLCDButtons == rightButton)
      {
        waitForRelease();
        count--;
      }
      break;

    default:
      count = 0;
      break;
    }
  }

  //Clear LCD
  clearLCDLine(0);
  clearLCDLine(1);
  
  switch(count) {  //pick auto, display
  case 0: //Choice 1 from LCD
    displayLCDCenteredString(0, "Goal Side Autonomous");
    displayLCDCenteredString(1, "is running!");
    programChoice = 1;
    break;

  case 1: //Choice 2 from LCD
    displayLCDCenteredString(0, "Autonomous 2");
    displayLCDCenteredString(1, "is running!");
		programChoice = 2;
    break;
      
  default:
    displayLCDCenteredString(0, "No valid choice");
    displayLCDCenteredString(1, "was made!");
    break;
  }
}


/////////////////////////////////////////////////////////////////////////////////////////
//
// Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
task autonomous()
{
//goal side of bump

    // Autonomous 1
	if(programChoice == 1){
		// Move forward to first point
		moveDrive(1, 500);

		// Move arm up
		moveArm(1, 750);

		// Move forward to second point
		moveDrive(1, 500);

		/* Not sure why this wait exists */
		wait1Msec(750);

		/* Do these never stop intentionally? */
		// Outtake preload
		moveIntake(-1);
		wait1Msec(2000);

		// Drive back to starting square
		moveDrive(-1, 1000);

		//stop robot for 3s to reposition
		wait1Msec(3000);

		// Move forward from new manually positioned angle
		moveDrive(1, 1300);

		/* Does this need to be here? */
		wait1Msec(50000);
	}

    // Autonomous 2
	else if(programChoice == 2) {
	  //move robot forward
    moveDrive(1, 750);

    //stop Robot and intake balls
    moveIntake(1);
	  wait1Msec(750);
    moveDrive(-1, 750);
	}
}



/////////////////////////////////////////////////////////////////////////////////////////
//
// User Control Task
//
// Functions for lift, drive, intake, and pneumatics.
//
/////////////////////////////////////////////////////////////////////////////////////////


task usercontrol() {
	while(1 == 1) {

		/* Drivetrain */

 		//Right side of the robot is controlled by the right joystick, Y-axis
		motor[frontRightMotor]	= vexRT[Ch2];
		motor[backRightMotor] 	= vexRT[Ch2];

		//Left side of the robot is controlled by the left joystick, Y-axis
		motor[frontLeftMotor]	  = vexRT[Ch3];
		motor[backLeftMotor]	  = vexRT[Ch3];



		/* Button Control */

		// Arm

		if(vexRT[Btn5U]) {
			moveArm(1); // Move arm up
		}
		else if(vexRT[Btn5D]) {
			moveArm(-1); // Move arm down
		}
		// If neither buttons 5U or 5D are pressed
		else {
			// Stop bottom tower movement (i.e. don't move arm up or down)
			motor[topRightTower]    = STOP;
			motor[topLeftTower]     = STOP;
			motor[bottomRightTower]	= STOP;
			motor[bottomLeftTower]  = STOP;
		}


		// Intake

		if (vexRT[Btn6U]) {
			moveIntake(1); //runs intake, pull
		}
		else if (vexRT[Btn6D]) {
			moveIntake(-1); //runs intake, push
		}
		else {
			moveIntake(0);
		}

		if(vexRT[Btn7U]) {
			// Engage solenoid
			SensorValue[hook1] = 1;
			SensorValue[hook2] = 1;
		}
		else if(vexRT[Btn7D]) {
			// Disengage solenoid
			SensorValue[hook1] = 0;
			SensorValue[hook2] = 0;
		}
    
		if(vexRT[Btn8U]) {
			//activate lock
			SensorValue[pistonLock1] = 1;
			SensorValue[pistonLock2] = 1;
		}
		else if(vexRT[Btn8D]) {
			SensorValue[pistonLock1] = 0;
			SensorValue[pistonLock2] = 0;
		}
	}
}
