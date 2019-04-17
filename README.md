# arm_usb_communication
#
# OPENOCD
# openocd -f board/stm32f429discovery.cfg
#
# GDB
# $arm-none-eabi-gdb
# $gdb-multiarch 
# $gdb-multiarch -tui
# 
# (gdb) set arch arm
# (gdb) tui enable
# (gdb) tui disable
# (gdb) layout src
# (gdb) layout regs
#
# (gdb) target remote localhost:3333
# (gdb) monitor reset halt
# (gdb) monitor arm semihosting enable
#
# (gdb) monito flash probe 0
# (gdb) monitor stm32f4x mass_erase 0
#
# (gdb) monitor reset run
#
# monitor flash write_image erase stm32f4_blink.bin 0x08000000
# monitor flash write_image erase /path/to/file/stm32f4_sample.hex
#
# set remotetimeout 2000
# show remotetimeout
