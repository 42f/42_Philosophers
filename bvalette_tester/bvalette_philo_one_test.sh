#! /bin/bash

print_victim_last_meal (){
 time_of_meal=0
 time_to_die=$1
 nb_of_victim=$(cat /tmp/a | grep "died" | wc -l)
 if [[ "$OSTYPE" == "darwin"* ]]; then
       victim=$(cat /tmp/a | grep "died" | sed -e $'s/ /\\\n/g' | tail -n2 | head -n1)
 else
       victim=$(cat /tmp/a | grep "died" | sed 's/ /\n/g' | tail -n2 | head -n1)
 fi

 echo "Last meal was :"
 last_meal=$(cat /tmp/a | grep " $victim is eating" | tail -n1 | wc -l)
 if [ $(($last_meal)) -eq "0" ]; then
        echo "[$victim have not eaten]"
 else
      cat /tmp/a | grep " $victim is eating" | tail -n1
 fi
 if [[ "$OSTYPE" == "darwin"* ]]; then
       time_of_meal=$(cat /tmp/a | grep " $victim is eating" | tail -n1 | sed -e $'s/ /\\\n/g' | head -n1)
 else
       time_of_meal=$(cat /tmp/a | grep " $victim is eating" | tail -n1 | sed 's/ /\n/g' | head -n1)
 fi

 echo "Timestamp of the last meal = $time_of_meal"

 if [[ "$OSTYPE" == "darwin"* ]]; then
       time_of_death=$(cat /tmp/a | grep "died" | tail -n1 | sed -e $'s/ /\\\n/g' | head -n1)
 else
       time_of_death=$(cat /tmp/a | grep "died" | tail -n1 | sed 's/ /\n/g' | head -n1)
 fi

 echo "Timestamp of the death     = $time_of_death"
 echo "Time to die parameter      = $time_to_die"

 if [ $(($time_of_meal)) -eq "0" ]; then
        echo "Death reported afer $(( $time_of_death - $time_to_die )) ms."
        t_delta=$(( $time_of_death - $time_to_die ))
        echo "Nb of dead philosopher: [$nb_of_victim]"
 else
        echo "Death reported afer $(( $time_of_death - $time_of_meal - $time_to_die )) ms."
        t_delta=$(( $time_of_death - $time_of_meal - $time_to_die ))
        echo "Nb of dead philosopher: [$nb_of_victim]"
 fi

 if [ $(( $t_delta )) -gt "10" ]; then
        echo "❌ [ nop !] timeframe for death declaration too long: $(( $t_delta ))"
        cat /tmp/a | tail -n20
        cat /tmp/err
        exit 42
 elif [ $(( $t_delta )) -lt "0" ]; then
        echo " ❌ [ nop !] timeframe for death declaration illogic: $(( $t_delta ))"
        cat /tmp/a | tail -n20
        cat /tmp/err
        exit 42
 else
        echo "✅ [OK]"
 fi

 if [ $(( $nb_of_victim )) -ne "1" ]; then
        echo " ❌ [ nop !] more than one died"
        cat /tmp/a | tail -n20
        cat /tmp/err
        exit 42
 fi
 err_log=$(cat /tmp/err | wc -l)
#  if [ $(( err_log )) -ne "0" ]; then
#         echo "[ nop !] stderr used:"
#         cat /tmp/a | tail -n20
#         echo "erro log:"
#         cat /tmp/err
#         exit 42
#  fi
}

main (){
 ./philo_one $1 $2 $3 $4 &>/tmp/a
#   2>/tmp/err ;
 var="fork" ; echo -n $var"      = " ;  cat /tmp/a | grep $var | wc -l ;
 var="eating" ; echo -n $var"    = " ;  cat /tmp/a | grep $var | wc -l ;
 var="sleeping" ; echo -n $var"  = " ;  cat /tmp/a | grep $var | wc -l ;
 var="thinking" ; echo -n $var"  = " ;  cat /tmp/a | grep $var | wc -l ;
 var="died" ; echo -n $var"      = " ;  cat /tmp/a | grep $var | wc -l ;
 echo
 echo "Death report:"
 var="died" ; cat /tmp/a | grep $var;
 print_victim_last_meal $2
}
echo $(date)
echo "Parameters are: $1 $2 $3 $4"
true > /tmp/a
main $1 $2 $3 $4
