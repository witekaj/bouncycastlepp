// 
// File:   BerSequenceGenerator.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 11:57 AM
//

#ifndef _BERSEQUENCEGENERATOR_H
#define	_BERSEQUENCEGENERATOR_H

//using System.IO;

namespace org {
  namespace bouncycastle {
    namespace asn1 {


      class BerSequenceGenerator : public BerGenerator {
      public:
        BerSequenceGenerator(Stream outStream) : base(outStream) {
          WriteBerHeader(Asn1Tags.Constructed | Asn1Tags.Sequence);
        }

        BerSequenceGenerator(Stream outStream, int tagNo, bool isExplicit)
        : base(outStream, tagNo, isExplicit) {
          WriteBerHeader(Asn1Tags.Constructed | Asn1Tags.Sequence);
        }

        void AddObject(Asn1Object obj) {
          obj.Encode(new DerOutputStream(Out));
        }

        void Close() {
          WriteBerEnd();
        }
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _BERSEQUENCEGENERATOR_H */

