include ./mk/env.mk
TARGET_NAME = spp_vf
TARGET = $(TARGET_NAME)_test
TEST_SRC_DIR = $(TARGET_NAME)
SRCS = $(TARGET_NAME)_test.c \
       $(TEST_SRC_DIR)/stub.c

OBJS = $(SRCS:.c=.o)
CFLAGS = $(DEFAULT_CFLAGS) -coverage -g -O0
CFLAGS += -I$(RTE_INCLUDE)
CFLAGS += -I./$(TEST_SRC_DIR)
CFLAGS += -I../
CFLAGS += -DUSE_UT_SPP_VF -DSPP_RINGLATENCYSTATS_ENABLE
LDFLAGS = $(DEFAULT_LDFLAGS)
LDLIBS = -ljansson -lcunit

COV_OBJS=$(SRCS:.c=.gcno)
COV_OBJS2=$(SRCS:.c=.gcda)
COV_OUT = $(TEST_SRC_DIR)/coverage

.PHONY: all clean
all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "[LD]$@..."
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	chmod +x run_$(TARGET).sh

%.o: %.c
	@echo "[CC]$<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(COV_OBJS) $(COV_OBJS2) $(TARGET) $(TARGET).info $(TARGET_NAME).info $(TARGET)-Results.xml
	$(RM) -r $(COV_OUT)
