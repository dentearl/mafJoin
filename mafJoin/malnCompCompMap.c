#include "malnCompCompMap.h"
#include "common.h"
#include "sonLibHash.h"
#include "malnComp.h"


struct malnCompCompMap {
    stHash *map;
};

/* constructor */
struct malnCompCompMap *malnCompCompMap_construct(void) {
    struct malnCompCompMap *mccm;
    AllocVar(mccm);
    mccm->map = stHash_construct();
    return mccm;
}

/* destructor */
void malnCompCompMap_destruct(struct malnCompCompMap *mccm) {
    if (mccm != NULL) {
        stHash_destruct(mccm->map);
        freeMem(mccm);
    }
}

/* add a mapping */
void malnCompCompMap_add(struct malnCompCompMap *mccm, struct malnComp *srcComp, struct malnComp *destComp) {
    stHash_insert(mccm->map, srcComp, destComp);
}

/* lookup a mapping, error if not found */
struct malnComp *malnCompCompMap_get(struct malnCompCompMap *mccm, struct malnComp *srcComp) {
    struct malnComp *destComp = stHash_search(mccm->map, srcComp);
    if (destComp == NULL) {
        errAbort("no mapping found for component: %s:%d-%d (%c)", srcComp->seq->orgSeqName, srcComp->start, srcComp->end, srcComp->strand);
    }
    return destComp;
}

/* lookup a mapping, NULL in not found */
struct malnComp *malnCompCompMap_find(struct malnCompCompMap *mccm, struct malnComp *srcComp) {
    return stHash_search(mccm->map, srcComp);
}

/* dump for debugging purposes */
void malnCompCompMap_dump(struct malnCompCompMap *mccm, FILE *fh, char *label) {
    fprintf(fh, "compCompMap: %s:\n", label);
    stHashIterator *keyIter = stHash_getIterator(mccm->map);
    struct malnComp *srcComp;
    while ((srcComp = stHash_getNext(keyIter)) != NULL) {
        struct malnComp *destComp = malnCompCompMap_get(mccm, srcComp);
        fputc('\t', fh);
        malnComp_prInfo(srcComp, fh);
        fputs(" ==> ", fh);
        malnComp_prInfo(destComp, fh);
        fputc('\n', fh);
    }
    stHash_destructIterator(keyIter);
}
