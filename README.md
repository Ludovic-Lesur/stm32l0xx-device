# Description

This repository contains the **startup code and linker scripts** of the STM32L0xx MCUs.

# Dependencies

The drivers rely on:

* An external `types.h` header file defining the **standard C types** of the targeted MCU.
* The `main` application function which is called at the end of the **reset handler**.

# Compilation flags

| **Flag name** | **Value** | **Description** |
|:---:|:---:|:---:|
| `STM32L0XX_DEVICE_DISABLE_FLAGS_FILE` | `defined` / `undefined` | Disable the `stm32l0xx_device_flags.h` header file inclusion when compilation flags are given in the project settings or by command line. |
| `STM32L0XX_DEVICE_DISABLE` | `defined` / `undefined` | Disable the STM32L0xx device code. |
| `STM32L0XX_DEVICE_STACK_SIZE` | `<value>` | Size of the stack to reserve in RAM memory. |
| `STM32L0XX_DEVICE_HEAP_SIZE` | `<value>` | Size of the heap to reserve in RAM memory. |

## Build

A static library can be compiled by command line with `cmake`.

```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE="<toolchain_file_path>" \
      -DTOOLCHAIN_PATH="<arm-none-eabi-gcc_path>" \
      -DTYPES_PATH="<types_file_path>" \
      -DEMBEDDED_UTILS_PATH="<embedded-utils_path>" \
      -DSTM32L0XX_DEVICE_STACK_SIZE=0x00000400 \
      -DSTM32L0XX_DEVICE_HEAP_SIZE=0x00000C00 \
      -G "Unix Makefiles" ..
make all
```