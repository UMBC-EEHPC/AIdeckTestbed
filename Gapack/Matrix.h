#pragma once

#include <stdint.h>
#include <initializer_list>
#include <Core/Heap/L2Heap.h>
#include <etl/optional.h>
#include <etl/memory.h>
#include <etl/algorithm.h>

namespace Gapack {

template<typename EntryType = int16_t, class Allocator = Core::Heap::L2Heap>
class Matrix {
    public:
        Matrix(int rows, int cols);
        Matrix(std::initializer_list<std::initializer_list<EntryType>> const& matrix);

        void print() const;

        ~Matrix() = default;
    private:
        int m_num_rows;
        int m_num_cols; 
        etl::unique_ptr<EntryType[], Core::Heap::L2Deleter<EntryType>> m_raw_matrix;
};

}