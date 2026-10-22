//
// Created by abdulhaq on 10/21/26.
//
#include "../header/get_key.h"

#include <errno.h>
#include <poll.h>
#include <termios.h>
#include <unistd.h>

static int read_byte(unsigned char *byte, int timeout_ms)
{
    struct pollfd pfd = {
        .fd = STDIN_FILENO,
        .events = POLLIN,
        .revents = 0
    };

    int result;

    do {
        result = poll(&pfd, 1, timeout_ms);
    } while (result < 0 && errno == EINTR);

    if (result == 0) return 0;
    if (result < 0) return -1;
    if (!(pfd.revents & POLLIN)) return -1;

    ssize_t n;

    do {
        n = read(STDIN_FILENO, byte, 1);
    } while (n < 0 && errno == EINTR);

    return n == 1 ? 1 : -1;
}

Key get_key(void)
{
    struct termios old_settings;
    struct termios new_settings;

    if (!isatty(STDIN_FILENO)) return KEY_ERROR;
    if (tcgetattr(STDIN_FILENO, &old_settings) == -1) return KEY_ERROR;

    new_settings = old_settings;
    new_settings.c_lflag &= ~(ICANON | ECHO);
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_settings) == -1) return KEY_ERROR;

    unsigned char first;
    Key result = KEY_ERROR;

    if (read_byte(&first, -1) != 1) goto cleanup;

    if (first == '\n' || first == '\r') {
        result = KEY_ENTER;
        goto cleanup;
    }

    if (first != 27) {
        result = KEY_UNKNOWN;
        goto cleanup;
    }

    unsigned char second;
    int status = read_byte(&second, 100);

    if (status == 0) {
        result = KEY_EXIT;
        goto cleanup;
    }

    if (status < 0) goto cleanup;

    if (second != '[' && second != 'O') {
        result = KEY_UNKNOWN;
        goto cleanup;
    }

    unsigned char third;
    status = read_byte(&third, 100);

    if (status != 1) goto cleanup;

    switch (third) {
        case 'A':
            result = KEY_UP;
            break;

        case 'B':
            result = KEY_DOWN;
            break;

        default:
            result = KEY_UNKNOWN;
            break;
    }

cleanup:
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old_settings) == -1)
        return KEY_ERROR;

    return result;
}