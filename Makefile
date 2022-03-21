build:
	cl /MD main.c project_utils/*.c -o so-cpp

clean:
	del so-cpp