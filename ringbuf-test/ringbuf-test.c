#include <stdio.h>
#include "ringbuf.h"

#define BUF_SIZE 96
#define READ_WRITE_CYCLES 2

void read_cycle() {
	int i = 1;
	int write_tot = 0;
	for (int n = 0; n < READ_WRITE_CYCLES; n++) {
		int write_buf[BUF_SIZE];
		for (int m = 0; m < BUF_SIZE; m++) {
			write_buf[m] = i++;
		}

		int wrote = ringbuf_write(write_buf, BUF_SIZE);
		write_tot += wrote;
		if (wrote < BUF_SIZE) {
			printf("Buffer full after %d bytes written!\n", write_tot);
			break;
		}
	}
}

void write_cycle() {
	int i = 1;
	int read_tot = 0;
	for (int n = 0; n < READ_WRITE_CYCLES; n++) {
		int read_buf[BUF_SIZE];
		int read = ringbuf_read(read_buf, BUF_SIZE);
		read_tot += read;

		for (int m = 0; m < read; m++) {
			if (read_buf[m] != i++) {
				printf("Mismatch at index %d! Got %d, expected %d!\n", m, read_buf[m], i - 1);
			}
		}
		if (read < BUF_SIZE) {
			printf("Buffer empty after %d bytes read!\n", read_tot);
			break;
		}
	}
}

int main() {
	ringbuf_zero();

	for (int i = 0; i < 10; i++) {
		read_cycle();
		write_cycle();
	}

	return 0;
}
