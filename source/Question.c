#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "../header//Question.h"
#include "../header/Question_types.h"
#include "../header/get_key.h"
#define CURSOR "->"

static int selected = 0;

// this method initialize the entering data into a struct called Question
// .این متد داده های ورودی را به یک ساختار Question تبدیل میکند
Question *init_question(const char *question, int options_number, const char **options, bool execute_message) {
    if (question == NULL || options == NULL || options_number <= 0) return NULL;
    Question *q = malloc(sizeof(Question));

    if (q == NULL) {
        fprintf(stderr, "Memory reservation failed!\n");
        return NULL;
    }

    q->question = NULL;
    q->options = NULL;
    q->options_number = 0;
    q->answer = NULL;

    // for question
    size_t question_len = strlen(question);
    q->question = malloc(question_len + 1);
    if (q->question == NULL) {
        free(q);
        return NULL;
    }
    memcpy(q->question, question, question_len + 1);

    // for options
    q->options = malloc((size_t)options_number * sizeof(*q->options));

    if (q->options == NULL) {
        free(q->question);
        free(q);
        return NULL;
    }
    int copied = 0;
    for (int i = 0; i < options_number; i++) {
        if (options[i] == NULL) goto cleanup;
        // get size
        size_t option_len = strlen(options[i]);
        // reserve for options
        char *option_copy = malloc(option_len + 1);
        if (option_copy == NULL) goto cleanup;
        // copy
        memcpy(option_copy, options[i], option_len + 1);
        q->options[i] = option_copy;
        copied++;
    }
    //3) options number
    q->options_number = options_number;

    if (execute_message == true) printf("Your Question made successfully initialized.");
    return q;

    cleanup:
        for (int i = 0; i < copied; i++) {
            free((void *)q->options[i]);
        }

        free(q->options);
        free(q->question);
        free(q);

    return NULL;
}

// this method will clear terminal
// .این متد به اندازه خط های که از ورودی میگیرد ترمینال را پاک میکند
void clear_terminal(int lines) {
    printf("\033[%dA", lines + 2);
    printf("\033[J");
}


QuestionStatus update_question(const Question *q) {
    if (q == NULL) return false;

    Key key = get_key();
    switch (key) {
        case KEY_UP:
            if (selected > 0) selected--;
            clear_terminal(q->options_number);
            break;

        case KEY_DOWN:
            if (selected < q->options_number -1) selected++;
            clear_terminal(q->options_number);
            break;;

        case KEY_ENTER:
            return QUESTION_SELECTED;

        case KEY_EXIT:
            return QUESTION_CANCELLED;

        default:
            return QUESTION_CONTINUE;
    }
    return QUESTION_CONTINUE;
}


void printer(const Question *q) {
    if (q == NULL) return;

    printf("Q) %s\n\n", q->question);
    for (int i = 0; i < q->options_number; i++) {
        if (q->options[i] == NULL) continue;

        if (i == selected) {
            printf("%s %d) %s\n", CURSOR, i + 1, q->options[i]);
        } else {
            printf("   %d) %s\n", i + 1, q->options[i]);
        }
    }

    fflush(stdout);
}


Question *question(const char *text, int options_number, const char **options) {
    Question *q = init_question(text, options_number, options, false);
    if (q == NULL) return NULL;

    selected = 0;
    while (1) {
        printer(q);
        QuestionStatus status = update_question(q);
        if (status == QUESTION_CONTINUE)
            continue;

        if (status == QUESTION_CANCELLED) {
            free_memory_question(q);
            return NULL;
        }

        if (status == QUESTION_SELECTED)
            break;
    }


    size_t len = strlen(q->options[selected]);
    q->answer = malloc(len + 1);
    if (q->answer == NULL) {
        free_memory_question(q);
        return NULL;
    }

    memcpy(q->answer, q->options[selected], len + 1);
    return q;
}


void free_memory_question(Question *q) {
    if (q == NULL) return;

    for (int i = 0; i < q->options_number; i++) {
        free((void *)q->options[i]);
    }

    free(q->options);
    free(q->question);
    free(q->answer);
    free(q);
}