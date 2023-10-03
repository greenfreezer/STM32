/******************************************************************************
  * @file           : unipolar_stepper.c
  * @Created on     : Oct 01, 2023
  * @brief          : Unipolar stepper motor controlling setup
  * @Author         : Mani
  *****************************************************************************/
/*include */
#include <main.h>

/* external handlers */
extern TIM_HandleTypeDef htim3;

/* macro*/
#define output_1_port_UNIPOLAR GPIOB
#define output_2_port_UNIPOLAR GPIOB
#define output_3_port_UNIPOLAR GPIOB
#define output_4_port_UNIPOLAR GPIOB
#define output_1_pin_UNIPOLAR GPIO_PIN_12
#define output_2_pin_UNIPOLAR GPIO_PIN_13
#define output_3_pin_UNIPOLAR GPIO_PIN_14
#define output_4_pin_UNIPOLAR GPIO_PIN_15

/* variables*/
uint16_t Wave_steps_UNIPOLAR=2048; //step count__ In my motor for one revolution 2048 @green steps
uint16_t Full_steps_UNIPOLAR=2048;
uint16_t Half_steps_UNIPOLAR=4096;
uint8_t Wave_step_sequence_UNIPOLAR=4;//}
uint8_t Full_step_sequence_UNIPOLAR=4;//}refer step_sequence sequence
uint8_t Half_step_sequence_UNIPOLAR=8;//}

//create micro second delay
void delay_us(uint16_t delay){
	__HAL_TIM_SET_COUNTER(&htim3,0);
	while(__HAL_TIM_GET_COUNTER(&htim3)<delay);
}

/**********************************************************************************
 * Function : unipolar stepper motor rpm setting
 * Purpose  : To ENABLE rpm for unipolar stepper motor in wave, full,half @green step drive
 * formula  : 60x10^6 is for 1 minute, (60x10^6)microsecond= 60second, because @green of rotation per minute.
 *           so delay in micro second={[(60x10^6)/steps]/rpm} microseconds.
 * notes    : im declare 8bit for rpm, so need rpm above 255 change to 16bit value
 *            also max rpm is 14. 1khz/4step
 * *******************************************************************************/
void Wave_drive_rpm_UNIPOLAR(uint8_t rpm){
	delay_us(60000000/Wave_steps_UNIPOLAR/rpm);
}

void Full_drive_rpm_UNIPOLAR(uint8_t rpm){
	delay_us(60000000/Full_steps_UNIPOLAR/rpm);
}

void Half_drive_rpm_UNIPOLAR(uint8_t rpm){
	delay_us(60000000/Half_steps_UNIPOLAR/rpm);
}

/**********************************************************************************
 * Function : unipolar stepper motor drive sequence setup
 * Purpose  : To drive stepper motor by using Wave_drive sequence method
 * formula  :
 * notes    : In wave drive method only one pole has been energized in one sequence.steps=2048
 * *******************************************************************************/
void Wave_drive_mode_UNIPOLAR(uint8_t sequence){

		switch(sequence){
		        case 0:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, ENABLE);  //INT-1  }
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, DISABLE); //INT-2  } this four output @green equals
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, DISABLE); //INT-3  }   one sequence
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, DISABLE); //INT-4  }
		        	break;
		        case 1:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, ENABLE);  //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, DISABLE); //INT-4
		        	break;
		        case 2:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, ENABLE);  //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, DISABLE); //INT-4
		        	break;
		        case 3:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, ENABLE);  //INT-4
		        	break;
		        	}
}

/**********************************************************************************
 * Function : unipolar stepper motor drive sequence setup
 * Purpose  : To drive stepper motor by using full_drive sequence method
 * formula  :
 * notes    : In full drive method two pole has been energized in one sequence at same time opposite of @green poles.steps=2048
 * *******************************************************************************/
void Full_drive_mode_UNIPOLAR(uint8_t sequence){

		switch(sequence){
		        case 0:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, ENABLE);  //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, ENABLE);  //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, DISABLE); //INT-4
		        	break;
		        case 1:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, ENABLE);  //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, ENABLE);  //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, DISABLE); //INT-4
		        	break;
		        case 2:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, ENABLE);  //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, ENABLE);  //INT-4
		        	break;
		        case 3:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, ENABLE);  //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, ENABLE);  //INT-4
		        	break;
		        	}
}

/**********************************************************************************
 * Function : unipolar stepper motor drive sequence setup
 * Purpose  : To drive stepper motor by using Half_drive @green sequence method
 * formula  :
 * notes    : In half drive method eight sequence progressed, 2 poles energized same time, also half @green driven,so steps=4096
 * *******************************************************************************/
void Half_drive_mode_UNIPOLAR(uint8_t sequence){

		switch(sequence){
		        case 0:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, ENABLE);  //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, DISABLE); //INT-4
		        	break;
		        case 1:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, ENABLE);  //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, ENABLE);  //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, DISABLE); //INT-4
		        	break;
		        case 2:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, ENABLE);  //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, DISABLE); //INT-4
		        	break;
		        case 3:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, ENABLE);  //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, ENABLE);  //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, DISABLE); //INT-4
		        	break;
		        case 4:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, ENABLE);  //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, DISABLE); //INT-4
		        	break;
		        case 5:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, ENABLE);  //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, ENABLE);  //INT-4
		        	break;
		        case 6:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, ENABLE);  //INT-4
		        	break;
		        case 7:
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, ENABLE);  //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, ENABLE);  //INT-4
		        	break;
		        	}
}

