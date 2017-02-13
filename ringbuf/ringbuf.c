#include <stdbool.h>
#include "ringbuf.h"

typedef struct _ringbuf_t {
	int buf[RINGBUF_SIZE];
	int* read;
	int* write;
	bool is_full;
} ringbuf_t;

ringbuf_t _glrb;

void ringbuf_zero() {
	_glrb.is_full = 0;
	_glrb.read = _glrb.write = _glrb.buf;
}

size_t ringbuf_read(int *dest, size_t len) {
	if (_glrb.read == _glrb.write && !_glrb.is_full) { // empty!
		return 0;
	}
	if (len > 0) { // we are about to read at least one byte
		_glrb.is_full = false;
	}
	for (size_t i = 0; i < len; i++) {
		*(dest + i) = *(_glrb.read++);
		if(_glrb.buf + RINGBUF_SIZE == _glrb.read) { // wrap around
			_glrb.read = _glrb.buf;
		}
		if (_glrb.read == _glrb.write) { // empty!
			return i + 1;
		}
	}

	return len;
}

size_t ringbuf_write(int *src, size_t len) {
	if (_glrb.is_full) {
		return 0;
	}
	for (size_t i = 0; i < len; i++) {
		*(_glrb.write++) = *(src + i);
		if (_glrb.buf + RINGBUF_SIZE == _glrb.write) { // wrap around
			_glrb.write = _glrb.buf;
		}
		if (_glrb.read == _glrb.write) { // full!
			_glrb.is_full = true;
			return 1 + i;
		}
	}

	return len;
}
