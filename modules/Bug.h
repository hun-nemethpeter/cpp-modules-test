template <typename T>
class Bug 
{
public:
  static void foo()
  {
    auto aa = [](T*) { };
  }
};
