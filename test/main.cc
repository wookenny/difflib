#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#define DIFFLIB_ENABLE_EXTERN_MACROS
#include <difflib.h>

DIFFLIB_INSTANTIATE_FOR_TYPE(std::string);
DIFFLIB_INSTANTIATE_FOR_TYPE(std::vector<std::string>);

struct Useless {};

static_assert(!difflib::is_standard_iterable<Useless>::value,"Check that Useless is not iterable");
static_assert(!difflib::is_hashable_sequence<Useless>::value,"Check that Useless is not a hashable sequence");

int main() {
  std::cout << difflib::is_hashable_sequence<std::string>::value << std::endl;
  std::cout << difflib::is_hashable_sequence< std::vector<std::string> >::value << std::endl;
  std::cout << difflib::is_hashable_sequence<Useless>::value << std::endl;
  
  std::string a = "test";
  std::string b = "test2";

  std::vector<std::string> va = {"1", "2", "3"};
  std::vector<std::string> vb = {"1", "4", "3"};

  auto foo = difflib::MakeSequenceMatcher(a,b);
  auto vfoo = difflib::MakeSequenceMatcher(va,vb);

  size_t a_i, b_i, size;
  a = " abcd"; b = "abcd abcd";
  foo.set_seq(a, b);
  std::tie(a_i, b_i, size) = foo.find_longest_match(0, 5, 0, 9);
  std::cout << "a=" << a_i << " b=" << b_i << " size=" << size << "\n";

  auto junk = [](char const& c) { return ' ' == c; };
  foo = difflib::MakeSequenceMatcher(a, b, junk);
  std::tie(a_i, b_i, size) = foo.find_longest_match(0, 5, 0, 9);
  std::cout << "a=" << a_i << " b=" << b_i << " size=" << size << "\n";
  a = "Gertrude Roger Sylvie Marcel Cunegonde";
  b = "Yvette Roger Andree Marcel Brigitte";

  std::cout<<"\na = "<<a<<"\nb = "<<b<<"\n";
  foo.set_seq(a,b);
  //foo = difflib::MakeSequenceMatcher(a, b);
 
  for(difflib::match_t const& m : foo.get_matching_blocks()) {
    size_t start1,start2,length;
    std::tie(start1,start2,length) = m;
    std::cout << start1 << " " << start2 << " " << length << "\n";
    std::cout << "  -> " << a.substr(0,start1)
                      << "("<<a.substr(start1,length)<< ")"
                      << a.substr(start1+length) << "\n";
    std::cout << "  -> " << b.substr(0,start2)
                      << "("<<b.substr(start2,length)<< ")"
                      << b.substr(start2+length) << "\n";
  }

  a = "Hello Roger";
  b = "Hello Peter";

  std::cout<<"\na = "<<a<<"\nb = "<<b<<"\n";
  foo.set_seq(a,b);
 
  for(difflib::match_t const& m : foo.get_matching_blocks()) {
    size_t start1,start2,length;
    std::tie(start1,start2,length) = m;
    std::cout << start1 << " " << start2 << " " << length << "\n";
    std::cout << "  -> " << a.substr(0,start1)
                      << "("<<a.substr(start1,length)<< ")"
                      << a.substr(start1+length) << "\n";
    std::cout << "  -> " << b.substr(0,start2)
                      << "("<<b.substr(start2,length)<< ")"
                      << b.substr(start2+length) << "\n";
  }

  std::cout<< "\nratio: " << foo.ratio() <<"\n";  
  std::cout << std::flush;
  return 0;
}
