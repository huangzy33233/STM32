#include "spi.h"

void Init_SPI0(void)
{
    spi_parameter_struct spi_init_struct;

    //GPIO时钟配置
    rcu_periph_clock_enable(RCU_GPIOA);

    //SPI时钟配置
    rcu_periph_clock_enable(RCU_SPI0);

    //GPIO复用模式设置
    gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_5 | GPIO_PIN_7);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5 | GPIO_PIN_7);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5 | GPIO_PIN_7);

    //复位SPI0
    spi_i2s_deinit(SPI0);

    //初始化SPI参数结构体
    spi_struct_para_init(&spi_init_struct);

    spi_init_struct.trans_mode           = SPI_TRANSMODE_BDTRANSMIT;    //发送模式
    spi_init_struct.device_mode          = SPI_MASTER;                  //SPI主机模式
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;          //8位数据宽度
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;     //空闲高电平，第二个时钟沿捕获
    spi_init_struct.nss                  = SPI_NSS_SOFT;                //软件NSS
    spi_init_struct.prescale             = SPI_PSC_32;                  //32分频
    spi_init_struct.endian               = SPI_ENDIAN_MSB;              //高位先传输
    spi_init(SPI0, &spi_init_struct);

    //使能SPI0
    spi_enable(SPI0);
}

void SPI0_Write(uint8_t data)
{
    //等待发送缓冲区空闲
    while(spi_i2s_flag_get(SPI0, SPI_FLAG_TBE) == RESET);

    //发送数据
    spi_i2s_data_transmit(SPI0, data);

    //等待传输完成
    while(spi_i2s_flag_get(SPI0, SPI_FLAG_TRANS) == SET);
}