#pragma once

#include <etl/vector.h>

namespace Core::Containers {

template<typename EntryType, class Allocator>
[[nodiscard]] etl::vector_ext<EntryType> create_vector_on_heap(size_t num_elements)
{
    size_t size = sizeof(EntryType) * num_elements;
    return etl::vector_ext<EntryType>(Allocator::self().allocate(size), size);
}

}