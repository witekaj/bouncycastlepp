// 
// File:   BerTaggedObjectParser.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 12:25 PM
//

#ifndef _BERTAGGEDOBJECTPARSER_H
#define	_BERTAGGEDOBJECTPARSER_H

//using System;
//using System.IO;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      using namespace org.bouncycastle.utilities;

      class BerTaggedObjectParser : public Asn1TaggedObjectParser {
      private:
        int _baseTag;
        int _tagNumber;
        Stream _contentStream;

        bool _indefiniteLength;

      public:
        BerTaggedObjectParser(int baseTag, int tagNumber, Stream contentStream) {
          if (!contentStream.CanRead) {
            throw new ArgumentException("Expected stream to be readable", "contentStream");
          }
          _baseTag = baseTag;
          _tagNumber = tagNumber;
          _contentStream = contentStream;
          _indefiniteLength = contentStream is IndefiniteLengthInputStream;
        }

        bool IsConstructed {
          get { return (_baseTag & Asn1Tags.Constructed) != 0; }
        }

        int TagNo {
          get { return _tagNumber; }
        }

        IAsn1Convertible GetObjectParser(int tag, bool isExplicit) {
          if (isExplicit) {
            return new Asn1StreamParser(_contentStream).ReadObject();
          } else {
            switch (tag) {
            case Asn1Tags.Set:
              if (_indefiniteLength) {
                return new BerSetParser(new Asn1ObjectParser(_baseTag, _tagNumber, _contentStream));
              } else {
                return new DerSet(loadVector(_contentStream)).Parser;
              }
            case Asn1Tags.Sequence:
              if (_indefiniteLength) {
                return new BerSequenceParser(new Asn1ObjectParser(_baseTag, _tagNumber, _contentStream));
              } else {
                return new DerSequence(loadVector(_contentStream)).Parser;
              }
            case Asn1Tags.OctetString:
              if (_indefiniteLength || IsConstructed) {
                return new BerOctetStringParser(new Asn1ObjectParser(_baseTag, _tagNumber, _contentStream));
              } else {
                return new DerOctetString(((DefiniteLengthInputStream)_contentStream).ToArray()).Parser;
              }
            }
          }
          throw Platform.CreateNotImplementedException("implicit tagging");
        }

      private:
        Asn1EncodableVector loadVector(Stream inStream) {
          Asn1StreamParser aIn = new Asn1StreamParser(inStream);
          Asn1EncodableVector v = new Asn1EncodableVector();

          IAsn1Convertible obj;
          while ((obj = aIn.ReadObject()) != null) {
            v.Add(obj.ToAsn1Object());
          }
          return v;
        }

        Asn1EncodableVector rLoadVector(Stream inStream) {
          try {
            return loadVector(inStream);
          } catch (IOException e) {
            throw new InvalidOperationException(e.Message, e);
          }
        }

      public:
        Asn1Object ToAsn1Object() {
          if (_indefiniteLength) {
            Asn1EncodableVector v = rLoadVector(_contentStream);

            if (v.Count > 1) {
              return new BerTaggedObject(false, _tagNumber, new BerSequence(v));
            } else if (v.Count == 1) {
              return new BerTaggedObject(true, _tagNumber, v[0]);
            } else {
              return new BerTaggedObject(false, _tagNumber, new BerSequence());
            }
          } else {
            if (IsConstructed) {
              Asn1EncodableVector v = rLoadVector(_contentStream);

              if (v.Count == 1) {
                return new DerTaggedObject(true, _tagNumber, v[0]);
              }
              return new DerTaggedObject(false, _tagNumber, new DerSequence(v));
            }
            try {
              return new DerTaggedObject(false, _tagNumber, new DerOctetString(((DefiniteLengthInputStream)_contentStream).ToArray()));
            } catch (IOException e) {
              throw new InvalidOperationException(e.Message, e);
            }
          }
        }
      };

    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _BERTAGGEDOBJECTPARSER_H */

