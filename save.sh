#!/bin/bash
for i in {1..5}; do
  for j in 1 2 4 8 16 32 64 128 256 512 1024; do
    ./a.out $j >> res
    echo $j >> res
  done
done
