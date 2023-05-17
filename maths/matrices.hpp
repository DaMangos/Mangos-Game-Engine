
#include <compare>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <iterator>

//                 | a, b, c |
// maths::matrix = | d, e, f |
//                 | g, h, i |
//
// maths::matrix.elements = {a, b, c, d, e, f, g, h, i};
//
// maths::matrix.row_space() = {{a, b, c}, {d, e, f}, {g, h, i}};
//
// maths::matrix::column_space = {{a, d, g}, {b, e, h}, {c, f, i}};

namespace maths
{
template <class arithmetic_type, std::size_t column_size, std::size_t row_size, bool dummy>
requires std::integral<arithmetic_type> or std::floating_point<arithmetic_type>
class _undelying_array
{
    _undelying_array() = delete;
};

template <class arithmetic_type, std::size_t column_size, std::size_t row_size>
requires std::integral<arithmetic_type> or std::floating_point<arithmetic_type>
class matrix : public _undelying_array<arithmetic_type, column_size, row_size, true>
{
  public:
    typedef std::size_t                                      size_type;
    typedef std::ptrdiff_t                                   difference_type;
    typedef arithmetic_type                                  value_type;
    typedef arithmetic_type                                 &reference;
    typedef arithmetic_type const                           &const_reference;
    typedef arithmetic_type                                 *pointer;
    typedef arithmetic_type const                           *const_pointer;
    typedef arithmetic_type                                 *iterator;
    typedef arithmetic_type const                           *const_iterator;
    typedef std::reverse_iterator<iterator>                  reverse_iterator;
    typedef std::reverse_iterator<const_iterator>            const_reverse_iterator;
    typedef matrix<value_type, column_size, row_size>        matrix_type;
    typedef matrix<value_type, column_size, row_size>       &matrix_reference;
    typedef matrix<value_type, column_size, row_size> const &matrix_const_reference;
    typedef matrix<value_type, column_size, row_size>       *matrix_pointer;
    typedef matrix<value_type, column_size, row_size> const *matrix_const_pointer;
    typedef matrix<value_type, row_size, column_size>        transposed_matrix_type;
    typedef matrix<value_type, row_size, column_size>       &transposed_matrix_reference;
    typedef matrix<value_type, row_size, column_size> const &transposed_matrix_const_reference;
    typedef matrix<value_type, row_size, column_size>       *transposed_matrix_pointer;
    typedef matrix<value_type, row_size, column_size> const *transposed_matrix_const_pointer;
    typedef matrix<value_type, column_size, 1>               column_vector_type;
    typedef matrix<value_type, column_size, 1>              &column_vector_reference;
    typedef matrix<value_type, column_size, 1> const        &column_vector_const_reference;
    typedef matrix<value_type, column_size, 1>              *column_vector_pointer;
    typedef matrix<value_type, column_size, 1> const        *column_vector_const_pointer;
    typedef matrix<value_type, 1, row_size>                  row_vector_type;
    typedef matrix<value_type, 1, row_size>                 &row_vector_reference;
    typedef matrix<value_type, 1, row_size> const           &row_vector_const_reference;
    typedef matrix<value_type, 1, row_size>                 *row_vector_pointer;
    typedef matrix<value_type, 1, row_size> const           *row_vector_const_pointer;

    static constexpr matrix<value_type, column_size, column_size> const identity = 1;

    static constexpr bool const is_value_size            = column_size == row_size == 1;
    static constexpr bool const is_square_size           = column_size == row_size >= 2;
    static constexpr bool const is_rectangle_size        = column_size >= 2 and row_size >= 2;
    static constexpr bool const is_column_vector_size    = column_size >= 2 and row_size == 1;
    static constexpr bool const is_2D_column_vector_size = column_size == 2 and row_size == 1;
    static constexpr bool const is_3D_column_vector_size = column_size == 3 and row_size == 1;
    static constexpr bool const is_4D_column_vector_size = column_size == 4 and row_size == 1;
    static constexpr bool const is_row_vector_size       = column_size == 1 and row_size >= 2;
    static constexpr bool const is_2D_row_vector_size    = column_size == 1 and row_size == 2;
    static constexpr bool const is_3D_row_vector_size    = column_size == 1 and row_size == 3;
    static constexpr bool const is_4D_row_vector_size    = column_size == 1 and row_size == 4;

