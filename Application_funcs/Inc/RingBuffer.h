#include <stdint.h>
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RINGBUFFER_H
#define __RINGBUFFER_H

#define SIZE_BUFFER 256

typedef struct 
{
  uint8_t buffer[SIZE_BUFFER];
  uint8_t InputItem;
  uint16_t NumOfItems;
} RingBuff_t;


void InitRB(RingBuff_t* buff);  // инициализация кольцевого буфера

void PutRBValue(RingBuff_t* buff, uint8_t val);  // Добавление байта в буфер 

int8_t GetRBValue(RingBuff_t* buff);  // Извлечение байта из буфера

// Получение данных о количестве свободных байт в буфере
uint8_t NumOfRBFreeItems(RingBuff_t *buff);

// Получение данных о количестве байт в буфере
uint8_t NumOfRBItems(RingBuff_t *buff);

// заполнение кольцевого буфера на основе сгенерированного массива случайных чисел
void FillRB(RingBuff_t* buff, uint8_t* src, uint8_t size);




#endif /* __RINGBUFFER_H */
