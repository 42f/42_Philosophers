./bvalette_philo_one_tester.sh
./bvalette_philo_one_test_5_800_200_200_7.sh

# from repo root :
ls --directory philo_one philo_three philo_two | xargs -I % sh -c 'make -C % re'
ls --directory philo_one philo_three philo_two | xargs --verbose -L 20 -I % sh -c 'timeout 2 %/philo_*  2 310 200 100 ; echo'
