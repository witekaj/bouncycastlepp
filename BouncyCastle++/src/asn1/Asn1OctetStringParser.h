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

namespace Org {
  namespace BouncyCastle {
    namespace Asn1 {
      
    	class Asn1OctetStringParser : public IAsn1Convertible {
      public:
        Stream GetOctetStream();
      }
      
    } //namespace Asn1
  } //namespace BouncyCastle
} //namespace Org


#endif	/* _ASN1OCTETSTRINGPARSER_H */

