

#include <chrono>
#include <type_traits>

template <typename TU1,
          class = typename std::enable_if<std::is_same<TU1, std::chrono::hours>::value ||
                                          std::is_same<TU1, std::chrono::minutes>::value ||
                                          std::is_same<TU1, std::chrono::seconds>::value ||
                                          std::is_same<TU1, std::chrono::milliseconds>::value ||
                                          std::is_same<TU1, std::chrono::microseconds>::value ||
                                          std::is_same<TU1, std::chrono::nanoseconds>::value>::type,
          typename TU2,
          class = typename std::enable_if<std::is_same<TU2, std::chrono::time_point<std::chrono::system_clock>>::value ||
                                          std::is_same<TU2, std::chrono::time_point<std::chrono::steady_clock>>::value>::type
         >
inline long timediff(TU2 t1, TU2 t2)
{
    return (long)std::chrono::duration_cast<TU1>(t2 - t1).count();
}
