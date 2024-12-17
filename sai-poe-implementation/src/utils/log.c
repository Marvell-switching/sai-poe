/*
 *  Copyright (C) 2024, MARVELL. All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 */

#include <h/utils/log.h>
#define LOG_FILE_PATH "/var/log/poelog"
#define MAX_LOG_FILE_SIZE (10 * 1024 * 1024) // 10MB

#include <stdio.h>
#include <stdarg.h>

void log_to_file(const char *level, const char *file, const char *func, int line, const char *fmt, ...) {
    FILE *log_file = fopen(LOG_FILE_PATH, "a+"); // Open the log file in append mode
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }

    // Check the file size
    fseek(log_file, 0, SEEK_END); // Move to the end of the file
    long file_size = ftell(log_file);
    if (file_size > MAX_LOG_FILE_SIZE) {
        fclose(log_file);

        // Truncate the file by reopening in "w" mode
        log_file = fopen(LOG_FILE_PATH, "w");
        if (log_file == NULL) {
            perror("Failed to truncate log file");
            return;
        }
    }

    va_list args;
    va_start(args, fmt); // Initialize va_list with the last known fixed argument

    // Print the log message to the file
    fprintf(log_file, "[%s:%s:%d] %s: ", file, func, line, level); // Log prefix
    vfprintf(log_file, fmt, args);                                // Log message with variable args
    fprintf(log_file, "\n");                                      // Newline for clarity

    va_end(args); // Clean up va_list
    fclose(log_file); // Close the log file
}