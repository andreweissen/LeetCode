#!/usr/bin/env bash

##
# A Bash-based answer to LeetCode question 192
#
# Apparently there are more efficient one-liner answers to this particular
# question that make use of <code>cat</code>, <code>grep</code>,
# <code>uniq</code>, and the other usual suspects, but the author is not
# presently adept or knowledgeable enough of these to employ them. Though this
# particular implementation makes use of <code>sort</code>, it is otherwise
# written in pure Bash and cobbled together from several StackOverflow threads.
#
# At the time of its submission, this implementation was found to be faster than
# 70% of all Bash implementations with a runtime of 4 ms and more efficient in
# terms of memory usage than 91% of Bash implementations with a memory usage of
# 3.2 MB.
#
# Author: Andrew Eissen <andrew@andreweissen.com>
##

declare -A words

while read -r -a line
do
  for word in "${line[@]}"
  do
    counter=words["$word"]
    words["$word"]=$((counter+1))
  done
done < words.txt

for word in "${!words[@]}"
do
  echo "$word ${words[$word]}"
done | sort -r -n -k 2
