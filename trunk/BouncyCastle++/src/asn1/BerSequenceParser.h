// 
// File:   BerSequenceParser.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 12:00 PM
//

#ifndef _BERSEQUENCEPARSER_H
#define	_BERSEQUENCEPARSER_H

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      
      class BerSequenceParser : public Asn1SequenceParser {
      private:
        readonly Asn1ObjectParser _parser;

      public:
        BerSequenceParser(Asn1ObjectParser parser) {
          this._parser = parser;
        }

        IAsn1Convertible ReadObject() {
          return _parser.ReadObject();
        }

        Asn1Object ToAsn1Object() {
          return new BerSequence(_parser.ReadVector());
        }
      };

    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _BERSEQUENCEPARSER_H */

