��ʲô�ط����õĶ�ʱ��?

// do_sleep - set current process state to sleep and add timer with "time"
//          - then call scheduler. if process run again, delete timer first.
int
do_sleep(unsigned int time) {
    if (time == 0) {
        return 0;
    }
    bool intr_flag;
    local_intr_save(intr_flag);
    timer_t __timer, *timer = timer_init(&__timer, current, time);
    current->state = PROC_SLEEPING;
    current->wait_state = WT_TIMER;
    add_timer(timer);
    local_intr_restore(intr_flag);

    schedule();

    del_timer(timer);
    return 0;
}
timer_init ��ʼ��timer
add_timer  ���ö�ʱ��.



����Ӧ�ĵȴ��������ĸ�?

timer_list



���Ļ��Ѳ�����ʲô�ط�?


��run_timer_list�У���
wakeup_proc(proc);
del_timer(timer);
����timer��Ӧ�Ľ���, wakeup_proc�ǽ���Ӧ���̼�������еĶ�����.