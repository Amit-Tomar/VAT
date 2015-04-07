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

typedef enum
{
    e_blackNwhite,
    e_rgbRainbow,
    e_diverging_BLUE_RED,
    e_diverging_GREEN_RED,
    e_diverging_PURPLE_ORANGE,
    e_diverging_YELLOW_BLACK,
}colorMappings;

extern unsigned int  DIMENSIONS_IN_DATA;
extern unsigned int  DATA_SET_SIZE;
extern bool IS_FEATURE_VECTOR_FILE;
extern dissimilarityFunction DISTANCE_FUNCTION_TYPE;
extern colorMappings COLOR_MAP_TYPE;
extern unsigned int MAX_INPUT_ELEMENTS_PER_LINE;



#endif // GLOBALSETTINGSDATA_H
