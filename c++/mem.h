
#include <memory>

// for c++ 11 to use make_unque
namespace test {

template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
   return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

} // namespace test
