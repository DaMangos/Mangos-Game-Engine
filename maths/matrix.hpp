// #pragma once
// #include <algorithm>
// #include <array>
// #include <cmath>
// #include <compare>
// #include <functional>
// #include <iterator>
// #include <type_traits>
// #include <vector>

// namespace maths
// {
// template <class arithmetic_type, std::size_t M, std::size_t N>
// requires std::is_arithmetic_v<arithmetic_type> and (M > 0) and (N > 0)
// class matrix final
// {
//   public:
//     typedef std::ptrdiff_t                        difference_type;
//     typedef std::size_t                           size_type;
//     typedef arithmetic_type                       value_type;
//     typedef value_type                           &reference;
//     typedef value_type const                     &const_reference;
//     typedef value_type                           *pointer;
//     typedef value_type const                     *const_pointer;
//     typedef value_type                           *iterator;
//     typedef value_type const                     *const_iterator;
//     typedef std::reverse_iterator<iterator>       reverse_iterator;
//     typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
//     typedef matrix<value_type, 1, N>              row_type;

//     static constexpr matrix<arithmetic_type, M, M> const identity = 1;

//     enum struct space
//     {
//       row,
//       column,
//       element
//     };

//     constexpr matrix(value_type value) noexcept requires(M == N)
//     : _elements()
//     {
//       for(size_type k = 0; k < column_size(); ++k)
//         (*this)(k, k) = value;
//     }

//     constexpr matrix(std::input_iterator auto first, std::input_iterator auto last) noexcept
//     : _elements()
//     {
//       assign(first, last);
//     }

//     constexpr matrix(std::initializer_list<value_type> values) noexcept
//     : _elements()
//     {
//       assign(values);
//     }

//     constexpr operator value_type() noexcept requires(M == N == 1)
//     {
//       return front();
//     }

//     template <size_type P>
//     constexpr matrix<value_type, M, P> operator*(matrix<value_type, N, P> const &other) const noexcept
//     {
//       matrix<value_type, M, P> output;
//       for(size_type i = 0; i < column_size(); ++i)
//         for(size_type j = 0; j < row_size(); ++j)
//           for(size_type k = 0; k < output.row_size(); ++k)
//             output(i, k) += (*this)(i, j) * other(j, k);
//       return output;
//     }

//     constexpr matrix operator*(value_type other) const noexcept
//     {
//       matrix output;
//       std::transform(begin(), end(), output.begin(), [&](value_type element) { return element * other; });
//       return output;
//     }

//     constexpr matrix operator/(value_type other) const noexcept
//     {
//       matrix output;
//       std::transform(begin(), end(), output.begin(), [&](value_type element) { return element / other; });
//       return output;
//     }

//     constexpr matrix operator+(matrix other) const noexcept
//     {
//       for(size_type k = 0; k < size(); ++k)
//         other[k] += (*this)[k];
//       return other;
//     }

//     constexpr matrix operator-(matrix other) const noexcept
//     {
//       for(size_type k = 0; k < size(); ++k)
//         other[k] -= (*this)[k];
//       return other;
//     }

//     constexpr matrix operator*=(matrix const &other) noexcept requires(M == N)
//     {
//       return *this = *this * other;
//     }

//     constexpr matrix operator*=(value_type const other) noexcept
//     {
//       return *this = *this * other;
//     }

//     constexpr matrix operator/=(value_type other) noexcept
//     {
//       return *this = *this / other;
//     }

//     constexpr matrix operator+=(matrix const &other) noexcept
//     {
//       return *this = *this + other;
//     }

//     constexpr matrix operator-=(matrix const &other) noexcept
//     {
//       return *this = *this - other;
//     }

//     constexpr void
//     assign_column(std::input_iterator auto first, std::input_iterator auto last, size_type column_to_assign) noexcept
//     {
//       std::copy_n(first,
//                   std::min(static_cast<size_type>(std::abs(std::distance(first, last))), column_size()),
//                   begin() + column_to_assign);
//     }

//     constexpr void assign(std::input_iterator auto first, std::input_iterator auto last) noexcept
//     {
//       std::copy_n(first, std::min(static_cast<size_type>(std::abs(std::distance(first, last))), size()), begin());
//     }

