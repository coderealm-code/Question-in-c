#include <stdio.h>
#include "./header/Question.h"


int main(void) {
        const char *options[] = {
                "Python",
                "C",
                "Java"
            };//k

        Question *q = question("Choose a language", 3, options);

        // بررسی لغو یا شکست ساخت سؤال
        // check if cancelled or failed
        if (q == NULL) {
                printf("Question cancelled or failed.\n");
                return 0;
        }

        // ابتدا جواب را بخوان
        // the answer
        printf("Your answer: %s\n", q->answer);

        // بعد تمام حافظه را آزاد کن
        // free memory and make it NULL
        free_memory_question(q);
        q = NULL;

        return 0;
}