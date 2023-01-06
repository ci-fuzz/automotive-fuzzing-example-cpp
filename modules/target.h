#ifndef TARGET_H
#define TARGET_H

#include <stdint.h>
#include <stdlib.h>

void start_thread1(const uint8_t * const message, size_t len);
void start_thread2(const uint8_t * const message, size_t len);
void start_thread3(const uint8_t * const message, size_t len);

#endif 