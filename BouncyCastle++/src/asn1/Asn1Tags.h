// 
// File:   Asn1Tags.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 10:10 AM
//

#ifndef _ASN1TAGS_H
#define	_ASN1TAGS_H

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      
      class Asn1Tags {
      public:
        static const int Boolean = 0x01;
        static const int Integer = 0x02;
        static const int BitString = 0x03;
        static const int OctetString = 0x04;
        static const int Null = 0x05;
        static const int ObjectIdentifier = 0x06;
        static const int External = 0x08;
        static const int Enumerated = 0x0a;
        static const int Sequence = 0x10;
        static const int SequenceOf = 0x10; // for completeness
        static const int Set = 0x11;
        static const int SetOf = 0x11; // for completeness

        static const int NumericString = 0x12;
        static const int PrintableString = 0x13;
        static const int T61String = 0x14;
        static const int VideotexString = 0x15;
        static const int IA5String = 0x16;
        static const int UtcTime = 0x17;
        static const int GeneralizedTime = 0x18;
        static const int GraphicString = 0x19;
        static const int VisibleString = 0x1a;
        static const int GeneralString = 0x1b;
        static const int UniversalString = 0x1c;
        static const int BmpString = 0x1e;
        static const int Utf8String = 0x0c;

        static const int Constructed = 0x20;
        static const int Application = 0x40;
        static const int Tagged = 0x80;
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org


#endif	/* _ASN1TAGS_H */

