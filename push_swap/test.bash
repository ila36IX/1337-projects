#!/bin/bash

i=0
number_of_args=100
passed=0
tests=1000
while [ $i -lt $tests ]; do
  i=$(($i + 1))
  args=`shuf --head-count=$number_of_args --input-range=1-999 | tr "\n" " "`
  ops=$(./push_swap $args)
  number_of_ops=$(echo "$ops" | wc -l)
  sorted=$(echo "$ops" | ./checker_linux $args)
  if [[ "$sorted" == "OK" ]] && [[ "$number_of_ops" -lt 700 ]]; then
    printf "."
    passed=$(($passed + 1))
  else
    printf "#"
  fi
done
printf "\n%s\n" $passed/$tests
