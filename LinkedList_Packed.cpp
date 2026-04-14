#include <Tools/Types.hpp>
#include <Tools/Clock.hpp>
#include <Tools/Random.hpp>

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>

/* Begin: Node struct */

template <typename T>
struct Node {
    T Value;
    uptr<Node<T>> Next;

    explicit Node(T Value, uptr<Node<T>> Next = nullptr);
};

template <typename T>
Node<T>::Node(T Value, uptr<Node<T>> Next) {
    this->Value = std::move(Value);
    this->Next = std::move(Next);
}

/* End: Node struct */

/* Begin: Iterator class */

template <typename T>
class LinkedIterator {
    Node<T>* Now;

    public:
    explicit LinkedIterator(Node<T>* node);

    T& operator*();
    T* operator->();
    LinkedIterator& operator++();

    bool operator==(const LinkedIterator& other) const;
    bool operator!=(const LinkedIterator& other) const;
};

/* End: Iterator class */

/* Begin: Linked List class */

template <typename T>
concept CtorIterables = OneOf<T, initl<T>, vec<T>>;

template <typename T>
class LinkedList {
    uptr<Node<T>> Head;
    idx LL_Size = size();

    public:

    LinkedList();

    LinkedList(const initl<T>& list);

    //LinkedList(const vec<T>& list);

    //template <typename R>
    //requires CtorIterables<R>
    //LinkedList(const R& list);

    template <std::ranges::input_range R>
    requires std::convertible_to<std::ranges::range_value_t<R>, T>
    LinkedList(const R& list);

    [[nodiscard]] idx size() const;

    // Append front
    void PushFront(const T& value);

    // Append back
    void PushBack(const T& Value);
    
    // Append at
    void PushAt(const idx After, T& Value);

    // Print all values
    void PrintData();

    // Convert node to usual std::vector<T>
    vec<T> GetIterableValues();

    // Convert node Value + Next node address to std::vector<pair<T, &Next>>
    vec<pair<T, Node<T>*>> GetIterablePairs();

    /* ---- Get from begin ----*/
    // Absolute beginning node object
    // O(1)
    Node<T>* GetHeadData();

    // Absolute beginning value
    // O(1)
    T GetHead();

    // Nth index AFTER absolute beginning node object
    // O(n)
    Node<T>* GetHeadData(idx After);

    // Nth index AFTER absolute beginning value
    // O(n)
    T GetHead(idx After);

    /* ---- Get from end ----*/

    // Absolute last element object
    Node<T>* GetTailData();

    // Absolute last element value
    // O(n)
    T GetTail();

    // Absolute last element object
    Node<T>* GetTailData(idx Before);

    // Nth element BEFORE absolute last element value
    // O(n)
    T GetTail(idx Before);

    /* ---- Getter and Setter ---- */
    // Array-like operators maybe?
    // Get Node object
    // O(n)
    T operator[](idx Index);

    // Set value
    // O(n)
    LinkedList& operator=(const LinkedList& Other);

    // Range based iterators
    LinkedIterator<T> begin();
    LinkedIterator<T> end();
};


/* Begin: Ctor */

template <typename T>
LinkedList<T>::LinkedList() {
    Head = nullptr;
    PushBack(T{});
}

template <typename T>
LinkedList<T>::LinkedList(const initl<T>& list) {
    Head = nullptr;
    for(const auto& v : list) {
        PushBack(v);
    }
}

// template <typename T>
// LinkedList<T>::LinkedList(const vec<T>& list) {
//     Head = nullptr;
//     for(const auto& v : list) {
//         PushBack(v);
//     }
// }

// template <typename T>
// template <typename R>
// requires CtorIterables<R>
// LinkedList<T>::LinkedList(const R& list) {
//     Head = nullptr;
//     for(const auto& v : list) {
//         PushBack(v);
//     }
// }

template <typename T>
template <std::ranges::input_range R>
requires std::convertible_to<std::ranges::range_value_t<R>, T>
LinkedList<T>::LinkedList(const R& list){
    this->Head = nullptr;
    for(const auto& v : list) {
        PushBack(v);
    }
}

/* End: Ctor */

/* End: Linked List class */

/* Begin: basic */

template <typename T>
idx LinkedList<T>::size() const {
    idx count = 0;
    for(auto* curr = Head.get(); curr; curr = curr->Next.get()) ++count;
    return count;
};

template <typename T>
void LinkedList<T>::PushFront(const T& value) {
    auto n = std::make_unique<Node<T>>(value, std::move(Head));
    Head = std::move(n);
}

template <typename T>
void LinkedList<T>::PushBack(const T& Value) {
    auto n = std::make_unique<Node<T>>(Value);
    
    if(!Head) {
        Head = std::move(n);
        return;
    }

    Node<T>* Current = Head.get();

    while(Current->Next != nullptr)
        Current = Current->Next.get();
    
    Current->Next = std::move(n);
}

