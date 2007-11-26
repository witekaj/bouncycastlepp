// 
// File:   Asn1OutputStream.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 2:56 AM
//

#ifndef _ASN1OUTPUTSTREAM_H
#define	_ASN1OUTPUTSTREAM_H

//using System.IO;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      
      class Asn1OutputStream : public DerOutputStream {
      public:
        Asn1OutputStream(Stream os) : base(os) {
        }

        void WriteObject(object obj) {
          if (obj == null) {
            WriteNull();
          } else if (obj is Asn1Object) {
            ((Asn1Object)obj).Encode(this);
          } else if (obj is Asn1Encodable) {
            ((Asn1Encodable)obj).ToAsn1Object().Encode(this);
          } else {
            throw new IOException("object not Asn1Encodable");
          }
        }
      }
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org



#endif	/* _ASN1OUTPUTSTREAM_H */

