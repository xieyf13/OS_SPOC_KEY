在什么地方设置的定时器?

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
timer_init 初始化timer
add_timer  设置定时器.



它对应的等待队列是哪个?

timer_list



它的唤醒操作在什么地方?


在run_timer_list中，有
wakeup_proc(proc);
del_timer(timer);
唤醒timer对应的进程, wakeup_proc是将相应进程加入可运行的队列中.