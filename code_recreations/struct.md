The LGJCbord struct memory layout:

      005: serial port object
      008: set to value 28 on init
      009: set to value 32 on init
      010: set to value 00 on init
      012: Set to 1 on init
      016: Set to 0 on init
      018: Open Fail is 0x00 Success is 0x01
      020: The serial port object probably
      024: CBord enable
      025: Check of CLASS RECEIVE BUFFER OKAY? set to 0 on init
      026: wont send if 1 (test mode no send?)

      031: Some variable that causes a branch
32 -> 037: CLASS SEND BUFFER
38 checksum variable
39 -> 045: SERIAL SEND BUFFER
46 -> 067: CLASS RECEIVE BUFFER
68 -> 195: SERIAL RECIEVE BUFFER
      196: int sent okay? set to 0 on init
      200: int Received Status? gets set to 1 on init

      209: First byte of sent message can be (0x11, 0x17 = 0x19 response) (0x00, 0x12 = 0x6) THIS IS CONFIRMED

      212: made up of a 24bit number from (50, 51, 52)
      216: Set to 0 if the bit 5 (from the right) of 52 doesn't equal 0 (could also be 50 I don't know what HYBYTE does) starts as 1
      217: Set to 0 if the bit 6 of 52 doesn't equal 0
      240: Some variable set to 0x0 on init (GETS THE NUMBER FROM 49 PUT IN THERE)
      241: possibly the last position
      256: Gets set to 0 when seat stop - possibly a position?

      260: Gets set to 1 when seat stops, and has not not be 2 to set seat to stop
      268: Gets set to something when seat stops

      289: sets whats in 35
      308: seems to be outputs?
      310: Life LED? Shows life counter on an LED maybe?

      312: gets set to 0xff on test mode.

      313: Something about teest mode
      314: seems to be outputs?
      320: means seat it okay?
      324: Some counter
      328: Gets set to value in 47 if value in 47 is less than 4

      332: Gets incremeneted if 53 is less than 10
      336: Gets set to what was in 53 - initially set to
      340: If 53 is less than 10 and this is 0 then this equals 200 + 53


      404 - think its 404 big?

32 - 0xC0
33 - 209 (Command)
35 -> 289 (or 0 in test mode when 33 is 0x13)
36 -> 308
37 -> 313 (or 0 in test mode when 33 is 0x13)

SEND:
  32 - 0xC0
  33 - Takes from 209 which is the command that is set I think
  34 - set to 0 - gets from 218
  35 - Set to 0 if on test mode or whats in 289 if notg
  36 - Gets set to 308
  37 - set to 131 if not in test mode?
  38 - Checksum

RECEIVE:
  46 - 0xC0
  47 - If less than 0x4 324 gets incremented by one, and 328 gets set to this
  48 - This gets checked at the startup, and if its 16 or 26 something else happens (26 looks like it means it works!)
  49 - Must be less than or equal to 0xC and 49 & 0xf != 0x0 can be (1,3,5,11)
  50 DWORD - LOW BYTE      |   -- SEEMS TO GET SET TO RETURN STATUS?
  51 - HIGH BYTE     |
  52 - HIGHEST BYTE  |
  53 - if <= 10 does some counter stuf
  54
  55 - DWORD
  56 - CAN BE 3
  57 - 55
  58 - 55
  59 - DWORD
  60 - 59
  61 - SWITCH CASE CAN BE 1 or 2
  62 - 59
  63
  64
  65
  66 -
  67 - CHECKSUM

  V1 = &61
  SELECT CASE V1:
    CASE 1:
      IF &56 != 3:
        V1 = 3
        IF &49 > 0XC0 || !(&49 & 1):
          V1 = 2
        &56 = V1
      return V1
    CASE 2:



At boot up it checks if test mode is enabled:
        *(int8_t *)_sInterfaceJvsManager::_bUseCredit = 0x0;
        int variable = (*g_pCbord + 48) & 0xff;
        if ((variable != 0x10) && (variable != 0x1a)) {
                (*g_pCbord + 209) = 0x13;
        }
        else {
                (*g_pCbord + 209) = 0x1a;
        }
        LGJCbord::resetSendParam();
        *(int8_t *)(*g_pCbord + 0x138) = 0xff;
        esi = operator new(0xa8);
        TestMenu::TestMenu();
        *g_pTestMenu = esi;
        TestMenu::set(esi);
        new_Player();
        eax = mtrLoopManager::setMode(*pLoopManager);


Gun test spinning the seat:
if (*(int8_t *)(*g_pCbord + 0x140) != 0x0) {
          var_24 = 0x51;
  }
  else {
          var_24 = 0x21;
  }
  LGJCbord::setSeatParam(*g_pCbord, var_24, 0x0);
