// 
// File:   ASN1SetParser.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 9:50 AM
//

#ifndef _ASN1SETPARSER_H
#define	_ASN1SETPARSER_H

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      
      class Asn1SetParser : public IAsn1Convertible {
      public:
        IAsn1Convertible ReadObject();
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _ASN1SETPARSER_H */

