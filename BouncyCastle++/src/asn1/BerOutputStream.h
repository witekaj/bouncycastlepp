// 
// File:   BerOutputStream.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 11:48 AM
//

#ifndef _BEROUTPUTSTREAM_H
#define	_BEROUTPUTSTREAM_H

//using System.IO;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      
      // TODO Make Obsolete in favour of Asn1OutputStream?
      class BerOutputStream : public DerOutputStream {
      public:
        BerOutputStream(Stream os) : base(os) {
        }

        virtual void WriteObject(object obj) {
          if (obj == null) {
            WriteNull();
          } else if (obj is Asn1Object) {
            ((Asn1Object)obj).Encode(this);
          } else if (obj is Asn1Encodable) {
            ((Asn1Encodable)obj).ToAsn1Object().Encode(this);
          } else {
            throw new IOException("object not BerEncodable");
          }
        }
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _BEROUTPUTSTREAM_H */

