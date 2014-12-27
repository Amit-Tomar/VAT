#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <vector>
#include <cmath>
#include <DataPoint.h>

template< typename dataPointFeatureType, typename dataPointDistanceType>

class DataSet
{
public:
    DataSet(){}
    virtual ~ DataSet() {}    

    virtual dataPointDistanceType getDistanceBetweenPoints(DataPoint <dataPointFeatureType> point1,DataPoint <dataPointFeatureType> point2)
    {
        // Eucledian

        dataPointDistanceType distance = 0 ;

        for( int i = 0 ; i < point1.getFeatureVector().size() ; ++i )
        {
            distance += pow ( point1.getFeatureI(i)-point2.getFeatureI(i), 2 );
        }

        return (dataPointDistanceType) sqrt(distance);
    }    

    std::vector <DataPoint<dataPointFeatureType> > & getDataPointsList()
    {
        return dataPointsList;
    }

    void pushDataPoint(DataPoint<dataPointFeatureType> data)
    {
        dataPointsList.push_back(data);
    }

    void randomRearrangeDataset()
    {
            for( unsigned int i = 0 ; i < dataPointsList.size() ; ++i)
            {
                int randomDatavaluePosition = rand() % dataPointsList.size();

                DataPoint<dataPointFeatureType> temp = dataPointsList[randomDatavaluePosition];
                dataPointsList[randomDatavaluePosition] = dataPointsList[i];
                dataPointsList[i] = temp;
            }
    }

private:

    std::vector <DataPoint<dataPointFeatureType> > dataPointsList;
};



#endif // DATASET_H
