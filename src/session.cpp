/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#include "session.h"
#include "error.h"
#include "future.h"

namespace Cassandra
{
  Session::~Session()
  {

  }

  SessionImpl::SessionImpl(CassCluster* cluster)
  {
    session = cass_session_new();
    try
    {
      Future future(cass_session_connect(session, cluster));
      future.check();
    }
    catch (DriverException& e)
    {
      cass_session_free(session);
      throw;
    }
  }
  
  SessionImpl::SessionImpl(CassCluster* cluster, const std::string& keyspace)
  {
    session = cass_session_new();
    try
    {
      Future future(cass_session_connect_keyspace(session, cluster, keyspace.c_str()));
      future.check();
    }
    catch (DriverException& e)
    {
      cass_session_free(session);
      throw;
    }
  }

  SessionImpl::~SessionImpl()
  {
    Future future(cass_session_close(session));
    future.wait();
    cass_session_free(session);
  }
  
  std::shared_ptr<PreparedStatement> SessionImpl::prepare(const std::string& query)
  {
    return std::make_shared<PreparedStatementImpl>(session, query);
  }
  
  std::shared_ptr<BoundStatement> SessionImpl::prepareBound(const std::string& query, std::size_t parameterCount)
  {
    return std::make_shared<BoundStatementImpl>(query, parameterCount);
  }
  
  std::shared_ptr<Result> SessionImpl::execute(std::shared_ptr<Cassandra::BoundStatement> statement)
  {
    return std::make_shared<ResultImpl>(cass_session_execute(session, statement->get()));
  }
  
  std::shared_ptr<Result> SessionImpl::execute(const std::string& query)
  {
    return execute(prepareBound(query, 0));
  }
  
  const CassSchemaMeta& SessionImpl::getKeyspaceSchema(const std::string& keyspace)
  {
    schema = cass_session_get_schema(session);
    const CassSchemaMeta* meta = cass_schema_get_keyspace(schema, keyspace.c_str());
    if (meta == nullptr)
    {
      throw NoKeyspaceException(keyspace);
    }
    return *meta;
  }
}
