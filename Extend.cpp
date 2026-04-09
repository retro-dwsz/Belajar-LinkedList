#include <fmt/format.h>
#include <fmt/ranges.h>

#include <Tools/Random.hpp>

#define GetArraySize(array) sizeof(array)/sizeof(array[0])

void Test_C_Array_Extend() {
    constexpr i32 arrA[] = {1, 2, 3};
    constexpr idx sizeA = std::size(arrA);
    fmt::print("ArrA = [");
    for(idx i = 0; i < sizeA; i++) {
        fmt::print("{}", arrA[i]);
        if(i + 1 < sizeA) fmt::print(", ");
    }
    fmt::println("]");
    
    constexpr i32 arrB[] = {4, 5, 6};
    constexpr idx sizeB = std::size(arrB);
    fmt::print("ArrB = [");
    for(idx i = 0; i < sizeB; i++) {
        fmt::print("{}", arrB[i]);
        if(i + 1 < sizeB) fmt::print(", ");
    }
    fmt::println("]");
    
    auto Merge = [](const i32* arrA, const idx sizeA, const i32* arrB, const idx sizeB) -> i32* {
        const idx sizeC = sizeA + sizeB;
        i32* arrC = (i32*)malloc(sizeC * sizeof(int));

        for(idx i = 0; i < sizeA; i++) {
            arrC[i] = arrA[i];
        }

        for(idx i = 0; i < sizeB; i++) {
            arrC[sizeA + i] = arrB[i];
        }

        return &*arrC;
    };

    i32* arrC = Merge(arrA, sizeA, arrB, sizeB);

    fmt::print("ArrC = [");
    for(idx i = 0; i < sizeA + sizeB; i++) {
        fmt::print("{}", arrC[i]);
        if(i + 1 < sizeA + sizeB) fmt::print(", ");
    }
    fmt::println("]");

    free(arrC);
}

void Test_CPP_Vector_Extend() {
    vec arrA = {1, 2, 3};
    fmt::println("arrA = {}", arrA);

    vec arrB = {4, 5, 6};
    fmt::println("arrB = {}", arrB);

    arrA.insert(
        arrA.end(),
        arrB.begin(),
        arrB.end()
    );

    fmt::println("ArrA = {}", arrA);
}

i32 main(){
    Test_CPP_Vector_Extend();
}
