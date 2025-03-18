//--------------------------------------------------------------
// The following code is supplied "as-is" and 
// is given without warranty of any kind. 
// It may be freely distributed and used. 
// The user holds author blameless from any complications or 
// problems that may arise from the use of this code.
//--------------------------------------------------------------
// Author: steveb
//--------------------------------------------------------------

#pragma once
#include <locale>
#include <sstream>
#include "Functions.h"

namespace convert
{
   enum EFmt
   {
      none,
      thou_sep,
      fraction,
   };

   namespace detail
   {
      inline void check_valid(const char* val)
      {
         std::locale loc (std::locale::empty(), std::locale::classic(), std::locale::numeric);
         auto ln = strlen(val);
         for(size_t i = 0; i < ln; ++i)
         {
            if(std::isalpha(val[i], loc))
               throw std::invalid_argument("alpha character found in convert::numeric_cast");
         }
      }

      inline std::string eval_fraction(const std::string& str, size_t pos)
      {
          std::stringstream ss;
          ss.setf(std::ios::fixed, std::ios::floatfield);
          std::string sWhole, sNom, sDenom;
          size_t nWhole = str.find(' ');
          double dResult = 0;

          if (nWhole == std::string::npos)
          {
              sNom = str.substr(0, pos);
              sDenom = str.substr(pos + 1, str.length() - 1);
              double dNom = atof(sNom.c_str());
              double dDenom = atof(sDenom.c_str());

              if (dDenom != 0)
                  dResult = dNom / dDenom;
          }
          else
          {
              sWhole = str.substr(0, nWhole);
              sNom = str.substr(nWhole, pos - nWhole);
              sDenom = str.substr(pos + 1, str.length() - 1);
              double dWhole = atof(sWhole.c_str());
              double dNom = atof(sNom.c_str());
              double dDenom = atof(sDenom.c_str());
              bool bNegative = false;
              if (dWhole < 0)
              {
                  dWhole = fabs(dWhole);
                  bNegative = true;
              }

              if (dDenom != 0)
                  dResult = dNom / dDenom + dWhole;

              if (bNegative)
                  dResult *= -1.0;
          }

          ss << dResult;
          return ss.str();
      }

      inline std::string prepare(const char* val, bool is_fract = false)
      {
         check_valid(val);
         std::string s;
         std::string sVal = val;
         size_t pos = is_fract ? sVal.find('/') : std::string::npos;
		 size_t coma = sVal.find(',');
         std::locale loc (std::locale::empty(), std::locale::classic(), std::locale::numeric);

         if(pos == std::string::npos)
         {
			 size_t i = 0;
			 if (val[i] == '-')
			 {
				 s = "-";
				 i++;
			 }
             auto ln = strlen(val);
            for(; i < ln; i++)
            {
               char c = val[i];
               if(std::isdigit(c, loc) || c == '.')
                  s += c;
			   else if (c == ',')
				   s += '.';
            }
         }
         else
             s = eval_fraction(sVal, pos);

         return s;
      }

      inline void to_thou_sep(std::string& val)
      {
         for(size_t point = 0, i = (val.find_last_of ('.') == -1 ? val.length() : val.find_last_of('.')); i > 0; --i, ++point) 
            if(point != 0 && point % 3 == 0)     
               val.insert(i, " ");     
      }

      template <typename T>
      inline void to_fract(const T& val, std::string& sRVal, double denominator)
      {
         double fract = 0;
         double wholeTmp = 0;
         double Val = (double)fabs((double)val);
         int whole = 0;
         bool bNeg = (val < 0);

         fract = modf(Val, &wholeTmp);
         whole = static_cast<int>(wholeTmp);
         double temp = fract / (1.0 / denominator);

         // sb 11/26/15 start
         // check that temp in an integer
         double intpart;
         double zero = modf(temp, &intpart);

         if (zero != 0.0)
         {
            // Numerator is not an integer
            std::stringstream ssE;
            ssE << "numerator is not an integer: " << temp;
            std::string err = ssE.str();
            throw std::runtime_error(err.c_str());
         }
         // sb 11/26/15 end 
         
         int numerator = static_cast<int>(temp);
         int denom = static_cast<int>(denominator);
         std::stringstream ss;
         if(numerator != 0)
            ss << whole << " " << numerator << "/" << denom;
         else
            ss << whole;

         sRVal = ss.str();
         if(bNeg)
            sRVal.insert(0, "-");
      }
   
      template <typename T> 
      inline T numeric_cast(const char* val, bool is_fraction = false)
      {
         T r = T();

         if(strlen(val) == 0)
            return r; // Do not bother

         std::stringstream ss;
         ss << detail::prepare(val, is_fraction);
         ss >> r;
         return r;
      }
   
      template <typename T>
      inline std::string string_cast(const T& val, std::streamsize prec, EFmt format, int denom)
      {
         std::string rVal;
         std::stringstream ss;
         ss.setf(std::ios::fixed, std::ios::floatfield);
         ss.precision(prec);     

         switch(format)
         {
         case thou_sep:
            ss << val;
            rVal = ss.str();
            to_thou_sep(rVal);
            break;
         case fraction:
            to_fract(val, rVal, denom);
            break;
         default:
            ss << val;
            rVal = ss.str();
           break;
         }
         return rVal;
      }
   } // detail
   
   // Numerics
   template <typename T> 
   inline T numeric_cast(const char* val, bool is_fraction = false)
   {
      return detail::numeric_cast<T>(val, is_fraction);
   }

   template <typename T> 
   inline T numeric_cast(std::wstring val, bool is_fraction = false)
   {
      return detail::numeric_cast<T>(WStringToString(val).c_str(), is_fraction);
   }

   template<typename T>
   inline std::string string_cast(const T val, std::streamsize prec=5, EFmt format=none, int denom=0)
   {
      return detail::string_cast<T>(val, prec, format, denom);
   }

   template<typename T>
   inline std::wstring wstring_cast(const T val, std::streamsize prec=5, EFmt format=none, int denom=0)
   {
      std::string rval = detail::string_cast<T>(val, prec, format, denom);
      return StringToWString(rval);
   }
};

 
