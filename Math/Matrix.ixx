module;

export module FatPound.Math.Matrix;

import FatPound.Math;

import <cassert>;

import std;

export namespace fatpound::math
{
    template <Number T>
    class Matrix final
    {
    public:
        Matrix(std::int64_t row, std::int64_t col)
            :
            row_count_((assert(row > 0), static_cast<std::size_t>(row))),
            col_count_((assert(col > 0), static_cast<std::size_t>(col))),
            matrix_(std::make_unique<T[]>(row_count_* col_count_))
        {

        }

        Matrix() = delete;
        Matrix(const Matrix& src)
            :
            row_count_(src.row_count_),
            col_count_(src.col_count_),
            matrix_(std::make_unique<T[]>(row_count_* col_count_))
        {
            std::copy(src.matrix_.get(), src.matrix_.get() + row_count_ * col_count_, matrix_.get());
        }
        Matrix(Matrix&& src) noexcept
            :
            row_count_(std::exchange(src.row_count_, 0)),
            col_count_(std::exchange(src.col_count_, 0)),
            matrix_(std::exchange(src.matrix_, nullptr))
        {

        }
        Matrix& operator = (const Matrix& src)
        {
            if (this != std::addressof(src))
            {
                row_count_ = src.row_count_;
                col_count_ = src.col_count_;
                matrix_ = std::make_unique<T[]>(row_count_ * col_count_);

                std::copy(src.matrix_.get(), src.matrix_.get() + row_count_ * col_count_, matrix_.get());
            }

            return *this;
        }
        Matrix& operator = (Matrix&& src) noexcept
        {
            if (this != std::addressof(src))
            {
                row_count_ = std::exchange(src.row_count_, 0);
                col_count_ = std::exchange(src.col_count_, 0);
                matrix_ = std::move(src.matrix_);
            }

            return *this;
        }
        ~Matrix() noexcept = default;


    public:
        void Print() const
        {
            for (std::size_t i = 0; i < row_count_; ++i)
            {
                PrintRow(i);
            }

            std::cout << '\n';
        }
        void PrintRow(std::size_t row) const
        {
            for (std::size_t i = 0; i < col_count_; ++i)
            {
                std::cout << matrix_[row * col_count_ + i] << ' ';
            }

            std::cout << '\n';
        }
        void PrintColumn(std::size_t col) const
        {
            for (std::size_t j = 0; j < row_count_; ++j)
            {
                std::cout << matrix_[j * row_count_ + col] << '\n';
            }
        }

        void SetRand(std::size_t row, std::size_t col, std::size_t max_included)
        {
            std::minstd_rand mrnd(std::random_device{}());
            std::uniform_real_distribution<double> ddist(0.0, static_cast<double>(max_included));

            matrix_[row * col_count_ + col] = static_cast<T>(ddist(mrnd));
        }
        void FillValue(const T& value)
        {
            std::fill(matrix_.get(), matrix_.get() + row_count_ * col_count_, value);
        }
        void FillRand(const T& max_included)
        {
            std::minstd_rand mrnd(std::random_device{}());
            std::uniform_real_distribution<double> ddist(0.0, static_cast<double>(max_included));

            std::generate(
                matrix_.get(),
                matrix_.get() + row_count_ * col_count_,
                [&]() -> T
                {
                    return static_cast<T>(ddist(mrnd));
                }
            );
        }

        void Transpose()
        {
            assert(row_count_ > 0 && col_count_ > 0);

            Matrix<T> copy(*this);

            for (std::size_t i = 0; i < row_count_; ++i)
            {
                for (std::size_t j = 0; j < col_count_; ++j)
                {
                    matrix_[i * col_count_ + j] = copy.matrix_[j * row_count_ + i];
                }
            }

            std::swap(row_count_, col_count_);
        }
        void ConvertToUnit()
        {
            assert(row_count_ > 0 && row_count_ == col_count_);

            for (std::size_t i = 0; i < row_count_ * col_count_; i += row_count_)
            {
                matrix_[i] = 1;
                ++i;
            }
        }
        void Add(const Matrix<T>& second)
        {
            assert(row_count_ == second.row_count_ && col_count_ == second.col_count_);

            for (std::size_t i = 0; i < row_count_ * col_count_; ++i)
            {
                matrix_[i] += second.matrix_[i];
            }
        }
        void Subtract(const Matrix<T>& second)
        {
            assert(row_count_ == second.row_count_ && col_count_ == second.col_count_);

            for (std::size_t i = 0; i < row_count_ * col_count_; ++i)
            {
                matrix_[i] -= second.matrix_[i];
            }
        }
        void Multiply(const Matrix<T>& second)
        {
            assert(col_count_ == second.row_count_);

            Matrix<T> temp(row_count_, second.col_count_);

            for (std::size_t i = 0; i < row_count_; ++i)
            {
                for (std::size_t k = 0; k < second.col_count_; ++k)
                {
                    T sum = 0;

                    for (std::size_t j = 0; j < col_count_; ++j)
                    {
                        if (matrix_[i * col_count_ + j] != 0 && second.matrix_[j * second.col_count_ + k] != 0)
                        {
                            sum += matrix_[i * col_count_ + j] * second.matrix_[j * second.col_count_ + k];
                        }
                    }

                    temp.matrix_[i * temp.col_count_ + k] = sum;
                }
            }

            *this = std::move(temp);
        }
        void Multiply(const T& k)
        {
            if (k == 1)
            {
                return;
            }

            for (std::size_t i = 0; i < row_count_ * col_count_; ++i)
            {
                matrix_[i] *= k;
            }
        }

