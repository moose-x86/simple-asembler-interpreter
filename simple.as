# use cat ./simple.as | ./bin/simple-asembler.out
ld a, 15
ld b, 1
ping:
  ld c, b
  ld b, 27
  loop1:
    out (0), a
    sleep 70000
    lrca
  djnz loop1
  ld b, 27
  loop2:
    out (0), a
    sleep 70000
    rrca
  djnz loop2
  ld b, c
djnz ping
