CC := gcc
CFLAGS := -O0
COUNT := 1000

SRCS = $(wildcard src/*.c)
TEST_RESULTS = $(subst .c,.csv,$(subst src,output,$(SRCS)))
REPORTS = $(subst .c,.png,$(subst src,report,$(SRCS)))

.PHONY: all tar clean

all: report.csv

tar: output.tar.gz

clean:
	rm -f report.csv output/*.csv build/*

.PRECIOUS: output/%.csv build/%

output.tar.gz: $(TEST_RESULTS)
	tar czf output.tar.gz output/

report.csv: $(TEST_RESULTS) $(REPORTS)
	python make_report.py $@ $(TEST_RESULTS)

output/%.csv: build/%
	for i in `(seq 1 $(COUNT))`; do $< >> $@; done

report/%.png: output/%.csv
	python plot.py $<


build/%: src/%.c
	$(CC) $(CFLAGS) $< -o $@
