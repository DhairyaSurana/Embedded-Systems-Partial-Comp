/*
 *  ======== Board.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the CC3220SF_LAUNCHXL
 *  by the SysConfig tool.
 */

#include <stddef.h>

#ifndef DeviceFamily_CC3220
#define DeviceFamily_CC3220
#endif

#include <ti/devices/DeviceFamily.h>

#include "Board.h"

/*
 *  =============================== ADC ===============================
 */

#include <ti/drivers/ADC.h>
#include <ti/drivers/adc/ADCCC32XX.h>

#include <ti/devices/cc32xx/driverlib/adc.h>

#define Board_ADCCOUNT 2

/*
 *  ======== adcCCC32XXObjects ========
 */
ADCCC32XX_Object adcCC32XXObjects[Board_ADCCOUNT];

/*
 *  ======== adcCC3220SHWAttrs ========
 */
const ADCCC32XX_HWAttrsV1 adcCC32XXHWAttrs[Board_ADCCOUNT] = {
    /* Board_ADC0 */
    {
        .adcPin = ADCCC32XX_PIN_59_CH_2,
    },
    /* Board_ADC1 */
    {
        .adcPin = ADCCC32XX_PIN_60_CH_3,
    },
};

/*
 *  ======== ADC_config ========
 */
const ADC_Config ADC_config[Board_ADCCOUNT] = {
    /* Board_ADC0 */
    {
        .fxnTablePtr = &ADCCC32XX_fxnTable,
        .object = &adcCC32XXObjects[Board_ADC0],
        .hwAttrs = &adcCC32XXHWAttrs[Board_ADC0]
    },
    /* Board_ADC1 */
    {
        .fxnTablePtr = &ADCCC32XX_fxnTable,
        .object = &adcCC32XXObjects[Board_ADC1],
        .hwAttrs = &adcCC32XXHWAttrs[Board_ADC1]
    },
};

const uint_least8_t ADC_count = Board_ADCCOUNT;


/*
 *  =============================== GPIO ===============================
 */

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOCC32XX.h>

/*
 *  ======== gpioPinConfigs ========
 *  Array of Pin configurations
 */
GPIO_PinConfig gpioPinConfigs[] = {
    /* Board_GPIO1 */
    GPIOCC32XX_GPIO_12 | GPIO_CFG_IN_NOPULL | GPIO_CFG_IN_INT_NONE,
    /* Board_GPIO2 */
    GPIOCC32XX_GPIO_14 | GPIO_CFG_IN_NOPULL | GPIO_CFG_IN_INT_NONE,
    /* Board_GPIO3 */
    GPIOCC32XX_GPIO_15 | GPIO_CFG_IN_NOPULL | GPIO_CFG_IN_INT_NONE,
    /* Board_GPIO4 */
    GPIOCC32XX_GPIO_16 | GPIO_CFG_IN_NOPULL | GPIO_CFG_IN_INT_NONE,
    /* Board_GPIO5 */
    GPIOCC32XX_GPIO_17 | GPIO_CFG_IN_NOPULL | GPIO_CFG_IN_INT_NONE,
    /* Board_GPIO6 */
    GPIOCC32XX_GPIO_28 | GPIO_CFG_IN_NOPULL | GPIO_CFG_IN_INT_NONE,
    /* Board_GPIO7 */
    GPIOCC32XX_GPIO_25 | GPIO_CFG_IN_NOPULL | GPIO_CFG_IN_INT_NONE,
    /* Board_GPIO8 */
    GPIOCC32XX_GPIO_00 | GPIO_CFG_IN_NOPULL | GPIO_CFG_IN_INT_NONE,
};

/*
 *  ======== GPIOCC32XX_config ========
 */
const GPIOCC32XX_Config GPIOCC32XX_config = {
    .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = NULL,
    .numberOfPinConfigs = 8,
    .numberOfCallbacks = 0,
    .intPriority = (~0)
};




/*
 *  =============================== Power ===============================
 */
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC32XX.h>
#include <ti/devices/cc32xx/driverlib/prcm.h>
#include "Board.h"

extern void PowerCC32XX_initPolicy(void);
extern void PowerCC32XX_sleepPolicy(void);
PowerCC32XX_ParkInfo parkInfo[];
/*
 *  This structure defines the configuration for the Power Manager.
 */
