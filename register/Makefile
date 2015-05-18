all: register register-clang
	

register: register.c
	gcc -g -o register register.c

register-clang: register.c
	clang -g -o register-clang register.c

clean:
	rm -f register register-clang

