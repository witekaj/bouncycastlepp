// 
// File:   Asn1Null.h
// Author: watsug
//
// Created on November 23, 2007, 12:59 PM
//

#ifndef _ASN1NULL_H
#define	_ASN1NULL_H

namespace Org {
  namespace BouncyCastle {
    namespace Asn1 {
      
      /**
       * A Null object.
       */
      class Asn1Null : public Asn1Object {
      public:
        Asn1Null() {
        }
    		virtual std::string ToString() {
          return "NULL";
        }        
      };

    } //namespace Asn1
  } //namespace BouncyCastle
} //namespace Org

#endif	/* _ASN1NULL_H */

