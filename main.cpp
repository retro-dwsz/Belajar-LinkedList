#include <fmt/format.h>
#include <fmt/ranges.h>

#include <Tools/Random.hpp>
#include <Tools/Clock.hpp>
#include <Tools/Types.hpp>

#include "LinkedLists.hpp"

#define GetArraySize(array) sizeof(array)/sizeof(array[0])

void Test_Vector(const vec<f64>& Data_Vector) {
    fmt::println("Vector:                {}\n", Data_Vector);
    fmt::println("Vector data");
    fmt::println("Object address:        {}", fmt::ptr(&Data_Vector));
    fmt::println("first element address: {}", fmt::ptr(&Data_Vector.front()));
    fmt::println("last  element address: {}", fmt::ptr(&Data_Vector.back()));
    fmt::println("Elements:              {}", Data_Vector.size());
    fmt::println("Size:                  {} bytes\n", sizeof(Data_Vector[0]) * Data_Vector.size());

    for(auto& i : Data_Vector) {
        fmt::println("{}\t-> {} bytes at {}", i, sizeof(i), fmt::ptr(&i));
    }
}

void Test_CArray(const vec<f64>& Data_Vector) {
    const f64* Data_Array = Data_Vector.data();
    size_t n = Data_Vector.size();

    fmt::println("Array:                {}", *Data_Array);
    fmt::println("\nArray data");
    fmt::println("Pointer address:      {}", fmt::ptr(Data_Array));
    fmt::println("first element address {}", fmt::ptr(&Data_Array[0]));
    fmt::println("last  element address {}", fmt::ptr(&Data_Array[n-1]));
    fmt::println("Elements:             {}", n);
    fmt::println("Size:                 {} bytes\n", sizeof(f64)*n);

    for(size_t i = 0; i < n; i++) {
        fmt::println("{}\t-> {} bytes at {}", Data_Array[i], sizeof(Data_Array[i]), fmt::ptr(&Data_Array[i]));
    }
}

void Tests(const idx DataCount) {
    const auto Data = Tools::Random::RandomNumsVD(DataCount, -10, 10, 2);

    fmt::println("\n{:-^80}", "Vector");
    auto Begin = HTimeNow();
    Test_Vector(Data);
    auto End = HTimeNow();
    auto Dur = Tools::Clock::CountDuration<Tools::Clock::Units::us>(Begin, End);
    fmt::println("Vector test lasted: {} μs", Dur);

    Begin = HTimeNow();
    fmt::println("\n{:-^80}", "C Array");
    Test_CArray(Data);
    End = HTimeNow();
    Dur = Tools::Clock::CountDuration<Tools::Clock::Units::us>(Begin, End);
    fmt::println("C-Array test lasted: {} μs", Dur);

    Begin = HTimeNow();
    fmt::println("\n{:-^80}", "Linked List");
    Test_LinkedList(Data);
    End = HTimeNow();
    Dur = Tools::Clock::CountDuration<Tools::Clock::Units::us>(Begin, End);
    fmt::println("Linked List test lasted: {} μs", Dur);
}

i32 main(const i32 argc, const char** argv) {
    idx DataCount = 0;
    if(argc == 1) {
        DataCount = 10;
        fmt::println("Using default data count (10)");
    } else {
        DataCount = std::stoull(argv[1]);
        fmt::println("Using {} data count", DataCount);
    }
    Tests(DataCount);
}