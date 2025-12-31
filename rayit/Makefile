.RECIPEPREFIX = |

BUILD_TYPE ?= debug
VERBOSE ?= false

ifeq ($(VERBOSE),false)
  Q := @
else ifeq ($(VERBOSE),true)
  Q := 
endif                           # TODO: handle invalid VERBOSE input

CXX := ccache g++
CXXFLAGS := -std=c++26 -Wall -Wextra -pedantic
DEPFLAGS := -MMD -MP -MF
LDFLAGS := 

ifeq ($(BUILD_TYPE),debug)
  CXXFLAGS += -ggdb -O0 -DWARNING_ENABLED -DDEBUG_ENABLED
else ifeq ($(BUILD_TYPE),release)
  CXXFLAGS += -O3
else ifeq ($(BUILD_TYPE),sane)
  CXXFLAGS += -ggdb3 -O1 -fsanitize=address,leak,undefined,pointer-overflow,   \
              pointer-compare,pointer-subtract -fno-omit-frame-pointer         \
              -DWARNING_ENABLED -DDEBUG_ENABLED
endif

BUILD_DIR := build/$(BUILD_TYPE)
TARGET := $(BUILD_DIR)/rayit
TARGET_SOURCES := $(wildcard *.cc)
TARGET_OBJECTS := $(addprefix $(BUILD_DIR)/,$(TARGET_SOURCES:.cc=.o))

.PHONY: all clean prepare build

all: build
build: $(TARGET)

prepare:
|@ echo "Preparing for compilation..."
|$(Q) mkdir -p $(BUILD_DIR)/

$(TARGET): $(TARGET_OBJECTS)
|@ echo "[Link $^ ==> $@]"
|$(Q) $(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cc | prepare
|@ echo "[Compile $< ==> $@]"
|$(Q) $(CXX) $(CXXFLAGS) $(DEPFLAGS) $(@:.o=.o.dep) -c -o $@ $<

clean:
|@ echo "Cleaning build files..."
|$(Q) rm -rf build/

-include $(TARGET_DEPS)
