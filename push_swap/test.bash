#!/bin/bash

i=0
test_numbers_count=500
passed=0
tests=100
while [ $i -lt $tests ]; do
  i=$(($i + 1))
  args=`shuf --head-count=$test_numbers_count --input-range=1-999 | tr "\n" " "`
  ops=$(./push_swap $args)
  number_of_ops=$(printf "$ops" | wc -l)
  sorted=$(printf "$ops" | ./checker $args )
  if [[ "$sorted" == "OK" ]] && [[ "$number_of_ops" -lt 7500 ]]; then
    printf "."
    passed=$(($passed + 1))
  else
    printf "#"
  fi
done
printf "\n%s\n" $passed/$tests
