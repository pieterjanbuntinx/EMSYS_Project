# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/e/gitwerk/EMSYS_Project_ToF_sensor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.c.obj: ../main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/main.c.obj"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/main.c.obj   -c /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/main.c

CMakeFiles/main.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/main.c.i"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -E /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/main.c > CMakeFiles/main.dir/main.c.i

CMakeFiles/main.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/main.c.s"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -S /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/main.c -o CMakeFiles/main.dir/main.c.s

CMakeFiles/main.dir/main.c.obj.requires:
.PHONY : CMakeFiles/main.dir/main.c.obj.requires

CMakeFiles/main.dir/main.c.obj.provides: CMakeFiles/main.dir/main.c.obj.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.c.obj.provides.build
.PHONY : CMakeFiles/main.dir/main.c.obj.provides

CMakeFiles/main.dir/main.c.obj.provides.build: CMakeFiles/main.dir/main.c.obj

CMakeFiles/main.dir/main-cstartup.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main-cstartup.c.obj: ../main-cstartup.c
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/main-cstartup.c.obj"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/main-cstartup.c.obj   -c /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/main-cstartup.c

CMakeFiles/main.dir/main-cstartup.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/main-cstartup.c.i"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -E /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/main-cstartup.c > CMakeFiles/main.dir/main-cstartup.c.i

CMakeFiles/main.dir/main-cstartup.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/main-cstartup.c.s"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -S /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/main-cstartup.c -o CMakeFiles/main.dir/main-cstartup.c.s

CMakeFiles/main.dir/main-cstartup.c.obj.requires:
.PHONY : CMakeFiles/main.dir/main-cstartup.c.obj.requires

CMakeFiles/main.dir/main-cstartup.c.obj.provides: CMakeFiles/main.dir/main-cstartup.c.obj.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main-cstartup.c.obj.provides.build
.PHONY : CMakeFiles/main.dir/main-cstartup.c.obj.provides

CMakeFiles/main.dir/main-cstartup.c.obj.provides.build: CMakeFiles/main.dir/main-cstartup.c.obj

CMakeFiles/main.dir/main-start.s.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main-start.s.obj: ../main-start.s
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building ASM object CMakeFiles/main.dir/main-start.s.obj"
	/usr/bin/arm-none-eabi-gcc  $(ASM_DEFINES) $(ASM_FLAGS) -o CMakeFiles/main.dir/main-start.s.obj -c /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/main-start.s

CMakeFiles/main.dir/main-start.s.obj.requires:
.PHONY : CMakeFiles/main.dir/main-start.s.obj.requires

CMakeFiles/main.dir/main-start.s.obj.provides: CMakeFiles/main.dir/main-start.s.obj.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main-start.s.obj.provides.build
.PHONY : CMakeFiles/main.dir/main-start.s.obj.provides

CMakeFiles/main.dir/main-start.s.obj.provides.build: CMakeFiles/main.dir/main-start.s.obj

CMakeFiles/main.dir/rpi-gpio.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/rpi-gpio.c.obj: ../rpi-gpio.c
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/rpi-gpio.c.obj"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/rpi-gpio.c.obj   -c /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/rpi-gpio.c

CMakeFiles/main.dir/rpi-gpio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/rpi-gpio.c.i"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -E /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/rpi-gpio.c > CMakeFiles/main.dir/rpi-gpio.c.i

CMakeFiles/main.dir/rpi-gpio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/rpi-gpio.c.s"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -S /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/rpi-gpio.c -o CMakeFiles/main.dir/rpi-gpio.c.s

CMakeFiles/main.dir/rpi-gpio.c.obj.requires:
.PHONY : CMakeFiles/main.dir/rpi-gpio.c.obj.requires

CMakeFiles/main.dir/rpi-gpio.c.obj.provides: CMakeFiles/main.dir/rpi-gpio.c.obj.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/rpi-gpio.c.obj.provides.build
.PHONY : CMakeFiles/main.dir/rpi-gpio.c.obj.provides

CMakeFiles/main.dir/rpi-gpio.c.obj.provides.build: CMakeFiles/main.dir/rpi-gpio.c.obj

CMakeFiles/main.dir/rpi-interrupts.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/rpi-interrupts.c.obj: ../rpi-interrupts.c
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/rpi-interrupts.c.obj"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/rpi-interrupts.c.obj   -c /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/rpi-interrupts.c

CMakeFiles/main.dir/rpi-interrupts.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/rpi-interrupts.c.i"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -E /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/rpi-interrupts.c > CMakeFiles/main.dir/rpi-interrupts.c.i

CMakeFiles/main.dir/rpi-interrupts.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/rpi-interrupts.c.s"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -S /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/rpi-interrupts.c -o CMakeFiles/main.dir/rpi-interrupts.c.s

CMakeFiles/main.dir/rpi-interrupts.c.obj.requires:
.PHONY : CMakeFiles/main.dir/rpi-interrupts.c.obj.requires

CMakeFiles/main.dir/rpi-interrupts.c.obj.provides: CMakeFiles/main.dir/rpi-interrupts.c.obj.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/rpi-interrupts.c.obj.provides.build
.PHONY : CMakeFiles/main.dir/rpi-interrupts.c.obj.provides

CMakeFiles/main.dir/rpi-interrupts.c.obj.provides.build: CMakeFiles/main.dir/rpi-interrupts.c.obj

