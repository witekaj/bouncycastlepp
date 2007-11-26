// 
// File:   BerOctetStringGenerator.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 11:26 AM
//

#ifndef _BEROCTETSTRINGGENERATOR_H
#define	_BEROCTETSTRINGGENERATOR_H

//using System;
//using System.IO;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      using namespace org.bouncycastle.utilities.io;
      
      class BerOctetStringGenerator: public BerGenerator {
      public:
        BerOctetStringGenerator(Stream outStream) : base(outStream) {
          WriteBerHeader(Asn1Tags.Constructed | Asn1Tags.OctetString);
        }

        BerOctetStringGenerator(Stream outStream, int tagNo, bool isExplicit)
        : base(outStream, tagNo, isExplicit) {
          WriteBerHeader(Asn1Tags.Constructed | Asn1Tags.OctetString);
        }

        Stream GetOctetOutputStream() {
          return GetOctetOutputStream(new byte[1000]); // limit for CER encoding.
        }

        Stream GetOctetOutputStream(int bufSize) {
          return bufSize < 1 ?	GetOctetOutputStream() :	GetOctetOutputStream(new byte[bufSize]);
        }

        Stream GetOctetOutputStream(byte[] buf) {
          return new BufferedBerOctetStream(this, buf);
        }

      private:
        class BufferedBerOctetStream : public BaseOutputStream {
        private:
          byte[] _buf;
          int    _off;
          readonly BerOctetStringGenerator _gen;

        public:
          BufferedBerOctetStream(BerOctetStringGenerator gen, byte[] buf) {
            _gen = gen;
            _buf = buf;
            _off = 0;
          }

          virtual void WriteByte(byte b) {
            _buf[_off++] = b;
            if (_off == _buf.Length) {
              DerOctetString.Encode(new DerOutputStream(_gen.Out), _buf, 0, _off);
              _off = 0;
            }
          }

          virtual void Write(byte[] buf, int offset, int len) {
            while (len > 0) {
              int numToCopy = System.Math.Min(len, _buf.Length - _off);
              if (numToCopy == _buf.Length) {
                DerOctetString.Encode(new DerOutputStream(_gen.Out), buf, offset, numToCopy);
              } else {
                Array.Copy(buf, offset, _buf, _off, numToCopy);
                _off += numToCopy;
                if (_off < _buf.Length) {
                  break;
                }
                DerOctetString.Encode(new DerOutputStream(_gen.Out), _buf, 0, _off);
                _off = 0;
              }
              offset += numToCopy;
              len -= numToCopy;
            }
          }

          virtual void Close() {
            if (_off != 0) {
              DerOctetString.Encode(new DerOutputStream(_gen.Out), _buf, 0, _off);
            }
            _gen.WriteBerEnd();
            base.Close();
          }
        }
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _BEROCTETSTRINGGENERATOR_H */

