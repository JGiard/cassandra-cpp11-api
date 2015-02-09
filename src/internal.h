/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#pragma once
#include <cassandra.h>

namespace Cassandra
{
  class CassResultPtr
  {
  public:
    CassResultPtr(const CassResult* result);
    
    ~CassResultPtr();
    
    const CassResult* get();
    
  private:
    const CassResult* result;
  };
}
