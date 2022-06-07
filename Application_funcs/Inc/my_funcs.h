#include <stdint.h>
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MY_FUNCS_H
#define __MY_FUNCS_H

typedef struct 
{
  volatile uint8_t rand_buff[50];
  volatile uint8_t rand_time;
  volatile uint8_t rand_size;
} RandBuff_t;

/**
  * @brief  создание случайного времени, размера буффера и заполнение первых 2х значений массива
  * @param  random_struct: указатель на структуру RandBuff_t случайных значений
  * @param  hadc: указатель на структуру ADC
  * @param  hadc: указатель на структуру CRC
  */
void init_buff(RandBuff_t* random_struct, ADC_HandleTypeDef hadc, CRC_HandleTypeDef hcrc);

/**
  * @brief  заполнение оставшейся (от 2-го эл-та) части массива случайных данных
  * @param  random_struct: указатель на структуру RandBuff_t случайных значений
  * @param  hadc: указатель на структуру ADC
  * @param  hadc: указатель на структуру CRC
  */
void fill_buff(RandBuff_t* random_struct, ADC_HandleTypeDef hadc, CRC_HandleTypeDef hcrc);

/**
  * @brief  возведение в степень
  * @param  base: число, которое возводим в степень
  * @param  degree: степень, в которую возводим
  * @retval полученный результат
  */
uint32_t BinaryPower(uint32_t base, uint8_t degree);

/**
  * @brief  подсчёт шестерок
  * @param  Y: случайное число, которое по модулю меньше 10
  * @retval второй значимый байт числа, равного количеству шестерок
  */
uint8_t Counter6Nums(uint8_t Y);

#endif /* __MY_FUNCS_H */
