LGJCbord globalBoard; //80
byte lastByte; lgcbord + 66;

byte usrCbordLoop::exec(usrCbordLoop *this) {
  if ( g_iSystemErrorStop) {
    globalBoard = 13;
    if ( pAdvLoop )
      *(pAdvLoop + 164) = 0;
    processMode = 0;
    g_iSystemErrorStop = 2;
  } else if ( g_iSystemShutdown && lgjBankManager::stopLoad(g_pBankManager) ){
    g_iSystemShutdown = 3;
    globalBoard = 15;
  }

  v1 = (LGJCbord *)globalBoard;
  switch ( globalBoard ) {
    case 0:
      if ( acpBackup::isExistSeatiniFile(g_pBackup)) {
        classReceiveBufferOkay = 1;
        acpBackup::TouchSeatiniFile(g_pBackup);
        somethingAboutTestMode = 1;
        if ( !acpBackup::isExistTesthaltFile(g_pBackup) ) {

          *(g_pCbord + 233) = lastByte;
          if (lastByte != 0)
            *(g_pCbord + 236) = lastByte * 0.020807063;
          else
            *(g_pCbord + 236) = 1065749138;
          goto LABEL_35;
        }
        *(g_pCbord + 209) = 16;
        acpShader::setFrameClear(g_pShader, 1);
        LOBYTE(v1) = mtrLoopManager::setMode(pLoopManager, "cbord");
        v111 = pCbordLoop;
        if ( pCbordLoop )
        {
          LOBYTE(v1) = (_BYTE)g_pCbord;
          *(g_pCbord + 4) = 2;
          *(_DWORD *)(v111 + 84) = 6;
        }
      }
      else
      {
        v53 = g_pCbord;
        *(g_pCbord + 209) = 1;
        *(g_pCbord + 26) = 1;
        globalBoard = 1;
        LOBYTE(v1) = acpShader::setFlipDrawMode(g_pShader, 1);
      }
      goto RETURN;
    case 1:
      v37 = *(g_pCbord + 48)
      if ( g_bSerialComm && v37 != 1)
      {
        LOBYTE(v1) = v37 + 1;
        if ( (_BYTE)v1 )
        {
          v106 = *(this + 88) + 1;
          v107 = *(this + 88) < 179;
          *(this + 88) = v106;
          if ( !((unsigned __int8)(v107 ^ __OFSUB__(v106, 180)) | (v106 == 180)) )
          {
            v108 = g_pLGJFont;
            *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
            v109 = (int)v108 + 968 * *((_DWORD *)v108 + 31006);
            *(_DWORD *)(v109 + 452) = 3;
            v110 = v106 % 120;
            if ( v110 <= 29 )
            {
              *(_DWORD *)(v109 + 544) = 500;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 137) = 0;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 144) = -1;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 145) = -1;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 146) = -1;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 147) = -1;
              LOBYTE(v1) = (unsigned int)strcpy(
                                           (char *)v108 + 968 * *((_DWORD *)v108 + 31006) + 832,
                                           "Serial Communications checking");
            }
            else if ( v110 <= 59 )
            {
              *(_DWORD *)(v109 + 544) = 500;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 137) = 0;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 144) = -1;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 145) = -1;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 146) = -1;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 147) = -1;
              LOBYTE(v1) = (unsigned int)strcpy(
                                           (char *)v108 + 968 * *((_DWORD *)v108 + 31006) + 832,
                                           "Serial Communications checking.");
            }
            else if ( v110 > 89 )
            {
              *(_DWORD *)(v109 + 544) = 500;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 137) = 0;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 144) = -1;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 145) = -1;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 146) = -1;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 147) = -1;
              LOBYTE(v1) = (unsigned int)strcpy(
                                           (char *)v108 + 968 * *((_DWORD *)v108 + 31006) + 832,
                                           "Serial Communications checking...");
            }
            else
            {
              *(_DWORD *)(v109 + 544) = 500;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 137) = 0;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 144) = -1;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 145) = -1;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 146) = -1;
              *((_DWORD *)v108 + 242 * *((_DWORD *)v108 + 31006) + 147) = -1;
              LOBYTE(v1) = (unsigned int)strcpy(
                                           (char *)v108 + 968 * *((_DWORD *)v108 + 31006) + 832,
                                           "Serial Communications checking..");
            }
            ++*((_DWORD *)v108 + 31006);
            g_pCbord = g_pCbord;
            v106 = *((_DWORD *)this + 22);
          }
          if ( v106 > 1800 || !*(g_pCbord + 24) )
          {
            v1 = (LGJCbord *)*(g_pCbord + 340);
            if ( !v1 )
            {
              *(g_pCbord + 340) = 209;
              goto LABEL_90;
            }
          }
        }
        else
        {
          globalBoard = 2;
        }
      }
      else
      {
        globalBoard = 3;
        LOBYTE(v1) = gsysMessage::setMsg(g_pMessage, 1, 2, 0);
      }
      goto RETURN;
    case 2u:
      v27 = g_pLGJFont;
      v28 = 0;
      *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
      v29 = (int)v27 + 968 * *((_DWORD *)v27 + 31006);
      *(_DWORD *)(v29 + 544) = 0;
      *(_DWORD *)(v29 + 452) = 4;
      *((_DWORD *)v27 + 242 * *((_DWORD *)v27 + 31006) + 137) = -150;
      *((_DWORD *)v27 + 242 * *((_DWORD *)v27 + 31006) + 144) = -1;
      *((_DWORD *)v27 + 242 * *((_DWORD *)v27 + 31006) + 145) = -1;
      *((_DWORD *)v27 + 242 * *((_DWORD *)v27 + 31006) + 146) = -1;
      *((_DWORD *)v27 + 242 * *((_DWORD *)v27 + 31006) + 147) = -1;
      strcpy((char *)v27 + 968 * *((_DWORD *)v27 + 31006) + 832, "UPDATED PROGRAM");
      ++*((_DWORD *)v27 + 31006);
      v30 = g_pCbord;
      if ( *((_BYTE *)g_pCbord + 54) )
      {
        v62 = g_pLGJFont;
        *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
        v63 = (int)v62 + 968 * *((_DWORD *)v62 + 31006);
        *(_DWORD *)(v63 + 544) = -90;
        *(_DWORD *)(v63 + 452) = 4;
        *((_DWORD *)v62 + 242 * *((_DWORD *)v62 + 31006) + 137) = -120;
        *((_DWORD *)v62 + 242 * *((_DWORD *)v62 + 31006) + 144) = -1;
        *((_DWORD *)v62 + 242 * *((_DWORD *)v62 + 31006) + 145) = -1;
        *((_DWORD *)v62 + 242 * *((_DWORD *)v62 + 31006) + 146) = -1;
        *((_DWORD *)v62 + 242 * *((_DWORD *)v62 + 31006) + 147) = -1;
        strcpy((char *)v62 + 968 * *((_DWORD *)v62 + 31006) + 832, "2ND BOOT");
        ++*((_DWORD *)v62 + 31006);
        v64 = *((_BYTE *)g_pCbord + 54);
        if ( v64 == 1 )
        {
          sprintf(&s, "Ver. %2x.%02x", *((unsigned __int8 *)g_pCbord + 60), *((unsigned __int8 *)g_pCbord + 61));
          v125 = g_pLGJFont;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v126 = (int)v125 + 968 * *((_DWORD *)v125 + 31006);
          *(_DWORD *)(v126 + 544) = 140;
          *(_DWORD *)(v126 + 452) = 4;
          *((_DWORD *)v125 + 242 * *((_DWORD *)v125 + 31006) + 137) = -120;
          *((_DWORD *)v125 + 242 * *((_DWORD *)v125 + 31006) + 144) = -1;
          *((_DWORD *)v125 + 242 * *((_DWORD *)v125 + 31006) + 145) = -1;
          *((_DWORD *)v125 + 242 * *((_DWORD *)v125 + 31006) + 146) = -1;
          *((_DWORD *)v125 + 242 * *((_DWORD *)v125 + 31006) + 147) = -1;
          strcpy((char *)v125 + 968 * *((_DWORD *)v125 + 31006) + 832, &s);
          ++*((_DWORD *)v125 + 31006);
          sprintf(&s, "SUM: %02X", *((unsigned __int8 *)g_pCbord + 57));
          v65 = g_pLGJFont;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v127 = (int)v65 + 968 * *((_DWORD *)v65 + 31006);
          *(_DWORD *)(v127 + 544) = 280;
          *(_DWORD *)(v127 + 452) = 4;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 137) = -120;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 144) = -1;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 145) = -1;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 146) = -1;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 147) = -1;
          v137 = &s;
        }
        else if ( v64 == 2 )
        {
          v65 = g_pLGJFont;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v123 = (int)v65 + 968 * *((_DWORD *)v65 + 31006);
          *(_DWORD *)(v123 + 544) = 140;
          *(_DWORD *)(v123 + 452) = 4;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 137) = -120;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 144) = -1;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 145) = -1;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 146) = -1;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 147) = -1;
          v137 = "FAILED";
        }
        else
        {
          v65 = g_pLGJFont;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v66 = (int)v65 + 968 * *((_DWORD *)v65 + 31006);
          *(_DWORD *)(v66 + 544) = 140;
          *(_DWORD *)(v66 + 452) = 4;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 137) = -120;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 144) = -1;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 145) = -1;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 146) = -1;
          *((_DWORD *)v65 + 242 * *((_DWORD *)v65 + 31006) + 147) = -1;
          v137 = "UNKNOWN";
        }
        v28 = 1;
        strcpy((char *)v65 + 968 * *((_DWORD *)v65 + 31006) + 832, v137);
        ++*((_DWORD *)v65 + 31006);
        v30 = g_pCbord;
      }
      if ( *((_BYTE *)v30 + 55) )
      {
        v57 = g_pLGJFont;
        *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
        v58 = (int)v57 + 968 * *((_DWORD *)v57 + 31006);
        v138 = 30 * v28 - 120;
        *(_DWORD *)(v58 + 544) = -90;
        *(_DWORD *)(v58 + 452) = 4;
        *((_DWORD *)v57 + 242 * *((_DWORD *)v57 + 31006) + 137) = v138;
        *((_DWORD *)v57 + 242 * *((_DWORD *)v57 + 31006) + 144) = -1;
        *((_DWORD *)v57 + 242 * *((_DWORD *)v57 + 31006) + 145) = -1;
        *((_DWORD *)v57 + 242 * *((_DWORD *)v57 + 31006) + 146) = -1;
        *((_DWORD *)v57 + 242 * *((_DWORD *)v57 + 31006) + 147) = -1;
        strcpy((char *)v57 + 968 * *((_DWORD *)v57 + 31006) + 832, "USB LOADER");
        ++*((_DWORD *)v57 + 31006);
        v59 = *((_BYTE *)g_pCbord + 55);
        if ( v59 == 1 )
        {
          sprintf(&s, "Ver. %2x.%02x", *((unsigned __int8 *)g_pCbord + 62), *((unsigned __int8 *)g_pCbord + 63));
          v128 = g_pLGJFont;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v129 = (int)v128 + 968 * *((_DWORD *)v128 + 31006);
          *(_DWORD *)(v129 + 544) = 140;
          *(_DWORD *)(v129 + 452) = 4;
          *((_DWORD *)v128 + 242 * *((_DWORD *)v128 + 31006) + 137) = v138;
          *((_DWORD *)v128 + 242 * *((_DWORD *)v128 + 31006) + 144) = -1;
          *((_DWORD *)v128 + 242 * *((_DWORD *)v128 + 31006) + 145) = -1;
          *((_DWORD *)v128 + 242 * *((_DWORD *)v128 + 31006) + 146) = -1;
          *((_DWORD *)v128 + 242 * *((_DWORD *)v128 + 31006) + 147) = -1;
          strcpy((char *)v128 + 968 * *((_DWORD *)v128 + 31006) + 832, &s);
          ++*((_DWORD *)v128 + 31006);
          sprintf(&s, "SUM: %02X", *((unsigned __int8 *)g_pCbord + 58));
          v60 = g_pLGJFont;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v130 = (int)v60 + 968 * *((_DWORD *)v60 + 31006);
          *(_DWORD *)(v130 + 544) = 280;
          *(_DWORD *)(v130 + 452) = 4;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 137) = v138;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 144) = -1;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 145) = -1;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 146) = -1;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 147) = -1;
          v136 = &s;
        }
        else if ( v59 == 2 )
        {
          v60 = g_pLGJFont;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v124 = (int)v60 + 968 * *((_DWORD *)v60 + 31006);
          *(_DWORD *)(v124 + 544) = 140;
          *(_DWORD *)(v124 + 452) = 4;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 137) = v138;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 144) = -1;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 145) = -1;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 146) = -1;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 147) = -1;
          v136 = "FAILED";
        }
        else
        {
          v60 = g_pLGJFont;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v61 = (int)v60 + 968 * *((_DWORD *)v60 + 31006);
          *(_DWORD *)(v61 + 544) = 140;
          *(_DWORD *)(v61 + 452) = 4;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 137) = v138;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 144) = -1;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 145) = -1;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 146) = -1;
          *((_DWORD *)v60 + 242 * *((_DWORD *)v60 + 31006) + 147) = -1;
          v136 = "UNKNOWN";
        }
        ++v28;
        strcpy((char *)v60 + 968 * *((_DWORD *)v60 + 31006) + 832, v136);
        ++*((_DWORD *)v60 + 31006);
        v30 = g_pCbord;
      }
      if ( *((_BYTE *)v30 + 56) )
      {
        v47 = g_pLGJFont;
        *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
        v48 = 30 * v28 - 120;
        v49 = (int)v47 + 968 * *((_DWORD *)v47 + 31006);
        *(_DWORD *)(v49 + 544) = -90;
        *(_DWORD *)(v49 + 452) = 4;
        *((_DWORD *)v47 + 242 * *((_DWORD *)v47 + 31006) + 137) = v48;
        *((_DWORD *)v47 + 242 * *((_DWORD *)v47 + 31006) + 144) = -1;
        *((_DWORD *)v47 + 242 * *((_DWORD *)v47 + 31006) + 145) = -1;
        *((_DWORD *)v47 + 242 * *((_DWORD *)v47 + 31006) + 146) = -1;
        *((_DWORD *)v47 + 242 * *((_DWORD *)v47 + 31006) + 147) = -1;
        strcpy((char *)v47 + 968 * *((_DWORD *)v47 + 31006) + 832, "APPLICATION");
        ++*((_DWORD *)v47 + 31006);
        v50 = *((_BYTE *)g_pCbord + 56);
        if ( v50 == 1 )
        {
          sprintf(&s, "Ver. %2x.%02x", *((unsigned __int8 *)g_pCbord + 64), *((unsigned __int8 *)g_pCbord + 65));
          v131 = g_pLGJFont;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v132 = (int)v131 + 968 * *((_DWORD *)v131 + 31006);
          *(_DWORD *)(v132 + 544) = 140;
          *(_DWORD *)(v132 + 452) = 4;
          *((_DWORD *)v131 + 242 * *((_DWORD *)v131 + 31006) + 137) = v48;
          *((_DWORD *)v131 + 242 * *((_DWORD *)v131 + 31006) + 144) = -1;
          *((_DWORD *)v131 + 242 * *((_DWORD *)v131 + 31006) + 145) = -1;
          *((_DWORD *)v131 + 242 * *((_DWORD *)v131 + 31006) + 146) = -1;
          *((_DWORD *)v131 + 242 * *((_DWORD *)v131 + 31006) + 147) = -1;
          strcpy((char *)v131 + 968 * *((_DWORD *)v131 + 31006) + 832, &s);
          ++*((_DWORD *)v131 + 31006);
          sprintf(&s, "SUM: %02X", *((unsigned __int8 *)g_pCbord + 59));
          v51 = g_pLGJFont;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v133 = (int)v51 + 968 * *((_DWORD *)v51 + 31006);
          *(_DWORD *)(v133 + 544) = 280;
          *(_DWORD *)(v133 + 452) = 4;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 137) = v48;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 144) = -1;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 145) = -1;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 146) = -1;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 147) = -1;
          strcpy((char *)v51 + 968 * *((_DWORD *)v51 + 31006) + 832, &s);
        }
        else if ( v50 == 2 )
        {
          v51 = g_pLGJFont;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v122 = (int)v51 + 968 * *((_DWORD *)v51 + 31006);
          *(_DWORD *)(v122 + 544) = 140;
          *(_DWORD *)(v122 + 452) = 4;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 137) = v48;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 144) = -1;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 145) = -1;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 146) = -1;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 147) = -1;
          strcpy((char *)v51 + 968 * *((_DWORD *)v51 + 31006) + 832, "FAILED");
        }
        else
        {
          v51 = g_pLGJFont;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v52 = (int)v51 + 968 * *((_DWORD *)v51 + 31006);
          *(_DWORD *)(v52 + 544) = 140;
          *(_DWORD *)(v52 + 452) = 4;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 137) = v48;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 144) = -1;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 145) = -1;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 146) = -1;
          *((_DWORD *)v51 + 242 * *((_DWORD *)v51 + 31006) + 147) = -1;
          strcpy((char *)v51 + 968 * *((_DWORD *)v51 + 31006) + 832, "UNKNOWN");
        }
        ++*((_DWORD *)v51 + 31006);
      }
      v31 = 0;
      v32 = 0;
      do
      {
        v33 = g_pLGJFont;
        *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
        v34 = (&cbord_update_jp01)[v31++];
        v35 = (int)v33 + 968 * *((_DWORD *)v33 + 31006);
        *(_DWORD *)(v35 + 544) = 0;
        *(_DWORD *)(v35 + 452) = 4;
        *((_DWORD *)v33 + 242 * *((_DWORD *)v33 + 31006) + 137) = v32;
        v32 += 40;
        *((_DWORD *)v33 + 242 * *((_DWORD *)v33 + 31006) + 144) = -1;
        *((_DWORD *)v33 + 242 * *((_DWORD *)v33 + 31006) + 145) = -1;
        *((_DWORD *)v33 + 242 * *((_DWORD *)v33 + 31006) + 146) = -1;
        *((_DWORD *)v33 + 242 * *((_DWORD *)v33 + 31006) + 147) = -1;
        LOBYTE(v1) = (unsigned int)strcpy((char *)v33 + 968 * *((_DWORD *)v33 + 31006) + 832, v34);
        ++*((_DWORD *)v33 + 31006);
      }
      while ( v31 <= 1 );
      goto RETURN;
    case 3u:
      *(g_pCbord + 209) = 2;
      v38 = acpSystem::getRegion(v135);
      v39 = dword_87B4CEC;
      v40 = g_pLGJFont;
      v41 = dword_87B4CE0;
      *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
      v42 = dword_87B4CE8;
      v43 = (int)v40 + 968 * *((_DWORD *)v40 + 31006);
      v9 = v38 != 1;
      v44 = dword_87B4CE4;
      *(_DWORD *)(v43 + 544) = v41;
      *(_DWORD *)(v43 + 452) = v39;
      v45 = off_87B4CF4;
      if ( !v9 )
        v45 = off_87B4CF0;
      *((_DWORD *)v40 + 242 * *((_DWORD *)v40 + 31006) + 137) = v44;
      *((_DWORD *)v40 + 242 * *((_DWORD *)v40 + 31006) + 144) = v42;
      *((_DWORD *)v40 + 242 * *((_DWORD *)v40 + 31006) + 145) = v42;
      *((_DWORD *)v40 + 242 * *((_DWORD *)v40 + 31006) + 146) = v42;
      *((_DWORD *)v40 + 242 * *((_DWORD *)v40 + 31006) + 147) = v42;
      strcpy((char *)v40 + 968 * *((_DWORD *)v40 + 31006) + 832, v45);
      ++*((_DWORD *)v40 + 31006);
      v46 = g_pCbord;

      if ( *(g_pCbord + 48) == 3 || _sInterface::checkTrgOn(1, 0x4000) ) {
        *(v46 + 209) = 3;
        *(this + 80) = 4;
        LOBYTE(v1) = gsysMessage::setMsg(g_pMessage, 1, 3, 0);

      }

      goto RETURN;

    case 4u:
      *((_BYTE *)g_pCbord + 209) = 3;
      v1 = g_pCbord;
      v22 = *((_DWORD *)g_pCbord + 53);
      if ( v22 & 0x360 || BYTE1(v22) & 0x30 || BYTE1(v22) & 8 )
      {
        if ( *((_DWORD *)g_pCbord + 53) & 0x360 )
        {
          v83 = acpSystem::getRegion(v135);
          v84 = dword_87B4C8C;
          v85 = g_pLGJFont;
          v86 = sensor_text_data;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v87 = dword_87B4C88;
          v88 = (int)v85 + 968 * *((_DWORD *)v85 + 31006);
          v9 = v83 != 1;
          v89 = dword_87B4C84;
          *(_DWORD *)(v88 + 544) = v86;
          *(_DWORD *)(v88 + 452) = v84;
          v90 = off_87B4C94;
          if ( !v9 )
            v90 = off_87B4C90;
          *((_DWORD *)v85 + 242 * *((_DWORD *)v85 + 31006) + 137) = v89;
          *((_DWORD *)v85 + 242 * *((_DWORD *)v85 + 31006) + 144) = v87;
          *((_DWORD *)v85 + 242 * *((_DWORD *)v85 + 31006) + 145) = v87;
          *((_DWORD *)v85 + 242 * *((_DWORD *)v85 + 31006) + 146) = v87;
          *((_DWORD *)v85 + 242 * *((_DWORD *)v85 + 31006) + 147) = v87;
          strcpy((char *)v85 + 968 * *((_DWORD *)v85 + 31006) + 832, v90);
          ++*((_DWORD *)v85 + 31006);
          v1 = g_pCbord;
        }
        if ( *((_BYTE *)v1 + 213) & 8 )
        {
          v75 = acpSystem::getRegion(v135);
          v76 = dword_87B4CA4;
          v77 = g_pLGJFont;
          v78 = dword_87B4C98;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v79 = dword_87B4CA0;
          v80 = (int)v77 + 968 * *((_DWORD *)v77 + 31006);
          v9 = v75 != 1;
          v81 = dword_87B4C9C;
          *(_DWORD *)(v80 + 544) = v78;
          *(_DWORD *)(v80 + 452) = v76;
          v82 = off_87B4CAC;
          if ( !v9 )
            v82 = off_87B4CA8;
          *((_DWORD *)v77 + 242 * *((_DWORD *)v77 + 31006) + 137) = v81;
          *((_DWORD *)v77 + 242 * *((_DWORD *)v77 + 31006) + 144) = v79;
          *((_DWORD *)v77 + 242 * *((_DWORD *)v77 + 31006) + 145) = v79;
          *((_DWORD *)v77 + 242 * *((_DWORD *)v77 + 31006) + 146) = v79;
          *((_DWORD *)v77 + 242 * *((_DWORD *)v77 + 31006) + 147) = v79;
          strcpy((char *)v77 + 968 * *((_DWORD *)v77 + 31006) + 832, v82);
          ++*((_DWORD *)v77 + 31006);
          v1 = g_pCbord;
        }
        if ( *((_DWORD *)v1 + 53) & 0x3000 )
        {
          v67 = acpSystem::getRegion(v135);
          v68 = dword_87B4CBC;
          v69 = g_pLGJFont;
          v70 = dword_87B4CB0;
          *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
          v71 = dword_87B4CB8;
          v72 = (int)v69 + 968 * *((_DWORD *)v69 + 31006);
          v9 = v67 != 1;
          v73 = dword_87B4CB4;
          *(_DWORD *)(v72 + 544) = v70;
          *(_DWORD *)(v72 + 452) = v68;
          v74 = off_87B4CC4;
          if ( !v9 )
            v74 = off_87B4CC0;
          *((_DWORD *)v69 + 242 * *((_DWORD *)v69 + 31006) + 137) = v73;
          *((_DWORD *)v69 + 242 * *((_DWORD *)v69 + 31006) + 144) = v71;
          *((_DWORD *)v69 + 242 * *((_DWORD *)v69 + 31006) + 145) = v71;
          *((_DWORD *)v69 + 242 * *((_DWORD *)v69 + 31006) + 146) = v71;
          *((_DWORD *)v69 + 242 * *((_DWORD *)v69 + 31006) + 147) = v71;
          strcpy((char *)v69 + 968 * *((_DWORD *)v69 + 31006) + 832, v74);
          ++*((_DWORD *)v69 + 31006);
          v1 = g_pCbord;
        }
        *((_BYTE *)v1 + 314) = 0;
        goto LABEL_51;
      }
      v112 = acpSystem::getRegion(v135);
      v113 = dword_87B4CD4;
      v114 = g_pLGJFont;
      v115 = dword_87B4CC8;
      *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
      v116 = dword_87B4CD0;
      v117 = (int)v114 + 968 * *((_DWORD *)v114 + 31006);
      v9 = v112 != 1;
      v118 = dword_87B4CCC;
      *(_DWORD *)(v117 + 544) = v115;
      *(_DWORD *)(v117 + 452) = v113;
      v119 = off_87B4CDC;
      if ( !v9 )
        v119 = off_87B4CD8;
      *((_DWORD *)v114 + 242 * *((_DWORD *)v114 + 31006) + 137) = v118;
      *((_DWORD *)v114 + 242 * *((_DWORD *)v114 + 31006) + 144) = v116;
      *((_DWORD *)v114 + 242 * *((_DWORD *)v114 + 31006) + 145) = v116;
      *((_DWORD *)v114 + 242 * *((_DWORD *)v114 + 31006) + 146) = v116;
      *((_DWORD *)v114 + 242 * *((_DWORD *)v114 + 31006) + 147) = v116;
      strcpy((char *)v114 + 968 * *((_DWORD *)v114 + 31006) + 832, v119);
      v120 = g_pCbord;
      ++*((_DWORD *)v114 + 31006);
      if ( !*((_BYTE *)v120 + 315) )
      {
        *((_BYTE *)v120 + 315) = 1;
        *((_DWORD *)v120 + 79) = 0;
      }
      if ( (unsigned __int8)_sInterfaceJvs::checkTrgOn(1, 2147483648)
        || (LOBYTE(v1) = _sInterface::checkTrgOn(1, 0x1000000), (_BYTE)v1)
        || !g_bNotAutoPlayCheck )
      {
        v121 = g_pMessage;
        *((_DWORD *)this + 20) = 5;
        gsysMessage::setMsg(v121, 1, 4, 0);
        v1 = g_pCbord;
        *((_BYTE *)g_pCbord + 314) = 1;
LABEL_51:
        *((_BYTE *)v1 + 315) = 0;
      }
