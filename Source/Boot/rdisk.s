# Function read disk
# args:
# word 1 - number of sectors to read
# word 2 - pointer to buffer

msg_error: .asciz "Can't read disk"
msg_error_size: .word .-msg_error-1

msg_success: .asciz "Disk readed successful!"
msg_success_size: .word .-msg_success-1

rdisk:
    pushw %bp
    movw %sp, %bp

    movb $0x02, %ah
    movb 4(%bp), %al    # sectors to read
    movw 6(%bp), %bx    # ptr to buffer to save

    movb $0x00, %ch
    movb $0x02, %cl     # sector number to start

    movw $0x00, %dx

    int $0x13

    jc rdisk_failed

    # print success message
    pushw $msg_success
    pushw msg_success_size
    call bprintln

    movw %bp, %sp
    popw %bp
    ret

rdisk_failed:
    pushw $msg_error
    pushw msg_error_size
    call bprintln
    hlt
