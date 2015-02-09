/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#include "error.h"

namespace Cassandra
{
  DriverException::DriverException(CassError errorCode)
    : DriverException(errorCode, "Cassandra driver error")
  {

  }
  
  DriverException::DriverException(CassError errorCode, const std::string& errorMessage)
    : std::runtime_error(errorMessage), errorCode(errorCode)
  {

  }
  
  CassError DriverException::getErrorCode() const
  {
    return errorCode;
  }
  
  TimeoutException::TimeoutException()
    : runtime_error("Timeout while waiting for a future")
  {

  }
  
  NoKeyspaceException::NoKeyspaceException(const std::string& keyspace)
    : runtime_error("the keyspace " + keyspace + " does not exists")
  {

  }
  
  RCcheck::RCcheck(CassError rc)
  {
    if (rc != CASS_OK)
    {
      throw DriverException(rc);
    }
  }
}