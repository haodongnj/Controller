test:
	gcc -o test_pr.elf test_pr.c ../pr.c -lm
	chmod +x test_pr.elf
	./test_pr.elf
	@echo "Run test_pr_plot.m in Octave/MATLAB to see test results"

clean:
	rm *.elf
	rm test_pr_output.txt