/******************************************************************************
  * @file           : bipolar_stepper.h
  * @Created on     : Sep 30, 2023
  * @brief          : Bipolar stepper motor controlling setup header
  * @Author         : Mani
  *****************************************************************************/

#ifndef INC_BIPOLAR_STEPPER_H_
#define INC_BIPOLAR_STEPPER_H_

extern void Wave_drive_with_angle_BIPOLAR(int direction,float angle,int rpm);
extern void Full_drive_with_angle_BIPOLAR(int direction,float angle,int rpm);
extern void Half_drive_with_angle_BIPOLAR(int direction,float angle,int rpm);


#endif /* INC_BIPOLAR_STEPPER_H_ */
