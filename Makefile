main:
	g++ ./bas/*.cpp -std=c++14 -o main -pthread -g

clean:
	rm main
