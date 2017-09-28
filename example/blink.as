ld c, 4294967295
ld a, 4278190335
ld b, 16
loop:
  out (0), a
  xor a, c
  sleep 0.5
djnz loop
