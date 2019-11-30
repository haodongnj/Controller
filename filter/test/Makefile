test:
	gcc -o test_filter.elf test_filter.c ../filter.c -lm
	chmod +x test_filter.elf
	./test_filter.elf
	echo "Run test_filter_plot.m by Octave/MATLAB to validate filter implementation"

clean:
	rm *.elf
	rm filter_results.txt