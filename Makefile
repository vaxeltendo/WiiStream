include $(DEVKITPPC)/wii_rules

TARGET      := boot
BUILD       := build
SOURCES     := .
DATA        := 

CFLAGS      := -g -O2 -Wall $(MACHDEP) -I$(DEVKITPRO)/libogc/include
CXXFLAGS    := $(CFLAGS)

LDFLAGS     := -g $(MACHDEP) -L$(DEVKITPRO)/libogc/lib/wii
LIBS        := -lwiiuse -lbte -logc -lm

ifneq ($(BUILD),$(canonical_build))

export OUTPUT   := $(CURDIR)/$(TARGET)
export VPATH    := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR  := $(CURDIR)/$(BUILD)

CFILES      := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
OBJS        := $(addprefix $(BUILD)/,$(CFILES:.c=.o))

export LD   := $(CC)

.PHONY: all clean

all: $(BUILD) $(OUTPUT).dol

$(BUILD):
	@[ -d $@ ] || mkdir -p $@

$(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT).elf: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

clean:
	rm -rf $(BUILD) $(TARGET).elf $(TARGET).dol

include $(DEVKITPPC)/base_rules

endif
