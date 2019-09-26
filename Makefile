# CONCURRENT DATA STRUCTURES 
# Makefile for theading projects
# These will use std::thread, but pthread is 
# stil required as a linking option
#
# Stefan Wong 2018

# OUTPUT DIRS
BIN_DIR=bin
OBJ_DIR=obj
SRC_DIR=src
TEST_DIR=test
# Directory for standalone programs
PROGRAM_DIR=programs
TEST_BIN=$(BIN_DIR)/test

# INCLUDES, LIBS
LIB_DIRS=

# Flags
OPT=-O0
CXXFLAGS=-Wall -g2 -pthread -D_REENTRANT -std=c++11 $(OPT)
TESTFLAGS=-lgtest -lgtest_main
LDFLAGS =$(shell root-config --ldflags) -pthread
LIBS = 
TEST_LIBS = -lgtest -lgtest_main

# Pass debug options to pre-processor
DEBUG_OPTS = 
CFLAGS += $(DEBUG_OPTS)


# Sources 
INCS          := -I$(SRC_DIR)
SOURCES       := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SOURCES  := $(wildcard $(TEST_DIR)/*.cpp)
OBJECTS       := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJECTS  := $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Generic target 
$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Unit test objects
$(TEST_OBJECTS): $(OBJ_DIR)/%.o : $(TEST_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@ 
	@echo "Compiled test object "$<""


# ==== PROGRAMS ==== #
PROGRAMS=hello basic_thread list_mutex thread_stack thread_queue

PROGRAM_SRC := $(wildcard $(PROGRAM_DIR)/*.cpp)
PROGRAM_OBJ := $(PROGRAM_SRC:$(PROGRAM_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# generic build target for programs 
$(PROGRAM_OBJ) : $(OBJ_DIR)/%.o : $(PROGRAM_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

$(PROGRAMS) : $(OBJECTS) $(PROGRAM_OBJ)
	$(CXX) $(LDFLAGS) $(OBJ_DIR)/$@.o -o $(BIN_DIR)/$@ $(LIBS)


# ==== TESTS ==== #


# Targets for example programs 
.PHONY: clean

all : programs

programs : $(PROGRAMS)

# TODO : if tests actually get written then put a test target here.


clean:
	rm -rfv *.o $(OBJ_DIR)/*.o 
	# Remove test binaries 
	rm -vf $(BIN_DIR)/*
	#rm -vf $(TEST_BIN)/*		# When there are test binaries, this will remove them.

print-%:
	@echo $* = $($*)

