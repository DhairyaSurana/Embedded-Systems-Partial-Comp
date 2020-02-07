################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/Dhairya Surana/c language/Embedded Systems/adcsinglechannel_CC3220SF_LAUNCHXL_freertos_ccs_syscfg" --include_path="C:/Users/Dhairya Surana/c language/Embedded Systems/adcsinglechannel_CC3220SF_LAUNCHXL_freertos_ccs_syscfg/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/posix/ccs" --include_path="C:/FreeRTOS/FreeRTOS/Source/include" --include_path="C:/FreeRTOS/FreeRTOS/Source/portable/CCS/ARM_CM3" --include_path="C:/Users/Dhairya Surana/c language/Embedded Systems/freertos_builds_CC3220SF_LAUNCHXL_release_ccs" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/include" --define=SF_DEBUG -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/Dhairya Surana/c language/Embedded Systems/adcsinglechannel_CC3220SF_LAUNCHXL_freertos_ccs_syscfg/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-159377375:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-159377375-inproc

build-159377375-inproc: ../adcsinglechannel.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs930/ccs/utils/sysconfig/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_3_20_00_06/.metadata/product.json" -o "syscfg" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/Board.c: build-159377375 ../adcsinglechannel.syscfg
syscfg/Board.h: build-159377375
syscfg/: build-159377375

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/Dhairya Surana/c language/Embedded Systems/adcsinglechannel_CC3220SF_LAUNCHXL_freertos_ccs_syscfg" --include_path="C:/Users/Dhairya Surana/c language/Embedded Systems/adcsinglechannel_CC3220SF_LAUNCHXL_freertos_ccs_syscfg/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/posix/ccs" --include_path="C:/FreeRTOS/FreeRTOS/Source/include" --include_path="C:/FreeRTOS/FreeRTOS/Source/portable/CCS/ARM_CM3" --include_path="C:/Users/Dhairya Surana/c language/Embedded Systems/freertos_builds_CC3220SF_LAUNCHXL_release_ccs" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/include" --define=SF_DEBUG -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/Dhairya Surana/c language/Embedded Systems/adcsinglechannel_CC3220SF_LAUNCHXL_freertos_ccs_syscfg/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


