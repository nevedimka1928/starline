#include "stm32f1xx_hal.h"
#include "RingBuffer.h"


void InitRB(RingBuff_t* buff){
  buff->InputItem = 0;
  buff->NumOfItems = 0;
}

void PutRBValue(RingBuff_t* buff, uint8_t val){
  buff->buffer[buff->InputItem] = val;
  buff->InputItem++;
  buff->NumOfItems++;
  if(buff->NumOfItems > SIZE_BUFFER)
    buff->NumOfItems = SIZE_BUFFER;
}

int8_t GetRBValue(RingBuff_t* buff){
  uint8_t val;
  int16_t OutputItem;
  // сохранение номера искомого элемента
  OutputItem = buff->InputItem - buff->NumOfItems;
  if(OutputItem < 0)  // если номер отрицательный
    OutputItem += SIZE_BUFFER;
  val = buff->buffer[OutputItem];
  buff->NumOfItems--;
  return val;
}

uint8_t NumOfRBFreeItems(RingBuff_t *buff){
  return (SIZE_BUFFER - buff->NumOfItems);
}

uint8_t NumOfRBItems(RingBuff_t *buff){
  return (buff->NumOfItems);
}

void FillRB(RingBuff_t* buff, uint8_t* src, uint8_t size){
  for(uint8_t i = 0; i < size; i++){
    PutRBValue(buff, src[i]);
  }
}



