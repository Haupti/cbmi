BUILD=build
TEST=test
SRC=src

SOURCES=$(wildcard $(SRC)/*.c)
TEST_SOURCES=$(wildcard $(TEST)/*.c)

build:
	gcc -B $(SRC) . -o ./$(BUILD)/bfc \
		$(SOURCES)

build_test:
	gcc -B $(SRC) -B $(TEST) . -o ./$(BUILD)/test \
		$(SOURCES) $(TEST_SOURCES)

test: build_test
	./build/test
