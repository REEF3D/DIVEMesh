TARGET   := DiveMESH
CXX      := -g++
CXXFLAGS := -std=c++17
LDFLAGS  := 

OPENMP ?= 0

ifeq ($(OPENMP),1)
CXXFLAGS += -fopenmp
LDFLAGS += -fopenmp
endif

OBJ_DIR  := ./build
APP_DIR  := ./bin
SRC      := $(wildcard src/*.cpp)
OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all clean debug info

all: CXXFLAGS += -w -O3
all: $(APP_DIR)/$(TARGET)

debug: CXXFLAGS += -O0 -w -g -g3
debug: $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

info:
	@echo "[*] Application dir: ${APP_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
