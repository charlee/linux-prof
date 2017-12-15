CC := gcc
CFLAGS := -O0
COUNT := 1000

SRCS = $(wildcard src/*.c)
TEST_RESULTS = $(subst .c,.csv,$(subst src,output,$(SRCS)))

.PHONY: all clean

all: report.csv
clean:
	rm report.csv output/*.csv build/*

.PRECIOUS: output/%.csv build/%

report.csv: $(TEST_RESULTS)
	python make_report.py $@ $(TEST_RESULTS)

output/%.csv: build/%
	$< >> $@

build/%: src/%.c
	$(CC) $(CFLAGS) $< -o $@