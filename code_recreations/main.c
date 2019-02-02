int processMode; // 4
int baudRate; // 8
_lgjSCI globalSerialPointer; // 20
bool globalSerialOpenedSuccessfully; // 24
bool classReceiveBufferOkay; // 25
bool somethingAboutTestMode; // 26
int charactersSentStatus; // 196
int receiveStatus; // 200
byte classCommand; // 209 - Set to 0x13 for test mode
time SystemTime; // 400 - set at init.

void *__cdecl LGJCbord::init(LGJCbord *this)
{
  bool tempTestMode; // zf@1
  _lgjSCI *serialPointer; // eax@1
  LGJCbord *basicallyThis; // eax@5
  signed int counter; // edx@5
  int time; // eax@7
  signed int otherCounter; // eax@7
  void *result; // eax@9
  acpSystem *v9; // [esp+0h] [ebp-18h]@1
  _sSystem theTimeObject // [esp+0h] [ebp-18h]@3
  acpSystem *v11; // [esp+0h] [ebp-18h]@10

  serialPointer = (_lgjSCI *)operator new((tea::Platform *)0x10);
  _lgjSCI::_lgjSCI(serialPointer);

  tempTestMode = g_bTestMode == 0;

  globalSerialPointer = serialPointer;
  if ( !tempTestMode ) {
    *(this + 340) = 0;
  }

  if ( !acpSystem::getChuteType(v9) && !acpSystem::getServiceType(v11) ) {
    *(this + 340) = 0;
  } else {
    *(this + 340) = 211;
  }

LABEL_3:
  charactersSentStatus = 0;
  *(this + 208) = 0;
  classReceiveBufferOkay = 0;
  tempTestMode = g_bTestMode == 0;
  receiveStatus = 1;
  *(this + 204) = 0;
  somethingAboutTestMode = !tempTestMode;
  baudRate = 115200;
  *(this + 12) = 1;
  *(this + 16) = 0;
  if (_lgjSCI::open(serialPointer, 1)) {
    globalSerialOpenedSuccessfully = 1;
    _lgjSCI::changeParam(globalSerialPointer, baudRate);
  } else {
    globalSerialOpenedSuccessfully = 0;
  }

  *(this + 216) = 1;
  *(this + 217) = 1;
  *(this + 309) = 1;
  *(this + 233) = 0;
  *(this + 236) = 1065749138;
  *(this + 324) = 0;
  *(this + 328) = 0;
  *(this + 332) = 0;
  *(this + 336) = 0;
  *(this + 220) = 0;
  *(this + 240) = 0;
  *(this + 218) = 0;
  *(this + 224) = 3;
  *(this + 241) = 0;
  *(this + 244) = 0;
  *(this + 252) = 0;
  *(this + 228) = 0;
  *(this + 232) = 0;
  *(this + 256) = 0;
  *(this + 260) = 0;
  *(this + 268) = 0;
  *(this + 272) = 0;
  *(this + 276) = 0;
  *(this + 284) = 0;
  *(this + 288) = 0;
  *(this + 289) = 0;
  *(this + 292) = 0;
  *(this + 296) = 0;
  *(this + 300) = 0;
  *(this + 304) = 0;
  *(this + 308) = 0;
  *(this + 310) = 64;
  *(this + 311) = 0;
  basicallyThis = this;
  *(this + 312) = 0;
  counter = 1;
  *(this + 313) = 0;
  *(this + 320) = 1;
  *(this + 314) = 0;
  *(this + 315) = 0;
  *(this + 316) = 0;
  do
  {
    *(basicallyThis + 352) = 0;
    *(basicallyThis + 356) = 0;
    *(basicallyThis + 360) = 0;
    *(basicallyThis + 364) = 0;
    *(basicallyThis + 368) = 0;
    *(basicallyThis + 372) = 0;
    basicallyThis = (LGJCbord *)(basicallyThis + 24);
    --counter;
  }
  while ( counter >= 0 );
  time = _sSystem::getTime(theTimeObject);
  *(this + 32) = 0;
  *(this + 33) = 0;
  SystemTime = time;
  *(this + 34) = 0;
  *(this + 35) = 0;
  *(this + 36) = 0;
  *(this + 37) = 0;
  *(this + 38) = 0;
  otherCounter = 0;
  do
    *(this + otherCounter++ + 39) = 0;
  while ( otherCounter <= 6 );
  *(this + 46) = 0;
  *(this + 47) = 0;
  *(this + 48) = 0;
  *(this + 49) = 0;
  *(this + 50) = 0;
  *(this + 51) = 0;
  *(this + 52) = 0;
  *(this + 53) = 0;
  *(this + 54) = 0;
  *(this + 55) = 0;
  *(this + 56) = 0;
  *(this + 57) = 0;
  *(this + 58) = 0;
  *(this + 59) = 0;
  *(this + 60) = 0;
  *(this + 61) = 0;
  *(this + 62) = 0;
  *(this + 63) = 0;
  *(this + 64) = 0;
  *(this + 65) = 0;
  *(this + 66) = 0;
  *(this + 67) = 0;
  *(this + 240) = 0;
  result = memset(this + 68, 0, 128);
  *(this + 344) = -18;
  *(this + 348) = -1;
  *(this + 4) = 0;
  return result;
}

