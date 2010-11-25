all: compile install
  

compile: libSO.cpp
  gcc -shared -o libso-eafit.so libSO.cpp

install: copy_lib copy_header
  
copy_lib:
  cp libso-eafit.so /usr/lib/

copy_header:
  cp SO.h /usr/include/

clean:
  rm -f *.so
