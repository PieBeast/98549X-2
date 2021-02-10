#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {

}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "It works I think");

	LeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	LeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	RightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	RightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	Flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	IntakeLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  IntakeRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	Indexer.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	pros::ADIGyro gyro('A');
	pros::delay(2000);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
 //ALWAYS HAVE NEGATIVE UNITS, CANT HAVE NEGATIVE SPEED ((-500, 100) not (500, -100))
void redBack() {



}
void redFront() {

}
void blueBack() {

}
void blueFront() {

}
void autonomous() {
	pros::Task PID(drivePID);
	bool enableDrivePID = true;

	//redBack();
	//redFront();
	//blueBack();
	//blueFront();
}
//hpp = declaring different headers aka header file, cpp is the actual code behind the headers, aka source file
//Different section for each component/motor
//driver code written in drive.cpp
void opcontrol() {
	while(true){
		bool enableDriverPID = false;
		//drive code
		setDriveMotors();
		//intake code
		setIntakeMotors();
		//indexer code
		setIndexerMotor();
		//flywheel code
		setFlywheelMotor();
	pros::delay(10); //need this as the robot runs this loop every few ms, aka what speed its being set to, but it takes ~10ms for the motors to update their voltage
	}
}
