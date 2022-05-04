#include <stdint.h>
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MY_FUNCS_H
#define __MY_FUNCS_H

#define BYTE_MASK       0x000000FF

void init_buff(void);  // инициализация буффера случайных чисел

void fill_buff(uint8_t size);  // заполнение оставшейся части массива

uint32_t BinaryPower(uint8_t b, uint8_t e);   // возведение в степень

uint8_t Counter6Nums(uint8_t Y);    // подсчёт шестерок

#endif /* __MY_FUNCS_H */