RETURN:
      if ( !g_iSystemShutdown )
      {
        v1 = (LGJCbord *)globalBoard;
        if ( v1 != (LGJCbord *)2 && v1 != (LGJCbord *)15 )
        {
          v12 = 0;
          if ( byte_88185A0 )
          {
            LOBYTE(v1) = 1;
            if ( !byte_88185A1 )
              v12 = 1;
          }
          if ( !v12 )
            LOBYTE(v1) = gsysCoin::exec(g_pCoin);
        }
      }
      return (unsigned int)v1;
    case 5u:
      *((_BYTE *)g_pCbord + 209) = 4;
      if ( *((_BYTE *)g_pCbord + 48) == 5 || (LOBYTE(v1) = _sInterface::checkTrgOn(1, 0x4000), (_BYTE)v1) )
      {
        acpShader::setFlipDrawMode(g_pShader, 0);
        v19 = g_pCbord;
        v20 = *((_BYTE *)g_pCbord + 66);
        *((_BYTE *)g_pCbord + 25) = 1;
        *((_BYTE *)v19 + 233) = v20;
        if ( v20 )
          *((float *)v19 + 59) = (float)v20 * 0.020807063;
        else
          *((_DWORD *)v19 + 59) = 1065749138;
        gsysMessage::delMsg(g_pMessage);
        v21 = g_pCbord;
        *((_BYTE *)g_pCbord + 314) = 0;
        *((_BYTE *)v21 + 315) = 0;
        acpBackup::TouchSeatiniFile(g_pBackup);
        if ( (unsigned __int8)acpBackup::isExistTesthaltFile(g_pBackup) )
          acpBackup::ClearTesthaltFile(g_pBackup);
LABEL_35:
        gotoAdvLoop(0);
        v1 = g_pCbord;
        *(g_pCbord + 216) = 0;
        *(g_pCbord+ 217) = 0;
      }
      else if ( *((_BYTE *)g_pCbord + 48) == 16 )
      {
        *((_DWORD *)this + 20) = 13;
      }
      goto RETURN;
    case 6u:
      acpShader::setFlipDrawMode(g_pShader, 1);
      v17 = g_pCbord;
      *((_BYTE *)g_pCbord + 312) = 0;
      *((_BYTE *)v17 + 240) = 0;
      *((_BYTE *)v17 + 218) = 0;
      *((_BYTE *)v17 + 241) = 0;
      *((_BYTE *)v17 + 232) = 0;
      *((_BYTE *)v17 + 256) = 0;
      *((_BYTE *)v17 + 272) = 0;
      *((_BYTE *)v17 + 289) = 0;
      *((_BYTE *)v17 + 308) = 0;
      *((_BYTE *)v17 + 310) = 64;
      *((_BYTE *)v17 + 311) = 0;
      *((_BYTE *)v17 + 313) = 0;
      v18 = g_pCbord;
      *((_DWORD *)v17 + 55) = 0;
      *((_DWORD *)v17 + 56) = 3;
      *((_DWORD *)v17 + 61) = 0;
      *((_DWORD *)v17 + 63) = 0;
      *((_DWORD *)v17 + 57) = 0;
      *((_DWORD *)v17 + 65) = 0;
      *((_DWORD *)v17 + 67) = 0;
      *((_DWORD *)v17 + 69) = 0;
      *((_DWORD *)v17 + 71) = 0;
      *((_BYTE *)v17 + 288) = 0;
      *((_DWORD *)v17 + 73) = 0;
      *((_DWORD *)v17 + 74) = 0;
      *((_DWORD *)v17 + 75) = 0;
      *((_DWORD *)v17 + 76) = 0;
      *((_BYTE *)v17 + 320) = 1;
      *((_BYTE *)v17 + 314) = 0;
      *((_BYTE *)v17 + 315) = 0;
      *((_DWORD *)v17 + 79) = 0;
      *((_BYTE *)v18 + 312) = 1;
      LOBYTE(v1) = gsysMessage::setMsg(g_pMessage, 1, 1, 0);
      goto LABEL_37;
    case 7u:
      LOBYTE(v1) = (_BYTE)g_pCbord;
      if ( *((_BYTE *)g_pCbord + 48) == 20 )
      {
        *((_BYTE *)g_pCbord + 209) = 20;
        *((_DWORD *)this + 20) = 8;
        LOBYTE(v1) = gsysMessage::setMsg(g_pMessage, 1, 0, 0);
      }
      goto RETURN;
    case 8u:
      v1 = g_pCbord;
      if ( *((_BYTE *)g_pCbord + 48) == 21 )
      {
        *((_BYTE *)g_pCbord + 209) = 21;
        *((_DWORD *)this + 20) = 9;
        LOBYTE(v1) = gsysMessage::setMsg(g_pMessage, 1, 7, 0);
      }
      else
      {
        v2 = *((_DWORD *)g_pCbord + 53);
        if ( v2 & 0x360 || BYTE1(v2) & 0x30 || BYTE1(v2) & 8 )
        {
          if ( *((_DWORD *)g_pCbord + 53) & 0x360 )
          {
            v99 = acpSystem::getRegion(v135);
            v100 = dword_87B4C8C;
            v101 = g_pLGJFont;
            v102 = dword_87B4C84;
            *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
            v103 = dword_87B4C88;
            v104 = (int)v101 + 968 * *((_DWORD *)v101 + 31006);
            *(_DWORD *)(v104 + 544) = sensor_text_data;
            *(_DWORD *)(v104 + 452) = v100;
            v105 = off_87B4C94;
            if ( v99 == 1 )
              v105 = off_87B4C90;
            *((_DWORD *)v101 + 242 * *((_DWORD *)v101 + 31006) + 137) = v102;
            *((_DWORD *)v101 + 242 * *((_DWORD *)v101 + 31006) + 144) = v103;
            *((_DWORD *)v101 + 242 * *((_DWORD *)v101 + 31006) + 145) = v103;
            *((_DWORD *)v101 + 242 * *((_DWORD *)v101 + 31006) + 146) = v103;
            *((_DWORD *)v101 + 242 * *((_DWORD *)v101 + 31006) + 147) = v103;
            strcpy((char *)v101 + 968 * *((_DWORD *)v101 + 31006) + 832, v105);
            ++*((_DWORD *)v101 + 31006);
            v1 = g_pCbord;
          }
          if ( *((_BYTE *)v1 + 213) & 8 )
          {
            v91 = acpSystem::getRegion(v135);
            v92 = dword_87B4CA4;
            v93 = g_pLGJFont;
            v94 = dword_87B4C98;
            *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
            v95 = dword_87B4CA0;
            v96 = (int)v93 + 968 * *((_DWORD *)v93 + 31006);
            v9 = v91 != 1;
            v97 = dword_87B4C9C;
            *(_DWORD *)(v96 + 544) = v94;
            *(_DWORD *)(v96 + 452) = v92;
            v98 = off_87B4CAC;
            if ( !v9 )
              v98 = off_87B4CA8;
            *((_DWORD *)v93 + 242 * *((_DWORD *)v93 + 31006) + 137) = v97;
            *((_DWORD *)v93 + 242 * *((_DWORD *)v93 + 31006) + 144) = v95;
            *((_DWORD *)v93 + 242 * *((_DWORD *)v93 + 31006) + 145) = v95;
            *((_DWORD *)v93 + 242 * *((_DWORD *)v93 + 31006) + 146) = v95;
            *((_DWORD *)v93 + 242 * *((_DWORD *)v93 + 31006) + 147) = v95;
            strcpy((char *)v93 + 968 * *((_DWORD *)v93 + 31006) + 832, v98);
            ++*((_DWORD *)v93 + 31006);
            v1 = g_pCbord;
          }
          if ( *((_DWORD *)v1 + 53) & 0x3000 )
          {
            v3 = acpSystem::getRegion(v135);
            v4 = dword_87B4CBC;
            v5 = g_pLGJFont;
            v6 = dword_87B4CB0;
            *((_DWORD *)g_pLGJFont + 242 * *((_DWORD *)g_pLGJFont + 31006) + 143) = 255;
            v7 = dword_87B4CB8;
            v8 = (int)v5 + 968 * *((_DWORD *)v5 + 31006);
            v9 = v3 != 1;
            v10 = dword_87B4CB4;
            *(_DWORD *)(v8 + 544) = v6;
            *(_DWORD *)(v8 + 452) = v4;
            v11 = off_87B4CC4;
            if ( !v9 )
              v11 = off_87B4CC0;
            *((_DWORD *)v5 + 242 * *((_DWORD *)v5 + 31006) + 137) = v10;
            *((_DWORD *)v5 + 242 * *((_DWORD *)v5 + 31006) + 144) = v7;
            *((_DWORD *)v5 + 242 * *((_DWORD *)v5 + 31006) + 145) = v7;
            *((_DWORD *)v5 + 242 * *((_DWORD *)v5 + 31006) + 146) = v7;
            *((_DWORD *)v5 + 242 * *((_DWORD *)v5 + 31006) + 147) = v7;
            LOBYTE(v1) = (unsigned int)strcpy((char *)v5 + 968 * *((_DWORD *)v5 + 31006) + 832, v11);
            ++*((_DWORD *)v5 + 31006);
          }
        }
      }
      goto RETURN;
    case 9u:
      LOBYTE(v1) = *((_BYTE *)g_pCbord + 48);
      switch ( (_BYTE)v1 )
      {
        case 5:
          gsysMessage::setMsg(g_pMessage, 0, 0, 0);
          acpShader::setFlipDrawMode(g_pShader, 0);
          g_iSystemEmergency = 0;
          g_iSystemSafety = 0;
          v54 = g_pBackup;
          *((_DWORD *)g_pCbord + 87) = -1;
          if ( (unsigned __int8)acpBackup::isExistTesthaltFile(v54) )
          {
            v55 = g_pCbord;
            v56 = *((_BYTE *)g_pCbord + 66);
            *((_BYTE *)g_pCbord + 233) = v56;
            if ( v56 )
              *((float *)v55 + 59) = (float)v56 * 0.020807063;
            else
              *((_DWORD *)v55 + 59) = 1065749138;
            acpBackup::ClearTesthaltFile(g_pBackup);
          }
          *((_BYTE *)g_pCbord + 312) = 0;
          *((_DWORD *)g_pCbord + 1) = 0;
LABEL_90:
          LOBYTE(v1) = gotoAdvLoop(0);
          break;
        case 0x10:
          *((_BYTE *)g_pCbord + 209) = 16;
          *((_DWORD *)this + 20) = 12;
          break;
        case 0x12:
          *((_BYTE *)g_pCbord + 209) = 18;
          *((_DWORD *)this + 20) = 10;
          break;
      }
      goto RETURN;
    case 0xAu:
      goto LABEL_28;
    case 0xBu:
      acpShader::setFlipDrawMode(g_pShader, 1);
      v23 = g_pCbord;
      *((_BYTE *)g_pCbord + 312) = 0;
      *((_BYTE *)v23 + 240) = 0;
      *((_BYTE *)v23 + 218) = 0;
      *((_BYTE *)v23 + 241) = 0;
      *((_BYTE *)v23 + 232) = 0;
      *((_BYTE *)v23 + 256) = 0;
      *((_BYTE *)v23 + 272) = 0;
      *((_BYTE *)v23 + 289) = 0;
      *((_BYTE *)v23 + 308) = 0;
      *((_BYTE *)v23 + 310) = 64;
      *((_BYTE *)v23 + 311) = 0;
      *((_BYTE *)v23 + 313) = 0;
      v24 = g_pCbord;
      *((_DWORD *)v23 + 55) = 0;
      *((_DWORD *)v23 + 56) = 3;
      *((_BYTE *)v24 + 312) = 3;
      *((_DWORD *)v23 + 61) = 0;
      *((_DWORD *)v23 + 63) = 0;
      v25 = g_pCbord;
      *((_DWORD *)v23 + 57) = 0;
      *((_DWORD *)v23 + 65) = 0;
      v26 = *((_DWORD *)v25 + 87);
      *((_DWORD *)v23 + 67) = 0;
      *((_DWORD *)v23 + 69) = 0;
      *((_DWORD *)v23 + 71) = 0;
      *((_BYTE *)v23 + 288) = 0;
      *((_DWORD *)v23 + 73) = 0;
      *((_DWORD *)v23 + 74) = 0;
      *((_DWORD *)v23 + 75) = 0;
      *((_DWORD *)v23 + 76) = 0;
      *((_BYTE *)v23 + 320) = 1;
      *((_BYTE *)v23 + 314) = 0;
      *((_BYTE *)v23 + 315) = 0;
      *((_DWORD *)v23 + 79) = 0;
      LOBYTE(v1) = gsysMessage::setMsg(g_pMessage, 2, v26, 0);
