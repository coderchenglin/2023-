mychild:mychild.c 
    gcc -o $@ $^ -std=c99
.PHONY:clean
clean:
    rm -f mychild
