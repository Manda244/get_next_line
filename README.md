*This project has been created as part of the 42 curriculum by marasolo.*

# get_next_line

## Description

`get_next_line` is a small C library function that reads from a file descriptor and returns the next line, one at a time, including the terminating newline character (if present). The goal is to implement a robust and memory-safe line reader that handles arbitrary line lengths, partial reads, and multiple file descriptors simultaneously.

This project is commonly used at 42 to practice low-level I/O, dynamic memory management, and working with buffers.

## Instructions

### Compilation

Compile the files using `gcc` (or your preferred C compiler). Example:

```sh
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line.c get_next_line_utils.c -o get_next_line
```

> **Note:** `BUFFER_SIZE` can be defined at compile time. It determines the size of the read buffer.

### Execution

Run the resulting binary with a file descriptor. Example using a file:

```sh
./get_next_line < file.txt
```

Or use it in another C program by including `get_next_line.h` and linking with `get_next_line.c` and `get_next_line_utils.c`.

## Algorithm & Design

### Selected algorithm

The implementation uses a **static buffer + remainder string** approach:

1. **Static remainder**: For each file descriptor, a static string (`static char *remainder`) stores any data read previously that was not yet returned as a full line.
2. **Reading in chunks**: The function reads from `read()` into a temporary buffer of size `BUFFER_SIZE` until a newline (`\n`) is found or `read()` returns 0 (EOF).
3. **Line extraction**: When a newline is found in the remainder, the function extracts the substring up to and including the newline and returns it. The rest of the remainder (after the newline) is kept for the next call.
4. **Memory management**: Memory is allocated for returned lines and for managing the remainder. Care is taken to free memory on error and to avoid leaks.

This approach is chosen because it:
- Works for any line length (not limited by `BUFFER_SIZE`).
- Handles partial reads (when `read()` returns less than requested).
- Supports multiple file descriptors by keeping a separate remainder per descriptor (if implemented that way; a single static remainder works for single-FD use).

### Justification

This algorithm matches the expected behavior of `get_next_line` in the 42 curriculum: successive calls return consecutive lines, and the function only reads as much as necessary to return the next line. It also avoids reading the entire file into memory, making it suitable for large files.

## Resources

- **POSIX `read(2)`** documentation: https://man7.org/linux/man-pages/man2/read.2.html
- **C standard library functions**: `malloc`, `free`, `write`, `read`, `strchr`, `strlen`.
- **42 subject**: get_next_line (mandatory project in the 42 cursus)

### AI usage

L'intelligence artificielle a été utilisée pour les tâches suivantes :

-  **Structuration du README** : Organisation des sections selon les critères du sujet.
-  **Rédaction technique** : Aide à la formulation des explications algorithmiques et des justifications techniques.
-  **Tests de robustesse** : Génération de scénarios de tests pour valider la gestion des erreurs (fd négatif, échecs de malloc).

## Additional notes

- Ensure `BUFFER_SIZE` is a positive integer. A zero or negative value is not supported.
- If `read()` returns `-1`, the function frees allocated memory and returns `NULL`.

