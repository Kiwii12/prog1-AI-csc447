# Template C++ makefile
# 
# Daniel Andrus (used with permission from author)
# Version 1.0


## This is where a target gets it's source files
SOURCE_FILES_ANN = ANNtrain.cpp C_Net.cpp Input.cpp

CPP_COMPILER=g++
CPP_LINKER=g++
CPP_COMPILE_FLAGS=-std=c++11
CPP_LINK_FLAGS=-std=c++11

# NOTICE build directory must be set in object targets

BUILD_DIR=.
SOURCE_DIR=.



# EDIT set custom program name

#Target is the program name
ANNtrain: $(addprefix $(BUILD_DIR)/, $(SOURCE_FILES_ANN:.cpp=.o))
	$(CPP_LINKER) $(CPP_LINK_FLAGS) -o $@ $^
	



# EDIT custom build directory

#first part of next line is the build directory
./%.o: $(addprefix $(SOURCE_DIR)/, %.cpp)
	@mkdir -p $(BUILD_DIR)
	$(CPP_COMPILER) $(CPP_COMPILE_FLAGS) -c -o $@ $<

clean:
	@rm -f $(addprefix $(BUILD_DIR)/, $(ANN_Train:.cpp=.o))
	@rm -f ANNtrain