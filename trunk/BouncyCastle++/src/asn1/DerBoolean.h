// 
// File:   DerBoolean.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on December 12, 2007, 8:39 AM
//

#ifndef _DERBOOLEAN_H
#define	_DERBOOLEAN_H

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      //using System;
      
      class DerBoolean : public Asn1Object {
      private:
        readonly byte value;

      public:
        static readonly DerBoolean False = new DerBoolean(false);
        static readonly DerBoolean True  = new DerBoolean(true);

        /**
         * return a bool from the passed in object.
         *
         * @exception ArgumentException if the object cannot be converted.
         */
        static DerBoolean GetInstance(object obj) {
          if (obj == null || obj is DerBoolean) {
            return (DerBoolean) obj;
          }
          if (obj is Asn1OctetString) {
            return new DerBoolean(((Asn1OctetString) obj).GetOctets());
          }
          if (obj is Asn1TaggedObject) {
            return GetInstance(((Asn1TaggedObject) obj).GetObject());
          }
          throw new ArgumentException("illegal object in GetInstance: " + obj.GetType().Name);
        }

        /**
         * return a DerBoolean from the passed in bool.
         */
        static DerBoolean GetInstance(bool value) {
          return value ? True : False;
        }

        /**
         * return a Boolean from a tagged object.
         *
         * @param obj the tagged object holding the object we want
         * @param explicitly true if the object is meant to be explicitly
         *              tagged false otherwise.
         * @exception ArgumentException if the tagged object cannot
         *               be converted.
         */
        static DerBoolean GetInstance(Asn1TaggedObject obj, bool explicitly) {
          return GetInstance(obj.GetObject());
        }

      private:
        DerBoolean(byte[] value) {
          // TODO Are there any constraints on the possible byte values?
          this.value = value[0];
        }
        DerBoolean(bool value) {
          this.value = value ? (byte)0xff : (byte)0;
        }

      public:
        bool IsTrue {
          get { return value != 0; }
        }

      protected:
        virtual  void Encode(DerOutputStream derOut) {
          // TODO Should we make sure the byte value is one of '0' or '0xff' here?
          derOut.WriteEncoded(Asn1Tags.Boolean, new byte[]{ value });
        }

        virtual bool Asn1Equals(Asn1Object asn1Object) {
          DerBoolean other = asn1Object as DerBoolean;
          if (other == null) {
            return false;
          }
          return IsTrue == other.IsTrue;
        }

        virtual int Asn1GetHashCode() {
          return IsTrue.GetHashCode();
        }

      public:
        virtual string ToString() {
          return IsTrue ? "TRUE" : "FALSE";
        }
      }
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _DERBOOLEAN_H */

