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
        if( dimension < featureVector.size() )
            return featureVector[dimension];
        else
        {
            std::cerr << "Invalid dimension for feature vector" << std::endl ;
            return (dataPointFeatureType)NULL;
        }
    }

private:

    std::vector <dataPointFeatureType> featureVector ;
};

#endif // DATAPOINT_H
