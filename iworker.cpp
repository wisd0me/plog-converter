//  2006-2008 (c) Viva64.com Team
//  2008-2020 (c) OOO "Program Verification Systems"
//  2020-2023 (c) PVS-Studio LLC

#include "iworker.h"

namespace PlogConverter
{

IWorker::~IWorker() = default;

[[nodiscard]]
bool IWorker::IsErrorHappend() const noexcept
{
  return false;
}
}
