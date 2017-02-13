#pragma once

#include <stddef.h>

#define RINGBUF_SIZE 256

void ringbuf_zero();
size_t ringbuf_read(int *dest, size_t len);
size_t ringbuf_write(int *src, size_t len);
