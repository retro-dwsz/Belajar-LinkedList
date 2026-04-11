#pragma once

#include <concepts>
#ifndef LINKEDLIST_LINKEDLIST_BASE_HPP
#define LINKEDLIST_LINKEDLIST_BASE_HPP

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/color.h>

#include <Tools/Types.hpp>

#include "LinkedList.Node.hpp"
#include "LinkedList.Iterator.hpp"

/* Begin: LinkedList class */

template <typename T>
concept CtorIterables = OneOf<T, initl<T>, vec<T>>;

template <typename T>
class LinkedList {
    uptr<Node<T>> Head;
    idx LL_Size = size();
    
    public:
    
    LinkedList(initl<T>& list);
    
    LinkedList(vec<T>& list);

    template <typename R>
    requires CtorIterables<R>
    LinkedList(R& list);

    template <std::ranges::input_range R>
    requires std::convertible_to<std::ranges::range_value_t<R>, T>
    LinkedList(R& list);

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
LinkedList<T>::LinkedList(initl<T>& list) {
    Head = nullptr;
    for(const auto& v : list) {
        PushBack(v);
    }
}

template <typename T>
LinkedList<T>::LinkedList(vec<T>& list) {
    Head = nullptr;
    for(const auto& v : list) {
        PushBack(v);
    }
}

template <typename T>
template <typename R>
requires CtorIterables<R>
LinkedList<T>::LinkedList(R& list) {
    Head = nullptr;
    for(const auto& v : list) {
        PushBack(v);
    }
}

template <typename T>
template <std::ranges::input_range R>
requires std::convertible_to<std::ranges::range_value_t<R>, T>
LinkedList<T>::LinkedList(R& list){
    this->Head = nullptr;
    for(const auto& v : list) {
        PushBack(v);
    }
}

/* End: Ctor */


/* End: Linked List class */

#endif //LINKEDLIST_LINKEDLIST_BASE_HPP