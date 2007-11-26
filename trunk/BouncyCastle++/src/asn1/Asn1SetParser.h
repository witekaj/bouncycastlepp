// 
// File:   ASN1SetParser.h
// Author: watsug
//
// Created on November 26, 2007, 9:50 AM
//

#ifndef _ASN1SETPARSER_H
#define	_ASN1SETPARSER_H

namespace Org {
  namespace BouncyCastle {
    namespace Asn1 {
      
      class Asn1SetParser : public IAsn1Convertible {
      public:
        IAsn1Convertible ReadObject();
      }
      
    } //namespace Asn1
  } //namespace BouncyCastle
} //namespace Org

#endif	/* _ASN1SETPARSER_H */

