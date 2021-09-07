/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v4.1
processor: MK64FN1M0xxx12
package_id: MK64FN1M0VLL12
mcu_data: ksdk2_0
processor_version: 4.0.1
board: FRDM-K64F
functionalGroups:
- name: BOARD_InitPeripherals
  called_from_default_init: true
  selectedCore: core0
- name: BOARD_InitBUTTONsPeripheral
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitLEDsPeripheral
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitDEBUG_UARTPeripheral
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitACCELPeripheral
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitSDHCPeripheral
  id_prefix: BOARD_
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system'
- global_system_definitions: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * SPI_0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'SPI_0'
- type: 'dspi'
- mode: 'DSPI_Polling'
- type_id: 'dspi_305e5b03c593d065f61ded8061d15797'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'SPI0'
- config_sets:
  - fsl_dspi:
    - dspi_mode: 'kDSPI_Master'
    - clockSource: 'BusInterfaceClock'
    - clockSourceFreq: 'GetFreq'
    - dspi_master_config:
      - whichCtar: 'kDSPI_Ctar0'
      - ctarConfig:
        - baudRate: '500000'
        - bitsPerFrame: '8'
        - cpol: 'kDSPI_ClockPolarityActiveHigh'
        - cpha: 'kDSPI_ClockPhaseFirstEdge'
        - direction: 'kDSPI_MsbFirst'
        - pcsToSckDelayInNanoSec: '1000'
        - lastSckToPcsDelayInNanoSec: '1000'
        - betweenTransferDelayInNanoSec: '1000'
      - whichPcs: 'PCS0_SS'
      - pcsActiveHighOrLow: 'kDSPI_PcsActiveLow'
      - enableContinuousSCK: 'false'
      - enableRxFifoOverWrite: 'false'
      - enableModifiedTimingFormat: 'false'
      - samplePoint: 'kDSPI_SckToSin0Clock'
    - quick_selection: 'QS_DSPI_1'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const dspi_master_config_t SPI_0_config = {
  .whichCtar = kDSPI_Ctar0,
  .ctarConfig = {
    .baudRate = 500000,
    .bitsPerFrame = 8,
    .cpol = kDSPI_ClockPolarityActiveHigh,
    .cpha = kDSPI_ClockPhaseFirstEdge,
    .direction = kDSPI_MsbFirst,
    .pcsToSckDelayInNanoSec = 1000,
    .lastSckToPcsDelayInNanoSec = 1000,
    .betweenTransferDelayInNanoSec = 1000
  },
  .whichPcs = kDSPI_Pcs0,
  .pcsActiveHighOrLow = kDSPI_PcsActiveLow,
  .enableContinuousSCK = false,
  .enableRxFifoOverWrite = false,
  .enableModifiedTimingFormat = false,
  .samplePoint = kDSPI_SckToSin0Clock
};

void SPI_0_init(void) {
  /* Initialization function */
  DSPI_MasterInit(SPI_0_PERIPHERAL, &SPI_0_config, SPI_0_CLK_FREQ);
}

/***********************************************************************************************************************
 * GPIO_1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'GPIO_1'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'GPIOC'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTC_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
    - quick_selection: 'QS_GPIO_1'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void GPIO_1_init(void) {
  /* Make sure, the clock gate for port C is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * PIT_1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'PIT_1'
- type: 'pit'
- mode: 'LPTMR_GENERAL'
- type_id: 'pit_a4782ba5223c8a2527ba91aeb2bc4159'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'PIT'
- config_sets:
  - fsl_pit:
    - enableRunInDebug: 'false'
    - timingConfig:
      - clockSource: 'BusInterfaceClock'
      - clockSourceFreq: 'GetFreq'
    - channels:
      - 0:
        - channelNumber: '0'
        - enableChain: 'false'
        - timerPeriod: '0.15s'
        - startTimer: 'true'
        - enableInterrupt: 'true'
        - interrupt:
          - IRQn: 'PIT0_IRQn'
          - enable_priority: 'false'
          - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const pit_config_t PIT_1_config = {
  .enableRunInDebug = false
};

void PIT_1_init(void) {
  /* Initialize the PIT. */
  PIT_Init(PIT_1_PERIPHERAL, &PIT_1_config);
  /* Set channel 0 period to 150 ms. */
  PIT_SetTimerPeriod(PIT_1_PERIPHERAL, kPIT_Chnl_0, PIT_1_0_TICKS);
  /* Enable interrupts from channel 0. */
  PIT_EnableInterrupts(PIT_1_PERIPHERAL, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
  /* Enable interrupt PIT_1_0_IRQN request in the NVIC */
  EnableIRQ(PIT_1_0_IRQN);
  /* Start channel 0. */
  PIT_StartTimer(PIT_1_PERIPHERAL, kPIT_Chnl_0);
}

/***********************************************************************************************************************
 * BOARD_InitBUTTONsPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * SW2 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'SW2'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitBUTTONsPeripheral'
- peripheral: 'GPIOC'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'true'
    - port_interrupt:
      - IRQn: 'PORTC_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_SW2_init(void) {
  /* Make sure, the clock gate for port C is enabled (e. g. in pin_mux.c) */
  /* Enable interrupt PORTC_IRQn request in the NVIC */
  EnableIRQ(PORTC_IRQn);
}

