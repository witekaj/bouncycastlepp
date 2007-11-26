// 
// File:   Asn1Encodable.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 23, 2007, 2:29 AM
//

#ifndef _ASN1ENCODABLE_H
#define	_ASN1ENCODABLE_H

//using System.IO;

namespace org {
  namespace bouncycastle {
    namespace asn1 {

      class Asn1Encodable : IAsn1Convertible {

      public:
        static const char* Der;// = "DER";
        static const char* Ber;// = "BER";

        byte[] GetEncoded() {
                MemoryStream bOut = new MemoryStream();
                Asn1OutputStream aOut = new Asn1OutputStream(bOut);

          aOut.WriteObject(this);

          return bOut.ToArray();
        }

        byte[] GetEncoded(string encoding) {
          if (encoding.Equals(Der)) {
            MemoryStream bOut = new MemoryStream();
            DerOutputStream dOut = new DerOutputStream(bOut);
            dOut.WriteObject(this);
            return bOut.ToArray();
          }
          return GetEncoded();
        }

        /**
        * Return the DER encoding of the object, null if the DER encoding can not be made.
        *
        * @return a DER byte array, null otherwise.
        */
        byte[] GetDerEncoded() {
          try {
            return GetEncoded(Der);
          } catch (IOException) {
            return null;
          }
        }

        virtual int GetHashCode() {
          return ToAsn1Object().CallAsn1GetHashCode();
        }

        virtual bool Equals(object obj) {
          if (obj == this)
            return true;

          IAsn1Convertible other = obj as IAsn1Convertible;

          if (other == null)
            return false;

          Asn1Object o1 = ToAsn1Object();
          Asn1Object o2 = other.ToAsn1Object();

          return o1 == o2 || o1.CallAsn1Equals(o2);
        }

        public abstract Asn1Object ToAsn1Object();
        }
      };

    } //namespace asn1
  } //namespace bouncycastle
} //namespace org


#endif	/* _ASN1ENCODABLE_H */
