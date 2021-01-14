//  2006-2008 (c) Viva64.com Team
//  2008-2020 (c) OOO "Program Verification Systems"
//  2020 (c) PVS-Studio LLC

#ifndef JUNITOUTPUT_H
#define JUNITOUTPUT_H
#include "ioutput.h"

#include <vector>

namespace PlogConverter
{

class JUOutput : public IOutput
{
  std::vector<Warning> m_w;

public:
  explicit JUOutput(const ProgramOptions &);
  void Start() override;
  void Write(const Warning& msg) override;
  void Finish() override;
  ~JUOutput() override;
};

}

#endif // JUNITOUTPUT_H