    enum struct space
    {
      column_space,
      row_space
    };

    template <class underling_pointer>
    requires std::same_as<underling_pointer, pointer> or std::same_as<underling_pointer, const_pointer>
    class column_iterator
    {
      public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef matrix::difference_type         difference_type;
        typedef matrix::value_type              value_type;
        typedef matrix::reference               reference;
        typedef matrix::const_reference         const_reference;
        typedef matrix::pointer                 pointer;
        typedef matrix::const_pointer           const_pointer;

        explicit constexpr column_iterator(underling_pointer pointer = nullptr) noexcept;

        constexpr reference                   operator*() noexcept;
        constexpr const_reference             operator*() const noexcept;
        constexpr pointer                     operator->() noexcept;
        constexpr const_pointer               operator->() const noexcept;
        constexpr reference                   operator[](size_type j) noexcept;
        constexpr const_reference             operator[](size_type j) const noexcept;
        constexpr iterator                   &operator++() noexcept;
        constexpr iterator                    operator++(int) noexcept;
        constexpr iterator                   &operator--() noexcept;
        constexpr iterator                    operator--(int) noexcept;
        constexpr iterator                   &operator+=(difference_type value) noexcept;
        constexpr iterator                   &operator-=(difference_type value) noexcept;
        friend constexpr iterator             operator+(iterator lhs, difference_type rhs) noexcept;
        friend constexpr iterator             operator+(difference_type lhs, iterator rhs) noexcept;
        friend constexpr iterator             operator-(iterator lhs, difference_type rhs) noexcept;
        friend constexpr iterator             operator-(difference_type lhs, iterator rhs) noexcept;
        friend constexpr std::strong_ordering operator<=>(iterator lhs, iterator rhs) noexcept = default;

      private:
        underling_pointer _underling_pointer;
    };

    template <class underling_matrix_reference>
    requires std::same_as<underling_matrix_reference, matrix_reference> or
             std::same_as<underling_matrix_reference, matrix_const_reference>
    class column_proxy
    {
      public:
        typedef matrix::size_type                      size_type;
        typedef matrix::difference_type                difference_type;
        typedef matrix::value_type                     value_type;
        typedef matrix::reference                      reference;
        typedef matrix::const_reference                const_reference;
        typedef matrix::pointer                        pointer;
        typedef matrix::const_pointer                  const_pointer;
        typedef column_iterator<matrix::pointer>       iterator;
        typedef column_iterator<matrix::const_pointer> const_iterator;
        typedef std::reverse_iterator<iterator>        reverse_iterator;
        typedef std::reverse_iterator<const_iterator>  const_reverse_iterator;

        column_proxy(underling_matrix_reference matrix);

        constexpr operator matrix<value_type, column_size, 1>() const noexcept;

        constexpr reference              operator[](size_type j) noexcept;
        constexpr const_reference        operator[](size_type j) const noexcept;
        constexpr reference              at(size_type j) noexcept;
        constexpr const_reference        at(size_type j) const noexcept;
        constexpr iterator               begin() noexcept;
        constexpr const_iterator         begin() const noexcept;
        constexpr iterator               end() noexcept;
        constexpr const_iterator         end() const noexcept;
        constexpr reverse_iterator       rbegin() noexcept;
        constexpr const_reverse_iterator rbegin() const noexcept;
        constexpr reverse_iterator       rend() noexcept;
        constexpr const_reverse_iterator rend() const noexcept;
        constexpr const_iterator         cbegin() const noexcept;
        constexpr const_iterator         cend() const noexcept;
        constexpr const_reverse_iterator crbegin() const noexcept;
        constexpr const_reverse_iterator crend() const noexcept;
        constexpr size_type              size() const noexcept;
        constexpr void                   fill(value_type value) const noexcept;

      private:
        underling_matrix_reference _underling_matrix;
    };

