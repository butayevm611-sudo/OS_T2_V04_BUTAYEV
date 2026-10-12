#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;      /* dinamik massiv */
    int size;       /* hozirgi elementlar soni */
    int capacity;   /* ajratilgan sig'im */
} Stack;

int is_empty(const Stack *s) {
    return s->size == 0;
}

/* Stekni yaratadi. Muvaffaqiyatli bo'lsa 1, aks holda 0 */
int stack_init(Stack *s, int cap) {
    s->data = malloc(cap * sizeof(int));
    if (s->data == NULL) {
        printf("Xato: xotira ajratilmadi.\n");
        return 0;
    }
    s->size = 0;
    s->capacity = cap;
    return 1;
}

/* Elementni qo'shadi. To'lsa, sig'im 2 barobar oshadi */
int push(Stack *s, int val) {
    if (s->size == s->capacity) {
        int new_cap = s->capacity * 2;
        int *tmp = realloc(s->data, new_cap * sizeof(int));
        if (tmp == NULL) {
            printf("Xato: realloc muvaffaqiyatsiz.\n");
            return 0;               /* eski s->data saqlanib qoladi */
        }
        s->data = tmp;
        s->capacity = new_cap;
        printf("Sig'im %d ga oshirildi.\n", new_cap);
    }
    s->data[s->size] = val;
    s->size++;
    return 1;
}

/* Oxirgi elementni olib tashlaydi, qiymatni *out ga yozadi */
int pop(Stack *s, int *out) {
    if (is_empty(s)) return 0;
    s->size--;
    *out = s->data[s->size];
    return 1;
}

/* Oxirgi elementni o'chirmasdan ko'rsatadi */
int peek(const Stack *s, int *out) {
    if (is_empty(s)) return 0;
    *out = s->data[s->size - 1];
    return 1;
}

void stack_free(Stack *s) {
    free(s->data);
    s->data = NULL;     /* dangling pointer bo'lmasligi uchun */
    s->size = 0;
    s->capacity = 0;
}

/* Butun son o'qiydi: 1 - ok, 0 - noto'g'ri kiritish, -1 - fayl oxiri */
int oqi_son(int *x) {
    int r = scanf("%d", x);
    if (r == 1) return 1;
    if (r == EOF) return -1;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}   /* bufer tozalash */
    return 0;
}

int main(void) {
    Stack s;
    int cap, tanlov, val, r;

    printf("Boshlang'ich sig'im (1..1000): ");
    r = oqi_son(&cap);
    if (r != 1 || cap < 1 || cap > 1000) {
        printf("Xato: sig'im 1 dan 1000 gacha butun son bo'lishi kerak.\n");
        return 1;
    }
    if (!stack_init(&s, cap)) return 1;

    while (1) {
        printf("\n1-push  2-pop  3-peek  4-is_empty  0-chiqish\nTanlang: ");
        r = oqi_son(&tanlov);
        if (r == -1) break;
        if (r == 0) {
            printf("Xato: son kiriting!\n");
            continue;
        }
        if (tanlov == 0) break;

        if (tanlov == 1) {
            printf("Qiymat: ");
            if (oqi_son(&val) != 1) {
                printf("Xato: butun son kiriting!\n");
                continue;
            }
            if (push(&s, val)) printf("%d qo'shildi.\n", val);
        } else if (tanlov == 2) {
            if (pop(&s, &val)) printf("Olindi: %d\n", val);
            else printf("Xato: stek bo'sh!\n");
        } else if (tanlov == 3) {
            if (peek(&s, &val)) printf("Eng yuqori: %d\n", val);
            else printf("Xato: stek bo'sh!\n");
        } else if (tanlov == 4) {
            printf(is_empty(&s) ? "Stek bo'sh.\n" : "Stek bo'sh emas.\n");
        } else {
            printf("Xato: tanlov 0 dan 4 gacha bo'lishi kerak.\n");
        }
    }

    stack_free(&s);
    printf("Dastur tugadi.\n");
    return 0;
}
