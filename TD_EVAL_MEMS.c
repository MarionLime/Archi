/*
 * TD_EVAL_MEMS.c
 *
 *  Created on: Jan 11, 2021
 *      Author: Mtapia
 */

#include "TD_EVAL_MEMS.h"

// Chip Select
#define CS_ENABLE  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
#define CS_DISABLE  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
// Set sensibility
float sensitivity = 0.0f;

									/*	WRITE FONCTION	*/

LIS3DSH_Status_t LIS3DSH_Write_reg(SPI_HandleTypeDef *accelSPI,
									uint8_t reg_addr,
									uint8_t *dataW,
									uint8_t size)

{
/* dataW --> |   0 reg_addr	|  1 data_High	|  2 data_Low	| */
	CS_ENABLE;
	//uint8_t tab[2] = {reg_addr, &dataW };
	if (HAL_SPI_Transmit(accelSPI, dataW, size, 10) == HAL_OK)
	{
		CS_DISABLE;
		return LIS3DSH_OK;
	}
	CS_DISABLE;
	return LIS3DSH_ERROR;
}

									/*	READ FONCTION	*/

LIS3DSH_Status_t LIS3DSH_Read_reg(SPI_HandleTypeDef *accelSPI,
									uint8_t reg_addr,
									uint8_t *dataR,
									uint8_t size)
{
	reg_addr |= 0x80; // Mask
	CS_ENABLE;
	if (HAL_SPI_Transmit(accelSPI, &reg_addr, size, 10) == HAL_OK)
	{
		if (HAL_SPI_Receive(accelSPI, dataR, size, 10) == HAL_OK)
		{
			CS_DISABLE;
			return LIS3DSH_OK;
		}
	}
	CS_DISABLE;
	return LIS3DSH_ERROR;
}

									/*	INIT. FONCTION	*/

LIS3DSH_Status_t LIS3DSH_Init(SPI_HandleTypeDef *accelSPI, LIS3DSH_init_t *accelInitDef)
{
	uint8_t spiData= 0x00;
	uint8_t spiCheckData = 0x00;

	/*	Sensitivity characteristics	*/
//  Mechanical sensitivity of the component.
switch (accelInitDef-> CTRL5_FullScale)
{
	case LIS3DSH_CTRL5_FullScale_2 :
		sensitivity = 0.06;
		break;
	case LIS3DSH_CTRL5_FullScale_4 :
		sensitivity = 0.12;
		break;
	case LIS3DSH_CTRL5_FullScale_6 :
		sensitivity = 0.18;
		break;
	case LIS3DSH_CTRL5_FullScale_8 :
		sensitivity = 0.24;
		break;
	case LIS3DSH_CTRL5_FullScale_16 :
		sensitivity = 0.73;
		break;
}

	/*	Data High register conf.	*/
	spiData	|= (accelInitDef->CTRL4_OutputRegister & 0x80);
	spiData |= (accelInitDef->CTRL5_AntiAliasing & 0x00);
	spiData |= (accelInitDef->CTRL5_FullScale & 0x00);

	/*	Data Low register conf.	*/
	spiData |= (accelInitDef->AXE_X & 0x01);
	spiData |= (accelInitDef->AXE_Y & 0x02);

	if(LIS3DSH_Write_reg(accelSPI, LIS3DSH_STATUS, &spiData, 3) == LIS3DSH_OK)
	{
		if (LIS3DSH_Read_reg(accelSPI,LIS3DSH_STATUS, &spiCheckData, 2) == LIS3DSH_OK)
		{
			if (spiCheckData == spiData)
			{
			return LIS3DSH_OK;
			}
		}
	}
	return LIS3DSH_ERROR;

}

									/* GET AXIS */

/* Axe X */

LIS3DSH_Status_t LIS3DSH_Get_Axis_X(SPI_HandleTypeDef *accelSPI, int16_t *accel)
{
	uint8_t dataR[2] = {0x00,0x00};
	uint16_t accelRaw = 0x0000;


	if(LIS3DSH_Read_reg(accelSPI, LIS3DSH_OUT_X, dataR, 2) == LIS3DSH_OK)
	{
		accelRaw = (dataR[1] << 8 | dataR[0]);
		float accel = accelRaw * sensitivity;


		return LIS3DSH_OK;
	}
	if(LIS3DSH_Read_reg(accelSPI, LIS3DSH_OUT_X, dataR, 2) == LIS3DSH_OK)
	{
		accelRaw = (dataR[1] << 8 | dataR[0]);
		float accel = accelRaw * sensitivity;

		return LIS3DSH_OK;
	}
}

/* Axe Y */

LIS3DSH_Status_t LIS3DSH_Get_Axis_Y(SPI_HandleTypeDef *accelSPI, int16_t *accel)
{
	uint8_t dataR[2] = { 0x00, 0x00 };
	uint16_t accelRaw = 0x0000;

	if(LIS3DSH_Read_reg(accelSPI, LIS3DSH_OUT_Y, dataR, 2) == LIS3DSH_OK)
	{
		accelRaw = (dataR[1] << 8 | dataR[0]);
		float accel = accelRaw * sensitivity;

		return LIS3DSH_OK;
	}
	if(LIS3DSH_Read_reg(accelSPI, LIS3DSH_OUT_Y, dataR, 2) == LIS3DSH_OK)
	{
		accelRaw = (dataR[1] << 8 | dataR[0]);
		float accel = accelRaw * sensitivity;

		return LIS3DSH_OK;
	}
}

