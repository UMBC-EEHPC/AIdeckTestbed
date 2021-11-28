#include "Matrix.h"

using namespace etl;
using namespace std;

namespace Gapack {

template<typename EntryType, class Allocator>
Matrix<EntryType, Allocator>::Matrix(int rows, int cols) :
    m_num_rows(rows),
    m_num_cols(cols),
    m_raw_matrix(Allocator::self().allocate(sizeof(EntryType) * rows * cols)) {}

template<typename EntryType, class Allocator>
Matrix<EntryType, Allocator>::Matrix(initializer_list<initializer_list<EntryType>> const& matrix) :
        m_num_rows(matrix.size()),
        m_num_cols((*matrix.begin()).size()),
        m_raw_matrix(Allocator::self().allocate(sizeof(EntryType) * m_num_rows * m_num_cols)) {
    int offset = 0;
    for_each(matrix.begin(), matrix.end(), [this, &offset](auto const& col){
        for_each(col.begin(), col.end(), [this, &offset](auto entry){
            m_raw_matrix[offset] = entry;
            offset++;
        });
    });
}

template<typename EntryType, class Allocator>
void Matrix<EntryType, Allocator>::print() const {
    for (int y = 0; y < m_num_rows; y++) {
        for(int x = 0; x < m_num_cols; x++) {
            int64_t const entry = static_cast<int64_t>(m_raw_matrix[(y * m_num_cols) + x]);
            printf("%" PRId64 " ", entry);
        }
        printf("\n");
    }
}

template class Matrix<int8_t>;
template class Matrix<int16_t>;
template class Matrix<int32_t>;
template class Matrix<int>;

template class Matrix<uint8_t>;
template class Matrix<uint16_t>;
template class Matrix<uint32_t>;

}