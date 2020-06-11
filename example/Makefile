#Makefile for bor building the examples distributed 
#with libMAX7221 libarary.

#AVR Microcontroller
ifdef mcu
	MCU = $(mcu)
else
	MCU = atmega328p
endif

#CPU frequency  (must be the same as the value used while building libMAX7221).
ifdef cpu_freq
	CPU_FREQ = $(cpu_freq)
else
	CPU_FREQ = 4000000L
endif

#Header files path (Update this with the library installation folder).
HEADERS_PATH = /usr/local/include/avr8

#Library path
LIBRARY_PATH = /usr/local/lib/avr8/$(MCU)

#List of source files
SOURCES += libMAX7221example.c libMAX7221example2.c

#List of object files
OBJECTS += $(SOURCES:.c=.o)

#Define C compiler flags
override CFLAGS = -Wall -I$(HEADERS_PATH) -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=$(MCU) -DF_CPU=$(CPU_FREQ)

.PHONY: libMAX7221example
.PHONY: libMAX7221example2

libMAX7221example: libMAX7221example.hex
libMAX7221example2: libMAX7221example2.hex


all: libMAX7221example libMAX7221example2

#Compile all of the source files
%.o: %.c
	@echo Compiling file: $<
	avr-gcc $(CFLAGS) -c $^ -o $@
	@echo

#Generate libMAX7221example ELF file from the object files using linker
libMAX7221example.elf: libMAX7221example.o
	@echo Building target file: $@. 
	avr-gcc -Wl,-Map,libMAX7221example.map -mmcu=$(MCU) -o $@ $^ -L$(LIBRARY_PATH) -lMAX7221
	@echo 
	@echo $@ memory footprint:
	avr-size --format=avr --mcu=$(MCU) $@

#Generate libMAX7221example2 ELF file from the object files using linker
libMAX7221example2.elf: libMAX7221example2.o
	@echo Building target file: $@. 
	avr-gcc -Wl,-Map,libMAX7221example2.map -mmcu=$(MCU) -o $@ $^ -L$(LIBRARY_PATH) -lMAX7221 
	@echo 
	@echo $@ memory footprint:
	avr-size --format=avr --mcu=$(MCU) $@

#Generate HEX files
libMAX7221example.hex: libMAX7221example.elf
	@echo Creating object file in ihex format.
	avr-objcopy -j .text -j .data -O ihex $< $@
	@echo

libMAX7221example2.hex: libMAX7221example2.elf
	@echo Creating object file in ihex format.
	avr-objcopy -j .text -j .data -O ihex $< $@
	@echo

.PHONY: clean

clean:
	rm -f *.o *.elf *.hex *.map
 
