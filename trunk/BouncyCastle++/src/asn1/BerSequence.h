// 
// File:   BerSequence.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 11:51 AM
//

#ifndef _BERSEQUENCE_H
#define	_BERSEQUENCE_H

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      
      class BerSequence : public DerSequence {
      public:
        /**
         * create an empty sequence
         */
        BerSequence() {
        }

        /**
         * create a sequence containing one object
         */
        BerSequence(Asn1Encodable obj) : base(obj) {
        }

        BerSequence(params Asn1Encodable[] v) : base(v) {
        }

        /**
         * create a sequence containing a vector of objects.
         */
        BerSequence(Asn1EncodableVector v) : base(v) {
        }

        /*
         */
        virtual void Encode(DerOutputStream derOut) {
          if (derOut is Asn1OutputStream || derOut is BerOutputStream) {
            derOut.WriteByte(Asn1Tags.Sequence | Asn1Tags.Constructed);
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



#endif	/* _BERSEQUENCE_H */

