/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#pragma once
#include <cassandra.h>
#include <stdint.h>

namespace Cassandra
{
  class UuidGenerator
  {
  public:
    UuidGenerator();
    
    virtual ~UuidGenerator();
    
    CassUuid fromNow();
    
    CassUuid fromTime(uint64_t msTimestamp);
    
    CassUuid random();
    
  private:
    CassUuidGen* uuidGenerator;
  };
  
  class UuidReader
  {
  public:
    static uint64_t toTime(CassUuid uuid);
  };
}
