#include <boost/atomic.hpp>
#include <boost/thread/mutex.hpp>

class Database
{
  static Database& instance()
  {
    Database* db = instance.load(boost::memory_order_consume);
    if(!db)
    {
      boost::mutex::scoped_lock lock(mtx);
      db = instance.load(boost::memory_order_consume);
      if(!db)
      {
        db = new Database();
        instance.store(db, boost::memory_order_release);
      }
    }
  }
private:
  static boost::atomic<Database*> instance;
  static boost::mutex mtx;
};