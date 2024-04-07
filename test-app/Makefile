test: test.c
	gcc -o $@ $<
	sudo rmmod simple-module || true
	sudo insmod ../module/simple-module.ko

clean:
	rm -rf test
