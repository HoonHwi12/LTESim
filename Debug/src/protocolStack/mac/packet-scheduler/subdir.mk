################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/protocolStack/mac/packet-scheduler/delay-edd-rule-downlink-packet-scheduler.cpp \
../src/protocolStack/mac/packet-scheduler/dl-exp-packet-scheduler.cpp \
../src/protocolStack/mac/packet-scheduler/dl-fls-packet-scheduler.cpp \
../src/protocolStack/mac/packet-scheduler/dl-mlwdf-packet-scheduler.cpp \
../src/protocolStack/mac/packet-scheduler/dl-pf-packet-scheduler.cpp \
../src/protocolStack/mac/packet-scheduler/downlink-packet-scheduler.cpp \
../src/protocolStack/mac/packet-scheduler/enhanced-uplink-packet-scheduler.cpp \
../src/protocolStack/mac/packet-scheduler/exp-rule-downlink-packet-scheduler.cpp \
../src/protocolStack/mac/packet-scheduler/log-rule-downlink-packet-scheduler.cpp \
../src/protocolStack/mac/packet-scheduler/mt-uplink-packet-scheduler.cpp \
../src/protocolStack/mac/packet-scheduler/mw-rule-downlink-packet-scheduler.cpp \
../src/protocolStack/mac/packet-scheduler/packet-scheduler.cpp \
../src/protocolStack/mac/packet-scheduler/roundrobin-uplink-packet-scheduler.cpp \
<<<<<<< HEAD
../src/protocolStack/mac/packet-scheduler/uplink-packet-scheduler.cpp \
../src/protocolStack/mac/packet-scheduler/dqn-packet-scheduler.cpp 
=======
../src/protocolStack/mac/packet-scheduler/uplink-packet-scheduler.cpp 
>>>>>>> ad05299149aa732f4d064f67e737dda4046b36a9

OBJS += \
./src/protocolStack/mac/packet-scheduler/delay-edd-rule-downlink-packet-scheduler.o \
./src/protocolStack/mac/packet-scheduler/dl-exp-packet-scheduler.o \
./src/protocolStack/mac/packet-scheduler/dl-fls-packet-scheduler.o \
./src/protocolStack/mac/packet-scheduler/dl-mlwdf-packet-scheduler.o \
./src/protocolStack/mac/packet-scheduler/dl-pf-packet-scheduler.o \
./src/protocolStack/mac/packet-scheduler/downlink-packet-scheduler.o \
./src/protocolStack/mac/packet-scheduler/enhanced-uplink-packet-scheduler.o \
./src/protocolStack/mac/packet-scheduler/exp-rule-downlink-packet-scheduler.o \
./src/protocolStack/mac/packet-scheduler/log-rule-downlink-packet-scheduler.o \
./src/protocolStack/mac/packet-scheduler/mt-uplink-packet-scheduler.o \
./src/protocolStack/mac/packet-scheduler/mw-rule-downlink-packet-scheduler.o \
./src/protocolStack/mac/packet-scheduler/packet-scheduler.o \
./src/protocolStack/mac/packet-scheduler/roundrobin-uplink-packet-scheduler.o \
<<<<<<< HEAD
./src/protocolStack/mac/packet-scheduler/uplink-packet-scheduler.o \
./src/protocolStack/mac/packet-scheduler/dqn-packet-scheduler.o 
=======
./src/protocolStack/mac/packet-scheduler/uplink-packet-scheduler.o 
>>>>>>> ad05299149aa732f4d064f67e737dda4046b36a9

CPP_DEPS += \
./src/protocolStack/mac/packet-scheduler/delay-edd-rule-downlink-packet-scheduler.d \
./src/protocolStack/mac/packet-scheduler/dl-exp-packet-scheduler.d \
./src/protocolStack/mac/packet-scheduler/dl-fls-packet-scheduler.d \
./src/protocolStack/mac/packet-scheduler/dl-mlwdf-packet-scheduler.d \
./src/protocolStack/mac/packet-scheduler/dl-pf-packet-scheduler.d \
./src/protocolStack/mac/packet-scheduler/downlink-packet-scheduler.d \
./src/protocolStack/mac/packet-scheduler/enhanced-uplink-packet-scheduler.d \
./src/protocolStack/mac/packet-scheduler/exp-rule-downlink-packet-scheduler.d \
./src/protocolStack/mac/packet-scheduler/log-rule-downlink-packet-scheduler.d \
./src/protocolStack/mac/packet-scheduler/mt-uplink-packet-scheduler.d \
./src/protocolStack/mac/packet-scheduler/mw-rule-downlink-packet-scheduler.d \
./src/protocolStack/mac/packet-scheduler/packet-scheduler.d \
./src/protocolStack/mac/packet-scheduler/roundrobin-uplink-packet-scheduler.d \
<<<<<<< HEAD
./src/protocolStack/mac/packet-scheduler/uplink-packet-scheduler.d \
./src/protocolStack/mac/packet-scheduler/dqn-packet-scheduler.d 
=======
./src/protocolStack/mac/packet-scheduler/uplink-packet-scheduler.d 
>>>>>>> ad05299149aa732f4d064f67e737dda4046b36a9


# Each subdirectory must supply rules for building sources it contributes
src/protocolStack/mac/packet-scheduler/%.o: ../src/protocolStack/mac/packet-scheduler/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-4.8 -w -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


