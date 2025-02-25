.psx
.create "asm_hellogpu.bin", 0x80010000

.org 0x80010000

IO_BASE_ADDR equ 0x1F80 ;IO PORTS MEMORY MAP BASE ADDRESS

GP0 equ 0x1810 ; GP0 register @ $1F801810 : Rendering data & VRAM ACCESS
GP1 equ 0x1814 ; GP1 register @ $1F801814 : Display Control & Environment SETUP

Main:
    lui $t0, IO_BASE_ADDR ; t0 = IO PORT BASE ADDRESS  just upper part $(1F80****)
;--------------------------------------------------
; Send Commands to GP1 (Mapped at 0x1F801814)
; This GP1 is for display Control and env setup
; ( Command = 8-bit MSB , Parameter = 24-bit LSB )
; CCPPPPPP : CC = COMMAND , PPPPPP = PARAMETERS 
;--------------------------------------------------


; DISPLAY CONTROL PACKETS TO GP1

    li $t1, 0x00000000   ; Command 0x00 = reset gpu
    sw $t1, GP1($t0)     ; Write Packet to GP1
    
    li $t1, 0x03000000   ; 03h = Display ENABLE packet
    sw $t1, GP1($t0)     ; Write Packet to GP0

    li $t1, 0x08000001  ; 08h = Display Mode (320x240 ,NTSC ,15bit color depth)
    sw $t1, GP1($t0)      ; Write to GP1

    li $t1, 0x06C60260  ; 06h = Horizontal Display Range packet (see nopsx documentation)
    sw $t1, GP1($t0)      ; Write to GP1

    li $t1, 0x07042018  ; 08h = Vertical Display Range packet (see nopsx documentation)
    sw $t1, GP1($t0)      ; Write to GP1

; Setup VRAM ACCESS GP0

;--------------------------------------------------
; Send Commands to GP0 (Mapped at 0x1F801810)
; These GP0 commands are used to setup the drawing area
; ( Command = 8-bit MSB , Parameter = 24-bit LSB )
; CCPPPPPP : CC = COMMAND , PPPPPP = PARAMETERS 
;--------------------------------------------------
  
  li $t1, 0xE1000400         ; E1 = Draw Mode Settings
  sw $t1, GP0($t0)			     ; Write to GP0

  li $t1, 0xE3000000		     ; E3 = Drawing Area TopLeft - 0bYYYYYYYYYYXXXXXXXXXX (10 bits for Y and X)
  sw $t1, GP0($t0)	         ; Write to GP0
  
  li $t1, 0xE403BD3F         ; E4 = Drawing area BottomRight - 0bYYYYYYYYYYXXXXXXXXXX (10 bits for X=319 and Y=239)
  sw $t1, GP0($t0)           ; Write to GP0

  li $t1, 0xE5000000         ; E5 = Drawing Offset - 0bYYYYYYYYYYYXXXXXXXXXXXX (X=0, Y=0)
  sw $t1, GP0($t0)		       ; Write to GP0


;----------- Filing Screen With a White Rectangle

  li $t1, 0x02FFFFFF          ; First Command to Fill Screen with blue rectangle CCBbGgRr (SEE NOPSX DOC)
  sw $t1, GP0($t0)             ; Write to GP0

  li $t1, 0x00000000           ; 
  sw $t1, GP0($t0)

  li $t1, 0x00EF013F            ; Write to GP0
  sw $t1, GP0($t0)

;----------- Drawing a Green flat triangle

; GP0(20h) - Monochrome three-point polygon, opaque
; 1st  Color+Command     (CcBbGgRrh)
; 2nd  Vertex1           (YyyyXxxxh)
; 3rd  Vertex2           (YyyyXxxxh)
; 4th  Vertex3           (YyyyXxxxh)

  li $t1, 0x2000FF00  ; 1st  Color+Command     (CcBbGgRrh)
  sw $t1, GP0($t0)

  li $t1, 0x005A0096  ; 2nd  Vertex1           (YyyyXxxxh)
  sw $t1, GP0($t0)

  li $t1, 0x00C80050  ; 3rd  Vertex2           (YyyyXxxxh)
  sw $t1, GP0($t0)

  li $t1, 0x00C800FA  ; 4th  Vertex3           (YyyyXxxxh)
  sw $t1, GP0($t0)

;----------- Drawing a Blue flat shaded quad

; GP0(28h) - Monochrome four-point polygon, opaque
; 1st  Color+Command     (CcBbGgRrh)
; 2nd  Vertex1           (YyyyXxxxh)
; 3rd  Vertex2           (YyyyXxxxh)
; 4th  Vertex3           (YyyyXxxxh)
; (5th) Vertex4           (YyyyXxxxh)

  li $t1, 0x28FF0000  ; 1st  Color+Command     (CcBbGgRrh)
  sw $t1, GP0($t0)

  li $t1, 0x00000000  ; 2nd  Vertex1           (YyyyXxxxh)
  sw $t1, GP0($t0)

  li $t1, 0x00000040  ; 3rd  Vertex2           (YyyyXxxxh)
  sw $t1, GP0($t0)

  li $t1, 0x00400000  ; 4th  Vertex3           (YyyyXxxxh)
  sw $t1, GP0($t0)

  li $t1, 0x00400040  ; 5th  Vertex4           (YyyyXxxxh)
  sw $t1, GP0($t0)


