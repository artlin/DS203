#include <Source/HwLayer/Bios.h>

class CCookies {
public:
  static char *GetCookie(char *strName) {
    char *strBuffer = BIOS::SYS::GetSharedBuffer();

    char *strFind = NULL;
    while ((strFind = strstr(strBuffer, strName)) != NULL) {
      if (strFind == strBuffer || strFind[-1] == ';') {
        // name=value
        strFind = strstr(strFind, "=");
        if (!strFind) {
          _ASSERT(0);
          return NULL;
        }
        return strFind + 1;
      }
      strBuffer = strFind + 1;
    }
    return NULL;
  }

  static void SetCookie(char *strName, char *strValue) {
    if (strValue == NULL || CUtils::StrLen(strValue) == 0) {
      DeleteCookie(strName);
      return;
    }
    char *strBuffer = BIOS::SYS::GetSharedBuffer();
    int nLength = BIOS::SYS::GetSharedLength();
    char *pCookie = GetCookie(strName);

    _ASSERT((int)((pCookie ? CUtils::StrLen(pCookie) : 0) +
                  CUtils::StrLen(strName) + CUtils::StrLen(strValue)) +
                2 <
            nLength);

    if (!pCookie) {
      _ASSERT(!strstr(strName, "=") && !strstr(strName, ";"));
      _ASSERT(!strstr(strValue, "=") && !strstr(strValue, ";"));

      char *strEnd = strBuffer + CUtils::StrLen(strBuffer);
      CUtils::StrCat(strEnd, strName);
      CUtils::StrCat(strEnd, "=");
      CUtils::StrCat(strEnd, strValue);
      CUtils::StrCat(strEnd, ";");
      return;
    }

    int nOldLength = strstr(pCookie, ";") - pCookie;
    int nNewLength = CUtils::StrLen(strValue);
    // move bytes
    if (nNewLength < nOldLength) {
      int nReduce = nOldLength - nNewLength;
      for (int i = pCookie - strBuffer + nOldLength;
           i <= (int)CUtils::StrLen(strBuffer); i++)
        strBuffer[i - nReduce] = strBuffer[i];
    } else if (nNewLength > nOldLength) {
      int nExpand = nNewLength - nOldLength;
      for (int i = CUtils::StrLen(strBuffer);
           i >= pCookie - strBuffer + nOldLength; i--)
        strBuffer[i + nExpand] = strBuffer[i];
    }
    memcpy(pCookie, strValue, nNewLength);
    _ASSERT(pCookie[nNewLength] == ';');
  }

  static void DeleteCookie(char *strName) {
    char *strBuffer = BIOS::SYS::GetSharedBuffer();
    char *pCookie = GetCookie(strName);
    _ASSERT(pCookie);

    char *pEnd = strstr(pCookie, ";");
    if (!pEnd) {
      _ASSERT(0);
      return;
    }
    pCookie -= CUtils::StrLen(strName) + 1;
    int nBegin = pCookie - strBuffer;
    int nEnd = pEnd - strBuffer + 1;

    int nReduce = nEnd - nBegin;
    for (int i = nEnd; i <= (int)CUtils::StrLen(strBuffer); i++)
      strBuffer[i - nReduce] = strBuffer[i];
  }
};
