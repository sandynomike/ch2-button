# Blue Pill Challeng 1: Blinky

This project contains the code required to blink the built-in LED on the Blue Pill.

<br>
Wiring<br>
No wiring other than the programming interface is required!<br>
<br>
Setup<br>
The default makefile is set up to work with an ST-LINK V2 programming dongle under Linux. For other
setups, open Makefile and edit as required. There are hints in the Makefile for different programming
options.
<br>
Running make will compile and attempt to upload the program to the Blue Pill. Of course the resulting .elf
file can be uploaded manually later.<br>
Requires:<br>
<hr>
Editor of your choice<br>
arm-none-eabi-gcc toolchain<br>
make<br>
git-bash (for windows)<br>
STM32_Programmer_CLI.exe Program to upload .elf file to the microcontroller / Blue Pill<br>
