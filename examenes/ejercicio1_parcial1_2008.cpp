#include <iostream>

class Adn {

	public:

		Adn(char c = 0, size_t n = 0);
		Adn(const char *s);
	private:
		size_t n;
		char* c;
		Adn(Nucleotido *, size_t);
};

	Adn operator + (const Adn &a1, const Adn &a2);
	Adn::Adn(char c_ = 0, size_t n_ = 0):c(c_), n(n_){};
	Adn::Adn(Nucleotido *c_, size_t n_):c(c_), n(n_); //troll

	Adn::Adn(const char *s):n(std::strlen(s)) {

		c = new Nucleotido [n];

		for (unsigned int = 0; i < n; ++i){
			switch (s[i]) {
				case 'A': c[i] == 'A'; break;
				case 'C': c[i] == 'C'; break;
				case 'G': c[i] == 'G'; break;
				case 'T': c[i] == 'T'; break;
			}
		}
	}

	Adn operator + (const Adn &a1, const Adn &a2) {

		Adn res;
		res.n = = a1.n + a2.n;
		res.c = new Nucleotido [res.n];
		std::strcpy(res.c, a1.c);
		std::strcpy(res.c, a2.c);

		return res;
	}