    template <class underling_matrix_reference>
    requires std::same_as<underling_matrix_reference, matrix_reference> or
             std::same_as<underling_matrix_reference, matrix_const_reference>
    class row_proxy
    {
      public:
        typedef matrix::size_type                     size_type;
        typedef matrix::difference_type               difference_type;
        typedef matrix::value_type                    value_type;
        typedef matrix::reference                     reference;
        typedef matrix::const_reference               const_reference;
        typedef matrix::pointer                       pointer;
        typedef matrix::const_pointer                 const_pointer;
        typedef matrix::iterator                      iterator;
        typedef matrix::const_iterator                const_iterator;
        typedef std::reverse_iterator<iterator>       reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        row_proxy(underling_matrix_reference matrix);

        constexpr operator matrix<arithmetic_type, 1, row_size>() const noexcept;

        constexpr reference              operator[](size_type j) noexcept;
        constexpr const_reference        operator[](size_type j) const noexcept;
        constexpr reference              at(size_type j) noexcept;
        constexpr const_reference        at(size_type j) const noexcept;
        constexpr iterator               begin() noexcept;
        constexpr const_iterator         begin() const noexcept;
        constexpr iterator               end() noexcept;
        constexpr const_iterator         end() const noexcept;
        constexpr reverse_iterator       rbegin() noexcept;
        constexpr const_reverse_iterator rbegin() const noexcept;
        constexpr reverse_iterator       rend() noexcept;
        constexpr const_reverse_iterator rend() const noexcept;
        constexpr const_iterator         cbegin() const noexcept;
        constexpr const_iterator         cend() const noexcept;
        constexpr const_reverse_iterator crbegin() const noexcept;
        constexpr const_reverse_iterator crend() const noexcept;
        constexpr size_type              size() const noexcept;
        constexpr void                   fill(value_type value) const noexcept;

      private:
        underling_matrix_reference _underling_matrix;
    };

    constexpr matrix() noexcept = default;
    constexpr matrix(value_type value) noexcept requires is_square_size;
    constexpr matrix(std::initializer_list<value_type> values) noexcept;
    constexpr matrix(std::initializer_list<column_vector_type> values) noexcept;
    constexpr matrix(std::initializer_list<row_vector_type> values) noexcept;

    constexpr operator value_type() const noexcept requires is_value_size;

    constexpr row_proxy<matrix_reference>          operator[](size_type i) noexcept;
    constexpr row_proxy<matrix_const_reference>    operator[](size_type i) const noexcept;
    constexpr row_proxy<matrix_reference>          at(size_type i);
    constexpr row_proxy<matrix_const_reference>    at(size_type i) const;
    constexpr reference                            at(size_type i, size_type j);
    constexpr const_reference                      at(size_type i, size_type j) const;
    constexpr column_proxy<matrix_reference>       at_column(size_type j);
    constexpr column_proxy<matrix_const_reference> at_column(size_type j) const;
    constexpr row_proxy<matrix_reference>          at_row(size_type i);
    constexpr row_proxy<matrix_const_reference>    at_row(size_type i) const;
    constexpr column_proxy<matrix_reference>       get_column(size_type j) noexcept;
    constexpr column_proxy<matrix_const_reference> get_column(size_type j) const noexcept;
    constexpr row_proxy<matrix_reference>          get_row(size_type i) noexcept;
    constexpr row_proxy<matrix_const_reference>    get_row(size_type i) const noexcept;

    constexpr iterator               begin() noexcept;
    constexpr const_iterator         begin() const noexcept;
    constexpr iterator               end() noexcept;
    constexpr const_iterator         end() const noexcept;
    constexpr reverse_iterator       rbegin() noexcept;
    constexpr const_reverse_iterator rbegin() const noexcept;
    constexpr reverse_iterator       rend() noexcept;
    constexpr const_reverse_iterator rend() const noexcept;
    constexpr const_iterator         cbegin() const noexcept;
    constexpr const_iterator         cend() const noexcept;
    constexpr const_reverse_iterator crbegin() const noexcept;
    constexpr const_reverse_iterator crend() const noexcept;

