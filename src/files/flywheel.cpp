#include "main.h"
void setFlywheel(int power){
  IntakeLeft = power;
  IntakeRight = power;

}
//driver control functions

void setFlywheelMotor(){
  int flywheelPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X));
  setFlywheel(flywheelPower);
//X Shoot
}
