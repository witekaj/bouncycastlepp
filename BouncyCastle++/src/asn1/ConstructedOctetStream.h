// 
// File:   ConstructedOctetStream.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 29, 2007, 1:10 AM
//

#ifndef _CONSTRUCTEDOCTETSTREAM_H
#define	_CONSTRUCTEDOCTETSTREAM_H

using System.IO;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      using namespace org.bouncycastle.utilities.io;

      class ConstructedOctetStream : public BaseInputStream {
      private:
        
        readonly Asn1ObjectParser _parser;
        bool _first = true;
        Stream _currentStream;

      public:
        ConstructedOctetStream(Asn1ObjectParser parser) {
          _parser = parser;
        }

        virtual int Read(byte[] buffer, int offset, int count) {
          if (_currentStream == null) {
            if (!_first) {
              return 0;
            }
            Asn1OctetStringParser s = (Asn1OctetStringParser)_parser.ReadObject();

            if (s == null) {
              return 0;
            }

            _first = false;
            _currentStream = s.GetOctetStream();
          }

          int totalRead = 0;
          for (;;) {
            int numRead = _currentStream.Read(buffer, offset + totalRead, count - totalRead);
            if (numRead > 0) {
              totalRead += numRead;
              if (totalRead == count) {
                return totalRead;
              }
            } else {
              Asn1OctetStringParser aos = (Asn1OctetStringParser)_parser.ReadObject();
              if (aos == null) {
                _currentStream = null;
                return totalRead;
              }
              _currentStream = aos.GetOctetStream();
            }
          }
        }

        virtual int ReadByte() {
          if (_currentStream == null) {
            if (!_first) {
              return 0;
            }
            Asn1OctetStringParser s = (Asn1OctetStringParser)_parser.ReadObject();
            if (s == null) {
              return 0;
            }

            _first = false;
            _currentStream = s.GetOctetStream();
          }
          for (;;) {
            int b = _currentStream.ReadByte();
            if (b >= 0) {
              return b;
            }
            Asn1OctetStringParser aos = (Asn1OctetStringParser)_parser.ReadObject();
            if (aos == null) {
              _currentStream = null;
              return -1;
            }
            _currentStream = aos.GetOctetStream();
          }
        }
      };

    } //namespace asn1
  } //namespace bouncycastle
} //namespace org


#endif	/* _CONSTRUCTEDOCTETSTREAM_H */

