// 
// File:   BerOctetStringParser.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 11:32 AM
//

#ifndef _BEROCTETSTRINGPARSER_H
#define	_BEROCTETSTRINGPARSER_H

//using System;
//using System.IO;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      using namespace org.bouncycastle.utilities.io;
  
      class BerOctetStringParser : public Asn1OctetStringParser {
      private:
        readonly Asn1ObjectParser _parser;
        
      public:
        BerOctetStringParser(Asn1ObjectParser parser) {
          _parser = parser;
        }

        Stream GetOctetStream() {
          return new ConstructedOctetStream(_parser);
        }

        Asn1Object ToAsn1Object() {
          try {
            return new BerOctetString(Streams.ReadAll(GetOctetStream()));
          } catch (IOException e) {
            throw new InvalidOperationException("IOException converting stream to byte array: " + e.Message, e);
          }
        }
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _BEROCTETSTRINGPARSER_H */

