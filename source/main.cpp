#include "version_lib.h"
#include <iostream>
#include "matrix.h"


int main(int argc, char *argv[]) 
{
  const std::string ver = "-version";
  if ( argc > 1)
  {
    if (argv[1] == ver)     std::cout << "version: " << version_major()<< '.'<< version_minor() << '.' << version_patch() << std::endl;
    else                    std::cout << "Type: -version, if you want to known proramm version" << std::endl;    
  }
  
    
  try
  {
    Matrix<int,-1> matrix1;
    matrix1[4][3] = 99;
    ((matrix1[87][2] = 11)=-1)=33;

    int z = -1;
    matrix1[4][3] = z;

    auto size = matrix1.size();
    
    std::cout << "Matrix size = " << size << std::endl;

    int x,y,v;
    for(const auto& c: matrix1)
    {
      std::tie(x, y, v) = c;
      std::cout << "["<< x << "][" << y << "] = " << v << std::endl;
    }

    std::cout << std::endl;

    Matrix<int, 0> matrix2;
    int n=9;
    for(int i=0;i<=n;++i)
    {
        matrix2[i][i] = i;
        matrix2[i][n-i] = n-i;
    }

    const Matrix<int,1> matrix3;
    for(int i=0;i<=n;++i)
    {
        matrix3[i][i] = i;
        matrix3[i][n-i] = n-i;
    }

    printMatrix(matrix2);
    printMatrix(matrix3);

  }
  
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

    return 0;
}