int __cdecl LGJCbord::exec(LGJCbord *this)
{
  bool didSerialOpen; // zf@1
  unsigned __int8 v2; // al@3
  int v3; // edx@3
  char v4; // dl@10
  unsigned __int8 v5; // dl@12
  int v6; // esi@13
  char v7; // dl@16
  int v8; // eax@22
  bool v9; // sf@22
  char v10; // cl@25
  char v11; // dl@26
  int result; // eax@42
  char v13; // al@45
  char v14; // dl@45
  int time; // eax@47
  int timeDifference; // edx@47
  float tempTimeDifference; // xmm0_4@48
  float v19; // ST18_4@49
  signed int v20; // esi@49
  char v21; // al@49
  char v22; // cl@64
  signed int v23; // ecx@67
  _sSystem *v24; // [esp+0h] [ebp-28h]@15
  _sSystem *v25; // [esp+0h] [ebp-28h]@47

  didSerialOpen = globalSerialOpenedSuccessfully == 0;
  *(this + 232) = *(this + 66);
  if ( didSerialOpen )
    receiveStatus = 0;
  else
    receiveStatus = LGJCbord::recv(this);

  v2 = *(this + 49);
  v3 = (this + 52) << 16) | (this + 51) << 8) | *(this + 50);
  *(this + 212) = v3;
  if ( v2 & 0xF && v2 <= 0xC )
    *(this + 240) = v2;
  if ( BYTE1(v3) & 0x10 )
    *(this + 216) = 0;
  if ( BYTE1(v3) & 0x20 )
    *(this + 217) = 0;
  v4 = *(this + 47);
  if (v4 - 2 <= 2)
  {
    ++*(this + 324);
    *(this + 328) = v4;
  }
  v5 = *(this + 53);
  if ( (v5 - 1) <= 9 )
  {
    v6 = *(this + 255);
    ++*(this + 332);
    *(this + 336) = v5;
    if ( !v6 )
      *(this + 340) = v5 + 200;
  }
  LGJCbord::check_seat_param(this);
  LGJCbord::set_param(this);
  v1 = classReceiveBufferOkay == 0;
  *(this + 32) = 0xC0;
  if ( v1 )
  {
    v7 = classCommand;
    *(this + 34) = 0;
    *(this + 33) = v7;
    if ( v7 == 19 )
    {
      v22 = *(this + 313);
      *(this + 35) = *(this + 289);
      *(this + 37) = v22;
    }
    else
    {
      *(this + 35) = 0;
      *(this + 37) = 0;
    }
    *(this + 36) = *(this + 308);
LABEL_19:
    *(this + 38) = 0;
    if ( !g_bSpecialCabinet )
      goto LABEL_28;
    goto LABEL_20;
  }
  v10 = classCommand;
  *(this + 33) = v10;
  if ( v10 != 19 && (unsigned __int8)(v10 - 12) > 2u )
  {
    v11 = *(this + 308);
    *(this + 34) = 0;
    *(this + 35) = 0;
    *(this + 36) = v11;
    if ( v10 != 19 )
      goto LABEL_27;
LABEL_46:
    *((_BYTE *)this + 37) = *((_BYTE *)this + 313);
    goto LABEL_19;
  }
  v13 = *((_BYTE *)this + 218);
  *((_BYTE *)this + 35) = *((_BYTE *)this + 289);
  v14 = *(this + 308);
  *(this + 34) = v13;
  *(this + 36) = v14;
  if ( v10 == 19 )
    goto LABEL_46;
