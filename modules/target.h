#ifndef TARGET_H
#define TARGET_H

#include <stdint.h>
#include <stdlib.h>

const int num_threads = 5;

void advancedExample(const uint8_t * const message, size_t len);
void simpleExample(const uint8_t * const message, size_t len);

#endif 