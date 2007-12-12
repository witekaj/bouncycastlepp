// 
// File:   DerEnumerated.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on December 12, 2007, 8:44 AM
//

#ifndef _DERENUMERATED_H
#define	_DERENUMERATED_H

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      //using namespace System;
      using namespace org.bouncycastle.math;
      using namespace org.bouncycastle.utilities;
      
    
      class DerEnumerated : public Asn1Object {
      private:
        readonly byte[] bytes;

        /**
         * return an integer from the passed in object
         *
         * @exception ArgumentException if the object cannot be converted.
         */
      public:
        static DerEnumerated GetInstance(object obj) {
          if (obj == null || obj is DerEnumerated) {
            return (DerEnumerated)obj;
          }
          if (obj is Asn1OctetString) {
            return new DerEnumerated(((Asn1OctetString)obj).GetOctets());
          }
          if (obj is Asn1TaggedObject) {
            return GetInstance(((Asn1TaggedObject)obj).GetObject());
          }
          throw new ArgumentException("illegal object in GetInstance: " + obj.GetType().Name);
        }

        /**
         * return an Enumerated from a tagged object.
         *
         * @param obj the tagged object holding the object we want
         * @param explicitly true if the object is meant to be explicitly
         *              tagged false otherwise.
         * @exception ArgumentException if the tagged object cannot
         *               be converted.
         */
        static DerEnumerated GetInstance(Asn1TaggedObject obj, bool explicitly) {
          return GetInstance(obj.GetObject());
        }

        DerEnumerated(int value) {
          bytes = BigInteger.ValueOf(value).ToByteArray();
        }

        DerEnumerated(BigInteger value) {
          bytes = value.ToByteArray();
        }

        DerEnumerated(byte[] bytes) {
          this.bytes = bytes;
        }

        BigInteger Value {
          get {
            return new BigInteger(bytes);
          }
        }

      protected:
        virtual void Encode(DerOutputStream derOut) {
          derOut.WriteEncoded(Asn1Tags.Enumerated, bytes);
        }

      protected:
        virtual bool Asn1Equals(Asn1Object asn1Object) {
          DerEnumerated other = asn1Object as DerEnumerated;
          if (other == null) {
            return false;
          }
          return Arrays.AreEqual(this.bytes, other.bytes);
        }

        virtual int Asn1GetHashCode() {
          return Value.GetHashCode();
        }
      }
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _DERENUMERATED_H */