/***********************************************************************************************************************
 * SW3 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'SW3'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitBUTTONsPeripheral'
- peripheral: 'GPIOA'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'true'
    - port_interrupt:
      - IRQn: 'PORTA_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_SW3_init(void) {
  /* Make sure, the clock gate for port A is enabled (e. g. in pin_mux.c) */
  /* Enable interrupt PORTA_IRQn request in the NVIC */
  EnableIRQ(PORTA_IRQn);
}

/***********************************************************************************************************************
 * BOARD_InitLEDsPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * LEDRGB_GREEN initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LEDRGB_GREEN'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitLEDsPeripheral'
- peripheral: 'GPIOE'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTE_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_LEDRGB_GREEN_init(void) {
  /* Make sure, the clock gate for port E is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * LEDRGB_RED_BLUE initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LEDRGB_RED_BLUE'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitLEDsPeripheral'
- peripheral: 'GPIOB'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTB_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_LEDRGB_RED_BLUE_init(void) {
  /* Make sure, the clock gate for port B is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * BOARD_InitDEBUG_UARTPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * DEBUG_UART initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'DEBUG_UART'
- type: 'uart'
- mode: 'polling'
- type_id: 'uart_cd31a12aa8c79051fda42cc851a27c37'
- functional_group: 'BOARD_InitDEBUG_UARTPeripheral'
- peripheral: 'UART0'
- config_sets:
  - uartConfig_t:
    - uartConfig:
      - clockSource: 'BusInterfaceClock'
      - clockSourceFreq: 'GetFreq'
      - baudRate_Bps: '115200'
      - parityMode: 'kUART_ParityDisabled'
      - stopBitCount: 'kUART_OneStopBit'
      - txFifoWatermark: '0'
      - rxFifoWatermark: '1'
      - idleType: 'kUART_IdleTypeStartBit'
      - enableTx: 'false'
      - enableRx: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const uart_config_t BOARD_DEBUG_UART_config = {
  .baudRate_Bps = 115200,
  .parityMode = kUART_ParityDisabled,
  .stopBitCount = kUART_OneStopBit,
  .txFifoWatermark = 0,
  .rxFifoWatermark = 1,
  .idleType = kUART_IdleTypeStartBit,
  .enableTx = false,
  .enableRx = false
};

void BOARD_DEBUG_UART_init(void) {
  UART_Init(BOARD_DEBUG_UART_PERIPHERAL, &BOARD_DEBUG_UART_config, BOARD_DEBUG_UART_CLOCK_SOURCE);
}

/***********************************************************************************************************************
 * BOARD_InitACCELPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * ACCEL_I2C initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'ACCEL_I2C'
- type: 'i2c'
- mode: 'I2C_Polling'
- type_id: 'i2c_2566d7363e7e9aaedabb432110e372d7'
- functional_group: 'BOARD_InitACCELPeripheral'
- peripheral: 'I2C0'
- config_sets:
  - fsl_i2c:
    - i2c_mode: 'kI2C_Master'
    - clockSource: 'BusInterfaceClock'
    - clockSourceFreq: 'GetFreq'
    - i2c_master_config:
      - enableMaster: 'true'
      - enableStopHold: 'false'
      - baudRate_Bps: '100000'
      - glitchFilterWidth: '0'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const i2c_master_config_t BOARD_ACCEL_I2C_config = {
  .enableMaster = true,
  .enableStopHold = false,
  .baudRate_Bps = 100000,
  .glitchFilterWidth = 0
};

void BOARD_ACCEL_I2C_init(void) {
  /* Initialization function */
  I2C_MasterInit(BOARD_ACCEL_I2C_PERIPHERAL, &BOARD_ACCEL_I2C_config, BOARD_ACCEL_I2C_CLK_FREQ);
}

/***********************************************************************************************************************
 * BOARD_InitSDHCPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * SDHC_DETECT initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'SDHC_DETECT'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitSDHCPeripheral'
- peripheral: 'GPIOE'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTE_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_SDHC_DETECT_init(void) {
  /* Make sure, the clock gate for port E is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  SPI_0_init();
  GPIO_1_init();
  PIT_1_init();
}

void BOARD_InitBUTTONsPeripheral(void)
{
  /* Initialize components */
  BOARD_SW2_init();
  BOARD_SW3_init();
}

void BOARD_InitLEDsPeripheral(void)
{
  /* Initialize components */
  BOARD_LEDRGB_GREEN_init();
  BOARD_LEDRGB_RED_BLUE_init();
}

void BOARD_InitDEBUG_UARTPeripheral(void)
{
  /* Initialize components */
  BOARD_DEBUG_UART_init();
}

void BOARD_InitACCELPeripheral(void)
{
  /* Initialize components */
  BOARD_ACCEL_I2C_init();
}

void BOARD_InitSDHCPeripheral(void)
{
  /* Initialize components */
  BOARD_SDHC_DETECT_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
