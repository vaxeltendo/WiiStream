FEAT_FLAGS := 

include $(DEVKITPPC)/wii_rules

TARGET      := boot
BUILD       := build
SOURCES     := .
DATA        := 
INCLUDES    := 

CFLAGS      := -g -O2 -Wall $(FEAT_FLAGS)
CXXFLAGS    := $(CFLAGS)

LDFLAGS     := -g $(FEAT_FLAGS)
LIBS        := -lwiiuse -lbte -logc -lm

ifneq ($(BUILD),$(canonical_build))
export OUTPUT   := $(CURDIR)/$(TARGET)
export VPATH    := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR  := $(CURDIR)/$(BUILD)

CFILES      := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
OBJS        := $(CFILES:.c=.o)

export LD   := $(CC)

all: $(BUILD) $(OUTPUT).dol

$(BUILD):
	@[ -d $@ ] || mkdir -p $@

$(OUTPUT).dol: $(OUTPUT).elf

clean:
	rm -rf $(BUILD) $(TARGET).elf $(TARGET).dol

include $(DEVKITPPC)/base_rules

endif
