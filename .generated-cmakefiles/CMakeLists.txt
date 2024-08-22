
# This file must be called once in the generate phase with MPLAB_PROJECT_NAME, MPLAB_CONF_NAME and MPLAB_IMAGE_NAME defined
if ((NOT DEFINED MPLAB_PROJECT_NAME) AND (NOT DEFINED CACHE{MPLAB_PROJECT_NAME}))
  message(FATAL_ERROR "MPLAB_PROJECT_NAME must be defined. Add -DPROJECT_NAME=XXX")
endif()
if ((NOT DEFINED MPLAB_CONF_NAME) AND (NOT DEFINED CACHE{MPLAB_CONF_NAME}))
  message(FATAL_ERROR "MPLAB_CONF_NAME must be defined. Add -DMPLAB_CONF_NAME=XXX")
endif()
if ((NOT DEFINED MPLAB_IMAGE_NAME) AND (NOT DEFINED CACHE{MPLAB_IMAGE_NAME}))
  message(FATAL_ERROR "MPLAB_IMAGE_NAME must be defined. Add  -DIMAGE_NAME=XXX")
endif()

set(OVERRIDES_CMAKE "/Users/rcaratti/Desenvolvimento/eu/Arduino/DSP/QN8066/QN8066_PIC16F/.generated-cmakefiles/${MPLAB_PROJECT_NAME}/${MPLAB_CONF_NAME}/image_${MPLAB_IMAGE_NAME}/overrides.cmake")
if(EXISTS ${OVERRIDES_CMAKE})
    set(CMAKE_USER_MAKE_RULES_OVERRIDE ${OVERRIDES_CMAKE})
endif()

set(MAIN_CMAKE "/Users/rcaratti/Desenvolvimento/eu/Arduino/DSP/QN8066/QN8066_PIC16F/.generated-cmakefiles/${MPLAB_PROJECT_NAME}/${MPLAB_CONF_NAME}/image_${MPLAB_IMAGE_NAME}/main.cmake")
cmake_minimum_required(VERSION 3.17)
set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_TOOLCHAIN_FILE "/Users/rcaratti/Desenvolvimento/eu/Arduino/DSP/QN8066/QN8066_PIC16F/.generated-cmakefiles/${MPLAB_PROJECT_NAME}/${MPLAB_CONF_NAME}/image_${MPLAB_IMAGE_NAME}/toolchain.cmake")
project(${MPLAB_IMAGE_NAME} LANGUAGES  C ASM )
include(${MAIN_CMAKE})
