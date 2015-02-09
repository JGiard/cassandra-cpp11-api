/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#pragma once
#include <cassandra.h>
#include <boost/noncopyable.hpp>

namespace Cassandra
{
  class Future : public boost::noncopyable
  {
  public:
    Future(CassFuture* future);
    
    ~Future();
    
    virtual bool isReady();
    
    virtual void wait();
    
    virtual void timedWait(int64_t timeout_us);
    
    virtual void check();
    
    virtual CassFuture* get();
    
  private:
    CassFuture* future;
  };
}
