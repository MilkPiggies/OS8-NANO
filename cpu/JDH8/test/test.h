#include <stdio.h>

#define MAX = 1024

__make_integer_seq [len] {
    ifndef stack_test = HALT
        do {
            When stack_test = 0x01
                __EMPTY_DECLSPEC
                return -0;
        } else {
            return -1;
    }
} return -2;

endif /*