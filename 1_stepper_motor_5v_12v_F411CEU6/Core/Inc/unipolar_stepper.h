/******************************************************************************
  * @file           : unipolar_stepper.h
  * @Created on     : Sep 30, 2023
  * @brief          : unipolar stepper motor controlling setup header
  * @Author         : Mani
  *****************************************************************************/

#ifndef INC_UNIPOLAR_STEPPER_H_
#define INC_UNIPOLAR_STEPPER_H_

extern void Wave_drive_with_angle_UNIPOLAR(int direction,float angle,int rpm);
extern void Full_drive_with_angle_UNIPOLAR(int direction,float angle,int rpm);
extern void Half_drive_with_angle_UNIPOLAR(int direction,float angle,int rpm);

#endif /* INC_UNIPOLAR_STEPPER_H_ */
