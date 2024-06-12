; Your First Assembly Program "Blinky"
; https://www.youtube.com/watch?v=7XG-JveGBjA&list=PL643xA3Ie_EuHoNV7AgvJXq-z1hrE8vsm&index=11

;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------

init:
            bic.w   #0001h, &PM5CTL0        ; disabled the GPIO power-on HighZ
            bis.b   #01h,   &P1DIR          ; setting the P1.0 as an output (P1.0=LED1)

main:
            xor.b   #01h,   &P1OUT          ; toggle P1.0 (LED1)

            mov.w   #0FFFFh, R4              ; puts a big number in R4

delay:
            dec.w   R4                      ; decrement R4
            jnz     delay                   ; repeat until R4=0

            jmp     main                    ; repeat main loop forever
            NOP

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
