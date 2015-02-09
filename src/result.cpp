/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#include "result.h"

namespace Cassandra
{
  Result::~Result()
  {

  }
  
  Rows::~Rows()
  {

  }

  ResultImpl::ResultImpl(CassFuture* future)
    : future(future)
  {
    
  }

  ResultImpl::~ResultImpl()
  {
    
  }
  
  void ResultImpl::wait()
  {
    if (result.get() == 0)
    {
      future.check();
      result = std::make_shared<CassResultPtr>(cass_future_get_result(future.get()));
    }
  }
 
  void ResultImpl::timedWait(int64_t timeout_us)
  {
    if (result.get() == 0)
    {
      future.timedWait(timeout_us);
      future.check();
      result = std::make_shared<CassResultPtr>(cass_future_get_result(future.get()));
    }
  }
  
  std::shared_ptr<Rows> ResultImpl::rows()
  {
    wait();
    return std::make_shared<RowsImpl>(result);
  }
  
  RowsImpl::RowsImpl(std::shared_ptr<CassResultPtr> result)
    : result(result)
  {
    rows = cass_iterator_from_result(result->get());
  }

  RowsImpl::~RowsImpl()
  {
    cass_iterator_free(rows);
  }

  RowIterator RowsImpl::begin()
  {
    RowIterator iterator = RowIterator(rows);
    ++iterator;
    return iterator;
  }

  RowIterator RowsImpl::end()
  {
    return RowIterator(rows, true);
  }
  
  size_t RowsImpl::rowCount()
  {
    return cass_result_row_count(result->get());
  }

  size_t RowsImpl::columnCount()
  {
    return cass_result_column_count(result->get());
  }
}
