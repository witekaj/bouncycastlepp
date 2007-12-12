// 
// File:   DerGeneralString.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on December 12, 2007, 9:34 AM
//

#ifndef _DERGENERALSTRING_H
#define	_DERGENERALSTRING_H

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      //using System;
      //using System.Text;
      
      class DerGeneralString : public DerStringBase {
      private:
        readonly string str;
        
      public:
        static DerGeneralString GetInstance(object obj) {
          if (obj == null || obj is DerGeneralString) {
            return (DerGeneralString) obj;
          }
          if (obj is Asn1OctetString) {
            return new DerGeneralString(((Asn1OctetString) obj).GetOctets());
          }
          if (obj is Asn1TaggedObject) {
            return GetInstance(((Asn1TaggedObject) obj).GetObject());
          }
          throw new ArgumentException("illegal object in GetInstance: " + obj.GetType().Name);
        }

        static DerGeneralString GetInstance(Asn1TaggedObject obj, bool explicitly) {
          return GetInstance(obj.GetObject());
        }

        DerGeneralString(byte[] str) : this(Encoding.ASCII.GetString(str, 0, str.Length)) {
        }

        DerGeneralString(string str) {
          if (str == null) {
            throw new ArgumentNullException("str");
          }
          this.str = str;
        }

        virtual string GetString() {
          return str;
        }

        byte[] GetOctets() {
          return Encoding.ASCII.GetBytes(str);
        }

      protected:
        virtual void Encode(DerOutputStream derOut) {
          derOut.WriteEncoded(Asn1Tags.GeneralString, GetOctets());
        }

        virtual bool Asn1Equals(Asn1Object asn1Object) {
          DerGeneralString other = asn1Object as DerGeneralString;
          if (other == null) {
            return false;
          }
          return this.str.Equals(other.str);
        }
      }
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _DERGENERALSTRING_H */