//     constexpr void assign(std::initializer_list<value_type> const &values) noexcept
//     {
//       std::copy_n(values.begin(),
//                   std::min(static_cast<size_type>(std::abs(std::distance(values.begin(), values.end()))), size()),
//                   begin());
//     }

//     constexpr void assign(std::initializer_list<matrix<value_type, M, 1>> const &values, space fill = space::columns)
//     noexcept
//     {
//       typename std::initializer_list<matrix<value_type, M, 1>>::iterator value = values.begin();
//       if(fill == space::rows)
//         for(size_type i = 0; i < column_size(); ++i, value++)
//           for(size_type j = 0; j < row_size() and value != values.end(); ++j)
//             if(j < column_size())
//               (*this)(i, j) = (*value)(j, 0);
//       if(fill == space::columns)
//         for(size_type j = 0; j < row_size(); ++j, value++)
//           for(size_type i = 0; i < column_size() and value != values.end(); ++i)
//             (*this)(i, j) = (*value)(i, 0);
//     }

//     constexpr void assign(std::initializer_list<matrix<value_type, 1, M>> const &values, space fill = space::columns)
//     noexcept
//     {
//       typename std::initializer_list<matrix<value_type, 1, M>>::iterator value = values.begin();
//       if(fill == space::rows)
//         for(size_type i = 0; i < column_size(); ++i, value++)
//           for(size_type j = 0; j < row_size() and value != values.end(); ++j)
//             (*this)(i, j) = (*value)(0, j);
//       if(fill == space::columns)
//         for(size_type j = 0; j < row_size(); ++j, value++)
//           for(size_type i = 0; i < column_size() and value != values.end(); ++i)
//             if(i < row_size())
//               (*this)(i, j) = (*value)(0, i);
//     }

//     constexpr iterator begin() noexcept
//     {
//       return iterator(data());
//     }

//     constexpr const_iterator begin() const noexcept
//     {
//       return const_iterator(data());
//     }

//     constexpr iterator end() noexcept
//     {
//       return iterator(begin() + size());
//     }

//     constexpr const_iterator end() const noexcept
//     {
//       return const_iterator(begin() + size());
//     }

//     constexpr reverse_iterator rbegin() noexcept
//     {
//       return reverse_iterator(end());
//     }

//     constexpr const_reverse_iterator rbegin() const noexcept
//     {
//       return const_reverse_iterator(end());
//     }

//     constexpr reverse_iterator rend() noexcept
//     {
//       return reverse_iterator(begin());
//     }

//     constexpr const_reverse_iterator rend() const noexcept
//     {
//       return const_reverse_iterator(begin());
//     }

//     constexpr const_iterator cbegin() const noexcept
//     {
//       return const_iterator(begin());
//     }

//     constexpr const_reverse_iterator crbegin() const noexcept
//     {
//       return const_reverse_iterator(end());
//     }

//     constexpr const_reverse_iterator crend() const noexcept
//     {
//       return const_reverse_iterator(begin());
//     }

//     constexpr row_iterator row_begin() noexcept
//     {
//       return row_iterator(data());
//     }

//     constexpr row_const_iterator row_begin() const noexcept
//     {
//       return row_const_iterator(data());
//     }

//     constexpr row_iterator row_end() noexcept
//     {
//       return row_iterator(row_begin() + row_size());
//     }

//     constexpr row_const_iterator row_end() const noexcept
//     {
//       return row_const_iterator(row_begin() + row_size());
//     }

//     constexpr row_reverse_iterator row_rbegin() noexcept
//     {
//       return row_reverse_iterator(row_end());
//     }

//     constexpr row_const_reverse_iterator row_rbegin() const noexcept
//     {
//       return row_const_reverse_iterator(row_end());
//     }

//     constexpr row_reverse_iterator row_rend() noexcept
//     {
//       return row_reverse_iterator(row_begin());
//     }

//     constexpr row_const_reverse_iterator row_rend() const noexcept
//     {
//       return row_const_reverse_iterator(row_begin());
//     }

//     constexpr row_const_iterator row_cbegin() const noexcept
//     {
//       return row_const_iterator(row_begin());
//     }

