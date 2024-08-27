################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
dsplib/source/transform/%.obj: ../dsplib/source/transform/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"E:/TI_CCS_IDE/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="E:/TI_Borad/MSP432/adc0_singleended_multichannel_timertrigger_dmareq_MSP_EXP432E401Y_nortos_ccs2/dsplib/include" --include_path="E:/TI_Borad/MSP432/ds_0_copy_FINAL" --include_path="E:/TI_Borad/simplelink_msp432e4_sdk_4_20_00_12/source" --include_path="E:/TI_Borad/simplelink_msp432e4_sdk_4_20_00_12/source/third_party/CMSIS/Include" --include_path="E:/TI_Borad/simplelink_msp432e4_sdk_4_20_00_12/source/ti/net/bsd" --include_path="E:/TI_CCS_IDE/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=none --define=_MPU_ENABLE --define=DeviceFamily_MSP432E4 --define=__MSP432E401Y__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="dsplib/source/transform/$(basename $(<F)).d_raw" --obj_directory="dsplib/source/transform" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


