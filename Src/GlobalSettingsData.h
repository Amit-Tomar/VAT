#ifndef GLOBALSETTINGSDATA_H
#define GLOBALSETTINGSDATA_H

typedef enum
{
    e_euclidean,
    e_cosine,
    e_jaccard,
    e_mahalanobis,
    e_manhattan,
    e_canberra,
    e_pearson
}dissimilarityFunction;

extern int  DIMENSIONS_IN_DATA;
extern int  DATA_SET_SIZE;
extern bool IS_FEATURE_VECTOR_FILE;
extern dissimilarityFunction DISTANCE_FUNCTION_TYPE;



#endif // GLOBALSETTINGSDATA_H
