/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#pragma once
#include <cassandra.h>
#include "row.h"
#include "future.h"
#include "internal.h"

namespace Cassandra
{
  class Rows
  {
  public:
    typedef RowIterator iterator;
    
    virtual ~Rows();
    
    virtual RowIterator begin() = 0;
    
    virtual RowIterator end() = 0;
    
    virtual std::size_t rowCount() = 0;
    
    virtual std::size_t columnCount() = 0;
  };
  
  class Result
  {
  public:
    virtual ~Result();
    
    virtual void wait() = 0;
    
    virtual void timedWait(int64_t timeout_us) = 0;
    
    virtual std::shared_ptr<Rows> rows() = 0;
  };
  
  class ResultImpl : public Result
  {
  public:
    ResultImpl(CassFuture* future);
    
    virtual ~ResultImpl();
    
    virtual void wait() override;
    
    virtual void timedWait(int64_t timeout_us) override;
    
    virtual std::shared_ptr<Rows> rows() override;
    
  private:
    Future future;
    bool hasResult = false;
    std::shared_ptr<CassResultPtr> result;
  };
  
  class RowsImpl : public Rows
  {
  public:
    RowsImpl(std::shared_ptr<CassResultPtr> result);
    
    virtual ~RowsImpl();
    
    virtual RowIterator begin() override;
    
    virtual RowIterator end() override;
    
    virtual std::size_t rowCount() override;
    
    virtual std::size_t columnCount() override;
    
  private:
    std::shared_ptr<CassResultPtr> result;
    CassIterator* rows;
  };
}
