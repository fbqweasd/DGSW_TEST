
OCI : main.o
	gcc -o OCI main.o  -locilib -D OCI_IMPORT_LINKAGE -D OCI_CHARSET_ANSI -L/opt/ext/ocilib/lib

main.o : main.c
	gcc  -c -o main.o main.c -I /opt/ext/ocilib/include    

clean :
	rm -rf *.o OCI
