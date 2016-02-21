#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

#include "lep_i2c.h"

void lepton_command(unsigned int moduleID, unsigned int commandID, unsigned int command)
{
  HAL_StatusTypeDef error;
  uint8_t data_write[4];
  uint8_t er[1] = {'a'};

  // Command Register is a 16-bit register located at Register Address 0x0004
  data_write[0] = (0x00);
  data_write[1] = (0x04);

  data_write[2] = (moduleID & 0x0f);
  data_write[3] = (((commandID << 2 ) & 0xfc) | (command & 0x3));

  error = HAL_I2C_Master_Transmit(&hi2c1, LEPTON_ADDRESS, data_write, 4, 1000);
  HAL_Delay(5);

  if (error != 0)
  {
    HAL_UART_Transmit(&huart1, er, 1, 1000);
  }
}

void set_reg(unsigned int reg)
{
  HAL_StatusTypeDef error;
  uint8_t er[1] = {'c'};
  uint8_t data_write[2];
  data_write[0] = (reg >> 8 & 0xff);
  data_write[1] = (reg & 0xff);

  error = HAL_I2C_Master_Transmit(&hi2c1, LEPTON_ADDRESS, data_write, 2, 1000);
  HAL_Delay(5);

   if (error != 0)
  {
    HAL_UART_Transmit(&huart1, er, 1, 1000);
  }
}

//Status reg 15:8 Error Code  7:3 Reserved 2:Boot Status 1:Boot Mode 0:busy

int read_reg(unsigned int reg)
{
  int reading = 0;
  uint8_t read_data[2];
  set_reg(reg);
  HAL_I2C_Master_Receive(&hi2c1, LEPTON_ADDRESS, read_data, 2, 1000);
  HAL_Delay(5);
  reading = read_data[0];  // receive high byte (overwrites previous reading)
  reading = reading << 8;    // shift high byte to be high 8 bits

  reading |= read_data[1]; // receive low byte as lower 8 bits
  return reading;
}

int read_metric_data()
{
  int i;
  int data;
  int payload_length;
  int sum = 0;
  uint8_t data_read[2];
  uint8_t busy[1] = {'b'};

  while (read_reg(0x2) & 0x01)
  {
    HAL_UART_Transmit(&huart1, busy , 1, 1000);
  }

  payload_length = read_reg(0x6);

  for (i = 0; i < (payload_length / 2); i++)
  {
    HAL_I2C_Master_Receive(&hi2c1, LEPTON_ADDRESS, data_read, 2, 1000);
    HAL_Delay(5);
    data = data_read[0] << 8;
    data |= data_read[1];
    sum = sum+data;
  }
  return sum;
}

void metric_enable()
{
  HAL_StatusTypeDef error;
  uint8_t er[1] = {'d'};
  uint8_t data_write[4];
  //16bit data_reg address
  data_write[0] = (0x00);
  data_write[1] = (DATA0);
  //16bit command equivalent to SDK LEP_GetAgcEnableState()
  data_write[2] = (0x00);
  data_write[3] = (0x01);
  error = HAL_I2C_Master_Transmit(&hi2c1, LEPTON_ADDRESS, data_write, 4, 1000);
  HAL_Delay(5);
  if (error != 0)
  {
    HAL_UART_Transmit(&huart1, er, 1, 1000);
  }
  //16bit data_len address
  data_write[0] = (0x00);
  data_write[1] = (DATALEN_REG);
  //16bit value for number of bytes in data_regs (not number of regs)
  data_write[2] = (0x00);
  data_write[3] = (0x02);
  error = HAL_I2C_Master_Transmit(&hi2c1, LEPTON_ADDRESS, data_write, 4, 1000);
  HAL_Delay(5);
  if (error != 0)
  {
    HAL_UART_Transmit(&huart1, er, 1, 1000);
  }
  //16bit command_reg address
  data_write[0] = (0x00);
  data_write[1] = (COMMANDID_REG);
  //16bit module id of AGC (0x0100) binary AND with SET (0x01) and then split into 2 bytes (0x0101)
  data_write[2] = (0x03);
  data_write[3] = (0x0D);
  error = HAL_I2C_Master_Transmit(&hi2c1, LEPTON_ADDRESS, data_write, 4, 1000);
  HAL_Delay(5);
  if (error != 0)
  {
    HAL_UART_Transmit(&huart1, er, 1, 1000);
  }
}

void tresh()
{
  HAL_StatusTypeDef error;
  uint8_t er[1] = {'e'};
  uint8_t data_write[4];
  //16bit data_reg address
  data_write[0] = (0x00);
  data_write[1] = (DATA0);
  //16bit command equivalent to SDK LEP_GetAgcEnableState()
  data_write[2] = (0x75);
  data_write[3] = (0x30);
  error = HAL_I2C_Master_Transmit(&hi2c1, LEPTON_ADDRESS, data_write, 4, 1000);
  HAL_Delay(5);
  if (error != 0)
  {
    HAL_UART_Transmit(&huart1, er, 1, 1000);
  }
  //16bit data_len address
  data_write[0] = (0x00);
  data_write[1] = (DATALEN_REG);
  //16bit value for number of bytes in data_regs (not number of regs)
  data_write[2] = (0x00);
  data_write[3] = (0x02);
  error = HAL_I2C_Master_Transmit(&hi2c1, LEPTON_ADDRESS, data_write, 4, 1000);
  HAL_Delay(5);
  if (error != 0)
  {
    HAL_UART_Transmit(&huart1, er, 1, 1000);
  }
  //16bit command_reg address
  data_write[0] = (0x00);
  data_write[1] = (COMMANDID_REG);
  //16bit module id of AGC (0x0100) binary AND with SET (0x01) and then split into 2 bytes (0x0101)
  data_write[2] = (0x03);
  data_write[3] = (0x15);
  error = HAL_I2C_Master_Transmit(&hi2c1, LEPTON_ADDRESS, data_write, 4, 1000);
  HAL_Delay(5);
  if (error != 0)
  {
    HAL_UART_Transmit(&huart1, er, 1, 1000);
  }
}
