logger_test:
	g++ demo.cpp log_sys.cpp utilities.cpp
	./a.out
demo_test:
	g++ demo.cpp chatroom.cpp tcp_services.cpp log_sys.cpp user.cpp utilities.cpp -pthread -o demo
	./demo
sql_test:
	g++ demo.cpp db.cpp log_sys.cpp user.cpp utilities.cpp -lsqlite3 -o demo
	./demo
clean:
	rm a.out result.log 