LABEL_27:
  *((_BYTE *)this + 37) = 0;
  *((_BYTE *)this + 38) = 0;
  if ( !g_bSpecialCabinet )
    goto LABEL_28;
LABEL_20:
  if (charactersSentStatus) {
    *(this + 204) = 0;
LABEL_63:
    *((_BYTE *)this + 208) = 0;
    goto LABEL_28;
  }
  if ( receiveStatus == 0 )
  {
    *(this + 204) = 0;
    *(this + 208) = 1;
    goto LABEL_28;
  }
  v8 = *(this + 204) + 1;
  v9 = *(this + 204) - 179 < 0;
  *(this + 204) = v8;
  if ( !((v9 ^ __OFSUB__(v8, 180)) | (v8 == 180)) )
  {
    if ( !*(g_pCbord + 340) )
      *(g_pCbord + 340) = 209;
    goto LABEL_63;
  }
LABEL_28:
  if ( globalSerialOpenedSuccessfully && somethingAboutTestMode) {
    charactersSentStatus = LGJCbord::send(this);
  } else {
    charactersSentStatus = 0;
  }
  if ( charactersSentStatus )
  {
    time = _sSystem::getTime(v24);
    timeDifference = time - SystemTime;
    if ( time - SystemTime < 0 ) {
      v23 = timeDifference & 1 | ((unsigned int)(time - SystemTime) >> 1);
      tempTimeDifference = (float)v23 + (float)v23;
    } else {
      tempTimeDifference = (float) timeDifference;
    }
    v20 = (float)(tempTimeDifference * 0.001); // 0.1%
    SystemTime = _sSystem::getTime(v25);
    v21 = *(this + 35);
    if ( v21 & 0x10 ) // 00010000
      *(this + 364) += v20;
    if ( v21 & 0x20 ) // 00100000
      *(this + 388) += v20;
    if ( v21 & 1 ) // 00000001
      *((_DWORD *)this + 92) += v20;
    if ( v21 & 2 ) // 00000010
      *((_DWORD *)this + 98) += v20;
    if ( v21 & 4 ) // 00000100
      *((_DWORD *)this + 93) += v20;
    if ( v21 & 8 ) // 00001000
      *((_DWORD *)this + 99) += v20;
  }
  if ( _sInterfaceJvs::checkTrgOn(1, 0x2000000) )
    ++*(this + 352);
  if ( _sInterfaceJvs::checkTrgOn(2, 0x2000000) )
    ++*(this + 376);
  if ( _sInterfaceJvs::checkTrgOn(1, 0x800000) )
    ++*(this + 356);
  if ( _sInterfaceJvs::checkTrgOn(2, 0x800000) )
    ++*(this + 380);
  if ( _sInterfaceJvs::checkTrgOn(1, 0x400000) )
    ++*(this + 360);
  result = _sInterfaceJvs::checkTrgOn(2, 0x400000);
  if ( result )
    ++*(this + 384);
  return result;
}

