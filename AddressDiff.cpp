#include <Tools/Types.hpp>
#include <Tools/Casting.hpp>
#include <Tools/Random.hpp>
#include <Tools/Vector.hpp>

#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

using namespace Tools::Cast;

#define fmt_color(Color) fmt::fg(fmt::color::Color)
using txs = fmt::text_style;

namespace FG {
    constexpr txs FG_DRED = fmt_color(dark_red);
    constexpr txs FG_DGRN = fmt_color(dark_green);
    constexpr txs FG_DBLE = fmt_color(dark_blue);
    constexpr txs FG_DYLW = fmt_color(green_yellow);
    constexpr txs FG_DCYN = fmt_color(dark_cyan);
    constexpr txs FG_DORG = fmt_color(dark_orange);
    constexpr txs FG_GRYN = fmt_color(lawn_green);
    constexpr txs FG_AQUA = fmt_color(aqua);
}

template <typename T>
inline auto Ptr2Num(T& x) {
    return rcast<u32p>(std::addressof(x));
}

template <typename T>
inline auto fmt_ptr(T& x) {
    return fmt::ptr(std::addressof(x));
}

#define TypeFormat(Color, TypeId)   \
    str{fmt::format(fmt::emphasis::bold | Color, #TypeId) }

str GetType(const str& t) {
    #if defined (TypeDebug)
    fmt::println("inputed: {}", t);
    #endif
    static const umap<str, str> types {
        {"a", TypeFormat(FG::FG_DORG, i8)},
        {"s", TypeFormat(FG::FG_DCYN, i16)},
        {"i", TypeFormat(FG::FG_DRED, i32)},
        {"x", TypeFormat(FG::FG_DGRN, i64)},
        
        {"f", TypeFormat(FG::FG_DBLE, f32)},
        {"d", TypeFormat(FG::FG_DYLW, f64)},
        {"e", TypeFormat(FG::FG_DYLW, fld)},

        // {"a", str{fmt::format(fmt::emphasis::bold | FG::FG_DORG, "i8 ")}},
        // {"s", str{fmt::format(fmt::emphasis::bold | FG::FG_DCYN, "i16")}},
        // {"i", str{fmt::format(fmt::emphasis::bold | FG::FG_DRED, "i32")}},
        // {"x", str{fmt::format(fmt::emphasis::bold | FG::FG_DGRN, "i64")}},
        // {"f", str{fmt::format(fmt::emphasis::bold | FG::FG_DBLE, "f32")}},
        // {"d", str{fmt::format(fmt::emphasis::bold | FG::FG_DYLW, "f64")}},
        // {"e", str{fmt::format(fmt::emphasis::bold | FG::FG_DYLW, "fld")}}
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
        fmt::format(FG::FG_GRYN, "{} bytes", sizeof(x)),  /* Size of data*/
        fmt::format(FG::FG_AQUA, "{}", fmt_ptr(x))        /* Where the data is */
    );
}

u32p Diff(const u32p& First, const u32p& Second){
    return rcast<u32p>(First) - rcast<u32p>(Second);
};

#define VariantLoop(Iterable)                               \
    for(idx i = 0; i < std::size(Iterable); i++){           \
        if(i == 0){                                         \
            std::visit([](const auto& x){                   \
                fmt::println("{}", LoopFmt(x));             \
            }, *std::next(Iterable.begin(), i));            \
        } else {                                            \
            std::visit([](const auto& x){                   \
                fmt::print("{}", LoopFmt(x));               \
            }, *std::next(Iterable.begin(), i));            \
        }                                                   \
        if(i != 0){                                         \
            fmt::println(                                   \
                " (jump {:#16x} address(es)) from {:p}",    \
                Ptr2Num(*std::next(Iterable.begin(), i)) -  \
                Ptr2Num(*std::next(Iterable.begin(), i-1)), \
                fmt_ptr(*std::next(Iterable.begin(), i-1))  \
            );                                              \
        }                                                   \
    }                                                       \


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

    const pair<void*, u32p> ptrA = {
        std::addressof(arr[1]),
        rcast<u32p>(std::addressof(arr[1]))
    };

    const pair<void*, u32p> ptrB = {
        std::addressof(arr[0]),
        rcast<u32p>(std::addressof(arr[0]))
    };

    const u64 diff = ptrA.second - ptrB.second;
    fmt::println(
        "\n{} - {} = {}\n",
        fmt::ptr(ptrA.first),
        fmt::ptr(ptrB.first),
        diff
    );
}

void Dynamic() {
    const auto Data_i = Tools::Random::RandomNumsVI(5);
    const auto Data_x = Tools::Random::RandomNumsVL(5);
    const auto Data_f = Tools::Random::RandomNumsVF(5);
    const auto Data_d = Tools::Random::RandomNumsVD(5);

    vec<tvar<i16, i64, f32, f64>> DataMix;
    DataMix.reserve(Data_i.size() + Data_x.size() + Data_f.size() + Data_d.size());

    for(const auto& i : Data_i){
        DataMix.push_back(scast<i16>(i));
    }

    for(const auto& i : Data_x){
        DataMix.push_back(i);
    }

    for(const auto& i : Data_f){
        DataMix.push_back(i);
    }

    for(const auto& i : Data_d){
        DataMix.push_back(i);
    }

    DataMix = Tools::Vector::Shuffle(DataMix);

    VariantLoop(DataMix)

    const std::pair<void*, u32p> ptrA = {
        std::addressof(DataMix[2]),
        rcast<u32p>(std::addressof(DataMix[1]))
    };
    const std::pair<void*, u32p> ptrB = {
        std::addressof(DataMix[1]),
        rcast<u32p>(std::addressof(DataMix[0]))
    };

    const u64 diff = ptrA.second - ptrB.second;
    fmt::println("\n{} - {} = {}\n", fmt::ptr(ptrA.first), fmt::ptr(ptrB.first), diff);
}

void std_list(){
    const auto Data_x = Tools::Random::RandomNumsVL();
    const auto Data_d = Tools::Random::RandomNumsVD();

    vec<tvar<i64, f64>> Data_t;
    for(auto& i : Data_x){
        Data_t.push_back(i);
    }
    for(auto& i : Data_d){
        Data_t.push_back(i);
    }

    Data_t = Tools::Vector::Shuffle(Data_t);

    fmt::println("{:*^50}", "[ std::vector ]");
    VariantLoop(Data_t);
    
    list<tvar<i64, f64>> DataMix;
    for(auto& i : Data_t){
        DataMix.push_back(i);
    }
    
    fmt::println("{:*^50}", "[ std::list ]");
    VariantLoop(DataMix);

    const std::pair<void*, u32p> ptrA = {
        std::addressof(*std::next(DataMix.begin(), 2)),
        rcast<u32p>(std::addressof(*std::next(DataMix.begin(), 2)))
    };
    const std::pair<void*, u32p> ptrB = {
        std::addressof(*std::next(DataMix.begin(), 1)),
        rcast<u32p>(std::addressof(*std::next(DataMix.begin(), 0)))
    };

    const u64 diff = ptrA.second - ptrB.second;
    fmt::println("\n{} - {} = {}\n", fmt::ptr(ptrA.first), fmt::ptr(ptrB.first), diff);
}

int main(){
    fmt::println("{:-^80}", "[ Primitive Types ]");
    Primitives();
    fmt::println("{:-^80}", "[ Dynamic Types ]");
    Dynamic();
    fmt::println("{:-^80}", "[ Linked Dynamic Types ]");
    std_list();
}
