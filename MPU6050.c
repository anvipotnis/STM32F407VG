//to read the value 0x68 from the WHO_AM_I register on the MPU6050
#include "stm32f4xx.h"
#include "cpal_i2c.h"

//uint8_t data;



int main(){


	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_ClockSpeed          = 100000;
	I2C_InitStruct.I2C_Mode                = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle           = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_OwnAddress1         = 0;
	I2C_InitStruct.I2C_Ack                 = I2C_Ack_Disable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

    uint8_t rxBuffer[1];
    CPAL_TransferTypeDef RX;
	RX.pbBuffer = rxBuffer;
	RX.wNumData = 1u;
	RX.wAddr1 = 0xD0;
	RX.wAddr2 = 0x75;

	CPAL_I2C_StructInit(&I2C1_DevStructure);
	I2C1_DevStructure.CPAL_Direction = CPAL_DIRECTION_TXRX;
	I2C1_DevStructure.CPAL_Mode = CPAL_MODE_MASTER;
	I2C1_DevStructure.CPAL_ProgModel = CPAL_PROGMODEL_INTERRUPT;
	I2C1_DevStructure.pCPAL_TransferRx = &RX;
	//I2C1_DevStructure.pCPAL_I2C_Struct = &I2C_InitStruct;
    //I2C1_DevStructure.CPAL_State= CPAL_STATE_DISABLED;

	CPAL_I2C_Init(&I2C1_DevStructure);
	if(CPAL_I2C_Read(&I2C1_DevStructure)==CPAL_PASS);
	while(I2C1_DevStructure.CPAL_State!=CPAL_STATE_READY_RX);

	//data = rxBuffer[0];
	//data = (data<<8u) + rxBuffer[1];
	while (1){

	}
}
