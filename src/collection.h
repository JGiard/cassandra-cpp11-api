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
#include <list>
#include <set>
#include <map>
#include <stdint.h>

namespace Cassandra
{
  class Collection
  {
  public:
    Collection(CassCollectionType type, std::size_t size);
    
    ~Collection();
    
    const CassCollection* getCollection() const;
    
    void append(int32_t value);
    
    void append(int64_t value);
    
    void append(float value);
    
    void append(double value);
    
    void append(bool value);
    
    void append(const std::string& value);
    
    void append(CassBytes value);
    
    void append(CassUuid value);
    
  private:
    CassCollection* collection;
  };
  
  template<class T>
  std::shared_ptr<Collection> buildListCollection(const std::list<T>& value)
  {
    std::shared_ptr<Collection> collection = std::make_shared<Collection>(CASS_COLLECTION_TYPE_LIST, value.size());
    for (const T& item : value)
    {
      collection->append(item);
    }
    return collection;
  }
  
  template<class T>
  std::shared_ptr<Collection> buildSetCollection(const std::set<T>& value)
  {
    std::shared_ptr<Collection> collection = std::make_shared<Collection>(CASS_COLLECTION_TYPE_SET, value.size());
    for (const T& item : value)
    {
      collection->append(item);
    }
    return collection;
  }
  
  template<class K, class V>
  std::shared_ptr<Collection> buildMapCollection(const std::map<K, V>& value)
  {
    std::shared_ptr<Collection> collection = std::make_shared<Collection>(CASS_COLLECTION_TYPE_MAP, value.size());
    for (const std::pair<K, V>& entry : value)
    {
      collection->append(entry.first);
      collection->append(entry.second);
    }
    return collection;
  }
}