LABEL_37:
      *((_DWORD *)this + 20) = 7;
      goto RETURN;
    case 0xCu:
      acpShader::setFlipDrawMode(g_pShader, 1);
LABEL_28:
      gsysMessage::setMsg(g_pMessage, 1, 6, 0);
      LOBYTE(v1) = (_BYTE)this;
      *((_DWORD *)this + 20) = 7;
      goto RETURN;
    case 0xDu:
      acpShader::setFlipDrawMode(g_pShader, 1);
      LOBYTE(v1) = gsysMessage::setMsg(g_pMessage, 1, 5, *((_DWORD *)g_pCbord + 85));
      *((_BYTE *)g_pCbord + 312) = 4;
      *((_BYTE *)g_pCbord + 209) = 22;
      *((_DWORD *)this + 20) = 14;
      goto RETURN;
    default:
      goto RETURN;
  }
}

char __cdecl LGJCbord::setGameStatusADV(LGJCbord *this)
{
  char v1; // cl@1
  char result; // al@3
  acpSystem *v3; // [esp+0h] [ebp-8h]@0

  v1 = *((_BYTE *)this + 209);
  if ( v1 == 23 || v1 == 17 || v1 == 18 )
  {
    result = 25 - ((unsigned __int8)acpSystem::isFreePlay(v3) < 1u);
    *((_BYTE *)this + 209) = result;
  }
  else
  {
    result = 6 - ((unsigned __int8)acpSystem::isFreePlay(v3) < 1u);
    *((_BYTE *)this + 209) = result;
  }
  return result;
}
