#pragma once
#ifndef DSO_USER_CHARMAP_H
#define DSO_USER_CHARMAP_H
#define ENABLE_CHARMAP

#if defined(ADD_MODULE) && defined(ENABLE_CHARMAP)
ADD_MODULE("CharMap", CWndCharMap)
#endif

#ifndef __CHARMAP_H__
#define __CHARMAP_H__

#include <Source/Core/Utils.h>
#include <Source/Framework/Wnd.h>

class CWndCharMap : public CWnd {
 public:
  virtual void Create(CWnd *pParent, ui16 dwFlags);
  virtual void OnPaint();
  virtual void OnMessage(CWnd *pSender, ui16 code, ui32 data);
  virtual void OnKey(ui16 nKey);
};

#endif
#endif
