#ifndef GRANDS_ENTIERS
#define GRANDS_ENTIERS

#include <string>
#include <vector>

class GrandEntier {
private:
  std::vector<bool> m_bits;
public:
  // Construct a LargeInteger from an unsigned integer
  GrandEntier(unsigned int petit_entier = 0);
  // Construct a Large integer from a vector of bits
  GrandEntier(const std::vector<bool>& bits);
  // Copy builder
  GrandEntier(const GrandEntier& grand_entier);

  std::string toString() const;	// Pour deboguer

  // Multiply the large integer by 2 ^ shift. Works with positive or negative shift
  void shiftBits(int shift);
  
  // Arithmetic operators
  bool operator==(const GrandEntier& grand_entier) const;
  GrandEntier operator+(const GrandEntier& grand_entier) const;
  GrandEntier operator-(const GrandEntier& grand_entier) const;
  GrandEntier operator*(const GrandEntier& grand_entier) const;
};

#endif