char __cdecl LGJCbord::check_seat_param(LGJCbord *this)
{
  int v1; // eax@1
  bool v2; // zf@11
  signed int v3; // ecx@19
  unsigned __int8 v4; // cl@24
  char v5; // al@25
  int v6; // eax@27
  unsigned __int8 v7; // al@29
  unsigned __int8 v8; // cl@29
  signed int v9; // ecx@41
  char v10; // bl@48
  signed int v11; // ecx@49
  bool v12; // zf@57
  unsigned __int8 v13; // al@62
  unsigned __int8 v14; // cl@62
  char v15; // cl@69
  int v16; // ebx@76

  v1 = *(this + 244);
  switch ( v1 )
  {
    case 1:
      if ( *(this + 224) != 3 )
      {
        v4 = *(this + 49);
        if ( v4 > 0xCu || (v5 = 1, !(v4 & 1)) )
          v5 = 0;
        v1 = 3 - (v5 < 1);
        *(this + 224) = v1;
      }
      return v1;
    case 2:
      v1 = *(this + 224);
      if ( v1 != 1 )
      {
        if ( v1 > 1 )
        {
          if ( v1 != 2 )
            return v1;
          LOBYTE(v1) = *(this + 241) & 0xF0;
          if ( (_BYTE) v1 == 16 )
          {
            if ( *(this + 49) == 1 )
              goto LABEL_13;
          }
          else if ( (_BYTE)v1 == 32 )
          {
            if ( *(this + 49) == 3 )
              goto LABEL_13;
            goto LABEL_8;
          }
          if ( (_BYTE)v1 == 48 )
          {
            if ( *(this + 49) == 5 )
              goto LABEL_13;
LABEL_9:
            if ( (_BYTE)v1 != 80 )
            {
LABEL_10:
              if ( (_BYTE)v1 != 96 )
                return v1;
              v2 = *(this + 49) == 11;
              goto LABEL_12;
            }
            v2 = *(this + 49) == 9;
LABEL_12:
            if ( v2 )
              goto LABEL_13;
            return v1;
          }
LABEL_8:
          if ( (_BYTE)v1 == 64 )
          {
            if ( *(this + 49) == 7 )
              goto LABEL_13;
            goto LABEL_10;
          }
          goto LABEL_9;
        }
        if ( v1 )
          return v1;
        LOBYTE(v1) = *(this + 49);
        v10 = *(this + 241) & 0xF0;
        if ( (unsigned __int8)v1 > 0xCu || (v11 = 1, !(v1 & 1)) )
          v11 = 0;
        if ( !v11 )
          return v1;
        if ( v10 == 16 )
        {
          if ( (_BYTE)v1 == 1 )
            goto LABEL_13;
        }
        else if ( v10 == 32 )
        {
          if ( (_BYTE)v1 == 3 )
            goto LABEL_13;
          goto LABEL_54;
        }
        if ( v10 == 48 )
        {
          if ( (_BYTE)v1 == 5 )
            goto LABEL_13;
          goto LABEL_55;
        }
LABEL_54:
        if ( v10 == 64 )
        {
          if ( (_BYTE)v1 == 7 )
            goto LABEL_13;
          goto LABEL_56;
        }
LABEL_55:
        if ( v10 == 80 )
        {
          v12 = (_BYTE)v1 == 9;
          goto LABEL_58;
        }
LABEL_56:
        if ( v10 != 96 )
          goto LABEL_43;
        v12 = (_BYTE)v1 == 11;
LABEL_58:
        if ( v12 )
          goto LABEL_13;
        goto LABEL_43;
      }
      LOBYTE(v1) = *(this + 49);
      if ( (_BYTE)v1 == 13 )
        goto LABEL_33;
      v15 = *(this + 241) & 0xF0;
      if ( v15 == 16 )
      {
        if ( (_BYTE)v1 == 1 )
          goto LABEL_13;
      }
      else if ( v15 == 32 )
      {
        if ( (_BYTE)v1 == 3 )
          goto LABEL_13;
        goto LABEL_72;
      }
      if ( v15 == 48 )
      {
        if ( (_BYTE)v1 == 5 )
          goto LABEL_13;
        goto LABEL_73;
      }
LABEL_72:
      if ( v15 == 64 )
      {
        if ( (_BYTE)v1 == 7 )
          goto LABEL_13;
        goto LABEL_74;
      }
LABEL_73:
      if ( v15 == 80 )
      {
        v2 = (_BYTE)v1 == 9;
        goto LABEL_12;
      }
LABEL_74:
      if ( v15 != 96 )
        return v1;
      v2 = (_BYTE)v1 == 11;
      goto LABEL_12;
    case 3:
      v6 = *(this + 224);
      if ( !v6 )
        goto LABEL_40;
      v1 = v6 - 1;
      if ( !v1 )
      {
        v7 = *(this + 49);
        v8 = v7;
        if ( !(v7 & 0xF) || v7 > 0xCu || (v1 = 1, v8 & 1) )
          v1 = 0;
        if ( v1 )
          goto LABEL_33;
      }
      return v1;
    case 4:
      v1 = *((_DWORD *)this + 56);
      if ( v1 == 1 )
      {
        v13 = *(this + 224);
        v14 = v13;
        if ( !(v13 & 0xF) || v13 > 0xCu || (v1 = 1, v14 & 1) )
          v1 = 0;
        if ( !v1 )
          return v1;
        *(this + 224) = 2;
LABEL_38:
        *(this + 228) = 30;
        return v1;
      }
      if ( v1 <= 1 )
        goto LABEL_39;
      if ( v1 == 2 )
      {
        if ( *(this + 232) != *(this + 66) )
          goto LABEL_38;
        v16 = *(this + 228) - 1;
        v2 = *(this + 228) == 1;
        *(this + 228) = v16;
        if ( v16 < 0 || v2 )
LABEL_13:
          *(this + 224) = 3;
      }
      return v1;
    case 5:
      v1 = *(this + 224);
      if ( v1 == 1 )
      {
LABEL_33:
        *(this + 224) = 2;
        return v1;
      }
      if ( v1 <= 1 )
      {
LABEL_39:
        if ( !v1 )
        {
LABEL_40:
          LOBYTE(v1) = *(this + 49);
          if ( (unsigned __int8)v1 > 0xCu || (v9 = 1, !(v1 & 1)) )
            v9 = 0;
          if ( v9 )
LABEL_43:
            *(this + 224) = 1;
        }
      }
      else if ( v1 == 2 )
      {
        LOBYTE(v1) = *(this + 49);
        if ( (unsigned __int8)v1 > 0xCu || (v3 = 1, !(v1 & 1)) )
          v3 = 0;
        if ( v3 )
          goto LABEL_13;
      }
      return v1;
    default:
      return v1;
  }
}

