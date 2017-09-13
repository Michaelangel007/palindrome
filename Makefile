all: pal findpal

.phony: clean

clean:
	@rm -f pal findpal

# -g  Debug Info
C_FLAGS=-Wall -Wextra -O2 -g -Wno-missing-field-initializers

INC_H=$(wildcard *.h)

pal: palindrome_bigint.cpp $(INC_H)
	g++ $(C_FLAGS) $< -o $@

findpal: find_palindrome.cpp $(INC_H)
	g++ $(C_FLAGS) $< -o $@

