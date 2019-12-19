#ifndef D_MY_ALLOCATOR_H_
#define D_MY_ALLOCATOR_H_ 1

#include <cstdlib>
#include <cstdint>

#include <exception>
#include <iostream>
#include <type_traits>

#include "vector.hpp"


namespace all {
  template<class T, size_t ALLOC_SIZE>
  struct my_allocator {
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using is_always_equal = std::false_type;

    template<class U>
    struct rebind {
      using other = my_allocator<U, ALLOC_SIZE>;
    };

    my_allocator():
      memory_pool_begin(new char[ALLOC_SIZE]),
      memory_pool_end(memory_pool_begin + ALLOC_SIZE),
      memory_pool_tail(memory_pool_begin)
    {};

    my_allocator(const my_allocator&) = delete;
    my_allocator(my_allocator&&) = delete;

    ~my_allocator() noexcept {
      delete[] memory_pool_begin;
    }

    T* allocate(std::size_t n);
    void deallocate(T* ptr, std::size_t n);

  private:
    char* memory_pool_begin;
    char* memory_pool_end;
    char* memory_pool_tail;
    containers::vector<char*> free_blocks_;
  };

  template<class T, size_t ALLOC_SIZE>
  T* my_allocator<T, ALLOC_SIZE>::allocate(std::size_t n) {
    if(n != 1){
      throw std::logic_error("This allocator can't allocate arrays");
    }
    if(size_t(memory_pool_end - memory_pool_tail) < sizeof(T)){
      if(free_blocks_.GetSize()){
        auto it = free_blocks_.begin();
        char* ptr = *it;
        free_blocks_.erase(0);
        return reinterpret_cast<T*>(ptr);
      }
      throw std::bad_alloc();
    }
    T* result = reinterpret_cast<T*>(memory_pool_tail);
    memory_pool_tail += sizeof(T);
    return result;
  }

  template<class T, size_t ALLOC_SIZE>
  void my_allocator<T, ALLOC_SIZE>::deallocate(T* ptr, std::size_t n) {
    if(n != 1){
      throw std::logic_error("This allocator can't allocate arrays");
    }
    if(ptr == nullptr){
      return;
    }
    free_blocks_.PushBack(reinterpret_cast<char*>(ptr));
  }
}

#endif // D_MY_ALLOCATOR_H_