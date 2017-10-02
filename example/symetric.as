ld b, 4
ld e, 32768
ld f, 65536


ping:
  ld c, b
  ld b, 14
  loop1:
    lrca f
    rrca e
    ld a, 0
    or a, e
    or a, f
    out (0), a
    sleep 0.1
  djnz loop1
  
  ld b, 14  
  loop2:
    rrca f
    lrca e
    ld a, 0
    or a, e
    or a, f
    out (0), a
    sleep 0.1
  djnz loop2
  ld b, c
  sleep 0.1
djnz ping
