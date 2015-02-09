/***************************************************************************
 * 
 * AFS
 *
 * (C) 2015 Antidot
 *
 ****************************************************************************/
#pragma once

#include <cxxtest/TestSuite.h>
#include <cluster.h>
#include <error.h>
#include <uuid.h>
#include <uuid/uuid.h>
#include <assert.h>

using namespace std;

namespace
{
  string generate_uuid()
  {
    uuid_t uuid ;
    char str[37] ; // for instance "8bc8a711-4b23-4628-85ed-7a07bc591fad"
    uuid_generate(uuid) ;
    uuid_unparse(uuid, str) ;

    return str ;
  }
  
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
      std::cerr << "future error" << std::endl;
      return false;
    }
    catch (std::runtime_error& e)
    {
      std::cerr << "error" << std::endl;
      return false;
    }
  }
}

class TestWrapper: public CxxTest::TestSuite
{
public:
  void test_basic1()
  {
    string keyspace = generateName();
    list<string> contactPoints = {"127.0.0.1"};
    std::shared_ptr<Cassandra::Cluster> cluster = make_shared<Cassandra::ClusterImpl>(contactPoints);
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
      uint64_t date = 1452175200000; // 2016-01-07 14:00:00
      bound->bind(5, uuidGen.fromTime(date));
      
      session->execute(bound)->wait();
    }
    {
      shared_ptr<Cassandra::BoundStatement> bound = insertStatement->bind();
      bound->bind(0, (int32_t)22);
      bound->bind(1, (int64_t)23);
      bound->bind(2, "bar");
      bound->bind(3, (double)22.22);
      bound->bind(4, false);
      uint64_t date = 1452178800000; // 2016-01-07 15:00:00
      bound->bind(5, uuidGen.fromTime(date));
      
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
      TS_ASSERT_EQUALS(Cassandra::UuidReader::toTime(row.getUuid("timevalue")), 1452175200000);
    }
    
    ++it;
    {
      Cassandra::Row& row = *it;
      TS_ASSERT_EQUALS(row.getInt("key"), 22);
      TS_ASSERT_EQUALS(row.getBigInt("ivalue"), 23);
      TS_ASSERT_EQUALS(row.getString("svalue"), "bar");
      TS_ASSERT_EQUALS(row.getDouble("dvalue"), 22.22);
      TS_ASSERT_EQUALS(row.getBool("bvalue"), false);
      TS_ASSERT_EQUALS(Cassandra::UuidReader::toTime(row.getUuid("timevalue")), 1452178800000);
    }
    ++it;
    TS_ASSERT_EQUALS(it, rows->end());

    return;
  }
};
