#!/bin/bash
p=1
while [ "$p" -le "$#" ]; do
  eval "NAME=\${$p}"
  p=$((p + 1))
  eval "VALUE=\${$p}"
  p=$((p + 1))
  echo $NAME = $VALUE
done
