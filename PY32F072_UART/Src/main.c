#include "main.h"

/* Tanımlar */
#define UART_TX_BUFFER_SIZE 12
#define UART_RX_BUFFER_SIZE 12

/* Global değişkenler */
UART_HandleTypeDef UartHandle;
uint8_t uartTxBuffer[UART_TX_BUFFER_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
uint8_t uartRxBuffer[UART_RX_BUFFER_SIZE];
uint8_t newline[2] = {'\r', '\n'};

/* Ana program */
int main(void)
{
  HAL_Init();

  /* USART1 interrupt öncelik ve enable */
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);

  /* GPIO ve UART konfigürasyonları */
  APP_GpioConfig_Led(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
  APP_UARTConfig(USART1, GPIOA, GPIO_PIN_6, GPIOA, GPIO_PIN_7, GPIO_AF1_USART1, 115200);

  /* UART alımını başlat */
  UART_RECEIVE(uartRxBuffer, UART_RX_BUFFER_SIZE);

  while (1)
  {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    HAL_Delay(500);
   //UART_SEND(uartTxBuffer, UART_TX_BUFFER_SIZE);
    //UART_SEND(newline, 2);
  }
}

/* UART alım tamam callback */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    /* Son 3 byte kontrolü */
    if (uartRxBuffer[UART_RX_BUFFER_SIZE - 3] == 10 &&
        uartRxBuffer[UART_RX_BUFFER_SIZE - 2] == 11 &&
        uartRxBuffer[UART_RX_BUFFER_SIZE - 1] == 12)
    {
      for (int i = 0; i < 10; i++)
      {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
        HAL_Delay(200);
      }
    }

    /* Tekrar alım başlat */
    UART_RECEIVE(uartRxBuffer, UART_RX_BUFFER_SIZE);
  }
}


