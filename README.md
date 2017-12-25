Linux System Calls Profiling
=============================

This is my course project for ECE1759.

Each system call is measured with CPU cycles (not real-time clock) in order to reduce the overhead of retriving real-time clock and increase precision.

## Test result

- Average cycles: [means.csv](./report/means.csv)
- Standard deviation: [stds.csv](./report/stds.csv)

## Cycles for all system calls

![02_fork.png](./report/02_fork.png)
![03_read.png](./report/03_read.png)
![04_write.png](./report/04_write.png)
![05_open.png](./report/05_open.png)
![06_close.png](./report/06_close.png)
![09_link.png](./report/09_link.png)
![0a_unlink.png](./report/0a_unlink.png)
![0a_unlink-removefile.png](./report/0a_unlink-removefile.png)
![0b_execve.png](./report/0b_execve.png)
![0d_time.png](./report/0d_time.png)
![0e_mknod.png](./report/0e_mknod.png)
![0f_chmod.png](./report/0f_chmod.png)
![12_stat.png](./report/12_stat.png)
![14_getpid.png](./report/14_getpid.png)
![19_stime.png](./report/19_stime.png)
![1b_alarm.png](./report/1b_alarm.png)
![1c_fstat.png](./report/1c_fstat.png)
![1e_utime.png](./report/1e_utime.png)
![26_rename.png](./report/26_rename.png)
![27_mkdir.png](./report/27_mkdir.png)
![28_rmdir.png](./report/28_rmdir.png)
![29_dup.png](./report/29_dup.png)
![2a_pipe.png](./report/2a_pipe.png)
![2b_times.png](./report/2b_times.png)
![2c_acct.png](./report/2c_acct.png)
![3c_umask.png](./report/3c_umask.png)
![3f_dup2.png](./report/3f_dup2.png)
![40_getppid.png](./report/40_getppid.png)
![41_getpgrp.png](./report/41_getpgrp.png)
