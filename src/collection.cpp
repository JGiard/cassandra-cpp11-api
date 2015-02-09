/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#include "collection.h"
#include <string>

namespace Cassandra
{
  Collection::Collection(CassCollectionType type, std::size_t size)
  {
    collection = cass_collection_new(type, size);
  }
  
  Collection::~Collection()
  {
    cass_collection_free(collection);
  }
  
  void Collection::append(int32_t value)
  {
    cass_collection_append_int32(collection, value);
  }
  
  void Collection::append(int64_t value)
  {
    cass_collection_append_int64(collection, value);
  }

  void Collection::append(float value)
  {
    cass_collection_append_float(collection, value);
  }

  void Collection::append(double value)
  {
    cass_collection_append_double(collection, value);
  }

  void Collection::append(bool value)
  {
    cass_collection_append_bool(collection, value ? cass_true : cass_false);
  }

  void Collection::append(const std::string& value)
  {
    cass_collection_append_string(collection, cass_string_init(value.c_str()));
  }

  void Collection::append(CassBytes value)
  {
    cass_collection_append_bytes(collection, value);
  }

  void Collection::append(CassUuid value)
  {
    cass_collection_append_uuid(collection, value);
  }

  const CassCollection* Collection::getCollection() const
  {
    return collection;
  }
}
