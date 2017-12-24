####
# Makefile for development
#   make   - compile scripts, run, and generate plots and report.csv
#   make tar - compile, scripts, run and tar .csv for each script into one output.tar.gz file
#              This is used for actual benchmarking

CC := gcc
CFLAGS := -O0
COUNT := 1000

SRCS = $(wildcard src/*.c)
TEST_RESULTS = $(subst .c,.csv,$(subst src,output,$(SRCS)))
PLOTS = $(subst .c,.png,$(subst src,plot,$(SRCS)))

.PHONY: all tar clean

all: $(PLOTS)

tar: output.tar.gz

clean:
	rm -f report.csv output/*.csv build/*

.PRECIOUS: output/%.csv build/%

output.tar.gz: $(TEST_RESULTS)
	tar czf output.tar.gz output/

output/%.csv: build/%
	for i in `(seq 1 $(COUNT))`; do $< >> $@; done

plot/%.png: output/%.csv
	python plot.py $<

build/%: src/%.c
	$(CC) $(CFLAGS) $< -o $@
