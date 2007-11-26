// 
// File:   Asn1OutputStream.h
// Author: watsug
//
// Created on November 26, 2007, 2:56 AM
//

#ifndef _ASN1OUTPUTSTREAM_H
#define	_ASN1OUTPUTSTREAM_H

//using System.IO;

namespace Org {
  namespace BouncyCastle {
    namespace Asn1 {
      
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
      
    } //namespace Asn1
  } //namespace BouncyCastle
} //namespace Org



#endif	/* _ASN1OUTPUTSTREAM_H */

