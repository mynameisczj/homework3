;edx是人数 N
;rsi 头指针
Scores_OFFSET = 20   ;分数偏移
AVERAGE_OFFSET = 36   ; key
STRUCT_SIZE    = 38    ; 总大小  38

.code
PUBLIC AsmSortScores
PUBLIC AsmCountAverage
AsmSortScores PROC 
    push rsi
    push rdi
    push rbx

    mov rsi, rcx                ;头指针     
    imul rdx, STRUCT_SIZE
    lea rdi, [rsi + rdx]        ;尾指针
    mov rax, rsi                ;rax外层指针
outer_loop:
    lea rbx,[rax+STRUCT_SIZE]   ;rbx内层指针
inner_loop:
    cmp rbx, rdi
    jge end_inner
 ;----------------------------------------
 ;对比然后交换
    mov dx, [rax + AVERAGE_OFFSET]
    cmp dx, [rbx + AVERAGE_OFFSET] 
    jge no_swap

    movups xmm0, xmmword ptr [rax]     
    movups xmm1, xmmword ptr [rax+16]  
    mov r8w, word ptr [rax+32]  
    mov r9d, dword ptr [rax+34]

    movups xmm2, xmmword ptr [rbx]
    movups xmm3, xmmword ptr [rbx+16]
    mov r10w, word ptr [rbx+32]
    mov r11d, dword ptr [rbx+34]

    movups [rax], xmm2
    movups [rax+16], xmm3
    mov [rax+32], r10w
    mov [rax+34], r11d

    movups [rbx], xmm0
    movups [rbx+16], xmm1
    mov [rbx+32], r8w
    mov [rbx+34], r9d
;----------------------------------------
no_swap:
    add rbx, STRUCT_SIZE
    jmp inner_loop
end_inner:
    add rax, STRUCT_SIZE
    cmp rax,rdi
    jb outer_loop
exit:
    pop rbx
    pop rdi
    pop rsi
    ret
AsmSortScores ENDP

AsmCountAverage PROC 
    push rsi
    push rdi
    push rbx

    mov rsi, rcx                ;头指针     
    imul rdx, STRUCT_SIZE
    lea rdi, [rsi + rdx]        ;尾指针
    mov rax, rsi                ;rax外层指针
op_loop:
    xor ebx, ebx 
    movsx ecx, word ptr [rax + Scores_OFFSET + 0]
    add  ebx, ecx
    movsx ecx, word ptr [rax + Scores_OFFSET + 2]
    add  ebx, ecx
    movsx ecx, word ptr [rax + Scores_OFFSET + 4]
    add  ebx, ecx
    movsx ecx, word ptr [rax + Scores_OFFSET + 6]
    add  ebx, ecx
    movsx ecx, word ptr [rax + Scores_OFFSET + 8]
    add  ebx, ecx
    movsx ecx, word ptr [rax + Scores_OFFSET + 10]
    add  ebx, ecx
    movsx ecx, word ptr [rax + Scores_OFFSET + 12]
    add  ebx, ecx
    movsx ecx, word ptr [rax + Scores_OFFSET + 14]
    add  ebx, ecx
    sar ebx,3
    mov word ptr [rax + AVERAGE_OFFSET], bx
    add rax, STRUCT_SIZE
    cmp rax,rdi
    jb op_loop
exit:
    pop rbx
    pop rdi
    pop rsi
    ret
AsmCountAverage ENDP
END