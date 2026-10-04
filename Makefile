ifneq ($(BUILD),$(canonical_build))

include $(DEVKITPPC)/wii_rules

TARGET      := boot
BUILD       := build
SOURCES     := .
DATA        := 

CFLAGS      := -g -O2 -Wall -mrvl -mcpu=750 -meabi -mhard-float -I$(DEVKITPRO)/libogc/include
CXXFLAGS    := $(CFLAGS)

LDFLAGS     := -g -mrvl -mcpu=750 -meabi -mhard-float -L$(DEVKITPRO)/libogc/lib/wii
LIBS        := -lwiiuse -lbte -logc -lm

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
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT).elf: $(OBJS)
	@echo "Enlazando ELF..."
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

$(OUTPUT).dol: $(OUTPUT).elf
	@echo "Convertidor ELF a DOL..."
	elf2dol $< $@

clean:
	rm -rf $(BUILD) $(TARGET).elf $(TARGET).dol

include $(DEVKITPPC)/base_rules

endif
