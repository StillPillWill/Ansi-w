all: benchmark test_totals

benchmark: benchmark.cc totals.cc generate.cc totals.h
	clang++ @compile_flags.txt -o benchmark benchmark.cc totals.cc generate.cc

test_totals: test_totals.cc totals.cc generate.cc totals.h
	clang++ @compile_flags.txt -o test_totals test_totals.cc totals.cc generate.cc

test: test_totals
	./test_totals

clean:
	rm -f benchmark test_totals
