#include "asm.h"
#include "lex.h"

// from builtin_macros.c, produced by builtin_macros.asm
extern unsigned char asm_macros_asm[];
extern unsigned char asm_macros_asm_len;

#define BUILTIN_MACROS_TEXT (asm_macros_asm)
#define BUILTIN_MACROS_LEN (asm_macros_asm_len)

// program-lifetime memory region
#define REGION_MIN_SIZE 0x40000
struct Region {
	void *current, *end, *next;
};

static const struct Op INSTRUCTIONS[] = {
    [I_MW] = {
        .name = "MW",
        .num_args = 2,
        .args = { A_REG, A_IMM8_REG },
        .macro = false,
        .instruction = I_MW
    },
     [I_LW] = {
        .name = "LW",
        .num_args = 2,
        .args = { A_REG, A_IMM16_HL },
        .macro = false,
        .instruction = I_LW
    },
    [I_SW] = {
        .name = "SW",
        .num_args = 2,
        .args = { A_IMM16_HL, A_REG },
        .macro = false,
        .instruction = I_SW
    },
    [I_PUSH] = {
        .name = "PUSH",
        .num_args = 1,
        .args = { A_IMM8_REG },
        .macro = false,
        .instruction = I_PUSH
    },
    [I_POP] = {
        .name = "POP",
        .num_args = 1,
        .args = { A_REG },
        .macro = false,
        .instruction = I_POP
    },
    [I_LDA] = {
        .name = "LDA",
        .num_args = 1,
        .args = { A_IMM16 },
        .macro = false,
        .instruction = I_LDA
    },
    [I_JNZ] = {
        .name = "JNZ",
        .num_args = 1,
        .args = { A_IMM8_REG },
        .macro = false,
        .instruction = I_JNZ
    },
    [I_INB] = {
        .name = "INB",
        .num_args = 2,
        .args = { A_REG, A_IMM8_REG },
        .macro = false,
        .instruction = I_INB
    },
    [I_OUTB] = {
        .name = "OUTB",
        .num_args = 2,
        .args = { A_IMM8_REG, A_REG },
        .macro = false,
        .instruction = I_OUTB
    },

#define DEF_OP_ARITHMETIC(_n)           \
    [I_##_n] = {                        \
        .name = #_n,                    \
        .num_args = 2,                  \
        .args = { A_REG, A_IMM8_REG },  \
        .macro = false,                 \
        .instruction = I_##_n           \
    }

    DEF_OP_ARITHMETIC(ADD),
    DEF_OP_ARITHMETIC(ADC),
    DEF_OP_ARITHMETIC(AND),
    DEF_OP_ARITHMETIC(OR),
    DEF_OP_ARITHMETIC(NOR),
    DEF_OP_ARITHMETIC(CMP),
    DEF_OP_ARITHMETIC(SBB),
};

// head of memory region linked list
static struct Region* region = NULL;

void asmprint(
		const struct Context* ctx,
		const struct Token* token,
		const char* tag,
		const char* filename,
		usize line,
		const char* fmt,
		...
	) {
	va_list args;
	va_start(args, fmt);

	if ((!ctx || !ctx->verbose) && !strcmp(tag, "DEBUG")) {
		va_end(args);
		return;
	}

	char bs[4][1024];
	
