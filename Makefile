#Makefile

CC = g++

UCFLAGS = -O3 -Wall -gstabs+ -std=c++0x

RUCFLAGS := $(shell root-config --cflags) -I./include/ -I/src/

LIBS := $(shell root-config --libs) -lTreePlayer
GLIBS := $(shell root-config --glibs)

VPATH = ./src/

SRCPP = Main.cpp\
        Plotter.cpp\
         
OBJCPP = $(patsubst %.cpp,obj/%.o,$(SRCPP))

all : run

obj/%.o : %.cpp
	@echo "[INFO]: Compiling... $*"
	@mkdir -p obj/
	@$(CC) -c $< $(UCFLAGS) $(RUCFLAGS) -o $@

run : $(OBJCPP)
	@echo "[INFO]: Linking..."
	@$(CC) $^ $(ACLIBS) $(LIBS) $(GLIBS)  -o $@

clean:
	@echo "[INFO]: Cleaning objects and executable..."
	@rm  -f obj/*.o
	@rm -f run
