#include <Tools/Types.hpp>
#include <Tools/Casting.hpp>
#include <Tools/Random.hpp>
#include <Tools/Vector.hpp>

#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

using namespace Tools::Cast;

constexpr fmt::text_style FG_DRED = fmt::fg(fmt::color::dark_red);
constexpr fmt::text_style FG_DGRN = fmt::fg(fmt::color::dark_green);
constexpr fmt::text_style FG_DBLE = fmt::fg(fmt::color::dark_blue);
constexpr fmt::text_style FG_DYLW = fmt::fg(fmt::color::green_yellow);
constexpr fmt::text_style FG_DCYN = fmt::fg(fmt::color::dark_cyan);
constexpr fmt::text_style FG_GRYN = fmt::fg(fmt::color::lawn_green);
constexpr fmt::text_style FG_AQUA = fmt::fg(fmt::color::aqua);

template <typename T>
inline auto Ptr2Num(T& x) {
    return rcast<u32p>(std::addressof(x));
}

template <typename T>
inline auto fmt_ptr(T& x) {
    return fmt::ptr(std::addressof(x));
}

str GetType(const str& t) {
    static umap<str, str> types {
        {"s", str{fmt::format(fmt::emphasis::bold | FG_DCYN, "i16")}},
        {"i", str{fmt::format(fmt::emphasis::bold | FG_DRED, "i32")}},
        {"x", str{fmt::format(fmt::emphasis::bold | FG_DGRN, "i64")}},
        {"f", str{fmt::format(fmt::emphasis::bold | FG_DBLE, "f32")}},
        {"d", str{fmt::format(fmt::emphasis::bold | FG_DYLW, "f64")}}
    };

    if (types.find(t) != types.end()) {
        return types.find(t)->second;
    }

    return "???";
};

template <typename T>
str LoopFmt(T& x){
    return fmt::format(
        "{}\t-> <{}> {} at {}",                       /* Main string */
        x,                                            /* Main data */
        GetType(typeid(x).name()),                    /* Data type */
        fmt::format(FG_GRYN, "{} bytes", sizeof(x)),  /* Size of data*/
        fmt::format(FG_AQUA, "{}", fmt_ptr(x))        /* Where the data is */
    );
}

u32p Diff(const u32p& First, const u32p& Second){
    return rcast<u32p>(First) - rcast<u32p>(Second);
};

void Primitives() {
    auto Data = Tools::Random::RandomNumsVL();
    auto* arr = Data.data();
    for(idx i = 0; i < std::size(Data); i++){
        if(i == 0){
            fmt::println("{}", LoopFmt(arr[i]));
        } else {
            fmt::print("{}", LoopFmt(arr[i]));
        }
        if(i != 0){
            fmt::println(
                " (jump {} address(es)) from {}",
                Ptr2Num(arr[i]) - Ptr2Num(arr[i-1]),
                fmt_ptr(arr[i-1])
            );
        }
    }

    std::pair<void*, u32p> ptrA = {
        std::addressof(arr[2]),
        rcast<u32p>(std::addressof(arr[1]))
    };
    std::pair<void*, u32p> ptrB = {
        std::addressof(arr[1]),
        rcast<u32p>(std::addressof(arr[0]))
    };

    u64 diff = ptrA.second - ptrB.second;
    fmt::println("\n{} - {} = {}", fmt::ptr(ptrA.first), fmt::ptr(ptrB.first), diff);
}

void Dynamic() {
    auto Data_i = Tools::Random::RandomNumsVI(5);
    auto Data_x = Tools::Random::RandomNumsVL(5);
    auto Data_f = Tools::Random::RandomNumsVF(5);
    auto Data_d = Tools::Random::RandomNumsVD(5);

    vec<tvar<i16, i64, f32, f64>> DataMix;
    DataMix.reserve(Data_i.size() + Data_x.size() + Data_f.size() + Data_d.size());

    for(auto& i : Data_i){
        DataMix.push_back(scast<i16>(i));
    }

    for(auto& i : Data_x){
        DataMix.push_back(i);
    }

    for(auto& i : Data_f){
        DataMix.push_back(i);
    }

    for(auto& i : Data_d){
        DataMix.push_back(i);
    }

    DataMix = Tools::Vector::Shuffle(DataMix);

    for(idx i = 0; i < DataMix.size(); i++){
        if(i == 0){
            std::visit([](auto& x){
                fmt::println("{}", LoopFmt(x));
            }, DataMix[i]);
        } else {
            std::visit([](auto& x){
                fmt::print("{}", LoopFmt(x));
            }, DataMix[i]);
        }
        if(i != 0){
            fmt::println(
                " (jump {} address(es)) from {}",
                Ptr2Num(DataMix[i]) - Ptr2Num(DataMix[i-1]),
                fmt_ptr(DataMix[i-1])
            );
        }
    }

    std::pair<void*, u32p> ptrA = {
        std::addressof(DataMix[2]),
        rcast<u32p>(std::addressof(DataMix[1]))
    };
    std::pair<void*, u32p> ptrB = {
        std::addressof(DataMix[1]),
        rcast<u32p>(std::addressof(DataMix[0]))
    };

    u64 diff = ptrA.second - ptrB.second;
    fmt::println("\n{} - {} = {}", fmt::ptr(ptrA.first), fmt::ptr(ptrB.first), diff);
}

int main(){
    fmt::println("{:-^80}", "[ Primitive Types ]");
    Primitives();
    fmt::println("{:-^80}", "[ Dynamic Types ]");
    Dynamic();
}