void __cdecl LGJCbord::set_seat_param(LGJCbord *this)
{
  char v1; // di@1
  int v2; // edx@1
  unsigned int v3; // esi@3
  unsigned int v4; // ecx@11
  bool v5; // zf@13
  int v6; // eax@17
  int v7; // edx@23
  bool v8; // zf@32
  char v9; // al@34
  char v10; // al@39
  char v11; // dl@45
  char v12; // al@48
  char v13; // al@53
  int v14; // eax@61
  int v15; // esi@66
  int v16; // edx@69
  int v17; // eax@73
  char v18; // al@93

  v1 = 0;
  v2 = *((_DWORD *)this + 69);
  if ( !v2 )
  {
    v3 = *((_DWORD *)this + 65);
    goto LABEL_10;
  }
  if ( v2 != 1 )
  {
    v3 = *((_DWORD *)this + 65);
    if ( !v3 )
    {
      if ( *((_DWORD *)this + 56) != 3 )
      {
        if ( *((_BYTE *)this + 288) && *((_BYTE *)this + 241) != *((_BYTE *)this + 272) )
        {
          *((_BYTE *)this + 256) = 0;
          *((_DWORD *)this + 65) = 1;
          *((_DWORD *)this + 67) = 0;
          *((_BYTE *)this + 288) = 0;
          v3 = 1;
        }
        goto LABEL_8;
      }
      v17 = *((_DWORD *)this + 71);
      v3 = *((_DWORD *)this + 69);
      *((_BYTE *)this + 256) = *((_BYTE *)this + 272);
      *((_DWORD *)this + 65) = v2;
      *((_DWORD *)this + 67) = v17;
      *((_BYTE *)this + 288) = 1;
      goto LABEL_10;
    }
    goto LABEL_20;
  }
  v3 = *((_DWORD *)this + 65);
  if ( v3 )
  {
    if ( *((_BYTE *)this + 288) )
    {
LABEL_20:
      v1 = 1;
      goto LABEL_10;
    }
    *((_DWORD *)this + 69) = 0;
  }
  else
  {
    if ( !*((_BYTE *)this + 288) )
    {
      *((_DWORD *)this + 69) = 0;
      goto LABEL_8;
    }
    v7 = *((_DWORD *)this + 71);
    if ( !v7 || *((_DWORD *)this + 63) == v7 )
    {
      v18 = *((_BYTE *)this + 272);
      v3 = 1;
      *((_DWORD *)this + 65) = 1;
      *((_BYTE *)this + 256) = v18;
      *((_DWORD *)this + 67) = v7;
    }
    *((_BYTE *)this + 288) = 0;
  }
LABEL_10:
  if ( v3 > 5 )
  {
LABEL_11:
    v4 = *((_DWORD *)this + 61);
    goto LABEL_12;
  }
LABEL_8:
  switch ( v3 )
  {
    case 0u:
      goto LABEL_11;
    case 1u:
      v4 = *((_DWORD *)this + 61);
      if ( v4 == 2 && *((_DWORD *)this + 56) != 3 )
        goto LABEL_86;
      v16 = *((_DWORD *)this + 67);
      if ( !v16 || *((_DWORD *)this + 63) == v16 )
      {
        *((_DWORD *)this + 63) = v16;
        *((_BYTE *)this + 241) = *((_BYTE *)this + 256);
        *((_DWORD *)this + 61) = v3;
        v4 = v3;
        *((_DWORD *)this + 56) = 1;
        if ( v1 )
          *((_BYTE *)this + 288) = 0;
      }
      goto LABEL_72;
    case 2u:
      v14 = *((_DWORD *)this + 61);
      if ( v14 == 5 )
        goto LABEL_75;
      v8 = v14 == 1;
      goto LABEL_63;
    case 3u:
      v4 = *((_DWORD *)this + 61);
      if ( v4 == 2 && *((_DWORD *)this + 56) != 3 )
        goto LABEL_72;
      v11 = *((_BYTE *)this + 256);
      if ( (unsigned __int8)(v11 - 119) <= 2u )
      {
        v12 = *((_BYTE *)this + 49);
        if ( v12 != 3 && v12 != 4 && v12 != 9 && v12 != 10 )
        {
          if ( v12 != 13 )
            goto LABEL_72;
          v13 = *((_BYTE *)this + 240);
          if ( v13 != 3 && v13 != 4 && v13 != 9 && v13 != 10 )
            goto LABEL_72;
        }
      }
      if ( v4 != 5 && (v4 != 1 || *((_DWORD *)this + 56) == 3) )
        goto LABEL_59;
      *((_DWORD *)this + 56) = 0;
      goto LABEL_60;
    case 4u:
      v4 = *((_DWORD *)this + 61);
      if ( v4 == 2 && *((_DWORD *)this + 56) != 3
        || (v9 = *((_BYTE *)this + 49), v9 != 3)
        && v9 != 4
        && v9 != 9
        && v9 != 10
        && (v9 != 13 || (v10 = *((_BYTE *)this + 240), v10 != 3) && v10 != 4 && v10 != 9 && v10 != 10) )
      {
LABEL_72:
        *((_DWORD *)this + 65) = 0;
        break;
      }
      if ( v4 != 5 && (v4 != 1 || *((_DWORD *)this + 56) == 3) )
      {
        v11 = *((_BYTE *)this + 256);
LABEL_59:
        *(this + 224) = *((_BYTE *)this + 241) != v11;
      }
      else
      {
        v11 = *((_BYTE *)this + 256);
        *((_DWORD *)this + 56) = 0;
      }
LABEL_60:
      *((_BYTE *)this + 241) = v11;
      goto LABEL_66;
    case 5u:
      v4 = *((_DWORD *)this + 61);
      if ( v4 == 2 && *((_DWORD *)this + 56) != 3 )
      {
LABEL_86:
        *((_DWORD *)this + 65) = 0;
      }
      else
      {
        if ( v4 == 3 || v4 == 5 || v4 == 4 )
          goto LABEL_75;
        v8 = v4 == 1;
LABEL_63:
        if ( !v8 )
          goto LABEL_96;
        if ( *((_DWORD *)this + 56) != 3 )
LABEL_75:
          *((_DWORD *)this + 56) = 0;
        else
LABEL_96:
          *((_DWORD *)this + 56) = 1;
        *((_BYTE *)this + 241) = *((_BYTE *)this + 256);
LABEL_66:
        v4 = v3;
        *((_DWORD *)this + 61) = v3;
        v15 = *((_DWORD *)this + 67);
        *((_DWORD *)this + 65) = 0;
        *((_DWORD *)this + 63) = v15;
        if ( v1 )
          *((_BYTE *)this + 288) = 0;
      }
      break;
  }
LABEL_12:
  switch ( v4 )
  {
    case 1u:
      v5 = *((_DWORD *)this + 56) == 3;
      goto LABEL_14;
    case 2u:
    case 3u:
    case 4u:
      v6 = *((_DWORD *)this + 56);
      if ( !v6 )
        goto LABEL_18;
      goto LABEL_28;
    case 5u:
      v6 = *((_DWORD *)this + 56);
      if ( v6 )
      {
        if ( v6 == 1 )
        {
          *((_BYTE *)this + 218) = -128;
        }
        else
        {
LABEL_28:
          v5 = v6 == 3;
LABEL_14:
          if ( !v5 )
            *((_BYTE *)this + 218) = *((_BYTE *)this + 241);
        }
      }
      else
      {
LABEL_18:
        *((_BYTE *)this + 218) = 0;
      }
      break;
    default:
      return;
  }
}

