build:
	g++ student_management_system.cpp -o bin/student_management_system.exe

run: build
	./bin/student_management_system