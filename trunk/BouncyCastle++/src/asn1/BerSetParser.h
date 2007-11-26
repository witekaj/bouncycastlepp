// 
// File:   BerSetParser.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 12:05 PM
//

#ifndef _BERSETPARSER_H
#define	_BERSETPARSER_H

namespace org {
  namespace bouncycastle {
    namespace asn1 {

      class BerSetParser : public Asn1SetParser {
      private:
        readonly Asn1ObjectParser _parser;

      public:
        BerSetParser(Asn1ObjectParser parser) {
          this._parser = parser;
        }

        IAsn1Convertible ReadObject() {
          return _parser.ReadObject();
        }

        Asn1Object ToAsn1Object() {
          return new BerSet(_parser.ReadVector());
        }
      };

    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _BERSETPARSER_H */

