/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#pragma once
#include <stdexcept>
#include <cassandra.h>

namespace Cassandra
{
  class DriverException : public std::runtime_error
  {
  public:
    DriverException(CassError errorCode);
    
    DriverException(CassError errorCode, const std::string& errorMessage);
    
    CassError getErrorCode() const;
    
  private:
    CassError errorCode;
  };
  
  class TimeoutException : public std::runtime_error
  {
  public:
    TimeoutException();
  };
  
  class NoKeyspaceException : public std::runtime_error
  {
  public:
    NoKeyspaceException(const std::string& keyspace);
  };
  
  class RCcheck
  {
  public:
    RCcheck(CassError rc);
  };
}
