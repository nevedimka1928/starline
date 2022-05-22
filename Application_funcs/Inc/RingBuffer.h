#include <stdint.h>
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RINGBUFFER_H
#define __RINGBUFFER_H

#define SIZE_BUFFER 255

typedef struct 
{
  uint8_t buffer[SIZE_BUFFER];  // массив значений
  uint8_t InputItem;  // индекс элемента для нового значения
  uint16_t NumOfItems;  // число эл-тов
} volatile RingBuff_t;

/**
  * @brief  инициализация кольцевого буфера
  * @param  buff: указатель на структуру кольцевого буфера (КБ)
  * @retval значение резульата выполнения операции инициализации
  */
int8_t InitRB(RingBuff_t* buff);

/**
  * @brief  Добавление байта в буфер
  * @param  buff: указатель на структуру кольцевого буфера
  * @param  val: новое значение в КБ
  */
void PutRBValue(RingBuff_t* buff, uint8_t val);

/**
  * @brief  Извлечение байта из буфера
  * @param  buff: указатель на структуру кольцевого буфера
  * @retval значение, забираемое из КБ
  */
uint8_t GetRBValue(RingBuff_t* buff);

/**
  * @brief  Получение данных о количестве свободных байт в буфере
  * @param  buff: указатель на структуру кольцевого буфера
  * @retval число свободных эл-тов в КБ
  */
uint8_t NumOfRBFreeItems(RingBuff_t *buff);

/**
  * @brief  Получение данных о количестве байт в буфере
  * @param  buff: указатель на структуру кольцевого буфера
  * @retval число эл-тов в КБ
  */
uint8_t NumOfRBItems(RingBuff_t *buff);

/**
  * @brief  Заполнение кольцевого буфера на основе сгенерированного массива случайных чисел
  * @param  buff: указатель на структуру кольцевого буфера
  * @param  src: источник новых данных для КБ
  * @param  size: длина новых данных для КБ
  * @retval статус корректной работы ("-1" - ошибка, "1" - все хорошо)
  */
// 
int8_t FillRB(RingBuff_t* buff, uint8_t* src, uint8_t size);

#endif /* __RINGBUFFER_H */
