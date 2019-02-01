int LGJCbord::recv(LGJCbord *this)
{
  signed int characters_received;
  signed int return_status;
  signed int data_start_index;
  signed int received_array_index;
  char checksum_calculator;
  char checksum_received;

  char* buffer = (char *) this + 68;
  memset(buffer, 0, 128);
  characters_received = _lgjSCI::recv(serial_port_object, buffer, 128);

  return_status = 1;
  if ( characters_received > 0 )
  {
    data_start_index = -1;
    received_array_index = 0;

    int timeout = 0;
    while ( buffer[received_array_index] != 0xC0 )
    {
      if ( ++received_array_index > 127 )
      {
        timeout = 1;
        break;
      }
    }

    if(timeout == 0)
      data_start_index = received_array_index;

    return_status = 3;

    if ( data_start_index < characters_received && data_start_index != -1 )
    {
      checksum_calculator = 0;
      for ( int i = data_start_index + 1; i < data_start_index + 21 ; ++i )
        checksum_calculator ^= buffer[i];

      checksum_received = buffer[21];

      return_status = 4;

      if ( checksum_received == checksum_calculator )
      {
        return_status = 0;
        *((_BYTE *)this + 46) = *(&buffer + data_start_index); // 0xC0
        *((_BYTE *)this + 47) = *(&buffer + data_start_index + 1); // 1
        *((_BYTE *)this + 48) = *(&buffer + data_start_index + 2); // 2
        *((_BYTE *)this + 49) = *(&buffer + data_start_index + 3); // 3
        *((_BYTE *)this + 50) = *(&buffer + data_start_index + 4); // 4
        *((_BYTE *)this + 51) = *(&buffer + data_start_index + 5); // 5
        *((_BYTE *)this + 52) = *(&buffer + data_start_index + 6); // 6
        *((_BYTE *)this + 53) = *(&buffer + data_start_index + 7); // 7
        *((_BYTE *)this + 54) = *(&buffer + data_start_index + 8); // 8
        *((_BYTE *)this + 55) = *(&buffer + data_start_index + 9); // 9
        *((_BYTE *)this + 56) = *(&buffer + data_start_index + 10); // 10
        *((_BYTE *)this + 57) = *(&buffer + data_start_index + 11); // 11
        *((_BYTE *)this + 58) = *(&buffer + data_start_index + 12); // 12
        *((_BYTE *)this + 59) = *(&buffer + data_start_index + 13); // 13
        *((_BYTE *)this + 60) = *(&buffer + data_start_index + 14); // 14
        *((_BYTE *)this + 61) = *(&buffer + data_start_index + 15); // 15
        *((_BYTE *)this + 62) = *(&buffer + data_start_index + 16); // 16
        *((_BYTE *)this + 63) = *(&buffer + data_start_index + 17); // 17
        *((_BYTE *)this + 64) = *(&buffer + data_start_index + 18); // 18
        *((_BYTE *)this + 65) = *(&buffer + data_start_index + 19); // 19
        *((_BYTE *)this + 66) = *(&buffer + data_start_index + 20); // 20
        *((_BYTE *)this + 67) = checksum_received; // Checksum
      }
    }
  }
  return return_status;
}
