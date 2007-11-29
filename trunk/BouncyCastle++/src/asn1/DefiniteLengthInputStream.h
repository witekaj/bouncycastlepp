// 
// File:   DefiniteLengthInputStream.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 29, 2007, 9:26 AM
//

#ifndef _DEFINITELENGTHINPUTSTREAM_H
#define	_DEFINITELENGTHINPUTSTREAM_H

using System;
using System.IO;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      using namespace org.bouncycastle.utilities.io;

      class DefiniteLengthInputStream : public LimitedInputStream {
      private:
        int _length;

      public:
        DefiniteLengthInputStream(Stream inStream, int length) : base(inStream) {
          if (length < 0) {
            throw new ArgumentException("negative lengths not allowed", "length");
          }
          this._length = length;
        }

        virtual int ReadByte() {
          if (_length > 0) {
            int b = _in.ReadByte();
            if (b < 0) {
              throw new EndOfStreamException();
            }
            --_length;
            return b;
          }
          SetParentEofDetect(true);
          return -1;
        }

        virtual int Read(byte[]	buf, int off, int len) {
          if (_length > 0) {
            int toRead = System.Math.Min(len, _length);
            int numRead = _in.Read(buf, off, toRead);
            if (numRead < 1) {
              throw new EndOfStreamException();
            }
            _length -= numRead;
            return numRead;
          }
          SetParentEofDetect(true);
          return 0;
        }

        byte[] ToArray() {
          byte[] bytes = new byte[_length];
          if (_length > 0) {
            if (Streams.ReadFully(_in, bytes, 0, _length) < _length) {
              throw new EndOfStreamException();
            }                
            _length = 0;
          }
          SetParentEofDetect(true);
          return bytes;
        }
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org



#endif	/* _DEFINITELENGTHINPUTSTREAM_H */

