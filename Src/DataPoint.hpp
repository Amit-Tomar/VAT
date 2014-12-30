#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <iostream>
#include <vector>

template< typename dataPointFeatureType>

class DataPoint
{

public:

    DataPoint(std::vector <dataPointFeatureType> featureVector )
    {
        this->featureVector = featureVector;
    }

    std::vector <dataPointFeatureType> getFeatureVector()
    {
        return featureVector;
    }

    void setFeatureVector(std::vector <dataPointFeatureType> featureVector)
    {
        this->featureVector = featureVector;
    }

    dataPointFeatureType getFeatureI(int dimension)
    {
        if( dimension < featureVector.size() && dimension >= 0)
            return featureVector[dimension];
        else
        {
            std::cerr << "Invalid dimension for feature vector" << std::endl ;
            return (dataPointFeatureType)NULL;
        }
    }

    dataPointFeatureType setFeatureI(int dimension , dataPointFeatureType feature)
    {
        if( dimension < featureVector.size() && dimension >= 0)
        {
            featureVector[dimension] = feature;
        }

        else
        {
            std::cerr << "Invalid dimension for feature vector" << std::endl ;
            return (dataPointFeatureType)NULL;
        }
    }

    long int totalFeatures()
    {
        return featureVector.size();
    }

private:

    std::vector <dataPointFeatureType> featureVector ;
};

#endif // DATAPOINT_H
