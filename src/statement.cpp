/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#include "statement.h"
#include "future.h"

namespace Cassandra
{
  BoundStatement::~BoundStatement()
  {

  }
  
  BoundStatementImpl::BoundStatementImpl(const CassPrepared* preparedStatement)
  {
    statement = cass_prepared_bind(preparedStatement);
  }
  
  BoundStatementImpl::BoundStatementImpl(const std::string& query, std::size_t parameterCount)
  {
    statement = cass_statement_new(cass_string_init(query.c_str()), parameterCount);
  }
  
  BoundStatementImpl::~BoundStatementImpl()
  {
    cass_statement_free(statement);
  }
  
  void BoundStatementImpl::bindNull(std::size_t index)
  {
    cass_statement_bind_null(statement, index);
  }
  
  void BoundStatementImpl::bind(std::size_t index, int32_t value)
  {
    cass_statement_bind_int32(statement, index, value);
  }
  
  void BoundStatementImpl::bind(std::size_t index, int64_t value)
  {
    cass_statement_bind_int64(statement, index, value);
  }

  void BoundStatementImpl::bind(std::size_t index, float value)
  {
    cass_statement_bind_float(statement, index, value);
  }

  void BoundStatementImpl::bind(std::size_t index, double value)
  {
    cass_statement_bind_double(statement, index, value);
  }

  void BoundStatementImpl::bind(std::size_t index, bool value)
  {
    cass_statement_bind_bool(statement, index, value ? cass_true : cass_false);
  }
  
  void BoundStatementImpl::bind(std::size_t index, const char* value)
  {
    cass_statement_bind_string(statement, index, cass_string_init(value));
  }
  
  void BoundStatementImpl::bind(std::size_t index, const std::string& value)
  {
    bind(index, value.c_str());
  }
  
  void BoundStatementImpl::bind(std::size_t index, CassUuid value)
  {
    cass_statement_bind_uuid(statement, index, value);
  }
  
  void BoundStatementImpl::bind(std::size_t index, CassBytes value)
  {
    cass_statement_bind_bytes(statement, index, value);
  }
  
  void BoundStatementImpl::bind(std::size_t index, std::shared_ptr<Collection> collection)
  {
    cass_statement_bind_collection(statement, index, collection->getCollection());
  }
  
  CassStatement* BoundStatementImpl::get()
  {
    return statement;
  }

  PreparedStatement::~PreparedStatement()
  {

  }

  PreparedStatementImpl::PreparedStatementImpl(CassSession* session, const std::string& query)
  {
    Future future(cass_session_prepare(session, cass_string_init(query.c_str())));
    future.wait();
    prepared = cass_future_get_prepared(future.get());
  }
  
  PreparedStatementImpl::~PreparedStatementImpl()
  {
    cass_prepared_free(prepared);
  }

  std::shared_ptr<BoundStatement> PreparedStatementImpl::bind()
  {
    return std::make_shared<BoundStatementImpl>(prepared);
  }
}
