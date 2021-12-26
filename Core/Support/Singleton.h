#pragma once

#include <Core/Heap/L1Heap.h>
#include <Core/Heap/L2Heap.h>
#include <etl/optional.h>

#define SINGLETON_CLASS(sc) \
        private: \
            sc() = default; \
        public: \
            [[nodiscard]] static sc* initialize(); \
            static sc& self(); \
            sc(sc&) = delete; \
            sc(sc&&) = delete; \
            sc& operator=(sc&) = delete; \
            sc& operator=(sc&&) = delete; 

#define SINGLETON_CLASS_WITH_ARGS(sc, ...) \
        private: \
            sc() = default; \
        public: \
            [[nodiscard]] static sc* initialize(__VA_ARGS__); \
            static sc& self(); \
            sc(sc&) = delete; \
            sc(sc&&) = delete; \
            sc& operator=(sc&) = delete; \
            sc& operator=(sc&&) = delete; 

template <class T, class Allocator>
[[nodiscard]] inline T* create_singleton() {
    return static_cast<T*>(Allocator::self().allocate(sizeof(T)));
}

template <class T>
[[nodiscard]] inline T* create_singleton_l1() {
    return create_singleton<T, Core::Heap::L1Heap>();
}

template <class T>
[[nodiscard]] inline T* create_singleton_l2() {
    return create_singleton<T, Core::Heap::L2Heap>();
}