logger_test:
	g++ demo.cpp log_sys.cpp utilities.cpp
	./a.out
demo_test:
	g++ demo.cpp chatroom.cpp tcp_services.cpp log_sys.cpp utilities.cpp \
		-pthread \
		-o demo -D DEMO_TEST_ON
	./demo
demo_debug:
	g++ -g demo.cpp chatroom.cpp tcp_services.cpp db.cpp user.cpp log_sys.cpp utilities.cpp -pthread -lsqlite3 -o demo
	gdb demo
sql_test:
	g++ demo.cpp tcp_services.cpp db.cpp log_sys.cpp user.cpp chatroom.cpp utilities.cpp -lsqlite3 -lpthread\
		 -o demo -D SQL_TEST_ON
	./demo
hash_test:
	g++ demo.cpp -o demo
	./demo
clean:
	rm a.out result.log demo