//     constexpr row_const_reverse_iterator row_crbegin() const noexcept
//     {
//       return row_const_reverse_iterator(row_end());
//     }

//     constexpr row_const_reverse_iterator row_crend() const noexcept
//     {
//       return row_const_reverse_iterator(row_begin());
//     }

//     constexpr size_type size() const noexcept
//     {
//       return column_size() * row_size();
//     }

//     constexpr size_type column_size() const noexcept
//     {
//       return M;
//     }

//     constexpr size_type row_size() const noexcept
//     {
//       return N;
//     }

//     constexpr size_type max_size() const noexcept
//     {
//       return size();
//     }

//     constexpr bool empty() const noexcept
//     {
//       return false;
//     }

//     constexpr reference operator[](size_type k) noexcept
//     {
//       return begin()[k];
//     }

//     constexpr const_reference operator[](size_type k) const noexcept
//     {
//       return begin()[k];
//     }

//     constexpr reference operator()(size_type i, size_type j) noexcept
//     {
//       return begin()[j + i * row_size()];
//     }

//     constexpr const_reference operator()(size_type i, size_type j) const noexcept
//     {
//       return begin()[j + i * row_size()];
//     }

//     constexpr reference at(size_type k)
//     {
//       if(k >= size())
//         throw std::out_of_range("matrix::at");
//       return (*this)[k];
//     }

//     constexpr const_reference at(size_type k) const
//     {
//       if(k >= size())
//         throw std::out_of_range("matrix::at");
//       return (*this)[k];
//     }

//     constexpr reference at(size_type i, size_type j)
//     {
//       if(j + i * row_size() >= size())
//         throw std::out_of_range("matrix::at");
//       return (*this)(i, j);
//     }

//     constexpr const_reference at(size_type i, size_type j) const
//     {
//       if(j + i * row_size() >= size())
//         throw std::out_of_range("matrix::at");
//       return (*this)(i, j);
//     }

//     constexpr reference front()
//     {
//       return (*this)[0];
//     }

//     constexpr const_reference front() const
//     {
//       return (*this)[0];
//     }

//     constexpr reference back()
//     {
//       return (*this)[size() - 1];
//     }

//     constexpr const_reference back() const
//     {
//       return (*this)[size() - 1];
//     }

//     constexpr pointer data() noexcept
//     {
//       return _elements;
//     }

//     constexpr const_pointer data() const noexcept
//     {
//       return _elements;
//     }

//     constexpr void fill(value_type value)
//     {
//       std::generate(begin(), end(), [&]() { return value; });
//     }

//     constexpr void swap(matrix &other) noexcept
//     {
//       std::swap(_elements, other._elements);
//     }

//     constexpr void swap_rows(size_type u, size_type v) requires(M > 1)
//     {
//       for(size_type i = 0; i < row_size(); ++i)
//         std::swap(at(i, u), at(i, v));
//     }

//     constexpr void swap_columns(size_type u, size_type v) requires(N > 1)
//     {
//       for(size_type j = 0; j < column_size(); ++j)
//         std::swap(at(u, j), at(v, j));
//     }

//     [[nodiscard]]
//     constexpr transposed_type transpose() const noexcept
//     {
//       transposed_type output;
//       for(size_type i = 0; i < column_size(); ++i)
//         for(size_type j = 0; j < row_size(); ++j)
//           output(j, i) = (*this)(i, j);
//       return output;
//     }

//     [[nodiscard]]
//     constexpr matrix row_echelon() const noexcept
//     {
//       matrix output = *this;
//       for(size_type k = 0; k < column_size(); ++k)
//       {
//         for(size_type i = k; output(k, k) == 0; ++i)
//         {
//           if(i == column_size())
//           {
//             ++k;
//             break;
//           }
//           if(output(i, k) != 0)
//           {
//             output.swap_rows(k, i);
//             break;
//           }
//         }
//         for(size_type i = k + 1; i < column_size(); ++i)
//         {
//           value_type u = output(i, k) / output(k, k);
//           for(size_type j = 0; j < row_size(); ++j)
//             output(i, j) -= u * output(k, j);
//         }
//       }
//       return output;
//     }

