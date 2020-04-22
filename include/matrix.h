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
    {

    }

    ~Matrix()
    {

    }

    // T Get(size_t x,size_t y) const
    // {
    //     key key(x,y);
    //     auto it = map_matrix.find(key);
    //     if(it != map_matrix.end())
    //     {
    //         return map_matrix.at(key);
    //     }
    //     return defValues;
    // }

/**
 * @brief Внутренний (Proxy class) класс для предоставления временных объектов при вызове операции [] у объекта класса Matrix.
 */
    class Proxy 
    {
        public:
        Proxy()
        {

        }
        Proxy(const Proxy&) = delete;
        Proxy& operator =(const Proxy&) = delete;        
        Proxy(Proxy&&) = delete;
        Proxy& operator =(Proxy&&) = delete;

        // Proxy(Matrix* matr, size_t index):matrixRef(matr)
        // {
        //     _key.first=index;
        // }

        Proxy(const Matrix* matr, size_t index)//:matirixRef(matr)
        {
            matrixRef = const_cast<Matrix*>(matr);
            // matr->size();
            // matrixRef = nullptr;
            _key.first=index;
        }

        auto& operator[] (int index) 
        {                        
            _key.second=index;
            return *this;
        }

        operator T() const
        {
            // if(!matrixRef) return defValues;
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
            //if(matrixRef==nullptr) return *this;
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

        // Proxy& operator = (const Proxy& prx) const
        // {
        //     this->matrixRef = prx.matrixRef;
        //     this->_key = prx._key;
        //     return *this;
        // }

       friend std::ostream& operator<< (std::ostream &out, const Proxy &prx)
        {
            // if (prx.matrixRef->getMap().find(prx._key) != prx.matrixRef->getMap().end())
            // {
            //     auto tmp = prx.matrixRef->getMap().at(prx._key);
            //     out << tmp;
            // }
            // else out << defValues;

            out << prx.operator T();
 
            return out;
        }
                
        private:
        key _key;
        Matrix*  matrixRef;
    };
   // private:
        // const matrix_map& getMap() const
        // {
        //     return map_matrix;
        // }
   // public:

        auto operator[](size_t index) const
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