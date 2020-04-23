#pragma once

#include <vector>
#include <map>
#include <tuple>
#include <utility>

/**
 * @brief Шаблон класса для создания двумерной бесконечной разраяженной матрицы.
 * @tparam T - тип элемента матрыцы
 * @tparam defValues - значение элемента матрцы по умолчанию (для разряженной области)
 */
template<typename T, T defValues>
class Matrix
{
    using key = typename std::pair<size_t,size_t>;
    using matrix_map = typename std::map<key,T>;
    using iterMap =typename matrix_map::const_iterator;

    public:

    Matrix():map_matrix()
    {}
    ~Matrix() = default;
/**
 * @brief Внутренний (Proxy class) класс для предоставления временных объектов при вызове операции [] у объекта класса Matrix.
 */
    class Proxy 
    {
        public:
        Proxy() = default;
  
        Proxy(const Proxy&) = delete;
        Proxy& operator =(const Proxy&) = delete;        
        Proxy(Proxy&&) = delete;
        Proxy& operator =(Proxy&&) = delete;

        Proxy(const Matrix* matr, size_t index)
        {
            matrixRef = const_cast<Matrix*>(matr);
            _key.first=index;
        }

        auto& operator[] (int index) 
        {                        
            _key.second=index;
            return *this;
        }

        const auto& operator[] (int index) const
        {                        
            _key.second=index;
            return *this;
        }

        operator T() const
        {
            auto it = matrixRef->map_matrix.find(_key);
            if(it != matrixRef->map_matrix.end())
            {
                return matrixRef->map_matrix.at(_key);
            }
            return defValues;
        }

        template<typename Z>
        Proxy& operator=(Z&& value) 
        {
            auto Temp = std::forward<Z>(value);

            if(Temp != defValues) 
            {
                matrixRef->map_matrix[_key] = Temp;
                return *this;
            } 
            else 
            {                
                auto it = matrixRef->map_matrix.find(_key);
                if(it != matrixRef->map_matrix.end())
                {
                    matrixRef->map_matrix.erase(it);
                }
                return *this;
            }
        }


       friend std::ostream& operator<< (std::ostream &out,Proxy& prx)
        {

            out << prx.operator T();
 
            return out;
        }
                
        private:
        mutable key _key;
        Matrix*  matrixRef;
    };

        const auto operator[](size_t index) const
        {
            return Proxy(this, index);
        }

        auto operator[](size_t index)
        {
            return Proxy(this, index);
        }

    int size() const
    {
        return map_matrix.size();
    }

/**
 * @brief Внутренний класс итератора для итерирования (forward iterator).
 */
    class MyIterator: public std::iterator<std::forward_iterator_tag, iterMap> 
{
    public:
    MyIterator(const iterMap& ptr): _ptr(ptr)
    {

    }

    MyIterator(const MyIterator& other):_ptr(other._ptr)
    {

    }

    auto operator *() const
    {
        return std::make_tuple(_ptr->first.first,_ptr->first.second,_ptr->second);
    }

    bool operator!=(MyIterator const& other) const
    {
        return this->_ptr != other._ptr;
    }

    bool operator==(MyIterator const& other) const
    {
        return this->_ptr == other._ptr;
    }

    MyIterator& operator++()
    {
        ++_ptr;
        return *this;
    }

    private:
        iterMap _ptr;
};

    auto begin() const
    {
        return MyIterator (map_matrix.begin());
    }

    auto end() const
    {
        return MyIterator (map_matrix.end());
    }
    
     auto cbegin() const
    {
        return MyIterator (map_matrix.cbegin());
    }

    auto cend() const
    {
        return MyIterator (map_matrix.cend());
    }

    private:
    matrix_map map_matrix;
};


/**
 * @brief Шаблонная функция печати для класса Matrix.
 * @tparam T - тип элемента матрыцы
 * @tparam defValues - значение элемента матрцы по умолчанию (для разряженной области)
 */
template<typename T, T defValues>
void printMatrix(const Matrix<T,defValues>& matrix)
{
    std::cout << "Matrix size: " << matrix.size() << std::endl;

    for(int i = 1; i < 9; ++i)
    {
        for( int j = 1; j < 9; ++j)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }

    int x,y,v;
    for(const auto& c: matrix)
    {
        std::tie(x, y, v) = c;
        std::cout << "["<< x << "][" << y << "] = " << v << std::endl;
    }
}