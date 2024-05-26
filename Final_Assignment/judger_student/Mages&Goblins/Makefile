# Makefile -- for use in MacOS or Linux systems
# source object target
# only find the subdirectory
SRC	:= $(wildcard *.cpp)
OBJS :=	$(SRC:%.cpp=%.o)
HEADERS := $(wildcard *.h)

# path to cs1604, change it to yours
CS1604_INCLUDE := ../../../cs1604_lib/src/cs1604/include
CS1604_LIBDIR := ../../../cs1604_lib/src/cs1604/lib
CS1604_LIB := CS1604

# compile and lib parameter
CXX		:= g++
CXXFLAGS  = -O2 -Wall -std=c++11 -g
INCLUDE := -I $(CS1604_INCLUDE)
LIBDIR := -L $(CS1604_LIBDIR)
LIB := -l $(CS1604_LIB)

TARGET := mages_goblins

$(TARGET):$(OBJS)
	$(CXX) $^ -o $@ $(LIBDIR) $(LIB)

%.o:%.cpp
	$(CXX) ${CXXFLAGS} $(INCLUDE) -c $^ -o $@

# clean
clean:
	rm $(OBJS)
	rm $(TARGET)
