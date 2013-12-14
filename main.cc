//#define string aaa
#include <dummy.h>
#include <IdPool.hh>
//#undef string

class Session : public IdResourceBase<Session>
{
public:
  Session(unsigned id) : IdResourceBase<Session>(id)
  {
     std::cout << "Session ctor" << std::endl;
  }

  ~Session()
  {
     std::cout << "Session dtor" << std::endl;
  }
};

class App
{
public:
  App()
    : sessionPool(100)
  {
    std::cout << "Session pool: " << sessionPool.getUsedCount() << std::endl;
    auto session = Session::create(sessionPool);
//    auto session = Session::createUnique(sessionPool);
    std::cout << "Hello session: " << session->getId() << std::endl;
    std::cout << "Session pool: " << sessionPool.getUsedCount() << std::endl;
  }

private:
  std::string str;
  std::vector<std::string> aa;
  IdPool<Session> sessionPool;
};

int main()
{
  App app;

  return 0;
}
