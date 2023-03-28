#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>
#include <stdlib.h>

uint8_t parser(const uint8_t * const message, size_t len) noexcept(false);

#endif