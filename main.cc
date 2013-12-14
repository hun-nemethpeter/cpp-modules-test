//#define string aaa
#include <dummy.h>
#include <IdPool.hh>
//#undef string

int main()
{
  std::string str;
  std::vector<std::string> aa;
  IdPool<Dummy> dummyPool(100);

  std::cout << "Hello" << std::endl;

  return 0;
}
