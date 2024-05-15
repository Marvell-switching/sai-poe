#include <stdio.h>

#define LOG_PRINT(fmt, ...) \
    fprintf(stderr, "[%s:%s:%d] " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#define LOG_ERROR(fmt, ...) \
    fprintf(stderr, "[%s:%s:%d] ERROR: " fmt "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)