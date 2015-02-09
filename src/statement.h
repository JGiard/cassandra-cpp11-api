/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#pragma once
#include <cassandra.h>
#include <string>
#include <memory>
#include "collection.h"

namespace Cassandra
{
  class BoundStatement
  {
  public:
    virtual ~BoundStatement();
    
    virtual void bindNull(std::size_t index) = 0;
    
    virtual void bind(std::size_t index, int32_t value) = 0;
    
    virtual void bind(std::size_t index, int64_t value) = 0;
    
    virtual void bind(std::size_t index, float value) = 0;
    
    virtual void bind(std::size_t index, double value) = 0;
    
    virtual void bind(std::size_t index, bool value) = 0;
    
    virtual void bind(std::size_t index, const char* value) = 0;
    
    virtual void bind(std::size_t index, const std::string& value) = 0;
    
    virtual void bind(std::size_t index, CassUuid value) = 0;
    
    virtual void bind(std::size_t index, CassBytes value) = 0;
    
    virtual void bind(std::size_t index, std::shared_ptr<Collection> collection) = 0;
    
    virtual CassStatement* get() = 0;
  };
  
  class PreparedStatement
  {
  public:
    virtual ~PreparedStatement();
    
    virtual std::shared_ptr<BoundStatement> bind() = 0;
  };
  
  class BoundStatementImpl : public BoundStatement
  {
  public:
    BoundStatementImpl(const CassPrepared* preparedStatement);
    
    BoundStatementImpl(const std::string& query, std::size_t parameterCount);
    
    virtual ~BoundStatementImpl();
    
    virtual void bindNull(std::size_t index);
    
    virtual void bind(std::size_t index, int32_t value) override;
    
    virtual void bind(std::size_t index, int64_t value) override;
    
    virtual void bind(std::size_t index, float value) override;
    
    virtual void bind(std::size_t index, double value) override;
    
    virtual void bind(std::size_t index, bool value) override;
    
    virtual void bind(std::size_t index, const char* value) override;
    
    virtual void bind(std::size_t index, const std::string& value) override;
    
    virtual void bind(std::size_t index, CassUuid value) override;
    
    virtual void bind(std::size_t index, CassBytes value) override;
    
    virtual void bind(std::size_t index, std::shared_ptr<Collection> collection) override;
    
    virtual CassStatement* get() override;
    
  private:
    CassStatement* statement;
  };
  
  class PreparedStatementImpl : public PreparedStatement
  {
  public:
    PreparedStatementImpl(CassSession* session, const std::string& query);
    
    virtual ~PreparedStatementImpl();
    
    virtual std::shared_ptr<BoundStatement> bind() override;
  private:
    const CassPrepared* prepared;
  };
}
