#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "poly.h"

int is_num(char c) {
    return (c >= '0') && (c <= '9');
}

int bin_pow(double base, int ind, double* res) {
    if (ind == 0) {
        *res = 1;
        return 0;
    }
    int _ind = ind;
    if (ind < 0) {
        _ind = ~ind + 1;
    }

    *res = 1.;

    double rec_res;
    bin_pow(base, _ind >> 1, &rec_res);
    *res = rec_res * rec_res;
    if (_ind & 0b1) {
        *res *= base;
    }

    if (ind < 0) {
        *res = 1 / *res;
    }
    return 0;
}

int create_node(node **_node) {
    *_node = (node *)malloc(sizeof(node));
    if (*_node == NULL) {
        printf("memory error\n");
        return -1;
    }

    (*_node)->coeff = 0;
    (*_node)->power = 0;
    (*_node)->next = NULL;

    return 0;
}

int poly_init(polynom **poly) {
    return create_node(poly);
}

int delete_node(node **node) {
    if (((*node)->next) != NULL) {
        delete_node(&((*node)->next));
    }
    free(*node);
    node = NULL;
    return 0;
}

int poly_delete(polynom **poly) {
    return delete_node(poly);
}

int poly_clear(polynom **poly) {
    if (((*poly)->next) != NULL) {
        delete_node(&((*poly)->next));
    }
    (*poly)->coeff = 0;
    (*poly)->power = 0;
    (*poly)->next = NULL;
    return 0;
}

int poly_add_node(polynom **poly, int _coeff, int _pow) {
    node *new = NULL;
    if (create_node(&new)) {
        return -1;
    }
    new->coeff = _coeff;
    new->power = _pow;

    if (_pow > ((*poly)->power)) {
        new->next = &(**poly);
        *poly = new;
    } else {
        node **w = poly;

        while ((*w) != NULL) {
            if (_pow == (*w)->power) {
                (*w)->coeff += _coeff;
                free(new);
                return 0;
            }

            if (_pow > (*w)->power) {
                break;
            }
            w = &((*w)->next);
        }

        new->next = *w;
        *w = new;
    }
    return 0;
}

int poly_set(polynom **poly, int pow, ...) {
    poly_clear(poly);

    va_list coeffs;
    va_start(coeffs, pow);

    (*poly)->coeff = va_arg(coeffs, int);
    (*poly)->power = pow;

    node *w; 
    w = *poly;

    for (int i = pow - 1; i > -1; --i) {
        if (create_node(&(w->next))) {
            va_end(coeffs);
            return -1;
        }
        w = w->next;
        w->coeff = va_arg(coeffs, int);
        w->power = i;
    }

    va_end(coeffs);
    return 0;
}

int spoly_set(polynom **poly, char* repr) {
    poly_clear(poly);

    int coeff = 1;
    int pow = 0;
    int sign = 1;
    int pow_sign = 1;
    int buff;

    char *ptr = repr;
    if (*ptr == '-') {
        sign = -1;
        ++ptr;
    }

    while (1) {
        switch (*ptr) 
        {
        case 'x':
            pow += 1;
            break;

        case '^':
            buff = pow - 1;
            pow = 0;
            if (ptr[1] == '-') {
                pow_sign = -1;
                ++ptr;
            }

            while (is_num(ptr[1])) {
                ++ptr;
                pow *= 10;
                pow += *ptr - '0';
            }
            pow += buff;
            break;

        case '+':
            if (coeff > 0) {
                if (poly_add_node(poly, sign * coeff, pow_sign * pow)) {
                    return -1;
                }
            }
            pow = 0;
            sign = 1;
            coeff = 1;
            pow_sign = 1;
            
            break;

        case '-':
            if (coeff > 0) {
                if (poly_add_node(poly, sign * coeff, pow_sign * pow)) {
                    return -1;
                }
            }
            pow = 0;
            sign = -1;
            coeff = 1;
            pow_sign = 1;
            
            break;

        case 0:
            if (coeff > 0) {
                if (poly_add_node(poly, sign * coeff, pow_sign * pow)) {
                    return -1;
                }
            }
            return 0;

        default:
            if (is_num(*ptr)) {
                buff = coeff;
                coeff = 0;
                while (is_num(*ptr)) {
                    coeff *= 10;
                    coeff += *ptr - '0';
                    ++ptr;
                }
                coeff *= buff;
                --ptr;

            } else {
                printf("invalid arg\n");
                return -1;
            }
            break;
        }
        ++ptr;
    }
    return 0;
}

int spoly_init(polynom **poly, char* repr) {
    if (poly_init(poly)) {
        return -1;
    }
    return spoly_set(poly, repr);
}

int poly_print(polynom *poly) {
    node *r = poly;
    int is_begin = 1;

    if ((r->next == NULL) && (r->coeff == 0)) {
        printf("0\n");
        return 0;
    }

    while (r != NULL) {
        if (r->coeff) {
            is_begin = 0;
            if (r->power) {
                switch (r->coeff)
                {
                case 1:
                    putchar('x');
                    break;
                case -1:
                    printf("-x");
                    break;
                default:
                    printf("%dx", r->coeff);
                    break;
                }
                
                if (r->power != 1) {
                    printf("^%d", r->power);
                }
            } else {
                printf("%d", r->coeff);
            }
        } 

        if (!is_begin) {
            if ((r->next != NULL) && (r->next->coeff > 0)) {
                putchar('+');
            }
        }
        r = r->next;
    }
    return 0;
}

