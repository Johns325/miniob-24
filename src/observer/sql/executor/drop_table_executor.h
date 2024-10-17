#pragma once

class SQLStageEvent;
#include "common/rc.h"

class DropTableExecutor {
 public:
  DropTableExecutor() = default;
  ~DropTableExecutor() = default;
  RC execute(SQLStageEvent *event);
};