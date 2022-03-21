CC = cl.exe
LINK=link.exe
CLFAGS = /MD /nologo /W4
default: build

build: so-cpp.obj hashmap.obj line_args.obj
	$(CC) /Zi so-cpp.obj hashmap.obj line_args.obj /Feso-cpp.exe

so-cpp.obj: so-cpp.c
	$(CC) $(CFLAGS) /c so-cpp.c /Foso-cpp.obj

hashmap.obj: hashmap.c
	$(CC) $(CFLAGS) /c hashmap.c /Fohashmap.obj

lince_args.obj: line_args.c
	$(CC) $(CFLAGS) /c line_args.c /Foline_args.obj

clean:
	del *.obj
	del so-cpp.exe