        T  GetDeterminant() const
        {
            if (row_count_ != col_count_)
            {
                throw std::runtime_error("The matrix is not a square matrix!");
            }

            if (row_count_ > 11)
            {
                throw std::runtime_error("The matrix's size is greater than 11 x 11 !");
            }

            T determinant = 0;

            switch (row_count_)
            {
            case 1:
            {
                determinant = matrix_[0];
            }
            break;

            case 2:
            {
                determinant = (matrix_[0] * matrix_[col_count_ + 1] - matrix_[1] * matrix_[col_count_]);
            }
            break;

            case 3:
            {
                for (std::size_t k = 0; k < 2; ++k)
                {
                    for (std::size_t i = 0; i < 3; ++i)
                    {
                        T prod = 1;

                        for (std::size_t j = 0; j < 3; ++j)
                        {
                            prod *= matrix_[((i + (k == 0 ? j : 2 - j)) % 3) * col_count_ + j];
                        }

                        determinant += prod * (k == 0 ? 1 : -1);
                    }
                }
            }
            break;

            default:
            {
                for (std::size_t i = 0; i < row_count_; ++i)
                {
                    Matrix<T> newm = MinorMatrix_(i, 0);

                    determinant += matrix_[i * col_count_] * newm.GetDeterminant() * (i % 2 == 0 ? 1 : -1);
                }
            }
            break;
            }

            return determinant;
        }
        T  GetValue(std::size_t row, std::size_t col) const
        {
            return matrix_[row * col_count_ + col];
        }

        T operator [] (const std::size_t index)
        {
            return matrix_[index % (row_count_ * col_count_)];
        }

        Matrix<T>  operator +  (const Matrix<T>& src)
        {
            return AddedMatrix_(src);
        }
        Matrix<T>  operator -  (const Matrix<T>& src)
        {
            return SubtractedMatrix_(src);
        }
        Matrix<T>  operator *  (const Matrix<T>& src)
        {
            return MultipliedMatrix_(src);
        }

        Matrix<T>& operator += (const Matrix<T>& src)
        {
            Add(src);

            return *this;
        }
        Matrix<T>& operator -= (const Matrix<T>& src)
        {
            Subtract(src);

            return *this;
        }
        Matrix<T>& operator *= (const Matrix<T>& src)
        {
            Multiply(src);

            return *this;
        }


    protected:


    private:
        Matrix<T> AddedMatrix_(const Matrix<T>& src) const
        {
            Matrix<T> newm(*this);
            newm.Add(src);

            return newm;
        }
        Matrix<T> SubtractedMatrix_(const Matrix<T>& src) const
        {
            Matrix<T> newm(*this);
            newm.Subtract(src);

            return newm;
        }
        Matrix<T> MultipliedMatrix_(const Matrix<T>& src) const
        {
            Matrix<T> newm(*this);
            newm.Multiply(src);

            return newm;
        }
        Matrix<T> TransposedMatrix_() const
        {
            Matrix<T> newm(col_count_, row_count_);

            for (std::size_t j = 0; j < col_count_; ++j)
            {
                for (std::size_t i = 0; i < row_count_; ++i)
                {
                    newm.matrix_[j * row_count_ + i] = matrix_[i * col_count_ + j];
                }
            }

            return newm;
        }
        Matrix<T> MinorMatrix_(std::size_t row, std::size_t col) const
        {
            Matrix<T> newm(row_count_ - 1, col_count_ - 1);

            T x = 0;
            T y;

            for (std::size_t i = 0; i < row_count_; ++i)
            {
                if (i == row)
                {
                    x = 1;
                    continue;
                }

                y = 0;

                for (std::size_t j = 0; j < col_count_; ++j)
                {
                    if (j == col)
                    {
                        y = 1;
                    }
                    else
                    {
                        newm.matrix_[(x == 1 ? i - 1 : i) * newm.col_count_ + (y == 1 ? j - 1 : j)] = matrix_[i * col_count_ + j];
                    }
                }
            }

            return newm;
        }
        Matrix<T> AdjacentMatrix_() const
        {
            Matrix<T> newm(row_count_, col_count_);

            for (std::size_t i = 0; i < row_count_; ++i)
            {
                for (std::size_t j = 0; j < col_count_; ++j)
                {
                    Matrix<T> minor = MinorMatrix_(i, j);

                    newm.SetValue(i, j, minor.GetDeterminant() * ((i + j) % 2 == 0 ? 1 : -1));
                }
            }

            newm.Transpose();

            return newm;
        }
        Matrix<T> InverseMatrix_() const
        {
            T det = GetDeterminant();

            if (det != 0 && det != std::numeric_limits<std::int64_t>::min())
            {
                Matrix<T> newm = AdjacentMatrix_();

                newm.Multiply(1.0 / static_cast<double>(GetDeterminant()));

                return newm;
            }

            return Matrix<T>();
        }


    private:
        const std::size_t row_count_;
        const std::size_t col_count_;

        std::unique_ptr<T[]> matrix_ = nullptr;
    };
}