int poly_cpy(polynom *source, polynom **targ) {
    if (poly_init(targ)) {
        return -1;
    }
    polynom *r = source;
    while (r != NULL) {
        if (poly_add_node(targ, r->coeff, r->power)) {
            poly_delete(targ);
            return -1;
        }
        r = r->next;
    }
    return 0;
}


polynom* poly_add(polynom *a, polynom *b) {
    polynom *result;
    if (poly_init(&result)) {
        return NULL;
    }

    polynom *left = a;
    polynom *right = b;

    while (left != NULL) {
        if (poly_add_node(&result, left->coeff, left->power)) {
            poly_delete(&result);
            return NULL;
        }
        left = left->next;
    }
    while (right != NULL) {
        if (poly_add_node(&result, right->coeff, right->power)) {
            poly_delete(&result);
            return NULL;
        }
        right = right->next;
    }

    return result;
}

polynom *poly_sub(polynom *a, polynom *b) {
    polynom *result;
    if (poly_init(&result)) {
        return NULL;
    }

    polynom *left = a;
    polynom *right = b;

    while (left != NULL) {
        if (poly_add_node(&result, left->coeff, left->power)) {
            poly_delete(&result);
            return NULL;
        }
        left = left->next;
    }
    while (right != NULL) {
        if (poly_add_node(&result, -right->coeff, right->power)) {
            poly_delete(&result);
            return NULL;
        }
        right = right->next;
    }

    return result;
}

polynom *poly_mult(polynom *a, polynom *b) {
    polynom *result;
    if (poly_init(&result)) {
        return NULL;
    }

    polynom *left = a;
    polynom *right = b;

    while (left != NULL) {
        right = b;

        while (right != NULL) {
            if (poly_add_node(&result, (left->coeff * right->coeff), (left->power + right->power))) {
                poly_delete(&result);
                return NULL;
            }
            right = right->next;
        }

        left = left->next;
    }

    return result;
}

polynom *poly_div(polynom *a, polynom *b) {
    polynom *result;
    if (poly_init(&result)) {
        return NULL;
    }

    polynom *numerator;
    if (poly_cpy(a, &numerator)) {
        return NULL;
    }
    polynom *r = numerator;
    polynom *buff;
    polynom *denominator = b;

    while (denominator->coeff == 0) {
        denominator = denominator->next;
        if (denominator == NULL) {
            poly_delete(&result);
            poly_delete(&numerator);
            printf("zero division error\n");
            return NULL;
        }
    }
        
    while (r != NULL && r->power >= denominator->power) {
        if (r->coeff / denominator->coeff == 0) {
            r = r->next;
        } else {
            if (poly_add_node(&result, r->coeff / denominator->coeff, r->power - denominator->power)) {
                poly_delete(&result);
                poly_delete(&numerator);
                return NULL;
            }
            poly_delete(&numerator);

            buff = poly_mult(denominator, result);
            numerator = poly_sub(a, buff);
            poly_delete(&buff);

            r = numerator;
        }
    }

    poly_delete(&numerator);
    return result;
}

polynom *poly_mod(polynom *a, polynom *b) {
    polynom *div = poly_div(a, b);
    polynom *mult = poly_mult(div, b);
    polynom *result = poly_sub(a, mult);
    poly_delete(&div);
    poly_delete(&mult);
    return result;
}

int poly_eval(int x, polynom *a) {
    polynom *r = a;
    int result = 0;
    double bu_ispugalsa;

    while (r != NULL) {
        bin_pow((double)x, r->power, &bu_ispugalsa);
        result += (int)bu_ispugalsa * r->coeff;
        r = r->next;
    }
    return result;
}

polynom *poly_diff(polynom *a) {
    polynom *r = a;
    polynom *result;
    if (poly_init(&result)) {
        return NULL;
    }

    while ((r->power != 0) && (r != NULL)) {
        if (poly_add_node(&result, r->coeff * r->power, r->power - 1)) {
            poly_delete(&result);
            return NULL;
        }
        r = r->next;
    }
    return result;
}

polynom *poly_cmps(polynom *a, polynom *b) {
    polynom *outter = a;
    polynom *inner = b;
    polynom *pow;
    polynom *buff;
    if (spoly_init(&pow, "1")) {
        return NULL;
    }
    polynom *result;
    if (poly_init(&result)) {
        poly_delete(&pow);
        return NULL;
    }

    if (spoly_set(&pow, "1")) {
        poly_delete(&pow);
        poly_delete(&result);
        return NULL;
    }
    for (int i = 0; i < outter->power; ++i) {
        poly_cpy(pow, &buff);
        poly_delete(&pow);
        pow = poly_mult(buff, inner);
        poly_delete(&buff);
    }

    while (outter != NULL) {
        
        for (int i = 0; i < outter->coeff; ++i) {
            buff = poly_add(result, pow);
            poly_delete(&result);
            result = buff;
        }
        for (int i = 0; i > outter->coeff; --i) {
            buff = poly_sub(result, pow);
            poly_delete(&result);
            result = buff;
        }
        poly_cpy(pow, &buff);
        poly_delete(&pow);
        pow = poly_div(buff, inner);
        poly_delete(&buff);
        outter = outter->next;
    }
    poly_delete(&pow);
    return result;
}
