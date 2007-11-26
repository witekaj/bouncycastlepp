// 
// File:   BerSet.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 12:02 PM
//

#ifndef _BERSET_H
#define	_BERSET_H

namespace org {
  namespace bouncycastle {
    namespace asn1 {

      class BerSet : public DerSet {
      public:
        /**
         * create an empty sequence
         */
        BerSet() {
        }

        /**
         * create a set containing one object
         */
        BerSet(Asn1Encodable obj) : base(obj) {
        }

        /**
         * create a set containing a vector of objects.
         */
        BerSet(Asn1EncodableVector v) : base(v, false) {
        }

        BerSet(Asn1EncodableVector v, bool needsSorting) : base(v, needsSorting) {
        }

        /*
         */
        virtual void Encode(DerOutputStream derOut) {
          if (derOut is Asn1OutputStream || derOut is BerOutputStream) {
            derOut.WriteByte(Asn1Tags.Set | Asn1Tags.Constructed);
            derOut.WriteByte(0x80);
            
            foreach (object o in this) {
              derOut.WriteObject(o);
            }
            derOut.WriteByte(0x00);
            derOut.WriteByte(0x00);
          } else {
            base.Encode(derOut);
          }
        }
      };

    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _BERSET_H */

