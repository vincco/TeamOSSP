#!/usr/bin/env bash
# Automated validation: naive MUST deadlock, every other strategy MUST NOT.
BIN=./dining
pass=0; fail=0
check() { # name expected_exit actual_exit
  if [ "$2" -eq "$3" ]; then echo "PASS  $1"; pass=$((pass+1)); else echo "FAIL  $1 (expected exit $2, got $3)"; fail=$((fail+1)); fi
}

$BIN -q -s naive -n 5 -d 15 >/dev/null;           check "naive, 5 philosophers deadlocks"            2 $?
for s in hierarchy waiter monitor asymmetric; do
  $BIN -q -s $s -n 5 -d 10 >/dev/null;            check "$s, 5 philosophers, no deadlock"            0 $?
  $BIN -q -s $s -n 20 -d 10 -e 50 -t 100 >/dev/null; check "$s, 20 philosophers stress, no deadlock" 0 $?
  $BIN -q -s $s -n 2 -d 5 >/dev/null;             check "$s, 2 philosophers edge case"               0 $?
done

echo; echo "Passed: $pass  Failed: $fail"
[ $fail -eq 0 ]
