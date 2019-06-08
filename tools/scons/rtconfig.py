# BSP Note: For TI EK-TM4C1294XL Tiva C Series Connected LancuhPad	(REV D)

import os

# toolchains options
ARCH       = 'arm'
CPU        = 'cortex-m4'
CROSS_TOOL = 'gcc'

if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')
	
#device options

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery, Keil MDK, IAR

PLATFORM 	= 'gcc'
EXEC_PATH 	= 'D:/ArdaArmTools/GNUARM_4.9_2015q1/bin'	

if os.getenv('RTT_EXEC_PATH'):
	EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
#BUILD = 'release'

# tool-chains
PREFIX = 'arm-none-eabi-'
CC = PREFIX + 'gcc'
AS = PREFIX + 'gcc'
AR = PREFIX + 'ar'
LINK = PREFIX + 'gcc'
TARGET_EXT = 'elf'
SIZE = PREFIX + 'size'
OBJDUMP = PREFIX + 'objdump'
OBJCPY = PREFIX + 'objcopy'

DEVICE = ' -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections'
CFLAGS = DEVICE + ' -std=c99'
AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -Wa,-mimplicit-it=thumb '


ar rcs libtest.a pin.o

# LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread-stm32.map,-cref,-u,Reset_Handler -T stm32_rom.ld'
# LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread-stm32.map'
# src = Glob('*.o')
# StaticLibrary('*.O')
# SharedLibrary('*o')

CPATH = ''
LPATH = ''

if BUILD == 'debug':
	CFLAGS += ' -O0 -gdwarf-2 -g'
#	AFLAGS += ' -gdwarf-2'
else:
	CFLAGS += ' -O2'

POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
