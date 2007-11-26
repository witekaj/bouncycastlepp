// 
// File:   BerGenerator.h
// Author: watsug
//
// Created on November 26, 2007, 10:14 AM
//

#ifndef _BERGENERATOR_H
#define	_BERGENERATOR_H

using System.IO;

using Org.BouncyCastle.Utilities.IO;

namespace Org {
  namespace BouncyCastle {
    namespace Asn1 {
  
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
      }
      
    } //namespace Asn1
  } //namespace BouncyCastle
} //namespace Org

#endif	/* _BERGENERATOR_H */

