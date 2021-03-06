#pragma once
#ifndef DSO_GUI_GENERATOR_CORE_COREGENERATOR_H
#define DSO_GUI_GENERATOR_CORE_COREGENERATOR_H

#include <Source/Framework/Classes.h>
#include <Source/HwLayer/Types.h>

class CCoreGenerator {
  static const struct TWaveData {
    char *pszName;
    ui16 nCount;
    const ui16 *pWave;
    ui16 nOversampling;
  } Waves[];

  // NOTE: big buffer
  static ui16 m_pRamWave[128 * 4];
  static int m_nRamLen;
  // buffer for editing custom waves and for copying signal
  // from oscilloscope
  static ui8 m_pVolatile[256];
  static int m_nVolatileLen;

 public:
  static ui16 *GetRamDac();
  static int GetRamLen();
  static void Update();

  static ui8 *GetVolatile();
  static int &GetVolatileLen();

  static int GetDuty();
  static void SetDuty(int nPercent);

  static const TWaveData *GetWave(int nWave);
  static void CopyToVolatile(int nWave);

 protected:
  static ui16 _GetCount(ui8 nWaveIndex);
  static ui16 *_GetWave(ui8 nWaveIndex);
};

#endif