CMakeFiles/main.dir/rpi-uart.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/rpi-uart.c.obj: ../rpi-uart.c
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/rpi-uart.c.obj"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/rpi-uart.c.obj   -c /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/rpi-uart.c

CMakeFiles/main.dir/rpi-uart.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/rpi-uart.c.i"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -E /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/rpi-uart.c > CMakeFiles/main.dir/rpi-uart.c.i

CMakeFiles/main.dir/rpi-uart.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/rpi-uart.c.s"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -S /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/rpi-uart.c -o CMakeFiles/main.dir/rpi-uart.c.s

CMakeFiles/main.dir/rpi-uart.c.obj.requires:
.PHONY : CMakeFiles/main.dir/rpi-uart.c.obj.requires

CMakeFiles/main.dir/rpi-uart.c.obj.provides: CMakeFiles/main.dir/rpi-uart.c.obj.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/rpi-uart.c.obj.provides.build
.PHONY : CMakeFiles/main.dir/rpi-uart.c.obj.provides

CMakeFiles/main.dir/rpi-uart.c.obj.provides.build: CMakeFiles/main.dir/rpi-uart.c.obj

CMakeFiles/main.dir/rpi-i2c.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/rpi-i2c.c.obj: ../rpi-i2c.c
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/rpi-i2c.c.obj"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/rpi-i2c.c.obj   -c /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/rpi-i2c.c

CMakeFiles/main.dir/rpi-i2c.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/rpi-i2c.c.i"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -E /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/rpi-i2c.c > CMakeFiles/main.dir/rpi-i2c.c.i

CMakeFiles/main.dir/rpi-i2c.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/rpi-i2c.c.s"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -S /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/rpi-i2c.c -o CMakeFiles/main.dir/rpi-i2c.c.s

CMakeFiles/main.dir/rpi-i2c.c.obj.requires:
.PHONY : CMakeFiles/main.dir/rpi-i2c.c.obj.requires

CMakeFiles/main.dir/rpi-i2c.c.obj.provides: CMakeFiles/main.dir/rpi-i2c.c.obj.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/rpi-i2c.c.obj.provides.build
.PHONY : CMakeFiles/main.dir/rpi-i2c.c.obj.provides

CMakeFiles/main.dir/rpi-i2c.c.obj.provides.build: CMakeFiles/main.dir/rpi-i2c.c.obj

CMakeFiles/main.dir/VL53L0X.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/VL53L0X.c.obj: ../VL53L0X.c
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/VL53L0X.c.obj"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/VL53L0X.c.obj   -c /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/VL53L0X.c

CMakeFiles/main.dir/VL53L0X.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/VL53L0X.c.i"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -E /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/VL53L0X.c > CMakeFiles/main.dir/VL53L0X.c.i

CMakeFiles/main.dir/VL53L0X.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/VL53L0X.c.s"
	/usr/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_FLAGS) -S /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/VL53L0X.c -o CMakeFiles/main.dir/VL53L0X.c.s

CMakeFiles/main.dir/VL53L0X.c.obj.requires:
.PHONY : CMakeFiles/main.dir/VL53L0X.c.obj.requires

CMakeFiles/main.dir/VL53L0X.c.obj.provides: CMakeFiles/main.dir/VL53L0X.c.obj.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/VL53L0X.c.obj.provides.build
.PHONY : CMakeFiles/main.dir/VL53L0X.c.obj.provides

CMakeFiles/main.dir/VL53L0X.c.obj.provides.build: CMakeFiles/main.dir/VL53L0X.c.obj

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.c.obj" \
"CMakeFiles/main.dir/main-cstartup.c.obj" \
"CMakeFiles/main.dir/main-start.s.obj" \
"CMakeFiles/main.dir/rpi-gpio.c.obj" \
"CMakeFiles/main.dir/rpi-interrupts.c.obj" \
"CMakeFiles/main.dir/rpi-uart.c.obj" \
"CMakeFiles/main.dir/rpi-i2c.c.obj" \
"CMakeFiles/main.dir/VL53L0X.c.obj"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/main.c.obj
main: CMakeFiles/main.dir/main-cstartup.c.obj
main: CMakeFiles/main.dir/main-start.s.obj
main: CMakeFiles/main.dir/rpi-gpio.c.obj
main: CMakeFiles/main.dir/rpi-interrupts.c.obj
main: CMakeFiles/main.dir/rpi-uart.c.obj
main: CMakeFiles/main.dir/rpi-i2c.c.obj
main: CMakeFiles/main.dir/VL53L0X.c.obj
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Convert the ELF output file to a binary image"
	arm-none-eabi-objcopy ./main -O binary ./kernel.img

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/requires: CMakeFiles/main.dir/main.c.obj.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/main-cstartup.c.obj.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/main-start.s.obj.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/rpi-gpio.c.obj.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/rpi-interrupts.c.obj.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/rpi-uart.c.obj.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/rpi-i2c.c.obj.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/VL53L0X.c.obj.requires
.PHONY : CMakeFiles/main.dir/requires

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/gitwerk/EMSYS_Project_ToF_sensor /mnt/e/gitwerk/EMSYS_Project_ToF_sensor /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/build /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/build /mnt/e/gitwerk/EMSYS_Project_ToF_sensor/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

