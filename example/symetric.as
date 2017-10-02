# use cat ./simple.as | ./bin/simple-asembler.out
ld b, 4
ld e, 32768
ld f, 65536

ping:
  ld c, b
  ld b, 15
  loop1:
    ld a, 0
    or a, e
    or a, f
    out (0), a
    lrca f
    rrca e
    sleep 0.1
  djnz loop1
  
  ld b, 15  
  loop2:
    ld a, 0
    or a, e
    or a, f
    out (0), a
    rrca f
    lrca e
    sleep 0.1
  djnz loop2
  ld b, c
  sleep 1
djnz ping
