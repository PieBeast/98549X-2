#include "main.h"
//helper functions

void setDrive(int left, int right);
void resetDriveEncoders();
double avgDriveEncoderValue();
//driver control functions

void setDriveMotors();
//Auton Functions

void translate(int units, int voltage); //moving or TRANSLATING from one "point" of the field to another
void rotate(int degrees, int voltage);

int drivePID();

//double kP();
//double kI();
//double kD();

int error();  //SensorValue - Desired Value, difference of where you are vs where you want to be, positional value
//int prevError(); //Position 10 msec ago
int derivative(); //difference between error and prev error, will speed up and slow down based on certain factors(battery voltage, friction)
int turnDerivative();
int turnError();
//int totalError();

int LeftFrontPosition();
int RightFrontPosition();
int LeftBackPosition();
int RightBackPosition();
int AveragePosition();

//int desiredValue();

//bool enableDrivePID();
