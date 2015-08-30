all: clean ts

ts:
	g++ -DKXVER=3 -m32 -shared -std=c++14 ts.c -o ts.so

clean:
	rm -vf "*.so"
