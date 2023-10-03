/******************************************************************************
  * @file           : bipolar_stepper.c
  * @Created on     : Oct 01, 2023
  * @brief          : Bipolar stepper motor controlling setup
  * @Author         : Mani
  *****************************************************************************/
/*include */
#include <main.h>

/* external handlers */

/* macro*/
#define output_1_port_BIPOLAR GPIOB
#define output_2_port_BIPOLAR GPIOB
#define output_3_port_BIPOLAR GPIOB
#define output_4_port_BIPOLAR GPIOB
#define output_1_pin_BIPOLAR GPIO_PIN_12
#define output_2_pin_BIPOLAR GPIO_PIN_13
#define output_3_pin_BIPOLAR GPIO_PIN_14
#define output_4_pin_BIPOLAR GPIO_PIN_15

/* variables*/
uint8_t Wave_steps_BIPOLAR=200; //step count__ In my motor for one step moves=1.8` angle. so total num of step full rotation=360*1.8=200steps
uint8_t Full_steps_BIPOLAR=200;
uint16_t Half_steps_BIPOLAR=400;
uint8_t Wave_step_sequence_BIPOLAR=4;//}
uint8_t Full_step_sequence_BIPOLAR=4;//}refer step_sequence sequence
uint8_t Half_step_sequence_BIPOLAR=8;//}

/**********************************************************************************
 * Function : bipolar stepper motor rpm setting
 * Purpose  : To set rpm for bipolar stepper motor in wave, full,half step drive
 * formula  : 60x10^6 is for 1 minute, (60x10^6)microsecond= 60second, because of rotation per minute.
 *           so delay in micro second={[(60x10^6)/steps]/rpm} microseconds.
 * notes    : @green im declare 8bit for rpm, so need rpm above 255 change @green to 16bit value
 *            also max rpm is 14. f/w=1kz/4sequence or halfstep=1khz/8sequence
 *            in delay us 1mhz crystal setting, so 1=(1x10^-6)
 * *******************************************************************************/
void Wave_drive_rpm_BIPOLAR(uint16_t rpm){
	delay_us(60000000/Wave_steps_BIPOLAR/rpm);// get ans of time and 1/t=>f/4   //max rpm=300 ->1000hz
}

void Full_drive_rpm_BIPOLAR(uint16_t rpm){
	delay_us(60000000/Full_steps_BIPOLAR/rpm);
}

void Half_drive_rpm_BIPOLAR(uint16_t rpm){
	delay_us(60000000/Half_steps_BIPOLAR/rpm);
}

/**********************************************************************************
 * Function : bipolar stepper motor drive sequence setup
 * Purpose  : To drive stepper motor by using Wave_drive sequence method
 * formula  :
 * notes    : In wave drive method only one pole has been energized in one sequence.steps=200
 * *******************************************************************************/
void Wave_drive_mode_BIPOLAR(uint8_t sequence){

		switch(sequence){
		        case 0:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, ENABLE);  //INT-1  }
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, DISABLE); //INT-2  } this four output equals
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, DISABLE); //INT-3  }   one sequence
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, DISABLE); //INT-4  }
		        	break;
		        case 1:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, ENABLE);  //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, DISABLE); //INT-4
		        	break;
		        case 2:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, ENABLE);  //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, DISABLE); //INT-4
		        	break;
		        case 3:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, ENABLE);  //INT-4
		        	break;
		        	}
}

/**********************************************************************************
 * Function : bipolar stepper motor drive sequence setup
 * Purpose  : To drive stepper motor by using full_drive sequence method
 * formula  :
 * notes    : In full drive method two pole has been energized in one sequence at same @green time opposite of poles.steps=200
 * *******************************************************************************/
void Full_drive_mode_BIPOLAR(uint8_t sequence){

		switch(sequence){
		        case 0:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, ENABLE);  //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, ENABLE);  //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, DISABLE); //INT-4
		        	break;
		        case 1:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, ENABLE);  //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, ENABLE);  //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, DISABLE); //INT-4
		        	break;
		        case 2:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, ENABLE);  //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, ENABLE);  //INT-4
		        	break;
		        case 3:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, ENABLE);  //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, ENABLE);  //INT-4
		        	break;
		        	}
}

/**********************************************************************************
 * Function : bipolar stepper motor drive sequence setup
 * Purpose  : To drive stepper motor by using Half_drive sequence method
 * formula  :
 * notes    : In half drive method eight sequence progressed, 2 poles @green energized same time, also half driven,so steps=400
 * *******************************************************************************/
void Half_drive_mode_BIPOLAR(uint8_t sequence){

		switch(sequence){
		        case 0:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, ENABLE);  //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, DISABLE); //INT-4
		        	break;
		        case 1:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, ENABLE);  //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, ENABLE);  //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, DISABLE); //INT-4
		        	break;
		        case 2:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, ENABLE);  //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, DISABLE); //INT-4
		        	break;
		        case 3:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, ENABLE);  //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, ENABLE);  //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, DISABLE); //INT-4
		        	break;
		        case 4:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, ENABLE);  //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, DISABLE); //INT-4
		        	break;
		        case 5:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, ENABLE);  //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, ENABLE);  //INT-4
		        	break;
		        case 6:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, DISABLE); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, ENABLE);  //INT-4
		        	break;
		        case 7:
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, ENABLE);  //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, DISABLE); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, DISABLE); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, ENABLE);  //INT-4
		        	break;
		        	}
}

