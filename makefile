logger_test:
	g++ demo.cpp log_sys.cpp utilities.cpp
	./a.out
clean:
	rm a.out result.log 