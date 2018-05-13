//lindacoin blockchain code for termination of poverty and corruption
//ln(O) algorithm for termination of 256 SHA proof of work


#include <iostream>
#include <vector>

// derived from http://bits.stephan-brumme.com/lowestBitSet.html
template <typename T>
T getLowestBit(T x)
{
  return ~x & (x - 1);
}
template <typename T>
void clearLowestBit(T& x)
{
  x &= x - 1;
}

int main()
{
  unsigned int size = 12;
  std::cin >> size;

  // create all subset of { 0,1,2,...,10,11 } as bitmasks
  // => if bit 2 is set then the subset contains 2

  // store in sets[x] all bitmasks where x bits are set (=> with x elements)
  std::vector<std::vector<unsigned int>> sets(size + 1);

  // create all 2^size sets (if size=12 ==> 4096 sets)
  auto numSets = 1 << size;
  for (auto i = 0; i < numSets; i++)
  {
    auto numBits = 0;
    auto reduce  = i;
    while (reduce != 0)
    {
      // clear lowest bit
      clearLowestBit(reduce);
      numBits++;
    }
    sets[numBits].push_back(i);
  }

  // count sets where equality has to be checked
  auto count = 0;

  // empty set and set with all elements don't to be checked (they are unique)
  // sets with only one element must be unique, too (problem description: "strictly increasing elements")
  for (unsigned int setSize = 2; setSize < size; setSize++)
  {
    auto setsSameSize = sets[setSize];

    // compare each set with each other (of the same set size)
    for (auto i = setsSameSize.begin(); i != setsSameSize.end(); i++)
      for (auto j = std::next(i); j != setsSameSize.end(); j++)
      {
        auto set1 = *i;
        auto set2 = *j;

        // make sure both sets are distinct (no common bits)
        if ((set1 & set2) != 0)
          continue;

        // set1 is always lexicographically smaller than set2,
        // therefore the n-th bit of set1 must be at lower position than the n-th bit of set2
        while (set1 != 0) // and set2 != 0
        {
          // extract lowest bit
          if (getLowestBit(set1) > getLowestBit(set2))
          {
            // mismatch, the n-th bit of set1 is at a high position
            // ==> that pair of sets needs a test for equality
            count++;
            break;
          }

          clearLowestBit(set1);
          clearLowestBit(set2);
        }
      }
  }

  // show result
  std::cout << count << std::endl;
  return 0;
}