/**********************************************************************************
 * Function : bipolar stepper motor drive sequence setup
 * Purpose  : To stop stepper motor
 * formula  :
 * notes    : all pins are pull_down to stop
 * *******************************************************************************/
void Holding_BIPOLAR(){
		        	HAL_GPIO_WritePin(output_1_port_BIPOLAR, output_1_pin_BIPOLAR, GPIO_PIN_RESET); //INT-1
		        	HAL_GPIO_WritePin(output_2_port_BIPOLAR, output_2_pin_BIPOLAR, GPIO_PIN_RESET); //INT-2
		        	HAL_GPIO_WritePin(output_3_port_BIPOLAR, output_3_pin_BIPOLAR, GPIO_PIN_RESET); //INT-3
		        	HAL_GPIO_WritePin(output_4_port_BIPOLAR, output_4_pin_BIPOLAR, GPIO_PIN_RESET); //INT-4
}
/**********************************************************************************
 * Function : bipolar stepper motor Angle setting
 * Purpose  : To control step angle in motor by using wave_drive sequence method
 * formula  : for one sequence ,the change of moving angle=[(full rotation(360`)/(step_count/step_sequence)]@green
 *           so, total number of sequence for given angle=(given angle/moving of angle per sequence)
 *           total steps per sequence=steps/step_sequence=400/4=>50
 * notes    :in unipolar im using value for angle step per sequence, but here we got 7.2 so im using this value float takes time@green
 * *******************************************************************************/
void Wave_drive_with_angle_BIPOLAR(int direction,float angle,int rpm){

	float angle_stepping_per_sequence=7.2;//(float)(360/(Wave_steps_BIPOLAR/Wave_step_sequence_BIPOLAR));
	int total_num_of_sequence=(int)(angle/angle_stepping_per_sequence);


	for(int S=0; S<total_num_of_sequence; S++){

		    if(direction==0){ //CW

			     for(int D=0; D<Wave_step_sequence_BIPOLAR; D++)
			     {
				     Wave_drive_mode_BIPOLAR(D);
				     Wave_drive_rpm_BIPOLAR(rpm);
			     }
		     }
			else if(direction==1){ //CCW

				for(int D=(Wave_step_sequence_BIPOLAR-1); D>=0; D--)
				{
					Wave_drive_mode_BIPOLAR(D);
					Wave_drive_rpm_BIPOLAR(rpm);
				}
			}

	}
	Holding_BIPOLAR();
}

/**********************************************************************************
 * Function : bipolar stepper motor Angle setting
 * Purpose  : To control step angle in motor by using Full_drive sequence method
 * formula  : for one sequence ,the change of moving angle=[(full rotation(360`)/(step_count/step_sequence)]
 *           so, total number of sequence for given angle=(given angle/moving of angle per sequence)@green
 *           total steps per sequence=steps/step_sequence=400/4=>50
 * notes    :
 * *******************************************************************************/
void Full_drive_with_angle_BIPOLAR(int direction,float angle,int rpm){

	float angle_stepping_per_sequence=7.2;//(float)(360/(Full_steps_BIPOLAR/Full_step_sequence_BIPOLAR));
	int total_num_of_sequence=(int)(angle/angle_stepping_per_sequence);


	for(int S=0; S<total_num_of_sequence; S++){

		    if(direction==0){ //CW

			     for(int D=0; D<Full_step_sequence_BIPOLAR; D++)
			     {
				     Full_drive_mode_BIPOLAR(D);
				     Full_drive_rpm_BIPOLAR(rpm);
			     }
		     }
			else if(direction==1){ //CCW

				for(int D=(Full_step_sequence_BIPOLAR-1); D>=0; D--)
				{
					Full_drive_mode_BIPOLAR(D);
					Full_drive_rpm_BIPOLAR(rpm);
				}
			}

	}
	Holding_BIPOLAR();
}

/**********************************************************************************
 * Function : bipolar stepper motor Angle setup
 * Purpose  : To control step angle in motor by using Half_drive sequence method
 * formula  : for one sequence ,the change of moving angle=[(full rotation(360`)/(step_count/step_sequence)]
 *           so, total number of sequence for given angle=(given angle/moving of angle per sequence)
 *           total steps per sequence=steps/step_sequence=800/8=>50
 * notes    :
 * *******************************************************************************/
void Half_drive_with_angle_BIPOLAR(int direction,float angle,int rpm){

	float angle_stepping_per_sequence=7.2;//(float)(360/(Half_steps_BIPOLAR/Half_step_sequence_BIPOLAR));//@green
	int total_num_of_sequence=(int)(angle/angle_stepping_per_sequence);


	for(int S=0; S<total_num_of_sequence; S++){

		    if(direction==0){ //CW

			     for(int D=0; D<Half_step_sequence_BIPOLAR; D++)
			     {
				     Half_drive_mode_BIPOLAR(D);
				     Half_drive_rpm_BIPOLAR(rpm);
			     }
		     }
			else if(direction==1){ //CCW

				for(int D=(Half_step_sequence_BIPOLAR-1); D>=0; D--)
				{
					Half_drive_mode_BIPOLAR(D);
					Half_drive_rpm_BIPOLAR(rpm);
				}
			}

	}
	Holding_BIPOLAR();
}
