# use cat ./fibonaci.as | ./bin/simple-asembler.out
# fibonaci
ld a, 1
ld c, 1
ld b, 32
loop:
  out (0), a
  ld d, a
  ld a, c
  add c, d
  sleep 0.25
djnz loop
