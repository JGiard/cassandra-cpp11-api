/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#pragma once
#include <cassandra.h>
#include <memory>
#include "statement.h"
#include "future.h"
#include "result.h"

namespace Cassandra
{
  class Session
  {
  public:
    virtual ~Session();
    
    virtual std::shared_ptr<PreparedStatement> prepare(const std::string& query) = 0;
    
    virtual std::shared_ptr<BoundStatement> prepareBound(const std::string& query, std::size_t parameterCount) = 0;
    
    virtual std::shared_ptr<Result> execute(std::shared_ptr<BoundStatement> statement) = 0;
    
    virtual std::shared_ptr<Result> execute(const std::string& query) = 0;
    
    virtual const CassSchemaMeta& getKeyspaceSchema(const std::string& keyspace) = 0;
  };
  
  class SessionImpl : public Session
  {
  public:
    SessionImpl(CassCluster* cluster);
    
    SessionImpl(CassCluster* cluster, const std::string& keyspace);
    
    virtual ~SessionImpl();
    
    virtual std::shared_ptr<PreparedStatement> prepare(const std::string& query) override;
    
    virtual std::shared_ptr<BoundStatement> prepareBound(const std::string& query, std::size_t parameterCount) override;
    
    virtual std::shared_ptr<Result> execute(std::shared_ptr<BoundStatement> statement) override;
    
    virtual std::shared_ptr<Result> execute(const std::string& query) override;
    
    virtual const CassSchemaMeta& getKeyspaceSchema(const std::string& keyspace) override;
    
  private:
    CassSession* session;
    const CassSchema* schema;
  };
}
