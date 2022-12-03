#pragma once
#include <Windows.h>
#include <tchar.h>
#include <sstream>

class IniFile
{
  LPCTSTR iniPath; // full ini path, valid during the use of Read/Write methods
public:
  typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>> Tstring;
  typedef std::basic_istringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>> Tistringstream;
  typedef std::basic_ostringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>> Tostringstream;

  IniFile(LPCTSTR _iniPath): iniPath(_iniPath) {}

  //bool Read(LPCTSTR sec, LPCTSTR key, LPTSTR str, DWORD sz, LPCTSTR def=_T("")) const
  //{
  //  return GetPrivateProfileString(sec, key, def, str, sz, iniPath)!=0;
  //}
  bool ReadVect(LPCTSTR sec, LPCTSTR key, std::vector<Tstring>& v) const
  {
    TCHAR cbuf[1024];
    GetPrivateProfileString(sec, key, _T(""), cbuf, sizeof(cbuf)/sizeof(cbuf[0]), iniPath);
    if(!cbuf[0]) return false;
    v.clear();
    Tstring str;
    Tistringstream is(cbuf);
    while(true)
    {
      is>>str;
      if(is.fail()) return false;
      v.push_back(str);
      if(is.eof()) break;
    }
    return true;
  }
  template<typename T> bool Read(LPCTSTR sec, LPCTSTR key, T& v, T vmin, T vmax) const
  {
    if(!Read(sec, key, v)) return false;
    if(v<vmin) v=vmin;
    else if(v>vmax) v=vmax;
    return true;
  }
  template<typename T> bool Read(LPCTSTR sec, LPCTSTR key, T& v) const
  {
    TCHAR cbuf[256];
    GetPrivateProfileString(sec, key, _T(""), cbuf, sizeof(cbuf)/sizeof(cbuf[0]), iniPath);
    if(!cbuf[0]) return false;
    Tistringstream is(cbuf);
    is>>v;
    return !is.fail();
  }

  bool Write(LPCTSTR sec, LPCTSTR key, LPCTSTR str) const { return WritePrivateProfileString(sec, key, str, iniPath); }
  template<typename T> bool Write(LPCTSTR sec, LPCTSTR key, T v) const
  {
    Tostringstream os;
    os<<v;
    return WritePrivateProfileString(sec, key, os.str().c_str(), iniPath);
  }
  bool WriteVect(LPCTSTR sec, LPCTSTR key, const std::vector<Tstring>& v) const
  {
    Tostringstream os;
    for(size_t i=0; i<v.size(); i++) os<<(i?" ":"")<<v[i];
    return WritePrivateProfileString(sec, key, os.str().c_str(), iniPath);
  }
};
