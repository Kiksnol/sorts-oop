#include <iostream>
#include <fstream>

template<typename Type>
void Swap(Type *A, Type *B)
{
  Type tmp = *A;

  *A = *B;
  *B = tmp;
}

template<typename Type>
void SortQ(Type *A, int N)
{
  int b = 0, e = N - 1;
  Type x;

  if (N < 2)
    return;

  x = A[N / 2];

  while (b <= e)
  {
    while (A[b] < x)
      b++;
    while (A[e] > x)
      e--;
    if (b <= e)
    {
      if (b != e)
        Swap(&A[b], &A[e]);
      b++;
      e--;
    }
  }

  SortQ(A, e + 1);
  SortQ(A + b, N - b);
}

struct arr
{
  double *A;
  int alen;
  std::fstream f;

  arr(void) : alen(0)
  {
    A = nullptr;
  }

  ~arr(void)
  {
    alen = 0;
    delete[] A;
  }

   arr( const arr &val )
   {
     if (A != nullptr)
       delete [] A, alen = 0;

     alen = val.alen;
     A = new double[val.alen];

     for (int i = 0; i < alen; i++)
       A[i] = val.A[i];
   }

   arr & operator =( const arr &val )
   {
     if (A != nullptr)
       delete [] A, alen = 0;

     alen = val.alen;
     A = new double[val.alen];

     for (int i = 0; i < alen; i++)
       A[i] = val.A[i];

     return *this;
   }

   arr & operator +(const arr &val)
   {
     if (this->A != nullptr)
     {
     int i;
     double *tmp;
     int tmplen = this->alen;

     tmp = new double[tmplen];
     memcpy(tmp, this->A, alen);

     delete[] this->A;

     this->A = new double[tmplen + val.alen];
     for (i = 0; i < tmplen; i++)
       this->A[i] = tmp[i];

     for (int j = 0, i = tmplen; i < tmplen + val.alen && j < val.alen; i++, j++)
       this->A[i] = val.A[j];

     delete[] tmp;

     return *this;
     }

   }

  void sort(void)
  {
    SortQ(A, alen);
  }

  void load(const std::string &FileName)
  {
    try
    {
      f.open(FileName, std::fstream::in);

      if (A != nullptr)
        delete[] A, A = nullptr;

      f >> this->alen;
      
      A = new double[this->alen];

      for (int i = 0; i < this->alen; i++)
        f >> A[i];

      f.close();
    }
    catch (std ::bad_alloc&)
    {
      f.close();
    }
    catch (...)
    {
      if (A != nullptr)
        delete[] A;

      f.close();
    }
  }

  void save(const std::string &FileName)
  {
    f.open(FileName, std::fstream::out);

    f << alen << std::endl;

    for (int i = 0; i < alen; i++)
      f << A[i] << std::endl;

    f.close();
  }

  void RandFill(const std::string &FileName, int Num)
  {
    f.open(FileName, std::fstream::out);

    f << Num << std::endl;

    for (int i = 0; i < Num; i++)
      f << rand() % Num + rand() % Num / (double)Num << std::endl;


    f.close();

    try
    {
      f.open(FileName, std::fstream::in);
      
      if (A != nullptr)
        delete[] A;

      f >> this->alen;

      A = new double[this->alen];

      for (int i = 0; i < this->alen; i++)
        f >> A[i];

      f.close();
    }
    catch (std::bad_alloc&)
    {
      f.close();
    }
    catch (...)
    {
      if (A != nullptr)
        delete[] A;

      f.close();
    }
  }
  
};

int main( void )
{
  arr f, f1, f2;

  f.RandFill("in.txt", 2);
  f.sort();
  f.save("res.txt");

  f1 = f;

  f2 = f1 + f;
}