int __cdecl LGJCbord::setSeatParam(LGJCbord *this, unsigned __int8 a2)
{
  signed int v2; // eax@1
  unsigned __int8 v3; // al@4
  unsigned __int8 v4; // dl@5
  int v5; // ecx@5
  int v6; // eax@9
  int result; // eax@9

  v2 = *(this + 344);
  if ( v2 != 13 )
  {
    if ( v2 > 13 )
    {
      if ( v2 == 14 )
      {
        v3 = 0;
        goto LABEL_5;
      }
    }
    else if ( v2 == 12 )
    {
      v3 = a2;
      goto LABEL_5;
    }
    goto LABEL_4;
  }
  if ( !a2 || a2 > 0x6Fu || (v3 = a2 - 48, a2 <= 0x3Fu) )
LABEL_4:
    v3 = a2;
LABEL_5:
  v4 = v3;
  v5 = 1;
  if ( v3 )
  {
    LOBYTE(v5) = 2;
    if ( v3 > 0x6Fu )
    {
      LOBYTE(v5) = 3;
      if ( (v3 - 112) > 0xFu )
        v5 = 5 - ((v3 + 112) < 0x30u);
    }
  }
  v6 = (unsigned __int16)(this + 110) + 1);
  *(this + 220) = v6;
  result = v6 + 1;
  switch ( v5 )
  {
    case 1:
      if ( *(this + 260) != 2 )
      {
        *(this + 256) = v4;
        *(this + 260) = v5;
        *(this + 268) = 0;
      }
      break;
    case 2:
      goto LABEL_20;
    case 3:
    case 4:
    case 5:
      if ( *(this + 260) != 2 )
      {
LABEL_20:
        *(this + 256) = v4;
        *(this + 260) = v5;
        *(this + 268) = result;
      }
      break;
    default:
      return result;
  }
  return result;
}

int __cdecl LGJCbord::setSeatParamStop(LGJCbord *this, int a2)
{
  int result; // eax@2
  if ( *(this + 260) != 2 )
  {
    *(this + 256) = 0;
    *(this + 260) = 1;
    result = a2;
    *(this + 268) = a2;
  }
  return result;
}
