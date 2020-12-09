
true > /tmp/a
make && watch -pn 0.2 './philo_one 3 900 200 200 10 | grep "died" >> /tmp/a | echo >> /tmp/a ; cat /tmp/a | tail --lines 50'

# should be 1 line of "died" then 1 kline with dots, never more lines inbetween dots.
true > /tmp/a
make && watch -pn 0.2 './philo_one 3 900 200 200 | grep "died" >> /tmp/a | echo ...... >> /tmp/a ; cat /tmp/a | tail --lines 50'


./philo_one 0 500 200 200 1 ; echo ; ./philo_one 1 500 200 200 1 ; echo ;./philo_one 2 500 200 200 1; echo ;./philo_one 3 500 200 200 1
