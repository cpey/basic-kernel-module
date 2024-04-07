test-app: test-app.c
	gcc -o $@ $< -I ../include
	sudo rmmod simple-module || true
	sudo insmod ../module/simple-module.ko

clean:
	rm -rf test-app
