// 
// File:   Asn1Set.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 26, 2007, 3:17 AM
//

#ifndef _ASN1SET_H
#define	_ASN1SET_H

//using System;
//using System.Collections;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
      using namespace org.bouncycastle.utilities.collections;
      
      class Asn1Set : public Asn1Object, public IEnumerable {
      private:
        readonly ArrayList _set;

        /**
         * return an ASN1Set from the given object.
         *
         * @param obj the object we want converted.
         * @exception ArgumentException if the object cannot be converted.
         */
      public:
        static Asn1Set GetInstance(object obj) {
          if (obj == null || obj is Asn1Set) {
            return (Asn1Set)obj;
          }
          throw new ArgumentException("unknown object in GetInstance");
        }

        /**
         * Return an ASN1 set from a tagged object. There is a special
         * case here, if an object appears to have been explicitly tagged on
         * reading but we were expecting it to be implictly tagged in the
         * normal course of events it indicates that we lost the surrounding
         * set - so we need to add it back (this will happen if the tagged
         * object is a sequence that contains other sequences). If you are
         * dealing with implicitly tagged sets you really <b>should</b>
         * be using this method.
         *
         * @param obj the tagged object.
         * @param explicitly true if the object is meant to be explicitly tagged
         *          false otherwise.
         * @exception ArgumentException if the tagged object cannot
         *          be converted.
         */
        static Asn1Set GetInstance(Asn1TaggedObject	obj, bool explicitly) {
          Asn1Object inner = obj.GetObject();
          if (explicitly) {
            if (!obj.IsExplicit()) {
              throw new ArgumentException("object implicit - explicit expected.");
            }
            return (Asn1Set) inner;
          }

          //
          // constructed object which appears to be explicitly tagged
          // and it's really implicit means we have to add the
          // surrounding sequence.
          //
          if (obj.IsExplicit()) {
            return new DerSet(inner);
          }

          if (inner is Asn1Set) {
            return (Asn1Set) inner;
          }

          //
          // in this case the parser returns a sequence, convert it
          // into a set.
          //
          if (inner is Asn1Sequence) {
            Asn1EncodableVector v = new Asn1EncodableVector();
            Asn1Sequence s = (Asn1Sequence) inner;
            foreach (Asn1Encodable ae in s) {
              v.Add(ae);
            }
            // TODO Should be able to construct set directly from sequence?
            return new DerSet(v, false);
          }

          throw new ArgumentException("unknown object in GetInstanceFromTagged");
        }

      protected:
        Asn1Set(int capacity) {
          _set = new ArrayList(capacity);
        }

      public:
        IEnumerator GetEnumerator() {
          return _set.GetEnumerator();
        }

        //[Obsolete("Use GetEnumerator() instead")]
        IEnumerator GetObjects() {
          return GetEnumerator();
        }

        /**
         * return the object at the set position indicated by index.
         *
         * @param index the set number (starting at zero) of the object
         * @return the object at the set postion indicated by index.
         */
        Asn1Encodable this[int index] {
          get { return (Asn1Encodable) _set[index]; }
        }

        //[Obsolete("Use 'object[index]' syntax instead")]
        Asn1Encodable GetObjectAt(int index) {
          return this[index];
        }

        //[Obsolete("Use 'Count' property instead")]
        int Size {
          get { return _set.Count; }
        }

        int Count {
          get { return _set.Count; }
        }

      private:
        class Asn1SetParserImpl : public Asn1SetParser {
        private:
          readonly Asn1Set outer;
          readonly int max;
          int index;

        public:
          Asn1SetParserImpl(Asn1Set outer) {
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

          virtual Asn1Object ToAsn1Object() {
            return outer;
          }
        }

      public:
        Asn1SetParser Parser {
          get { return new Asn1SetParserImpl(this); }
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

        virtual bool Asn1Equals(Asn1Object asn1Object) {
          Asn1Set other = asn1Object as Asn1Set;
          if (other == null) {
            return false;
          }

          if (Count != other.Count) {
            return false;
          }
          IEnumerator s1 = GetEnumerator();
          IEnumerator s2 = other.GetEnumerator();

          while (s1.MoveNext() && s2.MoveNext()) {
          //  if (!Platform.Equals(s1.Current, s2.Current))
          Asn1Object o1 = ((Asn1Encodable) s1.Current).ToAsn1Object();
          if (!o1.Equals(s2.Current)) {
            return false;
          }
        }
        return true;
      }
        
        /**
         * return true if a &lt;= b (arrays are assumed padded with zeros).
         */
      private:
        bool LessThanOrEqual(byte[] a, byte[] b) {
          if (a.Length <= b.Length) {
            for (int i = 0; i != a.Length; i++) {
              int l = a[i] & 0xff;
              int r = b[i] & 0xff;
              if (r > l) {
                return true;
              } else if (l > r) {
                return false;
              }
            }
            return true;
          } else {
            for (int i = 0; i != b.Length; i++) {
              int l = a[i] & 0xff;
              int r = b[i] & 0xff;
              if (r > l) {
                return true;
              } else if (l > r) {
                return false;
              }
            }
            return false;
          }
        }
        
      protected:
        void Sort() {
          if (_set.Count > 1) {
            bool swapped;
            do {
              byte[] a = ((Asn1Encodable) _set[0]).GetEncoded();
              swapped = false;
              int index = 0;
              do {
                byte[] b = ((Asn1Encodable) _set[index + 1]).GetEncoded();
                if (LessThanOrEqual(a, b)) {
                  a = b;
                } else {
                  object o = _set[index];
                  _set[index] = _set[index + 1];
                  _set[index + 1] = o;
                  swapped = true;
                }
              } while (++index != _set.Count - 1);
            } while (swapped);
          }
        }
        
        void AddObject(Asn1Encodable obj) {
          _set.Add(obj);
        }

      public:
        std::string ToString() {
          return CollectionUtilities.ToString(_set);
        }
      };

    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _ASN1SET_H */

