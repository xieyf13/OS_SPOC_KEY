13.1 总体介绍

(1) ucore的线程控制块数据结构是什么？

proc_struct


13.2 关键数据结构

(2) 如何知道ucore的两个线程同在一个进程？

查看两个线程的 cr3 和 mm_struct 是否相同，若相同则为同一进程。

(3) context和trapframe分别在什么时候用到？

context保存为的进程的上下文，在进程切换的时候会用到context。

trapframe是中断帧的指针，当发生中断、异常或者系统调用时，用于保存此进程或者线程在被中断前的状态。

(4) 用户态或内核态下的中断处理有什么区别？在trapframe中有什么体现？

用户态进入中断时，需要从用户栈切换到内核栈，因此需要首先额外保存ss和esp两个寄存器。

内核态进入中断时，不需要进行栈的切换，因此只需要压入error code，cs，eip，flags。

13.3 执行流程

(5) do_fork中的内核线程执行的第一条指令是什么？它是如何过渡到内核线程对应的函数的？

由在 /kern/process/proc.c 中 kernel_thread 处

tf.tf_eip = (uint32_t)kernel_thread_entry;

可见内核线程执行的第一条指令在 /kern/process/entry.S 中 kernel_thread_entry 处，为 pushl %edx

kernel thread调用之后，先把临时变量tf传递给do_fork函数，之后会执行 kernel_thread_entry 部分。


(6)内核线程的堆栈初始化在哪？

tf和context中的esp


(7)fork()父子进程的返回值是不同的。这在源代码中的体现中哪？

根据 /kern/process/proc.c 中的 do_fork() 函数，

父进程调用时，由 ret = proc->pid; 父进程的返回值是子进程的pid。

子进程调用时，由 proc->tf->tf_regs.reg_eax = 0; 子进程的返回值是0。



(8)内核线程initproc的第一次执行流程是什么样的？能跟踪出来吗？

