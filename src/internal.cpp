/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#include "internal.h"

namespace Cassandra
{
  CassResultPtr::CassResultPtr(const CassResult* result)
    : result(result)
  {

  }

  CassResultPtr::~CassResultPtr()
  {
    cass_result_free(result);
  }

  const CassResult* CassResultPtr::get()
  {
    return result;
  }
}
