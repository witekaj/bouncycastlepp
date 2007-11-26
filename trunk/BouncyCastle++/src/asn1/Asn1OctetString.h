// 
// File:   Asn1OctetString.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 2:46 AM
//

#ifndef _ASN1OCTETSTRING_H
#define	_ASN1OCTETSTRING_H

//using System;
//using System.Collections;
//using System.IO;
//using System.Text;


namespace org {
  namespace bouncycastle {
    namespace asn1 {
      using namespace org.bouncycastle.utilities;
      using namespace org.bouncycastle.utilities.encoders;
      
      class Asn1OctetString : public Asn1Object, public Asn1OctetStringParser {
        internal byte[] str;

      public:
        /**
         * return an Octet string from a tagged object.
         *
         * @param obj the tagged object holding the object we want.
         * @param explicitly true if the object is meant to be explicitly
         *              tagged false otherwise.
         * @exception ArgumentException if the tagged object cannot
         *              be converted.
         */
        static Asn1OctetString GetInstance(Asn1TaggedObject	obj, bool explicitly) {
          return GetInstance(obj.GetObject());
        }

        /**
         * return an Octet string from the given object.
         *
         * @param obj the object we want converted.
         * @exception ArgumentException if the object cannot be converted.
         */
        static Asn1OctetString GetInstance(object obj) {
          if (obj == null || obj is Asn1OctetString) {
            return (Asn1OctetString)obj;
          }
          if (obj is Asn1TaggedObject) {
            return GetInstance(((Asn1TaggedObject)obj).GetObject());
          }
          if (obj is Asn1Sequence) {
            ArrayList v = new ArrayList();

            foreach (object o in ((Asn1Sequence) obj)) {
              v.Add(o);
            }
            return new BerOctetString(v);
          }
          throw new ArgumentException("illegal object in GetInstance: " + obj.GetType().Name);
        }

        /**
         * @param string the octets making up the octet string.
         */
        Asn1OctetString(byte[] str) {
          if (str == null) {
            throw new ArgumentNullException("str");
          }

          this.str = str;
        }

        Asn1OctetString(Asn1Encodable obj) {
          try {
            this.str = obj.GetDerEncoded();
          } catch (IOException e) {
            throw new ArgumentException("Error processing object : " + e.ToString());
          }
        }

        Stream GetOctetStream() {
          return new MemoryStream(str, false);
        }

        public Asn1OctetStringParser Parser {
          get { return this; }
        }

        public virtual byte[] GetOctets() {
          return str;
        }

      protected:          
        
        int Asn1GetHashCode() {
          byte[] b = GetOctets();
          int value = 0;
          for (int i = 0; i != b.Length; i++) {
            value ^= (b[i] & 0xff) << (i % 4);
          }
          return value;
        }

        bool Asn1Equals(Asn1Object asn1Object) {
          DerOctetString other = asn1Object as DerOctetString;
          if (other == null) {
            return false;
          }
          return Arrays.AreEqual(GetOctets(), other.GetOctets());
        }

      public:
        std::string ToString() {
          byte[] hex = Hex.Encode(str);
          return std::string("#") + Encoding.ASCII.GetString(hex, 0, hex.Length);
        }
      };
        
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _ASN1OCTETSTRING_H */

