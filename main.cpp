//  Copyright © 2018 PRG_2. All rights reserved.

#include<iostream>
#include<stdexcept>
#include<algorithm>
#include<numeric>
#include<iterator>
#include"vector.cpp"

using namespace std;

int main() {
  Vector<int> vi {1,2,3,4,5};
  cout<<accumulate(vi.begin(), vi.end(), 0, [] (int sum, int elem) {return sum+elem;})<<'\n';
  
  Vector<string> vs {"a","bb","ccc"};
  vs.erase(find(vs.begin(), vs.end(), "bb"));
  for (auto& s : vs) s+="z";
  for (const auto& s : vs) cout<<s<<' ';
  cout<<'\n';
  
  // Why does the following statement work for vi, but not v_in?
  cout << *max_element(vi.begin(), vi.end()) << endl;
  
  // Print the smallest even number of vector vi
  Vector<int> even_temp;
  std::copy_if(vi.begin(), vi.end(),
               back_inserter(even_temp), [](int i){ return i%2 == 0; });
  auto min_even_numb = min_element(even_temp.begin(), even_temp.end(),
                                   [](const int& v1, const int& v2)
                                   { return v1 < v2; }
                                   );
  cout << "Smallest even number: " << *min_even_numb << endl;
  
  return 0;
}
