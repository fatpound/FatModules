module;

export module FatPound.Math.Matrix;

import FatPound.Math;

import <cassert>;

import std;

export namespace fatpound::math
{
    template <Number N>
    class Matrix final
    {
    public:
        Matrix(std::size_t row, std::size_t col)
            :
            row_count_(row),
            col_count_(col),
            matrix_(std::make_unique<N[]>(row_count_* col_count_))
        {

        }

        Matrix() = delete;
        Matrix(const Matrix& src)
            :
            row_count_(src.row_count_),
            col_count_(src.col_count_),
            matrix_(std::make_unique<N[]>(row_count_* col_count_))
        {
            std::copy(src.matrix_.get(), src.matrix_.get() + row_count_ * col_count_, matrix_.get());
        }
        Matrix& operator = (const Matrix& src)
        {
            if (this != std::addressof(src))
            {
                row_count_ = src.row_count_;
                col_count_ = src.col_count_;
                matrix_ = std::make_unique<N[]>(row_count_ * col_count_);

                std::copy(src.matrix_.get(), src.matrix_.get() + row_count_ * col_count_, matrix_.get());
            }

            return *this;
        }

        Matrix(Matrix&& src) noexcept
            :
            row_count_(std::exchange(src.row_count_, 0)),
            col_count_(std::exchange(src.col_count_, 0)),
            matrix_(std::exchange(src.matrix_, nullptr))
        {

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
        auto GetDeterminant() const -> N
        {
            if (row_count_ != col_count_)
            {
                throw std::runtime_error("The matrix is not a square matrix!");
            }

            if (row_count_ > 11)
            {
                throw std::runtime_error("The matrix's size is greater than 11 x 11 !\n"
                                        "Cannot perform this operation!");
            }

            N determinant = 0;

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
                        N prod = 1;

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
                    Matrix newm = MinorMatrix_(i, 0);

                    determinant += matrix_[i * col_count_] * newm.GetDeterminant() * (i % 2 == 0 ? 1 : -1);
                }
            }
            break;
            }

            return determinant;
        }
        auto GetValue(std::size_t row, std::size_t col) const -> N
        {
            return matrix_[row * col_count_ + col];
        }

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

            matrix_[row * col_count_ + col] = static_cast<N>(ddist(mrnd));
        }
        void FillValue(const N& value)
        {
            std::fill(matrix_.get(), matrix_.get() + row_count_ * col_count_, value);
        }
        void FillRand(const N& max_included)
        {
            std::minstd_rand mrnd(std::random_device{}());
            std::uniform_real_distribution<double> ddist(0.0, static_cast<double>(max_included));

            std::generate(
                matrix_.get(),
                matrix_.get() + row_count_ * col_count_,
                [&]() constexpr -> N
                {
                    return static_cast<N>(ddist(mrnd));
                }
            );
        }

        void Transpose()
        {
            assert(row_count_ > 0 && col_count_ > 0);

            Matrix<N> copy(*this);

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
        void Add(const Matrix& second)
        {
            assert(row_count_ == second.row_count_ && col_count_ == second.col_count_);

            for (std::size_t i = 0; i < row_count_ * col_count_; ++i)
            {
                matrix_[i] += second.matrix_[i];
            }
        }
        void Subtract(const Matrix& second)
        {
            assert(row_count_ == second.row_count_ && col_count_ == second.col_count_);

            for (std::size_t i = 0; i < row_count_ * col_count_; ++i)
            {
                matrix_[i] -= second.matrix_[i];
            }
        }
        void Multiply(const Matrix& second)
        {
            assert(col_count_ == second.row_count_);

            Matrix<N> temp(row_count_, second.col_count_);

            for (std::size_t i = 0; i < row_count_; ++i)
            {
                for (std::size_t k = 0; k < second.col_count_; ++k)
                {
                    N sum = 0;

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
        void MultiplyScalar(const N& k)
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


    public:
        auto operator [] (const std::size_t index) -> N
        {
            return matrix_[index % (row_count_ * col_count_)];
        }

        Matrix  operator +  (const Matrix& src)
        {
            return AddedMatrix_(src);
        }
        Matrix  operator -  (const Matrix& src)
        {
            return SubtractedMatrix_(src);
        }
        Matrix  operator *  (const Matrix& src)
        {
            return MultipliedMatrix_(src);
        }

        Matrix& operator += (const Matrix& src)
        {
            Add(src);

            return *this;
        }
        Matrix& operator -= (const Matrix& src)
        {
            Subtract(src);

            return *this;
        }
        Matrix& operator *= (const Matrix& src)
        {
            Multiply(src);

            return *this;
        }


    protected:


    private:
        Matrix AddedMatrix_(const Matrix& src) const
        {
            Matrix newm(*this);
            newm.Add(src);

            return newm;
        }
        Matrix SubtractedMatrix_(const Matrix& src) const
        {
            Matrix newm(*this);
            newm.Subtract(src);

            return newm;
        }
        Matrix MultipliedMatrix_(const Matrix& src) const
        {
            Matrix newm(*this);
            newm.Multiply(src);

            return newm;
        }
        Matrix TransposedMatrix_() const
        {
            Matrix newm(col_count_, row_count_);

            for (std::size_t j = 0; j < col_count_; ++j)
            {
                for (std::size_t i = 0; i < row_count_; ++i)
                {
                    newm.matrix_[j * row_count_ + i] = matrix_[i * col_count_ + j];
                }
            }

            return newm;
        }
        Matrix MinorMatrix_(std::size_t row, std::size_t col) const
        {
            Matrix newm(row_count_ - 1, col_count_ - 1);

            N x = 0;
            N y;

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
        Matrix AdjacentMatrix_() const
        {
            Matrix newm(row_count_, col_count_);

            for (std::size_t i = 0; i < row_count_; ++i)
            {
                for (std::size_t j = 0; j < col_count_; ++j)
                {
                    Matrix minor = MinorMatrix_(i, j);

                    newm.SetValue(i, j, minor.GetDeterminant() * ((i + j) % 2 == 0 ? 1 : -1));
                }
            }

            newm.Transpose();

            return newm;
        }
        Matrix InverseMatrix_() const
        {
            N det = GetDeterminant();

            if (det != 0 && det != std::numeric_limits<std::int64_t>::min())
            {
                Matrix newm = AdjacentMatrix_();

                newm.Multiply(1.0 / static_cast<double>(GetDeterminant()));

                return newm;
            }

            throw std::runtime_error("Could not apply inversion on the matrix!");
        }


    private:
        const std::size_t row_count_;
        const std::size_t col_count_;

        std::unique_ptr<N[]> matrix_ = nullptr;
    };
}