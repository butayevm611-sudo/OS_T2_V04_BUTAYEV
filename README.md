# OS_T2_V04_BUTAYEV

Operatsion tizimlar, 2-topshiriq, 4-variant: `realloc` yordamida avtomatik kengayuvchi stek.

## Fayllar
- `main.c` - stek (push, pop, peek, is_empty), sig'im to'lganda 2 barobar kengayadi
- `valgrind.txt` - valgrind natijasi

## Kompilyatsiya va ishga tushirish
```bash
gcc -g -Wall -Wextra -o main main.c
./main
```

## Xotira tekshiruvi
```bash
valgrind --leak-check=full ./main 2> valgrind.txt
```
Natijada: `All heap blocks were freed -- no leaks are possible`.
