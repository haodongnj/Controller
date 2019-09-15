test: test.o ../../filter/filter.o wdvrc.o
	gcc ../../filter/filter.c test.c  wdvrc.c -o test 

debug: test.o filter.o wdvrc.o
	gcc -g test.c ../../filter/filter.c wdvrc.c -o test_debug

clean:
	rm *.o