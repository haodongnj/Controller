test: test.o filter.o wdvrc.o
	gcc test.c filter.c wdvrc.c -o test 

debug: test.o filter.o wdvrc.o
	gcc -g test.c filter.c wdvrc.c -o test_debug

clean:
	rm *.o test test_debug text_output.txt 