#pragma once

#include <stdint.h>

#define ARCHI_FC_ADDR                   0x00000000
#define ARCHI_FC_PERIPHERALS_OFFSET     0x00200000

#define ARCHI_FC_PERIPHERALS_ADDR       (ARCHI_FC_ADDR + ARCHI_FC_PERIPHERALS_OFFSET)

#define ARCHI_FC_TIMER_SIZE             0x00000800

#define ARCHI_FC_TIMER_OFFSET           0x00000400
#define ARCHI_FC_EU_OFFSET              0x00000800
#define ARCHI_FC_ICACHE_OFFSET          0x00001400

#define ARCHI_FC_TIMER_ADDR             (void*)(ARCHI_FC_PERIPHERALS_ADDR + ARCHI_FC_TIMER_OFFSET)
#define PLP_TIMER_VALUE_LO              0x08
#define PLP_TIMER_CFG_REG_LO            0x00
#define PLP_TIMER_ENABLE_BIT            0
#define PLP_TIMER_RESET_BIT             1
#define PLP_TIMER_IRQ_ENABLE_BIT        2
#define PLP_TIMER_IEM_BIT               3
#define PLP_TIMER_CMP_CLR_BIT           4
#define PLP_TIMER_ONE_SHOT_BIT          5
#define PLP_TIMER_PRESCALER_ENABLE_BIT  6
#define PLP_TIMER_CLOCK_SOURCE_BIT      7
#define PLP_TIMER_PRESCALER_VALUE_BIT   8
#define PLP_TIMER_PRESCALER_VALUE_BITS  8
#define PLP_TIMER_64_BIT                31

#define plp_timer_conf_get(a,b,c,d,e,f,g,h,i)      ((a << PLP_TIMER_ENABLE_BIT) \
        | (b << PLP_TIMER_RESET_BIT) \
        | (c << PLP_TIMER_IRQ_ENABLE_BIT) \
        | (d << PLP_TIMER_IEM_BIT) \
        | (e << PLP_TIMER_CMP_CLR_BIT) \
        | (f << PLP_TIMER_ONE_SHOT_BIT) \
        | (g << PLP_TIMER_PRESCALER_ENABLE_BIT) \
        | (h << PLP_TIMER_PRESCALER_VALUE_BIT) \
        | (i << PLP_TIMER_64_BIT) \
        )
#define gap8_resethwtimer()                     pulp_write32(ARCHI_FC_TIMER_ADDR + PLP_TIMER_CFG_REG_LO, plp_timer_conf_get(1,1,0,0,0,0,0,0,0))
#define gap8_readhwtimer()                      pulp_read32(ARCHI_FC_TIMER_ADDR + PLP_TIMER_VALUE_LO)