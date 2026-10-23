# Question-in-c

**A lightweight interactive question and multiple-choice selection library written in C.**

Question-in-c is a C library designed to make it easier to create interactive questions in terminal-based applications. It allows users to navigate through a list of answer options using keyboard arrow keys and select an answer with Enter or cancel the operation with Escape.

Instead of implementing terminal navigation, keyboard input handling, and question rendering from scratch in every project, developers can use this library to manage interactive question selection.

## Features

- **Interactive questions:** Display a question with multiple answer options in the terminal.
- **Keyboard navigation:** Move between options using the Up and Down arrow keys.
- **Answer selection:** Press Enter to select the currently highlighted option.
- **Cancellation:** Press Escape to cancel the selection.
- **Dynamic memory management:** Allocate memory for question data and answer options dynamically.
- **Automatic memory cleanup:** Release allocated resources through the provided cleanup function.
- **Reusable components:** Integrate interactive questions into command-line applications written in C.
- **Simple API:** Use dedicated functions to initialize, display, update, and process questions.

## How It Works

Question-in-c displays a question followed by a list of available answers.

The currently selected option is indicated by a cursor:

```text
Q) What is the capital of France?

   1. London
-> 2. Paris
   3. Berlin
   4. Rome
```

The user can navigate through the options using the keyboard:

| Key | Action |
| --- | --- |
| Up Arrow | Move to the previous option |
| Down Arrow | Move to the next option |
| Enter | Select the highlighted answer |
| Escape | Cancel the selection |

The selected option is stored in the question object so that the application can process the result.

## Requirements

- A C compiler with C11 support recommended.
- A Unix-like operating system, such as Linux or macOS.
- A terminal that supports ANSI escape sequences.
- A POSIX-compatible environment for terminal keyboard input.

The keyboard input implementation uses terminal control facilities such as `termios`. Native Windows terminals may require a different implementation.

## Installation

Clone the repository:

```bash
git clone https://github.com/coderealm-code/Question-in-c.git
```

Enter the project directory:

```bash
cd Question-in-c
```

Compile the library source files together with your application, making sure to include the appropriate header directory.

For example, if your source files are located in `src/` and your headers are located in `header/`, adapt the following command to match your project structure:

```bash
gcc -std=c11 -Wall -Wextra -Iheader \
    main.c src/Question.c src/get_key.c \
    -o example
```

Run the application:

```bash
./example
```

The source filenames and directory names in the compilation command are examples. Use the actual filenames present in your checkout.

## Basic Usage

The library is intended to be used by initializing a question, displaying its options, handling the user's selection, and releasing the allocated memory.

The following example illustrates the intended usage pattern. Check the declarations in `Question.h` and the relevant headers to ensure that the function signatures match your version.

```c
#include <stdio.h>
#include <stdbool.h>

#include "Question.h"

int main(void)
{
    const char *options[] = {
        "Option A",
        "Option B",
        "Option C"
    };

    Question *q = init_question(
        "Choose an option:",
        3,
        options,
        false
    );

    if (q == NULL) {
        fprintf(stderr, "Failed to initialize question.\n");
        return 1;
    }

    Question *result = question(q);

    if (result != NULL &&
        result->answer != NULL) {
        printf("Selected answer: %s\n", result->answer);
    } else {
        printf("Question cancelled or no answer selected.\n");
    }

    free_memory_question(q);
    return 0;
}
```

**Important:** The example assumes that `question()` returns the same `Question *` object and that `answer` is a member of the structure. Verify the actual function signatures and cancellation behavior in the current implementation before compiling.

## API Overview

The library provides functions for managing the question lifecycle.

### `init_question()`

Initializes a question and prepares its text and answer options for use.

The initialization process is designed to allocate the required memory and copy the supplied question data into the question object.

### `question()`

Runs the interactive selection process, allowing the user to navigate through the available options and select an answer or cancel.

### `printer()`

Displays the question and its answer options in the terminal, including an indicator for the currently selected option.

### `update_question()`

Handles updates to the question's selection state based on the relevant input or internal state.

### `free_memory_question()`

Releases the dynamically allocated memory associated with a question object, including its question text, answer options, selected answer, and the object itself, according to the library's ownership rules.

Consult the declarations in the project's headers for the exact parameter types and return values of each function.

## Memory Management

Question-in-c uses dynamic memory allocation to support question text and answer options without requiring fixed-size buffers for their contents.

When using the library:

1. Check whether initialization succeeds before using the returned object.
2. Do not access a question object after its memory has been released.
3. Call `free_memory_question()` when the object is no longer needed.
4. Do not free the same object more than once.
5. Do not independently free fields that are owned and managed by the library.

The exact ownership rules are defined by the implementation. In the current design, the question object manages its dynamically allocated question text, copied answer options, and selected-answer storage.

## Project Structure

The project contains the implementation and header files required to manage question data, keyboard input, navigation, and terminal output.

Typical responsibilities include:

- **Question data:** Stores the question text, answer options, selection result, and related state.
- **Keyboard input:** Reads keyboard input and identifies navigation, selection, and cancellation keys.
- **Question rendering:** Prints the question and available answer options.
- **Selection handling:** Updates the highlighted option and processes the user's choice.
- **Memory management:** Allocates and releases resources used by the question object.

Refer to the repository's actual directory structure for the current filenames and locations.

## Limitations

- The library is intended primarily for interactive terminal applications.
- Keyboard navigation depends on terminal input and control support.
- Terminal behavior may vary across operating systems and terminal emulators.
- The current keyboard input implementation relies on POSIX terminal facilities.
- Applications must follow the library's memory ownership rules to avoid memory leaks and invalid memory access.

## Contributing

Contributions, bug reports, and suggestions are welcome.

If you find a bug or want to improve the library:

1. Fork the repository.
2. Create a branch for your changes.
3. Make and test your changes.
4. Submit a pull request describing the improvements.

Please keep changes focused and ensure that keyboard input, navigation, cancellation, and memory management continue to work correctly.

## License

Question-in-c is distributed under the **Eclipse Public License 2.0 (EPL-2.0)**.

See the [LICENSE](LICENSE) file for the complete license text.

SPDX-License-Identifier: EPL-2.0

## Author

Developed by **coderealm-code**.

Repository: https://github.com/coderealm-code/Question-in-c