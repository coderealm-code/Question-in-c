#ifndef QUESTION_H
#define QUESTION_H

#include "../header/Question_types.h"
#include <stdbool.h>

Question *init_question(const char *question, int options_number, const char **options, bool execute_message);
void clear_terminal(int lines);

void free_memory_question(Question *q);

void printer(const Question *q);
const char *get_answer(const Question *q, int select);
QuestionStatus update_question(const Question *q);

Question *question(const char *text, int options_number, const char **options);
void free_answer_memory(char *answer);

#endif