//     [[nodiscard]]
//     constexpr matrix reduced_row_echelon() const noexcept
//     {
//       matrix output = *this;
//       for(size_type k = 0; k < column_size(); ++k)
//       {
//         for(size_type i = k; output(k, k) == 0; ++i)
//         {
//           if(i == column_size())
//           {
//             ++k;
//             break;
//           }
//           if(output(i, k))
//           {
//             output.swap_rows(k, i);
//             break;
//           }
//         }
//         for(size_type i = 0; i < column_size() and k < column_size(); ++i)
//           if(i == k)
//           {
//             value_type u = output(k, k);
//             for(size_type j = 0; j < row_size(); ++j)
//               output(i, j) /= u;
//           }
//           else
//           {
//             value_type u = output(i, k) / output(k, k);
//             for(size_type j = 0; j < row_size(); ++j)
//               output(i, j) -= u * output(k, j);
//           }
//       }
//       return output;
//     }

//     [[nodiscard]]
//     constexpr matrix inverse() const noexcept requires(M == N)
//     {
//       matrix input  = *this;
//       matrix output = identity;
//       for(size_type k = 0; k < column_size(); ++k)
//       {
//         for(size_type i = k; input(k, k) == 0; ++i)
//         {
//           if(i == column_size())
//             return matrix(0);
//           if(input(i, k) != 0)
//           {
//             input.swap_rows(k, i);
//             output.swap_rows(k, i);
//             break;
//           }
//         }
//         for(size_type i = 0; i < column_size() and k < column_size(); ++i)
//         {
//           if(i == k)
//           {
//             value_type u = input(k, k);
//             for(size_type j = 0; j < column_size(); ++j)
//             {
//               input(i, j) /= u;
//               output(i, j) /= u;
//             }
//           }
//           else
//           {
//             value_type u = input(i, k) / input(k, k);
//             for(size_type j = 0; j < column_size(); ++j)
//             {
//               input(i, j) -= u * input(k, j);
//               output(i, j) -= u * output(k, j);
//             }
//           }
//         }
//       }
//       return output;
//     }

//     [[nodiscard]]
//     constexpr matrix normalize() const noexcept requires(N == 1)
//     {
//       return *this / length();
//     }

//     [[nodiscard]]
//     constexpr value_type trace() const noexcept requires(M == N)
//     {
//       value_type output = 1;
//       for(size_type k = 0; k < column_size(); ++k)
//         output *= (*this)(k, k);
//       return output;
//     }

//     [[nodiscard]]
//     constexpr value_type det() const noexcept requires(M == N)
//     {
//       matrix     input  = *this;
//       value_type output = 1;
//       for(size_type k = 0; k < column_size(); ++k)
//       {
//         for(size_type i = k; input(k, k) == 0; ++i)
//         {
//           if(i == column_size())
//             return 0;
//           if(input(i, k) != 0)
//           {
//             input.swap_rows(k, i);
//             output *= -1;
//             break;
//           }
//         }
//         for(size_type i = k + 1; i < column_size(); ++i)
//         {
//           value_type u = input(i, k) / input(k, k);
//           for(size_type j = 0; j < column_size(); ++j)
//             input(i, j) -= u * input(k, j);
//         }
//         output *= input(k, k);
//       }
//       return output;
//     }

//     [[nodiscard]]
//     constexpr value_type dot(matrix const &other) const noexcept requires(N == 1)
//     {
//       return transpose() * other;
//     }

//     [[nodiscard]]
//     constexpr value_type length_squared() const noexcept requires(N == 1)
//     {
//       return dot(*this);
//     }

//     [[nodiscard]]
//     constexpr value_type length() const noexcept requires(N == 1)
//     {
//       return std::sqrt(length_squared());
//     }

//     [[nodiscard]]
//     constexpr value_type angle(matrix const &other) const noexcept requires(N == 1)
//     {
//       return std::acos(dot(other) / (length() * other.length()));
//     }

//     matrix() = default;

//     constexpr std::strong_ordering operator<=>(matrix const &other) const noexcept = default;

//   private:
//     value_type _elements[M * N];
// };
// }