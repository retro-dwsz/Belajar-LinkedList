#pragma once

#ifndef LINKEDLIST_LINKEDLISTS_HPP
#define LINKEDLIST_LINKEDLISTS_HPP

#include <memory>

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/color.h>

#include <Tools/Types.hpp>
#include <Tools/Random.hpp>

template <typename T>
struct Node {
    T Value;
    uptr<Node<T>> Next;

    explicit Node(const T& Value, uptr<Node<T>> Next = nullptr) {
        this->Value = Value;
        this->Next = std::move(Next);
    }
};

template <typename T>
class LinkedIterator {
    Node<T>* Current;

    public:
    explicit LinkedIterator(Node<T>* node) : Current(node) {}

    T& operator*() {
        return Current->Value;
    }

    LinkedIterator& operator++() {
        Current = Current->Next.get();
        return *this;
    }

    bool operator!=(const LinkedIterator& other) const {
        return Current != other.Current;
    }

    T* operator->() {
        return &Current->Value;
    }

    bool operator==(const LinkedIterator& other) const {
        return Current == other.Current;
    }
};

template <typename T>
class LinkedList {
    uptr<Node<T>> Head;
    idx LL_Size = 0;

    public:
    [[nodiscard]] idx size() const {
        idx count = 0;
        Node<T>* Current = Head.get();

        while(Current) {
            count++;
            Current = Current->Next.get();
        }

        return count;
    };

    // Append front
    void PushFront(const T& value) {
        auto n = std::make_unique<Node<T>>(value, std::move(Head));
        Head = std::move(n);
    }

    // Append back
    void PushBack(const T& Value) {
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

    // Print all values
    void PrintData() {
        Node<T>* Current = Head.get();

        while(Current != nullptr) {
            fmt::println("{} @ {}", Current->Value, fmt::ptr(Current));
            Current = Current->Next.get();
        }
    }

    // Convert node to usual std::vector<T>
    vec<T> GetIterableValues() {
        vec<T> result;
        result.reserve(size());

        Node<T>* Current = Head.get();

        while(Current != nullptr) {
            result.push_back(Current->Value);
            Current = Current->Next.get();
        }

        return result;
    }

    // Convert node Value + Next node address to std::vector<pair<T, &Next>>
    vec<pair<T, Node<T>*>> GetIterablePairs() {
        vec<pair<T, Node<T>*>> result;
        result.reserve(size());

        Node<T>* Current = Head.get();

        while(Current != nullptr) {
            result.emplace_back(Current->Value, Current->Next.get());
            Current = Current->Next.get();
        }

        return result;
    }

    /* ---- How many elements here? ---- */
    // O(n)
    idx size() {
        Node<T>* Current = Head.get();
        idx count = 0;

        while(Current != nullptr) {
            count++;
            Current = Current->Next.get();
        }
        return count;
    }

    /* ---- Get from begin ----*/
    // Absolute beginning node object
    // O(1)
    Node<T>* GetHeadData() {
        return Head.get();
    }

    // Absolute beginning value
    // O(1)
    T GetHead() {
        return GetHeadData()->Value;
    }

    // Nth index AFTER absolute beginning node object
    // O(n)
    Node<T>* GetHeadData(idx After) {

        Node<T>* Current = Head.get();

        while(After-- && Current)
            Current = Current->Next.get();

        if(!Current)
            throw std::out_of_range("Index too big!");

        return Current;
    }

    // Nth index AFTER absolute beginning value
    // O(n)
    T GetHead(idx After) {
        return GetHeadData(After)->Value;
    }

    /* ---- Get from end ----*/

    // Absolute last element object
    Node<T>* GetTailData() {
        if(Head == nullptr) {
            throw std::runtime_error("Empty list!");
        }

        Node<T>* Current = Head.get();

        while(Current->Next != nullptr) {
            Current = Current->Next.get();
        }

        return Current;
    }

    // Absolute last element value
    // O(n)
    T GetTail() {
        return GetTailData()->Value;
    }

    // Absolute last element object
    Node<T>* GetTailData(const idx Before) {
        const idx len = size();

        if(Before >= len) {
            throw std::out_of_range("Index too large!");
        }
        if(Head == nullptr) {
            throw std::runtime_error("Empty list!");
        }

        idx Target = len-1 - Before;

        Node<T>* Current = Head.get();

        while(Target--) {
            Current = Current->Next.get();
        }

        return Current;
    }

    // Nth element BEFORE absolute last element value
    // O(n)
    T GetTail(const idx Before) {
        return GetTailData(Before)->Value;
    }

    /* ---- Getter and Setter ---- */
    // Array-like operators maybe?
    // Get Node object
    // O(n)
    T operator[](idx Index) {
        Node<T>* cur = Head.get();

        while(Index-- && cur) {
            cur = cur->Next.get();
        }

        if(!cur) {
            throw std::out_of_range("LinkedList index");
        }

        return cur->Value;
    }

    // Set value
    // O(n)
    LinkedList& operator=(const LinkedList& Other) {
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

    // Range based iterators
    LinkedIterator<T> begin() {
        return LinkedIterator<T>(Head.get());
    }

    LinkedIterator<T> end() {
        return LinkedIterator<T>(nullptr);
    }
};

template <typename  T>
void Test_LinkedList(const vec<T>& Vector_Data, const bool Debug) {

    LinkedList<T> Data_List;

    for(const auto& i : Vector_Data)
        Data_List.PushBack(i);

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

#endif //LINKEDLIST_LINKEDLISTS_HPP