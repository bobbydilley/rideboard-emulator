bool LGJCbord::send(LGJCbord *this)
{
  char checksum_calc;
  signed int counter;
  int bytes_sent;
  char* other_checksum_variable = *((_BYTE *)this + 38);
  char* buffer = (_BYTE *)this + 39;
  // Seems to move things around? Maybe taking from 1 buffer to another to send so it can do a repeat send if something went wrong?
  buffer[0] = *((_BYTE *)this + 32);  // This must contain 0xC0
  buffer[1] = *((_BYTE *)this + 33);
  buffer[2]  = *((_BYTE *)this + 34);
  buffer[3] = *((_BYTE *)this + 35);
  buffer[4]  = *((_BYTE *)this + 36);
  buffer[5]  = *((_BYTE *)this + 37);

  checksum_calc = 0;
  counter = 1;
  do
    checksum_calc ^= buffer[counter++];
  while ( counter <= 5 );

  other_checksum_variable = checksum_calc;
  buffer[6] = checksum_calc;  // Could be stored for later on, and maybe it is required in the response to confirm it read it right?

  bytes_sent = _lgjSCI::send(serial_port_object, buffer, 7);
  return bytes_sent == 7;
}
