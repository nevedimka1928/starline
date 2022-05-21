#include <stdint.h>
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MY_FUNCS_H
#define __MY_FUNCS_H


/**
  * @brief  создание случайного времени, размера буффера и заполнение первых 2х значений массива
  */
void init_buff(void);

/**
  * @brief  заполнение оставшейся (от 2-го эл-та) части массива случайных данных
  * @param  size: общее число случайных значений
  */
void fill_buff(uint8_t size);

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
