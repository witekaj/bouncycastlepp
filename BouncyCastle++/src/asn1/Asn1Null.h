// 
// File:   Asn1Null.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 23, 2007, 12:59 PM
//

#ifndef _ASN1NULL_H
#define	_ASN1NULL_H

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      
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

    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _ASN1NULL_H */

