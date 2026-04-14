#pragma once

#ifndef LINKEDLIST_LINKEDLIST_LL_BASIC_HPP
#define LINKEDLIST_LINKEDLIST_LL_BASIC_HPP

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/color.h>

#include <Tools/Types.hpp>

#include "LinkedList.LL.Base.hpp"

#include "LinkedList.Node.hpp"

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

#endif //LINKEDLIST_LINKEDLIST_LL_BASIC_HPP