#ifdef _WIN32
  #include <windows.h>
#endif
#include "base.h"

#ifndef PIPE_H
#define PIPE_H

const int LINE_INPUT_MAX_CHAR = 8192;

struct PipeStruct {
#ifdef _WIN32
  HANDLE hInput, hOutput;
  BOOL bConsole;
  int64nBytesLeft;
#else
  int64_t nInput, nOutput;
#endif
  int64_t nEof;
  int64_t nReadEnd;
  char szBuffer[LINE_INPUT_MAX_CHAR];

  void Open(const char *szExecFile = NULL);
  void Close(void) const;
  void ReadInput(void);
  bool CheckInput(void);
  bool GetBuffer(char *szLineStr);
  bool LineInput(char *szLineStr);
  void LineOutput(const char *szLineStr) const;
}; // pipe

#endif
