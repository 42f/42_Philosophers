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
 cat /tmp/a | grep " $victim is eating" | tail -n1
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
        echo "Nb of died philosopher: [$nb_of_victim]"
 else
        echo "Death reported afer $(( $time_of_death - $time_of_meal - $time_to_die )) ms."
        t_delta=$(( $time_of_death - $time_of_meal - $time_to_die ))
        echo "Nb of died philosopher: [$nb_of_victim]"
 fi

}

main (){
 ./philo_one $1 $2 $3 $4 $5 &>/tmp/a
#   2>/tmp/err ;
 var="fork" ; echo -n $var"      = " ;  cat /tmp/a | grep $var | wc -l ;
 var="eating" ; echo -n $var"    = " ;  cat /tmp/a | grep $var | wc -l ;
 var="sleeping" ; echo -n $var"  = " ;  cat /tmp/a | grep $var | wc -l ;
 var="thinking" ; echo -n $var"  = " ;  cat /tmp/a | grep $var | wc -l ;
 var="died" ; echo -n $var"      = " ;  cat /tmp/a | grep $var | wc -l ;
 echo
 echo "Death report:"
 var="died" ; cat /tmp/a | grep $var
 nb_of_victim=$(var="died" ; cat /tmp/a | grep $var | wc -l)
 nb_of_meals=$(cat /tmp/a | grep "eating" | wc -l)
if [ $(( $nb_of_victim )) -ne "0" ]; then
       print_victim_last_meal $2
       echo
       echo "❌ 💀 [ nop !] No one should die"
       echo "=============== LOG =========================================="
       cat /tmp/a
       exit 42
elif [ $(( $nb_of_meals / $1 )) -ne $5 ]; then
       print_victim_last_meal $2
       echo
       echo "❌ 💀 [ nop !] There should be 7 meals per philo"
       echo "=============== LOG =========================================="
       cat /tmp/a
       exit 42
else
       echo "✅  Good, no one died"
 fi

}
echo $(date)
echo "Parameters are: 5 800 200 200 7"
true > /tmp/a
main 5 800 200 200 7
