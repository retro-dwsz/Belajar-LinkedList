#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>

#include <Tools/Random.hpp>
#include <Tools/Clock.hpp>
#include <Tools/Types.hpp>

// #include "LinkedLists.hpp"
#include "Class/LinkedList.hpp"

// #define GetArraySize(array) sizeof(array)/sizeof(array[0])

template <typename T>
void Test_Vector(const vec<T>& Data_Vector) {
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

template <typename T>
void Test_CArray(const vec<T>& Data_Vector) {
    // const T* Data_Array = Data_Vector.data();
    const idx n = Data_Vector.size();

    // T* Data_Array = (T*)malloc(n * sizeof(T));
    auto Data_Array = Data_Vector.data();

    // for(idx i = 0; i < n; i++){
    //     Data_Array[i] = Data_Vector[i];
    // }

    fmt::println("Array:                {}", *Data_Array);
    fmt::println("\nArray data");
    fmt::println("Pointer address:      {}", fmt::ptr(Data_Array));
    fmt::println("first element address {}", fmt::ptr(&Data_Array[0]));
    fmt::println("last  element address {}", fmt::ptr(&Data_Array[n-1]));
    fmt::println("Elements:             {}", n);
    fmt::println("Size:                 {} bytes\n", sizeof(T)*n);

    for(idx i = 0; i < n; i++) {
        fmt::println("{}\t-> {} bytes at {}", Data_Array[i], sizeof(Data_Array[i]), fmt::ptr(&Data_Array[i]));
    }
}

template <typename T>
void Test_LinkedList(const vec<T>& Vector_Data, const bool Debug) {
    LinkedList<T> Data_List(Vector_Data);

    idx n = Data_List.size();

    auto Pairs = Data_List.GetIterablePairs();

    fmt::println("Linked List:          {}", Data_List);

    if(Debug) {
        fmt::println("Linked List debug:    ");
        fmt::print("[");
        for(size_t i = 0; i < Pairs.size(); ++i) {

            const auto& [value, next] = Pairs[i];

            fmt::print("[{}, {}]", value, fmt::ptr(next));

            if(i + 1 < Pairs.size())
                fmt::print(", ");
        }
        fmt::println("]");
    }

    fmt::println("\nLinked List data");
    fmt::println("Pointer address:      {}", fmt::ptr(&Data_List));
    fmt::println("first element address {}", fmt::ptr(Data_List.GetHeadData()));
    fmt::println("last  element address {}", fmt::ptr(Data_List.GetTailData()));
    fmt::println("Elements:             {}", n);
    fmt::println("Size:                 {} bytes\n", sizeof(T)*n);

    Node<T>* cur = Data_List.GetHeadData();

    while(cur) {
        fmt::println("{}\t-> {} bytes at {}", cur->Value, sizeof(cur->Value), fmt::ptr(cur));
        cur = cur->Next.get();
    }
}

void Tests(const idx DataCount) {
    const auto Data = Tools::Random::RandomNumsVI(DataCount, -10, 10);

    // const vec<str> Data = {"a", "b", "c", "d", "e"};

    fmt::println("\n{:-^80}", "Vector");
    auto Begin = Tools::Clock::HTimeNow();
    Test_Vector(Data);
    auto End = Tools::Clock::HTimeNow();
    auto Dur = Tools::Clock::CountDuration<Tools::Clock::Units::us>(Begin, End);
    fmt::println("Vector test lasted: {} μs", Dur);

    Begin = Tools::Clock::HTimeNow();
    fmt::println("\n{:-^80}", "C Array");
    Test_CArray(Data);
    End = Tools::Clock::HTimeNow();
    Dur = Tools::Clock::CountDuration<Tools::Clock::Units::us>(Begin, End);
    fmt::println("C-Array test lasted: {} μs", Dur);

    Begin = Tools::Clock::HTimeNow();
    fmt::println("\n{:-^80}", "Linked List");
    Test_LinkedList(Data, false);
    End = Tools::Clock::HTimeNow();
    Dur = Tools::Clock::CountDuration<Tools::Clock::Units::us>(Begin, End);
    fmt::println("Linked List test lasted: {} μs", Dur);
}

#include "Std_List.hpp"

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
