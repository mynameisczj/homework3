; 定义结构体偏移量（严格匹配 C++ 代码）
SNAME_OFFSET   = 0    ; char name[8]
SID_OFFSET     = 8    ; char sid[11]
SCORES_OFFSET  = 20   ; short scores[8]（20-35）
AVERAGE_OFFSET = 36   ; short average（36-37）
STRUCT_SIZE    = 38    ; 总大小 = 38

.code
PUBLIC AsmSortScores
AsmSortScores PROC FRAME
    push rsi
    .PUSHREG rsi
    push rdi
    .PUSHREG rdi
    push rbx
    .PUSHREG rbx
    .ENDPROLOG

    mov rsi, rcx              
    mov ecx, edx              
    dec ecx                   

outer_loop:
    mov rdi, rsi             
    lea rbx, [rsi + STRUCT_SIZE] 
    mov eax, ecx             

inner_loop:
    
    mov r8, rsi
    mov r9, rdx
    imul r9, STRUCT_SIZE
    add r8, r9               

    cmp rbx, r8
    jge no_swap              

    
    mov dx, [rdi + AVERAGE_OFFSET]  
    cmp dx, [rbx + AVERAGE_OFFSET] 
    jge no_swap                     

    
    movdqu xmm0, xmmword ptr [rdi]      
    movdqu xmm1, xmmword ptr [rdi+16]   
    mov r8w, word ptr [rdi+32]          
    mov r9d, dword ptr [rdi+34]         

    
    movdqu xmm2, xmmword ptr [rbx]
    movdqu xmm3, xmmword ptr [rbx+16]
    mov r10w, word ptr [rbx+32]
    mov r11d, dword ptr [rbx+34]


    movdqu [rdi], xmm2
    movdqu [rdi+16], xmm3
    mov [rdi+32], r10w
    mov [rdi+34], r11d

    movdqu [rbx], xmm0
    movdqu [rbx+16], xmm1
    mov [rbx+32], r8w
    mov [rbx+34], r9d

no_swap:
    add rdi, STRUCT_SIZE      
    add rbx, STRUCT_SIZE
    dec eax
    jnz inner_loop

    loop outer_loop

exit:
    pop rbx
    pop rdi
    pop rsi
    ret
AsmSortScores ENDP
END