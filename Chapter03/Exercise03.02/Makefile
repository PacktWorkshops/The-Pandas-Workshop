SHELL := /bin/bash
TARGETS := Exercise03.02.ipynb

.PHONY: all
all: $(TARGETS)

%.ipynb: %.md
	jupytext -o $@ --to notebook $<

.PHONY: clean
clean:
	rm -f $(TARGETS)