const PowerCC32XX_ConfigV1 PowerCC32XX_config = {
    .policyInitFxn             = PowerCC32XX_initPolicy,
    .policyFxn                 = PowerCC32XX_sleepPolicy,
    .enterLPDSHookFxn          = NULL,
    .resumeLPDSHookFxn         = NULL,
    .enablePolicy              = false,
    .enableGPIOWakeupLPDS      = true,
    .enableGPIOWakeupShutdown  = true,
    .enableNetworkWakeupLPDS   = true,
    .wakeupGPIOSourceLPDS      = PRCM_LPDS_GPIO13,
    .wakeupGPIOTypeLPDS        = PRCM_LPDS_FALL_EDGE,
    .wakeupGPIOFxnLPDS         = NULL,
    .wakeupGPIOFxnLPDSArg      = 0,
    .wakeupGPIOSourceShutdown  = PRCM_HIB_GPIO13,
    .wakeupGPIOTypeShutdown    = PRCM_HIB_RISE_EDGE,
    .ramRetentionMaskLPDS      = PRCM_SRAM_COL_1|PRCM_SRAM_COL_2|PRCM_SRAM_COL_3|PRCM_SRAM_COL_4,
    .keepDebugActiveDuringLPDS = false,
    .ioRetentionShutdown       = PRCM_IO_RET_GRP_0|PRCM_IO_RET_GRP_1|PRCM_IO_RET_GRP_2|PRCM_IO_RET_GRP_3,
    .pinParkDefs               = parkInfo,
    .numPins                   = 31
};


/*
 *  =============================== Timer ===============================
 */

#include <ti/drivers/Timer.h>
#include <ti/devices/cc32xx/inc/hw_memmap.h>
#include <ti/devices/cc32xx/inc/hw_ints.h>
#include <ti/drivers/timer/TimerCC32XX.h>

#define Board_TIMERCOUNT 2

/*
 *  ======== timerCC32XXObjects ========
 */
TimerCC32XX_Object timerCC32XXObjects[Board_TIMERCOUNT];

/*
 *  ======== timerCC32XXHWAttrs ========
 */
const TimerCC32XX_HWAttrs timerCC32XXHWAttrs[Board_TIMERCOUNT] = {
    /* Board_TIMER0 */
    {
        .baseAddress = TIMERA1_BASE,
        .subTimer    = TimerCC32XX_timer32,
        .intNum      = INT_TIMERA1A,
        .intPriority = (~0)
    },
    /* Board_TIMER1 */
    {
        .baseAddress = TIMERA0_BASE,
        .subTimer    = TimerCC32XX_timer32,
        .intNum      = INT_TIMERA0A,
        .intPriority = (~0)
    },
};

/*
 *  ======== Timer_config ========
 */
const Timer_Config Timer_config[Board_TIMERCOUNT] = {
    /* Board_TIMER0 */
    {
        .fxnTablePtr = &TimerCC32XX_fxnTable,
        .object      = &timerCC32XXObjects[Board_TIMER0],
        .hwAttrs     = &timerCC32XXHWAttrs[Board_TIMER0]
    },
    /* Board_TIMER1 */
    {
        .fxnTablePtr = &TimerCC32XX_fxnTable,
        .object      = &timerCC32XXObjects[Board_TIMER1],
        .hwAttrs     = &timerCC32XXHWAttrs[Board_TIMER1]
    },
};

const uint_least8_t Timer_count = Board_TIMERCOUNT;


/*
 *  =============================== UART ===============================
 */

#include <ti/drivers/UART.h>
#include <ti/devices/cc32xx/inc/hw_ints.h>
#include <ti/devices/cc32xx/inc/hw_memmap.h>
#include <ti/drivers/uart/UARTCC32XX.h>

#define Board_UARTCOUNT 1

#define UART0_BASE UARTA0_BASE
#define UART1_BASE UARTA1_BASE
#define INT_UART0  INT_UARTA0
#define INT_UART1  INT_UARTA1


static unsigned char uartCC32XXRingBuffer0[32];
UARTCC32XX_Object uartCC32XXObjects0;

static const UARTCC32XX_HWAttrsV1 uartCC32XXHWAttrs0 = {
    .baseAddr           = UART0_BASE,
    .intNum             = INT_UART0,
    .intPriority        = (~0),
    .flowControl        = UARTCC32XX_FLOWCTRL_NONE,
    .ringBufPtr         = uartCC32XXRingBuffer0,
    .ringBufSize        = sizeof(uartCC32XXRingBuffer0),
    .rxPin              = UARTCC32XX_PIN_45_UART0_RX,
    .txPin              = UARTCC32XX_PIN_62_UART0_TX,
    .ctsPin             = UARTCC32XX_PIN_UNASSIGNED,
    .rtsPin             = UARTCC32XX_PIN_UNASSIGNED,
    .errorFxn           = NULL
  };

const UART_Config UART_config[Board_UARTCOUNT] = {
    {   /* Board_UART0 */
        .fxnTablePtr = &UARTCC32XX_fxnTable,
        .object      = &uartCC32XXObjects0,
        .hwAttrs     = &uartCC32XXHWAttrs0
    },
};

