// 
// File:   ASN1SequenceParser.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 3:10 AM
//

#ifndef _ASN1SEQUENCEPARSER_H
#define	_ASN1SEQUENCEPARSER_H

namespace org {
  namespace bouncycastle {
    namespace asn1 {
	
      Asn1SequenceParser : public IAsn1Convertible {
        public:
        virtual IAsn1Convertible ReadObject() = 0;
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _ASN1SEQUENCEPARSER_H */

