#include "main.h"

pros::ADIGyro gyro('A');

//helper functions

void setDrive(int left, int right){
  LeftFront = left;
  RightFront = right;
  RightBack = right;
  LeftBack = left;
}
void resetDriveEncoders() {
  LeftBack.tare_position(); //tare postion = reset encoder units to 0
  LeftFront.tare_position();
  RightBack.tare_position();
  RightFront.tare_position();
}

double avgDriveEncoderValue() {//checks ALL encoders
  return (fabs(LeftFront.get_position()) +
         fabs(LeftBack.get_position()) +
         fabs(RightFront.get_position()) +
         fabs(RightBack.get_position())) / 4; //finds the average value of all encoders, and adjusts the robot accordingly
}

//driver control functions

void setDriveMotors() {
  int leftJoyStick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoyStick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  if(abs(leftJoyStick) < 10) //deadzone, need the absolute value so the robot can consider negative values, otherwise, anything negative will be set to 0.
    leftJoyStick = 0;
  if(abs(rightJoyStick) < 10)
    rightJoyStick = 0;

  setDrive(leftJoyStick, rightJoyStick);
}
//auton Functions

void translate(int units, int voltage) {
  //define a direction based on the units provided
  int direction = abs(units) / units; //either 1 or -1, allows negatives/ going backwards
  //reset motor encoders and gyro
  resetDriveEncoders();
  gyro.reset();
  //drive forward until units are reached
  while(avgDriveEncoderValue() < abs(units)) { //while the position of our robot is less then the units, fabs can cover decimals, abs cant
    setDrive(voltage * direction + gyro.get_value(), voltage * direction - gyro.get_value()); //set drive to voltage aka 127
    //if the gyro becomes negative, it'll correct itself by adding more units until corrected
    pros::delay(10);
  }
  //brief brake
  setDrive(-10 * direction, -10 * direction); //removes momentum when stopping
  pros::delay(50);
  //set drive back to neutral
  setDrive(0, 0); //if i dont do this, drive will continue at -10
}

void rotate(int degrees, int voltage) {
  //define direction based on units provided (1 or -1, left or right), positive left, negative right.
  int direction = abs(degrees) / degrees;
  //resetting gyro
  gyro.reset();
  //turn until units - 5 are reached
  setDrive(-voltage * direction, voltage * direction);
  while(fabs(gyro.get_value()) < abs(degrees * 10) - 50) {

    pros::delay(10);
  }
  //losing momentum
  pros::delay(100);
  //correcting for undershooting/overshooting
  if(fabs(gyro.get_value()) > abs(degrees * 10)){
    setDrive(0.5 * voltage * direction, 0.5 -voltage * direction);
    while(fabs(gyro.get_value()) < abs(degrees * 10)){
      pros::delay(10);
    }
  }
  else if(fabs(gyro.get_value()) < abs(degrees * 10)){
    setDrive(0.5 * -voltage * direction, 0.5 * voltage * direction);
    while(fabs(gyro.get_value()) < abs(degrees * 10)){
      pros::delay(10);
    }
  }
  //reset drive to zero
  setDrive(0, 0);
}
/*
PID CODE
//Settings
double kP = 0.00001; //get the error
double kI = 0.0; //Precision
double kD = 0.0; //remove oscillations
double TurnkP = 0.0;
double TurnkI = 0.0;
double TurnkD = 0.0;
//Auton Settings
int desiredValue = 200;
int desiredTurnValue = 0;
int totalError = 0;
int prevError = 0.0;
int TurnTotalError = 0.0;
int TurnPrevError = 0.0;

bool enableDrivePID = true;

int drivePID(){

  pros::Task PID(drivePID);
  while(enableDrivePID){

  //get postition of motors
    int LeftBackPosition = LeftBack.get_position();
    int LeftFrontPosition = LeftFront.get_position();
    int RightFrontPosition = RightFront.get_position();
    int RightBackPosition = RightBack.get_position();
    //get average of motors
    //LATERAL MOVEMENT PID
    int AveragePosition = (LeftBackPosition + RightBackPosition + LeftFrontPosition + RightFrontPosition)/4;

    //potential
    int error = AveragePosition - desiredValue;
    //derivative
    int derivative = error - prevError;
    //integral
    int totalError = totalError + error;//continue to add velocity

    double lateralMotorPower = (error * kP + derivative * kD + totalError * kI) / 12.0;



    //TURNING MOVEMENT PID

    void setDriveMotors();

    int TurnDifference = (LeftBackPosition + LeftFrontPosition) - (RightFrontPosition + RightBackPosition);

    //potential
    int TurnError = AveragePosition - desiredTurnValue;
    //derivative
    int turnDerivative = error - TurnPrevError;
    //integral
    int TurnTotalError = TurnTotalError + TurnError;//continue to add velocity

    double turnMotorPower = (TurnError * TurnkP + turnDerivative * TurnkD + TurnTotalError * TurnkI) / 12.0;

    LeftFront.move_voltage(lateralMotorPower + turnMotorPower);
    LeftBack.move_voltage(lateralMotorPower + turnMotorPower);
    RightFront.move_voltage(lateralMotorPower - turnMotorPower);
    RightBack.move_voltage(lateralMotorPower - turnMotorPower);

    //code

   int prevError = error;
   int turnPrevError = TurnError;
    pros::delay(10);
  }

  return 1;
}
*/
