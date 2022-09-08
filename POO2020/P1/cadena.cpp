
#include "cadena.hpp"

#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <stdexcept>



Cadena::Cadena(size_t t , char s ):tam_(t)
{

	s_ = new char[tam_+1] ; 

	for(size_t i = 0 ; i < t ; ++i)
	{
		s_[i] = s ; 
	}

	s_[tam_] = '\0' ; 
}

Cadena::Cadena(const Cadena& cad):tam_(cad.tam_)
{
		s_ = new char[cad.tam_ + 1] ; 
	
		strcpy(s_,cad.s_) ; 
}

Cadena::Cadena(const char* cad)
{

	tam_ = strlen(cad) ; 

	s_ = new char[tam_+1] ;

	strcpy(s_,cad) ; 

}

Cadena::Cadena(Cadena&& cad):s_(cad.s_),tam_(cad.tam_) // Poner elementos no constantes 
{
	cad.s_ = nullptr ;  // Indicar vacio 

	cad.tam_ = 0 ; //  Tamaño a 0  . . . ~destruc() 
}


Cadena::Cadena(const Cadena& cad ,size_t emp, size_t t):tam_(t)
{
	 
    if(emp > cad.tam_ -1)
    {
    	throw std::out_of_range("Indice Fuera de rango") ; 
    }

    s_ = new char[t +1] ;

	size_t i, j = emp ;  

	for(i = 0 ; i < tam_ ; ++i) 
	{
		s_[i] = cad[j] ;

		j++ ; 
	}
	
 	s_[tam_] = '\0' ; 

}


Cadena Cadena::substr(size_t i , size_t t) const 
{
	size_t limite = i + t ; 

		if(limite >= length() || i > length() || limite < i)
		{
			throw std::out_of_range("Error.Fuera del rango") ; 
		}

	 
	return Cadena(*this , i, t ) ; 

} 

Cadena& Cadena::operator +=(const Cadena& cad)
{
	
	Cadena a(*this) ; 

	this->tam_ += cad.tam_ ; 

	delete[] this->s_ ; 

	this->s_ = new char [this->tam_ + 1] ;

	strcpy(this->s_,a.s_) ;

	strcat(this->s_,cad.s_) ; 

	return *this ; 

}

Cadena& Cadena::operator =(Cadena&& cad)
{
	
	s_= cad.s_ ; 

	tam_ = cad.tam_ ; 

	cad.s_ = nullptr ; 

	cad.tam_ = 0 ; 

	return *this ; 
}

Cadena operator+(const Cadena& cad1, const Cadena& cad2)
{
	return Cadena(cad1) += cad2 ;  
}

Cadena& Cadena::operator=(const Cadena& cad)
{
	
	if(this != &cad) 
	{

	this->tam_ = cad.tam_ ; 
	
	delete[] this->s_ ; 
	
	this->s_ = new char[ tam_ +1] ; 
	
	strcpy(this->s_,cad.s_) ;

	}
	
	return *this ; 
	
}

Cadena& Cadena::operator=(const char* cad)
{
	
	this->tam_ = strlen(cad) ;

	delete[] this->s_ ; 
	
	this->s_ = new char[ tam_ +1] ; 

	strcpy(this->s_,cad) ; 

	return *this ;
}

char Cadena::operator[](size_t t) const noexcept
{
	return s_[t] ;
}


char& Cadena::operator[](size_t t) noexcept
{
	return s_[t] ; 
}

char Cadena::at(size_t t) const 
{
	if(t >= tam_)
	{
		throw std::out_of_range("Error.Fuera de rango") ; 
	}

	return s_[t] ; 
}

char& Cadena::at(size_t t)  
{	
	
	if(t >= tam_)
	{
		throw std::out_of_range("Error.Fuera de rango") ; 
	}

	return s_[t] ; 
}

const char* Cadena::c_str() const 
{
	return s_ ; 
}


bool operator <(const Cadena& f1 , const Cadena& f2)
{
	return  strcmp(f1.c_str(),f2.c_str()) < 0 ;
}

bool operator >(const Cadena& f1 , const Cadena& f2)
{
	return f2 < f1 ;
}

bool operator ==(const Cadena& f1 , const Cadena& f2) 
{
	return strcmp(f1.c_str(),f2.c_str()) == 0 ; 
} 

bool operator !=(const Cadena& f1 , const Cadena& f2) 
{
	return !(f1 == f2) ; 
}

bool operator <=(const Cadena& f1 , const Cadena& f2)
{
	return (f1 == f2 || f1 < f2) ; 
}

bool operator >=(const Cadena& f1 , const Cadena& f2)
{
	return (f1 == f2 || f2 < f1) ; 
}


// Destructor 

Cadena::~Cadena()
{
	delete[] s_ ; 
}

std::ostream& operator << (std::ostream& os, const Cadena& cad1)
{
	os << cad1.c_str() ; 

	return os ; 
}



std::istream &operator>>(std::istream& is,Cadena& cad)
{
  
  size_t i = 0;
  char* s = new char[32];
  char a;
 
  while(isspace(is.get()) != 0 && i < 32)
  {
  	 i++ ;
  }

  is.unget();
 
  i = 0;
 
  while(!isspace(is.peek()) && i < 32 && is.good())
  {
    a = is.get() ; 
    s[i++] = a ;
  }
  	
  s[i]='\0';
  
  cad =Cadena(s);

  delete[] s;

  return is;
}