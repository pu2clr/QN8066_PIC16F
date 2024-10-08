/*
 * File:   qn8066.c
 * Author: rcaratti
 *
 * Created on August 20, 2024, 10:26 PM
 */


#include <xc.h>
#include "QN8066.h"
#include "i2c.h"

/**
 * @defgroup g01 I2C BUS
 * @section g01 I2C
 * @detail I2C implementation
 * @see: https://circuitdigest.com/microcontroller-projects/i2c-communication-with-pic-microcontroller-pic16f877a
 */



void set_register(unsigned char registerNumber, unsigned char value) {
    i2c_begin();
    
    i2c_write(QN8066_I2C_ADDRESS);  // Sends device address
    i2c_write(registerNumber);      // Sends register
    i2c_write(value);               // Sends the data
    
    i2c_end();    
    __delay_ms(2);
}


unsigned char get_register(unsigned char registerNumber) {
    unsigned char value;
    i2c_begin();                       
    i2c_write(QN8066_I2C_ADDRESS);      // Send device address with the write bit
    i2c_write(registerNumber);          // Send the register address we want to read 
    i2c_begin();     
    i2c_write(QN8066_I2C_ADDRESS + 1);  // Send device address with the read bit
    value = i2c_read(1);                // Read a byte and send NACK after the read to indicate the read is completed
        
    i2c_end();                         // Send Stop    
    
    __delay_ms(2);
    
    return value;
}


void qn8066_begin(void) {
    
    
  i2c_initialize();
    
  reg_system1.raw = 0B11100011;
  reg_system2.raw = 0;
  reg_cca.raw = get_register(REG_CCA);
  reg_cca.arg.xtal_inj = 1; 
  reg_gplt.raw = get_register(REG_GPLT);
  reg_fdev.raw = get_register(REG_FDEV);
  reg_rds.raw =  get_register(REG_RDS);
  reg_reg_vga.raw = get_register(REG_REG_VGA);
  reg_int_ctrl.raw = get_register(REG_INT_CTRL);
  reg_pac.raw = get_register(REG_PAC);
  reg_vol_ctl.raw = get_register(REG_VOL_CTL);    
} 


void qn8066_set_tx(unsigned int frequency) {

  reg_system1.raw = 0B11100011;
  set_register(REG_SYSTEM1, reg_system1.raw);           // SYSTEM1 => 11100011  =>  swrst = 1; recal = 1; stnby = 1; ccs_ch_dis = 1; cca_ch_dis = 1
  set_register(REG_SYSTEM2, reg_system2.raw); 
  reg_system2.arg.rdsrdy = !(reg_system2.arg.rdsrdy);   // Toggle 
  set_register(REG_SYSTEM2, reg_system2.raw); 
  set_register(REG_CCA, reg_cca.raw);                   // CCA => 01010000 => xtal_inj = 0; imr = 1; SNR_CCA_TH = 010000
  // Sets the crystal oscillator divider
  set_register(REG_XTAL_DIV0, xtal_div & 0xFF);         // Lower 8 bits of xtal_div[10:0].
  set_register(REG_XTAL_DIV1, (xtal_div >> 8) |  0B0001000); // Higher 3 bits of xtal_div[10:0].
  set_register(REG_XTAL_DIV2, 0B01011100);              // XTAL_DIV2 = > 01011100 (It is the default value)

  // set_register(REG_SYSTEM1, reg_system1.raw);        // SYSTEM1 => 00001011 => Set TX On
  set_register(REG_FDEV, reg_fdev.raw);                 // FDEV => 01111101 => 125 (Decimal)
  set_register(REG_RDS, reg_rds.raw);                   // RDS => 00111100 => Line_in_en = 0; RDSFDEV = 60 (Decimal) 
  set_register(REG_GPLT, reg_gplt.raw);                 // GPLT => 00111001 => Tx_sftclpth = 00 (12?d2051 - 3db back off from 0.5v); t1m_sel = 11 (Infinity); GAIN_TXPLT = 1001 (9% 75 kHz)

  unsigned int  auxFreq = (frequency - 600)  * 2;
  reg_int_ctrl.raw =  0B00100000 | auxFreq >> 8;
  set_register(REG_INT_CTRL,reg_int_ctrl.raw );
  set_register(REG_TXCH, 0B11111111 & auxFreq);

  // Checking unkown registers
  // set_register(0x49, 0B11101000); 
  set_register(0x49, 0B11011111); 
  set_register(0x6E, 0B11111111); 

  reg_system1.raw = 0B00001011;
  set_register(REG_SYSTEM1, reg_system1.raw);   // SYSTEM1 => 00001011 => txreq = 1; ccs_ch_dis = 1; cca_ch_dis = 1 
  // set_register(REG_REG_VGA, 0B01011011);     // REG_VGA =>  01011011 => Tx_sftclpen = 0; TXAGC_GVGA = 101; TXAGC_GDB = 10; RIN = 11 (80K)
  set_register(REG_REG_VGA, reg_reg_vga.raw);   // REG_VGA =>  01011011 => Tx_sftclpen = 0; TXAGC_GVGA = 101; TXAGC_GDB = 10; RIN = 11 (80K)
  __delay_ms(100);
    
}
