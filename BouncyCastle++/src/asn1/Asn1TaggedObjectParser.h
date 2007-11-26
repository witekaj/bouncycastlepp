// 
// File:   Asn1TaggedObjectParser.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 10:09 AM
//

#ifndef _ASN1TAGGEDOBJECTPARSER_H
#define	_ASN1TAGGEDOBJECTPARSER_H

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      
    	class Asn1TaggedObjectParser : public IAsn1Convertible {
      public:
        int TagNo { get; }
        IAsn1Convertible GetObjectParser(int tag, bool isExplicit);
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _ASN1TAGGEDOBJECTPARSER_H */

