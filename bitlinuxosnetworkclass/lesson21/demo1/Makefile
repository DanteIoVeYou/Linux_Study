CC=g++
FLAG=-std=c++11
Src=mysignal.cc 
Bin=mysignal
$(Bin): $(Src)
	$(CC) -o $@ $^ $(FLAG)
.PHONY: clean
clean:
	rm -f $(Bin)
