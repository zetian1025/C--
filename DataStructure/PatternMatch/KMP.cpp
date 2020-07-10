//Tests about [Algrothem KMP]
//In comparsion with the original [Brute-Force]
//The core of KMP is GetNext(string,string),[k = next[k]]
//Be careful,be smart.

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int Brute_Force(string s, string t);

void GetNext(int next[], string t);
int KMP(string s, string t);

int main()
{
  string s = "abcabcd";
  string t = "bcd";
  //   int pos = Brute_Force(s, t);
  int pos = KMP(s, t);
  if (pos == -1)
  {
    cout << "Not found." << endl;
  }
  else
  {
    cout << "[first]Position from " << pos + 1 << " to " << pos + t.length()
         << endl;
  }

  return 0;
}

int Brute_Force(string s, string t)
{
  for (int i = 0; i < s.length(); i++)
  {
    if (s[i] == t[0])
    {
      int j = 0;
      for (j = 0; j < t.length(); j++)
      {
        if (s[i + j] != t[j])
        {
          break;
        }
      }

      if (j == t.length())
      {
        return i;
      }
    }
  }
  return -1;
}

void GetNext(int next[], string s)
{
  int t = 0, k = -1;
  next[0] = -1;
  while (t < s.length() - 1)
  {
    if (k == -1 || s[t] == s[k])
    {
      t++;
      k++;
      if (s[t] == s[k])
      {
        next[t] = next[k];
      }
      else
      {
        next[t] = k;
      }
    }
    else
    {
      k = next[k];
    }
  }
}
int KMP(string s, string t)
{
  int next[t.length()];
  GetNext(next, t);

  int pos_s = 0, pos_t = 0;
  int len_s = s.length(),len_t = t.length();
  while (pos_s<len_s && pos_t<len_t)
  {
    if (pos_t == -1 || s[pos_s] == t[pos_t])
    {
      pos_t++;pos_s++;
    }
    else
    {
      pos_t = next[pos_t];
    }
  }
  if (pos_t == t.length()){
    return pos_s-pos_t;
  }
  else
  {
    return -1;
  }
  
}