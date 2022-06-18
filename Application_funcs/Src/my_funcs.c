#include "stm32f1xx_hal.h"
#include "my_funcs.h"

volatile uint8_t rand_buff[50];
volatile uint8_t rand_time;
volatile uint8_t rand_size;

/* Private function prototypes -----------------------------------------------*/
static uint32_t adc_noise(ADC_HandleTypeDef hadc);
static uint32_t rand_gen(ADC_HandleTypeDef hadc, CRC_HandleTypeDef hcrc);
static uint8_t conv256to50(uint8_t word);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  создание случайного числа на основе шума АЦП
  * @param  hadc: указатель на структуру ADC
  * @retval 32-битное случайное число шума АЦП
  */
static uint32_t adc_noise(ADC_HandleTypeDef hadc){
  while(HAL_ADC_PollForConversion (&hadc, 10) == HAL_ERROR){}  // ожидание окончания преобразования
  uint32_t noise = 0;
  for (uint8_t i = 0; i < 16; i++){  // заполнение 32 бит
    HAL_ADC_Start (&hadc);  // запуск АЦП
    // сохранение по 2 младших бита от значения АЦП
    noise += (HAL_ADC_GetValue(&hadc) & 0x00000003) << 2*i;
  }
  return noise;
}

/**
  * @brief  преобразование шума АЦП в значение CRC
  * @param  hadc: указатель на структуру ADC
  * @param  hadc: указатель на структуру CRC
  * @retval 32-битное CRC шума АЦП
  */
static uint32_t rand_gen(ADC_HandleTypeDef hadc, CRC_HandleTypeDef hcrc){
  uint32_t crc_data = adc_noise(hadc);
  uint32_t CRC_Value = HAL_CRC_Calculate(&hcrc, &crc_data, 1);  // рассчет CRC
  return CRC_Value;
}

/**
  * @brief  перевод числа от диапазона 0-255 в 1-50
  * @param  word: число из диапазона 0-255
  * @retval число из диапазона 1-50
  */
static uint8_t conv256to50(uint8_t word){  // перевод числа от диапазона 0-255 в 1-50
  uint16_t tmp_word = (1 + (uint16_t)word)*50;
  if((tmp_word % 256) > 0){  // если есть остаток
    return ((uint8_t)((tmp_word / 256) + 1));  // вычислить и прибавить 1
  }
  else{
    return ((uint8_t)(tmp_word / 256));
  }
}

/* Exported functions --------------------------------------------------------*/

void init_buff(RandBuff_t* random_struct, ADC_HandleTypeDef hadc, CRC_HandleTypeDef hcrc){
  uint32_t temp_rnd = rand_gen(hadc, hcrc);
  random_struct->rand_time = conv256to50(*((uint8_t*)&temp_rnd));  // время
  random_struct->rand_size = conv256to50(*((uint8_t*)&temp_rnd + 1));  // размер
  random_struct->rand_buff[0] = *((uint8_t*)&temp_rnd + 2);  // 0-й элемент
  random_struct->rand_buff[1] = *((uint8_t*)&temp_rnd + 3);  // 1-й элемент
}

void fill_buff(RandBuff_t* random_struct, ADC_HandleTypeDef hadc, CRC_HandleTypeDef hcrc){
  if(random_struct->rand_size <= 2){ // если размер не больше уже заполненного
    return;     // не заполнять
  }
  for (uint8_t i = 2; i < random_struct->rand_size; ++i){  // цикл по эл-там буфера
    static uint32_t temp_rnd;
    if((i + 2)%4 == 0){  // при остатке от деления (смещённого на 2 индекса) равного 0
      temp_rnd = rand_gen(hadc, hcrc);  // обновление случайного числа
    }
    // заполнение эл-та массива в зависимости от его номера
    random_struct->rand_buff[i] = *((uint8_t*)&temp_rnd + ((i + 2) % 4));
  }
}

uint32_t BinaryPower(uint32_t base, uint8_t degree){
  uint32_t val = 1;
  while(degree != 0) {
    if((degree & 1) != 0) {
      val *= base;
    }
    base *= base;
    degree >>= 1;
  }
  return val;
}

uint8_t Counter6Nums(uint8_t Y){
  if(Y == 0){
    return 0;
  }
  uint32_t ret;
  ret = Y * BinaryPower(10, (Y-1));  // Количество цифр в числе = Y*(10**(Y-1))
  return (*((uint8_t*)&ret + 2));  // возвращение "второго значимого байта"
}


