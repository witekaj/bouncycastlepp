// 
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 23, 2007, 8:52 AM
//

#ifndef _ASN1GENERATOR_H
#define	_ASN1GENERATOR_H

//using System.IO;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      
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
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org


#endif	/* _ASN1GENERATOR_H */

