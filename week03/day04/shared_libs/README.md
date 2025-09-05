```bash
gcc -fPIC -c mylib.c
gcc -shared -o libmylib.so mylib.o
gcc -o main main.c -L. -lmylibrary
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ; ./main
./main
```
