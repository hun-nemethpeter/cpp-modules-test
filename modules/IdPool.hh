#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>
#include <utility>

template<typename T>
class IdPool
{
public:
  IdPool(unsigned size) : freeIds(size), buffer(size * sizeof(T))
  {
    for (unsigned i = 0; i < size; i++)
      freeIds[i] = i;
  }

  template<typename... Args>
  T* alloc(Args&&... args)
  {
    if (freeIdIndex > freeIds.size() - 1)
      throw std::runtime_error("IdPool is full!");

    unsigned id = freeIds[freeIdIndex++];
    void* ptr = &buffer[freeIds[id] * sizeof(T)];

    new (ptr)T(id, std::forward<Args>(args)...);

    return (T*)ptr;
  }

  void free(T* obj)
  {
    if (freeIdIndex == 0)
      throw std::runtime_error("Logic error, pool is empty!");

    obj->~T();
    freeIds[--freeIdIndex] = obj->id;
  }

  unsigned getUsedCount() const
  { return freeIdIndex; }

  unsigned getCapacity() const
  { return freeIds.size(); }

private:
  std::vector<unsigned> freeIds;
  unsigned freeIdIndex = 0;
  std::vector<char> buffer;
};

template <typename T>
class IdResourceBase
{
public:
  template<typename... Args>
  static T* create(IdPool<T>& pool, Args&&... args)
  { return pool.alloc(std::forward<Args>(args)...); }

  typedef std::unique_ptr<T, std::function<void (T*)>> Ptr;

  template<typename... Args>
  static Ptr createUnique(IdPool<T>& pool, Args&&... args)
  {
    T* item = pool.alloc(std::forward<Args>(args)...);
    return Ptr(item, [&pool](T* item) { pool.free(item); });
  }

  unsigned getId() const
  { return id; }

protected:
  IdResourceBase(unsigned id) : id(id)
  { }

  friend class IdPool<T>;
  unsigned id;
};
