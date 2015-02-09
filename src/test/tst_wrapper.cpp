/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#include "tst_wrapper.h"
#include <COMMON/CASSANDRA/CPP_WRAPPER/error.h>
#include <COMMON/CASSANDRA/CPP_WRAPPER/uuid.h>
#include <COMMON/CHANNEL/channel.h>
#include <COMMON/BASIC/basic.h>

TestWrapper::TestWrapper()
{
  try
  {
    list<string> contactPoints = {"127.0.0.1"};
    cluster = make_shared<Cassandra::ClusterImpl>(contactPoints);
    cluster->connect("system");
    enabled = true;
  }
  catch (Cassandra::DriverException& e)
  {
    enabled = false;
  }
}

namespace
{
  string generateName()
  {
    string name = "ks_" + generate_uuid();
    string::size_type pos = name.find("-");
    assert(pos != string::npos);
    name = name.substr(0, pos);
    return name;
  }
  
  bool test()
  {
    try
    {
      list<string> contactPoints = {"localhost"};
      auto cluster = make_shared<Cassandra::ClusterImpl>(contactPoints);
      cluster->connect("system");
      //cluster.reset();
     return false;
    }
    catch (Cassandra::DriverException& e)
    {
      LOG(ERROR, 1) << "future error";
      return false;
    }
    catch (std::runtime_error& e)
    {
      LOG(ERROR, 1) << "error";
      return false;
    }
  }
}

void TestWrapper::test_basic1()
{
  if (!enabled) return;
  try
  {
    string keyspace = generateName();
    shared_ptr<Cassandra::Session> session = cluster->connect();
    session->execute("CREATE KEYSPACE " + keyspace + " WITH replication={'class': 'SimpleStrategy', 'replication_factor': '1'}")->wait();
    session->execute("USE " + keyspace)->wait();
    Cassandra::UuidGenerator uuidGen;
    
    session->execute("CREATE TABLE content("
                     "key int,"
                     "ivalue bigint,"
                     "svalue text,"
                     "dvalue double,"
                     "bvalue boolean,"
                     "timevalue timeuuid,"
                     "PRIMARY KEY (key))")->wait();

    shared_ptr<Cassandra::PreparedStatement> insertStatement = session->prepare(
          "INSERT INTO content(key, ivalue, svalue, dvalue, bvalue, timevalue) "
          "VALUES(?,?,?,?,?,?)");
    
    {
      shared_ptr<Cassandra::BoundStatement> bound = insertStatement->bind();
      bound->bind(0, (int32_t)42);
      bound->bind(1, (int64_t)43);
      bound->bind(2, "foo");
      bound->bind(3, (double)42.42);
      bound->bind(4, true);
      N_Mule::T_date date(2016, 1, 7, 14, 0, 0);
      bound->bind(5, uuidGen.fromTime(date.get_udate()));
      
      session->execute(bound)->wait();
    }
    {
      shared_ptr<Cassandra::BoundStatement> bound = insertStatement->bind();
      bound->bind(0, (int32_t)22);
      bound->bind(1, (int64_t)23);
      bound->bind(2, "bar");
      bound->bind(3, (double)22.22);
      bound->bind(4, false);
      N_Mule::T_date date(2016, 1, 7, 15, 0, 0);
      bound->bind(5, uuidGen.fromTime(date.get_udate()));
      
      session->execute(bound)->wait();
    }
    
    shared_ptr<Cassandra::Rows> rows = session->execute("SELECT key, ivalue, svalue, dvalue, bvalue, timevalue FROM content")->rows();
    TS_ASSERT_EQUALS(rows->rowCount(), 2);
    Cassandra::Rows::iterator it = rows->begin();
    {
      Cassandra::Row& row = *it;
      TS_ASSERT_EQUALS(row.getInt("key"), 42);
      TS_ASSERT_EQUALS(row.getBigInt("ivalue"), 43);
      TS_ASSERT_EQUALS(row.getString("svalue"), "foo");
      TS_ASSERT_EQUALS(row.getDouble("dvalue"), 42.42);
      TS_ASSERT_EQUALS(row.getBool("bvalue"), true);
      TS_ASSERT_EQUALS(Cassandra::UuidReader::toTime(row.getUuid("timevalue")), N_Mule::T_date(2016, 1, 7, 14, 0, 0).get_udate());
    }
    
    ++it;
    {
      Cassandra::Row& row = *it;
      TS_ASSERT_EQUALS(row.getInt("key"), 22);
      TS_ASSERT_EQUALS(row.getBigInt("ivalue"), 23);
      TS_ASSERT_EQUALS(row.getString("svalue"), "bar");
      TS_ASSERT_EQUALS(row.getDouble("dvalue"), 22.22);
      TS_ASSERT_EQUALS(row.getBool("bvalue"), false);
      TS_ASSERT_EQUALS(Cassandra::UuidReader::toTime(row.getUuid("timevalue")), N_Mule::T_date(2016, 1, 7, 15, 0, 0).get_udate());
    }
    ++it;
    TS_ASSERT_EQUALS(it, rows->end());

    return;
  }
  LOG_CATCH_AND_DISPLAY("TestWrapper::test_basic1(", ERROR, 1);
  TS_FAIL("TestWrapper::test_basic1( error");
}
