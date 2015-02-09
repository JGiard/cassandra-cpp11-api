# cassandra-cpp11-api

I've put together a rudimentary cmake build system and extracted the current state of my c++11 api for https://github.com/datastax/cpp-driver.

It's not feature complete, I can think of the following not done :
 - cluster configuration
 - schema functions
 - ssl functions
 - statement configuration
 - binding by column name
 - retrieve collections from rows
 
There are (almost) no tests.
I was working alone on this so there might be a few things to review.
Here is was I can think of :
  - code style / headers ?
  - build system / header-only / integrated to c-driver ?

Some parts that may be requiring explanation :
  - collection binding : it's not possible to do a templated-bind method, this is the most fluent way I could think of
  - rows : used boost to achieve a standard iterator. Also ownership of CassResult* is managed independently of Result/Row so you don't need to keep the Result around for a Row to be valid.
  - statement binding : I choose to go with overloading instead of the bindXXX of java but I don't have a strong preference on this.
