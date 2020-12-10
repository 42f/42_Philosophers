print_victim_last_meal (){
 time_to_die=$1
 nb_of_victim=$(cat /tmp/a | grep "died" | wc -l)
 victim=$(cat /tmp/a | grep "died" | sed 's/ /\n/g'| tail --lines=2 | head --lines=1)
 echo "Last meal was :"
 cat /tmp/a | grep " $victim is eating" | tail --line=1
 time_of_meal=$(cat /tmp/a | grep " $victim is eating" | tail --line=1 | sed 's/ /\n/g' | head --lines=1)
 time_of_death=$(cat /tmp/a | grep "died" | tail --line=1 | sed 's/ /\n/g' | head --lines=1)
 if [ $(($time_of_meal)) -eq "0" ]; then
        echo "Death reported afer $(( $time_of_death - $time_to_die)) ms."
        echo "Nb of died philosopher: [$nb_of_victim]"
 else
        echo "Death reported afer $(( $time_of_death - $time_of_meal - $time_to_die)) ms."
        echo "Nb of died philosopher: [$nb_of_victim]"
 fi
 if [ $(( $time_of_death - $time_of_meal - $time_to_die)) -gt "10" ]; then
        echo "[ nop !]"
        exit 42
 elif [ $(( $time_of_death - $time_of_meal - $time_to_die)) -lt "0" ]; then
        echo "[ nop !]"
        exit 42
 else
        echo "[OK]"
 fi
 if [ $(( $nb_of_victim )) -ne "1" ]; then
        echo "[ nop !] more than one died"
        exit 42
 fi
}

main (){
 ./philo_one $1 $2 $3 $4 > /tmp/a 2>/tmp/err ;
 var="fork" ; echo -n $var"      = " ;  cat /tmp/a | grep $var | wc -l ;
 var="eating" ; echo -n $var"    = " ;  cat /tmp/a | grep $var | wc -l ;
 var="sleeping" ; echo -n $var"  = " ;  cat /tmp/a | grep $var | wc -l ;
 var="thinking" ; echo -n $var"  = " ;  cat /tmp/a | grep $var | wc -l ;
 var="died" ; echo -n $var"      = " ;  cat /tmp/a | grep $var | wc -l ;
 echo "\nDeath report:"
 var="died" ; cat /tmp/a | grep $var;
 print_victim_last_meal $2
}

echo "Parameters are: 1 $2 $3 $4"
true > /tmp/a
main $1 $2 $3 $4
