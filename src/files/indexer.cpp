#include "main.h"
//helper functions

void setIndexer(int power){
  IntakeLeft = power;
  IntakeRight = power;

}
//driver control functions

void setIndexerMotor(){
  int indexerPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1));
  setIndexer(indexerPower);
//top bumpers intake, bottom outtake
}
