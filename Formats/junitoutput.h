#pragma once
#include "ioutput.h"

#include <vector>

namespace PlogConverter
{

class JUOutput : public BasicFormatOutput<JUOutput>
{
  std::vector<Warning> m_w;

public:
  explicit JUOutput(const ProgramOptions &);
  ~JUOutput() override = default;

  void Start() override;
  bool Write(const Warning& msg) override;
  void Finish() override;

  [[nodiscard]]
  static bool SupportsRelativePath() noexcept
  {
    return true;
  }

  [[nodiscard]]
  static bool OutputIsFile() noexcept
  {
    return true;
  }

  [[nodiscard]]
  static std::string_view FormatName() noexcept
  {
    return "junit";
  }

  [[nodiscard]]
  static std::string_view OutputSuffix() noexcept
  {
    return FormatName();
  }
};

}
