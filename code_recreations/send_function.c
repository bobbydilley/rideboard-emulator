bool LGJCbord::send(LGJCbord *this)
{
  char checksum_calc; // dl@1
  signed int counter; // eax@1
  int bytes_sent; // eax@3
  // Seems to move things around? Maybe taking from 1 buffer to another to send so it can do a repeat send if something went wrong?
  *((_BYTE *)this + 39) = *((_BYTE *)this + 32);
  *((_BYTE *)this + 40) = *((_BYTE *)this + 33);
  *((_BYTE *)this + 41) = *((_BYTE *)this + 34);
  *((_BYTE *)this + 42) = *((_BYTE *)this + 35);
  *((_BYTE *)this + 43) = *((_BYTE *)this + 36);
  *((_BYTE *)this + 44) = *((_BYTE *)this + 37);

  checksum_calc = 0;
  counter = 1;
  do
    checksum_calc ^= *((_BYTE *)this + counter++ + 39);
  while ( counter <= 5 );

  *((_BYTE *)this + 38) = checksum_calc;
  *((_BYTE *)this + 45) = checksum_calc;  // Could be stored for later on, and maybe it is required in the response to confirm it read it right?

  bytes_sent = _lgjSCI::send(*((_lgjSCI **)this + 5), (char *)this + 39, 7u);   // Could be _lgjSCI::send(pointer_to_array, offset?, length);
  return bytes_sent == 7;
}
