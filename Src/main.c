/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"


/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
#define LEPTON_ADDRESS  (0x54)

#define POWER_REG (0x00)
#define STATUS_REG (0x02)
#define DATA_CRC_REG (0x28)

#define COMMANDID_REG (0x04)
#define DATALEN_REG (0x06)
#define DATA0 (0x08)

#define AGC (0x01)
#define SYS (0x02)
#define VID (0x03)
#define OEM (0x48)

#define GET (0x00)
#define SET (0x01)
#define RUN (0x02)

#define PING                        (0x00 )
#define CAM_STATUS                  (0x04 )
#define FLIR_SERIAL_NUMBER          (0x08 )
#define CAM_UPTIME                  (0x0C )
#define AUX_TEMPERATURE_KELVIN      (0x10 )
#define FPA_TEMPERATURE_KELVIN      (0x14 )
#define TELEMETRY_ENABLE_STATE      (0x18 )
#define TELEMETRY_LOCATION          (0x1C )
#define EXECTUE_FRAME_AVERAGE       (0x20 )
#define NUM_FRAMES_TO_AVERAGE       (0x24 )
#define CUST_SERIAL_NUMBER          (0x28 )
#define SCENE_STATISTICS            (0x2C )
#define SCENE_ROI                   (0x30 )
#define THERMAL_SHUTDOWN_COUNT      (0x34 )
#define SHUTTER_POSITION            (0x38 )
#define FFC_SHUTTER_MODE_OBJ        (0x3C )
#define RUN_FFC                     (0x42 )
#define FFC_STATUS                  (0x44 )

#define IMAGE_NUM_LINES 60
#define VOSPI_FRAME_SIZE 164
uint8_t Lep_Img[60][160];
uint8_t header[4];
uint8_t dma_done=1;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

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
  HAL_Delay(1);

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
  HAL_Delay(1);

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
  HAL_Delay(1);
  reading = read_data[0];  // receive high byte (overwrites previous reading)
  reading = reading << 8;    // shift high byte to be high 8 bits

  reading |= read_data[1]; // receive low byte as lower 8 bits
  return reading;
}

uint32_t read_metric_data()
{
  int i;
  uint32_t data;
  int payload_length;
  uint32_t sum = 0;
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
    HAL_Delay(1);
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
  data_write[2] = (0x00);
  data_write[3] = (0x01);
  error = HAL_I2C_Master_Transmit(&hi2c1, LEPTON_ADDRESS, data_write, 4, 1000);
  HAL_Delay(1);
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
  HAL_Delay(1);
  if (error != 0)
  {
    HAL_UART_Transmit(&huart1, er, 1, 1000);
  }
  //16bit command_reg address
  data_write[0] = (0x00);
  data_write[1] = (COMMANDID_REG);
  //16bit module id of VID (0x0300) binary AND with Enable focus metric calculation (0x0D)
  data_write[2] = (0x03);
  data_write[3] = (0x0D);
  error = HAL_I2C_Master_Transmit(&hi2c1, LEPTON_ADDRESS, data_write, 4, 1000);
  HAL_Delay(1);
  if (error != 0)
  {
    HAL_UART_Transmit(&huart1, er, 1, 1000);
  }
}

void thresh()
{
  HAL_StatusTypeDef error;
  uint8_t er[1] = {'e'};
  uint8_t data_write[4];
  //16bit data_reg address
  data_write[0] = (0x00);
  data_write[1] = (DATA0);
  data_write[2] = (0x75);
  data_write[3] = (0x30);
  error = HAL_I2C_Master_Transmit(&hi2c1, LEPTON_ADDRESS, data_write, 4, 1000);
  HAL_Delay(1);
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
  HAL_Delay(1);
  if (error != 0)
  {
    HAL_UART_Transmit(&huart1, er, 1, 1000);
  }
  //16bit command_reg address
  data_write[0] = (0x00);
  data_write[1] = (COMMANDID_REG);
  //16bit module id of VID (0x0300) binary AND with focus metric threshold (0x15)
  data_write[2] = (0x03);
  data_write[3] = (0x15);
  error = HAL_I2C_Master_Transmit(&hi2c1, LEPTON_ADDRESS, data_write, 4, 1000);
  HAL_Delay(1);
  if (error != 0)
  {
    HAL_UART_Transmit(&huart1, er, 1, 1000);
  }
}


/* Private function prototypes -----------------------------------------------*/


int main(void)
{
  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();

  uint8_t packet[VOSPI_FRAME_SIZE*IMAGE_NUM_LINES];
  HAL_StatusTypeDef status;
  HAL_Delay(2000);
  uint32_t i = 0;
  uint32_t j = 0;
  uint32_t send_d[1] = {0};

  //read_reg(0x2);


  //metric_enable();
  //thresh();

  do {

	  //HAL_Delay(200);
  	      if ((status = HAL_SPI_Receive(&hspi1, packet, VOSPI_FRAME_SIZE,200)) != HAL_OK)
  	      {
  	    	 printf("error");
  	    	 //HAL_Delay(200);
  	      }
  	    } while ((packet[0] & 0x0f) == 0x0f);


	  /*lepton_command(VID, 0x18 >> 2 , GET);
	  j = read_metric_data();
	  lepton_command(VID, 0x18 >> 2 , GET);
	  i = read_metric_data();
	  if(i > j)//This check is done because uint32_t can't get a negative number
	  {
		  if((i-j) > 100)
		  {
			  send_d[0] = 's';
			  HAL_UART_Transmit(&huart1,(uint8_t*)send_d,1,1000);
		  }
	   }
	  else
	  {
		  if((j-i) > 100)
		  {
			  send_d[0] = 'n';
			  HAL_UART_Transmit(&huart1,(uint8_t*)send_d,1,1000);
		  }
	  }*/
  while (1)
  {
	  if (dma_done==1) {
		  dma_done=0;
		  HAL_SPI_Receive_DMA(&hspi1, packet , VOSPI_FRAME_SIZE);
	  }

  }


}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)//Happens at the end of RX transaction
{
	int send_d[1] = {'0'};
	uint8_t* data = hspi->pRxBuffPtr;
	int frame;
	frame=1;
	frame = data[0] & 0xf;
	uint8_t frame2 = data[1];

	if (frame2 == 1) {
		frame2=1;
	}
	if(frame != 0xf)
	{
		send_d[0] = frame;//everything is O.K.
		HAL_UART_Transmit(&huart1,(uint8_t*)send_d,1,1000);
	}
	else
	{
		send_d[0] = 'r';//need re-sync
		HAL_UART_Transmit(&huart1,(uint8_t*)send_d,1,1000);
	}

	  dma_done=1;

}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{

}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
