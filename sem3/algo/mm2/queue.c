#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EFULL 2
#define EMPTY 3

/* Queue stuff */
typedef struct {
    int head;
    int tail;
    int len;
    int cap;
    int *buff;
} queue_t;

/* Queue functions */
int queue_init(queue_t *q, size_t cap)
{
    /* Make the struct and set i to zero */
    memset(q, 0, sizeof(queue_t));

    /* Allocate the buffer */
    q->buff = (int *)malloc(cap * sizeof(int));
    if (q->buff == NULL) {
        return 1;
    }

    /* Set capacity, the rest should be zero form memset */
    q->cap = cap;
    return 0;
}

void queue_free(queue_t *q)
{
    /* Free the heap buffer */
    free(q->buff);
}

int queue_place(queue_t *q, int val)
{
    /* Check if full */
    printf("len: %d\n", q->len);
    if (q->len >= q->cap) {
        printf("ERR: Full\n");
        return EFULL;
    }

    /* Add to queue */
    q->buff[q->head] = val;

    /* Increase values */
    q->head = (q->head + 1) % q->cap;
    q->len++;

    return 0;
}

int queue_get(queue_t *q, int *val)
{
    /* Check if empty */
    if (!q->len) {
        printf("ERR: Empty\n");
        return EMPTY;
    }

    /* Read value */
    if (val != NULL) {
        *val = q->buff[q->tail];
    }

    /* Decrease values */
    q->tail = (q->tail + 1) % q->cap;
    q->len--;

    return 0;
}

int main(void)
{
    int in;
    char com;

    queue_t q;
    queue_init(&q, 16);

    for (;;) {
        /* Read a command */
        scanf("%c", &com);

        if (com == 'w') {
            printf("> ");
            scanf("%d", &in);
            queue_place(&q, in);
        } else if (com == 'r') {
            queue_get(&q, &in);
            printf("%d\n", in);
        } else if (com == 'q') {
            break;
        }
    }

    queue_free(&q);
}
