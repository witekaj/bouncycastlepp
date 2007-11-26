// 
// File:   Asn1TaggedObject.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 10:01 AM
//

#ifndef _ASN1TAGGEDOBJECT_H
#define	_ASN1TAGGEDOBJECT_H

//using System;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      using namespace org.bouncycastle.utilities;
      
      /**
       * ASN.1 TaggedObject - in ASN.1 notation this is any object proceeded by
       * a [n] where n is some number - these are assume to follow the construction
       * rules (as with sequences).
       */
      class Asn1TaggedObject : public Asn1Object, public Asn1TaggedObjectParser {
      private:
        int            tagNo;
        bool           explicitly = true;
        Asn1Encodable  obj;

      public:
        static Asn1TaggedObject GetInstance(Asn1TaggedObject obj, bool explicitly) {
          if (explicitly) {
            return (Asn1TaggedObject) obj.GetObject();
          }
          throw new ArgumentException("implicitly tagged tagged object");
        }

        static Asn1TaggedObject GetInstance(object obj) {
          if (obj == null || obj is Asn1TaggedObject) {
            return (Asn1TaggedObject) obj;
          }
          throw new ArgumentException("unknown object in GetInstance");
        }

        /**
         * @param tagNo the tag number for this object.
         * @param obj the tagged object.
         */
      protected:
        Asn1TaggedObject(int tagNo, Asn1Encodable obj) {
          this.explicitly = true;
          this.tagNo = tagNo;
          this.obj = obj;
        }

        /**
         * @param explicitly true if the object is explicitly tagged.
         * @param tagNo the tag number for this object.
         * @param obj the tagged object.
         */
        Asn1TaggedObject(bool explicitly, int tagNo, Asn1Encodable obj) {
          this.explicitly = explicitly;
          this.tagNo = tagNo;
          this.obj = obj;
        }

        virtual bool Asn1Equals(Asn1Object asn1Object) {
          Asn1TaggedObject other = asn1Object as Asn1TaggedObject;
          if (other == null) {
            return false;
          }

          return this.tagNo == other.tagNo
//				&& this.empty == other.empty
            && this.explicitly == other.explicitly
            && Platform.Equals(GetObject(), other.GetObject());
        }

        virtual int Asn1GetHashCode() {
          int code = tagNo;
          if (obj != null) {
            code ^= obj.GetHashCode();
          }
          return code;
        }

      public:
        int TagNo {
          get { return tagNo; }
        }

        /**
         * return whether or not the object may be explicitly tagged.
         * <p>
         * Note: if the object has been read from an input stream, the only
         * time you can be sure if isExplicit is returning the true state of
         * affairs is if it returns false. An implicitly tagged object may appear
         * to be explicitly tagged, so you need to understand the context under
         * which the reading was done as well, see GetObject below.</p>
         */
        bool IsExplicit() {
          return explicitly;
        }

        bool IsEmpty() {
          return false; //empty;
        }

        /**
         * return whatever was following the tag.
         * <p>
         * Note: tagged objects are generally context dependent if you're
         * trying to extract a tagged object you should be going via the
         * appropriate GetInstance method.</p>
         */
        Asn1Object GetObject() {
          if (obj != null) {
            return obj.ToAsn1Object();
          }
          return null;
        }

        /**
        * Return the object held in this tagged object as a parser assuming it has
        * the type of the passed in tag. If the object doesn't have a parser
        * associated with it, the base object is returned.
        */
        IAsn1Convertible GetObjectParser(int tag, bool isExplicit) {
          switch (tag) {
          case Asn1Tags.Set:
            return Asn1Set.GetInstance(this, isExplicit).Parser;
          case Asn1Tags.Sequence:
            return Asn1Sequence.GetInstance(this, isExplicit).Parser;
          case Asn1Tags.OctetString:
            return Asn1OctetString.GetInstance(this, isExplicit).Parser;
          }

          if (isExplicit) {
            return GetObject();
          }
          throw Platform.CreateNotImplementedException("implicit tagging for tag: " + tag);
        }

        virtual std::string ToString() {
          return std::string("[") + tagNo + std::string("]") + obj;
        }
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org



#endif	/* _ASN1TAGGEDOBJECT_H */

