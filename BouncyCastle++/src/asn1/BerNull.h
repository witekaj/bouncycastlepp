// 
// File:   BerNull.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 10:19 AM
//

#ifndef _BERNULL_H
#define	_BERNULL_H

//using System;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      
      /**
       * A Ber Null object.
       */
      class BerNull : DerNull {
      public:
        static new readonly BerNull Instance = new BerNull(0);

        //[Obsolete("Use static Instance object")]
        BerNull() {
        }

      private:
        BerNull(int dummy) : base(dummy) {
        }

      public:
        virtual void Encode(DerOutputStream derOut) {
          if (derOut is Asn1OutputStream || derOut is BerOutputStream) {
            derOut.WriteByte(Asn1Tags.Null);
          } else {
            base.Encode(derOut);
          }
        }
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _BERNULL_H */

