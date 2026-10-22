//
// Created by abdulhaq on 10/1/26.
//

#ifndef C_PROJECTS_QUESTION_TYPES_H
#define C_PROJECTS_QUESTION_TYPES_H

typedef struct {
    char *question;
    int options_number;
    const char **options;
    char *answer;
} Question;

typedef enum {
    QUESTION_CONTINUE,
    QUESTION_SELECTED,
    QUESTION_CANCELLED
} QuestionStatus;

#endif //C_PROJECTS_QUESTION_TYPES_H
