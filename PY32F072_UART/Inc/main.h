#ifndef __MAIN_H
#define __MAIN_H

#include "py32f0xx_hal.h"
#include "py32f002bxx_Start_Kit.h"

/* Global UART handle */
extern UART_HandleTypeDef UartHandle;

/* Fonksiyon prototipleri */
static void APP_GpioConfig_Led(GPIO_TypeDef *port, uint16_t pin);
static void APP_UARTConfig(USART_TypeDef *USARTx,
                    GPIO_TypeDef *tx_port, uint16_t tx_pin,
                    GPIO_TypeDef *rx_port, uint16_t rx_pin,
                    uint8_t alternate,
                    uint32_t baudrate);
static HAL_StatusTypeDef UART_SEND(uint8_t *pData, uint16_t Size);
static HAL_StatusTypeDef UART_RECEIVE(uint8_t *pData, uint16_t Size);

/* GPIO konfigürasyon */
static void APP_GpioConfig_Led(GPIO_TypeDef *port, uint16_t pin)
{
  if (port == GPIOB)
    __HAL_RCC_GPIOB_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(port, &GPIO_InitStruct);
}

/* UART konfigürasyon */
static void APP_UARTConfig(USART_TypeDef *USARTx,
                    GPIO_TypeDef *tx_port, uint16_t tx_pin,
                    GPIO_TypeDef *rx_port, uint16_t rx_pin,
                    uint8_t alternate,
                    uint32_t baudrate)
{
  if (USARTx == USART1)
    __HAL_RCC_USART1_CLK_ENABLE();

  if (tx_port == GPIOA)
    __HAL_RCC_GPIOA_CLK_ENABLE();
  if (rx_port == GPIOA)
    __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = tx_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = alternate;
  HAL_GPIO_Init(tx_port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = rx_pin;
  HAL_GPIO_Init(rx_port, &GPIO_InitStruct);

  UartHandle.Instance = USARTx;
  UartHandle.Init.BaudRate = baudrate;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits = UART_STOPBITS_1;
  UartHandle.Init.Parity = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&UartHandle);
}

/* UART gönderme */
static HAL_StatusTypeDef UART_SEND(uint8_t *pData, uint16_t Size)
{
  return HAL_UART_Transmit_IT(&UartHandle, pData, Size);
}

/* UART alma */
static HAL_StatusTypeDef UART_RECEIVE(uint8_t *pData, uint16_t Size)
{
  return HAL_UART_Receive_IT(&UartHandle, pData, Size);
}

#endif
