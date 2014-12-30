#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <vector>
#include <cmath>
#include "DataPoint.hpp"
#include "Statistics.h"


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

    void normalizeDataset()
    {        
        evaluateStats();

        for( int i = 0 ; i < dataPointsList.size() ; ++i )
        {
            for( int j = 0 ; j < dataPointsList[i].totalFeatures() ; ++j )
                dataPointsList[i].setFeatureI(j , (dataPointsList[i].getFeatureI(j) - dataStatisticList[j].mean) / dataStatisticList[j].stdDeviation );
        }
    }

    void evaluateStats()
    {
        dataStatisticList.resize(dataPointsList[0].totalFeatures());

        std::cout << dataPointsList[0].totalFeatures() << std::endl ;

        // Calculate Mean
        for( int i = 0 ; i < dataPointsList.size() ; ++i )
        {
            for( int j = 0 ; j < dataPointsList[i].totalFeatures() ; ++j )
                dataStatisticList[j].mean += dataPointsList[i].getFeatureI(j);
        }

        for( int i = 0 ; i < dataPointsList[i].totalFeatures() ; ++i )
            dataStatisticList[i].mean /= dataPointsList.size();

        // Calculate Variance
        for( int i = 0 ; i < dataPointsList.size() ; ++i )
        {
            for( int j = 0 ; j < dataPointsList[i].totalFeatures() ; ++j )
                dataStatisticList[j].variance += pow(dataPointsList[i].getFeatureI(j) - dataStatisticList[j].mean,2) ;
        }

        for( int i = 0 ; i < dataPointsList[i].totalFeatures() ; ++i )
        {
            dataStatisticList[i].variance /= dataPointsList.size();
            dataStatisticList[i].stdDeviation = sqrt(dataStatisticList[i].variance);
        }

        for( int j = 0 ; j < dataPointsList[j].totalFeatures() ; ++j )
            std::cout << "Feature " << j << " Mean: " << dataStatisticList[j].mean << " Variance: " << dataStatisticList[j].variance << " StdDeviation: " << dataStatisticList[j].stdDeviation << std::endl ;
    }

private:

    std::vector <DataPoint<dataPointFeatureType> > dataPointsList;
    std::vector <Stats> dataStatisticList;
};



#endif // DATASET_H
