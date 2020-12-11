==24326== drd, a thread error detector
==24326== Copyright (C) 2006-2017, and GNU GPL'd, by Bart Van Assche.
==24326== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==24326== Command: ./philo_one 8 800 200 200 1
==24326== 
==24326== Conflicting store by thread 1 at 0x0545e300 size 4
==24326==    at 0x108FD2: thread_creation_loop (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==24326==    by 0x109157: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==24326==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==24326== Address 0x545e300 is at offset 0 from 0x545e300. Allocation context:
==24326==    at 0x4C32F2F: malloc (in /usr/lib/valgrind/vgpreload_drd-amd64-linux.so)
==24326==    by 0x1092D2: init_arrays (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==24326==    by 0x1090F0: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==24326==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==24326== Other segment start (thread 3)
==24326==    (thread finished, call stack no longer available)
==24326== Other segment end (thread 3)
==24326==    (thread finished, call stack no longer available)
==24326== 
==24326== Thread 11:
==24326== Conflicting store by thread 11 at 0x0545e038 size 8
==24326==    at 0x109485: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==24326==    by 0x4C36413: ??? (in /usr/lib/valgrind/vgpreload_drd-amd64-linux.so)
==24326==    by 0x4E556DA: start_thread (pthread_create.c:463)
==24326==    by 0x518EA3E: clone (clone.S:95)
==24326== Address 0x545e038 is at offset 8 from 0x545e030. Allocation context:
==24326==    at 0x4C32F2F: malloc (in /usr/lib/valgrind/vgpreload_drd-amd64-linux.so)
==24326==    by 0x108CA9: init_philo_info_storage (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==24326==    by 0x108ECC: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==24326== Other segment start (thread 3)
==24326==    (thread finished, call stack no longer available)
==24326== Other segment end (thread 3)
==24326==    (thread finished, call stack no longer available)
==24326== Other segment start (thread 3)
==24326==    (thread finished, call stack no longer available)
==24326== Other segment end (thread 3)
==24326==    (thread finished, call stack no longer available)
==24326== 
==24326== 
==24326== For counts of detected and suppressed errors, rerun with: -v
==24326== ERROR SUMMARY: 9 errors from 2 contexts (suppressed: 174 from 22)
