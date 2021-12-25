#pragma once

#include <stdint.h>
#include <initializer_list>
#include <Core/Heap/L2Heap.h>
#include <Core/Containers/HeapVector.h>
#include <Core/Sync/Mutex.h>
#include <Core/Sync/Spinlock.h>
#include <Core/Device/Serial/UART.h>
#include <etl/vector.h>
#include <etl/optional.h>
#include <etl/algorithm.h>
#include <etl/function.h>

namespace Gapack {

template<typename EntryType = int16_t, class Allocator = Core::Heap::L2Heap>
class Matrix {
    public:
        typedef EntryType Coeff;
        Matrix(int rows, int cols);
        Matrix(std::initializer_list<std::initializer_list<EntryType>> const& matrix);

        template<typename OtherEntryType, class OtherAllocator >
        Matrix(Matrix const& rhs);
        Matrix(Matrix&& rhs);

        [[gnu::always_inline]] inline EntryType& coeff(int row, int col);
        [[gnu::always_inline]] inline EntryType const& coeff(int row, int col) const;

        [[gnu::noinline]] void print();

        int get_num_rows() const { return m_num_rows; }
        int get_num_cols() const { return m_num_cols; }

        template <class Function>
        void for_each_coeff(Function f) {
            int y, x = 0;            
            etl::for_each(m_raw_matrix.begin(), m_raw_matrix.end(), [&](auto entry) {
                f(y, x, entry);
                x++;
                if (x >= get_num_cols()) {
                    x = 0;
                    y++;
                }
            });
        }

        ~Matrix();
    private:
        int m_num_rows;
        int m_num_cols; 
        etl::vector_ext<EntryType> m_raw_matrix;
        Core::Sync::Mutex m_mutex;

};

}