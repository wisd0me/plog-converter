//  2006-2008 (c) Viva64.com Team
//  2008-2020 (c) OOO "Program Verification Systems"
//  2020 (c) PVS-Studio LLC

#include "junitoutput.h"

namespace PlogConverter
{

JUOutput::JUOutput(const ProgramOptions &opt) : BasicFormatOutput(opt)
{

}

void JUOutput::Start()
{
}

bool JUOutput::Write(const Warning& msg)
{
  if (msg.IsDocumentationLinkMessage())
    return false;

  m_w.push_back(msg);
  return true;
}

static void _Write(std::basic_ostream<char>& m_ostream, const Warning& msg)
{
  const std::string loc(msg.GetFile() + ":" + std::to_string(msg.GetLine()));

  m_ostream << "  <testcase id=\"diagnostic\" name=\"" << msg.code << ' ' << loc << "\" time=\"0\">" << std::endl
            << "    <failure message=\"" << msg.code << ' ' << loc << "\" type=\"" << msg.GetLevelString() << "\">" << std::endl
            << "      " << msg.GetLevelString() << std::endl
            << "      " << EscapeHtml(msg.message) << std::endl;

  auto extendedLines = msg.GetExtendedLines();
  if (extendedLines.size() > 1)
    m_ostream << "      Position lines: " << Join(extendedLines, [](auto v) { return std::to_string(v); }, ",") << msg.GetFile() << std::endl;

  if (msg.HasCWE())
    m_ostream << "      CWECode: " << msg.GetCWEString() << std::endl;

  if (msg.GetType() == AnalyzerType::Misra && msg.HasSAST())
	  m_ostream << "      MISRA: " << msg.sastId << std::endl;

  m_ostream << "    </failure>" << std::endl
            << "  </testcase>" << std::endl;
}

void JUOutput::Finish()
{
  const std::string cnt(std::to_string(m_w.size()));

  m_ostream << "<?xml version=\"1.0\"?>" << std::endl
            << "<testsuites id=\"PVS\" name=\"Code Analysis\" tests=\"" << cnt << "\" "
            << "failures=\"" << cnt << "\" time=\"0\">" << std::endl
            << "  <testsuite id=\"PVS\" name=\"Code Analysis\" tests=\"" << cnt << "\" "
            << "failures=\"" << cnt << "\" time=\"0\">" << std::endl;

  for (auto i: m_w)
  {
    const std::string loc(i.GetFile() + ":" + std::to_string(i.GetLine()));

    _Write(m_ostream, i);
  }

  m_ostream << "  </testsuite>" << std::endl
            << "</testsuites>" << std::endl;
}

}
