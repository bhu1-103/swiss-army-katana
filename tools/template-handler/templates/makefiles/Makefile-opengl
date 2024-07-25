CXX = g++
CXXFLAGS = -Wall -g -I$(SRC_DIR)
SRC_DIR = source
BUILD_DIR = build
TARGET = pls-work
SRCS = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
LDFLAGS = -lGL -lGLU -lglut -lGLEW -lglfw

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean

