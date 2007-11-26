// 
// File:   BerGenerator.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 10:14 AM
//

#ifndef _BERGENERATOR_H
#define	_BERGENERATOR_H

using System.IO;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      using namespace org.bouncycastle.utilities.io;
  
      class BerGenerator : public Asn1Generator {
      private:
        bool _tagged = false;
        bool _isExplicit;
        int _tagNo;

      protected:
        BerGenerator(Stream outStream) : base(outStream) {
        }
        
      public:
        BerGenerator(Stream outStream, int tagNo, bool isExplicit) : base(outStream) {
          _tagged = true;
          _isExplicit = isExplicit;
          _tagNo = tagNo;
        }

        virtual Stream GetRawOutputStream() {
          return Out;
        }

      private:
        void WriteHdr(int tag) {
          Out.WriteByte((byte) tag);
          Out.WriteByte(0x80);
        }

      protected:
        void WriteBerHeader(int tag) {
          int tagNum = _tagNo | Asn1Tags.Tagged;
          if (_tagged) {
            if (_isExplicit) {
              WriteHdr(tagNum | Asn1Tags.Constructed);
              WriteHdr(tag);
            } else {
              if ((tag & Asn1Tags.Constructed) != 0) {
                WriteHdr(tagNum | Asn1Tags.Constructed);
              } else {
                WriteHdr(tagNum);
              }
            }
          } else {
            WriteHdr(tag);
          }
        }

        void WriteBerBody(Stream contentStream) {
          Streams.PipeAll(contentStream, Out);
        }

        void WriteBerEnd() {
          Out.WriteByte(0x00);
          Out.WriteByte(0x00);

          if (_tagged && _isExplicit) {  // write extra end for tag header
            Out.WriteByte(0x00);
            Out.WriteByte(0x00);
          }
        }
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _BERGENERATOR_H */

