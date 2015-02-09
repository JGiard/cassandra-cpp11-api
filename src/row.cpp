/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#include "row.h"
#include "error.h"

namespace Cassandra
{
  Row::~Row()
  {

  }

  RowImpl::RowImpl(const CassRow* row)
    : row(row)
  {

  }
  
  int32_t RowImpl::getInt(const std::string& column)
  {
    int32_t value;
    RCcheck(cass_value_get_int32(getValue(column), &value));
    return value;
  }
  
  int64_t RowImpl::getBigInt(const std::string& column)
  {
    int64_t value;
    RCcheck(cass_value_get_int64(getValue(column), &value));
    return value;
  }

  float RowImpl::getFloat(const std::string& column)
  {
    float value;
    RCcheck(cass_value_get_float(getValue(column), &value));
    return value;
  }

  double RowImpl::getDouble(const std::string& column)
  {
    double value;
    RCcheck(cass_value_get_double(getValue(column), &value));
    return value;
  }

  bool RowImpl::getBool(const std::string& column)
  {
    cass_bool_t value;
    RCcheck(cass_value_get_bool(getValue(column), &value));
    return value == cass_true ? true : false;
  }

  std::string RowImpl::getString(const std::string& column)
  {
    CassString value;
    RCcheck(cass_value_get_string(getValue(column), &value));
    return std::string(value.data, value.length);
  }

  CassUuid RowImpl::getUuid(const std::string& column)
  {
    CassUuid value;
    RCcheck(cass_value_get_uuid(getValue(column), &value));
    return value;
  }
  
  void RowImpl::getBytes(const std::string& column, CassBytes* bytes)
  {
    RCcheck(cass_value_get_bytes(getValue(column), bytes));
  }
  
  const CassValue* RowImpl::getValue(const std::string& column)
  {
    return cass_row_get_column_by_name(row, column.c_str());
  }

  RowIterator::RowIterator(CassIterator* rows, bool isEnd)
    : rows(rows), isEnd(isEnd)
  {

  }

  RowIterator::~RowIterator()
  {

  }

  void RowIterator::increment()
  {
    if (!cass_iterator_next(rows))
    {
      isEnd = true;
      currentRow.reset();
    }
    else
    {
      currentRow = std::make_shared<RowImpl>(cass_iterator_get_row(rows));
    }
  }

  Row& RowIterator::dereference() const
  {
    return *currentRow;
  }

  bool RowIterator::equal(const RowIterator& other) const
  {
    if (isEnd && other.isEnd)
    {
      return true;
    }
    else
    {
      return currentRow.get() == other.currentRow.get();
    }
  }
}
