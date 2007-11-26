// 
// File:   Asn1OctetStringParser.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 2:54 AM
//

#ifndef _ASN1OCTETSTRINGPARSER_H
#define	_ASN1OCTETSTRINGPARSER_H

using System.IO;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      
    	class Asn1OctetStringParser : public IAsn1Convertible {
      public:
        Stream GetOctetStream();
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org


#endif	/* _ASN1OCTETSTRINGPARSER_H */

