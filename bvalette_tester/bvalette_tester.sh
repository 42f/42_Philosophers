
true > /tmp/a
make && watch -pn 0.2 './philo_one 3 900 200 200 10 | grep "died" >> /tmp/a | echo >> /tmp/a ; cat /tmp/a | tail --lines 50'

# should be 1 line of "died" then 1 kline with dots, never more lines inbetween dots.
true > /tmp/a
make && watch -pn 0.2 './philo_one 3 900 200 200 | grep "died" >> /tmp/a | echo ...... >> /tmp/a ; cat /tmp/a | tail --lines 50'


./philo_one 0 500 200 200 1 ; echo ; ./philo_one 1 500 200 200 1 ; echo ;./philo_one 2 500 200 200 1; echo ;./philo_one 3 500 200 200 1


./philo_one 90 400 200 200 1>/tmp/a 2>/tmp/err ;\
        echo fork ; var=$_ ; cat /tmp/a | grep $var | wc -l ;\
        echo eating ; var=$_ ; cat /tmp/a | grep $var | wc -l ;\
        echo sleeping ; var=$_ ; cat /tmp/a | grep $var | wc -l ;\
        echo thinking ; var=$_ ; cat /tmp/a | grep $var | wc -l ;\
        echo died ; var=$_ ; cat /tmp/a | grep $var | wc -l
