//
// Created by abdulhaq on 10/21/26.
//

#ifndef C_PROJECTS_GET_KEY_H
#define C_PROJECTS_GET_KEY_H
typedef enum {
    KEY_UP,
    KEY_DOWN,
    KEY_ENTER,
    KEY_EXIT,
    KEY_UNKNOWN,
    KEY_ERROR
} Key;

Key get_key(void);
#endif //C_PROJECTS_GET_KEY_H
