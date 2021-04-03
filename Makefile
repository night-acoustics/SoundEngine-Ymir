
# https://opensource.com/article/18/8/what-how-makefile


# target: prerequisites
# <TAB> recipe
upload: build   
# sudo is for getting access to the the burner.
# avrdude is the software used to upload.
# -c usbasp denotes the burner. 
# -p ATMEGA32 denotes the processer
# -U ./blink.bin is the file name and path to upload to the processor
	sudo avrdude  -c usbasp -p ATMEGA32 -U ./noise.bin 
build:  
# avr-gcc is the compiler
# -mcu=atmega32 denotes the processer we are compiling for.
# ***.c denotes the file we need to compile. 
# -0s 
# -0 blink.bin is output.
	avr-gcc -mmcu=atmega32 noise.c -Os -o noise.bin
