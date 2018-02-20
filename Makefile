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
TEST_BIN=$(BIN_DIR)/test

# INCLUDES, LIBS
LIB_DIRS=

OPT=-O0
CXXFLAGS=-Wall -g2 -pthread -D_REENTRANT -std=c++11 $(OPT)
TESTFLAGS=-lgtest -lgtest_main
LDFLAGS =$(shell root-config --ldflags) -pthread
LIBS = 
TEST_LIBS = -lgtest -lgtest_main

# Pass debug options to pre-processor
DEBUG_OPTS = 
CFLAGS += $(DEBUG_OPTS)

.PHONY: clean

# Sources 
SOURCES       := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SOURCES  := $(wildcard $(TEST_DIR)/*.cpp)
OBJECTS       := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJECTS  := $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Generic target 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Unit test objects
$(TEST_OBJECTS): $(OBJ_DIR)/%.o : $(TEST_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@ 
	@echo "Compiled test object "$<""


# Targets for example programs 
hello: $(OBJECTS)
	$(CXX) $(LDFLAGS) \
		$(OBJ_DIR)/hello.o \
		$(INCS) \
		-o $(TEST_BIN)/hello $(TEST_LIBS) $(LIBS)

basic_thread: $(OBJECTS)
	$(CXX) $(LDFLAGS) \
	$(OBJ_DIR)/basic_thread.o \
	$(INCS) \
	-o $(TEST_BIN)/basic_thread $(TEST_LIBS) $(LIBS)


list_mutex: $(OBJECTS)
	$(CXX) $(LDFLAGS) \
	$(OBJ_DIR)/list_mutex.o \
	$(INCS) \
	-o $(TEST_BIN)/list_mutex $(TEST_LIBS) $(LIBS)

thread_stack: $(OBJECTS)
	$(CXX) $(LDFLAGS) \
	$(OBJ_DIR)/thread_stack.o \
	$(INCS) \
	-o $(TEST_BIN)/thread_stack $(TEST_LIBS) $(LIBS)




clean:
	rm -rfv *.o $(OBJ_DIR)/*.o 
	# Remove test binaries 
	#ifneq ("$(wildcard $(TEST_BIN)/test_*)", "")
	rm -vf $(TEST_BIN)/*

print-%:
	@echo $* = $($*)

