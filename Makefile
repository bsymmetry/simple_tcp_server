BUILD := build
CC := clang

.PHONY: all clean test

all: $(BUILD)/stcps tests/stcps_tests

$(BUILD)/stcps: src/server/main.cpp | $(BUILD)
	$(CC) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

tests/stcps_tests: tests/stcps_tests.cpp
	$(CC) -c $< -o $@

test:
	./tests/stcps_tests

clean:
	rm -rf $(BUILD) tests/stcps_tests