;----------- Drawing a gouraud shaded triangle

; GP0(30h) - Shaded three-point polygon, opaque
;  1st  Color1+Command    (CcBbGgRrh)
;  2nd  Vertex1           (YyyyXxxxh)
;  3rd  Color2            (00BbGgRrh)
;  4th  Vertex2           (YyyyXxxxh)
;  5th  Color3            (00BbGgRrh)
;  6th  Vertex3           (YyyyXxxxh)

  li $t1, 0x3000FF00  ; 1st  Color1+Command     (CcBbGgRrh)
  sw $t1, GP0($t0)

  li $t1, 0x00D20000  ; 2nd  Vertex1           (YyyyXxxxh)
  sw $t1, GP0($t0)

  li $t1, 0x00FF0000  ; 3rd  Color2         (00BbGgRrh)
  sw $t1, GP0($t0)

  li $t1, 0x00820028  ; 4th  Vertex2          (YyyyXxxxh)
  sw $t1, GP0($t0)

  li $t1, 0x000000FF  ; 5th  Color3          (00BbGgRrh)
  sw $t1, GP0($t0)

  li $t1, 0x00D20050  ; 5th  Vertex3         (YyyyXxxxh)
  sw $t1, GP0($t0)

; ---------------------------------------------------------------------------
  ; Set $a0 as the global parameter with the IO_BASE_ADDR to be used by subs
  ; Set $sp (the stack pointer to an address)
  ; ---------------------------------------------------------------------------
  lui $a0, IO_BASE_ADDR      ; Global Param: I/O Port Base Address (0x1F80****)
  la $sp, 0x00103CF0
  ; ---------------------------------------------------------------------------
  ; Draw a Blue flat-shaded triangle using a subroutine and a stack pointer
  ; ---------------------------------------------------------------------------

  addiu $sp, -(4 * 7)   ; declaring that there are 7 variables to put to the stack (4 bytes = 1 word * 7)

  li $t0, 0xFF0000           ; Param: Color (0xBBGGRR)
  sw $t0, 0($sp)

  li $t0, 200                ; Param: x1
  sw $t0, 4($sp)

  li $t0, 40                 ; Param: y1
  sw $t0, 8($sp)

  li $t0, 288                ; Param: x2
  sw $t0, 12($sp)

  li $t0, 56                 ; Param: y2
  sw $t0, 16($sp)

  li $t0, 224                ; Param: x3
  sw $t0, 20($sp)

  li $t0, 200                ; Param: y3
  sw $t0, 24($sp)

  jal DrawFlatTriangle       ; Invoke Draw Triangle subroutine with params
  nop

LoopForever:
    j LoopForever
    nop

; -----------------------------------------------------------------------------
; Subroutine to draw a flat-shaded triangle on the screen (3 vertices)
; Arguments:
; $a0 = IO_BASE_ADDR (IO ports are at address 0x1F80)
; 0($sp) = Color (for example: 0xBBGGRR)
; 4($sp) = x1
; 8($sp) = y1
; 12($sp) = x2
; 16($sp) = y2
; 20($sp) = x3
; 24($sp) = y3
; -----------------------------------------------------------------------------

DrawFlatTriangle:

  lui $t0, 0x2000            ; Command: 0x20 (flat triangle)
  lw  $t1, 0($sp)
  nop
  or  $t1, $t0, $t1          ; Command | Color
  sw  $t1, GP0($a0)          ; Write to GP0 (Command|Color)

  addi $sp ,$sp ,0x4

; now x1 and y1

  lw   $t1, 0($sp)           ; store x1 to $t1 ( you cant just andi on the $sp you have to load it first to a register then perform the and operation)
  nop
  andi $t1, $t1, 0xFFFF      ; x1 &= 0xFFFF

  addi $sp ,$sp ,0x4         ; increment stack pointer

  lh   $t2,0($sp)   ; (same goes for bit shifting you have to load to the register first)
  nop
  sll  $t2, $t2, 16          ; y1 <<= 16
  or   $t1,$t2,$t1
  sw   $t1, GP0($a0)         ; Write to GP0 (Vertex 1)

  addi $sp ,$sp ,0x4            
; now x2 and y2

  lw   $t1, 0($sp)           ; store x2 to $t1
  nop
  andi $t1, $t1, 0xFFFF      ; x2 &= 0xFFFF

  addi $sp ,$sp ,0x4         ; increment stack pointer

  lh   $t2,0($sp)
  nop
  sll  $t2, $t2, 16          ; y2 <<= 16
  or   $t1,$t2,$t1
  sw   $t1, GP0($a0)         ; Write to GP0 (Vertex 2)

  addi $sp ,$sp ,0x4            
 ; now x3 and y3

  lw   $t1, 0($sp)           ; store x3 to $t1  ( you cant just andi on the $sp you have to load it first to a register then perform the and operation)
  nop
  andi $t1, $t1, 0xFFFF      ; x3 &= 0xFFFF

  addi $sp ,$sp ,0x4         ; increment stack pointer

  lh   $t2,0($sp)
  nop
  sll  $t2, $t2, 16          ; y3 <<= 16
  or   $t1,$t2,$t1
  sw   $t1, GP0($a0)         ; Write to GP0 (Vertex 3)

  addi $sp ,$sp ,0x4            

  jr $ra                     ; Return address (stored in register $ra)
  nop


.close