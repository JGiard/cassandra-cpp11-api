/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#pragma once

#include <memory>
#include <string>
#include <list>
#include <cassandra.h>
#include "session.h"

namespace Cassandra
{
  class Cluster
  {
  public:
    virtual ~Cluster();
    
    virtual std::shared_ptr<Session> connect() = 0;
    
    virtual std::shared_ptr<Session> connect(const std::string& keyspace) = 0;
  };
  
  class ClusterImpl : public Cluster
  {
  public:
    ClusterImpl(const std::list<std::string>& contactPoints);
    
    virtual ~ClusterImpl();
    
    virtual std::shared_ptr<Session> connect() override;
    
    virtual std::shared_ptr<Session> connect(const std::string& keyspace) override;
    
  private:
    CassCluster* cluster;
    
    void init(const std::list<std::string>& contactPoints);
  };
}
