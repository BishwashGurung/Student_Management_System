build:
	g++ student_management_system.cpp -o bin/student_management_system

run: build
	./bin/student_management_system