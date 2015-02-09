/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#include "future.h"
#include "error.h"

namespace Cassandra
{
  Future::Future(CassFuture* future)
    : future(future)
  {

  }
  
  Future::~Future()
  {
    cass_future_free(future);
  }
  
  bool Future::isReady()
  {
    return cass_future_ready(future) == cass_true ? true : false;
  }
  
  void Future::wait()
  {
    cass_future_wait(future);
  }
  
  void Future::timedWait(int64_t timeout_us)
  {
    if (!cass_future_wait_timed(future, timeout_us))
    {
      throw TimeoutException();
    }
  }

  void Future::check()
  {
    wait();
    CassError rc = cass_future_error_code(future);
    if (rc != CASS_OK)
    {
      CassString message = cass_future_error_message(future);
      throw DriverException(rc, std::string(message.data, message.length));
    }
  }
  
  CassFuture* Future::get()
  {
    return future;
  }
}
