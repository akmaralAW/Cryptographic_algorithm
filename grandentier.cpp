#include "grandentier.hpp"

#include <algorithm>
#include <assert.h>
#include <iostream>

// Construct a LargeInteger from an unsigned integer
// Theta(1) since the size in bits of petier_entier is bounded by a constant
GrandEntier::GrandEntier(unsigned int petit_entier) {
  while (petit_entier != 0) {
    m_bits.push_back(petit_entier & 1);
    petit_entier = petit_entier >> 1;
  }

  assert(m_bits.empty() || m_bits.back());	// The strongest bit is always on
}
  
// Construct a Large integer from a vector of bits
// Theta(bits.size())
GrandEntier::GrandEntier(const std::vector<bool>& bits)
  : m_bits(bits)
{
  //Remove zeros at the highest positions. Ex: 00110 -> 110
  unsigned int taille = m_bits.size();
  while (taille > 0 && !m_bits[taille - 1]) {
    taille--;
  }
  m_bits.resize(taille);
  assert(m_bits.empty() || m_bits.back());	// The strongest bit is always on
}

// Copy builder
// Theta(n) where n is the number of bits
GrandEntier::GrandEntier(const GrandEntier& grand_entier)
  :m_bits(grand_entier.m_bits)
{
  assert(m_bits.empty() || m_bits.back());	// The strongest bit is always on
}

// Multiply the large dentures by 2 ^ shift. Works with positive or negative shift
// Worst case: Theta (n + shift) where n is the number of bits and shift > 0
// Best case: Theta (1) when shift = 0
void GrandEntier::shiftBits(int shift) {
  if (shift > 0) {
    if (!m_bits.empty()) {
      m_bits.insert(m_bits.begin(), shift, 0);
    }
  } else if (-shift >= m_bits.size()) {
    m_bits.clear();
  } else if (shift != 0) {
    m_bits.erase(m_bits.begin(), m_bits.begin() - shift);
  }
  assert(m_bits.empty() || m_bits.back());	// Le bit le plus fort est toujours allume
}

// Returns a binary representation of the number easy to display
// Theta (n) where n is the number of bits
std::string GrandEntier::toString() const {
  std::string resultat(m_bits.size(), 0);
  for (unsigned int i = 0; i < m_bits.size(); i++) {
    resultat[i] = (m_bits[m_bits.size() - i - 1] ? '1' : '0');
  }
  
  return resultat;
}

// Best case: Theta (1) when the two integers do not have the same number of bits
// Worst case: Theta (n) when the two integers have n bits and are equal
bool GrandEntier::operator==(const GrandEntier& grand_entier) const {
  return m_bits == grand_entier.m_bits;
}

// Time to add a number of n bits with a number of m bits: Theta (n + m)
GrandEntier GrandEntier::operator+(const GrandEntier& grand_entier) const {
  std::vector<bool> somme;
  unsigned int taille = std::max(grand_entier.m_bits.size(), m_bits.size());
  somme.reserve(taille + 1);
  bool retenue = false;
  for (unsigned int i = 0; i < taille; i++) {
    const bool bit_gauche = (i < m_bits.size()) && m_bits[i];
    const bool bit_droite = (i < grand_entier.m_bits.size()) && grand_entier.m_bits[i];
    somme.push_back(retenue ^ bit_gauche ^ bit_droite);
    retenue = (retenue && (bit_gauche || bit_droite)) || (bit_gauche && bit_droite);
  }
  if (retenue) {
    somme.push_back(true);
  }

  return somme;
}

// Time to subtract a number of n bits with a number of m bits: Theta (n + m)
GrandEntier GrandEntier::operator-(const GrandEntier& grand_entier) const {
  assert(m_bits.size() >= grand_entier.m_bits.size());
  
  std::vector<bool> difference;
  unsigned int taille = std::max(grand_entier.m_bits.size(), m_bits.size());
  difference.reserve(taille);
  bool emprun = false;
  for (unsigned int i = 0; i < taille; i++) {
    const bool bit_gauche = (i < m_bits.size()) && m_bits[i];
    const bool bit_droite = (i < grand_entier.m_bits.size()) && grand_entier.m_bits[i];
    difference.push_back(bit_gauche ^ emprun ^ bit_droite);
    emprun = (emprun && bit_droite) || ((emprun || bit_droite) && !bit_gauche);
  }

  return difference;
}
