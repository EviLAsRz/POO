
#ifndef CADENA_HPP
#define CADENA_HPP

#include <iterator> 


class Cadena
{

public:

	// Constructores 

	explicit Cadena(size_t t = 0 , char s = ' ') ; // Consctuctor boss  
	Cadena(const Cadena& cad) ; // Constructor copia 
	Cadena(const char* cad ) ; // Constructor cad 
	Cadena(const Cadena& cad , size_t i ,size_t t) ; // Consctuctor de substr
	Cadena(Cadena&& cad) ;  // Constructor movieminto

	//Operadores && Sobrecargas

	Cadena& operator =(Cadena&& cad) ; //  Aisgnacion en moviento 
	Cadena& operator=(const Cadena& cad) ; 
	Cadena& operator=(const char* cad) ; 
	Cadena& operator+=(const Cadena& cad) ; 
	Cadena substr(size_t i , size_t t) const  ; 
	char operator[](size_t t) const noexcept;
	char& operator[](size_t t) noexcept; 
	char at(size_t t) const ;
	char& at(size_t t) ;
	
	// Metodo de conversion
	const char* c_str()const ;

	// Metodo Destructor

	~Cadena() ; 

	//Metodo Observador

	size_t length() const noexcept  ;


	// Iteradores

	typedef char* iterator ; 
	typedef const char* const_iterator ; 
	typedef std::reverse_iterator<iterator> reverse_iterator ;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator ;


	iterator begin() { return s_ ;}
	const_iterator begin() const { return cbegin();  } // return s_
	const_iterator cbegin() const { return s_;}
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const {return crbegin() ; }
	const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }

	iterator end() { return s_ + tam_ ; }
	const_iterator end() const {return cend(); } // return s_+ tam_
	const_iterator cend() const { return s_ + tam_ ; }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return crend(); }
	const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }




private:

	char* s_ ; 
	size_t tam_ ; 


};


	inline size_t Cadena::length() const noexcept{ return tam_ ; }

	
	Cadena operator+(const Cadena& cad1, const Cadena& cad2)  ;
	bool operator < (const Cadena& f1 , const Cadena& f2) ;
	bool operator > (const Cadena& f1 , const Cadena& f2) ;
	bool operator !=(const Cadena& f1 , const Cadena& f2) ;
	bool operator <=(const Cadena& f1 , const Cadena& f2) ;
	bool operator >=(const Cadena& f1 , const Cadena& f2) ;
	bool operator ==(const Cadena& f1 , const Cadena& f2) ;

	std::ostream& operator << (std::ostream& os, const Cadena& cad1) ; 
	std::istream& operator >> (std::istream& is, Cadena& cad1) ;

	/*** HASH ***/

namespace std {
  template <> struct hash<Cadena> {
    size_t operator()(const Cadena& cad) const
    {return hash<std::string>{}(cad.c_str());}
  };
}

#endif // CADENA_HPP