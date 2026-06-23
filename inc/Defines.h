

#include <cr_section_macros.h>
#include <vector>
#include <cstdio>
#include "vars.h"
#include "target.h"
#include "Hardware.h"
#include "../src/drivers/GPIO/GPIO.h"

#ifndef __NOP
  #ifdef __GNUC__
    #define __NOP() __asm volatile ("nop")
  #else
    #define __NOP() __nop()
  #endif
#endif
