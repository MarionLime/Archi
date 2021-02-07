/*
 * TD_EVAL_MEMS.h
 *
 *  Created on: Jan 11, 2021
 *      Author: Mtapia
 */

#ifndef INC_TD_EVAL_MEMS_H_
#define INC_TD_EVAL_MEMS_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>



/* Define Register */
#define	LIS3DSH_CTRL_REG4						0x20
#define LIS3DSH_CTRL_REG5						0x24
#define LIS3DSH_STATUS							0x27
#define LIS3DSH_OUT_X							0x28
#define LIS3DSH_OUT_Y							0x2A



						/*		CTRL_REG4 PARAMETER		*/

/* Define coo X, Y, Z Enable "HIGH"  */
#define LIS3DSH_CTRL4_X_Enable					((uint8_t)0x01)		/*	Axe X High	*/
#define LIS3DSH_CTRL4_Y_Enable					((uint8_t)0x02)		/*	Axe Y High	*/

/* Define coo X, Y, Z Disable "LOW" */
#define LIS3DSH_CTRL4_X_Disable					((uint8_t)0x00)		/*	Axe X High	*/
#define LIS3DSH_CTRL4_Y_Disable					((uint8_t)0x00)		/*	Axe Y High	*/

/* Define Output Data Rate */
#define LIS3DSH_CTRL4_OutputRegister_Down		0x00		/*	Power Down	*/
#define LIS3DSH_CTRL4_OutputRegister_3			0x10		/*	3,125 Hz	*/
#define LIS3DSH_CTRL4_OutputRegister_6			0x20		/*	 6,25 Hz	*/
#define LIS3DSH_CTRL4_OutputRegister_12			0x30		/*   12,5 Hz	*/
#define LIS3DSH_CTRL4_OutputRegister_25			0x40		/*     25 Hz	*/
#define LIS3DSH_CTRL4_OutputRegister_50			0x50		/*     50 Hz	*/
#define LIS3DSH_CTRL4_OutputRegister_10			0x60		/*    100 Hz	*/
#define LIS3DSH_CTRL4_OutputRegister_400		0x70		/*    400 Hz	*/
#define LIS3DSH_CTRL4_OutputRegister_800		0x80		/*    800 Hz	*/
#define LIS3DSH_CTRL4_OutputRegister_1600		0x90		/*   1600 Hz	*/



						/*		CTRL_REG5 PARAMETER		*/

/* Define Anti-Aliasing Bandwirdth */
#define LIS3DSH_CTRL5_AntiAliasing_50			0xC0		/*     50 Hz 	*/
#define LIS3DSH_CTRL5_AntiAliasing_200			0x40		/*    200 Hz 	*/
#define LIS3DSH_CTRL5_AntiAliasing_400			0x80		/*    400 Hz  	*/
#define LIS3DSH_CTRL5_AntiAliasing_800			0x00		/*    800 Hz  	*/


/* Define Full-scale Selection */
#define LIS3DSH_CTRL5_FullScale_2				0x00		/*    +- 2 g 	*/
#define LIS3DSH_CTRL5_FullScale_4				0x08		/*    +- 4 g  	*/
#define LIS3DSH_CTRL5_FullScale_6				0x10		/*    +- 6 g 	*/
#define LIS3DSH_CTRL5_FullScale_8				0x18		/*    +- 8 g  	*/
#define LIS3DSH_CTRL5_FullScale_16				0x20		/*   +- 16 g  	*/



						/*		INITIALISATION	PARAMETER		*/

/* Init struct */
typedef struct
{
	uint8_t AXE_X;
	uint8_t AXE_Y;
	uint8_t CTRL4_OutputRegister;
	uint8_t CTRL5_AntiAliasing;
	uint8_t CTRL5_FullScale;
}LIS3DSH_init_t;


/* status enum */
typedef enum
{
	LIS3DSH_OK,
	LIS3DSH_ERROR
}LIS3DSH_Status_t;


/* Write Function */
LIS3DSH_Status_t LIS3DSH_Write_reg(SPI_HandleTypeDef *accelSPI,
									uint8_t reg_addr,
									uint8_t *dataW,
									uint8_t size);


/* Read Function */
LIS3DSH_Status_t LIS3DSH_Write_reg(SPI_HandleTypeDef *accelSPI,
									uint8_t reg_addr,
									uint8_t *dataR,
									uint8_t size);


/* Init Function */
LIS3DSH_Status_t LIS3DSH_Init(SPI_HandleTypeDef *accelSPI,
							  LIS3DSH_init_t *accelInit_Def);



						/*	GET AXES	*/

/* Axe X */
LIS3DSH_Status_t LIS3DSH_Get_Axis_X(SPI_HandleTypeDef *accelSPI, int16_t *accel);

/* Axe Y */
LIS3DSH_Status_t LIS3DSH_Get_Axis_Y(SPI_HandleTypeDef *accelSPI, int16_t *accel);



#endif					/* INC_TD_EVAL_MEMS_H_ */
