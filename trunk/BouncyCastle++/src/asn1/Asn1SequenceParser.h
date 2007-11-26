// 
// File:   ASN1SequenceParser.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 3:10 AM
//

#ifndef _ASN1SEQUENCEPARSER_H
#define	_ASN1SEQUENCEPARSER_H

namespace Org {
  namespace BouncyCastle {
    namespace Asn1 {
	
      Asn1SequenceParser : public IAsn1Convertible {
        public:
        virtual IAsn1Convertible ReadObject() = 0;
      }
      
    } //namespace Asn1
  } //namespace BouncyCastle
} //namespace Org

#endif	/* _ASN1SEQUENCEPARSER_H */

