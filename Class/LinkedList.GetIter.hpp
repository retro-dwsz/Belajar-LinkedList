#pragma once

#ifndef LINKEDLIST_LINKEDLIST_GET_ITERABLES_HPP
#define LINKEDLIST_LINKEDLIST_GET_ITERABLES_HPP

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/color.h>

#include "LinkedList.LL.base.hpp"

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

#endif //LINKEDLIST_LINKEDLIST_GET_ITERABLES_HPP