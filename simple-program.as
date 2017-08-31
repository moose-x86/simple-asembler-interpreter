# use cat ./simple-program.as | ./bin/simple-asembler.out
ld a, 1
ld b, 32
loop:
  out (0), a
  ld a, b
  lrca
djnz loop

