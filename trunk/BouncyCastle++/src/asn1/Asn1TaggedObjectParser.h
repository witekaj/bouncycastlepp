// 
// File:   Asn1TaggedObjectParser.h
// Author: watsug
//
// Created on November 26, 2007, 10:09 AM
//

#ifndef _ASN1TAGGEDOBJECTPARSER_H
#define	_ASN1TAGGEDOBJECTPARSER_H

namespace Org {
  namespace BouncyCastle {
    namespace Asn1 {
      
    	class Asn1TaggedObjectParser : public IAsn1Convertible {
      public:
        int TagNo { get; }
        IAsn1Convertible GetObjectParser(int tag, bool isExplicit);
      }
      
    } //namespace Asn1
  } //namespace BouncyCastle
} //namespace Org

#endif	/* _ASN1TAGGEDOBJECTPARSER_H */

