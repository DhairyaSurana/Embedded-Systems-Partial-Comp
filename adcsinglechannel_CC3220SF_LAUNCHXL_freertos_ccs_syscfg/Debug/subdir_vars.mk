################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../CC3220SF_LAUNCHXL_FREERTOS.cmd 

SYSCFG_SRCS += \
../adcsinglechannel.syscfg 

C_SRCS += \
../adcsinglechannel.c \
./syscfg/Board.c \
../debug.c \
../main_freertos.c \
../sensor_queue.c \
../sensor_state.c \
../timerone.c \
../timertwo.c 

GEN_FILES += \
./syscfg/Board.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./adcsinglechannel.d \
./syscfg/Board.d \
./debug.d \
./main_freertos.d \
./sensor_queue.d \
./sensor_state.d \
./timerone.d \
./timertwo.d 

OBJS += \
./adcsinglechannel.obj \
./syscfg/Board.obj \
./debug.obj \
./main_freertos.obj \
./sensor_queue.obj \
./sensor_state.obj \
./timerone.obj \
./timertwo.obj 

GEN_MISC_FILES += \
./syscfg/Board.h 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"adcsinglechannel.obj" \
"syscfg\Board.obj" \
"debug.obj" \
"main_freertos.obj" \
"sensor_queue.obj" \
"sensor_state.obj" \
"timerone.obj" \
"timertwo.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\Board.h" 

C_DEPS__QUOTED += \
"adcsinglechannel.d" \
"syscfg\Board.d" \
"debug.d" \
"main_freertos.d" \
"sensor_queue.d" \
"sensor_state.d" \
"timerone.d" \
"timertwo.d" 

GEN_FILES__QUOTED += \
"syscfg\Board.c" 

C_SRCS__QUOTED += \
"../adcsinglechannel.c" \
"./syscfg/Board.c" \
"../debug.c" \
"../main_freertos.c" \
"../sensor_queue.c" \
"../sensor_state.c" \
"../timerone.c" \
"../timertwo.c" 

SYSCFG_SRCS__QUOTED += \
"../adcsinglechannel.syscfg" 