const uint_least8_t UART_count = Board_UARTCOUNT;


#include <ti/drivers/power/PowerCC32XX.h>

/*
 * This table defines the parking state to be set for each parkable pin
 * during LPDS. (Device resources must be parked during LPDS to achieve maximum
 * power savings.)  If the pin should be left unparked, specify the state
 * PowerCC32XX_DONT_PARK.  For example, for a UART TX pin, the device
 * will automatically park the pin in a high state during transition to LPDS,
 * so the Power Manager does not need to explictly park the pin.  So the
 * corresponding entries in this table should indicate PowerCC32XX_DONT_PARK.
 */
PowerCC32XX_ParkInfo parkInfo[] = {
/*        PIN                    PARK STATE              Pin Alias
   -----------------  ------------------------------     ---------------*/

  {PowerCC32XX_PIN01, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP10 */
  {PowerCC32XX_PIN02, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP11 */
  {PowerCC32XX_PIN03, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP12 */
  {PowerCC32XX_PIN04, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP13 */
  {PowerCC32XX_PIN05, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP14 */
  {PowerCC32XX_PIN06, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP15 */
  {PowerCC32XX_PIN07, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP16 */
  {PowerCC32XX_PIN08, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP17 */
  {PowerCC32XX_PIN13, PowerCC32XX_WEAK_PULL_DOWN_STD},
  {PowerCC32XX_PIN15, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP22 */
  {PowerCC32XX_PIN16, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* TDI */
  {PowerCC32XX_PIN17, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* TDO */
  {PowerCC32XX_PIN18, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP28 */
  {PowerCC32XX_PIN19, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* TCK */
  {PowerCC32XX_PIN20, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* TMS */
  {PowerCC32XX_PIN21, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* SOP2 */
  {PowerCC32XX_PIN29, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP26 */
  {PowerCC32XX_PIN30, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP27 */
  {PowerCC32XX_PIN45, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP31 */
  {PowerCC32XX_PIN50, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP00 */
  {PowerCC32XX_PIN52, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP32 */
  {PowerCC32XX_PIN53, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP30 */
  {PowerCC32XX_PIN55, PowerCC32XX_WEAK_PULL_UP_STD},   /* GP01 */
  {PowerCC32XX_PIN57, PowerCC32XX_WEAK_PULL_UP_STD},   /* GP02 */
  {PowerCC32XX_PIN58, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP03 */
  {PowerCC32XX_PIN59, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP04 */
  {PowerCC32XX_PIN60, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP05 */
  {PowerCC32XX_PIN61, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP06 */
  {PowerCC32XX_PIN62, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP07 */
  {PowerCC32XX_PIN63, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP08 */
  {PowerCC32XX_PIN64, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP09 */
};


#include <ti/drivers/Board.h>

/*
 *  ======== Board_initHook ========
 *  Perform any board-specific initialization needed at startup.  This
 *  function is declared weak to allow applications to override it if needed.
 */
#if defined(__IAR_SYSTEMS_ICC__)
__weak void Board_initHook(void)
#elif defined(__GNUC__) && !defined(__ti__)
void __attribute__((weak)) Board_initHook(void)
#else
#pragma WEAK (Board_initHook)
void Board_initHook(void)
#endif
{
}

/*
 *  ======== Board_init ========
 *  Perform any initialization needed before using any board APIs
 */
void Board_init(void)
{
    /* ==== /ti/drivers/Power initialization ==== */
    PRCMCC3200MCUInit();
    Power_init();

    Board_initHook();
}

/*
 *  ======== Board_debugHeader ========
 *  This structure prevents the CC32XXSF bootloader from overwriting the
 *  internal FLASH; this allows us to flash a program that will not be
 *  overwritten by the bootloader with the encrypted program saved in
 *  "secure/serial flash".
 *
 *  This structure must be placed at the beginning of internal FLASH (so
 *  the bootloader is able to recognize that it should not overwrite
 *  internal FLASH).
 */
#if defined (__SF_DEBUG__) || defined(__SF_NODEBUG__)
#if defined(__TI_COMPILER_VERSION__)
#pragma DATA_SECTION(Board_debugHeader, ".dbghdr")
#pragma RETAIN(Board_debugHeader)
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma location=".dbghdr"
#elif defined(__GNUC__)
__attribute__ ((section (".dbghdr")))
#endif
#if defined(__SF_DEBUG__)
const uint32_t Board_debugHeader[] = {
    0x5AA5A55A,
    0x000FF800,
    0xEFA3247D
};
#elif defined (__SF_NODEBUG__)
const uint32_t Board_debugHeader[] = {
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};
#endif
#endif
