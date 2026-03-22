#ifndef LINKEDLIST_STD_LIST_HPP
#define LINKEDLIST_STD_LIST_HPP

#include <Tools/Types.hpp>

#include <list>

template <typename T>
void Test_std_list(const vec<T> Vector_Data) {
    std::list<T> LL;
    for(auto& i : Vector_Data) {
        LL.push_back(i);
    }
    const idx n = LL.size();

    fmt::println("\nstd::list data");
    fmt::println("Pointer address:      {}", fmt::ptr(&LL));
    fmt::println("first element         {} at {}",  LL.front(), fmt::ptr(LL.front()));
    fmt::println("second element        {} at {}",  LL.front(), fmt::ptr(LL.begin()+1));
    fmt::println("last element          {} at {}",  LL.back(), fmt::ptr(LL.back()));
    fmt::println("Elements:             {}", n);
    fmt::println("Size:                 {} bytes\n", sizeof(T)*n);

    fmt::println("[{}]", fmt::join(LL, ", "));

    // Insert 314.271 di index 2
    auto it = LL.begin();
    std::advance(it, 2);
    LL.insert(it, 314.271);

    fmt::println("[{}]", fmt::join(LL, ", "));

    // Sortir
    LL.sort();
    fmt::println("[{}]", fmt::join(LL, ", "));

    std::list<T> LL2;
    vec Data2 = Vector_Data;
    for(auto& i : Data2) {
        i += 3.14;
    }

    // Gabung
    LL.merge(LL2);
    fmt::println("[{}]", fmt::join(LL, ", "));
}

#endif //LINKEDLIST_STD_LIST_HPP