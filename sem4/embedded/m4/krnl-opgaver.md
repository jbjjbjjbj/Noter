# Opgaver

> Find 4 functioner til task, semafor, queue og message.

# Task

`k_crt_task` creates a new task and places it in the ready queue.

`k_set_prio` sets the priority of running task.

`k_sleep` put the task to sleep for some time.

`ki_task_shift` brugt internt til at skrift task.

# Semafor

`k_crt_sem` initialises a new semafor.

`k_mut_ceil_set` is called before k\_start.
And can be used to leverage priorities when other task i waiting. **I THINK**.

`k_set_sem_timer` setup a timer to trigger a semophore periodicly.

`k_signal` signal a semophore.

`k_wait` wait on a semophore.

# Queue

`k_crt_send_Q` create a new message queue.

# Message

`k_send` send a message to recieving task.

`k_receive` wait for a message froms other task.

Også funktioner til brug i interrupt, de har bare `ki_bla_bla` istedet.

