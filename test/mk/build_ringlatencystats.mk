include ./mk/env.mk
TARGET_NAME = ringlatencystats

TARGET = $(TARGET_NAME)_test
TEST_SRC_DIR = $(TARGET_NAME)
SRCS = $(TARGET_NAME)_test.c

OBJS = $(SRCS:.c=.o)
CFLAGS = $(DEFAULT_CFLAGS) -coverage -g -O0
#CFLAGS += -m32 -mssse3
CFLAGS += -m64 -mssse3
CFLAGS += -I$(RTE_INCLUDE)
CFLAGS += -I./$(TEST_SRC_DIR)
CFLAGS += -I../

CFLAGS += -DUSE_SPP_APL_LOG_DEBUG
CFLAGS += -DUSE_SPP_APL_LOG_TRACE
CFLAGS += -DUSE_SPP_PTACH_NO_DEMONIZE
CFLAGS += -DUSE_UT_SPP_APL

LDFLAGS = $(DEFAULT_LDFLAGS)

LDLIBS += -ljansson -lcunit
LDLIBS += -lrte_eal -lrte_mbuf -lrt -pthread -ldl

COV_OBJS=$(SRCS:.c=.gcno)
COV_OBJS2=$(SRCS:.c=.gcda)
COV_OUT = $(TEST_SRC_DIR)/coverage

.PHONY: all clean
all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "[LD]$@..."
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
#	chmod +x run_$(TARGET).sh

%.o: %.c
	@echo "[CC]$<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(COV_OBJS) $(COV_OBJS2) $(TARGET) $(TARGET).info $(TARGET_NAME).info $(TARGET)-Results.xml
	$(RM) -r $(COV_OUT)
