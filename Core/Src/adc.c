#include "adc.h"

void adc1_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    ADC1->CR1 &= ~ADC_CR1_RES;      // Độ phân giải 12-bit (giá trị 00)
    ADC1->CR1 &= ~ADC_CR1_SCAN;     // Tắt Scan mode (nếu chỉ dùng 1 kênh trong 1 sequence)

    // ADC Control Register 2 (ADC1->CR2)
    ADC1->CR2 &= ~ADC_CR2_ALIGN;    // Dữ liệu căn phải (Right alignment)
    ADC1->CR2 &= ~ADC_CR2_CONT;     // Single conversion mode (không phải continuous)
    ADC1->CR2 &= ~ADC_CR2_EXTSEL;   // Chọn software trigger (SWSTART)
    ADC1->CR2 &= ~ADC_CR2_EXTEN;    // Trigger bằng software

    // ADC Sample time register (ADC1->SMPR1 và ADC1->SMPR2)
    // Cho kênh 10 (PC0 = ADC1_IN10), nằm trong SMPR1
    // SMPR1_SMP10[2:0] bits. Ví dụ: 001 = 15 cycles, 010 = 28 cycles, 011 = 56 cycles
    // Chọn sampling time phù hợp, ví dụ 56 cycles (011)
    ADC1->SMPR1 &= ~(ADC_SMPR1_SMP10); // Xóa các bit cũ
    ADC1->SMPR1 |= (ADC_SMPR1_SMP10_0 | ADC_SMPR1_SMP10_1); // 56 cycles (011b)

    // ADC regular sequence register (ADC1->SQRx)
    // Chỉ dùng 1 kênh trong sequence -> L[3:0] = 0000 in ADC1->SQR1
    ADC1->SQR1 &= ~ADC_SQR1_L;      // Sequence length = 1 conversion

    // Đặt kênh 10 (PC0) làm kênh đầu tiên trong sequence
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;    // Xóa SQ1 bits
    ADC1->SQR3 |= (10UL << 0);      // Gán channel 10 cho SQ1 (SQ1_0 ... SQ1_4)

    // 2. Bật ADC
    ADC1->CR2 |= ADC_CR2_ADON;

    for(volatile int i=0; i<1000; i++); // Delay nhỏ
}

// Đọc giá trị từ một kênh ADC cụ thể của ADC1
uint16_t adc1_read_channel(uint8_t channel) {

    // 1. Bắt đầu chuyển đổi ADC
    ADC1->CR2 |= ADC_CR2_SWSTART;

    // 2. Đợi cho đến khi cờ EOC (End Of Conversion) được bật
    while (!(ADC1->SR & ADC_SR_EOC));

    // 3. Đọc giá trị từ thanh ghi dữ liệu ADC1->DR
    // Việc đọc ADC1->DR cũng sẽ tự động xóa cờ EOC.
    return (ADC1->DR & 0xFFF); // Trả về giá trị 12-bit
}
