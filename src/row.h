/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#pragma once
#include <boost/iterator/iterator_facade.hpp>
#include <cassandra.h>
#include <memory>

namespace Cassandra
{
  class Row
  {
  public:
    virtual ~Row();
    
    virtual int32_t getInt(const std::string& column) = 0;
    
    virtual int64_t getBigInt(const std::string& column) = 0;
    
    virtual float getFloat(const std::string& column) = 0;
    
    virtual double getDouble(const std::string& column) = 0;
    
    virtual bool getBool(const std::string& column) = 0;
    
    virtual std::string getString(const std::string& column) = 0;
    
    virtual CassUuid getUuid(const std::string& column) = 0;
    
    virtual void getBytes(const std::string& column, CassBytes* bytes) = 0;
  };
  
  class RowImpl : public Row
  {
  public:
    RowImpl(const CassRow* row);
    
    virtual int32_t getInt(const std::string& column) override;
    
    virtual int64_t getBigInt(const std::string& column) override;
    
    virtual float getFloat(const std::string& column) override;
    
    virtual double getDouble(const std::string& column) override;
    
    virtual bool getBool(const std::string& column) override;
    
    virtual std::string getString(const std::string& column) override;
    
    virtual CassUuid getUuid(const std::string& column) override;
    
    virtual void getBytes(const std::string& column, CassBytes* bytes) override;
    
  private:
    const CassRow* row;
    
    const CassValue* getValue(const std::string& column);
  };
  
  class RowIterator : public boost::iterator_facade<RowIterator, Row, boost::single_pass_traversal_tag>
  {
  public:
    RowIterator(CassIterator* rows, bool isEnd = false);

    virtual ~RowIterator();

  private:
    friend class boost::iterator_core_access;
    
    virtual void increment();
    
    bool equal(const RowIterator& other) const;
    
    Row& dereference() const;
    
    CassIterator* rows;
    bool isEnd;
    std::shared_ptr<Row> currentRow;
  };
}