template <typename T>
void LinkedList<T>::PushAt(const idx After, T& value) {
    if(!Head)
        throw std::runtime_error("List kosong");

    Node<T>* Current = Head.get();

    for(idx i = 0; i < After - 1; ++i)
    {
        if(!Current->Next)
            throw std::out_of_range("Index terlalu besar");

        Current = Current->Next.get();
    }

    auto node = std::make_unique<Node<T>>(value);

    node->Next = std::move(Current->Next);
    Current->Next  = std::move(node);
}

template <typename T>
void LinkedList<T>::PrintData() {
    Node<T>* Current = Head.get();

    while(Current != nullptr) {
        fmt::println("{} @ {}", Current->Value, fmt::ptr(Current));
        Current = Current->Next.get();
    }
}

/* End: basic */


/* Begin: Get Iterables */

template <typename T>
vec<T> LinkedList<T>::GetIterableValues() {
    vec<T> result;
    result.reserve(LL_Size);

    Node<T>* Current = Head.get();

    while(Current != nullptr) {
        result.push_back(Current->Value);
        Current = Current->Next.get();
    }

    return result;
}

template <typename T>
vec<pair<T, Node<T>*>> LinkedList<T>::GetIterablePairs() {
    vec<pair<T, Node<T>*>> result;
    result.reserve(LL_Size);

    Node<T>* Current = Head.get();

    while(Current != nullptr) {
        result.emplace_back(Current->Value, Current->Next.get());
        Current = Current->Next.get();
    }

    return result;
}

/* End: Get Iterables */

/* Begin: Get Head */

template <typename T>
Node<T>* LinkedList<T>::GetHeadData() {
    return Head.get();
}

template <typename T>
T LinkedList<T>::GetHead() {
    return GetHeadData()->Value;
}

template <typename T>
Node<T>* LinkedList<T>::GetHeadData(idx After) {
    Node<T>* Current = Head.get();
    
    while(After-- && Current) {
        Current = Current->Next.get();
    }
    
    if(!Current) {
        throw std::out_of_range("Index too big!");
    }
    
    return Current;
}

template <typename T>
T LinkedList<T>::GetHead(idx After) {
    return GetHeadData(After)->Value;
}

/* End: Get Head */

/* Begin: Get Tail */

template <typename T>
Node<T>* LinkedList<T>::GetTailData() {
    if(Head == nullptr) {
        throw std::runtime_error("Empty list!");
    }

    Node<T>* Current = Head.get();

    while(Current->Next != nullptr) {
        Current = Current->Next.get();
    }

    return Current;
}

template <typename T>
T LinkedList<T>::GetTail() {
    return GetTailData()->Value;
}

template <typename T>
Node<T>* LinkedList<T>::GetTailData(idx Before) {
    // const idx len = LL_Size;

    if(Before >= LL_Size) {
        throw std::out_of_range("Index too large!");
    }
    if(Head == nullptr) {
        throw std::runtime_error("Empty list!");
    }

    idx Target = LL_Size-1 - Before;

    Node<T>* Current = Head.get();

    while(Target--) {
        Current = Current->Next.get();
    }

    return Current;
}

template <typename T>
T LinkedList<T>::GetTail(idx Before) {
    return GetTailData(Before)->Value;
}

/* End: Get Tail */

/* Begin: Operators */

template <typename T>
T LinkedList<T>::operator[](idx Index) {
    return this->GetHead(Index);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& Other) {
    if (this == &Other) {
        return *this;
    }

    Head.reset();

    Node<T>* Current = Other.Head.get();
    while(Current != nullptr) {
        PushBack(Current->Value);
        Current = Current->Next.get();
    }

    return *this;
}

template <typename T>
LinkedIterator<T> LinkedList<T>::begin() {
    return LinkedIterator<T>(Head.get());
}

template <typename T>
LinkedIterator<T> LinkedList<T>::end() {
    return LinkedIterator<T>(nullptr);
}

/* End: Operators */

/* Begin: LinkedIterator */
template <typename T>
LinkedIterator<T>::LinkedIterator(Node<T>* node) {
    LinkedIterator<T>::Now = node;
};

template <typename T>
T& LinkedIterator<T>::operator*() {
    return Now->Value;
}

template <typename T>
T* LinkedIterator<T>::operator->() {
    return &Now->Value;
}

template <typename T>
LinkedIterator<T>& LinkedIterator<T>::operator++() {
    if(Now) Now = Now->Next.get();
    return *this;
}

template <typename T>
bool LinkedIterator<T>::operator==(const LinkedIterator& other) const {
    return Now == other.Now;
}

template <typename T>
bool LinkedIterator<T>::operator!=(const LinkedIterator& other) const {
    return Now != other.Now;
}

/* End: LinkedIterator */

/* Begin: Test */
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

void RunTest() {
    auto Begin = Tools::Clock::HTimeNow();
    
    const auto Data = Tools::Random::RandomNumsVI(32, -10, 10);

    fmt::println("\n{:-^80}", "Linked List");
    Test_LinkedList(Data, false);

    auto End = Tools::Clock::HTimeNow();
    auto Dur = Tools::Clock::CountDuration<Tools::Clock::Units::us>(Begin, End);
    fmt::println("Linked List test lasted: {} μs", Dur);
}
/* End: Test */

i32 main(){
    RunTest();
}