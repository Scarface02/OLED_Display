/**
 ****************************************************************************************
 *
 * \file SSD1322_HW_Driver.c
 *
 * \brief Hardware dependent functions for SSD1322 OLED display.
 *
 * This file contains functions that rely on hardware of used MCU. In this example functions
 * are filled with STM32F411RE hardware implementation. To use this library on any other MCU
 * you just have to provide its hardware implementations of functions from this file and higher
 * level functions should work without modification.
 *
 * Copyright (C) 2020 Wojciech Klimek
 * MIT license:
 * https://github.com/wjklimek1/SSD1322_OLED_library
 *
 ****************************************************************************************
 */

//=================== Include hardware HAL libraries =====================//
#include "user.h"

#include "SSD1322_HW_Driver.h"


//====================== CS pin low ========================//
/**
 *  @brief Drives CS (Chip Select) pin of SPI interface low.
 *
 *  CS pin may be also signed as "SS" or "NSS"
 */
void SSD1322_HW_drive_CS_low()
{
	//HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, 0);
    OLED_CS_SetLow();
}

//====================== CS pin high ========================//
/**
 *  @brief Drives CS (Chip Select) pin of SPI interface high.
 *
 *  CS pin may be also signed as "SS" or "NSS"
 */
void SSD1322_HW_drive_CS_high()
{
	//HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, 1);
    OLED_CS_SetHigh();
}

//====================== DC pin low ========================//
/**
 *  @brief Drives DC (Data/Command) pin of OLED driver low.
 *
 *  High state is for data and low state is for command.
 */
void SSD1322_HW_drive_DC_low()
{
	//HAL_GPIO_WritePin(SPI5_DC_GPIO_Port, SPI5_DC_Pin, 0);
    OLED_DC_SetLow();
}

//====================== DC pin high ========================//
/**
 *  @brief Drives DC (Data/Command) pin of of OLED driver high.
 *
 *  High state is for data and low state is for command.
 */
void SSD1322_HW_drive_DC_high()
{
	//HAL_GPIO_WritePin(SPI5_DC_GPIO_Port, SPI5_DC_Pin, 1);
    OLED_DC_SetHigh();
}

//====================== RESET pin low ========================//
/**
 *  @brief Drives RESET pin of of OLED driver low.
 *
 *  Logic low on RESET resets OLED driver.
 */
void SSD1322_HW_drive_RESET_low()
{
    
	//HAL_GPIO_WritePin(SPI5_RESET_GPIO_Port, SPI5_RESET_Pin, 0);
    OLED_RESET_SetLow();
}

//====================== RESET pin high ========================//
/**
 *  @brief Drives RESET pin of of OLED driver high.
 *
 *  Logic low on RESET resets OLED driver.
 */
void SSD1322_HW_drive_RESET_high()
{
	//HAL_GPIO_WritePin(SPI5_RESET_GPIO_Port, SPI5_RESET_Pin, 1);
    OLED_RESET_SetHigh();
}

//====================== Send single SPI byte ========================//
/**
 *  @brief Transmits single byte through SPI interface.
 *
 *  @param[in] byte_to_transmit byte that will be transmitted through SPI interface
 */
void SSD1322_HW_SPI_send_byte(uint8_t byte_to_transmit)
{
	//HAL_SPI_Transmit(&hspi5, &byte_to_transmit, 1, 10);
//    SPI_Write_8bit(byte_to_transmit);
    SPI1_Exchange8bit(byte_to_transmit);
}

//====================== Send array of SPI bytes ========================//
/**
 *  @brief Transmits array of bytes through SPI interface.
 *
 *  @param[in] array_to_transmit array of bytes that will be transmitted through SPI interface
 *  @param[in] array_size amount of bytes to transmit
 */
void SSD1322_HW_SPI_send_array(uint8_t *array_to_transmit, uint32_t array_size)
{
	//HAL_SPI_Transmit(&hspi5, array_to_transmit, array_size, 100);
    //SPI1_WriteBlock(array_to_transmit, array_size);
//    for(int packagecounter=0; packagecounter<array_size; packagecounter++){
//        SPI_Write_8bit(array_to_transmit[packagecounter]);
//    }
    for(int packagecounter=0; packagecounter<array_size; packagecounter++){
        SPI1_Exchange8bit(array_to_transmit[packagecounter]);
    }
}

//====================== Milliseconds delay ========================//
/**
 *  @brief Wait for x milliseconds.
 *
 *  NOTE: This function is only used in initialization sequence to pull reset down and high
 *  and later to wait for Vdd stabilization. It takes time ONLY on startup (around 200ms)
 *  and is NOT USED during normal operation.
 *
 *  @param[in] milliseconds time to wait
 */
void SSD1322_HW_msDelay(int milliseconds)
{
	//HAL_Delay(milliseconds);
    for(int i=0;i<milliseconds;i++){
        while(!IFS0bits.T2IF);
        IFS0bits.T2IF = 0;
    }
    
}

//void SPI_Write_8bit(uint8_t data) {
//    SCK_SetLow();
//    //NSS_SetLow();
////    __delay_us(20);
////    __delay_us(200);
//    for(int i=0;i<1000;i++);
//    for(uint8_t bitcount=8; bitcount!=0; bitcount--) {
//        SCK_SetLow();
////        __delay_us(1);
////        __delay_us(10);
//        for(int i=0;i<100;i++);
//        if(data&0x80) {
//            MOSI_SetHigh();
//        } else {
//            MOSI_SetLow();
//        }
//        SCK_SetHigh();
////        __delay_us(1);
////        __delay_us(10);
//        for(int i=0;i<100;i++);
//        data<<=1;
//    }
////    __delay_us(200);
//    for(int i=0;i<1000;i++);
//    SCK_SetLow();
//    MOSI_SetHigh();
//}