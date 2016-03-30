
子进程调用do_exit(int error_code) 函数 ( kern/process/proc.c/line449)
设置子进程的error_code，以及子进程的状态
current->state = PROC_ZOMBIE;
current->exit_code = error_code;
之后会尝试唤醒他的父进程, 如果父进程处于等待状态的话, 就唤起父进程, 如果父进程处于僵尸状态, 那么就唤起initproc.

父进程调用do_wait(int pid, int *code_store) 函数（kern/process/proc.c/line698）

repeat:
 if (pid != 0) {
        proc = find_proc(pid);
找到退出的子进程PCB（处于PROC_ZOMBIE状态）
 
found:
    if (proc == idleproc || proc == initproc) {
        panic("wait idleproc or initproc.\n");
    }
    if (code_store != NULL) {
        *code_store = proc->exit_code;
    }
 
设置code_store为子进程的exit_code,即把子进程的error_code存回父进程的返回值。