/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#include "cluster.h"
#include "error.h"
#include <iterator>
#include <boost/algorithm/string/join.hpp>

namespace Cassandra
{
  Cluster::~Cluster()
  {

  }

  ClusterImpl::ClusterImpl(const std::list<std::string>& contactPoints)
  {
    cluster = cass_cluster_new();
    try
    {
      init(contactPoints);
    }
    catch (DriverException& e)
    {
      cass_cluster_free(cluster);
      throw;
    }
  }

  ClusterImpl::~ClusterImpl()
  {
    cass_cluster_free(cluster);
  }
  
  void ClusterImpl::init(const std::list<std::string>& contactPoints)
  {
    std::string contactPointsString = boost::algorithm::join(contactPoints, ", ");
    RCcheck(cass_cluster_set_contact_points(cluster, contactPointsString.c_str()));
    cass_cluster_set_queue_size_io(cluster, 32768);
    cass_cluster_set_queue_size_event(cluster, 32768);
    cass_cluster_set_num_threads_io(cluster, 8);
    cass_cluster_set_core_connections_per_host(cluster, 2);
    cass_cluster_set_max_connections_per_host(cluster, 8);
  }
  
  std::shared_ptr<Session> ClusterImpl::connect()
  {
    return std::make_shared<SessionImpl>(cluster);
  }

  std::shared_ptr<Session> ClusterImpl::connect(const std::string& keyspace)
  {
    return std::make_shared<SessionImpl>(cluster, keyspace);
  }
}
