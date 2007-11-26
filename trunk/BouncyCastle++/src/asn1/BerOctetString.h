// 
// File:   BerOctetString.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 10:22 AM
//

#ifndef _BEROCTETSTRING_H
#define	_BEROCTETSTRING_H

//using System;
//using System.Collections;
//using System.IO;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      
      class BerOctetString : public DerOctetString, public IEnumerable {
      private:
        const int MaxLength = 1000;

        /**
         * convert a vector of octet strings into a single byte string
         */
        static byte[] ToBytes(ArrayList octs) {
          MemoryStream bOut = new MemoryStream();
          foreach (DerOctetString o in octs) {
            byte[] octets = o.GetOctets();
            bOut.Write(octets, 0, octets.Length);
          }
          return bOut.ToArray();
        }

        readonly ArrayList octs;

      /// <param name="str">The octets making up the octet string.</param>
      public:
        BerOctetString(byte[] str) : base(str) {
        }

        BerOctetString(ArrayList octets) : base(ToBytes(octets)) {
          this.octs = octets;
        }

        BerOctetString(Asn1Object obj) : base(obj) {
        }

        BerOctetString(Asn1Encodable obj) : base(obj.ToAsn1Object()) {
        }

        virtual byte[] GetOctets() {
          return str;
        }

        /**
         * return the DER octets that make up this string.
         */
        IEnumerator GetEnumerator() {
          if (octs == null) {
            return GenerateOcts().GetEnumerator();
          }
          return octs.GetEnumerator();
        }

        //[Obsolete("Use GetEnumerator() instead")]
        IEnumerator GetObjects() {
          return GetEnumerator();
        }

      private:
        ArrayList GenerateOcts() {
          int start = 0;
          int end = 0;
          ArrayList vec = new ArrayList();

          while ((end + 1) < str.Length) {
            if (str[end] == 0 && str[end + 1] == 0) {
              byte[] nStr = new byte[end - start + 1];
              Array.Copy(str, start, nStr, 0, nStr.Length);
              vec.Add(new DerOctetString(nStr));
              start = end + 1;
            }
            end++;
          }

          byte[] nStr2 = new byte[str.Length - start];
          Array.Copy(str, start, nStr2, 0, nStr2.Length);
          vec.Add(new DerOctetString(nStr2));
          return vec;
        }

        virtual void Encode(DerOutputStream derOut) {
          if (derOut is Asn1OutputStream || derOut is BerOutputStream) {
            derOut.WriteByte(Asn1Tags.Constructed | Asn1Tags.OctetString);
            derOut.WriteByte(0x80);

            //
            // write out the octet array
            //
            if (octs != null) {
              for (int i = 0; i != octs.Count; i++) {
                derOut.WriteObject(octs[i]);
              }
            } else {
              for (int i = 0; i < str.Length; i += MaxLength) {
                int end = System.Math.Min(str.Length, i + MaxLength);
                byte[] nStr = new byte[end - i];
                Array.Copy(str, i, nStr, 0, nStr.Length);
                derOut.WriteObject(new DerOctetString(nStr));
              }
            }
            derOut.WriteByte(0x00);
            derOut.WriteByte(0x00);
          } else {
            base.Encode(derOut);
          }
        }
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _BEROCTETSTRING_H */

