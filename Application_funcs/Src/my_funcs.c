#include "stm32f1xx_hal.h"
#include "my_funcs.h"

extern ADC_HandleTypeDef hadc1;
extern CRC_HandleTypeDef hcrc;
extern const uint32_t NumOfHouses;
uint8_t rand_buff[50];
uint8_t rand_time;
uint8_t rand_size;

/* static functions */

static uint32_t adc_noise(void){  // создание случайного числа на основе шума АЦП
//  while(HAL_ADC_PollForConversion (&hadc1, 10) == HAL_ERROR){}
  uint32_t noise = 0;
  for (uint8_t i = 0; i < 16; i++){  // заполнение 32 бит
    HAL_ADC_Start (&hadc1);  // запуск АЦП
    // сохранение по 2 младших бита от значения АЦП
    noise += (HAL_ADC_GetValue(&hadc1) & 0x00000003) << 2*i;
  }
  return noise;
}

static uint32_t rand_gen(void){        // преобразование шума АЦП в значение CRC
  uint32_t crc_data = adc_noise();
  uint32_t CRC_Value = HAL_CRC_Calculate(&hcrc, &crc_data, 1);  // рассчет CRC
  return CRC_Value;
}

static uint8_t conv256to50(uint8_t word){  // перевод числа от диапазона 0-255 в 1-50
  uint16_t tmp_word = (1 + (uint16_t)word)*50;
  if((tmp_word % 256) > 0)  // если есть остаток
    return ((uint8_t)((tmp_word / 256) + 1));  // вычислить и прибавить 1
  else
    return ((uint8_t)(tmp_word / 256));
}

/* included functions */

// создание случайного времени, размера буффера и заполнение первых 2х значений массива
void init_buff(void){
  uint32_t temp_rnd = rand_gen();
  rand_time = conv256to50((uint8_t)(temp_rnd & 0x000000FF));  // время
  rand_size = conv256to50((uint8_t)((temp_rnd & 0x0000FF00) >> 8));  // размер
  rand_buff[0] = (uint8_t)((temp_rnd & 0x00FF0000) >> 16);  // 0-й элемент
  rand_buff[1] = (uint8_t)((temp_rnd & 0xFF000000) >> 24);  // 1-й элемент
}

void fill_buff(uint8_t size){  // заполнение оставшейся части массива
  if(size <= 2) // если размер не больше уже заполненного
    return;     // не заполнять
  
  for (uint8_t i = 2; i < size; ++i){  // цикл по эл-там буфера
    static uint32_t temp_rnd;
//    temp_rnd = rand_gen();  // 
    uint8_t bites_shift = 8*((i - 2 + 4) % 4);  // сдвиг числа бит
    
    if((i + 2)%4 == 0)  // при остатке от деления равного 2
      temp_rnd = rand_gen();  // обновление случайного числа
    // заполнение эл-та массива в зависимости от его номера
    rand_buff[i] = (uint8_t)((temp_rnd >> bites_shift) & BYTE_MASK);
  }
}

uint32_t BinaryPower(uint8_t b, uint8_t e){  // возведение b в степень e
  uint32_t v = 1;
  while(e != 0) {
    if((e & 1) != 0) {
      v *= b;
    }
    b *= b;
    e >>= 1;
  }
  return v;
}

uint8_t Counter6Nums(uint8_t Y){
  if(Y == 0)
    return 0;
  uint32_t ret;
  ret = Y * BinaryPower(10, (Y-1));  // Количество цифр в числе = Y*(10**(Y-1))
  return ((ret >> 16) & 0x000000FF);  // возвращение "второго значимого байта"
}

