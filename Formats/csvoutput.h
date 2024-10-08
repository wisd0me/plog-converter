//  2006-2008 (c) Viva64.com Team
//  2008-2020 (c) OOO "Program Verification Systems"
//  2020-2023 (c) PVS-Studio LLC

#pragma once
#include "ioutput.h"

namespace PlogConverter
{

class CSVOutput : public BasicFormatOutput<CSVOutput>
{
public:
  explicit CSVOutput(const ProgramOptions&);
  ~CSVOutput() override = default;

  void Start() override;
  bool Write(const Warning& msg) override;

  [[nodiscard]]
  static bool SupportsRelativePath() noexcept
  {
    return false;
  }

  [[nodiscard]]
  static bool OutputIsFile() noexcept
  {
    return true;
  }

  [[nodiscard]]
  static std::string_view FormatName() noexcept
  {
    return "csv";
  }

  [[nodiscard]]
  static std::string_view OutputSuffix() noexcept
  {
    return FormatName();
  }
};

}
