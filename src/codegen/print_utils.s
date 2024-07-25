.section .rodata
formatInt: .asciz "%d\n"
formatStr: .asciz "%s\n"

.section .text
.global printInt
printInt:
    ldr x1, =formatInt   // Load the address of the format string into x1
    bl printf            // Call printf (assumes x0 contains the integer to print)
    ret                  // Return

.global printString
printString:
    ldr x1, =formatStr   // Load the address of the format string into x1
    bl printf            // Call printf (assumes x0 contains the address of the string)
    ret                  // Return