#ifndef _EVAL_COMPARATOR_API_H_
#define _EVAL_COMPARATOR_API_H_

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>

#include "avl.h"
#include "bioioC.h"
#include "cactus.h"
#include "commonC.h"
#include "hashTableC.h"
#include "hashTableC_itr.h"
#include "sonLib.h"

#include "disjointset.h"

typedef struct _solo {
	char *name;
	int32_t pos;
} ASolo;

typedef struct _pair {
	char *seq1;
	char *seq2;
	int32_t pos1;
	int32_t pos2;
} APair;

typedef struct _trio {
	char *seq1;
	char *seq2;
	char *seq3;
	int32_t pos1;
	int32_t pos2;
	int32_t pos3;
	int32_t top; // tree topology
} ATrio;

typedef struct _trioNames {
        char *speciesA;
        char *speciesB;
        char *speciesC;
} TrioNames;

typedef struct _trioDecoder {
	char **nodeLabelArray;
	char **leafLabelArray;
	struct hashtable *treeLabelHash;
	int32_t **lcaMatrix;
	int32_t nodeNum;
	int32_t leafNum;
} TrioDecoder;

void populateNameHash(const char *mAFFile, struct hashtable *htp);
void intersectHashes(struct hashtable *h1, struct hashtable *h2, struct hashtable *h3);
void printNameHash(struct hashtable *h);
struct avl_table *compareMAFs_AB(const char *mAFFileA, const char *mAFFileB, int32_t numberOfSamples, struct hashtable *ht);
struct avl_table *compareMAFs_AB_Trio(const char *mAFFileA, const char *mAFFileB, int32_t numberOfSamples, struct hashtable *ht, struct List *speciesList);
void reportResults(struct avl_table *results_AB, const char *mAFFileA, const char *mAFFileB, FILE *fileHandle);
void reportResultsTrio(struct avl_table *results_AB, const char *mAFFileA, const char *mAFFileB, FILE *fileHandle);
void aPair_destruct(APair *pair, void *extraArgument);
void aTrio_destruct(ATrio *trio, void *extraArgument);

TrioDecoder *trioDecoder_construct(char *treestring);

#endif /* _EVAL_COMPARATOR_API_H_ */