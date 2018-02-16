#pragma once
#ifndef DSO_GUI_OSCILLOSCOPE_MASK_MENUMASK_H
#define DSO_GUI_OSCILLOSCOPE_MASK_MENUMASK_H

#include "../Disp/ItemDisp.h"
#include <Source/Core/Controls.h>
#include <Source/Core/ListItems.h>
#include <Source/Core/Settings.h>
#include <Source/Gui/Oscilloscope/Controls/GraphOsc.h>

class CMIButton : public CWndMenuItem {
public:
  virtual void Create(const char *pszId, ui16 clr, int nRows, CWnd *pParent) {
    CWndMenuItem::Create(pszId, clr, nRows, pParent);
  }

  virtual void OnPaint() { CWndMenuItem::OnPaint(); }

  virtual void OnKey(ui16 nKey) {
    if (nKey & (BIOS::KEY::KeyEnter | BIOS::KEY::KeyLeft | BIOS::KEY::KeyRight))
      SendMessage(GetParent(), CWnd::WmKey, nKey);
    CWnd::OnKey(nKey);
  }
};

class CWndMenuMask : public CWnd {
public:
  enum EAction {
    ActionNone = 0,
    ActionBeep = 1,
    ActionBeepStop = 2,
    ActionStop = 3,
    ActionMax = ActionStop
  };
  enum EDisplay { DisplayNo = 0, DisplayYes = 1, DisplayMax = DisplayYes };

  static const char *const m_ppszTextAction[];
  static const char *const m_ppszDispAction[];

public:
  // Menu items
  CMIButton m_btnSource;
  CMIButton m_btnReset;
  CMIButton m_btnCollect;
  CMIButton m_btnStop;
  // CMIButton	m_btnAction;
  CMIButton m_btnExpand;
  CMIButton m_btnBlur;
  CMPItem m_itmAction;
  CProviderEnum m_proAction;
  CMPItem m_itmDisplay;
  CProviderEnum m_proDisplay;

  EAction m_Action;
  EDisplay m_Display;

  virtual void Create(CWnd *pParent, ui16 dwFlags);
  virtual void OnMessage(CWnd *pSender, CodeParam code, DataParam data);
};

#endif