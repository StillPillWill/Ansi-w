all: report test_metros

# With optimizations, as in Part #1
report: report.cc metros.cc generate.cc metros.h
	clang++ @compile_flags.txt -O2 -o report report.cc metros.cc generate.cc

test_metros: test_metros.cc metros.cc generate.cc metros.h
	clang++ @compile_flags.txt -o test_metros test_metros.cc metros.cc generate.cc

test: test_metros
	./test_metros

clean:
	rm -f report test_metros
