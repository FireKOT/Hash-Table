
section .text

        global hashTableFindAsm


hashTableFindAsm:

        push    rbp
        mov     rbp, rsp
        push    r12
        mov     r12, rsi
        push    rbx
        mov     rbx, rdi
        and     rsp, -32

        mov     rdi, rsi                ;-------------------------------
        call    [rbx + 8]               ;get id of list in table
                                        ;
        xor     edx, edx                ;
        div     QWORD [rbx+16]          ;-------------------------------

        mov     rax, [rbx]              ;-------------------------------
        lea     rdx, [rdx + rdx * 8]    ;get cur_node_id in list = head
        lea     rdx, [rax + rdx * 8]    ;
        mov     rax, [rdx + 8]          ;-------------------------------

        mov     rdi, [rdx + 32]
        test    rdi, rdi
        je      .not_found

        mov     r8,   [rdx]             ;set locally const values
        vmovdqa ymm1, [r12]             ;in registers

        xor     edx, edx
        jmp     .check_str

        .while:

                add     rdx, 1
                mov     rax, [rax + 8]
                cmp     rdx, rdi
                je      .not_found

        .check_str:

                lea     rax, [rax + rax * 2]            ;-------------------------------  
                lea     rax, [r8 + rax * 8]             ;get new string in list
                mov     rcx, [rax]                      ;-------------------------------  

                vpcmpeqb        ymm0, ymm1, [rcx]       ;-------------------------------  
                vpmovmskb       ecx, ymm0               ;fast string comparision                              
                cmp     ecx, -1                         ; 
                jne     .while                          ;------------------------------- 

                mov     eax, 1          ;-------------------------------       
                lea     rsp, [rbp - 16] ;if found        
                pop     rbx             ;
                pop     r12             ;
                pop     rbp             ;
                ret                     ;-------------------------------

        .not_found:

                xor     eax, eax        ;-------------------------------
                lea     rsp, [rbp - 16] ;if not found
                pop     rbx             ;
                pop     r12             ;
                pop     rbp             ;
                ret                     ;-------------------------------

