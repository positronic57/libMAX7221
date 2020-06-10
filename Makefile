#Makefile that builds libMAX7221 library for 8-bit AVR MCU.

#Library name
LIBRARY_NAME = libMAX7221

#AVR Microcontroller
ifdef mcu
	MCU = $(mcu) 
else
	MCU = atmega32
endif

#CPU frequency 
ifndef cpu_freq
	CPU_FREQ = 4000000L
else
	CPU_FRQE = $(cpu_freq)
endif

#Source files
SOURCES += MAX7221.c

#List of object files
OBJECTS += $(SOURCES:.c=.o)

#Library header file
HEADER += MAX7221.h

#Library installation folder
ifdef prefix
	PREFIX = $(prefix)
else
	PREFIX = /usr/local
endif

#Define C compiler flags
override CFLAGS = -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=$(MCU) -DF_CPU=$(CPU_FREQ)

#Define avr-ar options
override ARAGS = rcs


all: $(LIBRARY_NAME).a

$(SOURCES): $(HEADER)

#Compile all of the source files
$(OBJECTS): $(SOURCES)
	@echo Compiling file: $<
	avr-gcc $(CFLAGS) -c $^ -o $@
	@echo

#Builing the library
$(LIBRARY_NAME).a: $(OBJECTS)
	@echo Building target file: $@. 
	avr-ar $(ARAGS) $@ $^

#Install the library
install: $(LIBRARY_NAME).a
	if [ ! -d $(PREFIX)/lib/avr8/$(MCU) ]; then mkdir -p $(PREFIX)/lib/avr8/$(MCU); fi
	if [ ! -d $(PREFIX)/include/avr8 ]; then mkdir -p $(PREFIX)/include/avr8; fi
	install -m 0644 $(LIBRARY_NAME).a $(PREFIX)/lib/avr8/$(MCU)
	install -m 0644 $(HEADER) $(PREFIX)/include/avr8

#Uninstall the library	
.PHONY: uninstall
uninstall:
	rm $(PREFIX)/lib/avr8/$(MCU)/$(LIBRARY_NAME).a
	rm $(PREFIX)/include/avr8/$(HEADER)

.PHONY: clean
clean:
	rm -f $(LIBRARY_NAME).a $(OBJECTS)

