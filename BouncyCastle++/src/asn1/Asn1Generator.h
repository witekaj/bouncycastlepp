// 
// File:   ASN1Generator.h
// Author: watsug
//
// Created on November 23, 2007, 8:52 AM
//

#ifndef _ASN1GENERATOR_H
#define	_ASN1GENERATOR_H

//using System.IO;

namespace Org {
  namespace BouncyCastle {
    namespace Asn1 {
      
      public abstract class Asn1Generator {
      private:
        Stream _out;

      protected:
        Asn1Generator(Stream outStream) {
          _out = outStream;
        }

      Stream Out {
        get { return _out; }
      }

      public:
        virtual Stream GetRawOutputStream() = 0;
      }
      
    } //namespace Asn1
  } //namespace BouncyCastle
} //namespace Org


#endif	/* _ASN1GENERATOR_H */

