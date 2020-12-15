==20042== Helgrind, a thread error detector
==20042== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==20042== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==20042== Command: ./philo_one 8 800 200 200 1
==20042== 
==20042== ---Thread-Announcement------------------------------------------
==20042== 
==20042== Thread #3 was created
==20042==    at 0x5182A2E: clone (clone.S:71)
==20042==    by 0x4E49EC4: create_thread (createthread.c:100)
==20042==    by 0x4E49EC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
==20042==    by 0x4C36A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x109010: thread_creation_loop (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10910E: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042== 
==20042== ---Thread-Announcement------------------------------------------
==20042== 
==20042== Thread #2 was created
==20042==    at 0x5182A2E: clone (clone.S:71)
==20042==    by 0x4E49EC4: create_thread (createthread.c:100)
==20042==    by 0x4E49EC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
==20042==    by 0x4C36A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x109010: thread_creation_loop (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10910E: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042== 
==20042== ----------------------------------------------------------------
==20042== 
==20042== Possible data race during read of size 8 at 0x30B038 by thread #3
==20042== Locks held: none
==20042==    at 0x10A04A: get_current_time (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109462: init_data (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1094A1: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042== 
==20042== This conflicts with a previous write of size 8 by thread #2
==20042== Locks held: none
==20042==    at 0x10A05A: get_current_time (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109462: init_data (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1094A1: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042==  Address 0x30b038 is 0 bytes inside data symbol "origin_time.4189"
==20042== 
==20042== ---Thread-Announcement------------------------------------------
==20042== 
==20042== Thread #4 was created
==20042==    at 0x5182A2E: clone (clone.S:71)
==20042==    by 0x4E49EC4: create_thread (createthread.c:100)
==20042==    by 0x4E49EC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
==20042==    by 0x4C36A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x109010: thread_creation_loop (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10910E: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042== 
==20042== ---Thread-Announcement------------------------------------------
==20042== 
==20042== Thread #1 is the program's root thread
==20042== 
==20042== ----------------------------------------------------------------
==20042== 
==20042==  Lock at 0x5452258 was first observed
==20042==    at 0x4C37F2A: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x109245: init_mutex (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1090CF: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Address 0x5452258 is 120 bytes inside a block of size 360 alloc'd
==20042==    at 0x4C30F2F: malloc (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x108D1C: init_philo_info_storage (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108ECC: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Block was alloc'd by thread #1
==20042== 
==20042== Possible data race during read of size 1 at 0x5452193 by thread #4
==20042== Locks held: none
==20042==    at 0x10977E: try_grab_fork (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109846: get_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1098CD: acquire_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1095D3: take_forks_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109510: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042== 
==20042== This conflicts with a previous write of size 1 by thread #3
==20042== Locks held: 1, at address 0x5452258
==20042==    at 0x1097D3: try_grab_fork (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10985B: get_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1098CD: acquire_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1095D3: take_forks_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109510: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042==  Address 0x5452193 is 3 bytes inside a block of size 9 alloc'd
==20042==    at 0x4C30F2F: malloc (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x108CF5: init_philo_info_storage (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108ECC: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Block was alloc'd by thread #1
==20042== 
==20042== ----------------------------------------------------------------
==20042== 
==20042== Possible data race during write of size 1 at 0x5452192 by thread #2
==20042== Locks held: none
==20042==    at 0x109904: drop_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10972E: done_eating_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10957B: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042== 
==20042== This conflicts with a previous read of size 1 by thread #3
==20042== Locks held: none
==20042==    at 0x10977E: try_grab_fork (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109846: get_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1098CD: acquire_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1095D3: take_forks_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109510: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042==  Address 0x5452192 is 2 bytes inside a block of size 9 alloc'd
==20042==    at 0x4C30F2F: malloc (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x108CF5: init_philo_info_storage (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108ECC: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Block was alloc'd by thread #1
==20042== 
==20042== ----------------------------------------------------------------
==20042== 
==20042==  Lock at 0x5452230 was first observed
==20042==    at 0x4C37F2A: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x109245: init_mutex (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1090CF: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Address 0x5452230 is 80 bytes inside a block of size 360 alloc'd
==20042==    at 0x4C30F2F: malloc (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x108D1C: init_philo_info_storage (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108ECC: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Block was alloc'd by thread #1
==20042== 
==20042== Possible data race during read of size 1 at 0x5452192 by thread #3
==20042== Locks held: 1, at address 0x5452230
==20042==    at 0x1097BC: try_grab_fork (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109846: get_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1098CD: acquire_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1095D3: take_forks_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109510: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042== 
==20042== This conflicts with a previous write of size 1 by thread #2
==20042== Locks held: none
==20042==    at 0x109904: drop_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10972E: done_eating_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10957B: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042==  Address 0x5452192 is 2 bytes inside a block of size 9 alloc'd
==20042==    at 0x4C30F2F: malloc (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x108CF5: init_philo_info_storage (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108ECC: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Block was alloc'd by thread #1
==20042== 
==20042== ----------------------------------------------------------------
==20042== 
==20042==  Lock at 0x5452230 was first observed
==20042==    at 0x4C37F2A: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x109245: init_mutex (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1090CF: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Address 0x5452230 is 80 bytes inside a block of size 360 alloc'd
==20042==    at 0x4C30F2F: malloc (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x108D1C: init_philo_info_storage (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108ECC: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Block was alloc'd by thread #1
==20042== 
==20042== Possible data race during write of size 1 at 0x5452192 by thread #3
==20042== Locks held: 1, at address 0x5452230
==20042==    at 0x1097D3: try_grab_fork (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109846: get_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1098CD: acquire_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1095D3: take_forks_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109510: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042== 
==20042== This conflicts with a previous write of size 1 by thread #2
==20042== Locks held: none
==20042==    at 0x109904: drop_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10972E: done_eating_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10957B: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042==  Address 0x5452192 is 2 bytes inside a block of size 9 alloc'd
==20042==    at 0x4C30F2F: malloc (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x108CF5: init_philo_info_storage (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108ECC: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Block was alloc'd by thread #1
==20042== 
==20042== ---Thread-Announcement------------------------------------------
==20042== 
==20042== Thread #5 was created
==20042==    at 0x5182A2E: clone (clone.S:71)
==20042==    by 0x4E49EC4: create_thread (createthread.c:100)
==20042==    by 0x4E49EC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
==20042==    by 0x4C36A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x109010: thread_creation_loop (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10910E: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042== 
==20042== ----------------------------------------------------------------
==20042== 
==20042==  Lock at 0x1FFF000100 was first observed
==20042==    at 0x4C37F2A: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x1091DD: init_mutex (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1090CF: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Address 0x1fff000100 is on thread #1's stack
==20042==  in frame #4, created by main (???:)
==20042== 
==20042== Possible data race during write of size 1 at 0x1FFF0000A0 by thread #3
==20042== Locks held: 1, at address 0x1FFF000100
==20042==    at 0x10A14B: check_aliveness (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1094C1: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042== 
==20042== This conflicts with a previous read of size 1 by thread #5
==20042== Locks held: none
==20042==    at 0x109860: get_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1098CD: acquire_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1095D3: take_forks_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109510: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042==  Address 0x1fff0000a0 is on thread #1's stack
==20042==  in frame #4, created by main (???:)
==20042== 
==20042== ----------------------------------------------------------------
==20042== 
==20042==  Lock at 0x1FFF000100 was first observed
==20042==    at 0x4C37F2A: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x1091DD: init_mutex (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1090CF: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Address 0x1fff000100 is on thread #1's stack
==20042==  in frame #4, created by main (???:)
==20042== 
==20042== Possible data race during read of size 1 at 0x1FFF0000A0 by thread #4
==20042== Locks held: none
==20042==    at 0x109860: get_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1098CD: acquire_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1095D3: take_forks_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109510: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042== 
==20042== This conflicts with a previous write of size 1 by thread #3
==20042== Locks held: 1, at address 0x1FFF000100
==20042==    at 0x10A14B: check_aliveness (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1094C1: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042==  Address 0x1fff0000a0 is on thread #1's stack
==20042==  in frame #4, created by main (???:)
==20042== 
==20042== ----------------------------------------------------------------
==20042== 
==20042== Possible data race during write of size 1 at 0x5452193 by thread #4
==20042== Locks held: none
==20042==    at 0x109917: drop_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10972E: done_eating_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10957B: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042== 
==20042== This conflicts with a previous read of size 1 by thread #3
==20042== Locks held: none
==20042==    at 0x10977E: try_grab_fork (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10985B: get_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1098CD: acquire_forks (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1095D3: take_forks_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109510: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042==  Address 0x5452193 is 3 bytes inside a block of size 9 alloc'd
==20042==    at 0x4C30F2F: malloc (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x108CF5: init_philo_info_storage (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108ECC: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Block was alloc'd by thread #1
==20042== 
==20042== ---Thread-Announcement------------------------------------------
==20042== 
==20042== Thread #6 was created
==20042==    at 0x5182A2E: clone (clone.S:71)
==20042==    by 0x4E49EC4: create_thread (createthread.c:100)
==20042==    by 0x4E49EC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
==20042==    by 0x4C36A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x109010: thread_creation_loop (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10910E: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042== 
==20042== ----------------------------------------------------------------
==20042== 
==20042==  Lock at 0x1FFF000100 was first observed
==20042==    at 0x4C37F2A: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x1091DD: init_mutex (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1090CF: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Address 0x1fff000100 is on thread #1's stack
==20042==  in frame #4, created by main (???:)
==20042== 
==20042== Possible data race during read of size 1 at 0x1FFF0000A0 by thread #6
==20042== Locks held: none
==20042==    at 0x10992C: check_loop_conditions (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10955C: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042== 
==20042== This conflicts with a previous write of size 1 by thread #3
==20042== Locks held: 1, at address 0x1FFF000100
==20042==    at 0x10A14B: check_aliveness (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1094C1: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042==  Address 0x1fff0000a0 is on thread #1's stack
==20042==  in frame #4, created by main (???:)
==20042== 
==20042== ----------------------------------------------------------------
==20042== 
==20042== Possible data race during write of size 4 at 0x5452390 by thread #1
==20042== Locks held: none
==20042==    at 0x108FD2: thread_creation_loop (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10912C: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042== 
==20042== This conflicts with a previous read of size 4 by thread #2
==20042== Locks held: none
==20042==    at 0x10948C: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042==  Address 0x5452390 is 0 bytes inside a block of size 36 alloc'd
==20042==    at 0x4C30F2F: malloc (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x109296: init_arrays (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1090F0: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Block was alloc'd by thread #1
==20042== 
==20042== ---Thread-Announcement------------------------------------------
==20042== 
==20042== Thread #10 was created
==20042==    at 0x5182A2E: clone (clone.S:71)
==20042==    by 0x4E49EC4: create_thread (createthread.c:100)
==20042==    by 0x4E49EC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
==20042==    by 0x4C36A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x109010: thread_creation_loop (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10912C: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042== 
==20042== ----------------------------------------------------------------
==20042== 
==20042==  Lock at 0x1FFF000100 was first observed
==20042==    at 0x4C37F2A: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x1091DD: init_mutex (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1090CF: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Address 0x1fff000100 is on thread #1's stack
==20042==  in frame #4, created by main (???:)
==20042== 
==20042== Possible data race during read of size 1 at 0x1FFF0000A0 by thread #10
==20042== Locks held: none
==20042==    at 0x1099BF: loop_condition (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x109A54: philo_monitor (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042== 
==20042== This conflicts with a previous write of size 1 by thread #3
==20042== Locks held: 1, at address 0x1FFF000100
==20042==    at 0x10A14B: check_aliveness (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x1094C1: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042==  Address 0x1fff0000a0 is on thread #1's stack
==20042==  in frame #4, created by main (???:)
==20042== 
==20042== ----------------------------------------------------------------
==20042== 
==20042== Possible data race during read of size 1 at 0x5452141 by thread #10
==20042== Locks held: none
==20042==    at 0x109A69: philo_monitor (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042== 
==20042== This conflicts with a previous write of size 1 by thread #2
==20042== Locks held: none
==20042==    at 0x10971B: done_eating_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10957B: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042==  Address 0x5452141 is 1 bytes inside a block of size 9 alloc'd
==20042==    at 0x4C30F2F: malloc (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x108CDD: init_philo_info_storage (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108ECC: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Block was alloc'd by thread #1
==20042== 
==20042== ---Thread-Announcement------------------------------------------
==20042== 
==20042== Thread #11 was created
==20042==    at 0x5182A2E: clone (clone.S:71)
==20042==    by 0x4E49EC4: create_thread (createthread.c:100)
==20042==    by 0x4E49EC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
==20042==    by 0x4C36A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x109010: thread_creation_loop (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10912C: process_philo (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108EDB: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042== 
==20042== ----------------------------------------------------------------
==20042== 
==20042== Possible data race during write of size 1 at 0x5452142 by thread #3
==20042== Locks held: none
==20042==    at 0x10971B: done_eating_action_handler (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x10957B: philo_state_machine (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042== 
==20042== This conflicts with a previous read of size 1 by thread #11
==20042== Locks held: none
==20042==    at 0x109A69: philo_monitor (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x4E496DA: start_thread (pthread_create.c:463)
==20042==    by 0x5182A3E: clone (clone.S:95)
==20042==  Address 0x5452142 is 2 bytes inside a block of size 9 alloc'd
==20042==    at 0x4C30F2F: malloc (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20042==    by 0x108CDD: init_philo_info_storage (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==    by 0x108ECC: main (in /home/user42/42/42_Philosophers/philo_one/philo_one)
==20042==  Block was alloc'd by thread #1
==20042== 
==20042== 
==20042== For counts of detected and suppressed errors, rerun with: -v
==20042== Use --history-level=approx or =none to gain increased speed, at
==20042== the cost of reduced accuracy of conflicting-access information
==20042== ERROR SUMMARY: 57 errors from 13 contexts (suppressed: 869 from 72)
