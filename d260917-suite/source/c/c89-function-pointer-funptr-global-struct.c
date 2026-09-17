// <svf-test-suite>@64f017e/src/basic_c_tests/funptr-global.c

#include <stdlib.h>
typedef int PRSize;
typedef unsigned int PRUint32;
typedef unsigned int PRUintn;
typedef int PRIntn;

struct PLHashAllocOps {
   void *(*allocTable)(void *pool , PRSize size ) ;
};
typedef struct PLHashAllocOps PLHashAllocOps;

static void *DefaultAllocTable(void *pool , PRSize size )
{ void *tmp ;

  {
  tmp = malloc((unsigned int )size);
  return (tmp);
}
}

PLHashAllocOps defaultHashAllocOps  =    {& DefaultAllocTable};
void PL_NewHashTable(PRUint32 n , void *allocPriv )
{
  void *tmp___0 ;
  void *tmp___1 ;

  PLHashAllocOps const   * allocOps = (PLHashAllocOps const   *)(& defaultHashAllocOps);
  tmp___0 = (*(allocOps->allocTable))(allocPriv, (int )sizeof(int));
  tmp___1 = (*(allocOps->allocTable))(allocPriv, (int )sizeof(int));

}

int main(){return 0;}
