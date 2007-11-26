// 
// File:   BerTaggedObject.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 12:20 PM
//

#ifndef _BERTAGGEDOBJECT_H
#define	_BERTAGGEDOBJECT_H

//using System;
//using System.Collections;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      using namespace org.bouncycastle.utilities;

      /**
       * Ber TaggedObject - in ASN.1 nottation this is any object proceeded by
       * a [n] where n is some number - these are assume to follow the construction
       * rules (as with sequences).
       */
      class BerTaggedObject : public DerTaggedObject {
      public:
        /**
         * @param tagNo the tag number for this object.
         * @param obj the tagged object.
         */
        BerTaggedObject(int tagNo, Asn1Encodable obj) : base(tagNo, obj) {
        }

        /**
         * @param explicitly true if an explicitly tagged object.
         * @param tagNo the tag number for this object.
         * @param obj the tagged object.
         */
        BerTaggedObject(bool explicitly, int tagNo, Asn1Encodable obj) 
        : base(explicitly, tagNo, obj) {
        }

        /**
         * create an implicitly tagged object that contains a zero
         * length sequence.
         */
        BerTaggedObject(int tagNo) : base(false, tagNo, new BerSequence()) {
        }

        virtual void Encode(DerOutputStream  derOut) {
          if (derOut is Asn1OutputStream || derOut is BerOutputStream) {
            derOut.WriteByte((byte)(Asn1Tags.Constructed | Asn1Tags.Tagged | tagNo));
            derOut.WriteByte(0x80);

            if (!IsEmpty()) {
              if (!explicitly) {
                IEnumerable eObj;
                if (obj is Asn1OctetString) {
                  if (obj is BerOctetString) {
                    eObj = (BerOctetString) obj;
                  } else {
                    Asn1OctetString octs = (Asn1OctetString)obj;
                    eObj = new BerOctetString(octs.GetOctets());
                  }
                } else if (obj is Asn1Sequence) {
                  eObj = (Asn1Sequence) obj;
                } else if (obj is Asn1Set) {
                  eObj = (Asn1Set) obj;
                } else {
                  throw Platform.CreateNotImplementedException(obj.GetType().Name);
                }

                foreach (object o in eObj) {
                  derOut.WriteObject(o);
                }
              } else {
                derOut.WriteObject(obj);
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

#endif	/* _BERTAGGEDOBJECT_H */

