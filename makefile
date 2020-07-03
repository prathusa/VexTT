# VEXcode makefile 2019_03_26_01

# show compiler output
VERBOSE = 0

# include toolchain options
include vex/mkenv.mk

# location of the project source cpp and c files
SRC_C  = $(wildcard *.cpp) 
SRC_C += $(wildcard *.c)
SRC_C += $(wildcard */*.cpp) 
SRC_C += $(wildcard */*.c)
SRC_C += $(wildcard */*/*.cpp) 
SRC_C += $(wildcard */*/*.c)
SRC_C += $(wildcard */*/*/*.cpp) 
SRC_C += $(wildcard */*/*/*.c)
SRC_C += $(wildcard */*/*/*/*.cpp) 
SRC_C += $(wildcard */*/*/*/*.c)
SRC_C += $(wildcard */*/*/*/*/*.cpp) 
SRC_C += $(wildcard */*/*/*/*/*.c)
SRC_C += $(wildcard */*/*/*/*/*/*.cpp) 
SRC_C += $(wildcard */*/*/*/*/*/*.c)
SRC_C += $(wildcard */*/*/*/*/*/*/*.cpp) 
SRC_C += $(wildcard */*/*/*/*/*/*/*.c)
SRC_C += $(wildcard */*/*/*/*/*/*/*/*.cpp) 
SRC_C += $(wildcard */*/*/*/*/*/*/*/*.c)
SRC_C += $(wildcard */*/*/*/*/*/*/*/*/*.cpp) 
SRC_C += $(wildcard */*/*/*/*/*/*/*/*/*.c)
SRC_C += $(wildcard */*/*/*/*/*/*/*/*/*/*.cpp) 
SRC_C += $(wildcard */*/*/*/*/*/*/*/*/*/*.c)

OBJ = $(addprefix $(BUILD)/, $(addsuffix .o, $(basename $(SRC_C))) )

# location of include files that c and cpp files depend on
SRC_H  = $(wildcard *.h)
SRC_H  += $(wildcard */*.h)
SRC_H  += $(wildcard */*/*.h)
SRC_H  += $(wildcard */*/*/*.h)
SRC_H  += $(wildcard */*/*/*/*.h)
SRC_H  += $(wildcard */*/*/*/*/*.h)
SRC_H  += $(wildcard */*/*/*/*/*/*.h)
SRC_H  += $(wildcard */*/*/*/*/*/*/*.h)
SRC_H  += $(wildcard */*/*/*/*/*/*/*/*.h)
SRC_H  += $(wildcard */*/*/*/*/*/*/*/*/*.h)
SRC_H  += $(wildcard */*/*/*/*/*/*/*/*/*/*.h)
# Matplotlib's Files on Prath's PC dir
SRC_H  += $(C:/Users/prath/AppData/Roaming/Python/Python38/*.h)
SRC_H  += $(C:/Users/prath/AppData/Roaming/Python/Python38/*/*.h)
SRC_H  += $(C:/Users/prath/AppData/Roaming/Python/Python38/*/*/*.h)
SRC_H  += $(C:/Users/prath/AppData/Roaming/Python/Python38/*/*/*/*.h)
SRC_H  += $(C:/Users/prath/AppData/Roaming/Python/Python38/*/*/*/*/*.h)

# additional dependancies
SRC_A  = makefile

# project header file locations
INC_F  = include

# build targets
all: $(BUILD)/$(PROJECT).bin

# include build rules
include vex/mkrules.mk
