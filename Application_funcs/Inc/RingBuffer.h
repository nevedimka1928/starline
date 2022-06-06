#include <stdint.h>
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RINGBUFFER_H
#define __RINGBUFFER_H

typedef struct 
{
  int16_t length;  // длина выделяемой памяти
  uint8_t* head;  // указатель на начало массива значений
  volatile uint8_t* InputItem;  // указатель на элемент для нового значения
  volatile uint16_t NumOfItems;  // число эл-тов
} RingBuff_t;

enum RB_ERRORS { 
    RB_OK = 1,
    RB_ERR_NULL  = -1,  // некорректные аргументы-указатели
    RB_ERR_EMPTY = -2,  // пустой буффер
    RB_ERR_EXCEEDANCE = -3,     // выход аргумента за допустимые пределы
    RB_ERR_COPY = -4    // ошибка копирования данных
};

/**
  * @brief  инициализация кольцевого буфера
  * @param  capacity: длина кольцевого буфера (КБ)
  * @retval указатель на структуру объекта кольцевого буфера
  */
RingBuff_t* InitRB(int16_t capacity);

/**
  * @brief  удаление динамической памяти кольцевого буфера
  * @param  buff: указатель на структуру кольцевого буфера (КБ)
  */
void deleteRingBuffer(RingBuff_t* buff);

/**
  * @brief  Добавление байта в буфер
  * @param  buff: указатель на структуру кольцевого буфера
  * @param  val: новое значение в КБ
  * @retval статус выполнения функции
  */
int8_t PutRBValue(RingBuff_t* buff, uint8_t val);

/**
  * @brief  Извлечение байта из буфера
  * @param  buff: указатель на структуру кольцевого буфера
  * @param  readed_val: возвращаемое значение
  * @retval статус выполнения функции
  */
int8_t GetRBValue(RingBuff_t* buff, uint8_t* readed_val);

/**
  * @brief  Получение данных о количестве свободных байт в буфере
  * @param  buff: указатель на структуру кольцевого буфера
  * @param  readed_val: возвращаемое значение
  * @retval статус выполнения функции
  */
int8_t NumOfRBFreeItems(RingBuff_t *buff, uint8_t* readed_val);

/**
  * @brief  Получение данных о количестве байт в буфере
  * @param  buff: указатель на структуру кольцевого буфера
  * @param  readed_val: возвращаемое значение
  * @retval статус выполнения функции
  */
int8_t NumOfRBItems(RingBuff_t *buff, uint8_t* readed_val);

/**
  * @brief  Заполнение кольцевого буфера на основе сгенерированного массива случайных чисел
  * @param  buff: указатель на структуру кольцевого буфера
  * @param  src: источник новых данных для КБ
  * @param  size: длина новых данных для КБ
  * @retval статус корректной работы
  */
// 
int8_t FillRB(RingBuff_t* buff, uint8_t* src, uint8_t size);

#endif /* __RINGBUFFER_H */
