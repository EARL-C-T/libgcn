# libGCN #
### BY EARL T (ET) ###
===
#### CREDIT TO [ED WILLIAMS] ('https://edwilliams.org/avform147.htm') ####
***MOST OF THESE FORMULAS ORIGINATED THERE AS DID THE IDEA FOR THIS LIBARY ***
----
## GOAL ##
____
* TO MAKE A SMALL SHARED LIB FOR GREAT CIRCLE NAV THAT HAS FEW DEPENDENCIES :
  1) **MATH.H** *FOR MOST FUNCTIONS*
  2) **FLOAT.H** *CURENTLY JUST FOR DBL_ESPILON MAY RM**
  3) **STDIO.H** *FOR PRINTF IDK*
  4) **ERRNO.H** *ERRORS WILL RM*
* TO MAKE INTO A CROSS-COMPILEING LIB MENT FOR USE IN EMBEDED SYSTEMS
  1) **AVR** FIRST TARGET
  2)  **ESP32** I KNOW NEED TO MAKE IT WORK ON 32 BIT
  3)  **RISCV**
  4)  **STM**
  5)  **ETC**
* THIS IS A WIP AND IM STILL NEW TO C ANY HELP OR ADVICE WOULD BE GREAT
## INSTALL ##
*************
OK THIS IS KINDA SUPER BARE BONES BUT RUN build.sh THEN SUDO install.sh 
COMPILES TO A SHARED LIBARY AND  INSTALLS HEADER IN /usr/include AND LIB 
IN /usr/lib 

IM ALSO BOUT TO ADD A AVR STATIC THAT SHOULD COMPILE AND ARCIVE TO A STATIC 
LIB FOR AVR IT WONT INSTALL ANYWERE JUST SO YA CAN ADD IT IN AS A LIBARY 
AVR ONLY DOSE STATIC IF YA 
