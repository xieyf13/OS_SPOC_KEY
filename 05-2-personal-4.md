
�ӽ��̵���do_exit(int error_code) ���� ( kern/process/proc.c/line449)
�����ӽ��̵�error_code���Լ��ӽ��̵�״̬
current->state = PROC_ZOMBIE;
current->exit_code = error_code;
֮��᳢�Ի������ĸ�����, ��������̴��ڵȴ�״̬�Ļ�, �ͻ��𸸽���, ��������̴��ڽ�ʬ״̬, ��ô�ͻ���initproc.

�����̵���do_wait(int pid, int *code_store) ������kern/process/proc.c/line698��

repeat:
 if (pid != 0) {
        proc = find_proc(pid);
�ҵ��˳����ӽ���PCB������PROC_ZOMBIE״̬��
 
found:
    if (proc == idleproc || proc == initproc) {
        panic("wait idleproc or initproc.\n");
    }
    if (code_store != NULL) {
        *code_store = proc->exit_code;
    }
 
����code_storeΪ�ӽ��̵�exit_code,�����ӽ��̵�error_code��ظ����̵ķ���ֵ��