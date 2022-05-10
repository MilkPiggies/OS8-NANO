@ifndef OSCALL_ASM
@define OSCALL_ASM

; OS HEADER
; NOT TO BE INCLUDED IN OS

@define OSCALL_OFFSET 5
@define OSCALL_SIZE   5

; === MATH.ASM ===
@define mul         ((0x00 * OSCALL_SIZE) + OSCALL_OFFSET)
@define mul16_8     ((0x01 * OSCALL_SIZE) + OSCALL_OFFSET)
@define mul16       ((0x02 * OSCALL_SIZE) + OSCALL_OFFSET)
@define cmp16       ((0x03 * OSCALL_SIZE) + OSCALL_OFFSET)
; 0x04
; 0x05
; 0x06
; 0x07

; === UTIl.ASM ===
@define strlen      ((0x08 * OSCALL_SIZE) + OSCALL_OFFSET)
@define memcpy      ((0x09 * OSCALL_SIZE) + OSCALL_OFFSET)
@define memcpy16    ((0x0A * OSCALL_SIZE) + OSCALL_OFFSET)
@define memset      ((0x0B * OSCALL_SIZE) + OSCALL_OFFSET)
; 0x0C
; 0x0D
; 0x0E
; 0x0F

; === SHIFT.ASM ===
@define shl         ((0x10 * OSCALL_SIZE) + OSCALL_OFFSET)
@define shr         ((0x11 * OSCALL_SIZE) + OSCALL_OFFSET)
; 0x12
; 0x13

; === GFX.ASM ===
@define set_pixel   ((0x14 * OSCALL_SIZE) + OSCALL_OFFSET)
@define draw_char   ((0x15 * OSCALL_SIZE) + OSCALL_OFFSET)
@define draw_str    ((0x16 * OSCALL_SIZE) + OSCALL_OFFSET)
; 0x17
; 0x18
; 0x19
; 0x1A
; 0x1B

; === TERM.ASM ===
@define term_print      ((0x1C * OSCALL_SIZE) + OSCALL_OFFSET)
@define term_print_str  ((0x1D * OSCALL_SIZE) + OSCALL_OFFSET)
@define term_clear      ((0x1E * OSCALL_SIZE) + OSCALL_OFFSET)
; 0x1F
; 0x20
; 0x21
; 0x22
; 0x23

@endif