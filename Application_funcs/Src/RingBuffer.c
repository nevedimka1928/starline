#include "stm32f1xx_hal.h"
#include "RingBuffer.h"
#include <stdlib.h>

RingBuff_t* InitRB(int16_t capacity){
  if((capacity > 256) || (capacity < 1)) {return NULL;}
  
  uint8_t* start_mem = malloc(capacity * sizeof(uint8_t));
  if(start_mem == NULL) {return NULL;}
  
  RingBuff_t* new_RB = malloc(sizeof(RingBuff_t));
  if(new_RB == NULL){
    free(start_mem); 
    return NULL;
  }
  
  new_RB->InputItem = start_mem;
  new_RB->head = start_mem;
  new_RB->NumOfItems = 0;
  new_RB->length = capacity;
  return new_RB;
}

void deleteRingBuffer(RingBuff_t* buff){
  if(buff == NULL) return;
  free(buff->head);
  free(buff);
}

int8_t PutRBValue(RingBuff_t* buff, uint8_t val, volatile uint8_t* access){
  if(buff == NULL) return RB_ERR_NULL;
  while(*access == 0){}  // ожидание разрешения доступа к кольцевому буфферу (КБ)
  *access = 0;  // запрет доступа к КБ
  *(buff->InputItem) = val;  // запись нового значения в КБ
  buff->InputItem++;  // инкремент позиции
  if(buff->InputItem >= (buff->head + buff->length)){
    buff->InputItem = buff->head;  // установка позиции в 0, при выходе за пределы
  }
  if(buff->NumOfItems < buff->length){
    buff->NumOfItems++;  // инкремент кол-ва эл-тов
  }
  *access = 1;  // разрешение доступа к кольцевому буфферу (КБ)
  return RB_OK;
}

int8_t GetRBValue(RingBuff_t* buff, uint8_t* readed_val, volatile uint8_t* access){
  if(buff == NULL) return RB_ERR_NULL;
  if(buff->NumOfItems == 0) return RB_ERR_EMPTY;  // ошибка пустого буффера
  while(*access == 0){}  // ожидание разрешения доступа к кольцевому буфферу (КБ)
  *access = 0;  // запрет доступа к КБ
  uint8_t volatile* OutputItem = buff->InputItem;  // сохранение в переменную выходного индекса входного
  // сохранение номера искомого элемента
  OutputItem -= buff->NumOfItems;  // вычитание кол-ва эл-тов (отдельно из-за volatile)
  if(OutputItem < buff->head)  // если номер отрицательный
    OutputItem += buff->length;  // смена позиции на конец памяти КБ
  *readed_val = *OutputItem;  // чтение значения
  buff->NumOfItems--;  // декремент кол-ва эл-тов
  *access = 1;  // разрешение доступа к кольцевому буфферу (КБ)
  return RB_OK;
}

int8_t NumOfRBFreeItems(RingBuff_t *buff, uint8_t* readed_val){
  if(buff == NULL) return RB_ERR_NULL;
  *readed_val = buff->length - buff->NumOfItems;
  return RB_OK;
}

int8_t NumOfRBItems(RingBuff_t *buff, uint8_t* readed_val){
  if(buff == NULL) return RB_ERR_NULL;
  *readed_val = buff->NumOfItems;
  return RB_OK;
}

int8_t FillRB(RingBuff_t* buff, volatile uint8_t* src, volatile uint8_t size, volatile uint8_t* access){
  if(buff == NULL) return RB_ERR_NULL;
  if(src == NULL) return RB_ERR_NULL;
  if((size == 0) || (size > 50)) return RB_ERR_EXCEEDANCE;
  
  for(uint8_t i = 0; i < size; i++){
    if(PutRBValue(buff, src[i], access) != RB_OK)
      return RB_ERR_COPY;
  }
  return RB_OK;
}
