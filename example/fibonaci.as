# use cat ./fibonaci.as | ./bin/simple-asembler.out
# fibonaci
ld a, 2863311530
ld b, 10
loop:
  out (0), a
  xor a, a
  sleep 0.2
djnz loop
