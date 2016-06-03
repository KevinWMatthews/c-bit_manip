# Set QUIET to @ to suppress folder creation and deletion
# Set SILENCE to @ to suppress compier output
# For the most complete silence, pass the -s option
QUIET = @
SILENCE = @



#############################
### Product Configuration ###
#############################
TARGET_NAME = BitManip

SRC_DIRS = src
INC_DIRS = inc
TEST_DIRS = test
BUILD_DIR = build
OBJECT_DIR = obj
CPPUTEST_HOME = /usr/local

CFLAGS += -Wfatal-errors
INCLUDE_FLAGS = $(addprefix -I, $(INC_DIRS))
TEST_INCLUDE_FLAGS = $(addprefix -I, $(TEST_DIRS))
CPPFLAGS += -I$(CPPUTEST_HOME)/include
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -l CppUTest -lCppUTestExt

C_COMPILER = gcc
CPP_COMPILER = g++
CFLAGS += -Wall
DEP_FLAGS = -MMD -MP

IGNORE_MAKEFILE_ERROR_ON_LINE = -



#######################
### Auto-generation ###
#######################
# Auto-generate list of source code
SRC = $(call get_c_src_from_dir_list, $(SRC_DIRS))
src_obj = $(call c_to_o, $(SRC))
SRC_OBJ = $(addprefix $(OBJECT_DIR)/, $(src_obj))
src_dep = $(call c_to_d, $(SRC))
SRC_DEP = $(addprefix $(OBJECT_DIR)/, $(src_dep))

# Auto-generate list of test code
TEST = $(call get_cpp_src_from_dir_list, $(TEST_DIRS))
test_obj = $(call cpp_to_o, $(TEST))
TEST_OBJ = $(addprefix $(OBJECT_DIR)/, $(test_obj))
test_dep = $(call cpp_to_d, $(TEST))
TEST_DEP = $(addprefix $(OBJECT_DIR)/, $(test_dep))

DEP_FILES = $(SRC_DEP) + $(TEST_DEP)

TARGET = $(BUILD_DIR)/$(TARGET_NAME)



########################
### Helper functions ###
########################
get_c_src_from_dir_list = $(foreach dir, $1, $(call get_c_src_from_dir, $(dir)))
get_c_src_from_dir = $(wildcard $1/*.c)
c_to_o = $(call convert_extension,.c,.o,$1)
c_to_d = $(call convert_extension,.c,.d,$1)

get_cpp_src_from_dir_list = $(foreach dir, $1, $(call get_cpp_src_from_dir, $(dir)))
get_cpp_src_from_dir = $(wildcard $1/*.cpp)
cpp_to_o = $(call convert_extension,.cpp,.o,$1)
cpp_to_d = $(call convert_extension,.cpp,.d,$1)

# $1 is the initial extension
# $2 is the final extension
# $3 is the file in question
convert_extension = $(patsubst %$1,%$2,$3)



ifneq ("(MAKECMDGOALS)","clean")
-include $(DEP_FILES)
endif



###########
# Targets #
###########
.PHONY: test rebuild clean

test: $(TARGET)
	@echo
	@echo Executing unit tests for: $(TARGET)
	$(IGNORE_MAKEFILE_ERROR_ON_LINE) $(SILENCE)./$(TARGET) -c

# Each product runs all product-specific tests as well as all general tests.
# This may not be the best approach; it won't scale well.
$(TARGET): $(SRC_OBJ) $(TEST_OBJ)
	$(SILENCE)$(QUIET)mkdir -p $(dir $@)
	$(SILENCE)$(CPP_COMPILER) -o $@ $(SRC_OBJ) $(TEST_OBJ) $(INCLUDE_FLAGS) $(CPPFLAGS) $(CXXFLAGS) $(LD_LIBRARIES)

# Compile test .cpp files
$(OBJECT_DIR)/%.o: %.cpp
	$(SILENCE)$(QUIET)mkdir -p $(dir $@)
	$(SILENCE)$(CPP_COMPILER) $(DEP_FLAGS) -o $@ -c $< $(CFLAGS) $(INCLUDE_FLAGS) $(TEST_INCLUDE_FLAGS)

# Compile source .c files
$(OBJECT_DIR)/%.o: %.c
	$(SILENCE)$(QUIET)mkdir -p $(dir $@)
	$(SILENCE)$(C_COMPILER) $(DEP_FLAGS) -o $@ -c $< $(CFLAGS) $(INCLUDE_FLAGS)

rebuild: clean test

clean:
	$(SILENCE)$(QUIET)rm -rf $(BUILD_DIR)
	$(SILENCE)$(QUIET)rm -rf $(OBJECT_DIR)
