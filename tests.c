#include <criterion/criterion.h>


#include "main.h"
#define TEST_TIMEOUT 15

Test(escape_quad_suite, test1, .timeout = TEST_TIMEOUT) {
  tPointi a = {0,0};
  tPointi b = {0,2};
  tPointi c = {2,2};
  tPointi d = {2,0};
  tPointi e = {1,1};
  tPointi f = {3,3};
  cr_assert_eq(true, EscapeQuad(a,b,c,d,e,f), "EscapeQuad is false");
}
