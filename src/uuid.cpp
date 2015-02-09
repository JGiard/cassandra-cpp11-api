/***************************************************************************
 * 
 * AFS
 *
 * (C) 2014 Antidot
 *
 ****************************************************************************/
#include "uuid.h"

namespace Cassandra
{
  UuidGenerator::UuidGenerator()
  {
    uuidGenerator = cass_uuid_gen_new();
  }

  UuidGenerator::~UuidGenerator()
  {
    cass_uuid_gen_free(uuidGenerator);
  }
  
  CassUuid UuidGenerator::fromNow()
  {
    CassUuid uuid;
    cass_uuid_gen_time(uuidGenerator, &uuid);
    return uuid;
  }

  CassUuid UuidGenerator::fromTime(uint64_t msTimestamp)
  {
    CassUuid uuid;
    cass_uuid_gen_from_time(uuidGenerator, msTimestamp, &uuid);
    return uuid;
  }

  CassUuid UuidGenerator::random()
  {
    CassUuid uuid;
    cass_uuid_gen_random(uuidGenerator, &uuid);
    return uuid;
  }
  
  uint64_t UuidReader::toTime(CassUuid uuid)
  {
    return cass_uuid_timestamp(uuid);
  }
}
