;edx是人数 N
;rsi 头指针
AVERAGE_OFFSET = 36   ; short average（36-37）
STRUCT_SIZE    = 38    ; 总大小 = 38
.code
PUBLIC AsmSortScores
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

    vmovups ymm0, ymmword ptr [rax]     
    mov r8w, word ptr [rax+32]  
    mov r9d, dword ptr [rax+34]

    vmovups ymm1, ymmword ptr [rbx]
    mov r10w, word ptr [rbx+32]
    mov r11d, dword ptr [rbx+34]

    vmovups [rax], ymm1
    mov [rax+32], r10w
    mov [rax+34], r11d

    vmovups [rbx], ymm0
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
END