    constexpr void assign(std::initializer_list<value_type> values) noexcept;
    constexpr void assign(std::initializer_list<column_vector_type> values) noexcept;
    constexpr void assign(std::initializer_list<row_vector_type> values) noexcept;

    constexpr void                   fill(value_type value) noexcept;
    constexpr void                   swap(matrix_reference other) noexcept;
    constexpr size_type              size() const noexcept;
    constexpr matrix_type            row_echelon() const noexcept;
    constexpr matrix_type            reduced_row_echelon() const noexcept;
    constexpr transposed_matrix_type transpose() const noexcept;

    constexpr matrix_type inverse() const noexcept requires is_square_size;
    constexpr value_type  trace() const noexcept requires is_square_size;
    constexpr value_type  det() const noexcept requires is_square_size;

    constexpr matrix_type normalize() const noexcept requires is_column_vector_size;
    constexpr value_type  angle(matrix_const_reference other) const noexcept requires is_column_vector_size;
    constexpr value_type  dot(matrix_const_reference other) const noexcept requires is_column_vector_size;
    constexpr value_type  length_squared() const noexcept requires is_column_vector_size;
    constexpr value_type  length() const noexcept requires is_column_vector_size;

    constexpr value_type  phi() const noexcept requires is_column_vector_size and std::floating_point<value_type>;
    constexpr value_type  theta() const noexcept requires is_column_vector_size and std::floating_point<value_type>;
    constexpr matrix_type cross(matrix_const_reference other) const noexcept
      requires is_3D_column_vector_size and std::floating_point<value_type>;
};

template <class arithmetic_type, std::size_t column_size, std::size_t row_size>
requires std::integral<arithmetic_type> or std::floating_point<arithmetic_type>
class _undelying_array<arithmetic_type, column_size, row_size, true>
{
  public:
    typedef matrix<arithmetic_type, column_size, row_size> matrix;

    constexpr typename matrix::pointer       data() noexcept;
    constexpr typename matrix::const_pointer data() const noexcept;

  protected:
    constexpr _undelying_array() noexcept = default;

  private:
    typename matrix::value_type _elements[column_size * row_size] = {};
};

template <class arithmetic_type>
requires std::integral<arithmetic_type> or std::floating_point<arithmetic_type>
class _undelying_array<arithmetic_type, 4, 1, true>
{
  public:
    typedef matrix<arithmetic_type, 4, 1> matrix;

    constexpr typename matrix::pointer       data() noexcept;
    constexpr typename matrix::const_pointer data() const noexcept;

    typename matrix::value_type x = 0, y = 0, z = 0, w = 0;

  protected:
    constexpr _undelying_array() noexcept = default;
};

template <class arithmetic_type>
requires std::integral<arithmetic_type> or std::floating_point<arithmetic_type>
class _undelying_array<arithmetic_type, 3, 1, true>
{
  public:
    typedef matrix<arithmetic_type, 3, 1> matrix;

    constexpr typename matrix::pointer       data() noexcept;
    constexpr typename matrix::const_pointer data() const noexcept;

    typename matrix::value_type x = 0, y = 0, z = 0;

  protected:
    constexpr _undelying_array() noexcept = default;
};

template <class arithmetic_type>
requires std::integral<arithmetic_type> or std::floating_point<arithmetic_type>
class _undelying_array<arithmetic_type, 2, 1, true>
{
  public:
    typedef matrix<arithmetic_type, 2, 1> matrix;

    constexpr typename matrix::pointer       data() noexcept;
    constexpr typename matrix::const_pointer data() const noexcept;

    typename matrix::value_type x = 0, y = 0;

  protected:
    constexpr _undelying_array() noexcept = default;
};

template <class arithmetic_type>
requires std::integral<arithmetic_type> or std::floating_point<arithmetic_type>
class _undelying_array<arithmetic_type, 1, 1, true>
{
  public:
    typedef matrix<arithmetic_type, 1, 1> matrix;

    constexpr typename matrix::pointer       data() noexcept;
    constexpr typename matrix::const_pointer data() const noexcept;

    typename matrix::value_type x = 0;

  protected:
    constexpr _undelying_array() noexcept = default;
};
}