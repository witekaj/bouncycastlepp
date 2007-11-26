// 
// File:   BerNull.h
// Author: watsug
//
// Created on November 26, 2007, 10:19 AM
//

#ifndef _BERNULL_H
#define	_BERNULL_H

//using System;

namespace Org {
  namespace BouncyCastle {
    namespace Asn1 {
      
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
      }
      
    } //namespace Asn1
  } //namespace BouncyCastle
} //namespace Org

#endif	/* _BERNULL_H */

