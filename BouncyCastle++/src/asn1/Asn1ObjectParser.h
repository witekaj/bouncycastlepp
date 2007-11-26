// 
// File:   ASN1ObjectParser.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 23, 2007, 1:05 PM
//

#ifndef _ASN1OBJECTPARSER_H
#define	_ASN1OBJECTPARSER_H


namespace org {
  namespace bouncycastle {
    namespace asn1 {
      //using namespace System;
      //using namespace System.IO;
  
    	class Asn1ObjectParser {
        private int _baseTag;
        private int _tagNumber;

        private Asn1StreamParser _aIn;

        internal Asn1ObjectParser(int baseTag, int tagNumber, Stream contentStream) {
          _baseTag = baseTag;
          _tagNumber = tagNumber;
          _aIn = new Asn1StreamParser(contentStream);
    		}

        /**
         * Return the tag number for this object.
         *
         * @return the tag number.
         */
        internal int TagNumber {
          get { return _tagNumber; }
        }

        internal int BaseTag {
          get { return _baseTag; }
        }

        internal IAsn1Convertible ReadObject() {
          return _aIn.ReadObject();
        }

        internal Asn1EncodableVector ReadVector() {
          Asn1EncodableVector v = new Asn1EncodableVector();
          try
          {
            IAsn1Convertible obj;
            while ((obj = ReadObject()) != null)
            {
              v.Add(obj.ToAsn1Object());
            }
          }
          catch (IOException e)
          {
            throw new InvalidOperationException(e.Message, e);
          }

          return v;
        }
    	};

    } //namespace asn1
  } //namespace bouncycastle
} //namespace org



#endif	/* _ASN1OBJECTPARSER_H */