/**********************************************************************************
 * Function : unipolar stepper motor drive sequence setup
 * Purpose  : To stop stepper motor
 * formula  :
 * notes    : all pins are pull_down to stop
 * *******************************************************************************/
void Holding_UNIPOLAR(){
		        	HAL_GPIO_WritePin(output_1_port_UNIPOLAR, output_1_pin_UNIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_UNIPOLAR, output_2_pin_UNIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_UNIPOLAR, output_3_pin_UNIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_UNIPOLAR, output_4_pin_UNIPOLAR, DISABLE); //INT-4
}

/**********************************************************************************
 * Function : unipolar stepper motor Angle setting
 * Purpose  : To control step angle in motor by using wave_drive sequence method
 * formula  : for one sequence ,the change of moving angle=[(full rotation(360`)/(step_count/step_sequence)]
 *           so, total number of sequence for given angle=(given angle/moving of angle per sequence)
 *           total steps per sequence=steps/step_sequence=2048/4=>512
 * notes    :
 * *******************************************************************************/
void Wave_drive_with_angle_UNIPOLAR(int direction,float angle,int rpm){

	float angle_stepping_per_sequence=0.703125;//(float)(360/(Wave_steps_UNIPOLAR/@green Wave_step_sequence_UNIPOLAR));
	int total_num_of_sequence=(int)(angle/angle_stepping_per_sequence);


	for(int S=0; S<total_num_of_sequence; S++){

		    if(direction==0){ //CW

			     for(int D=(Wave_step_sequence_UNIPOLAR-1); D>=0; D--)
			     {
				     Wave_drive_mode_UNIPOLAR(D);
				     Wave_drive_rpm_UNIPOLAR(rpm);
			     }
		     }
			else if(direction==1){ //CCW

				for(int D=0; D<Wave_step_sequence_UNIPOLAR; D++)
				{
					Wave_drive_mode_UNIPOLAR(D);
					Wave_drive_rpm_UNIPOLAR(rpm);
				}
			}

	}
	Holding_UNIPOLAR();
}

/**********************************************************************************
 * Function : unipolar stepper motor Angle setting
 * Purpose  : To control step angle in motor by using Full_drive sequence method
 * formula  : for one sequence ,the change of moving angle=[(full rotation(360`)/(step_count/step_sequence)]
 *           so, total number of sequence for given angle=(given angle/moving of @green angle per sequence)
 *           total steps per sequence=steps/step_sequence=2048/4=>512
 * notes    :
 * *******************************************************************************/
void Full_drive_with_angle_UNIPOLAR(int direction,float angle,int rpm){

	float angle_stepping_per_sequence=0.703125;//(float)(360/(Full_steps_UNIPOLAR/Full_step_sequence_UNIPOLAR));
	int total_num_of_sequence=(int)(angle/angle_stepping_per_sequence);


	for(int S=0; S<total_num_of_sequence; S++){

		    if(direction==0){ //CW

			     for(int D=(Full_step_sequence_UNIPOLAR-1); D>=0; D--)
			     {
				     Full_drive_mode_UNIPOLAR(D);
				     Full_drive_rpm_UNIPOLAR(rpm);
			     }
		     }
			else if(direction==1){ //CCW

				for(int D=0; D<Full_step_sequence_UNIPOLAR; D++)
				{
					Full_drive_mode_UNIPOLAR(D);
					Full_drive_rpm_UNIPOLAR(rpm);
				}
			}

	}
	Holding_UNIPOLAR();
}

/**********************************************************************************
 * Function : unipolar stepper motor Angle setup
 * Purpose  : To control step angle in motor by using Half_drive sequence method
 * formula  : for one sequence ,the change of moving angle=[(full rotation(360`)/(step_count/step_sequence)]
 *           so, total number of sequence for given angle=(given angle/moving of angle per sequence)@green
 *           total steps per sequence=steps/step_sequence=4096/8=>512
 * notes    :
 * *******************************************************************************/
void Half_drive_with_angle_UNIPOLAR(int direction,float angle,int rpm){

	float angle_stepping_per_sequence=0.703125;//(float)(360/(Half_steps_UNIPOLAR/Half_step_sequence_UNIPOLAR));@green
	int total_num_of_sequence=(int)(angle/angle_stepping_per_sequence);


	for(int S=0; S<total_num_of_sequence; S++){

		    if(direction==0){ //CW

			     for(int D=(Half_step_sequence_UNIPOLAR-1); D>=0; D--)
			     {
				     Half_drive_mode_UNIPOLAR(D);
				     Half_drive_rpm_UNIPOLAR(rpm);
			     }
		     }
			else if(direction==1){ //CCW

				for(int D=0; D<Half_step_sequence_UNIPOLAR; D++)
				{
					Half_drive_mode_UNIPOLAR(D);
					Half_drive_rpm_UNIPOLAR(rpm);
				}
			}

	}
	Holding_UNIPOLAR();
}
