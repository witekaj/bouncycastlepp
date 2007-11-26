// 
// File:   Asn1Sequence.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 2:59 AM
//

#ifndef _ASN1SEQUENCE_H
#define	_ASN1SEQUENCE_H

//using System;
//using System.Collections;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      using namespace org.bouncycastle.utilities.collections;
  
      class Asn1Sequence : public Asn1Object, public IEnumerable {
      private:
        readonly ArrayList seq;

        /**
         * return an Asn1Sequence from the given object.
         *
         * @param obj the object we want converted.
         * @exception ArgumentException if the object cannot be converted.
         */
      public:
        
        static Asn1Sequence GetInstance(object obj) {
          if (obj == null || obj is Asn1Sequence) {
            return (Asn1Sequence)obj;
          }
          throw new ArgumentException("unknown object in GetInstance");
        }

        /**
         * Return an ASN1 sequence from a tagged object. There is a special
         * case here, if an object appears to have been explicitly tagged on
         * reading but we were expecting it to be implictly tagged in the
         * normal course of events it indicates that we lost the surrounding
         * sequence - so we need to add it back (this will happen if the tagged
         * object is a sequence that contains other sequences). If you are
         * dealing with implicitly tagged sequences you really <b>should</b>
         * be using this method.
         *
         * @param obj the tagged object.
         * @param explicitly true if the object is meant to be explicitly tagged,
         *          false otherwise.
         * @exception ArgumentException if the tagged object cannot
         *          be converted.
         */
      static Asn1Sequence GetInstance(Asn1TaggedObject obj, bool explicitly) {
        Asn1Object inner = obj.GetObject();
        if (explicitly) {
          if (!obj.IsExplicit()) {
            throw new ArgumentException("object implicit - explicit expected.");
          }
          return (Asn1Sequence) inner;
        }

        //
        // constructed object which appears to be explicitly tagged
        // when it should be implicit means we have to add the
        // surrounding sequence.
        //
        if (obj.IsExplicit()) {
          if (obj is BerTaggedObject) {
            return new BerSequence(inner);
          }
          return new DerSequence(inner);
        }
        if (inner is Asn1Sequence) {
          return (Asn1Sequence) inner;
        }
        throw new ArgumentException("unknown object in GetInstanceFromTagged");
      }

      protected:
        Asn1Sequence(int capacity) {
          seq = new ArrayList(capacity);
        }

      public:
        IEnumerator GetEnumerator() {
          return seq.GetEnumerator();
        }

        //[Obsolete("Use GetEnumerator() instead")]
        IEnumerator GetObjects() {
          return GetEnumerator();
        }

      private:
        
        class Asn1SequenceParserImpl : public Asn1SequenceParser {
        private:
          readonly Asn1Sequence outer;
          readonly int max;
          int index;

        public:
          Asn1SequenceParserImpl(Asn1Sequence outer) {
            this.outer = outer;
            this.max = outer.Count;
          }

          IAsn1Convertible ReadObject() {
            if (index == max) {
              return null;
            }

            Asn1Encodable obj = outer[index++];
            if (obj is Asn1Sequence) {
              return ((Asn1Sequence)obj).Parser;
            }

            if (obj is Asn1Set) {
              return ((Asn1Set)obj).Parser;
            }
            return obj;
          }

          Asn1Object ToAsn1Object() {
            return outer;
          }
        }

      public:
        Asn1SequenceParser Parser {
          get { return new Asn1SequenceParserImpl(this); }
        }

        /**
         * return the object at the sequence postion indicated by index.
         *
         * @param index the sequence number (starting at zero) of the object
         * @return the object at the sequence postion indicated by index.
         */
        Asn1Encodable this[int index] {
          get { return (Asn1Encodable) seq[index]; }
        }

        //[Obsolete("Use 'object[index]' syntax instead")]
        Asn1Encodable GetObjectAt(int index) {
          return this[index];
        }

        //[Obsolete("Use 'Count' property instead")]
        int Size {
          get { return seq.Count; }
        }

        public int Count {
          get { return seq.Count; }
        }

      protected:
        virtual int Asn1GetHashCode() {
          int hc = 0;
          foreach (object o in this) {
            if (o != null) {
              hc ^= o.GetHashCode();
            }
          }
          return hc;
        }

        virtual bool Asn1Equals( Asn1Object asn1Object) {
          Asn1Sequence other = asn1Object as Asn1Sequence;
          if (other == null) {
            return false;
          }
          if (Count != other.Count) {
            return false;
          }

          IEnumerator s1 = GetEnumerator();
          IEnumerator s2 = other.GetEnumerator();
    			while (s1.MoveNext() && s2.MoveNext()) {
//				if (!Platform.Equals(s1.Current, s2.Current))
            Asn1Object o1 = ((Asn1Encodable) s1.Current).ToAsn1Object();
            if (!o1.Equals(s2.Current)) {
              return false;
            }
          }
          return true;
        }

        void AddObject(Asn1Encodable obj) {
          seq.Add(obj);
        }
        
      public:
        virtual string ToString() {
          return CollectionUtilities.ToString(seq);
        }
      };
      
    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _ASN1SEQUENCE_H */

