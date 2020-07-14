logger_test:
	g++ demo.cpp log_sys.cpp utilities.cpp
	./a.out
demo_test:
	g++ demo.cpp chatroom.cpp tcp_services.cpp log_sys.cpp utilities.cpp -pthread -o demo
	./demo
clean:
	rm a.out result.log 