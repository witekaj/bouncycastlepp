// 
// File:   Asn1EncodableVector.h
// Author: Adam Augustyn
//         CryptoTech, http://www.cryptotech.com.pl
//
// Created on November 23, 2007, 2:35 AM
//

#ifndef _ASN1ENCODABLEVECTOR_H
#define	_ASN1ENCODABLEVECTOR_H

//using System.Collections;

namespace org {
  namespace bouncycastle {
    namespace asn1 {
  
      class Asn1EncodableVector : IEnumerable {

      private:
        private ArrayList v = new ArrayList();

      public:
        static Asn1EncodableVector FromEnumerable(IEnumerable e) {
          Asn1EncodableVector v = new Asn1EncodableVector();
          foreach (Asn1Encodable obj in e) {
            v.Add(obj);
          }
          return v;
        }

        Asn1EncodableVector(params Asn1Encodable[] v) {
          Add(v);
        }

        void Add(params Asn1Encodable[] objs) {
          foreach (Asn1Encodable obj in objs) {
            v.Add(obj);
          }
        }

        Asn1Encodable this[int index] {
          get { return (Asn1Encodable) v[index]; }
        }

        int Count() {
          get { return v.Count; }
        }

        IEnumerator GetEnumerator() {
          return v.GetEnumerator();
        }
    	};

    } //namespace asn1
  } //namespace bouncycastle
} //namespace org

#endif	/* _ASN1ENCODABLEVECTOR_H */

