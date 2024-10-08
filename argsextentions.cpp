//  2006-2008 (c) Viva64.com Team
//  2008-2020 (c) OOO "Program Verification Systems"
//  2020-2023 (c) PVS-Studio LLC

#include "argsextentions.h"

StringSplitter::StringSplitter(std::vector<std::string> separators)
  : m_separators { std::move(separators) }
{
}

template <typename It>
It StringSplitter::SkipSeparator(It strIt, It last, std::string_view sep) const noexcept
{
  auto ret = strIt;

  for (auto sepCh : sep)
  {
    if (strIt == last)
    {
      return strIt;
    }

    if (sepCh == *(strIt++))
    {
      ++ret;
    }
  }

  return ret;
}

template<typename It>
bool StringSplitter::IsAnySeparator(It strIt, It last) const noexcept
{
  for (const auto &sep : m_separators)
  {
    if (SkipSeparator(strIt, last, sep) != strIt)
    {
      return true;
    }
  }

  return false;
}

template <typename It>
It StringSplitter::SkipAnySeparator(It strIt, It last) const noexcept
{
  for (const auto &sep : m_separators)
  {
    if (auto skipped = SkipSeparator(strIt, last, sep); 
        skipped != last && skipped != strIt)
    {
      return SkipAnySeparator(skipped, last);
    }
    else if (skipped == last)
    {
      return skipped;
    }
  }

  return strIt;
}

template <typename It>
It StringSplitter::FindSeparator(It first, It last) const noexcept
{
  for(auto it = first; it != last; ++it)
  {
    if (IsAnySeparator(it, last))
    {
      return it;
    }
  }

  return last;
}

std::vector<std::string_view> StringSplitter::operator()(std::string_view str) const noexcept
{
  std::vector<std::string_view> result;
  auto first = std::begin(str);
  auto last = std::end(str);

  for (auto substr = FindSeparator(first, last), 
            previous = first; 
       previous != last; 
       substr = FindSeparator(substr, last))
  {
    if (auto dist = std::distance(previous, substr); dist != 0)
    {
      result.emplace_back(&*previous, dist);
    }

    if (substr != last)
    { 
      auto before = substr;
      substr = SkipAnySeparator(substr, last);
      
      // infinit cycle guard
      if (substr == before)
      {
        substr = last;
      }
    }

    previous = substr;
  }

  return result;
}

DefaultSplitter::DefaultSplitter()
  : StringSplitter { std::vector<std::string>{ ","s } }
{
}

PathSplitter::PathSplitter()
  : StringSplitter { std::vector<std::string>{ ";"s } }
{
}