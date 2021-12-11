// https://github.com/sejongresearch/2020.Spring.DataStructure
// 퀴즈 5번 문제

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../List/LinkedList.h"

List* getPolynomialList(int numArr[], int arrLen) {
    List* polynomialList = (List*)malloc(sizeof(List));
    listInit(polynomialList);

    for (int i = 0; i < arrLen; i += 2) {
        Element element = (Element)malloc(sizeof(Data));
        element->coefficient = numArr[i];
        element->exponent = numArr[i + 1];
        listAdd(polynomialList, i / 2, element);
    }

    return polynomialList;
}

List* calPolynomial(List* aPolynomial, List* bPolynomial) {
    List* result = (List*)malloc(sizeof(List));
    listInit(result);

    int rIdx = 0, aIdx = 0, bIdx = 0;
    Element a;
    Element b;
    Element c;
    while (true) {
        if (aIdx >= aPolynomial->size) {
            for (; bIdx < bPolynomial->size; bIdx++) {
                b = listGet(bPolynomial, bIdx);
                listAdd(result, rIdx++, b);
            }
            break;
        } else if (bIdx >= bPolynomial->size) {
            for (; aIdx < aPolynomial->size; aIdx++) {
                a = listGet(aPolynomial, aIdx);
                listAdd(result, rIdx++, a);
            }
            break;
        }

        a = listGet(aPolynomial, aIdx);
        b = listGet(bPolynomial, bIdx);

        if (a->exponent > b->exponent) {
            listAdd(result, rIdx++, a);
            aIdx++;
        } else if (a->exponent < b->exponent) {
            listAdd(result, rIdx++, b);
            bIdx++;
        } else {
            c = (Element)malloc(sizeof(Data));
            c->coefficient = (a->coefficient) + (b->coefficent);
            c->exponent = a->coefficient;
            listAdd(result, rIdx++, c);
            free(a);
            free(b);
        }
    }

    listDestroy(aPolynomial);
    listDestroy(bPolynomial);
    free(aPolynomial);
    free(bPolynomial);

    return result;
}

int main() {
    int a; scanf("%d", &a);
    a *= 2;
    int aArr[a];
    for (int i = 0; i < a; i++) {
        scanf("%d", &aArr[i]);
    }

    int b; scanf("%d", &b);
    b *= 2;
    int bArr[b];
    for (int i = 0; i < b; i++) {
        scanf("%d", &bArr[i]);
    }

    List* resultList = calPolynomial(getPolynomialList(aArr, a), getPolynomialList(bArr, b));

    Element e;
    for (int i = 0; i < resultList->size; i++) {
        e = listGet(resultList, i);
        printf("%d %d ", e->coefficient, e->exponent);

        if (e != NULL) { free(e); }
    } printf("\n");

    return 0;
}