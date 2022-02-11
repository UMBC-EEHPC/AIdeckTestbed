#include "Matrix.h"

using namespace etl;
using namespace Core::Sync;
using Core::Containers::create_vector_on_heap;
using std::initializer_list;

namespace Gapack {

template class Matrix<int8_t>;
template class Matrix<int16_t>;
template class Matrix<int32_t>;
template class Matrix<int>;

template class Matrix<uint8_t>;
template class Matrix<uint16_t>;
template class Matrix<uint32_t>;

template class Matrix<int8_t, Core::Heap::L1Heap>;
template class Matrix<int16_t, Core::Heap::L1Heap>;
template class Matrix<int32_t, Core::Heap::L1Heap>;
template class Matrix<int, Core::Heap::L1Heap>;

template class Matrix<uint8_t, Core::Heap::L1Heap>;
template class Matrix<uint16_t, Core::Heap::L1Heap>;
template class Matrix<uint32_t, Core::Heap::L1Heap>;

template<typename EntryType, class Allocator>
Matrix<EntryType, Allocator>::Matrix(int rows, int cols)
    : m_num_rows(rows)
    , m_num_cols(cols)
    , m_raw_matrix(create_vector_on_heap<EntryType, Allocator>(m_num_rows * m_num_cols))
    , m_mutex(Mutex())
{
}

template<typename EntryType, class Allocator>
Matrix<EntryType, Allocator>::Matrix(initializer_list<initializer_list<EntryType>> const& matrix)
    : m_num_rows(matrix.size())
    , m_num_cols((*matrix.begin()).size())
    , m_raw_matrix(create_vector_on_heap<EntryType, Allocator>(m_num_rows * m_num_cols))
    , m_mutex(Mutex())
{
    auto start = m_raw_matrix.begin();
    for_each(matrix.begin(), matrix.end(), [&](auto& row) {
        start = copy(row.begin(), row.end(), start);
    });

    /* 
     * The ETL copy algorithm is bugged and doesn't update 
     * the size of the matrix on its own.
     */
    m_raw_matrix.uninitialized_resize(m_num_rows * m_num_cols);
}

template<typename EntryType, class Allocator>
Matrix<EntryType, Allocator>::~Matrix()
{

    Allocator::self().deallocate(
        static_cast<void*>(m_raw_matrix.data()),
        m_raw_matrix.size() * sizeof(EntryType));
}

template<typename EntryType, class Allocator>
[[gnu::noinline]] void Matrix<EntryType, Allocator>::print()
{
    MutexLocker locker(m_mutex);

    int prev_row = 0;
    for_each_coeff([&prev_row](int row, int col, auto coeff) {
        if (row != prev_row) {
            printf("\n");
            prev_row++;
        }
        printf("%d ", coeff);
    });
    printf("\n");
}

template<typename EntryType, class Allocator>
EntryType& Matrix<EntryType, Allocator>::coeff(int row, int col)
{
    return m_raw_matrix[(row * m_num_cols) + col];
}

template<typename EntryType, class Allocator>
EntryType const& Matrix<EntryType, Allocator>::coeff(int row, int col) const
{
    return m_raw_matrix[(row * m_num_cols) + col];
}

}