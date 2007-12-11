// 
// File:   DerApplicationSpecific.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on December 10, 2007, 11:38 PM
//

#ifndef _DERAPPLICATIONSPECIFIC_H
#define	_DERAPPLICATIONSPECIFIC_H

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      using namespace org.bouncycastle.utilities;

      /**
      * Base class for an application specific object
      */
      class DerApplicationSpecific : public Asn1Object {
      private:
        readonly int	tag;
        readonly byte[]	octets;

      public:
        DerApplicationSpecific(int tag, byte[] octets) {
          this.tag = tag;
          this.octets = octets;
        }

        DerApplicationSpecific(int tag, Asn1Encodable obj) : this(true, tag, obj) {
	}

	DerApplicationSpecific(bool isExplicit, int tag, Asn1Encodable obj) {
          if (tag >= 0x1f) {
            throw new IOException("unsupported tag number");
          }
          byte[] data = obj.GetDerEncoded();

          if (isExplicit) {
            this.tag = tag | Asn1Tags.Constructed;
            this.octets = data;
          } else {
            this.tag = tag;
            int lenBytes = GetLengthOfLength(data);
            byte[] tmp = new byte[data.Length - lenBytes];
            Array.Copy(data, lenBytes, tmp, 0, tmp.Length);
            this.octets = tmp;
          }
	}

      private:
        int GetLengthOfLength(byte[] data) {
          int count = 2;	// TODO: assumes only a 1 byte tag number
          while((data[count - 1] & 0x80) != 0) {
            count++;
          }

          return count;
        }

      public:
        bool IsConstructed() {
          return (tag & Asn1Tags.Constructed) != 0;
        }

        byte[] GetContents() {
          return octets;
        }

        int ApplicationTag {
          get { return tag; }
        }

	Asn1Object GetObject() {
          return FromByteArray(GetContents());
	}

        /**
         * Return the enclosed object assuming implicit tagging.
         *
         * @param derTagNo the type tag that should be applied to the object's contents.
         * @return  the resulting object
         * @throws IOException if reconstruction fails.
         */
        Asn1Object GetObject(int derTagNo) {
          if (tag >= 0x1f) {
            throw new IOException("unsupported tag number");
          }
          byte[] tmp = this.GetEncoded();
          tmp[0] = (byte) derTagNo;
          return FromByteArray(tmp);;
	}

	virtual void Encode(DerOutputStream derOut) {
          derOut.WriteEncoded(Asn1Tags.Application | tag, octets);
        }

      protected:
        virtual bool Asn1Equals(Asn1Object asn1Object) {
          DerApplicationSpecific other = asn1Object as DerApplicationSpecific;
          if (other == null) {
            return false;
          }
          return this.tag == other.tag && Arrays.AreEqual(this.octets, other.octets);
        }

	virtual int Asn1GetHashCode() {
          byte[] b = GetContents();
          int hc = 0;
          for (int i = 0; i != b.Length; i++) {
            hc ^= ((int) b[i]) << (i % 4);
          }
          return hc ^ ApplicationTag;
        }
      }
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _DERAPPLICATIONSPECIFIC_H */

