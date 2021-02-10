#include "main.h"
//helper functions

void setIntake(int power){
  IntakeLeft = power;
  IntakeRight = power;

}
//driver control functions

void setIntakeMotors(){
  int IntakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
  //127 is max power, when you press L1 or L2 the value gets set to 1, so when you press L1, but not l2, it become 127 x (1 - 0) = 127 power,
  //when you press L2, 127 x (0 - 1) = -127 power, and when you press neither, 127 x (0 - 0) = 0 power, same with if you press both.
  setIntake(IntakePower);
//top bumpers intake, bottom outtake
}
