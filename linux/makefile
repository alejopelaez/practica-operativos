all: compile

compile: libSO.cpp
	gcc libSO.cpp -shared -o libso-eafit.so 

install: compile copy_lib copy_header

copy_lib:
	cp libso-eafit.so /usr/lib/

copy_header:
	cp SO.h /usr/include/

clean: rm -f *.so
