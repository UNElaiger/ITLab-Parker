/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "esp_01.h"
//#include "Setings.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SPEED_1      TIM3->CCR1//5 
#define DIR_1        GPIOB,GPIO_PIN_5//4
 
#define SPEED_2      TIM2->CCR3//6
#define DIR_2        GPIOA,GPIO_PIN_8//7

#define RX_BUF_MASK 1024-1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void clear_rx_buf(void);
uint8_t check_answer(char *str,uint16_t wait);
void usart1_send_string(const char str[]);
void usart2_send_string(const char str[]);
void esp_Start2(void);
void ESP_AP_START(void);
void esp_Start(void);
void close_conections(void);
void usart1_reciv_string(void);
void recive(void);
void clear_Mess(void);
void MOVE(void);
void Start(void);

//-------------motor-------------
void forward(void);
void back(void);
void left(void);
void right(void);
void tank_left(void);
void tank_right(void);
void stop(void);
//-------------motor-------------
void parse_PAGE(void);
char AP_or_ST[] = "AP";// station - ST, access poin == AP
char *p1 = NULL,*p2 = NULL,*p3 = NULL,*p4 = NULL;
char apName[40]="";
char apPass[40]="";
char ipServer[40]="";
char typeAPorST[40]="";
bool flag_for_page =true;
const char acsessPoint[20]="Mi 9T Pro";
const char acsessPass[20]="qwertyuiop223";
const char serverIp [15]= "192.168.43.76";
const char conn_TCP2 []= "AT+CIPSTART=\"TCP\",\"192.168.43.76\",9076\r\n";

bool RC = true;// Kostil na vremja
uint16_t motor_speed = 65535;
uint32_t speed;

//void recive(void);
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))
#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA           0x01000000

struct __FILE { int handle;};
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
   if (DEMCR & TRCENA) {

while (ITM_Port32(0) == 0){};
    ITM_Port8(0) = ch;
  }
  return(ch);
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char test[] = "AT\r\n";
char sendbuf[50];
char rx_buf[1024]="";
volatile uint16_t rx_pos=0;

//const char conn_TCP2 []= "AT+CIPSTART=\"TCP\",\"192.168.8.100\",9076\r\n";
const uint16_t serverPort = 9076;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//=================================SETTINGS======================================//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

char mess[50]="";

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
 /* USER CODE BEGIN WHILE */
	uint8_t step=0;
	char str[] = "";
	char send[]="";
	//char test_string []= " hello";
	
__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);// start PWM
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);// start PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);// start PWM
//esp_Start();
//
uint32_t foto = 0;
sprintf(str,"%s%s","\r\nINIT FINISHED","\r\n");
usart2_send_string(str);
Start();






///////////////////////////////////////////////////////////////////ACCESS POINT/////////////////////////////////////////////////////////////////////////
/*
else if (strncmp(AP_or_ST, "AP", strlen(AP_or_ST))==0)// Start like Access Point 
{

	
	
if(setting_ap == true)// configuring the robot via the browser
	{
	
	}
if (remote_control == true)
	{
		usart2_send_string("remote controll");
		usart2_send_string("Access point ip: ");
		//usart1_send_string(chek_ip);
		clear_rx_buf();
		while(1)
			{
				usart2_send_string(rx_buf);
				//clear_rx_buf();
				HAL_Delay(1000);
			}			
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////ACCESS POINT
*/




//--------------------------------------- MOTOR TEST---------------------------------------------
	/*
	while(1)
		{
			
			usart2_send_string("Motor test 1\r\n");
			//motor 1
		  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET);
			//motor 2
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);
			usart2_send_string("Motor test 2\r\n");
			HAL_Delay(1000);
			//motor 1
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET);
			//motor 2
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET);
			usart2_send_string("Motor test 3\r\n");
			HAL_Delay(1000);
			//motor 1
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET);
			//motor 2
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);
			HAL_Delay(1000);
			*/
			/*
			
			//motor 1
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET);
			//motor 2
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);
			
			HAL_Delay(1000);
			
		};
		

		*/
