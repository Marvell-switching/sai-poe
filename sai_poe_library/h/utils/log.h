#include <stdio.h>

// #define LOG_PRINT(fmt, ...) \
//     fprintf(stderr, "[%s:%s:%d] " fmt "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

// #define LOG_ERROR(fmt, ...) \
//     fprintf(stderr, "[%s:%s:%d] ERROR: " fmt "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#define LOG_FILE_PATH "/var/log/poelog"

void log_to_file(const char *level, const char *file, const char *func, int line, const char *fmt, ...);

#define LOG_PRINT(fmt, ...) \
    log_to_file("POE-INFO", __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_ERROR(fmt, ...) \
    log_to_file("POE-ERROR", __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

