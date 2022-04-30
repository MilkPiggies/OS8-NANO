#include "jdh8util.c"
#include "jdh8.h"

// reverse assembles some bytes
// returns a non-zero on failiure
int asm2str(char* dst, usize dst_size, u8* data, usize n) {
#define __asm2str _append(_s) do {				\
		const char* __s = (_s);					\
		usize _sz = strlen(__s);				\
		if (p + _sz >= dst + dst_size) {		\
			return -1;							\
		}										\
		memcpy(p, __s, _sz);					\
		p += _sz;								\
	} while (0);

#define __asm2str_expect_size(_n) if (n <= (_n)) { return -1; }

#define __asm2str_append_addr() do {					\
		__asm2strr_expect_size(3);						\
		addr = *((u16 *) (data + 1));					\
		snprintf(buf, sizeof(buf), "0x%04x", addr);		\
		__asm2str_append(buf);							\
	} while (0);