#! /bin/bash

print_victim_last_meal (){
 first_eater=0
 first_eat_time=0
 first_sleep=0
 first_think=0
 time_of_meal=0
 time_to_die=$2
 nb_of_victim=$(cat /tmp/log | grep "died" | wc -l)
 if [[ "$OSTYPE" == "darwin"* ]]; then
       victim=$(cat /tmp/log | grep "died" | sed -e $'s/ /\\\n/g' | tail -n2 | head -n1)
 else
       victim=$(cat /tmp/log | grep "died" | sed 's/ /\n/g' | tail -n2 | head -n1)
 fi
 if [[ "$OSTYPE" == "darwin"* ]]; then
       first_eater=$(cat /tmp/log | grep "eating" | head -n1 | sed -e $'s/ /\\\n/g' | head -n2 | tail -n1)
       first_eat_time=$(cat /tmp/log | grep "eating" | sed -e $'s/ /\\\n/g' | head -n1)
       first_sleep=$(cat /tmp/log | grep " $first_eater " | grep "sleeping" | head -n1 | sed -e $'s/ /\\\n/g' | head -n1)
       first_think=$(cat /tmp/log | grep " $first_eater " | grep "thinking" | head -n1 | sed -e $'s/ /\\\n/g' | head -n1)
 else
       first_eater=$(cat /tmp/log | grep "eating" | head -n1 | sed 's/ /\n/g' | head -n2 | tail -n1)
       first_eat_time=$(cat /tmp/log | grep "eating" |  sed 's/ /\n/g' | head -n1)
       first_sleep=$(cat /tmp/log | grep " $first_eater " | grep "sleeping" | head -n1 | sed 's/ /\n/g' | head -n1)
       first_think=$(cat /tmp/log | grep " $first_eater " | grep "thinking" | head -n1 | sed 's/ /\n/g' | head -n1)
 fi

 echo "Last meal was :"
 last_meal=$(cat /tmp/log | grep " $victim is eating" | tail -n1 | wc -l)
 if [ $(($last_meal)) -eq "0" ]; then
        echo "[$victim have not eaten]"
 else
      cat /tmp/log | grep " $victim is eating" | tail -n1
 fi
 if [[ "$OSTYPE" == "darwin"* ]]; then
       time_of_meal=$(cat /tmp/log | grep " $victim is eating" | tail -n1 | sed -e $'s/ /\\\n/g' | head -n1)
 else
       time_of_meal=$(cat /tmp/log | grep " $victim is eating" | tail -n1 | sed 's/ /\n/g' | head -n1)
 fi

 echo "Timestamp of the last meal = $time_of_meal"

 if [[ "$OSTYPE" == "darwin"* ]]; then
       time_of_death=$(cat /tmp/log | grep "died" | tail -n1 | sed -e $'s/ /\\\n/g' | head -n1)
 else
       time_of_death=$(cat /tmp/log | grep "died" | tail -n1 | sed 's/ /\n/g' | head -n1)
 fi

 echo "Timestamp of the death     = $time_of_death"
 echo "Time to die parameter      = $time_to_die"

       echo "-----------------------------------------"
       echo "Timestamp: $first_eater is eating   @ $first_eat_time"
       echo "Timestamp: $first_eater is sleeping @ $first_sleep"
       echo "Timestamp: $first_eater is thinking @ $first_think"

       if [ $(( $first_sleep )) -gt "0" ]; then
              t_delta=$(( $first_sleep - $first_eat_time ))
              if [ $(( $t_delta )) -lt $(( $3 )) ]; then
                     echo "         ❌ [ nop !] $first_eater is eating too early !"
              fi
       fi

       if [ $(( $first_think )) -gt "0" ]; then
              t_delta=$(( $first_think - $first_sleep ))
              if [ $(( $t_delta )) -lt $(( $4 )) ]; then
                     echo "         ❌ [ nop !] $first_eater is sleeping too early !"
              fi
       fi
       echo
       echo "-----------------------------------------"

       if [ $(($time_of_meal)) -eq "0" ]; then
              echo "Death reported afer $(( $time_of_death - $time_to_die )) ms."
              t_delta=$(( $time_of_death - $time_to_die ))
       else
              echo "Death reported afer $(( $time_of_death - $time_of_meal - $time_to_die )) ms."
              t_delta=$(( $time_of_death - $time_of_meal - $time_to_die ))
       fi



       if [ $(( $t_delta )) -gt "10" ]; then
              echo "❌ [ nop !] timeframe for death declaration too long: $(( $t_delta ))"
              echo "=============== LOG =========================================="
              cat /tmp/log | tail -n20
              echo "=============== ERR LOG ======================================"
              cat /tmp/err
              exit 42
       elif [ $(( $t_delta )) -lt "0" ]; then
              echo " ❌ [ nop !] timeframe for death declaration illogic: $(( $t_delta ))"
              echo "=============== LOG =========================================="
              cat /tmp/log | tail -n20
              echo "=============== ERR LOG ======================================"
              cat /tmp/err
              exit 42
       else
              echo "✅ [OK]"
       fi

       if [ $(( $nb_of_victim )) -ne "1" ]; then
              echo " ❌ [ nop !] more than one died"
              echo "=============== LOG =========================================="
              cat /tmp/log | tail -n20
              echo "=============== ERR LOG ======================================"
              cat /tmp/err
              exit 42
       fi
}

main (){
 ./philo_* $1 $2 $3 $4 &>/tmp/log
#   2>/tmp/err ;
 var="fork" ; echo -n $var"      = " ;  cat /tmp/log | grep $var | wc -l ;
 var="eating" ; echo -n $var"    = " ;  cat /tmp/log | grep $var | wc -l ;
 var="sleeping" ; echo -n $var"  = " ;  cat /tmp/log | grep $var | wc -l ;
 var="thinking" ; echo -n $var"  = " ;  cat /tmp/log | grep $var | wc -l ;
 var="died" ; echo -n $var"      = " ;  cat /tmp/log | grep $var | wc -l ;
 echo
 echo "Death report:"
 var="died" ; cat /tmp/log | grep $var;
 print_victim_last_meal $1 $2 $3 $4
}
echo $(date)
echo "Parameters are: $1 $2 $3 $4"
true > /tmp/log
true > /tmp/err
main $1 $2 $3 $4