//--------------------------------------- MOTOR TEST---------------------------------------------
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, INC_Pin|IND_Pin|INA_Pin|INB_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|H2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(H1_GPIO_Port, H1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : INC_Pin IND_Pin INA_Pin INB_Pin */
  GPIO_InitStruct.Pin = INC_Pin|IND_Pin|INA_Pin|INB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin H2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|H2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LDPIN_Pin */
  GPIO_InitStruct.Pin = LDPIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(LDPIN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : H1_Pin */
  GPIO_InitStruct.Pin = H1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(H1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void USART1_IRQHandler(void){
    unsigned char rx_b;    
    if (USART1->SR & USART_SR_RXNE) 
	{     
		    rx_b = USART1->DR;
		    rx_buf[rx_pos++]=rx_b;//extern
	     	rx_pos &= RX_BUF_MASK;
		   	printf("%c",rx_b);
	}
      rx_buf[rx_pos+1]='\0';
}

void clear_rx_buf(void){
 for(;rx_pos!=0;rx_pos--)
		rx_buf[rx_pos]='\0';
	rx_pos=0;
	//usart2_send_string("Buff clear");
}

void clear_Mess(void){
 for(uint16_t i = 0;i < 50;i++)
	mess[i]='\0';
	//rx_pos=0;
}
void usart1_send_string(const char str[]){
HAL_UART_Transmit(&huart1,(uint8_t*)str,strlen(str),100);
}

void usart2_send_string(const char str[]){
HAL_UART_Transmit(&huart2,(uint8_t*)str,strlen(str),100);
}

void usart1_reciv_string(){
HAL_UART_Receive_IT(&huart1,(uint8_t*)rx_buf,1024);
//HAL_UART_Transmit(&huart1,(uint8_t*)str,strlen(str),100);
}

void back(void)
{
HAL_GPIO_WritePin(DIR_1,GPIO_PIN_SET);
HAL_GPIO_WritePin(DIR_2,GPIO_PIN_SET);
SPEED_2 = SPEED_1 = motor_speed;
usart2_send_string("Back\r\n");
};
void forward(void)
{
HAL_GPIO_WritePin(DIR_1,GPIO_PIN_RESET);
HAL_GPIO_WritePin(DIR_2,GPIO_PIN_RESET);
SPEED_2 = SPEED_1 = motor_speed;
usart2_send_string("Forward\r\n");
};
void right(void)
{
HAL_GPIO_WritePin(DIR_1,GPIO_PIN_SET);
HAL_GPIO_WritePin(DIR_2,GPIO_PIN_RESET);
SPEED_2 = SPEED_1 = motor_speed;
usart2_send_string("Right\r\n");
};
void left(void)
{
HAL_GPIO_WritePin(DIR_1,GPIO_PIN_RESET);
HAL_GPIO_WritePin(DIR_2,GPIO_PIN_SET);
SPEED_2 = SPEED_1 = motor_speed;
usart2_send_string("Left \r\n");
};
void tank_left(void)
{
HAL_GPIO_WritePin(DIR_1,GPIO_PIN_SET);
SPEED_1 = motor_speed;
SPEED_2 = 0; 
usart2_send_string("Tank Left\r\n");
};
void tank_right(void)
{
HAL_GPIO_WritePin(DIR_2,GPIO_PIN_SET);
SPEED_1 = 0;
SPEED_2 = motor_speed; 
usart2_send_string("Tank Right\r\n");
};

void stop(void)
{
HAL_GPIO_WritePin(DIR_1,GPIO_PIN_SET);
HAL_GPIO_WritePin(DIR_2,GPIO_PIN_SET);
SPEED_1 = 0;
SPEED_2 = 0; 
usart2_send_string("Stop\r\n");
};
void MOVE()
{
//if(check_answer("f",100))
clear_rx_buf();
if(strstr(rx_buf,"b"))
			{
				while(1)
					{
						back();
						if(strstr(rx_buf,"z"))
							{
								stop();
								break;
							}
					}
					clear_rx_buf();
			}

	//else if(check_answer("b",100))
		else if(strstr(rx_buf,"f"))
			{
				while(1)
					{
						forward();
						if(strstr(rx_buf,"z"))
							{
								stop();
								break;
							}
					}
					clear_rx_buf();
			}
	//else if(check_answer("r",100))
		else if(strstr(rx_buf,"r"))
			{
				while(1)
					{
						right();
						if(strstr(rx_buf,"z"))
							{
								stop();
								break;
							}					
					}
					clear_rx_buf();
			}
	//else if(check_answer("l",100))
		else if(strstr(rx_buf,"l"))
			{
				while(1)
					{
						left();
						if(strstr(rx_buf,"z"))
							{
								stop();
								break;
							}
					}
					clear_rx_buf();
			}
	//else if(check_answer("TL",100))
		else if(strstr(rx_buf,"q"))
			{
				while(1)
					{
						tank_left();
						if(strstr(rx_buf,"z"))
							{
								stop();
								break;
							}
					}
					clear_rx_buf();
			}
			
//else if(check_answer("TR",100))
	else if(strstr(rx_buf,"e"))
			{
				while(1)
					{
						tank_right();
						if(strstr(rx_buf,"z"))
							{
								stop();
								break;
							}
					}
					clear_rx_buf();
			}
}

uint8_t check_answer(char *str,uint16_t wait){
uint32_t time_Ms_Now = HAL_GetTick();
char *istr = NULL;
	while(istr==NULL && ((HAL_GetTick()-time_Ms_Now)< wait)){
			istr=strstr(rx_buf,str);
		} 
		if(istr!=NULL){
			
			if (strncmp(AP_or_ST, "ST", strlen(AP_or_ST))==0)clear_rx_buf();
			return 1;	
		}else return 0;
}
//---------------------------------------------ESP START LIKE AP---------------------------------------------------------
	void ESP_AP_START(void){
uint8_t step=0;
while(1){
	
	switch(step){
		 case(0):	
			usart2_send_string("send_string(at_test)\r\n");
		 usart1_send_string(at_test);
			if (check_answer("OK",1000))step++;	
		break;
		case(1):
			usart2_send_string("send_string(echoOff)\r\n");
			usart1_send_string(echoOff);
			if (check_answer("OK",1000))
				step++;
		break;
		case(2):
			usart2_send_string("send_string(multip_Conn)\r\n");
			usart1_send_string(multip_Conn);
			if (check_answer("OK",3000))
				step++;
		break;
		case(3):	
			usart2_send_string("send_string(esp_Mode)\r\n");	
			usart1_send_string(esp_Mode_AP);
			if (check_answer("OK",3000))
				step++;
		break;		
		case(4):	
			//usart2_send_string("send_string(restart)\r\n");
			//usart1_send_string(restart);
		  HAL_Delay(2500);
      //clear_rx_buf();
      step++;
		break;
		case(5):
			usart2_send_string("send_string(start_AP)\r\n");	
			usart1_send_string(start_AP);
			if (check_answer("OK",3000))
				step++;
		case(6):
			usart2_send_string("send_string(start_Server)\r\n");	
			usart1_send_string(start_Server);
			if (check_answer("OK",3000))
				step++;
		case(7):
			usart2_send_string("send_string(get_IP)\r\n");	
			usart1_send_string(get_IP);
			if (check_answer("+CIFSR:",5000))
				step++;
			
	}
if (step==8)
	{
		usart2_send_string("Access point is ready\r\n");	
		break;
	}
	HAL_Delay(200);
 }
}
//---------------------------------------------ESP START LIKE AP---------------------------------------------------------

//---------------------------------------------PARSE_PAGE----------------------------------------------------------------
void parse_PAGE(void)
{
int size_str=sizeof("apName");
p1=strstr(rx_buf,"apName=");
p2=strstr(rx_buf,"apPass=");
p3=strstr(rx_buf,"apIP=");
p4=strstr(rx_buf,"type=");
//p3=strstr(rx_buf,"ip=");
int i=0;
while(p1[size_str]!='&')
{
    apName[i] = p1[size_str];
    i++;
    size_str++;
}

usart2_send_string("AP settings:\r\n");
						
usart2_send_string("BSSID: ");
usart2_send_string(apName);


size_str = sizeof("apPass");
i=0;
while(p2[size_str]!='&') // while(p2[size_str]!=' ')
{
    apPass[i] = p2[size_str];
    i++;
    size_str++;
}

usart2_send_string("\r\n");
usart2_send_string("PASSWORD: ");
usart2_send_string(apPass);
usart2_send_string("\r\n");
i=0;
size_str = sizeof("apIP");
while(p3[size_str]!='&')
{
   ipServer[i] = p3[size_str];
    i++;
    size_str++;
}

usart2_send_string("IP: ");
usart2_send_string(ipServer);
usart2_send_string("\r\n");

i=0;
size_str = sizeof("type");
while(p4[size_str]!=' ')
{
   typeAPorST[i] = p4[size_str];
    i++;
    size_str++;
}
usart2_send_string("TYPE: ");
usart2_send_string(typeAPorST);
usart2_send_string("\r\n");
usart2_send_string(rx_buf);
usart2_send_string("============\r\n");
clear_rx_buf();




}
//---------------------------------------------PARSE_PAGE----------------------------------------------------------------


//===========================close all conection=================================//
void close_conections(void){
int NUMconnect =4;	
  while(NUMconnect!=0){
		 HAL_Delay(50);
	   usart1_send_string(close_All_Connections[NUMconnect--]);
   }
	usart2_send_string("ALL CONNECTION CLOSE");
}
//===========================close all conection=================================//

//---------------------------------------------ESP START LIKE STANTION---------------------------------------------------------
void esp_Start2(void){
//usart1_send_string(restart);
uint8_t step=0;

while(1){
	
	switch(step){
		 case(0):	
			usart2_send_string("send_string(at_test)\r\n");
		 usart1_send_string(at_test);
			if (check_answer("OK",1000))step++;	
		break;
		case(1):
			usart2_send_string("send_string(echoOff)\r\n");
			usart1_send_string(echoOff);
			if (check_answer("OK",1000))step++;
		break;
		case(2):
			usart2_send_string("send_string(station_mode)\r\n");
			usart1_send_string(station_mode);
			if (check_answer("OK",1000))step++;
		break;
		case(3):	
		usart2_send_string("send_string(restart)\r\n");
			usart1_send_string(restart);
		  HAL_Delay(2500);
      clear_rx_buf();
      step++;
		break;
		case(4):
			usart2_send_string("send_string(conect_to_AP)\r\n");	
			sprintf(sendbuf,"%s%s%s%s%s","AT+CWJAP=\"",acsessPoint,"\",\"",acsessPass,"\"\r\n");
		  usart1_send_string(sendbuf);
			if (check_answer("OK",10000))
			step++;
		break;
		case(5):			
			usart2_send_string("send_string(conect_to_AP_ststus)\r\n");	
			usart1_send_string(conect_AP_status);
		  if (check_answer("OK",5000))step++;
		break;
		case(6):
			usart2_send_string("send_string(get_IP)\r\n");
			usart1_send_string(get_IP);
		  if (check_answer("OK",1000))step++;
		break;
		case(7):
			usart2_send_string("NoMultConn\r\n");
			usart1_send_string(NoMultConn);
		  if (check_answer("OK",1000))step++;
		break;
		case(8):
			usart2_send_string("connect to server\r\n");	
		  usart1_send_string(conn_TCP2);          // connect to server
		  if (check_answer("CONNECT",3000))
					step++;
		break;
			case(9):
				usart2_send_string("info about connect:\r\n");
				usart1_send_string(info);          // connect to server
			HAL_UART_Transmit(&huart2,(uint8_t*)rx_buf,strlen(rx_buf),1000);
		  if (check_answer("OK",1000))
				{
					step++;
				}
		break;
	}
if (step==10)break;
	HAL_Delay(200);
 }
}
//---------------------------------------------ESP START LIKE STANTION---------------------------------------------------------

	void esp_Start(void){
			
			usart2_send_string("send_string(at_test)\r\n");
		 usart1_send_string(at_test);
			usart2_send_string("send_string(echoOff)\r\n");
			usart1_send_string(echoOff);
			usart2_send_string("send_string(station_mode)\r\n");
			usart1_send_string(station_mode);
		usart2_send_string("send_string(restart)\r\n");
			usart1_send_string(restart);
		  HAL_Delay(2500);
      clear_rx_buf();
			usart2_send_string("send_string(conect_to_AP)\r\n");	
			sprintf(sendbuf,"%s%s%s%s%s","AT+CWJAP=\"",acsessPoint,"\",\"",acsessPass,"\"\r\n");
		  usart1_send_string(sendbuf);		
			usart2_send_string("send_string(conect_to_AP_ststus)\r\n");	
			usart1_send_string(conect_AP_status);
			usart2_send_string("send_string(get_IP)\r\n");
			usart1_send_string(get_IP);
			usart2_send_string("NoMultConn\r\n");
			usart1_send_string(NoMultConn);
			usart2_send_string("connect to server\r\n");	
		  usart1_send_string(conn_TCP2);          // connect to server
				usart2_send_string("info about connect:\r\n");
				usart1_send_string(info);          // connect to server
			HAL_UART_Transmit(&huart2,(uint8_t*)rx_buf,strlen(rx_buf),1000);

}
void Start(void)
{
char str[] = "";
char send[]="";
char CHIP[] = "";
//HAL_Delay(5000);
usart2_send_string("send_string(restart)\r\n");
usart1_send_string(restart);
HAL_Delay(2500);
clear_rx_buf();
usart2_send_string("Start INIT\r\n");	
ESP_AP_START(); // start like Access point
if (RC!=true)
	{
			while(1) // start WEB page
		{
			//usart2_send_string(rx_buf);
			if(check_answer("GET / HTTP/1.1",100) && flag_for_page==true)
				{
					//usart2_send_string(send_buf);
					sprintf(CHIP,"%s%d%c%d%s","AT+CIPSEND=",0,',',strlen(text),"\r\n");
					usart2_send_string(CHIP);
					usart1_send_string(CHIP);
					HAL_Delay(50);
					if(check_answer(">",500))
						{
							//clear_rx_buf();
							//usart2_send_string("Second CP\r\n");
							clear_rx_buf();
							usart1_send_string(text);
							HAL_Delay(50);
							if(check_answer("OK", 1000))
								{
									HAL_Delay(50);
									//usart2_send_string(rx_buf);
									clear_rx_buf();								
									flag_for_page=false;
								}
						}//close_conections();
						
			//usart1_send_string(close_conn);
				}
			else if(check_answer("GET /AP?",100)==1 && flag_for_page==false)
				{
					flag_for_page=true;
					// usart2_send_string("SUBMIT eeeeeeeeeeeee");
					usart2_send_string("\r\n");
					usart2_send_string(rx_buf);
					usart2_send_string("\r\n");
					parse_PAGE();
					//usart2_send_string(p2);
					//close_conections();
					clear_rx_buf();
					HAL_Delay(50);
					break;
				}
			//usart2_send_string(rx_buf);
		}	
	usart2_send_string(rx_buf);
	usart2_send_string("okey");



	}	
if (strstr(typeAPorST,"ST"))// start like Statione and connect to server
		{
      ///////////////////////////////////////////////////////////////////STATION/////////////////////////////////////////////////////////////////////////
      //HAL_UART_Transmit(&huart2,(uint8_t*)str,strlen(str),1000);
			usart2_send_string("ST starting\r\n");	
			esp_Start2(); // start like stantion
			char send_[]="im STM";
			char *tok;
			char mess[50]="";
			uint16_t some_data = 777;
			uint8_t Flag= 1;

			while (1)
				{
					if(Flag==1)// first message for connect
						{
							sprintf(mess,"%s%c",send_,'\0');
							if(DEBUG)printf("adc_value = %s\r\n", mess);
							if(DEBUG)printf("send_TSP_sizeof_message\r\n");	
							sprintf(sendbuf,"%s%d%s%c",send_TSP,strlen(mess),"\r\n",'\0');
							usart1_send_string(sendbuf);
							HAL_Delay(50);	
							if(DEBUG)printf("send_TSP_message\r\n");
							usart1_send_string(mess);
							if(DEBUG)usart2_send_string(rx_buf);
							clear_Mess();
							if(check_answer("SEND OK",2000))
								{
									Flag=0;
									usart2_send_string("send END\r\n");
								}
						}
					 sprintf(mess,"%d%c",some_data,'\0');
					 if(DEBUG)printf("adc_value = %s\r\n", mess);
					 if(DEBUG)printf("send_TSP_sizeof_message\r\n");	
					 sprintf(sendbuf,"%s%d%s%c",send_TSP,strlen(mess),"\r\n",'\0');
					 usart1_send_string(sendbuf);
					 HAL_Delay(50);	
           usart1_send_string(mess);
					 MOVE();						

			
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
				}
         ///////////////////////////////////////////////////////////////////STATION/////////////////////////////////////////////////////////////////////////
}
		
else if (strstr(typeAPorST,"AP") || RC == true)// start like Statione and connect to server
		{
			usart2_send_string("AP starting\r\n");
			ESP_AP_START();
			while(1)
				{
					MOVE();
				}
			//usart2_send_string("AP starting\r\n");	
			//ESP_AP_START(); // start like Access point
			//sprintf(str,"%s%s","\r\nAP is enabled","\r\n");
			//HAL_UART_Transmit(&huart2,(uint8_t*)str,strlen(str),1000);
			//usart2_send_string("Chek HTML\r\n");
			//bool exit_from_chek_IP = false;
			//bool setting_ap = true ;// configuring the robot via the browser
			//bool remote_control = false;
			//int count = 0;
			//char html[] = "";
			//char CHIP[] = "";
			//char send_buf[] ="";
			//usart2_send_string(rx_buf);
		}
	}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
